#pragma once
#include "stdhdrs.h"
#include <mysql.h>

class CDBCmd
{
public:
    CDBCmd();
    virtual ~CDBCmd();

private:
    MYSQL* m_dbconn;
    MYSQL_RES* m_res;
    MYSQL_ROW    m_row;
    MYSQL_FIELD* m_fieldinfo;
    int          m_nfields;
    int          m_nrecords;

    MYSQL_STMT* m_stmt;           // Prepared statement
    MYSQL_BIND* m_bindResult;     // Result binding

    CLCString    m_sql;
    unsigned long m_sqlLen;

public:
    // Initialization
    void Init(MYSQL* conn);

    // Query execution
    bool Open();      // SELECT
    bool Update();    // INSERT/UPDATE/DELETE
    void Close();

    // Cursor
    bool MoveNext();
    bool MoveFirst();

    // Set query text (will prepare internally)
    void SetQuery(const char* sql);

    // Record fetching
    bool GetRec(const char* fieldname, int& n);
    bool GetRec(const char* fieldname, unsigned int& n);
    bool GetRec(const char* fieldname, short& n);
    bool GetRec(const char* fieldname, unsigned short& n);
    bool GetRec(const char* fieldname, char& ch);
    bool GetRec(const char* fieldname, unsigned char& ch);
    bool GetRec(const char* fieldname, CLCString& str, bool bTrim = true);
    bool GetRec(const char* fieldname, float& f);
    bool GetRec(const char* fieldname, LONGLONG& ll);

    bool GetRec(int fieldno, int& n);
    bool GetRec(int fieldno, unsigned int& n);
    bool GetRec(int fieldno, short& n);
    bool GetRec(int fieldno, unsigned short& n);
    bool GetRec(int fieldno, char& ch);
    bool GetRec(int fieldno, unsigned char& ch);
    bool GetRec(int fieldno, CLCString& str, bool bTrim = true);
    bool GetRec(int fieldno, float& f);
    bool GetRec(int fieldno, LONGLONG& ll);

    char* GetRec(const char* fieldname);
    char* GetRec(int fieldno);
    int FindField(const char* fieldname);

    // Transaction helpers (fixed)
    void BeginTrans() {
        if (m_dbconn) {
            mysql_autocommit(m_dbconn, 0); // disable autocommit
            mysql_real_query(m_dbconn, "BEGIN", 5);
        }
    }

    void Commit() {
        if (m_dbconn) {
            mysql_real_query(m_dbconn, "COMMIT", 6);
            mysql_autocommit(m_dbconn, 1); // re-enable autocommit
        }
    }

    void Rollback() {
        if (m_dbconn) {
            mysql_real_query(m_dbconn, "ROLLBACK", 8);
            mysql_autocommit(m_dbconn, 1); // re-enable autocommit
        }
    }

    // Error handling
    const char* ErrorString() { return m_dbconn ? mysql_error(m_dbconn) : "No connection"; }
    unsigned long insertid() { return m_dbconn ? mysql_insert_id(m_dbconn) : 0; }
};
