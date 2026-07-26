// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.AffinityList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class AffinityList
  {
    public static System.Collections.Generic.List<tAffinity2> List = new System.Collections.Generic.List<tAffinity2>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_name_ger, a_name_usa, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita FROM t_affinity ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = AffinityList.connection.Settings.SqlHost;
    public static string User = AffinityList.connection.Settings.SqlUser;
    public static string Password = AffinityList.connection.Settings.SqlPassword;
    public static string Database = AffinityList.connection.Settings.SqlDatabase;
    public static string language = AffinityList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (AffinityList.language)
      {
        case "GER":
          AffinityList.namee = "a_name_ger";
          return AffinityList.namee;
        case "BRA":
          AffinityList.namee = "a_name_brz";
          return AffinityList.namee;
        case "RUS":
          AffinityList.namee = "a_name_rus";
          return AffinityList.namee;
        case "ESP":
          AffinityList.namee = "a_name_spn";
          return AffinityList.namee;
        case "MEX":
          AffinityList.namee = "a_name_mex";
          return AffinityList.namee;
        case "THA":
          AffinityList.namee = "a_name_thai";
          return AffinityList.namee;
        case "ITA":
          AffinityList.namee = "a_name_ita";
          return AffinityList.namee;
        case "USA":
          AffinityList.namee = "a_name_usa";
          return AffinityList.namee;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      AffinityList.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=None;", (object) AffinityList.Host, (object) AffinityList.Database, (object) AffinityList.User, (object) AffinityList.Password);
      return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			// Always create a fresh connection; don't assign to a static one
			using (var conn = new MySqlConnection(AffinityList.ConnectionString))
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
      AffinityList.namee = AffinityList.StringFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) AffinityList.GetFromQuery(AffinityList.LoadFromDatabaseSQL).Rows)
        AffinityList.List.Add(new tAffinity2()
        {
          ItemID = Convert.ToInt32(row["a_index"]),
          Name = Convert.ToString(row[AffinityList.namee ?? ""])
        });
    }
  }
}
