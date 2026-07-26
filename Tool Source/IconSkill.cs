// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.IconSkill
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  internal class IconSkill
  {
    public static System.Collections.Generic.List<SkillIcon> List = new System.Collections.Generic.List<SkillIcon>();
    public static string LoadFromDatabaseSQL = "SELECT * FROM t_skill ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = IconSkill.connection.Settings.SqlHost;
    public static string User = IconSkill.connection.Settings.SqlUser;
    public static string Password = IconSkill.connection.Settings.SqlPassword;
    public static string Database = IconSkill.connection.Settings.SqlDatabase;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    private static string language = IconSkill.connection.Settings.Language;
    public static string namee;
    public static string ClientDescription;
    public static string ToolTip;
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_name_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_name_ita"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name_usa"
    };

    public static string StringFromLanguage()
    {
      switch (IconSkill.language)
      {
        case "GER":
          IconSkill.namee = "a_name_ger";
          return IconSkill.namee;
        case "POL":
          IconSkill.namee = "a_name_pld";
          return IconSkill.namee;
        case "BRA":
          IconSkill.namee = "a_name_brz";
          return IconSkill.namee;
        case "RUS":
          IconSkill.namee = "a_name_rus";
          return IconSkill.namee;
        case "FRA":
          IconSkill.namee = "a_name_frc";
          return IconSkill.namee;
        case "ESP":
          IconSkill.namee = "a_name_spn";
          return IconSkill.namee;
        case "MEX":
          IconSkill.namee = "a_name_mex";
          return IconSkill.namee;
        case "THA":
          IconSkill.namee = "a_name_thai";
          return IconSkill.namee;
        case "ITA":
          IconSkill.namee = "a_name_ita";
          return IconSkill.namee;
        case "USA":
          IconSkill.namee = "a_name_usa";
          return IconSkill.namee;
        default:
          return (string) null;
      }
    }

    public static string ClientDescrFromLanguage()
    {
      switch (IconSkill.language)
      {
        case "GER":
          IconSkill.ClientDescription = "a_client_description_ger";
          return IconSkill.ClientDescription;
        case "POL":
          IconSkill.ClientDescription = "a_client_description_pld";
          return IconSkill.ClientDescription;
        case "BRA":
          IconSkill.ClientDescription = "a_client_description_brz";
          return IconSkill.ClientDescription;
        case "RUS":
          IconSkill.ClientDescription = "a_client_description_rus";
          return IconSkill.ClientDescription;
        case "FRA":
          IconSkill.ClientDescription = "a_client_description_frc";
          return IconSkill.ClientDescription;
        case "ESP":
          IconSkill.ClientDescription = "a_client_description_spn";
          return IconSkill.ClientDescription;
        case "MEX":
          IconSkill.ClientDescription = "a_client_description_mex";
          return IconSkill.ClientDescription;
        case "THA":
          IconSkill.ClientDescription = "a_client_description_thai";
          return IconSkill.ClientDescription;
        case "ITA":
          IconSkill.ClientDescription = "a_client_description_ita";
          return IconSkill.ClientDescription;
        case "USA":
          IconSkill.ClientDescription = "a_client_description_usa";
          return IconSkill.ClientDescription;
        default:
          return (string) null;
      }
    }

    public static string ToolTipFromLanguage()
    {
      switch (IconSkill.language)
      {
        case "GER":
          IconSkill.ToolTip = "a_client_tooltip_ger";
          return IconSkill.ToolTip;
        case "POL":
          IconSkill.ToolTip = "a_client_tooltip_pld";
          return IconSkill.ToolTip;
        case "BRA":
          IconSkill.ToolTip = "a_client_tooltip_brz";
          return IconSkill.ToolTip;
        case "RUS":
          IconSkill.ToolTip = "a_client_tooltip_rus";
          return IconSkill.ToolTip;
        case "FRA":
          IconSkill.ToolTip = "a_client_tooltip_frc";
          return IconSkill.ToolTip;
        case "ESP":
          IconSkill.ToolTip = "a_client_tooltip_spn";
          return IconSkill.ToolTip;
        case "MEX":
          IconSkill.ToolTip = "a_client_tooltip_mex";
          return IconSkill.ToolTip;
        case "THA":
          IconSkill.ToolTip = "a_client_tooltip_thai";
          return IconSkill.ToolTip;
        case "ITA":
          IconSkill.ToolTip = "a_client_tooltip_ita";
          return IconSkill.ToolTip;
        case "USA":
          IconSkill.ToolTip = "a_client_tooltip_usa";
          return IconSkill.ToolTip;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
            IconSkill.ConnectionString = string.Format(
          "Data Source={0};Database={1};User ID={2};Password={3};SslMode=None;",
          IconSkill.Host, IconSkill.Database, IconSkill.User, IconSkill.Password
      );
            return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			// Always create a new local connection
			using (var conn = new MySqlConnection(IconSkill.ConnectionString))
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
      IconSkill.namee = IconSkill.StringFromLanguage();
      IconSkill.ClientDescription = IconSkill.ClientDescrFromLanguage();
      IconSkill.ToolTip = IconSkill.ToolTipFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) IconSkill.GetFromQuery(IconSkill.LoadFromDatabaseSQL).Rows)
        IconSkill.List.Add(new SkillIcon()
        {
          SkillID = Convert.ToInt32(row["a_index"]),
          FileID = Convert.ToInt32(row["a_client_icon_texid"]),
          Row = Convert.ToInt32(row["a_client_icon_row"]),
          Col = Convert.ToInt32(row["a_client_icon_col"]),
          Name = Convert.ToString(row[IconSkill.namee ?? ""]),
          Desc = Convert.ToString(row[IconSkill.ClientDescription ?? ""]),
          Tooltip = Convert.ToString(row[IconSkill.ToolTip ?? ""])
        });
    }
  }
}
