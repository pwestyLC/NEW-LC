#include "DBCmd.h"
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "Log.h"
#include <new>

CDBCmd::CDBCmd()
    : m_dbconn(nullptr), m_res(nullptr), m_fieldinfo(nullptr),
    m_nfields(0), m_nrecords(0), m_stmt(nullptr), m_bindResult(nullptr),
    m_sqlLen(0)
{
}

CDBCmd::~CDBCmd()
{
    Close();
}

void CDBCmd::Init(MYSQL* conn)
{
    m_dbconn = conn;
    if (m_dbconn)
        mysql_set_character_set(m_dbconn, "utf8mb4");
}

void CDBCmd::SetQuery(const char* sql)
{
    char tmp[8192];
    BackSlash(tmp, sizeof(tmp), sql);

    // Ensure m_sql has enough buffer to hold the full escaped SQL.
    size_t srcLen = strlen(tmp);
    // Destroy and placement-new a CLCString with sufficient buffer size
    m_sql.~CLCString();
    new (&m_sql) CLCString(static_cast<int>(srcLen + 1));
    // Copy the full string into the newly allocated buffer
    m_sql.CopyFrom(tmp, static_cast<int>(srcLen + 1));
    m_sqlLen = static_cast<unsigned long>(srcLen);
}

bool CDBCmd::Open()
{
    Close();
    if (!m_dbconn) return false;
    // Use non-prepared queries exclusively to avoid mixing stmt APIs and
    // causing "Commands out of sync" when multiple queries run on the same
    // connection. This matches the original Linux behaviour and is simpler.
    if (mysql_real_query(m_dbconn, m_sql, m_sqlLen) != 0)
    {
        unsigned int conn_err = mysql_errno(m_dbconn);
        const char* conn_errstr = mysql_error(m_dbconn);
        // Additional diagnostics: log length and hex dump of the SQL string as seen by the client
        const char* s = m_sql;
        unsigned long len = m_sqlLen;
        size_t actual_len = s ? strlen(s) : 0;
        char hexdump[1024];
        hexdump[0] = '\0';
        if (s && len > 0) {
            unsigned long maxBytes = len < 64 ? len : 64;
            unsigned long copied = 0;
            for (unsigned long i = 0; i < maxBytes && copied + 4 < sizeof(hexdump); ++i) {
                int n = snprintf(hexdump + copied, sizeof(hexdump) - copied, "%02X ", (unsigned char)s[i]);
                if (n <= 0) break;
                copied += (unsigned long)n;
            }
        }

        (void)conn_err; (void)conn_errstr; (void)actual_len; (void)hexdump;
        return false;
    }

    m_res = mysql_store_result(m_dbconn);
    if (!m_res)
        return false;

    (void)m_res; (void)m_sql;

    m_nfields = static_cast<int>(mysql_num_fields(m_res));
    m_fieldinfo = mysql_fetch_fields(m_res);
    m_nrecords = static_cast<int>(mysql_num_rows(m_res));

    // Log field names for diagnostics (helps detect mismatched/aliased column names)
    if (m_fieldinfo && m_nfields > 0) {
        CLCString fieldlist(1024);
        for (int i = 0; i < m_nfields; ++i) {
            if (i > 0) fieldlist += ",";
            fieldlist += m_fieldinfo[i].name;
        }
        (void)fieldlist;
    }

    m_row = mysql_fetch_row(m_res);
    return true;
}

bool CDBCmd::Update()
{
    Close();
    if (!m_dbconn) return false;

    m_stmt = mysql_stmt_init(m_dbconn);
    if (!m_stmt) return false;

    if (mysql_stmt_prepare(m_stmt, m_sql, m_sqlLen) != 0)
    {
        mysql_stmt_close(m_stmt);
        m_stmt = nullptr;
        return false;
    }

    if (mysql_stmt_execute(m_stmt) != 0)
        return false;

    m_nrecords = static_cast<int>(mysql_stmt_affected_rows(m_stmt));
    return true;
}

void CDBCmd::Close()
{
    if (m_res) { mysql_free_result(m_res); m_res = nullptr; }
    if (m_stmt) { mysql_stmt_close(m_stmt); m_stmt = nullptr; }
    if (m_bindResult) { delete[] m_bindResult; m_bindResult = nullptr; }
    m_fieldinfo = nullptr;
    m_nrecords = 0;
    m_nfields = 0;
}

bool CDBCmd::MoveFirst()
{
    if (!m_res) return false;
    mysql_data_seek(m_res, 0);
    m_row = mysql_fetch_row(m_res);
    return m_row != nullptr;
}

bool CDBCmd::MoveNext()
{
    if (!m_res) return false;
    m_row = mysql_fetch_row(m_res);
    return m_row != nullptr;
}

char* CDBCmd::GetRec(int fieldno)
{
    if (!m_res || !m_row || fieldno < 0 || fieldno >= m_nfields)
        return nullptr;
    return m_row[fieldno];
}

char* CDBCmd::GetRec(const char* fieldname)
{
    return GetRec(FindField(fieldname));
}

int CDBCmd::FindField(const char* fieldname)
{
    if (!m_fieldinfo) return -1;
    for (int i = 0; i < m_nfields; ++i)
        if (strcmp(m_fieldinfo[i].name, fieldname) == 0)
            return i;
    return -1;
}

// ======================
// GetRec overloads
// ======================

bool CDBCmd::GetRec(int fieldno, int& n)
{
    char* ret = GetRec(fieldno);
    if (!ret) return false;
    n = std::atoi(ret);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned int& n)
{
    int t;
    if (!GetRec(fieldno, t)) return false;
    n = static_cast<unsigned int>(t);
    return true;
}

bool CDBCmd::GetRec(int fieldno, short& n)
{
    int t;
    if (!GetRec(fieldno, t)) return false;
    n = static_cast<short>(t);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned short& n)
{
    int t;
    if (!GetRec(fieldno, t)) return false;
    n = static_cast<unsigned short>(t);
    return true;
}

bool CDBCmd::GetRec(int fieldno, char& ch)
{
    int t;
    if (!GetRec(fieldno, t)) return false;
    ch = static_cast<char>(t);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned char& ch)
{
    int t;
    if (!GetRec(fieldno, t)) return false;
    ch = static_cast<unsigned char>(t);
    return true;
}

bool CDBCmd::GetRec(int fieldno, float& f)
{
    char* ret = GetRec(fieldno);
    if (!ret) return false;
    f = static_cast<float>(std::atof(ret));
    return true;
}

bool CDBCmd::GetRec(int fieldno, LONGLONG& ll)
{
    char* ret = GetRec(fieldno);
    if (!ret) return false;
    ll = std::strtoll(ret, nullptr, 10);
    return true;
}

bool CDBCmd::GetRec(int fieldno, CLCString& str, bool bTrim)
{
    char* ret = GetRec(fieldno);
    if (!ret) { str = ""; return false; }

    char* p = ret;
    if (bTrim) while (*p && isspace(*p)) p++;

    char* pStart = p;
    if (strlen(pStart) < 1) { str = ""; return true; }

    char* pEnd = pStart + strlen(pStart) - 1;
    if (bTrim) while (pEnd >= pStart && isspace(*pEnd)) pEnd--;

    if (pEnd < pStart) { str = ""; return true; }

    int len = static_cast<int>(pEnd - pStart + 2);
    if (len > str.BufferSize()) len = str.BufferSize();

    char* tmp = new char[len];
    memcpy(tmp, pStart, len - 1);
    tmp[len - 1] = '\0';
    str = tmp;
    delete[] tmp;

    return true;
}

// Fieldname versions
bool CDBCmd::GetRec(const char* fieldname, int& n) { return GetRec(FindField(fieldname), n); }
bool CDBCmd::GetRec(const char* fieldname, unsigned int& n) { return GetRec(FindField(fieldname), n); }
bool CDBCmd::GetRec(const char* fieldname, short& n) { return GetRec(FindField(fieldname), n); }
bool CDBCmd::GetRec(const char* fieldname, unsigned short& n) { return GetRec(FindField(fieldname), n); }
bool CDBCmd::GetRec(const char* fieldname, char& ch) { return GetRec(FindField(fieldname), ch); }
bool CDBCmd::GetRec(const char* fieldname, unsigned char& ch) { return GetRec(FindField(fieldname), ch); }
bool CDBCmd::GetRec(const char* fieldname, float& f) { return GetRec(FindField(fieldname), f); }
bool CDBCmd::GetRec(const char* fieldname, LONGLONG& ll) { return GetRec(FindField(fieldname), ll); }
bool CDBCmd::GetRec(const char* fieldname, CLCString& str, bool bTrim) { return GetRec(FindField(fieldname), str, bTrim); }
