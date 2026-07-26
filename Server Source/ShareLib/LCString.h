#ifndef __LCSTRING_H__
#define __LCSTRING_H__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef CIRCLE_WINDOWS
#define VSNPRINTF vsnprintf
#else
#define VSNPRINTF _vsnprintf
#endif // CIRCLE_WINDOWS

class CLCString
{
private:
    char* m_strBuf;
    int   m_nSize;

    char* Search(char* target, char* find);

public:
    // Constructors
    CLCString();
    CLCString(int size);
    CLCString(const CLCString& src);
    CLCString(const char* src);

    // Destructor
    ~CLCString();

    // Format string
    int Format(const char* fmt, ...);

    // Length of string
    int Length() const;

    // Size of buffer
    int BufferSize() const;

    // TRIM spaces
    void Trim(bool bOnlySpace = true);

    // Copy from src
    void CopyFrom(const char* src, int len);

    // Replace substring
    void Replace(char* oldstr, char* newstr);

    // Assign operators
    CLCString& operator=(const char* str);
    CLCString& operator=(const CLCString& str);

    // Array operator
    char operator[](int idx) const;

    // Cast operator
    operator const char* () const;

    // Append string
    CLCString& operator+=(const char* str);
    CLCString& operator+=(const CLCString& str);

    // Static helper
    static bool IsSpace(char ch);

    // Access internal buffer
    char* GetBuffer();
    const char* GetBuffer() const;

    // Set string length (update null terminator)
    void SetLength(int len);

protected:
    void Init(int size);
};

// ============================================
// Implementations (inline)
// ============================================

inline void CLCString::Init(int size)
{
    if (size <= 0) size = 1024;
    m_nSize = size;
    m_strBuf = new char[m_nSize];
    memset(m_strBuf, 0, sizeof(char) * m_nSize);
}

inline CLCString::CLCString(int size) { Init(size); }

inline CLCString::CLCString(const CLCString& src)
{
    Init(src.m_nSize);
    strcpy(m_strBuf, src.m_strBuf);
}

inline CLCString::CLCString(const char* src)
{
    if (!src) { Init(1); return; }
    Init((int)strlen(src) + 1);
    strcpy(m_strBuf, src);
}

inline CLCString::CLCString() { Init(51); }

inline CLCString::~CLCString()
{
    if (m_strBuf) delete[] m_strBuf;
    m_strBuf = nullptr;
    m_nSize = 0;
}

inline int CLCString::Length() const { return m_strBuf ? (int)strlen(m_strBuf) : 0; }

inline int CLCString::BufferSize() const { return m_nSize; }

inline int CLCString::Format(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    int ret = VSNPRINTF(m_strBuf, m_nSize - 1, fmt, vl);
    m_strBuf[m_nSize - 1] = '\0';
    va_end(vl);
    return ret;
}

inline void CLCString::Trim(bool bOnlySpace)
{
    int len = Length();
    if (len == 0) return;

    int start = 0;
    while ((bOnlySpace && m_strBuf[start] == ' ') || (!bOnlySpace && IsSpace(m_strBuf[start])))
        start++;

    if (start > 0)
    {
        memmove(m_strBuf, m_strBuf + start, len - start + 1);
        len -= start;
    }

    int end = len - 1;
    while (end >= 0 && ((bOnlySpace && m_strBuf[end] == ' ') || (!bOnlySpace && IsSpace(m_strBuf[end]))))
        end--;

    m_strBuf[end + 1] = '\0';
}

inline void CLCString::CopyFrom(const char* src, int len)
{
    if (!src || len < 1) { m_strBuf[0] = '\0'; return; }
    if (len >= m_nSize) len = m_nSize - 1;   // leave space for null terminator
    memcpy(m_strBuf, src, len);
    m_strBuf[len] = '\0';
}

inline void CLCString::Replace(char* oldstr, char* newstr)
{
    if (!oldstr || !newstr) return;

    char tmp[1024];
    char* p = Search(m_strBuf, oldstr);
    while (p)
    {
        *p = '\0';
        strcpy(tmp, p + strlen(oldstr));
        strcat(m_strBuf, newstr);
        strcat(m_strBuf, tmp);
        p = Search(p + strlen(newstr), oldstr);
    }
}

inline char* CLCString::Search(char* target, char* find)
{
    if (!target || !find) return nullptr;
    int s1 = (int)strlen(target);
    int s2 = (int)strlen(find);
    for (char* p = target; p <= target + s1 - s2; ++p)
        if (strncmp(p, find, s2) == 0) return p;
    return nullptr;
}

inline CLCString& CLCString::operator=(const char* str)
{
    if (!str) { m_strBuf[0] = '\0'; return *this; }
    int nSize = (int)strlen(str) + 1;
    if (nSize > m_nSize) nSize = m_nSize;
    memcpy(m_strBuf, str, nSize - 1);
    m_strBuf[nSize - 1] = '\0';
    return *this;
}

inline CLCString& CLCString::operator=(const CLCString& str)
{
    *this = str.m_strBuf;
    return *this;
}

inline char CLCString::operator[](int idx) const
{
    return (idx < 0 || idx >= Length()) ? 0 : m_strBuf[idx];
}

inline CLCString::operator const char* () const { return m_strBuf; }

inline CLCString& CLCString::operator+=(const char* str)
{
    if (!str) return *this;
    int curLen = Length();
    int strLen = (int)strlen(str);
    if (curLen + strLen + 1 > m_nSize) strLen = m_nSize - curLen - 1;
    if (strLen > 0)
    {
        memcpy(m_strBuf + curLen, str, strLen);
        m_strBuf[curLen + strLen] = '\0';
    }
    return *this;
}

inline CLCString& CLCString::operator+=(const CLCString& str)
{
    *this += str.m_strBuf;
    return *this;
}

inline bool CLCString::IsSpace(char ch)
{
    return (ch >= 0x09 && ch <= 0x0d) || (ch == 0x20);
}

// =======================
// New methods for CDBCmd compatibility
// =======================

inline char* CLCString::GetBuffer() { return m_strBuf; }
inline const char* CLCString::GetBuffer() const { return m_strBuf; }
inline void CLCString::SetLength(int len)
{
    if (len < 0) len = 0;
    if (len >= m_nSize) len = m_nSize - 1;
    m_strBuf[len] = '\0';
}

#endif // __LCSTRING_H__
