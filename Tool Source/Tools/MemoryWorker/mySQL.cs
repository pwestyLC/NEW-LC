using MySqlConnector;
using StringExporter;
using System.Data;

namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
    public class mySQL
    {
        public static MySqlConnection mysqlCon;
        public static string ConnectionString;
        public static Connection connection = new Connection();
        private DataTable _dt;

        private string Host = FormExport.connection.Settings.SqlHost;
        private string User = FormExport.connection.Settings.SqlUser;
        private string Password = FormExport.connection.Settings.SqlPassword;
        private string Database = FormExport.connection.Settings.SqlDatabase;

        public DataTable dt => _dt;

        public static bool SetConnection()
        {
            config.ReadConfig();
            ConnectionString = config.ConfigString;
            return true;
        }

        // General query returning a DataTable
        public static DataTable GetFromQuery(string query)
        {
            var table = new DataTable();
            using (var conn = new MySqlConnection(ConnectionString))
            {
                conn.Open();
                using (var cmd = new MySqlCommand(query, conn))
                using (var reader = cmd.ExecuteReader())
                {
                    table.Load(reader);
                }
            }
            return table;
        }

        // Query from instance connection parameters
        public DataTable Query(string strQuery)
        {
            var table = new DataTable();
            using (var conn = new MySqlConnection(
                $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
            {
                conn.Open();
                using (var adapter = new MySqlDataAdapter(strQuery, conn))
                {
                    adapter.Fill(table);
                }
            }
            _dt = table;
            return table;
        }

        // Alternate icon query (duplicate of GetFromQuery)
        public static DataTable GetFromQueryIcon(string query)
        {
            var table = new DataTable();
            using (var conn = new MySqlConnection(ConnectionString))
            {
                conn.Open();
                using (var cmd = new MySqlCommand(query, conn))
                using (var reader = cmd.ExecuteReader())
                {
                    table.Load(reader);
                }
            }
            return table;
        }

        // Single value query
        public static object SingleQuery(string query)
        {
            using (var conn = new MySqlConnection(ConnectionString))
            {
                conn.Open();
                using (var cmd = new MySqlCommand(query, conn))
                {
                    return cmd.ExecuteScalar();
                }
            }
        }

        // Execute update/insert/delete
        public static void UpdateQuery(string query)
        {
            using (var conn = new MySqlConnection(ConnectionString))
            {
                conn.Open();
                using (var cmd = new MySqlCommand(query, conn))
                {
                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}
