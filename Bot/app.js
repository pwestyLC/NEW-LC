import { Client, GatewayIntentBits, Partials, EmbedBuilder } from "discord.js";
import mysql from "mysql2/promise"; // Promise-based MySQL
import config from "./config.json" with { type: "json" };
import net from "net";
import { startCrashWatcher } from "./crashWatcher.js";
import { startSalesWatcher } from "./salesWatcher.js";
// =============================================================
// GM Command Senders
// =============================================================

// Broadcast GM command to all configured servers
async function sendGMCommand(command) {
  const results = [];

  for (const srv of config.gmServers) {
    const { host, port, name } = srv;
    try {
      await new Promise((resolve, reject) => {
        const client = new net.Socket();

        client.connect(port, host, () => {
          console.log(`[BOT] Sending GM command to ${name}: ${command}`);
          client.write(command);
        });

        client.on("data", (data) => {
          const response = data.toString().trim();
          console.log(`[BOT] ${name} response: ${response}`);
          client.destroy();
          resolve(response);
        });

        client.on("error", (err) => {
          console.error(`[BOT] Error connecting to ${name}: ${err.message}`);
          reject(err);
        });

        client.on("close", () => {
          console.log(`[BOT] Connection to ${name} closed`);
        });
      });
      results.push(`[${name}] OK`);
    } catch (err) {
      results.push(`[${name}] FAIL: ${err.message}`);
    }
  }

  return results.join("\n");
}

// Send GM command to a specific GameServer
function sendGMCommandTo(server, command) {
  return new Promise((resolve, reject) => {
    const client = new net.Socket();

    client.connect(server.port, server.host, () => {
      console.log(`[BOT] Sending GM command to ${server.name} (${server.host}:${server.port}): ${command}`);
      client.write(command);
    });

    client.on("data", (data) => {
      const response = data.toString().trim();
      console.log(`[BOT] Response from ${server.name}: ${response}`);
      client.destroy();
      resolve(response);
    });

    client.on("error", (err) => {
      console.error(`[BOT] Error on ${server.name}: ${err.message}`);
      reject(err);
    });

    client.on("close", () => {
      console.log(`[BOT] Connection to ${server.name} closed`);
    });
  });
}


// Create Discord client with intents
const client = new Client({
    intents: [
        GatewayIntentBits.Guilds,
        GatewayIntentBits.GuildMessages,
        GatewayIntentBits.MessageContent
    ],
    partials: [Partials.Channel, Partials.Message]
});

// Create MySQL connection pool
const pool = mysql.createPool(config.mysql);

// Utility functions
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function randomIntFromInterval(min, max) { // inclusive
    return Math.floor(Math.random() * (max - min + 1) + min);
}

// Global flags
let running = false;
let running2 = false;
let startlogInterval;
let lastIndex = 0;


// Start watcher once bot is fully ready
client.once("clientReady", () => {
  console.log(`${client.user.tag} is online!`);
  startCrashWatcher(client);
  startSalesWatcher(client);
});

// Message event
client.on('messageCreate', async (message) => {
    if (message.author.bot || !message.guild) return;

    const prefix = '!';
    if (!message.content.startsWith(prefix)) return;

    const args = message.content.slice(prefix.length).trim().split(/ +/g);
    const command = args.shift().toLowerCase();

    // Only admins can use commands
    if (
  command !== 'siege' &&
  !message.member.permissions.has('Administrator') &&
  !message.member.roles.cache.some(role => role.name.toLowerCase() === 'developer')
) {
  return message.channel.send(
    "Slash commands are for admins or developers only, use ! instead. Refer to #bot-commands."
  );
}

    switch (command) {
        case 'siege': {
  try {
    const [rows] = await pool.query(`
      SELECT a_zone_index, a_owner_guild_name, a_next_war_time 
      FROM lc_db.t_castle
      WHERE a_zone_index IN (4, 7)
    `);

    if (!rows.length)
      return message.channel.send("No siege data found.");

    for (const row of rows) {
      let zoneName, color;

      // Convert zone index and color
      if (row.a_zone_index === 4) {
        zoneName = "Dratan Castle";
        color = 0xFFD700; // Golden yellow
      } else if (row.a_zone_index === 7) {
        zoneName = "Merac Castle";
        color = 0xFF4500; // Bright orange red
      } else {
        zoneName = `Zone ${row.a_zone_index}`;
        color = 0x888888; // Neutral gray fallback
      }

      // Convert timestamp to readable UTC format
      const timestamp = Number(row.a_next_war_time);
      const nextWarTime = new Date(timestamp * 1000).toUTCString();

      const embed = new EmbedBuilder()
        .setTitle(zoneName)
        .setDescription("⚔️ **Current Siege Information**")
        .setColor(color)
        .addFields(
          { name: "Owner Guild", value: row.a_owner_guild_name || "None", inline: true },
          { name: "Next Siege Time (UTC)", value: nextWarTime, inline: true }
        )
        .setTimestamp()
        .setFooter({ text: "LC BOT 2.0" });

      await message.channel.send({ embeds: [embed] });
    }
  } catch (err) {
    console.error(err);
    message.channel.send("❌ Error fetching siege data.");
  }
}
break;

       case 'itemgive': {
  if (args.length < 2)
    return message.channel.send("Usage: /itemgive <charIndex> <itemId> [plus] [flag] [count]");

  const charIndex = parseInt(args.shift());
  const dbindex = parseInt(args.shift());
  const plus = parseInt(args.shift() || "0");
  const flag = parseInt(args.shift() || "0");
  const count = parseInt(args.shift() || "1");

  if (isNaN(charIndex) || isNaN(dbindex))
    return message.channel.send("Invalid input: character index and item ID are required.");

  try {
    // Step 1: Get the account (portal) ID from t_characters
    const [charRows] = await pool.query(
      `SELECT a_user_index FROM lc_db.t_characters WHERE a_index = ? LIMIT 1`,
      [charIndex]
    );

    if (!charRows.length)
      return message.channel.send("❌ Character not found in t_characters table.");

    const portalIndex = charRows[0].a_user_index;

    // Step 2: Find subserver from t_users using a_portal_index
    const [userRows] = await pool.query(
      `SELECT a_subnum FROM lc_db_auth.t_users WHERE a_portal_index = ? LIMIT 1`,
      [portalIndex]
    );

    if (!userRows.length)
      return message.channel.send("❌ Account not found in t_users table (likely offline).");

    const { a_subnum } = userRows[0];

    if (!a_subnum || a_subnum < 1)
      return message.channel.send("⚠️ That player isn't connected to any subserver.");

    // Step 3: Match to correct GameServer
    const server = config.gmServers.find(s => s.name.endsWith(String(a_subnum)));

    if (!server)
      return message.channel.send(`❌ No GameServer configured for subserver ${a_subnum}.`);

    // Step 4: Send GM command
    const cmd = `gm_itemget ${charIndex} ${dbindex} ${plus} ${flag} ${count}`;
    const response = await sendGMCommandTo(server, cmd);

    message.channel.send(
      `🎁 Sent item **${dbindex}** (x${count}) to char index ${charIndex} on **${server.name}**\nResponse: \`${response}\``
    );

  } catch (err) {
    console.error(err);
    message.channel.send("❌ Failed to send item to player.");
  }
}
break;


        case 'shutdown': {
    if (args.length < 4)
        return message.channel.send("Usage: !shutdown <serverno> <subno> <seconds> <message>");

    const serverno = parseInt(args[0]);
    const subno = parseInt(args[1]);
    const seconds = parseInt(args[2]);
    const msg = args.slice(3).join(' ');

    if (isNaN(serverno) || isNaN(subno) || isNaN(seconds))
        return message.channel.send("Invalid format. Example: /shutdown 1 2 60 Server maintenance soon!");

    try {
        const cmd = `gm_shutdown ${serverno} ${subno} ${seconds} ${msg}`;
        await sendGMCommand(cmd);
        message.channel.send(`⚠️ Shutdown initiated for Server ${serverno}-${subno} in ${seconds} sec.\nMessage: "${msg}"`);
    } catch (err) {
        console.error(err);
        message.channel.send("❌ Failed to send shutdown command.");
    }
}
break;

case 'reboot': {
    if (args.length < 3)
        return message.channel.send("Usage: !reboot <scope> <seconds> <message>");

    const scope = args[0].toLowerCase(); // all, server, subserver
    const seconds = parseInt(args[1]);
    const msg = args.slice(2).join(' ');

    if (isNaN(seconds))
        return message.channel.send("Invalid seconds value. Example: /reboot all 60 Restarting soon.");

    if (!['all', 'server', 'subserver'].includes(scope))
        return message.channel.send("Invalid scope. Use: all | server | subserver");

    try {
        const cmd = `gm_reboot ${scope} ${seconds} ${msg}`;
        await sendGMCommand(cmd);
        message.channel.send(`🔁 Reboot scheduled for "${scope}" in ${seconds} sec.\nMessage: "${msg}"`);
    } catch (err) {
        console.error(err);
        message.channel.send("❌ Failed to send reboot command.");
    }
}
break;


        case 'where':
    try {
        const [rows] = await pool.query(`
            SELECT z.a_name AS zone_name, COUNT(*) AS user_count
            FROM lc_db_auth.t_users u
            JOIN lc_data.t_zonedata z ON u.a_zone_num = z.a_zone_index
            WHERE u.a_zone_num != -1
            GROUP BY u.a_zone_num
            ORDER BY user_count DESC
        `);

        if (!rows.length) {
            return message.channel.send("No users currently online in any zones.");
        }

        // Build embed
        const embed = new EmbedBuilder()
            .setTitle("🌐 Zone Population")
            .setDescription("Shows the number of online players in each active zone.")
            .setColor(0x3498db)
            .setTimestamp()
            .setFooter({ text: 'LC BOT 2.0' });

        let total = 0;
        rows.forEach(row => {
            embed.addFields({
                name: row.zone_name,
                value: `${row.user_count} player${row.user_count !== 1 ? 's' : ''}`,
                inline: true
            });
            total += row.user_count;
        });

        embed.addFields({ name: "🧮 Total Online", value: `${total}`, inline: false });

        message.channel.send({ embeds: [embed] });
    } catch (err) {
        console.error(err);
        message.channel.send("Error fetching zone data.");
    }
    break;

        case 'purgeuser': {
  const targetArg = args[0];
  const amount = parseInt(args[1]);

  if (!targetArg || isNaN(amount) || amount <= 0 || amount > 100) {
    return message.channel.send("Usage: `!purgeuser <username|mention|id> <1-100>`");
  }

  // Try to find the user
  let targetMember =
    message.mentions.members.first() || // @mention
    message.guild.members.cache.get(targetArg) || // ID
    message.guild.members.cache.find(member =>
      member.user.tag.toLowerCase() === targetArg.toLowerCase() ||
      member.displayName.toLowerCase() === targetArg.toLowerCase()
    );

  if (!targetMember) {
    return message.channel.send(`Could not find user "${targetArg}".`);
  }

  // Fetch up to 100 recent messages
  const fetched = await message.channel.messages.fetch({ limit: 100 });
  const userMessages = fetched.filter(m => m.author.id === targetMember.user.id).first(amount);

  if (userMessages.length === 0) {
    return message.channel.send(`No recent messages found from ${targetMember.user.tag}`);
  }

  try {
    await message.channel.bulkDelete(userMessages, true);
    message.channel.send(`🧹 Deleted ${userMessages.length} messages from ${targetMember.user.tag}`)
      .then(msg => setTimeout(() => msg.delete(), 4000));
  } catch (err) {
    console.error(err);
    message.channel.send("Failed to purge messages. Note: messages older than 14 days can't be deleted.");
  }
}
break;



        case 'kicked':
            const targetName = args[0];
            if (!targetName) return message.channel.send("Usage: `/kick <playername>`");

            try {
                const response = await sendGMCommand(`gm_kick ${targetName}`);
                message.channel.send(`✅ Kick command sent for **${targetName}**\nResponse: \`${response || 'no response'}\``);
            } catch (err) {
                console.error(err);
                message.channel.send(`❌ Failed to send kick command: ${err.message}`);
            }
            break;

            case 'echo': {
    if (args.length < 2) return message.channel.send("Usage: /echo <scope> <message> or /echo zone <zoneIndex> <message>");

    let scope = args.shift().toLowerCase(); // "all", "server", "subserver", "zone"
    let zoneIndex = null;
    let msg;

    if (scope === "zone") {
        if (args.length < 2) return message.channel.send("Usage: /echo zone <zoneIndex> <message>");
        zoneIndex = parseInt(args.shift());
        if (isNaN(zoneIndex)) return message.channel.send("Invalid zone index.");
        msg = args.join(' ');
    } else {
        msg = args.join(' ');
    }

    // sendGMCommand will call your game server TCP listener
    try {
        let cmdStr = `gm_echo ${scope}`;
        if (zoneIndex !== null) cmdStr += ` ${zoneIndex}`;
        cmdStr += ` ${msg}`;

        await sendGMCommand(cmdStr);

        let reply = (scope === "zone") ? `zone ${zoneIndex}` : scope;
        message.channel.send(`Echo sent to ${reply}: ${msg}`);
    } catch (err) {
        console.error(err);
        message.channel.send("Failed to send echo command.");
    }
}
break;

        case 'draw':
            try {
                const [countRow] = await pool.query(
                    `SELECT COUNT(*) AS count FROM lc_db_auth.t_users WHERE a_subnum >=1 AND a_zone_num >=0`
                );
                const count = countRow[0].count;
                if (count <= 0) return message.channel.send("No eligible users found.");

                let charData;
                let attempts = 0;
                while (!charData && attempts < count) {
                    const [rows] = await pool.query(
                        `SELECT a_index, a_idname, a_charidx, a_subnum, a_zone_num
                         FROM lc_db_auth.t_users
                         WHERE a_subnum >=1 AND a_zone_num >=0
                         ORDER BY RAND() LIMIT 1`
                    );

                    const row = rows[0];
                    const [charRows] = await pool.query(
                        `SELECT a_user_index, a_name, a_nick, a_admin, a_discord_winner, a_ctid
                         FROM lc_db.t_characters
                         WHERE a_index = ?`, [row.a_charidx]
                    );

                    const char = charRows[0];
                    if (char.a_admin === 0 && char.a_discord_winner !== 1) {
                        charData = { ...row, ...char };
                        break;
                    }
                    attempts++;
                }

                if (!charData) return message.channel.send("No valid winner found.");

                // Pick random item
                const rndInt = randomIntFromInterval(1, 9);
                const items = Object.values(config.itemdata);
                const itemid = items[rndInt - 1];

                // Update winner and give item
                await pool.query(`UPDATE lc_db.t_characters SET a_discord_winner = 1 WHERE a_index = ?`, [charData.a_charidx]);

                const tablename = charData.a_user_index.toString().slice(-1);
                await pool.query(
                    `INSERT INTO lc_db_auth.t_gift0${tablename} 
                    (a_index, a_server, a_send_user_idx, a_send_char_name, a_send_msg, a_recv_user_idx, a_recv_char_name, a_send_date, a_ctid, a_use_date, a_use_char_idx)
                    VALUES (NULL, 1, 120362, 'DISCORD BOT', 'discord reward winner', ?, ?, NOW(), ?, '0000-00-00 00:00:00', 0)`,
                    [charData.a_user_index, charData.a_nick, itemid]
                );

                const embed = new EmbedBuilder()
                    .setTitle(`${charData.a_nick}`)
                    .setDescription("YOU WON THE RANDOM DRAW CONTEST")
                    .addFields(
                        { name: 'Sub-Server', value: String(charData.a_subnum), inline: true },
                        { name: 'Zone Num', value: String(charData.a_zone_num), inline: true },
                        { name: 'Item Won', value: String(itemid), inline: true }
                    )
                    .setTimestamp()
                    .setFooter({ text: 'LC BOT 2.0' });

                message.channel.send({ embeds: [embed] });
            } catch (err) {
                console.error(err);
                message.channel.send("An error occurred while performing the draw.");
            }
            break;

        case 'showonline':
            try {
                const [rows] = await pool.query(`SELECT COUNT(*) AS count FROM t_users WHERE a_zone_num >=0`);
                message.channel.send("TOTAL USERS ONLINE = " + rows[0].count);
            } catch (err) {
                console.error(err);
                message.channel.send("Error fetching online users.");
            }
            break;

        case 'banned':
            try {
                const [rows] = await pool.query(`SELECT a_idname FROM t_users WHERE a_enable = 0`);
                if (!rows.length) return message.channel.send("No banned users.");
                rows.forEach(row => message.channel.send(`${row.a_idname}`));
            } catch (err) {
                console.error(err);
                message.channel.send("Error fetching banned users.");
            }
            break;

        case 'didihack':
            const memberName = args.join(' ');
            if (!memberName) return message.channel.send("Member Name can't be blank");

            try {
                const [rows] = await pool.query(
                    `SELECT a_hacktype, a_nick, a_index, a_char_id, a_enable
                     FROM lc_db.t_hack_characters
                     WHERE a_char_id REGEXP ? AND a_hacktype = a_hacktype LIMIT 5`,
                    [memberName]
                );

                if (!rows.length) return message.channel.send("No hacks found for that user.");

                rows.forEach(row => {
                    const embed = new EmbedBuilder()
                        .setTitle(`${row.a_char_id}`)
                        .setDescription("Information about hacks you may have used")
                        .addFields({ name: "Hacks", value: row.a_hacktype })
                        .setTimestamp()
                        .setFooter({ text: 'LC BOT 2.0' });

                    message.channel.send({ embeds: [embed] });
                });
            } catch (err) {
                console.error(err);
                message.channel.send("Error fetching hack info.");
            }
            break;

        case 'itemfind':
            if (args.length < 1) return message.channel.send("Item Name can't be blank");
            const itemName = args.join(' ').replace(/['"]/g, '');

            try {
                const [rows] = await pool.query(`SELECT * FROM lc_data.t_item WHERE a_name = ?`, [itemName]);
                if (!rows.length) return message.channel.send("Item not found.");

                rows.forEach(row => {
                    const embed = new EmbedBuilder()
                        .setTitle(row.a_name)
                        .setDescription("Information about This Item")
                        .addFields(
                            { name: "Level", value: String(row.a_name_usa) },
                            { name: "NPC", value: row.a_descr_usa }
                        )
                        .setTimestamp()
                        .setFooter({ text: 'LC BOT 2.0' });

                    message.channel.send({ embeds: [embed] });
                });
            } catch (err) {
                console.error(err);
                message.channel.send("Error fetching item info.");
            }
            break;

        case 'auction':
            try {
                const [rows] = await pool.query(
                    `SELECT a_index, a_item_name 
                     FROM lc_db.t_tradeagent 
                     ORDER BY a_index DESC LIMIT 10`
                );
                rows.forEach(row => {
                    const embed = new EmbedBuilder()
                        .setTitle(`${row.a_index}`)
                        .setDescription("Item Information")
                        .addFields({ name: "Item Name", value: row.a_item_name })
                        .setTimestamp()
                        .setFooter({ text: 'LC BOT 2.0' });

                    message.channel.send({ embeds: [embed] });
                });
            } catch (err) {
                console.error(err);
                message.channel.send("Error fetching auction items.");
            }
            break;


// STARTLOG command
case 'startlog':
    if (running) return message.channel.send("Thread already running.");
    running = true;

    

    startlogInterval = setInterval(async () => {
        if (!running) return; // extra safety

        try {
            const [rows] = await pool.query(
                `SELECT * FROM lc_db.t_hack_characters WHERE a_index > ? ORDER BY a_index ASC`,
                [lastIndex]
            );

            for (const row of rows) {
                message.channel.send(`${row.a_char_id} Used HACK ---> ${row.a_hacktype}.`);
                lastIndex = Math.max(lastIndex, row.a_index);
            }
        } catch (err) {
            console.error(err);
        }
    }, 5000);
    break;

// STOP command
case 'stop':
    if (!running) return message.channel.send("Thread is not running.");
    running = false;
    if (startlogInterval) {
        clearInterval(startlogInterval);
        startlogInterval = null;
    }
    message.channel.send("startlog thread stopped.");
    break;

        default:
            message.channel.send("Unknown command.");
    }
});
// Login bot
client.login(config.client.token);
