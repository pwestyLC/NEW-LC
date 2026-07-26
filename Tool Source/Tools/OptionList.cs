// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.OptionList
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class OptionList
  {
    public static System.Collections.Generic.List<tOption> List = new System.Collections.Generic.List<tOption>();
    public static string LoadFromDatabaseSQL = "SELECT a_type, a_name_ger, a_name_usa, a_name_frc, a_name_pld, a_name_brz, a_name_rus, a_name_mex, a_name_spn, a_name_thai, a_name_ita  FROM t_option ORDER BY a_type";
    public static Connection connection = new Connection();
    public static string Host = OptionList.connection.Settings.SqlHost;
    public static string User = OptionList.connection.Settings.SqlUser;
    public static string Password = OptionList.connection.Settings.SqlPassword;
    public static string Database = OptionList.connection.Settings.SqlDatabase;
    public static string language = OptionList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (OptionList.language)
      {
        case "GER":
          OptionList.namee = "a_name_ger";
          return OptionList.namee;
        case "POL":
          OptionList.namee = "a_name_pld";
          return OptionList.namee;
        case "BRA":
          OptionList.namee = "a_name_brz";
          return OptionList.namee;
        case "RUS":
          OptionList.namee = "a_name_rus";
          return OptionList.namee;
        case "FRA":
          OptionList.namee = "a_name_frc";
          return OptionList.namee;
        case "ESP":
          OptionList.namee = "a_name_spn";
          return OptionList.namee;
        case "MEX":
          OptionList.namee = "a_name_mex";
          return OptionList.namee;
        case "THA":
          OptionList.namee = "a_name_thai";
          return OptionList.namee;
        case "ITA":
          OptionList.namee = "a_name_ita";
          return OptionList.namee;
        case "USA":
          OptionList.namee = "a_name_usa";
          return OptionList.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (OptionList.language)
      {
        case "GER":
          OptionList.descrr = "a_descr_ger";
          return OptionList.descrr;
        case "POL":
          OptionList.descrr = "a_descr_pld";
          return OptionList.descrr;
        case "BRA":
          OptionList.descrr = "a_descr_brz";
          return OptionList.descrr;
        case "RUS":
          OptionList.descrr = "a_descr_rus";
          return OptionList.descrr;
        case "FRA":
          OptionList.descrr = "a_descr_frc";
          return OptionList.descrr;
        case "ESP":
          OptionList.descrr = "a_descr_spn";
          return OptionList.descrr;
        case "MEX":
          OptionList.descrr = "a_descr_mex";
          return OptionList.descrr;
        case "THA":
          OptionList.descrr = "a_descr_thai";
          return OptionList.descrr;
        case "ITA":
          OptionList.descrr = "a_descr_ita";
          return OptionList.descrr;
        case "USA":
          OptionList.descrr = "a_descr_usa";
          return OptionList.descrr;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      OptionList.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) OptionList.Host, (object) OptionList.Database, (object) OptionList.User, (object) OptionList.Password);
      return true;
    }

        public static DataTable GetFromQuery(string query)
        {
            var fromQuery = new DataTable();

            using (var conn = new MySqlConnection(OptionList.ConnectionString))
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
      OptionList.namee = OptionList.StringFromLanguage();
      OptionList.descrr = OptionList.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) OptionList.GetFromQuery(OptionList.LoadFromDatabaseSQL).Rows)
        OptionList.List.Add(new tOption()
        {
          ItemID = Convert.ToInt32(row["a_type"]),
          Name = Convert.ToString(row[OptionList.namee ?? ""])
        });
    }
  }
}
