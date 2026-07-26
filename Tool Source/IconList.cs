// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.IconList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class IconList
  {
    public static System.Collections.Generic.List<ticon> List = new System.Collections.Generic.List<ticon>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_name_ger, a_name_usa, a_name_frc, a_name_pld, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita, a_texture_id, a_texture_row, a_texture_col, a_descr_usa, a_descr_ger, a_descr_ita, a_descr_thai, a_descr_spn, a_descr_frc, a_descr_pld, a_descr_brz, a_descr_mex, a_descr_rus, a_num_0  FROM t_item ORDER BY a_index";
    public static Connection connection = new Connection();
        public static string Host = IconList.connection.Settings.SqlHost;
        public static string User = IconList.connection.Settings.SqlUser;
        public static string Password = IconList.connection.Settings.SqlPassword;
        public static string Database = IconList.connection.Settings.SqlDatabase;
        public static string language = IconList.connection.Settings.Language;

        public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string DescrFromLanguage()
    {
      switch (IconList.language)
      {
        case "GER":
          IconList.descrr = "a_descr_ger";
          return IconList.descrr;
        case "POL":
          IconList.descrr = "a_descr_pld";
          return IconList.descrr;
        case "BRA":
          IconList.descrr = "a_descr_brz";
          return IconList.descrr;
        case "RUS":
          IconList.descrr = "a_descr_rus";
          return IconList.descrr;
        case "FRA":
          IconList.descrr = "a_descr_frc";
          return IconList.descrr;
        case "ESP":
          IconList.descrr = "a_descr_spn";
          return IconList.descrr;
        case "MEX":
          IconList.descrr = "a_descr_mex";
          return IconList.descrr;
        case "THA":
          IconList.descrr = "a_descr_thai";
          return IconList.descrr;
        case "ITA":
          IconList.descrr = "a_descr_ita";
          return IconList.descrr;
        case "USA":
          IconList.descrr = "a_descr_usa";
          return IconList.descrr;
        default:
          return (string) null;
      }
    }

    public static string StringFromLanguage()
    {
      switch (IconList.language)
      {
        case "GER":
          IconList.namee = "a_name_ger";
          return IconList.namee;
        case "POL":
          IconList.namee = "a_name_pld";
          return IconList.namee;
        case "BRA":
          IconList.namee = "a_name_brz";
          return IconList.namee;
        case "RUS":
          IconList.namee = "a_name_rus";
          return IconList.namee;
        case "FRA":
          IconList.namee = "a_name_frc";
          return IconList.namee;
        case "ESP":
          IconList.namee = "a_name_spn";
          return IconList.namee;
        case "MEX":
          IconList.namee = "a_name_mex";
          return IconList.namee;
        case "THA":
          IconList.namee = "a_name_thai";
          return IconList.namee;
        case "ITA":
          IconList.namee = "a_name_ita";
          return IconList.namee;
        case "USA":
          IconList.namee = "a_name_usa";
          return IconList.namee;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
            IconList.ConnectionString = string.Format(
          "Data Source={0};Database={1};User ID={2};Password={3};SslMode=None;",
          IconList.Host, IconList.Database, IconList.User, IconList.Password
      );

            return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(IconList.ConnectionString))
			{
				conn.Open();

				using (var cmd = new MySqlCommand(query, conn))
				using (var reader = cmd.ExecuteReader())
				{
					fromQuery.Load(reader);
				}

				conn.Close();
			}

			return fromQuery;
		}

		public static void Import()
    {
      IconList.namee = IconList.StringFromLanguage();
      IconList.descrr = IconList.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) IconList.GetFromQuery(IconList.LoadFromDatabaseSQL).Rows)
        IconList.List.Add(new ticon()
        {
          ItemID = Convert.ToInt32(row["a_index"]),
          FileID = Convert.ToInt32(row["a_texture_id"]),
          Row = Convert.ToInt32(row["a_texture_row"]),
          Col = Convert.ToInt32(row["a_texture_col"]),
          Name = Convert.ToString(row[IconList.namee ?? ""]),
          Desc = Convert.ToString(row[IconList.descrr ?? ""]),
          num0 = Convert.ToInt32(row["a_num_0"])
        });
    }
  }
}
