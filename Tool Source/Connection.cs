using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
    public class Settings
    {
        public string Episode { get; set; } = "";
        public string ClientPath { get; set; } = "";
        public string SqlHost { get; set; } = "";
        public string SqlUser { get; set; } = "";
        public string SqlPassword { get; set; } = "";
        public string SqlDatabase { get; set; } = "";
        public string SqlDbDatabase { get; set; } = "";
        public string SqlDbAuth { get; set; } = "";
        public string SqlDbDataLod { get; set; } = "";
        public string Language { get; set; } = "";

        public Dictionary<string, string> PathPre { get; set; } = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
        public Dictionary<string, string> PathShip { get; set; } = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
        public Dictionary<string, string> StrPathShip { get; set; } = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
        public Dictionary<string, string> StrPathPre { get; set; } = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
    }

    public class Connection
    {
        private readonly string _settingsPath;
        public Settings Settings { get; private set; }

        public Connection()
        {
            _settingsPath = Path.Combine(Directory.GetCurrentDirectory(), "Config", "Settings.cfg");
            LoadSettings();
        }

        private void LoadSettings()
        {
            // If file doesn't exist, create a blank one with only section headers
            if (!File.Exists(_settingsPath))
            {
                MessageBox.Show("Settings file not found. A blank file will be created.");
                Directory.CreateDirectory(Path.GetDirectoryName(_settingsPath));

                string[] blankSettings =
                {
                    "[## MYSQL]",
                    "[path_pre]",
                    "[path_ship]",
                    "[Str_Path_Ship]",
                    "[Str_Path_Pre]"
                };

                File.WriteAllLines(_settingsPath, blankSettings);
            }

            Settings = new Settings();
            string currentSection = "";

            foreach (var line in File.ReadAllLines(_settingsPath))
            {
                string trimmed = line.Trim();

                // Skip empty lines or comments
                if (string.IsNullOrWhiteSpace(trimmed) || trimmed.StartsWith("##"))
                    continue;

                // Detect section headers
                if (trimmed.StartsWith("[") && trimmed.EndsWith("]"))
                {
                    currentSection = trimmed.Substring(1, trimmed.Length - 2).Trim();
                    continue;
                }

                // Parse key=value
                var parts = trimmed.Split(new[] { '=' }, 2);
                if (parts.Length != 2)
                    continue;

                string key = parts[0].Trim();
                string value = parts[1].Trim();

                switch (currentSection.ToLower())
                {
                    case "## mysql":
                        switch (key.ToUpper())
                        {
                            case "EPISODE": Settings.Episode = value; break;
                            case "CLIENTPATH": Settings.ClientPath = value; break;
                            case "SQL_HOST": Settings.SqlHost = value; break;
                            case "SQL_USER": Settings.SqlUser = value; break;
                            case "SQL_PASSWORD": Settings.SqlPassword = value; break;
                            case "SQL_DATABASE": Settings.SqlDatabase = value; break;
                            case "SQL_DB_DATABASE": Settings.SqlDbDatabase = value; break;
                            case "SQL_DB_AUTH": Settings.SqlDbAuth = value; break;
                            case "SQL_DB_DATALOD": Settings.SqlDbDataLod = value; break;
                            case "LANGUAGE": Settings.Language = value; break;
                        }
                        break;

                    case "path_pre": Settings.PathPre[key] = value; break;
                    case "path_ship": Settings.PathShip[key] = value; break;
                    case "str_path_ship": Settings.StrPathShip[key] = value; break;
                    case "str_path_pre": Settings.StrPathPre[key] = value; break;
                }
            }
        }
    }
}
