// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.NpcShopList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class NpcShopList
  {
    public static System.Collections.Generic.List<tNpcShop> List = new System.Collections.Generic.List<tNpcShop>();
    public static string LoadFromDatabaseSQL = "SELECT a_keeper_idx, a_name_ger, a_name_usa, a_name_brz, a_name_rus, a_name_mex, a_name_thai, a_name_ita FROM t_shop ORDER BY a_keeper_idx";
    public static Connection connection = new Connection();
    public static string Host = NpcShopList.connection.Settings.SqlHost;
    public static string User = NpcShopList.connection.Settings.SqlUser;
    public static string Password = NpcShopList.connection.Settings.SqlPassword;
    public static string Database = NpcShopList.connection.Settings.SqlDatabase;
    public static string language = NpcShopList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (NpcShopList.language)
      {
        case "GER":
          NpcShopList.namee = "a_name_ger";
          return NpcShopList.namee;
        case "BRA":
          NpcShopList.namee = "a_name_brz";
          return NpcShopList.namee;
        case "RUS":
          NpcShopList.namee = "a_name_rus";
          return NpcShopList.namee;
        case "MEX":
          NpcShopList.namee = "a_name_mex";
          return NpcShopList.namee;
        case "THA":
          NpcShopList.namee = "a_name_thai";
          return NpcShopList.namee;
        case "ITA":
          NpcShopList.namee = "a_name_ita";
          return NpcShopList.namee;
        case "USA":
          NpcShopList.namee = "a_name_usa";
          return NpcShopList.namee;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
            NpcShopList.ConnectionString = string.Format(
          "Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;",
          NpcShopList.Host, NpcShopList.Database, NpcShopList.User, NpcShopList.Password
      );

            return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(NpcShopList.ConnectionString))
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
      NpcShopList.namee = NpcShopList.StringFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) NpcShopList.GetFromQuery(NpcShopList.LoadFromDatabaseSQL).Rows)
        NpcShopList.List.Add(new tNpcShop()
        {
          ItemID = Convert.ToInt32(row["a_keeper_idx"]),
          Name = Convert.ToString(row[NpcShopList.namee ?? ""])
        });
    }
  }
}
