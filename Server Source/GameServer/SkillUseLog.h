#pragma once
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
class CPC;

class CSkillUseLog
{
public:
    // Main log function
    static void Log(
        CPC* ch,
        int skillIndex,
        float reuseTime,
        int skillDelay,
        bool abnormal
    );

    // Track last use pulse for cooldown calculation
    static int GetLastSkillUsePulse(int charIdx, int skillIndex);
    static void SetLastSkillUsePulse(int charIdx, int skillIndex, int pulse);

    static void LoadWatchedCharacters();
    static bool IsWatched(int charIdx);
private:
    static void RotateIfNeeded();
    static std::string CurrentDate();        // YYYY-MM-DD
    static std::string TimestampNow();       // YYYY-MM-DD HH:MM:SS,mmm
    static void EnsureDir();

private:
    // Log file
    static std::ofstream s_file;
    static std::string   s_currentDate;
    static std::mutex    s_mtx;

    // Map to track last skill use per character and skill
    static std::unordered_set<int> s_watchedChars;
    static std::unordered_map<int, std::unordered_map<int, int>> s_lastSkillUsePulse;
    
};
