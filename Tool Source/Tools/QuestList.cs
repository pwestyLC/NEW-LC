// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.QuestListPick
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class QuestListPick
  {
    public static System.Collections.Generic.List<tQuest> List = new System.Collections.Generic.List<tQuest>();
    public static string LoadFromDatabaseSQL = "SELECT a_index, a_name_ger, a_name_usa, a_name_frc, a_name_pld, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita, a_desc_ger, a_desc_pld, a_desc_brz, a_desc_rus, a_desc_frc, a_desc_spn, a_desc_mex, a_desc_thai, a_desc_ita, a_desc_usa, a_desc2_ger, a_desc2_pld, a_desc2_brz, a_desc2_rus, a_desc2_frc, a_desc2_spn, a_desc2_mex, a_desc2_thai, a_desc2_ita, a_desc2_usa, a_desc3_ger, a_desc3_pld, a_desc3_brz, a_desc3_rus, a_desc3_frc, a_desc3_spn, a_desc3_mex, a_desc3_thai, a_desc3_ita, a_desc3_usa  FROM t_quest ORDER BY a_index";
    public static Connection connection = new Connection();
    public static string Host = QuestListPick.connection.Settings.SqlHost;
    public static string User = QuestListPick.connection.Settings.SqlUser;
    public static string Password = QuestListPick.connection.Settings.SqlPassword;
    public static string Database = QuestListPick.connection.Settings.SqlDatabase;
    public static string language = QuestListPick.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string desc;
    public static string desc2;
    public static string desc3;

    public static string StringFromLanguage()
    {
      switch (QuestListPick.language)
      {
        case "GER":
          QuestListPick.namee = "a_name_ger";
          return QuestListPick.namee;
        case "POL":
          QuestListPick.namee = "a_name_pld";
          return QuestListPick.namee;
        case "BRA":
          QuestListPick.namee = "a_name_brz";
          return QuestListPick.namee;
        case "RUS":
          QuestListPick.namee = "a_name_rus";
          return QuestListPick.namee;
        case "FRA":
          QuestListPick.namee = "a_name_frc";
          return QuestListPick.namee;
        case "ESP":
          QuestListPick.namee = "a_name_spn";
          return QuestListPick.namee;
        case "MEX":
          QuestListPick.namee = "a_name_mex";
          return QuestListPick.namee;
        case "THA":
          QuestListPick.namee = "a_name_thai";
          return QuestListPick.namee;
        case "ITA":
          QuestListPick.namee = "a_name_ita";
          return QuestListPick.namee;
        case "USA":
          QuestListPick.namee = "a_name_usa";
          return QuestListPick.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (QuestListPick.language)
      {
        case "GER":
          QuestListPick.desc = "a_desc_ger";
          return QuestListPick.desc;
        case "POL":
          QuestListPick.desc = "a_desc_pld";
          return QuestListPick.desc;
        case "BRA":
          QuestListPick.desc = "a_desc_brz";
          return QuestListPick.desc;
        case "RUS":
          QuestListPick.desc = "a_desc_rus";
          return QuestListPick.desc;
        case "FRA":
          QuestListPick.desc = "a_desc_frc";
          return QuestListPick.desc;
        case "ESP":
          QuestListPick.desc = "a_desc_spn";
          return QuestListPick.desc;
        case "MEX":
          QuestListPick.desc = "a_desc_mex";
          return QuestListPick.desc;
        case "THA":
          QuestListPick.desc = "a_desc_thai";
          return QuestListPick.desc;
        case "ITA":
          QuestListPick.desc = "a_desc_ita";
          return QuestListPick.desc;
        case "USA":
          QuestListPick.desc = "a_desc_usa";
          return QuestListPick.desc;
        default:
          return (string) null;
      }
    }

    public static string Descr2FromLanguage()
    {
      switch (QuestListPick.language)
      {
        case "GER":
          QuestListPick.desc2 = "a_desc2_ger";
          return QuestListPick.desc2;
        case "POL":
          QuestListPick.desc2 = "a_desc2_pld";
          return QuestListPick.desc2;
        case "BRA":
          QuestListPick.desc2 = "a_desc2_brz";
          return QuestListPick.desc2;
        case "RUS":
          QuestListPick.desc2 = "a_desc2_rus";
          return QuestListPick.desc2;
        case "FRA":
          QuestListPick.desc2 = "a_desc2_frc";
          return QuestListPick.desc2;
        case "ESP":
          QuestListPick.desc2 = "a_desc2_spn";
          return QuestListPick.desc2;
        case "MEX":
          QuestListPick.desc2 = "a_desc2_mex";
          return QuestListPick.desc2;
        case "THA":
          QuestListPick.desc2 = "a_desc2_thai";
          return QuestListPick.desc2;
        case "ITA":
          QuestListPick.desc2 = "a_desc2_ita";
          return QuestListPick.desc2;
        case "USA":
          QuestListPick.desc2 = "a_desc2_usa";
          return QuestListPick.desc2;
        default:
          return (string) null;
      }
    }

    public static string Descr3FromLanguage()
    {
      switch (QuestListPick.language)
      {
        case "GER":
          QuestListPick.desc3 = "a_desc3_ger";
          return QuestListPick.desc3;
        case "POL":
          QuestListPick.desc3 = "a_desc3_pld";
          return QuestListPick.desc3;
        case "BRA":
          QuestListPick.desc3 = "a_desc3_brz";
          return QuestListPick.desc3;
        case "RUS":
          QuestListPick.desc3 = "a_desc3_rus";
          return QuestListPick.desc3;
        case "FRA":
          QuestListPick.desc3 = "a_desc3_frc";
          return QuestListPick.desc3;
        case "ESP":
          QuestListPick.desc3 = "a_desc3_spn";
          return QuestListPick.desc3;
        case "MEX":
          QuestListPick.desc3 = "a_desc3_mex";
          return QuestListPick.desc3;
        case "THA":
          QuestListPick.desc3 = "a_desc3_thai";
          return QuestListPick.desc3;
        case "ITA":
          QuestListPick.desc3 = "a_desc3_ita";
          return QuestListPick.desc3;
        case "USA":
          QuestListPick.desc3 = "a_desc3_usa";
          return QuestListPick.desc3;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
            QuestListPick.ConnectionString = string.Format(
          "Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;",
          QuestListPick.Host, QuestListPick.Database, QuestListPick.User, QuestListPick.Password
      );

            return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(QuestListPick.ConnectionString))
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
      QuestListPick.namee = QuestListPick.StringFromLanguage();
      QuestListPick.desc = QuestListPick.DescrFromLanguage();
      QuestListPick.desc2 = QuestListPick.Descr2FromLanguage();
      QuestListPick.desc3 = QuestListPick.Descr3FromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) QuestListPick.GetFromQuery(QuestListPick.LoadFromDatabaseSQL).Rows)
        QuestListPick.List.Add(new tQuest()
        {
          ItemID = Convert.ToInt32(row["a_index"]),
          Name = Convert.ToString(row[QuestListPick.namee ?? ""]),
          Desc = Convert.ToString(row[QuestListPick.desc ?? ""]),
          Desc2 = Convert.ToString(row[QuestListPick.desc2 ?? ""]),
          Desc3 = Convert.ToString(row[QuestListPick.desc3 ?? ""])
        });
    }
  }
}
