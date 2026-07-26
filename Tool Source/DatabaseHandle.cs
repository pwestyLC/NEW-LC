using LcDevPack_TeamDamonA.Tools;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Collections.Concurrent;

namespace LcDevPack_TeamDamonA
{
    public class DatabaseHandle
    {
        public static Connection connection = new Connection();

        private string Host => connection.Settings.SqlHost;
        private string User => connection.Settings.SqlUser;
        private string Password => connection.Settings.SqlPassword;
        private string Database => connection.Settings.SqlDatabase;
        private string Language => connection.Settings.Language;

        private string name;
        public List<string> Menu = new List<string>();

        // image cache to avoid repeatedly loading files and exhausting GDI handles
        private static readonly ConcurrentDictionary<string, Image> _imageCache = new ConcurrentDictionary<string, Image>(StringComparer.OrdinalIgnoreCase);

        private static Image LoadImageClone(string path)
        {
            try
            {
                if (!File.Exists(path)) return null;
                byte[] data = File.ReadAllBytes(path);
                using (var ms = new MemoryStream(data))
                using (var tmp = Image.FromStream(ms))
                {
                    return new Bitmap(tmp); // clone so we can dispose stream safely
                }
            }
            catch
            {
                return null;
            }
        }

        private static Image GetCachedImage(string path)
        {
            if (string.IsNullOrEmpty(path)) return null;
            return _imageCache.GetOrAdd(path, p => LoadImageClone(p));
        }

        private string EncodeMySqlString(string value)
            => value.Replace("\\", "\\\\").Replace("'", "\\'");

        private string GetConnectionString(string host, string user, string password, string database)
            => $"server={host};port=3306;user={user};password={password};database={database};charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;";

        private string GetConnectionString()
            => GetConnectionString(Host, User, Password, Database);

        // universal SELECT helper
        private DataTable RunSelect(string query)
        {
            using var conn = new MySqlConnection(GetConnectionString());
            using var cmd = new MySqlCommand(query, conn);
            using var adapter = new MySqlDataAdapter(cmd);
            DataTable table = new DataTable();
            conn.Open();
            adapter.Fill(table);
            return table;
        }

        // language column selectors
        public string StringFromLanguage() =>
            Language switch
            {
                "GER" => "a_name_ger",
                "POL" => "a_name_pld",
                "BRA" => "a_name_brz",
                "RUS" => "a_name_rus",
                "FRA" => "a_name_frc",
                "ESP" => "a_name_spn",
                "MEX" => "a_name_mex",
                "THA" => "a_name_thai",
                "ITA" => "a_name_ita",
                "USA" => "a_name_usa",
                _ => null
            };

        public string StringFromLanguageCatalog() =>
            Language switch
            {
                "GER" => "a_ctname_ger",
                "POL" => "a_ctname_pld",
                "BRA" => "a_ctname_brz",
                "RUS" => "a_ctname_rus",
                "FRA" => "a_ctname_frc",
                "ESP" => "a_ctname_spn",
                "MEX" => "a_ctname_mex",
                "THA" => "a_ctname_tld",
                "ITA" => "a_ctname_ita",
                "USA" => "a_ctname_usa",
                _ => null
            };

        // searches for items by language column
        public List<string> SearchList(string searchString, string[] rowName, string tableName)
        {
            try
            {
                string colLang = StringFromLanguage();
                string term = EncodeMySqlString(searchString);
                string query = $"SELECT a_index, {colLang} FROM {tableName} " +
                               $"WHERE {colLang} LIKE '%{term}%' OR a_index LIKE '%{term}%' ORDER BY a_index;";

                DataTable dt = RunSelect(query);
                List<string> results = new List<string>();

                foreach (DataRow row in dt.Rows)
                {
                    string entry = "";
                    for (int i = 0; i < rowName.Length; i++)
                    {
                        entry += row[rowName[i]].ToString();
                        if (i == 0 && rowName.Length > 1)
                            entry += " - ";
                    }
                    results.Add(entry);
                }

                return results;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return new List<string> { "Error" };
            }
        }

        // same as above but for catalogs
        public List<string> SearchListCatalog(string searchString, string[] rowName, string tableName)
        {
            try
            {
                string colLang = StringFromLanguageCatalog();
                string term = EncodeMySqlString(searchString);
                string query = $"SELECT a_ctid, {colLang} FROM {tableName} " +
                               $"WHERE {colLang} LIKE '%{term}%' OR a_ctid LIKE '%{term}%' ORDER BY a_ctid;";

                DataTable dt = RunSelect(query);
                List<string> results = new List<string>();

                foreach (DataRow row in dt.Rows)
                {
                    string entry = "";
                    for (int i = 0; i < rowName.Length; i++)
                    {
                        entry += row[rowName[i]].ToString();
                        if (i == 0 && rowName.Length > 1)
                            entry += " - ";
                    }
                    results.Add(entry);
                }

                return results;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return new List<string> { "Error" };
            }
        }

        // RESTORED and FIXED
        public List<string> SelectMySqlReturnList(
            string[] rowName,
            string Host,
            string User,
            string Password,
            string Database,
            string Query)
        {
            try
            {
                using var conn = new MySqlConnection(GetConnectionString(Host, User, Password, Database));
                using var cmd = new MySqlCommand(Query, conn);
                using var adapter = new MySqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                conn.Open();
                adapter.Fill(dt);

                List<string> results = new List<string>();
                foreach (DataRow row in dt.Rows)
                {
                    string entry = "";
                    for (int i = 0; i < rowName.Length; i++)
                    {
                        entry += row[rowName[i]].ToString();
                        if (i == 0 && rowName.Length > 1)
                            entry += " - ";
                    }
                    results.Add(entry);
                }

                return results;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return new List<string> { "Error" };
            }
        }

        // RESTORED and FIXED
        public List<string> SelectMySqlExplodedReturnList(
            string[] rowName,
            string Host,
            string User,
            string Password,
            string Database,
            string Query)
        {
            try
            {
                using var conn = new MySqlConnection(GetConnectionString(Host, User, Password, Database));
                using var cmd = new MySqlCommand(Query, conn);
                using var adapter = new MySqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                conn.Open();
                adapter.Fill(dt);

                List<string> results = new List<string>();
                foreach (DataRow row in dt.Rows)
                {
                    foreach (string column in rowName)
                    {
                        string raw = row[column].ToString();
                        string[] parts = raw.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                        results.AddRange(parts);
                    }
                }

                return results;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return new List<string> { "Error" };
            }
        }

        // RESTORED and FIXED
        public string[] SelectMySqlReturnArray(
            string Host,
            string User,
            string Password,
            string Database,
            string Query,
            string[] rows)
        {
            try
            {
                using var conn = new MySqlConnection(GetConnectionString(Host, User, Password, Database));
                using var cmd = new MySqlCommand(Query, conn);
                using var adapter = new MySqlDataAdapter(cmd);
                DataTable dt = new DataTable();
                conn.Open();
                adapter.Fill(dt);

                string[] result = new string[rows.Length];
                if (dt.Rows.Count > 0)
                {
                    DataRow row = dt.Rows[0];
                    for (int i = 0; i < rows.Length; i++)
                        result[i] = row[rows[i]].ToString();
                }

                return result;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return Array.Empty<string>();
            }
        }

        public void SendQueryMySql(string Host, string User, string Password, string Database, string Query)
        {
            try
            {
                using var conn = new MySqlConnection(GetConnectionString(Host, User, Password, Database));
                using var cmd = new MySqlCommand(Query, conn);
                conn.Open();
                cmd.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
            }
        }

        public int CountByRow(string Host, string User, string Password, string Database, string Query)
        {
            try
            {
                using var conn = new MySqlConnection(GetConnectionString(Host, User, Password, Database));
                using var cmd = new MySqlCommand(Query, conn);
                conn.Open();
                return Convert.ToInt32(cmd.ExecuteScalar());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "SQL Error");
                return 0;
            }
        }
        // === ICON AND NAME HELPERS ===

        public Bitmap IconFast(int itemID)
        {
            // create output bitmap
            Bitmap bmp = new Bitmap(32, 32);

            // draw fallback first
            var fallback = GetCachedImage("icons/ItemBtn0.png");
            using (Graphics g = Graphics.FromImage(bmp))
            {
                if (fallback != null)
                    g.DrawImage(fallback, new Rectangle(0, 0, 32, 32));
                else
                    g.Clear(Color.Transparent);
            }

            if (itemID == -1)
                return bmp;

            ticon icon = IconList.List.Find(p => p.ItemID == itemID);
            if (icon == null)
                return bmp;

            string filePath = $"icons/ItemBtn{icon.FileID}.png";
            var src = GetCachedImage(filePath);
            if (src == null)
                return bmp;

            Bitmap result = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(result))
            {
                Rectangle srcRect = new Rectangle(icon.Col * 32, icon.Row * 32, 32, 32);
                try { g.DrawImage(src, new Rectangle(0, 0, 32, 32), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 32, 32)); }
            }
            bmp.Dispose();
            return result;
        }

        public Bitmap IconSkill1(int fileID, int row, int col)
        {
            string filePath = $"icons/SkillBtn{fileID}.png";
            var src = GetCachedImage(filePath);
            if (src == null)
                return new Bitmap(32, 32);

            Bitmap bmp = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                Rectangle srcRect = new Rectangle(col * 32, row * 32, 32, 32);
                try { g.DrawImage(src, new Rectangle(0, 0, 32, 32), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 32, 32)); }
            }
            return bmp;
        }

        public Bitmap IconItem(int fileID, int row, int col)
        {
            string filePath = $"icons/ItemBtn{fileID}.png";
            var src = GetCachedImage(filePath);
            if (src == null)
                return new Bitmap(32, 32);

            Bitmap bmp = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                Rectangle srcRect = new Rectangle(col * 32, row * 32, 32, 32);
                try { g.DrawImage(src, new Rectangle(0, 0, 32, 32), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 32, 32)); }
            }
            return bmp;
        }

        public Bitmap IconCombo(int fileID, int row, int col)
        {
            string filePath = $"icons/ComboBtn{fileID}.png";
            var src = GetCachedImage(filePath);
            if (src == null)
                return new Bitmap(50, 50);

            Bitmap bmp = new Bitmap(50, 50);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                Rectangle srcRect = new Rectangle(col * 50, row * 50, 50, 50);
                try { g.DrawImage(src, new Rectangle(0, 0, 50, 50), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 50, 50)); }
            }
            return bmp;
        }

        public Bitmap SkillsFast(int skillID)
        {
            var fallback = GetCachedImage("icons/SkillBtn0.png");
            Bitmap bmp = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                if (fallback != null)
                    g.DrawImage(fallback, new Rectangle(0, 0, 32, 32));
                else
                    g.Clear(Color.Transparent);
            }

            if (skillID == -1)
                return bmp;

            SkillIcon skill = IconSkill.List.Find(p => p.SkillID == skillID);
            if (skill == null)
                return bmp;

            string path = $"icons/SkillBtn{skill.FileID}.png";
            var src = GetCachedImage(path);
            if (src == null)
                return bmp;

            Bitmap result = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(result))
            {
                Rectangle srcRect = new Rectangle(skill.Col * 32, skill.Row * 32, 32, 32);
                try { g.DrawImage(src, new Rectangle(0, 0, 32, 32), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 32, 32)); }
            }
            bmp.Dispose();
            return result;
        }

        public string SkillNameFast(int skillID)
        {
            if (skillID == -1)
                return "None";
            SkillIcon skill = IconSkill.List.Find(p => p.SkillID == skillID);
            return skill?.Name ?? "None";
        }

        public string QuestNameFast(int questIndex)
        {
            if (questIndex == -1)
                return "None";
            tQuest quest = QuestListPick.List.Find(p => p.ItemID == questIndex);
            return quest?.Name ?? "None";
        }

        public string OptionNameFast(int optionID)
        {
            if (optionID == -1)
                return "None";
            tOption option = OptionList.List.Find(p => p.ItemID == optionID);
            return option?.Name ?? "None";
        }

        public string FunctionMonsterName(int monsterID)
        {
            string query = $"SELECT a_name FROM t_npc WHERE a_index = '{monsterID}'";
            using var conn = new MySqlConnection(GetConnectionString());
            using var cmd = new MySqlCommand(query, conn);
            conn.Open();
            using MySqlDataReader reader = cmd.ExecuteReader();
            return reader.Read() ? reader.GetString(0) : "None";
        }

        public Bitmap IconAction(int fileID, int row, int col)
        {
            string path = $"icons/ActionBtn{fileID}.png";
            var src = GetCachedImage(path);
            if (src == null)
                return new Bitmap(32, 32);

            Bitmap bmp = new Bitmap(32, 32);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                Rectangle srcRect = new Rectangle(col * 32, row * 32, 32, 32);
                try { g.DrawImage(src, new Rectangle(0, 0, 32, 32), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 32, 32)); }
            }
            return bmp;
        }

        public Bitmap IconItemCollection(int fileID, int row, int col)
        {
            string path = $"icons/ItemCollectionBtn{fileID}.png";
            var src = GetCachedImage(path);
            if (src == null)
                return new Bitmap(60, 60);

            Bitmap bmp = new Bitmap(60, 60);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                Rectangle srcRect = new Rectangle(col * 60, row * 60, 60, 60);
                try { g.DrawImage(src, new Rectangle(0, 0, 60, 60), srcRect, GraphicsUnit.Pixel); }
                catch { g.DrawImage(src, new Rectangle(0, 0, 60, 60)); }
            }
            return bmp;
        }

        public string ItemNameFast(int itemID)
        {
            if (itemID == -1)
                return "None";

            ticon icon = IconList.List.Find(p => p.ItemID == itemID);
            return icon?.Name ?? "None";
        }

        public string MobNameFast(int mobIndex)
        {
            if (mobIndex == -1)
                return "None";

            tNpc npc = NpcList.List.Find(p => p.ItemID == mobIndex);
            return npc?.Name ?? "None";
        }

    }
}
