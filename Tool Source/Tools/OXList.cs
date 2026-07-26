// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.OXList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class OXList
  {
    public static System.Collections.Generic.List<tOX> List = new System.Collections.Generic.List<tOX>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_question  FROM t_oxquiz ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = OXList.connection.Settings.SqlHost;
    public static string User = OXList.connection.Settings.SqlUser;
    public static string Password = OXList.connection.Settings.SqlPassword;
    public static string Database = OXList.connection.Settings.SqlDatabase;
    public static string language = OXList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    private string country;

    public string NationCode()
    {
      switch (OXList.language)
      {
        case "GER":
          this.country = "13";
          return this.country;
        case "POL":
          this.country = "16";
          return this.country;
        case "BRA":
          this.country = "10";
          return this.country;
        case "RUS":
          this.country = "17";
          return this.country;
        case "FRA":
          this.country = "15";
          return this.country;
        case "ESP":
          this.country = "14";
          return this.country;
        case "MEX":
          this.country = "20";
          return this.country;
        case "THA":
          this.country = "4";
          return this.country;
        case "ITA":
          this.country = "19";
          return this.country;
        case "USA":
          this.country = "9";
          return this.country;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      OXList.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) OXList.Host, (object) OXList.Database, (object) OXList.User, (object) OXList.Password);
      return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(OXList.ConnectionString))
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
      foreach (DataRow row in (InternalDataCollectionBase) OXList.GetFromQuery(OXList.LoadFromDatabaseSQL).Rows)
        OXList.List.Add(new tOX()
        {
          QIndex = Convert.ToInt32(row["a_index"]),
          Question = Convert.ToString(row["a_question"])
        });
    }
  }
}
