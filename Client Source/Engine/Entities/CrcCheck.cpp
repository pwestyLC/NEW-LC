#include "stdh.h"
#include <Engine/Entities/CrcCheck.h>
#include <sstream>
#include <fstream>

ULONG crc32_table[256];
ULONG ulPolynomial = 0x04c11db7;
CTString clientFolder;
CTString fnCheckFile[] =
    {
        
        "Data\\Character\\Mage\\ma.ba",
        "Data\\Character\\Mage\\ma.smc",
        "Data\\Character\\Healer\\hw.ba",
        "Data\\Character\\Healer\\hw.smc",
        "Data\\Character\\Knight\\ni.ba",
        "Data\\Character\\Knight\\ni.smc",
        "Data\\Character\\NightShadow\\ns.ba",
        "Data\\Character\\NightShadow\\ns.smc",
        "Data\\Character\\Rogue\\ro.ba",
        "Data\\Character\\Rogue\\ro.smc",
        "Data\\Character\\Sorcerer\\so.ba",
        "Data\\Character\\Sorcerer\\so.smc",
        "Data\\Character\\Sorcerer\\sot1.ba",
        "Data\\Character\\Sorcerer\\sot1.smc",
        "Data\\Character\\Sorcerer\\sot2.ba",
        "Data\\Character\\Sorcerer\\sot2.smc",
        "Data\\Character\\Titan\\ti.ba",
        "Data\\Character\\Titan\\ti.smc",
        "Bin\\Nksp.exe",
        "Bin\\NHzGuard.dll"
};

CCrcCheck::CCrcCheck(void)
{
}
 
 
CCrcCheck::~CCrcCheck(void)
{
}
 
bool CCrcCheck::LoadCrc( const char* Folder, const char* ZNFileName )  //disable crc check pwesty
{
    /*InitCrcTable();
    clientFolder = Folder;
 
    FILE *fp = fopen(ZNFileName, "rb");
    if(!fp)
        return false;
 
    int crc[CRC_CHECK_FILECOUNT]; //dethunter12 crc
    fread(&crc, sizeof(int), CRC_CHECK_FILECOUNT, fp);
    fclose(fp);
 
    for(int i=0; i<CRC_CHECK_FILECOUNT; i++)
    {
        if(!Check(i, crc[i]))
            return false;
    }*/
 
    return true;
}

void CCrcCheck::Export(const char* Folder)
{
    InitCrcTable();
    clientFolder = Folder;

    std::ofstream file("Data/Etc/binary.lod", std::ios::out | std::ios::binary);
    for (int i=0; i<CRC_CHECK_FILECOUNT; i++)
    {
        CTString strPath = clientFolder + fnCheckFile[i];
        FILE* fp = fopen(strPath.str_String, "rb");
        if(fp == NULL)
            return;
    
        long size = FileSize(fp);
        if(size < 1)
            return;
    
        unsigned char* buf = new unsigned char[size];
        memset(buf, 0, size);
    
        fread(buf, 1, size, fp);
        fclose(fp);
    
        int crc2 = Get_CRC(buf, size);

        file.write(reinterpret_cast<const char *>(&crc2), sizeof(crc2));
    }
    file.close();
}
 
bool CCrcCheck::Check( int num, int crc )
{
    CTString strPath = clientFolder + fnCheckFile[num];
    FILE* fp = fopen(strPath.str_String, "rb");
    if(fp == NULL)
        return false;
 
    long size = FileSize(fp);
    if(size < 1)
        return false;
 
    unsigned char* buf = new unsigned char[size];
    memset(buf, 0, size);
 
    fread(buf, 1, size, fp);
    fclose(fp);
 
    int crc2 = Get_CRC(buf, size);
 
    delete buf;
 
    return(crc == crc2);
 
}
 
void CCrcCheck::InitCrcTable()
{
 
    // 256 values representing ASCII character codes.
    for(int i = 0; i <= 0xFF; i++)
    {
        crc32_table[i]=Reflect(i, 8) << 24;
        for (int j = 0; j < 8; j++)
            crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
        crc32_table[i] = Reflect(crc32_table[i], 32);
    }
 
}
 
//////////////////////////////////////////////////////////////
// Reflection is a requirement for the official CRC-32 standard.
// You can create CRCs without it, but they won't conform to the standard.
//////////////////////////////////////////////////////////////////////////
 
ULONG CCrcCheck::Reflect(ULONG ref, char ch)
{                                 // Used only by Init_CRC32_Table()
 
    ULONG value(0);
 
    // Swap bit 0 for bit 7
    // bit 1 for bit 6, etc.
    for(int i = 1; i < (ch + 1); i++)
    {
        if(ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}
 
///////////////////////////////////////////////////////////////
 
ULONG CCrcCheck::Get_CRC(unsigned char* buffer, ULONG bufsize)
{
    ULONG  crc(0xffffffff);
    int len;
    len = bufsize;
    // Save the text in the buffer.
 
    // Perform the algorithm on each character
    // in the string, using the lookup table values.
 
    for(int i = 0; i < len; i++)
          crc = (crc >> 8) ^ crc32_table[(crc & 0xFF) ^ buffer[i]];
 
    // Exclusive OR the result with the beginning value.
    return crc^0xffffffff;
 
}
 
////////////////////////////////////////////////////////////
 
long CCrcCheck::FileSize(FILE *input)
{
 
  long fileSizeBytes;
  fseek(input, 0, SEEK_END);
  fileSizeBytes = ftell(input);
  fseek(input, 0, SEEK_SET);
 
  return fileSizeBytes;
}