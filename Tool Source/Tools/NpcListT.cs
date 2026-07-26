// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.NpcListT
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class NpcListT
  {
    public static System.Collections.Generic.List<tNpc> List = new System.Collections.Generic.List<tNpc>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_name_ger, a_name_usa, a_name_frc, a_name_pld, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita, a_file_smc, a_descr_ger, a_descr_pld, a_descr_brz, a_descr_rus, a_descr_frc, a_descr_spn, a_descr_mex, a_descr_thai, a_descr_ita, a_descr_usa, a_zone_flag, a_extra_flag  FROM t_npc WHERE a_flag = '33554736' AND a_flag = '33554480'  ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = NpcListT.connection.Settings.SqlHost;
    public static string User = NpcListT.connection.Settings.SqlUser;
    public static string Password = NpcListT.connection.Settings.SqlPassword;
    public static string Database = NpcListT.connection.Settings.SqlDatabase;
    public static string language = NpcListT.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (NpcListT.language)
      {
        case "GER":
          NpcListT.namee = "a_name_ger";
          return NpcListT.namee;
        case "POL":
          NpcListT.namee = "a_name_pld";
          return NpcListT.namee;
        case "BRA":
          NpcListT.namee = "a_name_brz";
          return NpcListT.namee;
        case "RUS":
          NpcListT.namee = "a_name_rus";
          return NpcListT.namee;
        case "FRA":
          NpcListT.namee = "a_name_frc";
          return NpcListT.namee;
        case "ESP":
          NpcListT.namee = "a_name_spn";
          return NpcListT.namee;
        case "MEX":
          NpcListT.namee = "a_name_mex";
          return NpcListT.namee;
        case "THA":
          NpcListT.namee = "a_name_thai";
          return NpcListT.namee;
        case "ITA":
          NpcListT.namee = "a_name_ita";
          return NpcListT.namee;
        case "USA":
          NpcListT.namee = "a_name_usa";
          return NpcListT.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (NpcListT.language)
      {
        case "GER":
          NpcListT.descrr = "a_descr_ger";
          return NpcListT.descrr;
        case "POL":
          NpcListT.descrr = "a_descr_pld";
          return NpcListT.descrr;
        case "BRA":
          NpcListT.descrr = "a_descr_brz";
          return NpcListT.descrr;
        case "RUS":
          NpcListT.descrr = "a_descr_rus";
          return NpcListT.descrr;
        case "FRA":
          NpcListT.descrr = "a_descr_frc";
          return NpcListT.descrr;
        case "ESP":
          NpcListT.descrr = "a_descr_spn";
          return NpcListT.descrr;
        case "MEX":
          NpcListT.descrr = "a_descr_mex";
          return NpcListT.descrr;
        case "THA":
          NpcListT.descrr = "a_descr_thai";
          return NpcListT.descrr;
        case "ITA":
          NpcListT.descrr = "a_descr_ita";
          return NpcListT.descrr;
        case "USA":
          NpcListT.descrr = "a_descr_usa";
          return NpcListT.descrr;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      NpcListT.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) NpcListT.Host, (object) NpcListT.Database, (object) NpcListT.User, (object) NpcListT.Password);
      return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(NpcListT.ConnectionString))
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
      NpcListT.namee = NpcListT.StringFromLanguage();
      NpcListT.descrr = NpcListT.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) NpcListT.GetFromQuery(NpcListT.LoadFromDatabaseSQL).Rows)
        NpcListT.List.Add(new tNpc()
        {
          ItemID = Convert.ToInt32(row["a_index"]),
          Name = Convert.ToString(row[NpcListT.namee ?? ""]),
          SMCPath = Convert.ToString(row["a_file_smc"]),
          Desc = Convert.ToString(row[NpcListT.descrr ?? ""])
        });
    }
  }
}
