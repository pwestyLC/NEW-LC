// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.OnlineMallList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;
using System.Text;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class OnlineMallList
  {
    public static System.Collections.Generic.List<tOnlineCatalog> List = new System.Collections.Generic.List<tOnlineCatalog>();
    public static string LoadFromDatabaseSQL = "SELECT id, title, description  FROM lastchaos_bundles_time ORDER BY id";
    public static Connection connection = new Connection();
    public static string Host = OnlineMallList.connection.Settings.SqlHost;
    public static string User = OnlineMallList.connection.Settings.SqlUser;
    public static string Password = OnlineMallList.connection.Settings.SqlPassword;
    public static string Database = OnlineMallList.connection.Settings.SqlDatabase;
    public static string DB_Auth = OnlineMallList.connection.Settings.SqlDbAuth;
    public static string language = OnlineMallList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (OnlineMallList.language)
      {
        case "GER":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "POL":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "BRA":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "RUS":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "FRA":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "ESP":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "THA":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        case "USA":
          OnlineMallList.namee = "title";
          return OnlineMallList.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (OnlineMallList.language)
      {
        case "GER":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "POL":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "BRA":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "RUS":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "FRA":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "ESP":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "THA":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        case "USA":
          OnlineMallList.descrr = "description";
          return OnlineMallList.descrr;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      OnlineMallList.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) OnlineMallList.Host, (object) OnlineMallList.DB_Auth, (object) OnlineMallList.User, (object) OnlineMallList.Password);
      return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(OnlineMallList.ConnectionString))
			{
				conn.Open();

				using (var cmd = new MySqlCommand(query, conn))
				using (var reader = cmd.ExecuteReader())
				{
					fromQuery.Load(reader);
				}
			}

			return fromQuery;
		}


		public static void Import()
    {
      OnlineMallList.namee = OnlineMallList.StringFromLanguage();
      OnlineMallList.descrr = OnlineMallList.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) OnlineMallList.GetFromQuery(OnlineMallList.LoadFromDatabaseSQL).Rows)
        OnlineMallList.List.Add(new tOnlineCatalog()
        {
          ItemID = Convert.ToInt32(row["id"]),
          Name = Encoding.GetEncoding("TIS-620").GetString(Encoding.GetEncoding("iso-8859-1").GetBytes(Convert.ToString(row[(OnlineMallList.namee ?? "") ?? ""]))),
          Desc = Encoding.GetEncoding("TIS-620").GetString(Encoding.GetEncoding("iso-8859-1").GetBytes(Convert.ToString(row[(OnlineMallList.descrr ?? "") ?? ""])))
        });
    }
  }
}
