#include <boost/thread/tss.hpp>
#include "stdhdrs.h"

#include "Log.h"
#include "Server.h"

//////////////////////////////////////////////////////////////////////////
static boost::thread_specific_ptr<CLogBuffer> _ptr;
//////////////////////////////////////////////////////////////////////////
CLogBuffer::CLogBuffer()
{
	m_buf = new char[MAX_BUFFER_SIZE];
}

CLogBuffer::~CLogBuffer()
{
	delete [] m_buf;
	m_buf = NULL;
}

CLogBuffer& CLogBuffer::operator << (const char* m)
{
	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%s", m);
	return *this;
}

CLogBuffer& CLogBuffer::operator << (int m)
{
	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%d", m);
	return *this;
}

CLogBuffer& CLogBuffer::operator << (LONGLONG m)
{
#ifdef _WIN64
	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%I64d", m);
#else
	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%lld", m);
#endif
	return *this;
}

CLogBuffer& CLogBuffer::operator << (ULONGLONG m)
{

	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%llu", m);

	return *this;
}

CLogBuffer& CLogBuffer::operator << (float m)
{
	m_nowpos += snprintf(m_buf + m_nowpos, MAX_BUFFER_SIZE - m_nowpos, "%.4f", m);
	return *this;
}

CLogBuffer& CLogBuffer::operator<<(const CLogHeader& lh)
{
    m_nowpos = 0;
    std::string msg;

    switch (lh.m_type)
    {
    case LHT_MSG:
        msg = std::string(lh.m_msg) + " > ";
        break;

    case LHT_MSG_ID:
        msg = std::string(lh.m_msg) + " > " + lh.m_id + " : ";
        break;

    case LHT_MSG_ID_NAME:
        msg = std::string(lh.m_msg) + " > " + lh.m_name + " : " + lh.m_id + " : ";
        break;

    case LHT_MSG_ID_NICK:
        msg = std::string(lh.m_msg) + " > " + lh.m_name + " : " + lh.m_nick + " : " + lh.m_id + " : ";
        break;

    case LHT_TIME_CLASSTYPE_MSG:
        msg = "GROUP_" + std::to_string(gserver->m_serverno) +
              " CHANNEL_" + std::to_string(gserver->m_subno) +
              " - [ lc@barunson " + lh.m_msg;
        break;

    default:
        msg = lh.m_msg; // fallback, just in case
        break;
    }

    // Copy safely into m_buf
    strncpy(m_buf, msg.c_str(), MAX_BUFFER_SIZE);
    m_buf[MAX_BUFFER_SIZE - 1] = '\0';
    m_nowpos = std::min<size_t>(msg.size(), MAX_BUFFER_SIZE - 1);

    return *this;
}


CLogBuffer& CLogBuffer::operator << (ITEMLOGMANI ilm)
{
	if (ilm.m_pItem == NULL)
	{
		(*this) << "(null)";
		return (*this);
	}

	if (ilm.m_pItem->IsRareItem() == true
			&& ilm.m_pItem->m_pRareOptionProto != NULL
			&& ilm.m_pItem->m_pRareOptionProto->GetIndex() > 0)
	{
		(*this) << "[ rare index: " << ilm.m_pItem->m_pRareOptionProto->GetIndex() << delim
				<< "rare bit: " << ilm.m_pItem->m_nRareOptionBit << "] " ;
	}

	(*this) << ilm.m_pItem->getDBIndex() << delim
			<< ilm.m_pItem->m_itemProto->getItemName() << delim
			<< ilm.m_pItem->m_serial.c_str() << delim
			<< ilm.m_pItem->getWearPos() << delim
			<< ilm.m_pItem->getPlus() << delim
			<< ilm.m_pItem->getFlag() << delim
			<< ilm.m_pItem->getUsed() << delim
			<< ilm.m_pItem->getUsed_2() << delim
			<< ilm.m_pItem->Count();

	if (!ilm.m_bSimple)
	{
		(*this) << delim << "OPTION"
				<< delim << ilm.m_pItem->m_nOption;
		int i;
		for (i = 0; i < ilm.m_pItem->m_nOption; i++)
		{
			(*this) << delim << ilm.m_pItem->m_option[i].m_type
					<< delim << ilm.m_pItem->m_option[i].m_value;
		}
	}

	(*this) << delim << "SOCKET" << delim << ilm.m_pItem->m_socketList.GetSocketCount();

	for (int i = 0; i < MAX_SOCKET_COUNT; i++)
	{
		(*this) << delim << ilm.m_pItem->m_socketList.GetJewelAt(i);
	}

	if (ilm.m_pItem->IsOriginItem())
	{
		(*this) << delim << "REFORM VARIATION INFO";
		for (int i = 0; i < MAX_VARIATION_COUNT; i++)
		{
			(*this) << delim << ilm.m_pItem->getOriginVar(i);
		}
	}

	return (*this);
}

CLogBuffer& CLogBuffer::GetCLogBuffer()
{
	if (_ptr.get() == NULL)
	{
		_ptr.reset(new CLogBuffer);
	}

	return *(_ptr.get());
}

void CLogBuffer::Write()
{
	LOG_INFO(m_buf);
}
