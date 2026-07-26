#include "DBCmd.h"
#include "bnf.h"
#include "logsystem.h"
#include "PrintExcuteInfo.h"
#include <boost/format.hpp>
#include <cstdlib>

CDBCmd::CDBCmd()
    : m_dbconn(nullptr)
    , m_nrecords(0)
    , m_res(nullptr)
    , m_row(nullptr)
    , m_fieldinfo(nullptr)
    , m_nfields(0)
{
}

CDBCmd::CDBCmd(MYSQL* mysql)
    : m_dbconn(mysql)
    , m_nrecords(0)
    , m_res(nullptr)
    , m_row(nullptr)
    , m_fieldinfo(nullptr)
    , m_nfields(0)
{
}

CDBCmd::~CDBCmd()
{
    Close();
}

bool CDBCmd::Open()
{
    Close();

    if (!m_dbconn)
    {
        LOG_ERROR("CDBCmd::Open() called with null DB connection. query[%s]", m_sql.c_str());
        return false;
    }

    if (mysql_real_query(m_dbconn, m_sql.c_str(), static_cast<unsigned long>(m_sql.size())) != 0)
    {
        LOG_ERROR("query error (mysql_real_query) : error[%s] query[%s]", mysql_error(m_dbconn), m_sql.c_str());
        return false;
    }

    m_res = mysql_store_result(m_dbconn);
    if (m_res == NULL)
    {
        // check if error exists
        if (mysql_errno(m_dbconn) != 0)
        {
            LOG_ERROR("query error (mysql_store_result) : error[%s] query[%s]", mysql_error(m_dbconn), m_sql.c_str());
            return false;
        }
        else
        {
            // empty result set, no rows, but table exists
            m_nrecords = 0;
            m_nfields = 0;
            m_fieldinfo = NULL;
            return true;
        }
    }

    m_nrecords = (int)mysql_num_rows(m_res);
    m_nfields = (int)mysql_num_fields(m_res);
    m_fieldinfo = mysql_fetch_fields(m_res);

    map_.clear();
    for (int i = 0; i < m_nfields; ++i)
    {
        map_.insert(map_t::value_type(m_fieldinfo[i].name, i));
    }

    return true;
}


bool CDBCmd::MoveFirst()
{
    if (!m_res) return false;

    mysql_data_seek(m_res, 0);
    m_row = mysql_fetch_row(m_res);
    return m_row != nullptr;
}

bool CDBCmd::Seek(int nOffset)
{
    if (!m_res) return false;

    mysql_data_seek(m_res, nOffset);
    m_row = mysql_fetch_row(m_res);
    return m_row != nullptr;
}

bool CDBCmd::MoveNext()
{
    if (!m_res) return false;

    m_row = mysql_fetch_row(m_res);
    return m_row != nullptr;
}

bool CDBCmd::Update()
{
    Close();

    if (!m_dbconn) return false;

    if (mysql_real_query(m_dbconn, m_sql.c_str(), static_cast<unsigned long>(m_sql.size())) != 0)
    {
        m_nrecords = 0;
        LOG_ERROR("query error (mysql_real_query) : error[%s] query[%s]", mysql_error(m_dbconn), m_sql.c_str());
        return false;
    }

    m_nrecords = static_cast<int>(mysql_affected_rows(m_dbconn));
    return true;
}

// ---------------------------
// GetRec by index implementations
// ---------------------------

bool CDBCmd::GetRec(int fieldno, int& n)
{
    char* ret = GetRec(fieldno);
    if (!ret) return false;

    n = std::atoi(ret);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned int& n)
{
    int tmp;
    if (!GetRec(fieldno, tmp)) return false;
    n = static_cast<unsigned int>(tmp);
    return true;
}

bool CDBCmd::GetRec(int fieldno, short& n)
{
    int tmp;
    if (!GetRec(fieldno, tmp)) return false;
    n = static_cast<short>(tmp);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned short& n)
{
    int tmp;
    if (!GetRec(fieldno, tmp)) return false;
    n = static_cast<unsigned short>(tmp);
    return true;
}

bool CDBCmd::GetRec(int fieldno, char& ch)
{
    int tmp;
    if (!GetRec(fieldno, tmp)) return false;
    ch = static_cast<char>(tmp);
    return true;
}

bool CDBCmd::GetRec(int fieldno, unsigned char& ch)
{
    int tmp;
    if (!GetRec(fieldno, tmp)) return false;
    ch = static_cast<unsigned char>(tmp);
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

    ll = std::atoll(ret);
    return true;
}

bool CDBCmd::GetRec(int fieldno, ULONGLONG& ll)
{
    char* ret = GetRec(fieldno);
    if (!ret) return false;

    ll = std::strtoull(ret, nullptr, 10);
    return true;
}

bool CDBCmd::GetRec(int fieldno, CLCString& str, bool bTrim)
{
    char* ret = GetRec(fieldno);
    if (!ret)
    {
        str = "";
        return false;
    }

    // Copy directly into CLCString buffer
    str.CopyFrom(ret, static_cast<int>(strlen(ret) + 1));
    if (bTrim) str.Trim();
    return true;
}

bool CDBCmd::GetRec(int fieldno, std::string& str)
{
    char* ret = GetRec(fieldno);
    if (!ret)
    {
        str.clear();
        return false;
    }
    str = ret;
    return true;
}

// ---------------------------
// FindField
// ---------------------------

int CDBCmd::FindField(const char* fieldname)
{
    auto it = map_.find(fieldname);
    if (it != map_.end()) return it->second;

    std::string msg = boost::str(boost::format("query[%s] / field not found: '%s'") % m_sql % fieldname);
    LOG_ERROR("%s", msg.c_str());
    PrintExcuteInfo::Instance()->SetStopMessage(msg);
    bnf::instance()->Stop();
    return -1;
}
