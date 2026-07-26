#pragma once

// D3D9 Device Reference Tracker
// Tracks which D3D9DeviceChild objects hold public references that
// contribute to the device's COM refcount (via the 0→1 AddRef transition).
// Call D3D9DevRefTracker::Dump() to see which objects are still holding
// a device ref at any point (e.g. right before device Release).
//
// Enable by defining D3D9_DEVREF_TRACKING_ENABLED in project settings
// or before including this header.

#ifdef D3D9_DEVREF_TRACKING_ENABLED

#include <cstdio>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <windows.h>

struct D3D9DevRefEntry {
    const char* typeName;   // human-readable type
    uint32_t    addCount;   // how many times 0→1 happened (should be 1 normally)
};

class D3D9DevRefTracker {
public:
    static void OnAddDeviceRef(void* obj, const char* typeName) {
        std::lock_guard<std::mutex> lock(GetMutex());
        auto& entry = GetMap()[obj];
        entry.typeName = typeName;
        entry.addCount++;

        char buf[256];
        snprintf(buf, sizeof(buf),
            "[DevRefTracker] +DEV ref: ptr=0x%p type=%-30s (addCount=%u)\n",
            obj, typeName, entry.addCount);
        OutputDebugStringA(buf);

        FILE* f = GetFile();
        if (f) { fprintf(f, "[%10u] %s", GetTickCount(), buf); fflush(f); }
    }

    static void OnRemoveDeviceRef(void* obj, const char* typeName) {
        std::lock_guard<std::mutex> lock(GetMutex());
        auto it = GetMap().find(obj);
        if (it != GetMap().end()) {
            GetMap().erase(it);
        }

        char buf[256];
        snprintf(buf, sizeof(buf),
            "[DevRefTracker] -DEV ref: ptr=0x%p type=%-30s (remaining=%zu)\n",
            obj, typeName, GetMap().size());
        OutputDebugStringA(buf);

        FILE* f = GetFile();
        if (f) { fprintf(f, "[%10u] %s", GetTickCount(), buf); fflush(f); }
    }

    // Call this before device Release() to see what's still holding refs
    static void Dump(const char* context = "Dump") {
        std::lock_guard<std::mutex> lock(GetMutex());
        auto& map = GetMap();

        char buf[512];
        snprintf(buf, sizeof(buf),
            "\n===== DevRefTracker %s: %zu objects holding device refs =====\n",
            context, map.size());
        OutputDebugStringA(buf);

        FILE* f = GetFile();
        if (f) { fprintf(f, "[%10u] %s", GetTickCount(), buf); }

        for (auto& pair : map) {
            snprintf(buf, sizeof(buf),
                "  ptr=0x%p  type=%-30s  addCount=%u\n",
                pair.first, pair.second.typeName, pair.second.addCount);
            OutputDebugStringA(buf);
            if (f) { fprintf(f, "[%10u] %s", GetTickCount(), buf); }
        }

        snprintf(buf, sizeof(buf), "===== End DevRefTracker %s =====\n\n", context);
        OutputDebugStringA(buf);
        if (f) { fprintf(f, "[%10u] %s", GetTickCount(), buf); fflush(f); }
    }

    static void Reset() {
        std::lock_guard<std::mutex> lock(GetMutex());
        GetMap().clear();
    }

private:
    static std::mutex& GetMutex() {
        static std::mutex s_mutex;
        return s_mutex;
    }

    static std::unordered_map<void*, D3D9DevRefEntry>& GetMap() {
        static std::unordered_map<void*, D3D9DevRefEntry> s_map;
        return s_map;
    }

    static FILE* GetFile() {
        static FILE* s_file = nullptr;
        static bool s_tried = false;
        if (!s_tried) {
            s_tried = true;
            s_file = fopen("D3D9_DevRefTracker.txt", "a");
        }
        return s_file;
    }
};

// Macros for use in D3D9DeviceChild
#define D3D9_DEVREF_TRACK_ADD(ptr, typeName)    D3D9DevRefTracker::OnAddDeviceRef((void*)(ptr), typeName)
#define D3D9_DEVREF_TRACK_REMOVE(ptr, typeName) D3D9DevRefTracker::OnRemoveDeviceRef((void*)(ptr), typeName)
#define D3D9_DEVREF_DUMP(ctx)                   D3D9DevRefTracker::Dump(ctx)

#else // D3D9_DEVREF_TRACKING_ENABLED

#define D3D9_DEVREF_TRACK_ADD(ptr, typeName)    ((void)0)
#define D3D9_DEVREF_TRACK_REMOVE(ptr, typeName) ((void)0)
#define D3D9_DEVREF_DUMP(ctx)                   ((void)0)

#endif // D3D9_DEVREF_TRACKING_ENABLED
