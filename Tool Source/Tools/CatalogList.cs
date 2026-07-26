// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.CatalogList
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
  public class CatalogList
  {
    public static System.Collections.Generic.List<tCatalog> List = new System.Collections.Generic.List<tCatalog>();
    public static string LoadFromDatabaseSQL = "SELECT a_ctid, a_ctname_ger, a_ctname_usa, a_ctname_pld, a_ctname_brz, a_ctname_rus, a_ctname_spn, a_ctname_tld, a_ctdesc_ger, a_ctdesc_pld, a_ctdesc_brz, a_ctdesc_rus, a_ctdesc_spn, a_ctdesc_tld, a_ctdesc_usa, a_ctname_tld_eng,a_ctdesc_tld_eng  FROM t_catalog ORDER BY a_ctid";
    public static Connection connection = new Connection();
    public static string Host = CatalogList.connection.Settings.SqlHost;
    public static string User = CatalogList.connection.Settings.SqlUser;
    public static string Password = CatalogList.connection.Settings.SqlPassword;
    public static string Database = CatalogList.connection.Settings.SqlDatabase;
    public static string language = CatalogList.connection.Settings.Language;
    public static MySqlConnection mysqlCon;
    public static string ConnectionString;
    public static string namee;
    public static string descrr;

    public static string StringFromLanguage()
    {
      switch (CatalogList.language)
      {
        case "GER":
          CatalogList.namee = "a_ctname_ger";
          return CatalogList.namee;
        case "POL":
          CatalogList.namee = "a_ctname_pld";
          return CatalogList.namee;
        case "BRA":
          CatalogList.namee = "a_ctname_brz";
          return CatalogList.namee;
        case "RUS":
          CatalogList.namee = "a_ctname_rus";
          return CatalogList.namee;
        case "FRA":
          CatalogList.namee = "a_ctname_frc";
          return CatalogList.namee;
        case "ESP":
          CatalogList.namee = "a_ctname_spn";
          return CatalogList.namee;
        case "THA":
          CatalogList.namee = "a_ctname_tld_eng";
          return CatalogList.namee;
        case "USA":
          CatalogList.namee = "a_ctname_usa";
          return CatalogList.namee;
        default:
          return (string) null;
      }
    }

    public static string DescrFromLanguage()
    {
      switch (CatalogList.language)
      {
        case "GER":
          CatalogList.descrr = "a_ctdesc_ger";
          return CatalogList.descrr;
        case "POL":
          CatalogList.descrr = "a_ctdesc_pld";
          return CatalogList.descrr;
        case "BRA":
          CatalogList.descrr = "a_ctdesc_brz";
          return CatalogList.descrr;
        case "RUS":
          CatalogList.descrr = "a_ctdesc_rus";
          return CatalogList.descrr;
        case "FRA":
          CatalogList.descrr = "a_ctdesc_frc";
          return CatalogList.descrr;
        case "ESP":
          CatalogList.descrr = "a_ctdesc_spn";
          return CatalogList.descrr;
        case "THA":
          CatalogList.descrr = "a_ctdesc_tld_eng";
          return CatalogList.descrr;
        case "USA":
          CatalogList.descrr = "a_ctdesc_usa";
          return CatalogList.descrr;
        default:
          return (string) null;
      }
    }

    public static bool SetConnection()
    {
      CatalogList.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) CatalogList.Host, (object) CatalogList.Database, (object) CatalogList.User, (object) CatalogList.Password);
      return true;
    }

		public static DataTable GetFromQuery(string query)
		{
			var fromQuery = new DataTable();

			using (var conn = new MySqlConnection(CatalogList.ConnectionString))
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
      CatalogList.namee = CatalogList.StringFromLanguage();
      CatalogList.descrr = CatalogList.DescrFromLanguage();
      foreach (DataRow row in (InternalDataCollectionBase) CatalogList.GetFromQuery(CatalogList.LoadFromDatabaseSQL).Rows)
        CatalogList.List.Add(new tCatalog()
        {
          ItemID = Convert.ToInt32(row["a_ctid"]),
          Name = Encoding.GetEncoding("TIS-620").GetString(Encoding.GetEncoding("iso-8859-1").GetBytes(Convert.ToString(row[(CatalogList.namee ?? "") ?? ""]))),
          Desc = Encoding.GetEncoding("TIS-620").GetString(Encoding.GetEncoding("iso-8859-1").GetBytes(Convert.ToString(row[(CatalogList.descrr ?? "") ?? ""])))
        });
    }
  }
}
