import fs from "fs";
import path from "path";
import { EmbedBuilder } from "discord.js";

// === CONFIGURATION ===
const SERVER_DIR = "/home/Server"; // root of GameServer folders
const CHANNEL_ID = "1436794153609466026"; // Discord channel for crash alerts
const WATCH_INTERVAL = 3000; // milliseconds between file checks

// Automatically watch all bt_crash files in GameServer1..4
const CRASH_FILES = [1, 2, 3, 4].map(
  i => path.join(SERVER_DIR, `GameServer${i}`, `bt_crash${i}.txt`)
);

// Track last known modification times
const fileTimes = new Map();

// === MAIN FUNCTION ===
export function startCrashWatcher(client) {
  console.log("[CrashWatcher] Starting file watcher...");

  for (const file of CRASH_FILES) {
    try {
      // Initialize timestamp
      if (fs.existsSync(file)) {
        fileTimes.set(file, fs.statSync(file).mtimeMs);
      } else {
        console.warn(`[CrashWatcher] File not found (will watch later): ${file}`);
        continue;
      }

      // Watch file for changes
      fs.watchFile(file, { interval: WATCH_INTERVAL }, (curr, prev) => {
        if (curr.mtimeMs !== prev.mtimeMs) {
          fileTimes.set(file, curr.mtimeMs);
          handleCrashDetected(file, client);
        }
      });

      console.log(`[CrashWatcher] Watching ${file}`);
    } catch (err) {
      console.error(`[CrashWatcher] Error watching ${file}: ${err.message}`);
    }
  }
}

// === CRASH DETECTION HANDLER ===
async function handleCrashDetected(file, client) {
  const fileName = path.basename(file);
  const serverNum = fileName.match(/\d+/)?.[0] || "?";
  console.log(`[CrashWatcher] Crash detected in GameServer${serverNum}`);

  let firstLine = "Unknown crash time";
  try {
    const content = fs.readFileSync(file, "utf8");
    firstLine =
      content.split("\n").find(line => line.toLowerCase().includes("crash detected")) ||
      firstLine;
  } catch (err) {
    console.error(`[CrashWatcher] Could not read ${file}: ${err.message}`);
  }

  const embed = new EmbedBuilder()
    .setTitle(`⚠️ Crash Detected - GameServer ${serverNum}`)
    .setDescription(`\`\`\`${firstLine}\`\`\``)
    .setColor(0xff0000)
    .setTimestamp()
    .setFooter({ text: "Last Chaos Server Monitor" });

  try {
    const channel = await client.channels.fetch(CHANNEL_ID);
    if (!channel) {
      console.error(`[CrashWatcher] Channel ${CHANNEL_ID} not found.`);
      return;
    }

    const guild = channel.guild;
    // Dynamically find roles by name
    const devRole = guild.roles.cache.find(r => r.name.toLowerCase() === "developer");
    const adminRole = guild.roles.cache.find(r => r.name.toLowerCase() === "administrator");

    let mentions = "";
    if (devRole) mentions += `<@&${devRole.id}> `;
    if (adminRole) mentions += `<@&${adminRole.id}> `;

    await channel.send({
      content: `${mentions}🚨 Crash detected on **GameServer ${serverNum}**`,
      embeds: [embed],
    });

    console.log(`[CrashWatcher] Discord alert sent for GameServer${serverNum}`);
  } catch (err) {
    console.error(`[CrashWatcher] Failed to send Discord message: ${err.message}`);
  }
}
