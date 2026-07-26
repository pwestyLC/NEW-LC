#ifndef INCL_CRCCHECK_H
#define INCL_CRCCHECK_H
#ifdef PRAGMA_ONCE
#pragma once
#endif
 
#include <Engine/Base/CTString.h>
#define CRC_CHECK_FILECOUNT 31 //dethunter12 crc check file size change
 
// ---------------------------------------------------<<
class ENGINE_API CCrcCheck
{   
 
public:
    /* Default constructor. */
    CCrcCheck(void);
    /* Destructor. */
    ~CCrcCheck(void);
 
    static bool     LoadCrc(const char* Folder, const char* ZNFileName);
    static void     Export(const char* Folder);
 
private:
    static bool         Check( int num, int crc );
    static void         InitCrcTable();
    static ULONG        Reflect(ULONG ref, char ch);
    static ULONG        Get_CRC(unsigned char* buffer, ULONG bufsize);
    static long         FileSize(FILE *input);
 
};
 
#endif