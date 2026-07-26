// Decompiled with JetBrains decompiler
// Type: UTIL.mysql
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools;
using MySqlConnector;
using System;
using System.Data;

#nullable disable
namespace UTIL
{
  internal class mysql
  {
    public static MySqlConnection connection = new MySqlConnection();
    private string Host = AffinityEditor.connection.Settings.SqlHost;
    private readonly string User = AffinityEditor.connection.Settings.SqlUser;
    private string Password = AffinityEditor.connection.Settings.SqlPassword;
    private string Database = AffinityEditor.connection.Settings.SqlDatabase;
    private DataTable _dt;

    public DataTable dt => this._dt;

    public bool Connect()
    {
      if (mysql.connection != null)
        mysql.connection.Close();
      string connectionString = string.Format("server={0};user id={1}; password={2}; database={3}; ", (object) this.Host, (object) this.User, (object) this.Password, (object) this.Database) + "pooling=false;Charset=latin1;Respect Binary Flags=false;";
      try
      {
        mysql.connection = new MySqlConnection(connectionString);
        return true;
      }
      catch (MySqlException ex)
      {
        Console.WriteLine("Error connecting to the server: " + ex.Message);
      }
      return false;
    }

    public DataTable Query(string strQuery)
    {
      mysql.connection.Open();
      MySqlCommand mySqlCommand = new MySqlCommand(strQuery, mysql.connection);
      MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter(strQuery, mysql.connection);
      this._dt = new DataTable();
      mySqlDataAdapter.Fill(this._dt);
      mysql.connection.Close();
      return this._dt;
    }

    public void Close()
    {
      if (mysql.connection == null)
        return;
      mysql.connection.Close();
    }
  }
}
