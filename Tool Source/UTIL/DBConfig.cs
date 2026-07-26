// Decompiled with JetBrains decompiler
// Type: DBConfig
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA;
using System;
using System.IO;
using UTIL;

#nullable disable
public class DBConfig
{
  public static Connection connection = new Connection();
  private string Host = DBConfig.connection.Settings.SqlHost;
  private string User = DBConfig.connection.Settings.SqlUser;
  private string Password = DBConfig.connection.Settings.SqlPassword;
  private string Database = DBConfig.connection.Settings.SqlDatabase;
  private DatabaseHandle databaseHandle = new DatabaseHandle();
  public string[] _config_DB = new string[4]
  {
    DBConfig.connection.Settings.SqlHost,
    DBConfig.connection.Settings.SqlUser,
    DBConfig.connection.Settings.SqlPassword,
    DBConfig.connection.Settings.SqlDatabase

  };
  private string[] _strPreFix;
  private string[] _strLocal;
  private string[] _strVersion;
  private string[] _strLang;
  private int _nLocalMax;
  private int _nPrefixMax;
  private int _nVerMax;
  private int _nLangMax;

  public DBConfig()
  {
    this.ConfigLoad(Directory.GetParent(Directory.GetCurrentDirectory()).ToString() + "\\DB_Config.ini");
  }

  public string GetTable(int nLocal, int nVer)
  {
    return (nLocal >= 0 || nLocal < this._nPrefixMax) && (nVer >= 0 || nVer < this._nVerMax) ? this._config_DB[3] + this._strPreFix[nLocal] + this._strVersion[nVer] : "";
  }

  public string GetStrVer(int nVer)
  {
    return nVer >= 0 || nVer < this._nVerMax ? this._strVersion[nVer] : "";
  }

  public string GetStrLang(int nIdx)
  {
    return nIdx >= 0 || nIdx < this._nVerMax ? this._strLang[nIdx] : "";
  }

  public string GetStrLocal(int nIdx)
  {
    return nIdx >= 0 || nIdx < this._nLocalMax ? this._strLocal[nIdx] : "";
  }

  public int GetLocalMax() => this._nLocalMax;

  public int GetVerMax() => this._nVerMax;

  public int GetLangMax() => this._nLangMax;

  public bool ConfigLoad(string fileName)
  {
    INI ini = new INI(fileName);
    int[] numArray = new int[4]
    {
      this._nLocalMax,
      this._nPrefixMax,
      this._nVerMax,
      this._nLangMax
    };
    for (int index1 = 0; index1 < 4; ++index1)
    {
      int index2 = index1;
      DBConfig.eSECTION eSection = (DBConfig.eSECTION) index1;
      numArray[index2] = Convert.ToInt32(ini.GetIniValue(eSection.ToString(), "Count"));
    }
    this._nLocalMax = numArray[0];
    this._nPrefixMax = numArray[1];
    this._nVerMax = numArray[2];
    this._nLangMax = numArray[3];
    if (this._nLocalMax > 0)
      this._strLocal = new string[numArray[0]];
    for (int index = 0; index < this._nLocalMax; ++index)
    {
      string Key = "{eKEY.LOCAL.ToString()}{i}";
      this._strLocal[index] = ini.GetIniValue(DBConfig.eSECTION.LOCAL.ToString(), Key);
    }
    if (this._nPrefixMax > 0)
      this._strPreFix = new string[numArray[1]];
    for (int index = 0; index < this._nPrefixMax; ++index)
    {
      string Key = "{eKEY.PREFIX.ToString()}{i}";
      this._strPreFix[index] = ini.GetIniValue(DBConfig.eSECTION.DB_PREFIX.ToString(), Key);
    }
    if (this._nVerMax > 0)
      this._strVersion = new string[numArray[2]];
    for (int index = 0; index < this._nVerMax; ++index)
    {
      string Key = "{eKEY.VER.ToString()}{i}";
      this._strVersion[index] = ini.GetIniValue(DBConfig.eSECTION.VERSION.ToString(), Key);
    }
    if (this._nLangMax > 0)
      this._strLang = new string[numArray[3]];
    for (int index = 0; index < this._nLangMax; ++index)
    {
      string Key = "{eKEY.LANG.ToString()}{i}";
      this._strLang[index] = ini.GetIniValue(DBConfig.eSECTION.LANGUAGE.ToString(), Key);
    }
    return true;
  }

  public enum eCONFIG_DB
  {
    eIP,
    eACCOUNT,
    ePASSWD,
    eTABLE,
    eCONFIG_MAX,
  }

  public enum eSECTION
  {
    LOCAL,
    DB_PREFIX,
    VERSION,
    LANGUAGE,
    MAX,
  }

  public enum eKEY
  {
    LOCAL,
    PREFIX,
    VER,
    LANG,
    MAX,
  }
}
