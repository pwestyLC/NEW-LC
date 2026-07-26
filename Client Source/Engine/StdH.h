
#if		defined(_MSC_VER) && (_MSC_VER >= 1600)
#	define WINDOW_SDK_70A
#endif

#define ENGINE_INTERNAL 1
#define ENGINE_EXPORTS 1

#pragma warning(disable : 4786)
#pragma warning(disable : 4391)		// Platform SDK Warning
#pragma warning(disable : 4996)		// CRT _s
#pragma warning(disable : 4200)		// packet zero-base array
#pragma warning(disable : 4819)		// packet zero-base array
#pragma warning(disable : 4603)		// packet zero-base array


#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <math.h>
#include <search.h>   // for qsort
#include <float.h>    // for FPU control

#include <crtdbg.h>


extern "C"
{
    #include <Engine/lua/lua.h>
    #include <Engine/lua/lualib.h>
    #include <Engine/lua/lauxlib.h>
};

#include <Engine/Xbox/XKeyboard.h>

  #include <winsock2.h>
  #include <windows.h>
  #include <mmsystem.h> // for timers

#include <Engine/Base/Types.h>
#include <Engine/Base/Assert.h>
#include <boost/thread.hpp>

#if		!defined(WORLD_EDITOR)
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/shared_ptr.hpp>
#endif	// WORLD_EDITOR

#ifdef	_DEBUG
#	pragma comment(lib, "zlibD.lib")
#	pragma comment(lib, "libpngD.lib")
#else	// _DEBUG
#	pragma comment(lib, "zlib.lib")
#	pragma comment(lib, "libpng.lib")
#endif	// _DEBUG

#ifndef XORSTR_H
#define XORSTR_H
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private:
	XorStr();
public:
	char s[BUFLEN];
	XorStr(const char* xs);
	~XorStr()
	{
		for (int i = 0; i < BUFLEN; i++) s[i] = 0;
	}
};



template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}

#endif // XORSTR_H