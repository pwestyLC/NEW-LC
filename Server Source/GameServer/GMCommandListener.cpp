#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

#define DEMIGOD
#include "GMCommandListener.h"
#include "../ShareLib/NetMsg.h"
#include "../ShareLib/Config.h"
#include "../ShareLib/packetType/ptype_server_to_server_kick.h"
#include "../ShareLib/packetType/ptype_reserved_gm_command.h"
#include "Utils.h"
#include "Server.h"
#include "CmdMsg.h"
#include "AutoBuffer.h"

#if defined(_WIN32)
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using socklen_t = int;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1
#define closesocket close
#define SOCKET int
#endif

// -------------------------------------------------------------
// Command handler
// -------------------------------------------------------------
// Helper: uppercase a string (avoid C++11 lambdas for older toolchains)
static std::string strToUpper(const std::string& s)
{
    std::string r = s;
    for (size_t i = 0; i < r.size(); ++i)
        r[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(r[i])));
    return r;
}

void HandleCommand(const std::string& cmd)
{
    std::istringstream ss(cmd);
    std::string token;
    ss >> token;

    if (token == "gm_kick")
    {
        std::string player;
        ss >> player;
        if (!player.empty())
        {
            CNetMsg::SP rmsg(new CNetMsg);
            ServerToServerPacket::makeKickUser(rmsg, 5, player.c_str()); // 5 = DISCORD BOT GM idx
            SEND_Q(rmsg, gserver->m_helper);
            LOG_INFO("[Discord-Bot] Kick requested for %s", player.c_str());
        }
    }
    else if (token == "gm_autobuff")
    {
        // Usage: gm_autobuff <on|off|reload> [minutes] [subno...]
        // Example: "gm_autobuff on 15 1 2 3 4" -> minutes=15, target subnos=1,2,3,4
        std::string subcmd;
        ss >> subcmd;

        if (subcmd.empty())
        {
            LOG_INFO("[Discord-Bot] Invalid gm_autobuff usage: missing subcommand");
            return;
        }

        // use file-scope helper instead of lambda to support older compilers
        // 'strToUpper' defined above

        // collect remaining tokens
        std::vector<int> nums;
        std::string tok;
        while (ss >> tok)
        {
            // accept only numeric tokens as subno or minutes
            bool isnum = !tok.empty();
            for (size_t i = 0; i < tok.size() && isnum; ++i) {
                if (!std::isdigit(static_cast<unsigned char>(tok[i]))) isnum = false;
            }
            if (isnum) nums.push_back(atoi(tok.c_str()));
        }

        int mins = 0;
        std::vector<int> targetSubnos;

        if (!nums.empty())
        {
            // first numeric token is minutes (if subcmd is ON), rest are subnos
            if (strToUpper(subcmd) == "ON")
            {
                mins = nums[0];
                for (size_t i = 1; i < nums.size(); ++i) targetSubnos.push_back(nums[i]);
            }
            else
            {
                // OFF/RELOAD: treat numeric tokens as target subnos
                for (size_t i = 0; i < nums.size(); ++i) targetSubnos.push_back(nums[i]);
            }
        }

        // If targets provided and this server's subno is not among them, ignore
        if (!targetSubnos.empty())
        {
            bool match = false;
            for (size_t i = 0; i < targetSubnos.size(); ++i) if (targetSubnos[i] == gserver->m_subno) { match = true; break; }
            if (!match)
            {
                LOG_INFO("[Discord-Bot] gm_autobuff target subnos do not include this subno %d - ignoring", gserver->m_subno);
                return;
            }
        }

        if (strToUpper(subcmd) == "ON")
        {
            int intervalSec = gserver->m_buffSystem.SetTime(mins);
            gserver->m_buffSystem.TurnOn();
            gserver->m_buffSystem.TickSystem();
            LOG_INFO("[Discord-Bot] AutoBuff ON (interval=%d sec)", intervalSec);
        }
        else if (strToUpper(subcmd) == "OFF")
        {
            gserver->m_buffSystem.TurnOff();
            LOG_INFO("[Discord-Bot] AutoBuff OFF");
        }
        else if (strToUpper(subcmd) == "RELOAD")
        {
            gserver->m_buffSystem.ReloadTable();
            gserver->m_buffSystem.TickSystem();
            LOG_INFO("[Discord-Bot] AutoBuff table reloaded and buffs applied");
        }
        else
        {
            LOG_INFO("[Discord-Bot] Invalid gm_autobuff usage: unknown subcommand %s", subcmd.c_str());
        }
    }
    else if (token == "gm_echo")
    {
        std::string scope;
        ss >> scope;
        std::string message;
        std::getline(ss, message);
        boost::algorithm::trim(message);

#ifdef _WIN32
        // If the incoming bytes are already UTF-8, don't reinterpret them as CP_ACP
        auto is_valid_utf8 = [](const std::string& s) -> bool {
            const unsigned char* bytes = reinterpret_cast<const unsigned char*>(s.c_str());
            size_t len = s.size();
            size_t i = 0;
            while (i < len) {
                if (bytes[i] <= 0x7F) { i++; continue; }
                else if ((bytes[i] & 0xE0) == 0xC0) {
                    if (i + 1 >= len) return false;
                    if ((bytes[i + 1] & 0xC0) != 0x80) return false;
                    unsigned int code = ((bytes[i] & 0x1F) << 6) | (bytes[i + 1] & 0x3F);
                    if (code < 0x80) return false;
                    i += 2;
                }
                else if ((bytes[i] & 0xF0) == 0xE0) {
                    if (i + 2 >= len) return false;
                    if ((bytes[i + 1] & 0xC0) != 0x80 || (bytes[i + 2] & 0xC0) != 0x80) return false;
                    unsigned int code = ((bytes[i] & 0x0F) << 12) | ((bytes[i + 1] & 0x3F) << 6) | (bytes[i + 2] & 0x3F);
                    if (code < 0x800) return false;
                    i += 3;
                }
                else if ((bytes[i] & 0xF8) == 0xF0) {
                    if (i + 3 >= len) return false;
                    if ((bytes[i + 1] & 0xC0) != 0x80 || (bytes[i + 2] & 0xC0) != 0x80 || (bytes[i + 3] & 0xC0) != 0x80) return false;
                    unsigned int code = ((bytes[i] & 0x07) << 18) | ((bytes[i + 1] & 0x3F) << 12) | ((bytes[i + 2] & 0x3F) << 6) | (bytes[i + 3] & 0x3F);
                    if (code < 0x10000 || code > 0x10FFFF) return false;
                    i += 4;
                }
                else return false;
            }
            return true;
            };

        if (!message.empty() && !is_valid_utf8(message)) {
            int wlen = MultiByteToWideChar(CP_ACP, 0, message.c_str(), -1, nullptr, 0);
            if (wlen > 0) {
                std::wstring wmsg(wlen, 0);
                MultiByteToWideChar(CP_ACP, 0, message.c_str(), -1, &wmsg[0], wlen);
                int u8len = WideCharToMultiByte(CP_UTF8, 0, wmsg.c_str(), -1, nullptr, 0, nullptr, nullptr);
                if (u8len > 0) {
                    std::string utf8msg(u8len, 0);
                    WideCharToMultiByte(CP_UTF8, 0, wmsg.c_str(), -1, &utf8msg[0], u8len, nullptr, nullptr);
                    message = utf8msg;
                }
            }
        }
#endif

        if (!scope.empty() && !message.empty())
        {
            CNetMsg::SP rmsg(new CNetMsg);
            if (scope == "zone")
                MsgrNoticeMsg(rmsg, -1, gserver->m_serverno, gserver->m_subno, 0, message.c_str());
            else if (scope == "server")
                MsgrNoticeMsg(rmsg, -1, gserver->m_serverno, -1, -1, message.c_str());
            else if (scope == "all")
                MsgrNoticeMsg(rmsg, -1, -1, -1, -1, message.c_str());
            else if (scope == "subserver")
                MsgrNoticeMsg(rmsg, -1, gserver->m_serverno, gserver->m_subno, -1, message.c_str());
            else if (scope == "zoneall")
                MsgrNoticeMsg(rmsg, -1, -1, -1, 0, message.c_str());
            else {
                LOG_INFO("[Discord-Bot] Unknown echo scope: %s", scope.c_str());
                return;
            }

            SEND_Q(rmsg, gserver->m_messenger);
            LOG_INFO("[Discord-Bot] Echo sent: %s -> %s", scope.c_str(), message.c_str());
        }
    }
    else if (token == "gm_shutdown")
    {
        // Usage: gm_shutdown <serverno> <subno> <timeSec> <message>
        int serverno = 0, subno = 0, t = 0;
        ss >> serverno >> subno >> t;

        std::string message;
        std::getline(ss, message);
        boost::algorithm::trim(message);

        CNetMsg::SP rmsg(new CNetMsg);
        MsgrGMShutdownReqMsg(rmsg, serverno, subno, t, message.c_str());
        SEND_Q(rmsg, gserver->m_messenger);

        LOG_INFO("[Discord-Bot] Shutdown triggered for server %d-%d in %d sec: %s",
            serverno, subno, t, message.c_str());
    }
    else if (token == "gm_reboot")
    {
        // Usage: gm_reboot <scope> <delaySec> <message>
        std::string scope;
        ss >> scope;

        int t = 0;
        ss >> t;

        std::string message;
        std::getline(ss, message);
        boost::algorithm::trim(message);

        CNetMsg::SP rmsg(new CNetMsg);

        if (scope == "all")
            MsgrRebootReqMsg(rmsg, -1, -1, -1, -1);
        else if (scope == "server")
            MsgrRebootReqMsg(rmsg, -1, gserver->m_serverno, -1, -1);
        else if (scope == "subserver")
            MsgrRebootReqMsg(rmsg, -1, gserver->m_serverno, gserver->m_subno, -1);
        else
        {
            LOG_INFO("[Discord-Bot] Unknown reboot scope: %s", scope.c_str());
            return;
        }

        RefMsg(rmsg) << t << message.c_str();
        SEND_Q(rmsg, gserver->m_messenger);

        LOG_INFO("[Discord-Bot] Reboot triggered (%s) in %d sec: %s",
            scope.c_str(), t, message.c_str());
    }

    else if (token == "gm_itemget")
    {
        int charIndex = 0, dbindex = 0, plus = 0, flag = 0;
        LONGLONG count = 1;

        ss >> charIndex >> dbindex >> plus >> flag >> count;

        if (charIndex <= 0 || dbindex <= 0)
        {
            LOG_INFO("[Discord-Bot] Invalid itemget command: charIndex=%d dbindex=%d", charIndex, dbindex);
            return;
        }

        CPC* target = PCManager::instance()->getPlayerByCharIndex(charIndex);
        if (target == nullptr)
        {
            LOG_INFO("[Discord-Bot] Character %d not found (offline or invalid).", charIndex);
            return;
        }

        CItem* item = gserver->m_itemProtoList.CreateItem(dbindex, -1, plus, flag, count);
        if (item == nullptr)
        {
            LOG_INFO("[Discord-Bot] Failed to create item %d", dbindex);
            return;
        }

        if (target->m_inventory.addItem(item) == false)
        {
            delete item;
            CNetMsg::SP rmsg(new CNetMsg);
            SysFullInventoryMsg(rmsg, 0);
            SEND_Q(rmsg, target->m_desc);
            LOG_INFO("[Discord-Bot] Inventory full for char %s(%d)", target->GetName(), charIndex);
            return;
        }

        addItemResult& addResult = target->m_inventory.getLastAddItemResult();
        if (addResult.pItem)
        {
            GAMELOG << init("DISCORD_ITEMGET", target)
                << itemlog(addResult.pItem)
                << end;
        }

        // Optional: send a system notice to the player
        CNetMsg::SP msg(new CNetMsg);
        SayMsg(msg, MSG_CHAT_NOTICE, 0, "", "", "An item has been added to your inventory by the Discord Bot.");
        SEND_Q(msg, target->m_desc);

        LOG_INFO("[Discord-Bot] Item %d (count=%lld, plus=%d, flag=%d) sent to [%s](%d)",
            dbindex, count, plus, flag, target->GetName(), charIndex);
    }
}


// -------------------------------------------------------------
// Listener thread
// -------------------------------------------------------------
void StartGMCommandListener()
{
    std::thread([]() {

#if defined(_WIN32)
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

        std::string bind_host = gserver->m_config.Find("Server", "IP");
        int bind_port = atoi(gserver->m_config.Find("Server", "GMPort"));

        SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == INVALID_SOCKET) {
            LOG_INFO("[Discord-Bot] Socket creation failed");
            return;
        }

        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(bind_host.c_str());
        address.sin_port = htons(bind_port);

        if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
            LOG_INFO("[Discord-Bot] Bind failed on %s:%d", bind_host.c_str(), bind_port);
            closesocket(server_fd);
#if defined(_WIN32)
            WSACleanup();
#endif
            return;
        }

        if (listen(server_fd, 3) < 0) {
            LOG_INFO("[Discord-Bot] Listen failed on %s:%d", bind_host.c_str(), bind_port);
            closesocket(server_fd);
#if defined(_WIN32)
            WSACleanup();
#endif
            return;
        }

        LOG_INFO("\n****************************\n"
            "Discord-Bot is connected. / ip[%s] / port[%d]\n"
            "****************************\n",
            bind_host.c_str(), bind_port);

        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        char buffer[1024] = { 0 };

        while (true) {
            SOCKET client_fd = accept(server_fd, (sockaddr*)&client_addr, &addrlen);
            if (client_fd == INVALID_SOCKET) continue;

            memset(buffer, 0, sizeof(buffer));
#if defined(_WIN32)
            int len = recv(client_fd, buffer, static_cast<int>(sizeof(buffer) - 1), 0);
            if (len == SOCKET_ERROR) len = -1;
#else
            ssize_t len = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
#endif
            if (len <= 0) {
                closesocket(client_fd);
                continue;
            }

            std::string cmd(buffer, len);
            LOG_INFO("[Discord-Bot] Received: %s", cmd.c_str());
            HandleCommand(cmd);

            closesocket(client_fd);
        }

        closesocket(server_fd);

#if defined(_WIN32)
        WSACleanup();
#endif
        }).detach();
}
