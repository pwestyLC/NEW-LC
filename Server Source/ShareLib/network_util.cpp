#include <string>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#else
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#endif

static bool isLoopbackIp(const std::string& ip)
{
    return ip == "127.0.0.1" || ip == "::1";
}

bool getLocalIp(std::string& out, bool preferIPv4 = true)
{
    out.clear();

#if defined(_WIN32)
    // Winsock must be initialized for inet_ntop, etc.
    WSADATA wsa{};
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return false;

    // GetAdaptersAddresses is the modern way to enumerate NICs.
    ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER;
    ULONG family = AF_UNSPEC; // IPv4 + IPv6

    ULONG bufLen = 0;
    if (GetAdaptersAddresses(family, flags, nullptr, nullptr, &bufLen) != ERROR_BUFFER_OVERFLOW)
    {
        WSACleanup();
        return false;
    }

    auto* addrs = (IP_ADAPTER_ADDRESSES*)malloc(bufLen);
    if (!addrs)
    {
        WSACleanup();
        return false;
    }

    DWORD rc = GetAdaptersAddresses(family, flags, nullptr, addrs, &bufLen);
    if (rc != NO_ERROR)
    {
        free(addrs);
        WSACleanup();
        return false;
    }

    auto pickFromFamily = [&](int wantFamily) -> bool {
        char ipbuf[INET6_ADDRSTRLEN];

        for (auto* a = addrs; a; a = a->Next)
        {
            // Only consider interfaces that are "up"
            if (a->OperStatus != IfOperStatusUp)
                continue;

            // Skip loopback adapters
            if (a->IfType == IF_TYPE_SOFTWARE_LOOPBACK)
                continue;

            for (auto* ua = a->FirstUnicastAddress; ua; ua = ua->Next)
            {
                if (!ua->Address.lpSockaddr)
                    continue;

                int fam = ua->Address.lpSockaddr->sa_family;
                if (fam != wantFamily)
                    continue;

                void* src = nullptr;
                if (fam == AF_INET)
                    src = &((sockaddr_in*)ua->Address.lpSockaddr)->sin_addr;
                else if (fam == AF_INET6)
                    src = &((sockaddr_in6*)ua->Address.lpSockaddr)->sin6_addr;

                if (!src)
                    continue;

                if (!inet_ntop(fam, src, ipbuf, sizeof(ipbuf)))
                    continue;

                std::string ip = ipbuf;
                if (isLoopbackIp(ip))
                    continue;

                out = ip;
                return true;
            }
        }
        return false;
        };

    bool ok = false;
    if (preferIPv4)
        ok = pickFromFamily(AF_INET) || pickFromFamily(AF_INET6);
    else
        ok = pickFromFamily(AF_INET6) || pickFromFamily(AF_INET);

    free(addrs);
    WSACleanup();
    return ok;

#else
    // Linux / CentOS 9+:
    ifaddrs* ifaddr = nullptr;
    if (getifaddrs(&ifaddr) != 0 || !ifaddr)
        return false;

    auto pickFromFamily = [&](int wantFamily) -> bool {
        char ipbuf[INET6_ADDRSTRLEN];

        for (ifaddrs* ifa = ifaddr; ifa; ifa = ifa->ifa_next)
        {
            if (!ifa->ifa_addr)
                continue;

            // Must be up and running
            unsigned int fl = (unsigned int)ifa->ifa_flags;
            if ((fl & IFF_UP) == 0)
                continue;

            // Skip loopback interfaces
            if (fl & IFF_LOOPBACK)
                continue;

            int fam = ifa->ifa_addr->sa_family;
            if (fam != wantFamily)
                continue;

            void* src = nullptr;
            if (fam == AF_INET)
                src = &((sockaddr_in*)ifa->ifa_addr)->sin_addr;
            else if (fam == AF_INET6)
                src = &((sockaddr_in6*)ifa->ifa_addr)->sin6_addr;

            if (!src)
                continue;

            if (!inet_ntop(fam, src, ipbuf, sizeof(ipbuf)))
                continue;

            std::string ip = ipbuf;
            if (isLoopbackIp(ip))
                continue;

            out = ip;
            return true;
        }
        return false;
        };

    bool ok = false;
    if (preferIPv4)
        ok = pickFromFamily(AF_INET) || pickFromFamily(AF_INET6);
    else
        ok = pickFromFamily(AF_INET6) || pickFromFamily(AF_INET);

    freeifaddrs(ifaddr);
    return ok;
#endif
}
