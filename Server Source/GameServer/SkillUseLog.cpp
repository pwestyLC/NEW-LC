#include "stdhdrs.h"
#include "Character.h"
#include "SkillUseLog.h"
#include <filesystem>
#include <iomanip>
#include <sstream>
#include "Server.h"

namespace fs = std::filesystem;

std::ofstream CSkillUseLog::s_file;
std::string   CSkillUseLog::s_currentDate;
std::mutex    CSkillUseLog::s_mtx;
std::unordered_set<int> CSkillUseLog::s_watchedChars;
std::unordered_map<int, std::unordered_map<int, int>> CSkillUseLog::s_lastSkillUsePulse;


void CSkillUseLog::LoadWatchedCharacters()
{
    std::lock_guard<std::mutex> lock(s_mtx);

    s_watchedChars.clear();

    // Adjust DB names to YOUR schema
    CDBCmd cmd;
    cmd.Init(&gserver->m_dbchar);

    cmd.SetQuery(
        "SELECT char_index FROM t_skill_watch"
    );

    if (!cmd.Open())
        return;

    while (cmd.MoveNext())
    {
        int charIdx = 0;
        cmd.GetRec("char_index", charIdx);
        s_watchedChars.insert(charIdx);
    }

    LOG_INFO("SkillUseLog: Loaded %zu watched characters",
        s_watchedChars.size());
}

bool CSkillUseLog::IsWatched(int charIdx)
{
    return s_watchedChars.find(charIdx) != s_watchedChars.end();
}
void CSkillUseLog::EnsureDir()
{
    fs::create_directories("Checks");
}

std::string CSkillUseLog::CurrentDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return buf;
}

std::string CSkillUseLog::TimestampNow()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t t = system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << ',' << std::setw(3) << std::setfill('0') << ms.count();

    return oss.str();
}

void CSkillUseLog::RotateIfNeeded()
{
    std::string today = CurrentDate();
    if (today == s_currentDate && s_file.is_open())
        return;

    if (s_file.is_open())
        s_file.close();

    EnsureDir();

    s_currentDate = today;
    std::string filename = "Checks/skill_use_" + today + ".log";
    s_file.open(filename, std::ios::out | std::ios::app);
}

int CSkillUseLog::GetLastSkillUsePulse(int charIdx, int skillIndex)
{
    auto itChar = s_lastSkillUsePulse.find(charIdx);
    if (itChar != s_lastSkillUsePulse.end())
    {
        auto itSkill = itChar->second.find(skillIndex);
        if (itSkill != itChar->second.end())
            return itSkill->second;
    }
    return 0;
}

void CSkillUseLog::SetLastSkillUsePulse(int charIdx, int skillIndex, int pulse)
{
    s_lastSkillUsePulse[charIdx][skillIndex] = pulse;
}

void CSkillUseLog::Log(
    CPC* ch,
    int skillIndex,
    float reuseTime,      
    int skillDelay,       
    bool abnormal
)
{
    if (!ch)
        return;

    if (!IsWatched(ch->m_index))
        return;
    std::lock_guard<std::mutex> lock(s_mtx);
    RotateIfNeeded();
    if (!s_file.is_open())
        return;

    // Update last pulse
    SetLastSkillUsePulse(ch->m_index, skillIndex, gserver->m_pulse);

    
    s_file
        << TimestampNow() << " | "
        << "charIdx=" << ch->m_index << " | "
        << "name=" << ch->m_name << " | "
        << "skill=" << skillIndex << " | "
        << "reuse=" << reuseTime << " | "
        << "skillDelay=" << skillDelay << " | "
        << (abnormal ? "ABNORMAL" : "OK")
        << '\n';

    s_file.flush();
}
