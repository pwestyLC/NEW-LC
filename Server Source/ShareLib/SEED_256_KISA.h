
#ifndef _SEED_256_KISA_H
#define _SEED_256_KISA_H

/********************** Include files ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************* Type Definitions **********************/

#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#else
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t  BYTE;
#endif
/* Endianness detection */
#if defined(_WIN32) || defined(_WIN64) || \
    defined(__i386__) || defined(__x86_64__) || defined(__x86_64) || \
    defined(__ARMEL__) || defined(__AARCH64EL__)
    #define SEED_LITTLE_ENDIAN
#else
    #if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
        #define SEED_LITTLE_ENDIAN
    #else
        #define SEED_BIG_ENDIAN
    #endif
#endif

/******************* Constant Definitions *********************/

#define NoRounds         24
#define NoRoundKeys      (NoRounds*2)
#define SeedBlockSize    16    /* in bytes */
#define SeedBlockLen     128   /* in bits */

/********************** Common Macros ************************/

#if defined(_MSC_VER)
#define ROTL(x, n)     (_lrotl((x), (n)))
#define ROTR(x, n)     (_lrotr((x), (n)))
#else
#define ROTL(x, n)     (((x) << (n)) | ((x) >> (32-(n))))
#define ROTR(x, n)     (((x) >> (n)) | ((x) << (32-(n))))
#endif

/**************** Function Prototype Declarations **************/

void SeedEncrypt(		/* encryption function */
	BYTE *pbData, 				// [in,out]	data to be encrypted
	DWORD *pdwRoundKey			// [in]			round keys for encryption
);
void SeedDecrypt(		/* decryption function */
	BYTE *pbData, 				// [in,out]	data to be decrypted
	DWORD *pdwRoundKey			// [in]			round keys for decryption
);
void SeedRoundKey(		/* key scheduling function */
	DWORD *pdwRoundKey, 		// [out]		round keys for encryption or decryption
	BYTE *pbUserKey				// [in]			secret user key
);

/*************************** END OF FILE **************************************/
#endif
