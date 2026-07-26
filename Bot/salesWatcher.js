import mysql from "mysql2/promise";
import { EmbedBuilder } from "discord.js";
import config from "./config.json" with { type: "json" };

const pool = mysql.createPool(config.mysql);

const POLL_INTERVAL_MS = 15_000;
const BATCH_LIMIT      = 50;

const SELECT_PENDING_SALES = `
  SELECT
    pss.sale_id,
    pss.buyer_char_name,
    pss.item_name,
    pss.item_count_sold,
    pss.price_per_item,
    pss.total_price,
    pso.char_index                AS seller_char_index,
    seller.a_name                 AS seller_char_name,
    CAST(bg.discord_id AS CHAR)   AS seller_discord_id
  FROM lc_db.personal_shop_sales_log     pss
  JOIN lc_db.personal_shop_offline       pso    ON pso.shop_id    = pss.shop_id
  JOIN lc_db.t_characters                seller ON seller.a_index = pso.char_index
  JOIN lc_db_auth.bg_user                bg     ON bg.user_code   = seller.a_user_index
  WHERE pss.notification_sent = 0
    AND bg.discord_id IS NOT NULL
    AND CAST(bg.discord_id AS CHAR) REGEXP '^[0-9]{17,20}$'
  ORDER BY pss.sale_id
  LIMIT ?
`;

const MARK_SENT = `
  UPDATE lc_db.personal_shop_sales_log
     SET notification_sent = 1
   WHERE sale_id IN (?)
`;

// ---------- formatting helpers ----------
const fmt = (n) => Number(n).toLocaleString("en-US");

function truncate(str, max) {
  if (!str) return "";
  return str.length > max ? str.slice(0, max - 1) + "…" : str;
}

/**
 * Build a compact, aligned embed for a batch of sales for one seller.
 * Uses a monospace code block so Item / Qty / Total / Ea. line up.
 */
function buildSalesEmbed(sellerName, sales) {
  const W = { item: 24, qty: 5, total: 12, unit: 11 };

  const header =
    "Item".padEnd(W.item) + " " +
    "Qty".padStart(W.qty) + "  " +
    "Total".padStart(W.total) + "  " +
    "Ea.".padStart(W.unit);
  const divider = "─".repeat(header.length);

  // Discord field value cap is 1024 chars; chunk if we overflow.
  const rowLines = sales.map(s =>
    truncate(s.item_name, W.item).padEnd(W.item) + " " +
    ("x" + s.item_count_sold).padStart(W.qty) + "  " +
    fmt(s.total_price).padStart(W.total) + "  " +
    fmt(s.price_per_item).padStart(W.unit)
  );

  const tableChunks = [];
  let current = [];
  let currentLen = header.length + divider.length + 20;
  for (const line of rowLines) {
    if (currentLen + line.length + 1 > 950) {
      tableChunks.push(current);
      current = [];
      currentLen = header.length + divider.length + 20;
    }
    current.push(line);
    currentLen += line.length + 1;
  }
  if (current.length) tableChunks.push(current);

  const buyers = [...new Set(sales.map(s => s.buyer_char_name))];
  const buyerLine = buyers.length === 1
    ? `**Buyer:** ${buyers[0]}`
    : `**Buyers:** ${buyers.join(", ")}`;

  const total = sales.reduce((a, s) => a + Number(s.total_price), 0);

  const embed = new EmbedBuilder()
    .setColor(0x2ecc71)
    .setAuthor({ name: "🛒 Offline Shop Sale" })
    .setDescription(`Hey **${sellerName}**, your shop made a sale!\n${buyerLine}`)
    .setTimestamp()
    .setFooter({ text: "LC BOT 2.0 · Offline Shop" });

  tableChunks.forEach((chunk, i) => {
    embed.addFields({
      name: i === 0 ? "\u200b" : "\u200b",
      value: "```\n" + header + "\n" + divider + "\n" + chunk.join("\n") + "\n```",
      inline: false,
    });
  });

  embed.addFields({
    name: "💰 Total This Batch",
    value: `**${fmt(total)} NAS**`,
    inline: false,
  });

  return embed;
}

// ---------- poll loop ----------
async function pollOnce(client) {
  const [rows] = await pool.query(SELECT_PENDING_SALES, [BATCH_LIMIT]);
  if (!rows.length) return;

  const bySeller = new Map();
  for (const r of rows) {
    let entry = bySeller.get(r.seller_char_index);
    if (!entry) {
      entry = { info: r, sales: [] };
      bySeller.set(r.seller_char_index, entry);
    }
    entry.sales.push(r);
  }

  const settledIds = [];

  for (const { info, sales } of bySeller.values()) {
    for (const s of sales) settledIds.push(s.sale_id);

    try {
      const user  = await client.users.fetch(info.seller_discord_id);
      const embed = buildSalesEmbed(info.seller_char_name, sales);
      await user.send({ embeds: [embed] });
      console.log(`[salesWatcher] DM sent to ${info.seller_char_name} (${sales.length} sale(s)).`);
    } catch (err) {
      console.error(`[salesWatcher] DM failed for ${info.seller_char_name} (${info.seller_discord_id}): ${err.message}`);
    }
  }

  if (settledIds.length) {
    await pool.query(MARK_SENT, [settledIds]);
  }
}

export function startSalesWatcher(client) {
  console.log(`[salesWatcher] Started (poll every ${POLL_INTERVAL_MS / 1000}s).`);
  let inFlight = false;

  const tick = async () => {
    if (inFlight) return;
    inFlight = true;
    try {
      await pollOnce(client);
    } catch (err) {
      console.error("[salesWatcher] pollOnce error:", err);
    } finally {
      inFlight = false;
    }
  };

  tick();
  setInterval(tick, POLL_INTERVAL_MS);
}