// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.NpcList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class NpcList
  {
    public static System.Collections.Generic.List<tNpc> List = new System.Collections.Generic.List<tNpc>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_name_ger, a_name_usa, a_name_frc, a_name_pld, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita, a_file_smc, a_descr_ger, a_descr_pld, a_descr_brz, a_descr_rus, a_descr_frc, a_descr_spn, a_descr_mex, a_descr_thai, a_descr_ita, a_descr_usa, a_zone_flag, a_extra_flag  FROM t_npc ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = NpcList.connection.Settings.SqlHost;
    public static string User = NpcList.connection.Settings.SqlUser;
    public static string Password = NpcList.connection.Settings.SqlPassword;
    public static string Database = NpcList.connection.Settings.SqlDatabase;
    public static string language = NpcList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (NpcList.language)
      {
        case "GER":
          NpcList.namee = "a_name_ger";
          return NpcList.namee;
        case "POL":
          NpcList.namee = "a_name_pld";
          return NpcList.namee;
        case "BRA":
          NpcList.namee = "a_name_brz";
          return NpcList.namee;
        case "RUS":
          NpcList.namee = "a_name_rus";
          return NpcList.namee;
        case "FRA":
          NpcList.namee = "a_name_frc";
          return NpcList.namee;
        case "ESP":
          NpcList.namee = "a_name_spn";
          return NpcList.namee;
        case "MEX":
          NpcList.namee = "a_name_mex";
          return NpcList.namee;
        case "THA":
          NpcList.namee = "a_name_thai";
          return NpcList.namee;
        case "ITA":
          NpcList.namee = "a_name_ita";
          return NpcList.namee;
        case "USA":
          NpcList.namee = "a_name_usa";
          return NpcList.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (NpcList.language)
      {
        case "GER":
          NpcList.descrr = "a_descr_ger";
          return NpcList.descrr;
        case "POL":
          NpcList.descrr = "a_descr_pld";
          return NpcList.descrr;
        case "BRA":
          NpcList.descrr = "a_descr_brz";
          return NpcList.descrr;
        case "RUS":
          NpcList.descrr = "a_descr_rus";
          return NpcList.descrr;
        case "FRA":
          NpcList.descrr = "a_descr_frc";
          return NpcList.descrr;
        case "ESP":
          NpcList.descrr = "a_descr_spn";
          return NpcList.descrr;
        case "MEX":
          NpcList.descrr = "a_descr_mex";
          return NpcList.descrr;
        case "THA":
          NpcList.descrr = "a_descr_thai";
          return NpcList.descrr;
        case "ITA":
          NpcList.descrr = "a_descr_ita";
          return NpcList.descrr;
        case "USA":
          NpcList.descrr = "a_descr_usa";
          return NpcList.descrr;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
            NpcList.ConnectionString = string.Format(
          "Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;",
          NpcList.Host, NpcList.Database, NpcList.User, NpcList.Password
      );

            return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(NpcList.ConnectionString))
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
      NpcList.namee = NpcList.StringFromLanguage();
      NpcList.descrr = NpcList.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) NpcList.GetFromQuery(NpcList.LoadFromDatabaseSQL).Rows)
        NpcList.List.Add(new tNpc()
        {
          ItemID = Convert.ToInt32(row["a_index"]),
          Name = Convert.ToString(row[NpcList.namee ?? ""]),
          SMCPath = Convert.ToString(row["a_file_smc"]),
          Desc = Convert.ToString(row[NpcList.descrr ?? ""])
        });
    }
  }
}
