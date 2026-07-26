#include "logsystem.h"

#include <cstdarg>
#include <cstdio>
#include <mutex>
#include <string>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

static std::once_flag g_once;
static std::string g_logfileBase = "Server";

static std::mutex g_logMutex;
static std::ofstream g_logStream;
static std::string g_currentDate;
static const std::uint64_t g_rotationSize = 50ull * 1024ull * 1024ull; // 50 MB

static std::string GetDateString()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[16];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return std::string(buf);
}

static std::string GetTimestamp()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << ',' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

static void OpenLogFileForDate(const std::string& date)
{
    std::filesystem::create_directories(std::filesystem::path("LogFiles"));
    if (g_logStream.is_open()) g_logStream.close();
    std::string filename = std::string("LogFiles/") + g_logfileBase + "_" + date + ".log";
    g_logStream.open(filename, std::ios::out | std::ios::app);
}

static void InitLoggingOnce()
{
    g_currentDate = GetDateString();
    OpenLogFileForDate(g_currentDate);
}

static void EnsureInit()
{
    std::call_once(g_once, InitLoggingOnce);
}

enum class Severity { Fatal, Error, Warning, Info, Debug, Trace };

static const char* SeverityToString(Severity s)
{
    switch (s) {
    case Severity::Fatal:   return "FATAL";
    case Severity::Error:   return "ERROR";
    case Severity::Warning: return "WARN";
    case Severity::Info:    return "INFO";
    case Severity::Debug:   return "DEBUG";
    default:                return "TRACE";
    }
}

static void vlog(Severity sev, const char* fmt, va_list ap)
{
    EnsureInit();

    char msgbuf[8192];
    std::vsnprintf(msgbuf, sizeof(msgbuf), fmt, ap);

    std::lock_guard<std::mutex> lk(g_logMutex);

    // rotate on date change
    std::string date = GetDateString();
    if (date != g_currentDate) {
        g_currentDate = date;
        OpenLogFileForDate(g_currentDate);
    }

    if (!g_logStream.is_open()) return; // fail silently

    // rotation by size
    try {
        g_logStream.seekp(0, std::ios::end);
        auto sz = static_cast<std::uint64_t>(g_logStream.tellp());
        if (sz >= g_rotationSize) {
            g_logStream.close();
            // simple rotation: rename with timestamp suffix and create new
            std::string oldname = std::string("LogFiles/") + g_logfileBase + "_" + g_currentDate + ".log";
            std::string newname = oldname + ".1";
            std::error_code ec;
            std::filesystem::rename(oldname, newname, ec);
            OpenLogFileForDate(g_currentDate);
        }
    } catch (...) {
        // ignore filesystem errors
    }

    g_logStream << GetTimestamp() << " [" << SeverityToString(sev) << "] " << msgbuf << '\n';
    g_logStream.flush();
}

void LogSystem::setSubstitutedValue(const std::string variable, const std::string value)
{
    if (variable == "logfile") {
        std::lock_guard<std::mutex> lk(g_logMutex);
        g_logfileBase = value;
        // reopen using new base if already initialized
        if (g_logStream.is_open()) {
            OpenLogFileForDate(g_currentDate);
        }
    }
}

void LogSystem::configureXml(const std::string /*filename*/)
{
    EnsureInit();
}

void LogSystem::configureProperty(const std::string /*filename*/) { EnsureInit(); }
void LogSystem::configureBasic() { EnsureInit(); }

#define DEF_LOGFN(Name, Sev) \
void LogSystem::Name(const char* fmt, ...) { \
    va_list ap; va_start(ap, fmt); vlog(Sev, fmt, ap); va_end(ap); \
}

DEF_LOGFN(Fatal, Severity::Fatal)
DEF_LOGFN(Error, Severity::Error)
DEF_LOGFN(Warn, Severity::Warning)
DEF_LOGFN(Info, Severity::Info)
DEF_LOGFN(Debug, Severity::Debug)
DEF_LOGFN(Trace, Severity::Trace)
