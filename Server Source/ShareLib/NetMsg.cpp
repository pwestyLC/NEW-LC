// NetMsg.cpp: implementation of the CNetMsg class.
//
//////////////////////////////////////////////////////////////////////
#include <signal.h>
#include <string.h>
#include <boost/pool/singleton_pool.hpp>
#include "NetMsg.h"
#include "CryptMem.h"
#include "SEED_256_KISA.h"
#include "LCCRC32.h"

CLCCRC32 gCRC32;

struct tag_pool {};
typedef boost::singleton_pool<tag_pool, (MAX_MESSAGE_SIZE + sizeof(int))> g_netmsgpool;

//////////////////////////////////////////////////////////////////////
// SEED 암호화를 위한 초기화
static DWORD pdwRoundKey[48];
static BYTE pbUserKey[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
							 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
							};

void CNetMsg::InitSEEDEncrypt()
{
	SeedRoundKey(pdwRoundKey, pbUserKey);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNetMsg::CNetMsg()
	:m_mtype(MSG_UNKNOWN)
	,m_buf_all(NULL)
	,m_buf(NULL)
{
	Init();
}

CNetMsg::CNetMsg(const CNetMsg& src)
{
	m_buf_all = m_buf = NULL;
	Init(src);
}

CNetMsg::CNetMsg(const CNetMsg::SP& src)
{
	m_buf_all = m_buf = NULL;
	Init(src);
}

CNetMsg::CNetMsg(int mtype)
{
	m_buf_all = m_buf = NULL;
	Init(mtype);
}

CNetMsg::CNetMsg(int mtype, int key)
{
	m_buf_all = m_buf = NULL;
	Init(mtype, key);
}

CNetMsg::~CNetMsg()
{
	if (m_buf_all)
	{
		g_netmsgpool::free(m_buf_all);
	}
}

void CNetMsg::Init()
{
	m_mtype = MSG_UNKNOWN;
	if (!m_buf_all)
	{
		m_buf_all = (unsigned char*)g_netmsgpool::malloc();
		m_buf = m_buf_all + sizeof(MsgHeader);
	}
	m_size = 0;
	m_ptr = 0;

	secretkey = 0;

	crypt_flag_ = false;
	crc32_flag_ = false;
	make_header_flag_ = false;

	// check sum
	m_buf_all[MAX_MESSAGE_SIZE + 0] = 0xCC;
	m_buf_all[MAX_MESSAGE_SIZE + 1] = 0xCC;
	m_buf_all[MAX_MESSAGE_SIZE + 2] = 0xCC;
	m_buf_all[MAX_MESSAGE_SIZE + 3] = 0xCC;
}

void CNetMsg::Init(int mtype)
{
	Init();
	m_mtype = mtype;

	unsigned char ubtype = (unsigned char)m_mtype;
	*this << ubtype;

	secretkey = 0;
}

void CNetMsg::Init(const CNetMsg& src)
{
	Init();
	m_mtype = src.m_mtype;
	m_size = src.m_size;
	memcpy(m_buf, src.m_buf, m_size);
	m_ptr = src.m_ptr;

	secretkey = src.secretkey;
}

void CNetMsg::Init(const CNetMsg::SP& src)
{
	Init();
	m_mtype = src->m_mtype;
	m_size = src->m_size;
	memcpy(m_buf, src->m_buf, m_size);
	m_ptr = src->m_ptr;

	secretkey = src->secretkey;
}

void CNetMsg::Init(int mtype, int key)
{
	Init();
	m_mtype = mtype;

	unsigned char ubtype = (unsigned char)m_mtype;
	*this << ubtype;

	secretkey = key;
}

void CNetMsg::Read(void* buf, long size)
{
	if (size < 1 || !CanRead(size))
		return ;
	memcpy(buf, m_buf + m_ptr, size);
	m_ptr += size;
}

void CNetMsg::Write(void* buf, long size)
{
	if (size < 1 || !CanWrite(size))
		return ;
	memcpy(m_buf + m_ptr, buf, size);
	m_ptr += size;
	if (m_ptr > m_size)
		m_size = m_ptr;
}

void CNetMsg::WriteRaw(void* buf, long size)
{
	if (size > MAX_MESSAGE_SIZE)
	{
		Init(MSG_UNKNOWN);
		return ;
	}
	unsigned char* mtype = (unsigned char*)buf;
	Init((int)(*mtype), secretkey);
	Write(mtype + MAX_MESSAGE_TYPE, size - MAX_MESSAGE_TYPE);
	m_size = size;
	m_ptr = 0;
	MoveFirst();
}

CNetMsg& CNetMsg::operator >> (CLCString& str)
{
	if (!m_buf || m_ptr >= m_size)
	{
		str.GetBuffer()[0] = '\0';
		str.SetLength(0);
		m_ptr = m_size;
		return *this;
	}

	// Find the null terminator
	size_t i;
	for (i = m_ptr; i < static_cast<size_t>(m_size); ++i)
	{
		if (m_buf[i] == '\0')
			break;
	}

	size_t len = i - static_cast<size_t>(m_ptr); // length excluding NULL
	size_t realRead = len;

	// Clamp to the string buffer size
	if (realRead >= static_cast<size_t>(str.BufferSize()))
		realRead = str.BufferSize() - 1; // leave space for NULL terminator

	// Copy directly into CLCString buffer
	memcpy(str.GetBuffer(), m_buf + m_ptr, realRead);
	str.GetBuffer()[realRead] = '\0';
	str.SetLength(static_cast<int>(realRead));

	// Move pointer past the null terminator if found
	m_ptr = (i < static_cast<size_t>(m_size)) ? i + 1 : m_size;

	return *this;
}




CNetMsg& CNetMsg::operator << (const char* str)
{
	if (str == NULL)
		return *this;

	// NULL을 포함해서 넣을 수 있으면 넣고 아니면 NULL만 넣는다, NULL도 못 넣으면 그냥 스킵
	if (CanWrite(strlen(str) + 1))
	{
		Write((void*)((const char*)str), strlen(str) + 1);
	}
	else if (CanWrite())
	{
		char ch = 0;
		*this << ch;
	}
	return *this;
}

CNetMsg& CNetMsg::operator << (CNetMsg& src)
{
	if (src.m_size < 1 || !CanWrite(src.m_size))
		return *this;
	memcpy(m_buf + m_ptr, src.m_buf, src.m_size);
	m_ptr += src.m_size;
	if (m_ptr > m_size)
		m_size = m_ptr;

	return *this;
}

CNetMsg& CNetMsg::operator << (CNetMsg::SP& src)
{
	if (src->m_size < 1 || !CanWrite(src->m_size))
		return *this;
	memcpy(m_buf + m_ptr, src->m_buf, src->m_size);
	m_ptr += src->m_size;
	if (m_ptr > m_size)
		m_size = m_ptr;

	return *this;
}

void CNetMsg::crypt()
{
	int loopcount = this->m_size / 16;
	for (int i = 0; i < loopcount; ++i)
	{
		SeedEncrypt(m_buf + (i * 16), pdwRoundKey);
	}

	crypt_flag_ = true;
}

void CNetMsg::decrypt()
{
	int loopcount = this->m_size / 16;
	for (int i = 0; i < loopcount; ++i)
	{
		SeedDecrypt(m_buf + (i * 16), pdwRoundKey);
	}
}

bool CNetMsg::checkCRC32()
{
	extern CLCCRC32 gCRC32;

	unsigned int nRecvCRCResult = *(unsigned int *)(this->m_buf + this->m_size);
	HTONL(nRecvCRCResult);

	unsigned int nCRCResult = gCRC32.CalcCRC32(this->m_buf, this->m_size);

	return (nRecvCRCResult == nCRCResult);
}

void CNetMsg::makeCRC32()
{
	// only wirte
	extern CLCCRC32 gCRC32;

	unsigned int nCRCResult = gCRC32.CalcCRC32(this->m_buf, this->m_size);
	HTONL(nCRCResult);
	*(unsigned int *)(this->m_buf + this->m_size) = nCRCResult;

	crc32_flag_ = true;
}

void CNetMsg::makeHeader()
{
	MsgHeader* h = (MsgHeader*)m_buf_all;

	h->reliable = (1 << 0) | (1 << 7) | (1 << 8);
	HTONS(h->reliable);

	// seq는 rnsocketioserviceTCP에서 만듦
	h->id = 0;
	h->size = m_size;
	HTONL(h->size);

	make_header_flag_ = true;
}

// m_buf + pos에서 length 만큼 패킷의 길이를 줄인다.
void CNetMsg::Reduce( int pos, int length )
{
	::memmove(m_buf + pos, m_buf + pos + length, m_size - length);
	m_size -= length;
}

void CNetMsg::setSize( int size )
{
	m_mtype = m_buf[0];
	m_size = size;

	if (m_size >= (MAX_MESSAGE_SIZE - sizeof(MsgHeader)))
		raise(SIGABRT);
}

bool CNetMsg::isRightPacket()
{
	if (m_buf_all[MAX_MESSAGE_SIZE + 0] != 0xCC
		|| m_buf_all[MAX_MESSAGE_SIZE + 1] != 0xCC
		|| m_buf_all[MAX_MESSAGE_SIZE + 2] != 0xCC
		|| m_buf_all[MAX_MESSAGE_SIZE + 3] != 0xCC)
		return false;

	return true;
}
