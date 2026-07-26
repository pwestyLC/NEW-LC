#pragma once
// D3D9 Resource Lifecycle Diagnostic Logger
// Logs creation and release of D3D9 COM objects to a file.
// Enable by defining D3D_RESOURCE_LOG_ENABLED before including this header,
// or set it globally in the project preprocessor definitions.
//
// Output goes to "D3D_ResourceLog.txt" in the working directory.

#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <cstring>
#include <cctype>
#include <windows.h>

// Toggle this to enable/disable resource logging globally
#define D3D_RESOURCE_LOG_ENABLED
// Filter out noisy resource categories
#define D3D_RESOURCE_LOG_FILTER_TEXTURES

#ifdef D3D_RESOURCE_LOG_ENABLED

inline FILE* D3DResLog_GetFile()
{
    static FILE* s_pFile = nullptr;
    if (s_pFile == nullptr)
    {
        s_pFile = fopen("D3D_ResourceLog.txt", "a");
        if (s_pFile)
        {
            time_t t = time(nullptr);
            struct tm tm;
            localtime_s(&tm, &t);
            fprintf(s_pFile, "\n========== D3D Resource Log Session %04d-%02d-%02d %02d:%02d:%02d ==========\n",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
            fflush(s_pFile);
        }
    }
    return s_pFile;
}

inline bool D3DResLog_ContainsNoCase(const char* haystack, const char* needle)
{
    if (!haystack || !needle || !*needle)
        return false;

    for (const char* h = haystack; *h; ++h)
    {
        const char* hIt = h;
        const char* nIt = needle;
        while (*hIt && *nIt && std::tolower(static_cast<unsigned char>(*hIt)) == std::tolower(static_cast<unsigned char>(*nIt)))
        {
            ++hIt;
            ++nIt;
        }
        if (*nIt == '\0')
            return true;
    }
    return false;
}

inline bool D3DResLog_IsFilteredType(const char* typeName)
{
#ifdef D3D_RESOURCE_LOG_FILTER_TEXTURES
    if (D3DResLog_ContainsNoCase(typeName, "texture"))
        return true;
#endif
    return false;
}

inline void D3DResLog_Write(const char* fmt, ...)
{
    FILE* f = D3DResLog_GetFile();
    if (!f) return;
    
    // Timestamp
    DWORD tick = GetTickCount();
    fprintf(f, "[%10u] ", tick);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    
    fprintf(f, "\n");
    fflush(f);
}

// Log a Release() call with object pointer, type name, file/line, and resulting refcount
inline void D3DResLog_Release(const char* typeName, void* ptr, long refAfter, const char* file, int line)
{
    if (D3DResLog_IsFilteredType(typeName))
        return;
    D3DResLog_Write("RELEASE  %-30s ptr=0x%p  refAfter=%ld  [%s:%d]", typeName, ptr, refAfter, file, line);
}

// Log a full D3DRELEASE (loop to 0) call
inline void D3DResLog_FullRelease(const char* typeName, void* ptr, const char* file, int line)
{
    if (D3DResLog_IsFilteredType(typeName))
        return;
    D3DResLog_Write("D3DRELEASE %-28s ptr=0x%p  (released to 0)  [%s:%d]", typeName, ptr, file, line);
}

// Log resource creation
inline void D3DResLog_Create(const char* typeName, void* ptr, const char* details, const char* file, int line)
{
    if (D3DResLog_IsFilteredType(typeName))
        return;
    D3DResLog_Write("CREATE   %-30s ptr=0x%p  %s  [%s:%d]", typeName, ptr, details ? details : "", file, line);
}

// Log a phase/milestone marker
inline void D3DResLog_Marker(const char* msg)
{
    D3DResLog_Write("-------- %s --------", msg);
}

// Query and log the current refcount of a COM object (AddRef+Release trick)
inline long D3DResLog_GetRefCount(IUnknown* obj)
{
    if (!obj) return 0;
    obj->AddRef();
    return (long)obj->Release();
}

inline void D3DResLog_RefCount(const char* name, IUnknown* obj, const char* file, int line)
{
    if (!obj)
    {
        D3DResLog_Write("REFCOUNT %-30s ptr=NULL  [%s:%d]", name, file, line);
        return;
    }
    long ref = D3DResLog_GetRefCount(obj);
    D3DResLog_Write("REFCOUNT %-30s ptr=0x%p  ref=%ld  [%s:%d]", name, (void*)obj, ref, file, line);
}

// Convenience macros
#define D3DRES_LOG_CREATE(type, ptr, details)  D3DResLog_Create(#type, (void*)(ptr), details, __FILE__, __LINE__)
#define D3DRES_LOG_RELEASE(type, ptr, ref)     D3DResLog_Release(#type, (void*)(ptr), ref, __FILE__, __LINE__)
#define D3DRES_LOG_FULLRELEASE(type, ptr)      D3DResLog_FullRelease(#type, (void*)(ptr), __FILE__, __LINE__)
#define D3DRES_LOG_MARKER(msg)                 D3DResLog_Marker(msg)
#define D3DRES_LOG_REFCOUNT(name, ptr)         D3DResLog_RefCount(name, (IUnknown*)(ptr), __FILE__, __LINE__)
#define D3DRES_LOG(fmt, ...)                   D3DResLog_Write(fmt, __VA_ARGS__)
#ifdef D3D_RESOURCE_LOG_FILTER_TEXTURES
#define D3DRES_LOG_TEXTURE(fmt, ...)           ((void)0)
#else
#define D3DRES_LOG_TEXTURE(fmt, ...)           D3DResLog_Write(fmt, __VA_ARGS__)
#endif

#else // D3D_RESOURCE_LOG_ENABLED not defined

#define D3DRES_LOG_CREATE(type, ptr, details)  ((void)0)
#define D3DRES_LOG_RELEASE(type, ptr, ref)     ((void)0)
#define D3DRES_LOG_FULLRELEASE(type, ptr)      ((void)0)
#define D3DRES_LOG_MARKER(msg)                 ((void)0)
#define D3DRES_LOG_REFCOUNT(name, ptr)         ((void)0)
#define D3DRES_LOG(fmt, ...)                   ((void)0)
#define D3DRES_LOG_TEXTURE(fmt, ...)           ((void)0)

#endif // D3D_RESOURCE_LOG_ENABLED
