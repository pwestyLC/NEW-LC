#ifndef __DBCMD_H__
#define __DBCMD_H__

#include <string>
#include <boost/unordered_map.hpp>
#include "Conf.h"
#include "mysql.h"
#include "LCString.h"

class CDBConn
{
public:
    CDBConn() { mysql_init(&dbconn); }
    ~CDBConn() { mysql_close(&dbconn); }

    bool connect(
        const char* host,
        const char* user,
        const char* passwd,
        const char* db = nullptr,
        unsigned int port = 0,
        const char* unix_socket = nullptr,
        unsigned long clientflag = 0
    )
    {
        return mysql_real_connect(&dbconn, host, user, passwd, db, port, unix_socket, clientflag) != nullptr;
    }

    void close() { mysql_close(&dbconn); }
    operator MYSQL* () { return &dbconn; }

private:
    MYSQL dbconn;
};

class CDBCmd
{
public:
    typedef boost::unordered_map<std::string, int> map_t;

    CDBCmd();
    CDBCmd(MYSQL* mysql);
    ~CDBCmd();
public:
    int GetRecordCount() const { return m_nrecords; }
    MYSQL* GetDbConn() const { return m_dbconn; }
    MYSQL_ROW& GetRecordRow() { return m_row; }
    map_t map_;
    MYSQL* m_dbconn;
    int m_nrecords;
    MYSQL_RES* m_res;
    MYSQL_ROW m_row;
    MYSQL_FIELD* m_fieldinfo;
    int m_nfields;
    std::string m_sql;

public:
    void Init(MYSQL* conn) { m_dbconn = conn; }
    bool Open();
    void Close();
    bool MoveNext();
    bool MoveFirst();
    bool Seek(int nOffset);
    void SetQuery(const char* sql);
    void SetQuery(const std::string& sql);
    bool Update();

    // GetRec by field name
    bool GetRec(const char* fieldname, int& n);
    bool GetRec(const char* fieldname, unsigned int& n);
    bool GetRec(const char* fieldname, short& n);
    bool GetRec(const char* fieldname, unsigned short& n);
    bool GetRec(const char* fieldname, char& ch);
    bool GetRec(const char* fieldname, unsigned char& ch);
    bool GetRec(const char* fieldname, CLCString& str, bool bTrim = true);
    bool GetRec(const char* fieldname, float& f);
    bool GetRec(const char* fieldname, LONGLONG& ll);
    bool GetRec(const char* fieldname, ULONGLONG& ll);
    bool GetRec(const char* fieldname, std::string& str);

    // GetRec by field index
    bool GetRec(int fieldno, int& n);
    bool GetRec(int fieldno, unsigned int& n);
    bool GetRec(int fieldno, short& n);
    bool GetRec(int fieldno, unsigned short& n);
    bool GetRec(int fieldno, char& ch);
    bool GetRec(int fieldno, unsigned char& ch);
    bool GetRec(int fieldno, CLCString& str, bool bTrim = true);
    bool GetRec(int fieldno, float& f);
    bool GetRec(int fieldno, LONGLONG& ll);
    bool GetRec(int fieldno, ULONGLONG& ll);
    bool GetRec(int fieldno, std::string& str);

    // Raw access
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

    const char* ErrorString() { return mysql_error(m_dbconn); }
    int insertid() { return static_cast<int>(mysql_insert_id(m_dbconn)); }
};

// Inline helpers
inline void CDBCmd::Close()
{
    if (m_res)
    {
        mysql_free_result(m_res);
        m_res = nullptr;
    }
}

inline void CDBCmd::SetQuery(const char* sql) { m_sql = sql; }
inline void CDBCmd::SetQuery(const std::string& sql) { m_sql = sql; }

// GetRec by name simply forwards to index-based version
inline bool CDBCmd::GetRec(const char* fieldname, int& n) { return GetRec(FindField(fieldname), n); }
inline bool CDBCmd::GetRec(const char* fieldname, unsigned int& n) { return GetRec(FindField(fieldname), n); }
inline bool CDBCmd::GetRec(const char* fieldname, short& n) { return GetRec(FindField(fieldname), n); }
inline bool CDBCmd::GetRec(const char* fieldname, unsigned short& n) { return GetRec(FindField(fieldname), n); }
inline bool CDBCmd::GetRec(const char* fieldname, char& ch) { return GetRec(FindField(fieldname), ch); }
inline bool CDBCmd::GetRec(const char* fieldname, unsigned char& ch) { return GetRec(FindField(fieldname), ch); }
inline bool CDBCmd::GetRec(const char* fieldname, CLCString& str, bool bTrim) { return GetRec(FindField(fieldname), str, bTrim); }
inline bool CDBCmd::GetRec(const char* fieldname, float& f) { return GetRec(FindField(fieldname), f); }
inline bool CDBCmd::GetRec(const char* fieldname, LONGLONG& ll) { return GetRec(FindField(fieldname), ll); }
inline bool CDBCmd::GetRec(const char* fieldname, ULONGLONG& ll) { return GetRec(FindField(fieldname), ll); }
inline bool CDBCmd::GetRec(const char* fieldname, std::string& str) { return GetRec(FindField(fieldname), str); }

inline char* CDBCmd::GetRec(const char* fieldname) { return GetRec(FindField(fieldname)); }

inline char* CDBCmd::GetRec(int fieldno) { return m_row ? m_row[fieldno] : nullptr; }

#endif // __DBCMD_H__
