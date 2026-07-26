#include "stdh.h"

#include <Engine/Base/Console.h>
#include <Engine/Base/CTString.h>
#include <Engine/Base/ErrorReporting.h>
#include <Engine/Base/ErrorTable.h>
#include <Engine/Base/Synchronization.h>
#include <Engine/Base/Translation.h>
#include <Engine/Base/MemoryTracking.h>

#include <Engine/Network/ClientInterface.h>
#include <Engine/Network/CommunicationInterface.h>
#include <Engine/Network/CPacket.h>
//#include <Engine/Network/GameSpy.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Network/Server.h>

//0105
#include <Engine//Network/tcpipconnection.h>
//#include <Engine//Network/Inputbuffer.h> 
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIMessageBox.h>
#include <vector>
#include <Engine/GameState.h>
#include <Engine/GameStageManager/StageMgr.h>
#include <Engine/Loading.h>

#pragma comment(lib, "ws2_32.lib")




// GET MAC ADDRESS
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#pragma comment(lib, "wbemuuid.lib")
// GET MAC ADDRESS

#define SERVER_LOCAL_CLIENT     0
// ������ ���� ����
#define MAX_LOGINSERVER			(5)


#define USER_NUM_FULL		1000
#define USER_NUM_BUSY		300

extern INDEX net_iPort;
extern CTString net_strLocalHost;
extern INDEX net_bLookupHostNames;
extern INDEX net_bReportICMPErrors;
extern FLOAT net_fDropPackets;
extern FLOAT net_tmConnectionTimeout;
extern INDEX net_bReportPackets;

#ifdef EUROUPEAN_SERVER_LOGIN
extern INDEX g_iConnectEuroupean;
#endif

extern SOCKET g_hSocket;
extern INDEX	g_iCountry;

static struct ErrorCode ErrorCodes[] = {
	ERRORCODE(WSAEINTR          , "WSAEINTR"),
	ERRORCODE(WSAEBADF          , "WSAEBADF"),
	ERRORCODE(WSAEACCES         , "WSAEACCES"),
	ERRORCODE(WSAEFAULT         , "WSAEFAULT"),
	ERRORCODE(WSAEINVAL         , "WSAEINVAL"),
	ERRORCODE(WSAEMFILE         , "WSAEMFILE"),
	ERRORCODE(WSAEWOULDBLOCK    , "WSAEWOULDBLOCK"),
	ERRORCODE(WSAEINPROGRESS    , "WSAEINPROGRESS"),
	ERRORCODE(WSAEALREADY       , "WSAEALREADY"),
	ERRORCODE(WSAENOTSOCK       , "WSAENOTSOCK"),
	ERRORCODE(WSAEDESTADDRREQ   , "WSAEDESTADDRREQ"),
	ERRORCODE(WSAEMSGSIZE       , "WSAEMSGSIZE"),
	ERRORCODE(WSAEPROTOTYPE     , "WSAEPROTOTYPE"),
	ERRORCODE(WSAENOPROTOOPT    , "WSAENOPROTOOPT"),
	ERRORCODE(WSAEPROTONOSUPPORT, "WSAEPROTONOSUPPORT"),
	ERRORCODE(WSAESOCKTNOSUPPORT, "WSAESOCKTNOSUPPORT"),
	ERRORCODE(WSAEOPNOTSUPP     , "WSAEOPNOTSUPP"),
	ERRORCODE(WSAEPFNOSUPPORT   , "WSAEPFNOSUPPORT"),
	ERRORCODE(WSAEAFNOSUPPORT   , "WSAEAFNOSUPPORT"),
	ERRORCODE(WSAEADDRINUSE     , "WSAEADDRINUSE"),
	ERRORCODE(WSAEADDRNOTAVAIL  , "WSAEADDRNOTAVAIL"),
	ERRORCODE(WSAENETDOWN       , "WSAENETDOWN"),
	ERRORCODE(WSAENETUNREACH    , "WSAENETUNREACH"),
	ERRORCODE(WSAENETRESET      , "WSAENETRESET"),
	ERRORCODE(WSAECONNABORTED   , "WSAECONNABORTED"),
	ERRORCODE(WSAECONNRESET     , "WSAECONNRESET"),
	ERRORCODE(WSAENOBUFS        , "WSAENOBUFS"),
	ERRORCODE(WSAEISCONN        , "WSAEISCONN"),
	ERRORCODE(WSAENOTCONN       , "WSAENOTCONN"),
	ERRORCODE(WSAESHUTDOWN      , "WSAESHUTDOWN"),
	ERRORCODE(WSAETOOMANYREFS   , "WSAETOOMANYREFS"),
	ERRORCODE(WSAETIMEDOUT      , "WSAETIMEDOUT"),
	ERRORCODE(WSAECONNREFUSED   , "WSAECONNREFUSED"),
	ERRORCODE(WSAELOOP          , "WSAELOOP"),
	ERRORCODE(WSAENAMETOOLONG   , "WSAENAMETOOLONG"),
	ERRORCODE(WSAEHOSTDOWN      , "WSAEHOSTDOWN"),
	ERRORCODE(WSAEHOSTUNREACH   , "WSAEHOSTUNREACH"),
	ERRORCODE(WSASYSNOTREADY    , "WSASYSNOTREADY"),
	ERRORCODE(WSAVERNOTSUPPORTED, "WSAVERNOTSUPPORTED"),
	ERRORCODE(WSANOTINITIALISED , "WSANOTINITIALISED"),
	ERRORCODE(WSAEDISCON        , "WSAEDISCON"),
	ERRORCODE(WSAHOST_NOT_FOUND , "WSAHOST_NOT_FOUND"),
	ERRORCODE(WSATRY_AGAIN      , "WSATRY_AGAIN"),
	ERRORCODE(WSANO_RECOVERY    , "WSANO_RECOVERY"),
	ERRORCODE(WSANO_DATA        , "WSANO_DATA"),
};

struct LoginServer
{
	char	szName[100];
	char	szAddress[100];
	char	szPort[100];
	char	szFullUsers[50];
	char	szBusyUsers[50];
};

static struct ErrorTable SocketErrors = ERRORTABLE(ErrorCodes);

//structures used to emulate bandwidth and latency parameters - shared by all client interfaces
CPacketBufferStats _pbsSend;
CPacketBufferStats _pbsRecv;

ULONG				cm_ulLocalHost;			// configured local host address
CTString			cm_strAddress;			// local address
CTString			cm_strName;			// local address
unsigned char		cm_chSB1	= 0;
unsigned char		cm_chSB2	= 0;
unsigned char		cm_chSB3	= 0;
unsigned char		cm_chSB4	= 0;

CTCriticalSection cm_csComm;  // critical section for access to communication data

BOOL cm_bNetworkInitialized;

// index 0 is the server's local client, this is an array used by server only
CClientInterface cm_aciClients[SERVER_CLIENTS];

// Broadcast interface - i.e. interface for 'nonconnected' communication
CClientInterface cm_ciBroadcast;

// this is used by client only
CClientInterface cm_ciLocalClient;

// global communication interface object (there is only one for the entire engine)
CCommunicationInterface _cmiComm;

//0105 //0202
SOCKET client_socket;

int client_cnt;

//CInputBuffer m_inbuf;

/*
*
*	Two helper functions - conversion from IP to words
*
*/

// convert address to a printable string
CTString AddressToString(ULONG ulHost)
{
  ULONG ulHostNet = htonl(ulHost);


  // initially not converted
  struct hostent *hostentry = NULL;

  // if DNS lookup is allowed
  if (net_bLookupHostNames) {
    // lookup the host
	  hostentry = gethostbyaddr ((char *)&ulHostNet, sizeof(ulHostNet), AF_INET);
  }

  // if DNS lookup succeeded
	if (hostentry!=NULL) {
    // return its ascii name
    return (char *)hostentry->h_name;
  // if DNS lookup failed
  } else {
    // just convert to dotted number format
    return inet_ntoa((const in_addr &)ulHostNet);
  }
};

// convert string address to a number
ULONG StringToAddress(const CTString &strAddress)
{

  // first try to convert numeric address
  ULONG ulAddress = ntohl(inet_addr(strAddress));
  // if not a valid numeric address
  if (ulAddress==INADDR_NONE) {
    // lookup the host
    HOSTENT *phe = gethostbyname(strAddress);
    // if succeeded
    if (phe!=NULL) {
      // get that address
      ulAddress = ntohl(*(ULONG*)phe->h_addr_list[0]);
    }
  }

  // return what we got
  return ulAddress;
};



CCommunicationInterface::CCommunicationInterface(void)
{
  TRACKMEM(Mem,"Network");
  cm_csComm.cs_iIndex = -1;
  CTSingleLock slComm(&cm_csComm, TRUE);
 
  cci_bInitialized = FALSE;
  cci_bWinSockOpen = FALSE;

  cci_bServerInitialized = FALSE;
  cci_bClientInitialized = FALSE;
  cm_ciLocalClient.ci_bClientLocal = FALSE;

  cci_hSocket=INVALID_SOCKET;

  //0105
  m_bTcpIp =TRUE; //g_bTcp;//TRUE;//
	//0202
  client_socket = INVALID_SOCKET;
	/*
  for(int i=0;i<10;i++)
  {
	  client_socket[i] = INVALID_SOCKET;
  }
	*/
  client_cnt = 0;
};


// initialize
void CCommunicationInterface::Init(void) 
{
	CTSingleLock slComm(&cm_csComm, TRUE);
	
	cci_bWinSockOpen = FALSE;
	cci_bInitialized = TRUE;
	
// ������ ���� ����
	cci_szAddr[0]			= 0;
	cci_iPort				= -1;
	cci_iSelectedServerNum	= -1;
	cci_iFullUsers			= 0;
	cci_iBusyUsers			= 0;
// ������ ���� ��
	
	// mark as initialized
	cm_bNetworkInitialized = FALSE;
	
	cci_pbMasterInput.Clear();
	cci_pbMasterOutput.Clear();
	
	cci_bInitUpdateMasterBuffer = TRUE; //0616 updatemasterbuufers()�� �ʱ�ȭ�Ҽ� �ְ� �Ѵ�..

};

// close
void CCommunicationInterface::Close(void) 
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(cci_bInitialized);
  if(cci_bClientInitialized){    
    Client_Close();
  }
  if(cci_bServerInitialized){
    Server_Close();
  };


  // mark as closed
  cm_bNetworkInitialized = FALSE;
  cci_bInitialized = FALSE;
	cm_ciLocalClient.ci_bClientLocal = FALSE;

	cci_pbMasterInput.Clear();
	cci_pbMasterOutput.Clear();
};

void CCommunicationInterface::InitWinsock(void)
{
	if (cci_bWinSockOpen) 
	{
    return;
  }

  // start winsock
  WSADATA	winsockdata;
  WORD wVersionRequested;
  wVersionRequested = MAKEWORD(2, 2);
  int iResult = WSAStartup(wVersionRequested, &winsockdata);
  // if winsock open ok
	if (iResult==0) 
	{
    // remember that
    cci_bWinSockOpen = TRUE;
    CPrintF(TRANS("  winsock opened ok\n"));
  }
	else
	{
		int iResult = WSACleanup();
		ASSERT(iResult==0);
	}
};

void CCommunicationInterface::EndWinsock(void)
{
	if (!cci_bWinSockOpen) 
	{
    return;
  }

  int iResult = WSACleanup();
  ASSERT(iResult==0);
  cci_bWinSockOpen = FALSE;
};

//������ ���� ���� �ý��� ���콺 �۾�	09.09
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CCommunicationInterface::Disconnect(void)
{
	if (cci_hSocket != INVALID_SOCKET) 
	{
		closesocket(cci_hSocket);
		cci_bWinSockOpen	= FALSE;
		cci_bSocketOpen		= FALSE;
		cci_hSocket			= INVALID_SOCKET;
		g_hSocket			= cci_hSocket;
		cci_bWinSockOpen	= FALSE;
		cm_ciBroadcast.Clear();
	}
	cci_pbMasterInput.Clear();
	cci_pbMasterOutput.Clear();	
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : strIP - 
//			ulPort - 
//-----------------------------------------------------------------------------
void CCommunicationInterface::Reconnect(CTString strIP, ULONG ulPort)
{
	//if(cci_bWinSockOpen)
	Disconnect();

	CreateSocket_t();
	InitWinsock();

	_tcpip.ConnectToServer(strIP.str_String, ulPort);
	cci_bWinSockOpen	= TRUE;
	cci_bSocketOpen		= TRUE;
	cci_hSocket			= _tcpip.Socket;
}
//������ ���� �� �ý��� ���콺 �۾�		09.09


// prepares the comm interface for use - MUST be invoked before any data can be sent/received
BOOL CCommunicationInterface::PrepareForUse(BOOL bUseNetwork, BOOL bClient, BOOL bTcpIp)
{
	// clear the network conditions emulation data
	_pbsSend.Clear();
	_pbsRecv.Clear();
	
	// if the network is already initialized, shut it down before proceeding
	if (cm_bNetworkInitialized) 
	{
		// ������ �ݴ� �κ�.
		Unprepare();
	}
	
	// make sure winsock is off (could be on if enumeration was triggered)
	//#if _GAMESPY
	//	GameSpy_EnumCancel();
	//#endif
	EndWinsock();
	
	if (bUseNetwork) 
	{
		CPrintF(TRANS("Initializing TCP/IP...\n"));
		if (bClient && bTcpIp) 
		{						// by seo-40225
			CPrintF(TRANS("  opening as mmo client\n"));
			m_bTcpIp = TRUE;
		} 
		else if (bClient && !bTcpIp) 
		{
			CPrintF(TRANS("  opening as client\n"));
		} 
		else if (!bClient && bTcpIp) 
		{
			CPrintF(TRANS("  opening as mmo test server\n"));
			_pNetwork->IsTcpServer = TRUE;
			m_bTcpIp = TRUE;
		} 
		else 
		{
			CPrintF(TRANS("  opening as server\n"));
			_pNetwork->IsTcpServer = FALSE;
		}
		
		// make sure winsock is on
		InitWinsock();
		
		// no address by default
		cm_ulLocalHost = 0;
		// if there is a desired local address
		if (net_strLocalHost!="") 
		{
			// ����μ��� ���̴� net_strLocalHost�� ���̴� ������ �ƴ� �Ͱ���. by seo 40225
			CPrintF(TRANS("  user forced local address: %s\n"), (const char*)net_strLocalHost);
			// use that address
			cm_strName = net_strLocalHost;
			cm_ulLocalHost = StringToAddress(cm_strName);
			// if invalid
			if (cm_ulLocalHost==0 || cm_ulLocalHost==-1) 
			{
				cm_ulLocalHost=0;
				// report it
				CPrintF(TRANS("  requested local address is invalid\n"));
			}
		}
		
		// if no valid desired local address
		CPrintF(TRANS("  getting local addresses\n"));

		// get default
		char hostname[256];
		gethostname(hostname, sizeof(hostname)-1);
		cm_strName = hostname;
		// lookup the host
		HOSTENT *phe = gethostbyname(cm_strName);
		
		GetMAC(cci_iMac);
		

		// if succeeded
		if (phe!=NULL) 
		{
			// get the addresses
			cm_strAddress = "";
			for(INDEX i=0; phe->h_addr_list[i]!=NULL; i++) 
			{
				if (i>0)
				{
					cm_strAddress += ", ";
				}
				cm_strAddress	+= inet_ntoa(*(const in_addr *)phe->h_addr_list[i]);
				cm_chSB1		= ((const in_addr *)phe->h_addr_list[i])->S_un.S_un_b.s_b1;
				cm_chSB2		= ((const in_addr *)phe->h_addr_list[i])->S_un.S_un_b.s_b2;
				cm_chSB3		= ((const in_addr *)phe->h_addr_list[i])->S_un.S_un_b.s_b3;
				cm_chSB4		= ((const in_addr *)phe->h_addr_list[i])->S_un.S_un_b.s_b4;
			}
		}
		
		CPrintF(TRANS("  local addresses: %s (%s)\n"), cm_strName, cm_strAddress);
		CPrintF(TRANS("  port: %d\n"), net_iPort);
		
		// try to open master UDP socket
		try 
		{
			// ������ �����ϴ� �κ�.
			OpenSocket_t(cm_ulLocalHost, bClient?0:net_iPort);
			cci_pbMasterInput.pb_ppbsStats = NULL;
			cci_pbMasterOutput.pb_ppbsStats = NULL;
			cm_ciBroadcast.SetLocal(NULL);
		} 
		catch (char *strError) 
		{
			CPrintF(TRANS("  cannot open UDP socket: %s\n"), strError);
			return FALSE;
		}
	}
	
	cm_bNetworkInitialized = cci_bWinSockOpen;
	return TRUE;
};

// shut down the communication interface
void CCommunicationInterface::Unprepare(void)
{
  // close winsock
	if (cci_bWinSockOpen) 
	{
		// if socket is open
		if (cci_hSocket != INVALID_SOCKET) 
		{
			// close it
			closesocket(cci_hSocket);
			cci_hSocket = INVALID_SOCKET;
			g_hSocket	= cci_hSocket;
		}
		
		cm_ciBroadcast.Clear();
		EndWinsock();
		cci_bBound=FALSE;
	}
	
	cci_pbMasterInput.Clear();
	cci_pbMasterOutput.Clear();
	
	cm_bNetworkInitialized = cci_bWinSockOpen;
};

BOOL CCommunicationInterface::IsNetworkEnabled(void)
{
	return cm_bNetworkInitialized;
};

// get address of local machine
void CCommunicationInterface::GetHostName(CTString &strName, CTString &strAddress)
{
	strName		= cm_strName;
	strAddress	= cm_strAddress;
};

/*
*
*
*	Socket functions - creating, binding...
*
*
*/
// create an inet-family socket
void CCommunicationInterface::CreateSocket_t()
{
	//0105 1line �����
	//  ASSERT(cci_hSocket==INVALID_SOCKET);
	// open the socket
	//0105
	if(m_bTcpIp)
	{
		cci_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		cci_hSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
	cci_bBound = FALSE;
	if (cci_hSocket == INVALID_SOCKET) 
	{
		ThrowF_t(TRANS("Cannot open socket. %s"), (const char*)GetSocketError(WSAGetLastError()));
	}
};

// bind socket to the given address
void CCommunicationInterface::Bind_t(ULONG ulLocalHost, ULONG ulLocalPort)
{
	if (cci_hSocket==INVALID_SOCKET) {
		ASSERT(FALSE);
		return;
	}
	
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ulLocalPort);
	sin.sin_addr.s_addr = htonl(ulLocalHost);
	
	// bind socket to server address/port
	if (bind(cci_hSocket, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		ThrowF_t(TRANS("Cannot bind socket. %s"), (const char*)GetSocketError(WSAGetLastError()));
	}
	
	cci_bBound = TRUE;
};


// set socket to non-blocking mode
void CCommunicationInterface::SetNonBlocking_t(void)
{
	if (cci_hSocket==INVALID_SOCKET) {
		ASSERT(FALSE);
		return;
	}
	
	ULONG ulArgNonBlocking = 1;
	if (ioctlsocket(cci_hSocket, FIONBIO, &ulArgNonBlocking) == SOCKET_ERROR) {
		ThrowF_t(TRANS("Cannot set socket to non-blocking mode. %s"), 
			(const char*)GetSocketError(WSAGetLastError()));
	}
	ULONG ulArgBroadcast = 1;
	if (setsockopt(cci_hSocket, SOL_SOCKET, SO_BROADCAST, (const char*)&ulArgBroadcast, sizeof(int) ) == SOCKET_ERROR) {
		ThrowF_t(TRANS("Cannot allow broadcast on a socket. %s"));
	}
	
};

// get generic socket error info string about last error
CTString CCommunicationInterface::GetSocketError(INDEX iError)
{
	CTString strError;
	strError.PrintF(TRANS("Socket %d, Error %d (%s)"),
		cci_hSocket, iError, ErrorDescription(&SocketErrors, iError));
	return strError;
};

BOOL CCommunicationInterface::CheckIPFilter()
{
	// ȸ�� ���ΰ� �ƴ϶�� IP ���͸�...
#if defined VER_TEST
	return FALSE;
#endif
	return TRUE;
}

BOOL CCommunicationInterface::IsValidIP()
{
	//-----------------------------------------------------------------
	BOOL bSatisfied = FALSE;

	hostent *Hostent = gethostbyname(cci_szAddr);
	if (Hostent != NULL)
	{
		// sl.dta�� �ִ� IP�� ����.
		for( INDEX i = 0; Hostent->h_addr_list[i] != NULL; ++i )
		{
			// (chSB1.chSB2.chSB3.chSB4)
			const unsigned char chSB1 = ((const in_addr *)Hostent->h_addr_list[i])->S_un.S_un_b.s_b1;
			const unsigned char chSB2 = ((const in_addr *)Hostent->h_addr_list[i])->S_un.S_un_b.s_b2;
			const unsigned char chSB3 = ((const in_addr *)Hostent->h_addr_list[i])->S_un.S_un_b.s_b3;
			const unsigned char chSB4 = ((const in_addr *)Hostent->h_addr_list[i])->S_un.S_un_b.s_b4;

			for( std::vector<sIPFilter>::iterator iter = m_vecIPFilter.begin(); iter != m_vecIPFilter.end(); ++iter )
			{
				// �ش��ϴ� ������ ��� IP ��ϵ�...
				if( g_iCountry == (*iter).iCountry )
				{
					// (chSB1.chSB2.chSB3.chSB4)
					const unsigned char chFilterSB1 = (*iter).chSB1;
					const unsigned char chFilterSB2 = (*iter).chSB2;
					const unsigned char chFilterSB3 = (*iter).chSB3;
					const unsigned char chFilterSB4 = (*iter).chSB4;

					// sl.dta�� �ִ� �����ǿ� �ϵ� �ڵ��Ǿ��ִ� IP�� �����ϴٸ�, ������ ������.
					if( chSB1 == chFilterSB1 && chSB2 == chFilterSB2 )
					{
						if( chFilterSB3 == (UCHAR)-1 || chFilterSB3 == chSB3 )
						{
							if( chFilterSB4 == (UCHAR)-1 || chFilterSB4 == chSB4)
							{
								// ���� ����
								bSatisfied = TRUE;
								break;
							}
						}
					}
				}
			}
		}
	}

	return bSatisfied;
}

// open an UDP socket at given port
void CCommunicationInterface::OpenSocket_t(ULONG ulLocalHost, ULONG ulLocalPort)
{
	// create the socket as UDP
	CreateSocket_t();
	
	// ������ ���۽ÿ�...
	if(m_bTcpIp && _pNetwork->IsTcpServer)
	{	 
		//	 SetNonBlocking_t(); 
		ULONG ulArgBroadcast = 1;
		
		int i = MAX_PACKET_SIZE;
		if(setsockopt(cci_hSocket,  SOL_SOCKET, SO_SNDBUF, (char *) &i, sizeof(i))== SOCKET_ERROR) {	
			int err = WSAGetLastError();
		}
		
		BOOL bl = 0;
		
		if(setsockopt(cci_hSocket, SOL_SOCKET, SO_LINGER, (char *) &bl, sizeof(BOOL))== SOCKET_ERROR) {	
			int err = WSAGetLastError();
		}
		
		Bind_t(ulLocalHost, ulLocalPort); 
		
		ULONG ulArgNonBlocking = 1;
		if (ioctlsocket(cci_hSocket, FIONBIO, &ulArgNonBlocking) == SOCKET_ERROR) 
		{
			ThrowF_t(TRANS("Cannot set socket to non-blocking mode. %s"), 
				(const char*)GetSocketError(WSAGetLastError()));
		}
		
		// ������ ���۽ÿ�.
		if(listen(cci_hSocket,57)== SOCKET_ERROR) 
		{			
			int err = WSAGetLastError();
		}
		
		cci_bBound = FALSE;
	}
	else if(m_bTcpIp)
	{
		LoginServer loginsvr[MAX_LOGINSERVER];
		memset(&loginsvr, 0, sizeof(LoginServer) * MAX_LOGINSERVER);

		int	ServerNum = ReadInfo(loginsvr);

#ifdef	VER_TEST
		{
			CUIManager::getSingleton()->setIPString(loginsvr[0].szAddress);
		}
#endif	// VER_TEST

		if (ServerNum <= 0)
			return;

		cci_iSelectedServerNum	= rand() % ServerNum;
		cci_iPort				= atoi(loginsvr[cci_iSelectedServerNum].szPort);
		cci_iBusyUsers			= atoi(loginsvr[cci_iSelectedServerNum].szBusyUsers);
		cci_iFullUsers			= atoi(loginsvr[cci_iSelectedServerNum].szFullUsers);

		if(cci_iBusyUsers <= 0)
		{
			cci_iBusyUsers = USER_NUM_BUSY+100;
		}

		if(cci_iFullUsers <= 0)
		{
			cci_iFullUsers = USER_NUM_FULL;
		}
		strcpy(cci_szAddr, loginsvr[cci_iSelectedServerNum].szAddress);


		//-------------------------------------------------------------------------------
		//					### ���� ���� �κ� ���� ###
		//
		// NOTE : sl.dta�� �տ� �� �ڸ��� vecIPFilter�� ���ִ� IP�� ���Ͽ�,
		// NOTE : ���ٸ� ������ ����Ѵ�.
		// NOTE : ����ؾ� �� IP�� �� �߰��ȴٸ� vecIPFilter�� �߰��ϰ�, 
		// NOTE : IP_FILTER�� üũ�Ұ�.
		// NOTE : ����!!! ȸ�� ���ο����� '���� ���� �κ� üũ'�� ���� ����. !!!
		//-------------------------------------------------------------------------------
		// FIXME : IP_FILTER�� CLIENT_FILTER�� �ߺ��Ǵ� �κ��� ����, ���� �Լ��� ���� �Ұ� ����.

		if (CheckIPFilter() == TRUE)
		{
			if (IsValidIP() == FALSE)
			{
				cci_iSelectedServerNum = -1;
				return;
			}
		}
		// ������ ������ �õ�.
		_tcpip.ConnectToServer(cci_szAddr, cci_iPort); //������ ������ִ� ��ǻ�� ������	

		cci_hSocket = _tcpip.Socket;
		g_hSocket	= cci_hSocket;
	}
	else
	{
		Bind_t(ulLocalHost, ulLocalPort); 	  
		// go non-blocking
		SetNonBlocking_t();
	}
	
	// mark as open
	cci_bSocketOpen = TRUE;
};

// get address of this host
void CCommunicationInterface::GetLocalAddress_t(ULONG &ulHost, ULONG &ulPort)
{
	ASSERT(cci_bBound);
	
	ulHost = 0;
	ulPort = 0;
	if (cci_hSocket==INVALID_SOCKET) 
	{
		ASSERT(FALSE);
		return;
	}
	
	// get socket local port and address
	sockaddr_in sin;
	int iSize = sizeof(sin);
	if (getsockname(cci_hSocket, (sockaddr*)&sin, &iSize) == SOCKET_ERROR) 
	{
		ThrowF_t(TRANS("Cannot get local address on socket. %s"), 
			(const char*)GetSocketError(WSAGetLastError()));
	}
	ulHost = ntohl(sin.sin_addr.S_un.S_addr);
	ulPort = ntohs(sin.sin_port);
}

// get address of the peer host connected to this socket
void CCommunicationInterface::GetRemoteAddress_t(ULONG &ulHost, ULONG &ulPort)
{
	ulHost = 0;
	ulPort = 0;
	if (cci_hSocket==INVALID_SOCKET) {
		ASSERT(FALSE);
		return;
	}
	
	// get socket local port
	sockaddr_in sin;
	int iSize = sizeof(sin);
	if (getpeername(cci_hSocket, (sockaddr*)&sin, &iSize) == SOCKET_ERROR) {
		ThrowF_t(TRANS("Cannot get remote address on socket. %s"), 
			(const char*)GetSocketError(WSAGetLastError()));
	}
	ulHost = ntohl(sin.sin_addr.S_un.S_addr);
	ulPort = ntohs(sin.sin_port);
}


/*
*  ---->>>>  BROADCAST INTERFACE   <<<<----
*/

// broadcast communication
void CCommunicationInterface::Broadcast_Send(const void *pvSend, SLONG slSendSize,CAddress &adrDestination)
{
	CTSingleLock slComm(&cm_csComm, TRUE);
	
	cm_ciBroadcast.ci_adrAddress.adr_ulAddress = adrDestination.adr_ulAddress;
	cm_ciBroadcast.ci_adrAddress.adr_uwPort = adrDestination.adr_uwPort;
	cm_ciBroadcast.ci_adrAddress.adr_uwID = adrDestination.adr_uwID;
	
	cm_ciBroadcast.Send(pvSend, slSendSize,FALSE);
}

BOOL CCommunicationInterface::Broadcast_Receive(void *pvReceive, SLONG &slReceiveSize,CAddress &adrAddress)
{
	CTSingleLock slComm(&cm_csComm, TRUE);
	return cm_ciBroadcast.ReceiveFrom(pvReceive, slReceiveSize,&adrAddress,FALSE);
}

//! ��ε�ĳ��Ʈ �ι��� ������Ʈ. �����û ó��.
// update the broadcast input buffer - handle any incoming connection requests
void CCommunicationInterface::Broadcast_Update_t() 
{
	CPacket* ppaConnectionRequest;
	BOOL bIsAlready;
	BOOL bFoundEmpty;
	ULONG iClient;
	UBYTE ubDummy=65;

	//! �ι��ۿ� �����û ��Ŷ�� ���Դٸ�,
	// while there is a connection request packet in the input buffer
	while ((ppaConnectionRequest = cm_ciBroadcast.ci_pbReliableInputBuffer.GetConnectRequestPacket()) != NULL) {
		// see if there is a client already connected at that address and port
		bIsAlready = FALSE;
		for (iClient=1;iClient<SERVER_CLIENTS;iClient++) 
		{
			//! �̹� �������ִ� ��巹�����,
			if (cm_aciClients[iClient].ci_adrAddress.adr_ulAddress == ppaConnectionRequest->pa_adrAddress.adr_ulAddress &&
					cm_aciClients[iClient].ci_adrAddress.adr_uwPort == ppaConnectionRequest->pa_adrAddress.adr_uwPort) {
		   //! �װ� ���ӽõ��ϴ� ������ ���̴� Ŭ�����Ѵ�.
          // if it is, this client probably failed to connect the last time, so clear it
          _pNetwork->ga_srvServer.HandleClientDisconected(iClient);
			}
		}
		// if the client is already connected then just ignore the packet - else, connect it
		// find an empty client structure
		bFoundEmpty = FALSE;
		for (iClient=1;iClient<SERVER_CLIENTS;iClient++) {
			//! ������� �ʴ� array�� ã�Ҵٸ�, �װ��� Ŭ���̾�Ʈ �ּҿ� ��Ʈ ����.
			if (cm_aciClients[iClient].ci_bUsed == FALSE) {
				bFoundEmpty = TRUE;
				//0105 ���⼭ Ŭ���̾�Ʈ �ּҿ� ��Ʈ�� �����Ѵ�.
				if(m_bTcpIp&& _pNetwork->IsTcpServer){//����
					int sockaddr_size = sizeof( SOCKADDR_IN );		
					SOCKADDR_IN clientsockaddr;	
					//0131	//0202				
					
					getpeername( client_socket, (LPSOCKADDR)&clientsockaddr, &sockaddr_size);
					
					
					cm_aciClients[iClient].ci_adrAddress.adr_ulAddress = ntohl(clientsockaddr.sin_addr.s_addr);
					cm_aciClients[iClient].ci_adrAddress.adr_uwPort = ntohs(clientsockaddr.sin_port);
					
				}else{
					// we have an empty slot, so fill it for the client
					cm_aciClients[iClient].ci_adrAddress.adr_ulAddress = ppaConnectionRequest->pa_adrAddress.adr_ulAddress;
					cm_aciClients[iClient].ci_adrAddress.adr_uwPort = ppaConnectionRequest->pa_adrAddress.adr_uwPort;
				}
				//! ID����. 
				// generate the ID
				UWORD uwID = _pTimer->GetHighPrecisionTimer().tv_llValue&0x0FFF;
				if (uwID==0 || uwID=='//') {
					uwID+=1;
				}										
				cm_aciClients[iClient].ci_adrAddress.adr_uwID = (uwID<<4)+iClient;

				// form the connection response packet
				ppaConnectionRequest->pa_adrAddress.adr_uwID = '//';
				ppaConnectionRequest->pa_uwReliable = UDP_PACKET_RELIABLE | UDP_PACKET_RELIABLE_HEAD | UDP_PACKET_RELIABLE_TAIL | UDP_PACKET_CONNECT_RESPONSE;
				//! Ŭ���̾�Ʈ�� �Ҵ�� ID�� �˷��ش�.
				// return it to the client
				ppaConnectionRequest->WriteToPacket(&(cm_aciClients[iClient].ci_adrAddress.adr_uwID),sizeof(cm_aciClients[iClient].ci_adrAddress.adr_uwID),ppaConnectionRequest->pa_uwReliable,cm_ciBroadcast.ci_ulSequence++,ppaConnectionRequest->pa_adrAddress.adr_uwID,sizeof(cm_aciClients[iClient].ci_adrAddress.adr_uwID));
				if (cm_ciBroadcast.ci_pbOutputBuffer.AppendPacket(*ppaConnectionRequest,TRUE,FALSE) == FALSE) {
					ASSERT (FALSE);
				}
				//! �� Ŭ���̾�Ʈ�� ���� ���Ǵ°Ŵ�.
				cm_aciClients[iClient].ci_bUsed = TRUE;
				//0131
				//				client_cnt++;

				return;
			}
		}

		// if none found
		if (!bFoundEmpty) {
			// error
			ThrowF_t(TRANS("Server: Cannot accept new clients, all slots used!\n"));
		}

	}

};


/*
*  ---->>>>  SERVER  <<<<----
*/

/*
*  Initialize server
*/
void CCommunicationInterface::Server_Init_t(void) 
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(cci_bInitialized);
  ASSERT(!cci_bServerInitialized);
	


  // for each client
  for(INDEX iClient=0; iClient<SERVER_CLIENTS; iClient++) {
    // clear its status
    cm_aciClients[iClient].Clear();
		cm_aciClients[iClient].ci_pbOutputBuffer.pb_ppbsStats = &_pbsSend;
		cm_aciClients[iClient].ci_pbInputBuffer.pb_ppbsStats = &_pbsRecv;
  }

	// mark the server's instance of the local client as such
	cm_aciClients[SERVER_LOCAL_CLIENT].ci_bClientLocal = TRUE;
	cm_aciClients[SERVER_LOCAL_CLIENT].ci_bUsed = TRUE;

	// prepare the client part of the local client 
	cm_ciLocalClient.Clear();
	cm_ciLocalClient.ci_bUsed = TRUE;
	cm_ciLocalClient.ci_bClientLocal = TRUE;
	cm_ciLocalClient.ci_pbOutputBuffer.pb_ppbsStats = &_pbsSend;
	cm_ciLocalClient.ci_pbInputBuffer.pb_ppbsStats = &_pbsRecv;



  // mark that the server was initialized
  cci_bServerInitialized = TRUE;
};

/*
*  Close server
*/
void CCommunicationInterface::Server_Close(void) 
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  // close all clients
  for (INDEX iClient=0; iClient<SERVER_CLIENTS; iClient++) {
    cm_aciClients[iClient].Clear();
  }

  // mark that the server is uninitialized
  cci_bServerInitialized = FALSE;
};

/*
*  Server clear client and prepare for new connection
*/
void CCommunicationInterface::Server_ClearClient(INDEX iClient)
{
  // synchronize access to communication data
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  cm_aciClients[iClient].Clear();
};

BOOL CCommunicationInterface::Server_IsClientLocal(INDEX iClient)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  return iClient==SERVER_LOCAL_CLIENT;
};

BOOL CCommunicationInterface::Server_IsClientUsed(INDEX iClient)
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  return cm_aciClients[iClient].ci_bUsed;
};

CTString CCommunicationInterface::Server_GetClientName(INDEX iClient)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);

  if (iClient==SERVER_LOCAL_CLIENT) {
    return TRANS("Local machine");
  }

  cm_aciClients[iClient].ci_strAddress = AddressToString(cm_aciClients[iClient].ci_adrAddress.adr_ulAddress);

  return cm_aciClients[iClient].ci_strAddress;
};


ULONG CCommunicationInterface::Server_GetClientPendingData(INDEX iClient)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  return cm_aciClients[iClient].GetPendingDataSize();
};

ULONG CCommunicationInterface::Server_GetMaxPendingData()
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ULONG ulMaxData = 0;
  ULONG ulData;
  for (INDEX iClient=0;iClient<SERVER_CLIENTS;iClient++) {
    ulData = cm_aciClients[iClient].GetPendingDataSize();
    if (ulData > ulMaxData) {
      ulMaxData = ulData;
    }
  }
  return ulMaxData;
};


ULONG CCommunicationInterface::Server_GetTotalPendingData()
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ULONG ulData = 0;
  for (INDEX iClient=0;iClient<SERVER_CLIENTS;iClient++) {
    ulData += cm_aciClients[iClient].GetPendingDataSize();
  }
  return ulData;
};

/*
*  Server Send/Receive Reliable
*/
void CCommunicationInterface::Server_Send_Reliable(INDEX iClient, const void *pvSend, SLONG slSendSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  cm_aciClients[iClient].Send(pvSend, slSendSize,TRUE);
  Server_Update();
};

BOOL CCommunicationInterface::Server_Receive_Reliable(INDEX iClient, void *pvReceive, SLONG &slReceiveSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  return cm_aciClients[iClient].Receive(pvReceive, slReceiveSize,TRUE);
};

/*
*  Server Send/Receive Unreliable
*/
void CCommunicationInterface::Server_Send_Unreliable(INDEX iClient, const void *pvSend, SLONG slSendSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  cm_aciClients[iClient].Send(pvSend, slSendSize,FALSE);
  Server_Update();
};

BOOL CCommunicationInterface::Server_Receive_Unreliable(INDEX iClient, void *pvReceive, SLONG &slReceiveSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  ASSERT(iClient>=0 && iClient<SERVER_CLIENTS);
  return cm_aciClients[iClient].Receive(pvReceive, slReceiveSize,FALSE);
};

//! ���� ������Ʈ
BOOL CCommunicationInterface::Server_Update()
{

	CTSingleLock slComm(&cm_csComm, TRUE);
	//	CPacket *ppaPacket;
	//	CPacket *ppaPacketCopy;
	CTimerValue tvNow = _pTimer->GetHighPrecisionTimer();
	//	INDEX iClient;
	
	//! ���� Ŭ���̾�Ʈ�� Ŭ���̾�Ʈ 0��° array�� ���۸� �±�ȯ �Ѵ�. input����<->out����
	// transfer packets for the local client
	if (cm_ciLocalClient.ci_bUsed && cm_ciLocalClient.ci_pciOther != NULL) {
		cm_ciLocalClient.ExchangeBuffers();
	};
	
	/* //0311 ����
	//! out���� ������Ʈ.
	cm_aciClients[0].UpdateOutputBuffers();
	
	//! ��Ŭ �÷��̰� �ƴ϶��,
	// if not just playing single player
	if (cci_bServerInitialized) {
		try {
			//! ��ε� ĳ��Ʈ ������Ʈ.
			Broadcast_Update_t();
		} catch (char *strError) {
			CPrintF(strError);
		}
		
		//! ��� Ŭ���̾�Ʈ�� ���Ͽ� out���ۿ��� ������ out���۷� ��Ŷ�� �����Ѵ�. ���� ����.
		// for each client transfer packets from the output buffer to the master output buffer
		for (iClient=1; iClient<SERVER_CLIENTS; iClient++) {
			CClientInterface &ci = cm_aciClients[iClient];
			//! �� Ŭ���̾�Ʈ�� ����Ǿ� ���� ������ skip
			// if not connected
			if (!ci.ci_bUsed) {
				// skip it
				continue;
			}
			//! out���� ������Ʈ.
			// update its buffers, if a reliable packet is overdue (has not been delivered too long)
			// disconnect the client			
			if (ci.UpdateOutputBuffers() != FALSE) {
				//! ���� �ƿ������� ù��°��Ŷ�� ������ �ð��� ��ٸ��� ��Ŷ�� �ִٸ�,??
				//!��Ŷ�� ������ �ð��̶�� ������ �ƿ����۷� �����Ѵ�.
				// transfer packets ready to be sent out to the master output buffer
				while (ci.ci_pbOutputBuffer.pb_ulNumOfPackets > 0) {
					ppaPacket = ci.ci_pbOutputBuffer.PeekFirstPacket();
					//! ���� �ð��̶��,
					if (ppaPacket->pa_tvSendWhen < tvNow) {
						ci.ci_pbOutputBuffer.RemoveFirstPacket(FALSE);
						//0105 ACK��Ŷ���� Ȯ�� ���� �ʱ�
						if(!(m_bTcpIp&& _pNetwork->IsTcpServer)){//����
							//! �����̾�� ��Ŷ�̶�� ��ũ��Ŷ ����.
							if (ppaPacket->pa_uwReliable & UDP_PACKET_RELIABLE) {
								ppaPacketCopy = CreatePacket();
								*ppaPacketCopy = *ppaPacket;
								if (ci.ci_pbWaitAckBuffer.AppendPacket(*ppaPacketCopy,FALSE,FALSE) == FALSE) {
									ASSERT(FALSE);
								}
							}
						}
						//! ������ out���ۿ� �ִ´�.
						if (cci_pbMasterOutput.AppendPacket(*ppaPacket,FALSE,FALSE) == FALSE){
							ASSERT(FALSE);
						}
					} else {
						break;
					}
				}
			} else {
				CPrintF(TRANS("Unable to deliver data to client '%s', disconnecting.\n"),AddressToString(cm_aciClients[iClient].ci_adrAddress.adr_ulAddress));
				Server_ClearClient(iClient);
				_pNetwork->ga_srvServer.HandleClientDisconected(iClient);
				
			}
		}
		
		// update broadcast output buffers
		// update its buffers
		cm_ciBroadcast.UpdateOutputBuffers();
		//! ��ε�ĳ��Ʈ �ƿ����ۿ� ��Ŷ�� �ִٸ�,
		// transfer packets ready to be sent out to the master output buffer
		while (cm_ciBroadcast.ci_pbOutputBuffer.pb_ulNumOfPackets > 0) {
			ppaPacket = cm_ciBroadcast.ci_pbOutputBuffer.PeekFirstPacket();
			//! ���� �ð��� �Ǿ��ٸ�, 
			if (ppaPacket->pa_tvSendWhen < tvNow) {
				cm_ciBroadcast.ci_pbOutputBuffer.RemoveFirstPacket(FALSE);
				if (cci_pbMasterOutput.AppendPacket(*ppaPacket,FALSE,FALSE) == FALSE) {
					ASSERT(FALSE);
				}
			} else {
				break;
			}
		}
	*/		
		// send/receive packets over the TCP/IP stack
		UpdateMasterBuffers();
	/* //0311 ����
		//! ������ in���ۿ� ��Ŷ�� ����ִٸ�,
		// dispatch all packets from the master input buffer to the clients' input buffers
		while (cci_pbMasterInput.pb_ulNumOfPackets > 0) {
			BOOL bClientFound;
			ppaPacket = cci_pbMasterInput.GetFirstPacket();
			bClientFound = FALSE;
			//! �����㰡 ��û�ϴ� ���Ʈĳ��Ʈ ��Ŷ�̶��,
			if (ppaPacket->pa_adrAddress.adr_uwID=='//' || ppaPacket->pa_adrAddress.adr_uwID==0) {
				if (cm_ciBroadcast.ci_pbInputBuffer.AppendPacket(*ppaPacket,FALSE,TRUE) == FALSE) {
					DeletePacket(ppaPacket);
				}
				bClientFound = TRUE;
			} else {
				for (iClient=0; iClient<SERVER_CLIENTS; iClient++) {
					//! �� Ŭ���̾�Ʈ ���̵� Ȯ��
					if (ppaPacket->pa_adrAddress.adr_uwID == cm_aciClients[iClient].ci_adrAddress.adr_uwID) {
						//! �ش� �ι��ۿ�  ��Ŷ �ֱ�.
						if (cm_aciClients[iClient].ci_pbInputBuffer.AppendPacket(*ppaPacket,FALSE,TRUE) == FALSE) {
							DeletePacket(ppaPacket);
						}
						bClientFound = TRUE;
						break;
					}
				}
			}
			if (!bClientFound) {
				// warn about possible attack
				extern INDEX net_bReportMiscErrors;
				if (net_bReportMiscErrors) {
					CPrintF(TRANS("WARNING: Invalid message from: %s\n"), AddressToString(ppaPacket->pa_adrAddress.adr_ulAddress));
				}
			}
		}
		//! ��� Ŭ���̾�Ʈ �ι��� ������Ʈ
		for (iClient=1; iClient<SERVER_CLIENTS; iClient++) {
			cm_aciClients[iClient].UpdateInputBuffers();
		}
		
		
	}
	*/	
	cm_aciClients[0].UpdateInputBuffers();
	//! ���� �ι��� ������Ʈ
	cm_ciLocalClient.UpdateInputBuffers();
	/* //0311 ����
	//! ��ε�ĳ��Ʈ �ι��� ������Ʈ
	cm_ciBroadcast.UpdateInputBuffersBroadcast();
	//! ��ε�ĳ��Ʈ ������Ʈ
	Broadcast_Update_t();
	*/	
	return TRUE;
};

/*
*  ---->>>>  CLIENT  <<<<----
*/

/*
*  Initialize client
*/
//!Ŭ���̾�Ʈ �ʱ�ȭ
void CCommunicationInterface::Client_Init_t(char* strServerName)
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(cci_bInitialized);
  ASSERT(!cci_bClientInitialized);

  // retrieve server address from server name
  ULONG ulServerAddress = StringToAddress(strServerName);
  // if lookup failed
  if (ulServerAddress==INADDR_NONE) {
    ThrowF_t(TRANS("Host '%s' not found!\n"), strServerName);
  }

  // call client init with server address
  Client_Init_t(ulServerAddress);


};

void CCommunicationInterface::Client_Init_t(ULONG ulServerAddress)
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(cci_bInitialized);
  ASSERT(!cci_bClientInitialized);
	//! Ŭ���̾�Ʈ �������̽� �ʱ�ȭ.out����,In���� state �ʱ�ȭ.
  cm_ciLocalClient.Clear();
	cm_ciLocalClient.ci_pbOutputBuffer.pb_ppbsStats = &_pbsSend;
	cm_ciLocalClient.ci_pbInputBuffer.pb_ppbsStats = &_pbsRecv;
	//! ������ �ƴ϶��(Ŭ���̾�Ʈ �ʱ�ȭ �ϰ� �Ѿ��..)
  // if this computer is not the server
  if (!cci_bServerInitialized) {
    // open with connecting to remote server
    cm_ciLocalClient.ci_bClientLocal= FALSE;
	//! ���� ���� ���� ���ӽ����� �޴´�.
    Client_OpenNet_t(ulServerAddress);

  // if this computer is server
  } else {
		//! ������� ���� Ŭ���̾�Ʈ ����.
    // open local client
    cm_ciLocalClient.ci_bClientLocal = TRUE;
    Client_OpenLocal();
  }
	//! Ŭ���̾�Ʈ �ʱ�ȭ �Ǿ���.
  cci_bClientInitialized = TRUE;
};

/*
*  Close client
*/
void CCommunicationInterface::Client_Close(void)
{
  CTSingleLock slComm(&cm_csComm, TRUE);

  ASSERT(cci_bInitialized);

	// dispatch remaining packets (keep trying for half a second - 10 attempts)
  for(TIME tmWait=0; tmWait<500;
    Sleep(NET_WAITMESSAGE_DELAY), tmWait+=NET_WAITMESSAGE_DELAY) {
    // if all packets are successfully sent, exit loop
		if  ((cm_ciLocalClient.ci_pbOutputBuffer.pb_ulNumOfPackets == 0) 
			&& (cm_ciLocalClient.ci_pbWaitAckBuffer.pb_ulNumOfPackets == 0)) {
				break;
			}
    if (Client_Update() == FALSE) {
			break;
		}
	}

  cm_ciLocalClient.Clear();

  cm_ciLocalClient.ci_bClientLocal= FALSE;
  cci_bClientInitialized = FALSE;
};


/*
*  Open client local
*/
//! �������� ���� ���� Ŭ���̾�Ʈ ����
void CCommunicationInterface::Client_OpenLocal(void)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  //! ������ 0��° Ŭ���̾�Ʈ ���̺��� ���� Ŭ���̾�Ʈ �������̽��� �����Ѵ�.
  CClientInterface &ci0 = cm_ciLocalClient;
  CClientInterface &ci1 = cm_aciClients[SERVER_LOCAL_CLIENT];
  //! ���� ���÷� ����.  
  ci0.ci_bUsed = TRUE;
  ci0.SetLocal(&ci1);
  ci1.ci_bUsed = TRUE;
  ci1.SetLocal(&ci0);
};


/*
*  Open client remote
*/
//! Ŭ���̾�Ʈ ����.
void CCommunicationInterface::Client_OpenNet_t(ULONG ulServerAddress)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
	CPacket* ppaInfoPacket;
	CPacket* ppaReadPacket;
	UBYTE ubDummy=65;
	UBYTE ubReliable;

  // check for reconnection
  static ULONG ulLastServerAddress = -1;
  BOOL bReconnecting = ulServerAddress == ulLastServerAddress;
  ulLastServerAddress = ulServerAddress;

  const INDEX iRefresh = 100; // (delay between retries in miliseconds)
  // determine connection timeout
  INDEX ctRetries = bReconnecting?(net_tmConnectionTimeout*1000/2/iRefresh):5;

  // start waiting for server's response
  if (ctRetries>1) {
    CallProgressHook_t(0.0f);
  }

	//!	���� ��û ��Ŷ�� �����.
	// form the connection request packet
	ppaInfoPacket = CreatePacket();
	ubReliable = UDP_PACKET_RELIABLE | UDP_PACKET_RELIABLE_HEAD | UDP_PACKET_RELIABLE_TAIL | UDP_PACKET_CONNECT_REQUEST;
	ppaInfoPacket->pa_adrAddress.adr_ulAddress = ulServerAddress;
	ppaInfoPacket->pa_adrAddress.adr_uwPort = net_iPort;
	ppaInfoPacket->pa_ubRetryNumber = 0;
	ppaInfoPacket->WriteToPacket(&ubDummy,1,ubReliable,cm_ciLocalClient.ci_ulSequence++,'//',1);
	//! �����û��Ŷ�� �ƿ����ۿ� �ִ´�.
	if (cm_ciLocalClient.ci_pbOutputBuffer.AppendPacket(*ppaInfoPacket,TRUE,FALSE) == FALSE){
    ASSERT(FALSE);
  }
	//! ���� �ּҿ� ��Ʈ ��ȣ�� Ŭ���̾�Ʈ �������̽��� ����
	// set client destination address to server address
	cm_ciLocalClient.ci_adrAddress.adr_ulAddress = ulServerAddress;
	cm_ciLocalClient.ci_adrAddress.adr_uwPort = net_iPort;
	
  // for each retry
	for(INDEX iRetry=0; iRetry<ctRetries; iRetry++) 
	{
	    //! ���۸� ������Ʈ �Ͽ� �ƿ����۾ȿ� �ִ� ���ӿ�û��Ŷ�� ������, ���ӽ��� ��Ŷ�� ��ٸ���.
		// send/receive and juggle the buffers
		if (Client_Update() == FALSE) 
		{
			break;
		}
		//! �����̾�� Input���ۿ� ��� ��Ŷ�� ���� �ִٸ�,
		// if there is something in the input buffer
		if (cm_ciLocalClient.ci_pbReliableInputBuffer.pb_ulNumOfPackets > 0) 
		{
			//! ù��Ŷ�� ���ͼ�
			ppaReadPacket = cm_ciLocalClient.ci_pbReliableInputBuffer.GetFirstPacket();
			//! �װ� ���ӽ��� ��Ŷ�̶�� 
			// and it is a connection confirmation
			if (ppaReadPacket->pa_uwReliable &  UDP_PACKET_CONNECT_RESPONSE) 
			{
				// the client has succedeed to connect, so read the uwID from the packet
				//! ������ ��Ŷ���� adr_uwID�� ��´�.
				cm_ciLocalClient.ci_adrAddress.adr_ulAddress = ulServerAddress;
				cm_ciLocalClient.ci_adrAddress.adr_uwPort = net_iPort;
				cm_ciLocalClient.ci_adrAddress.adr_uwID = *((UWORD*) (ppaReadPacket->pa_pubPacketData + MAX_HEADER_SIZE));
				cm_ciLocalClient.ci_bUsed = TRUE;
				cm_ciLocalClient.ci_bClientLocal = FALSE;
				cm_ciLocalClient.ci_pciOther = NULL;
				//! �����̾�� input���ۿ��� �� ��Ŷ�� �����.
				cm_ciLocalClient.ci_pbReliableInputBuffer.RemoveConnectResponsePackets();

				DeletePacket(ppaReadPacket);

				// finish waiting
				CallProgressHook_t(1.0f);		    
				return;
			}
		}

    Sleep(iRefresh);
    CallProgressHook_t(FLOAT(iRetry)/ctRetries);
	}
	
	cci_bBound = FALSE;
	ThrowF_t(TRANS("Client: Timeout receiving UDP port"));
};

/*
*  Clear local client
*/

void CCommunicationInterface::Client_Clear(void)
{
  // synchronize access to communication data
  CTSingleLock slComm(&cm_csComm, TRUE);

  cm_ciLocalClient.Clear();
};

/*
*  Client get status
*/
BOOL CCommunicationInterface::Client_IsConnected(void)
{
  // synchronize access to communication data
  CTSingleLock slComm(&cm_csComm, TRUE);

  return cm_ciLocalClient.ci_bUsed;
};

/*
*  Client Send/Receive Reliable
*/
void CCommunicationInterface::Client_Send_Reliable(const void *pvSend, SLONG slSendSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  //! output���ۿ� �ֱ�.
  cm_ciLocalClient.Send(pvSend, slSendSize,TRUE);
  //! �����̶�� ���� ������Ʈ.
  if (cci_bServerInitialized) {
    Server_Update();
  } else {
    Client_Update();
  }
};

BOOL CCommunicationInterface::Client_Receive_Reliable(void *pvReceive, SLONG &slReceiveSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  return cm_ciLocalClient.Receive(pvReceive, slReceiveSize,TRUE);
};

BOOL CCommunicationInterface::Client_Receive_Reliable(CTStream &strmReceive)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  return cm_ciLocalClient.Receive(strmReceive,TRUE);
};
//! ��Ŷ�� �����ִ� ���ۻ�����(slExpectedSize)�� ������ ���ۿ� �����ϴ� �����̾�� ��Ŷ�� ������(slReceivedSize)�� ����.
void CCommunicationInterface::Client_PeekSize_Reliable(SLONG &slExpectedSize,SLONG &slReceivedSize)
{
  slExpectedSize = cm_ciLocalClient.GetExpectedReliableSize();
  slReceivedSize = cm_ciLocalClient.GetCurrentReliableSize();
}

/*
*  Client Send/Receive Unreliable
*/
void CCommunicationInterface::Client_Send_Unreliable(const void *pvSend, SLONG slSendSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  cm_ciLocalClient.Send(pvSend, slSendSize,FALSE);

  if (cci_bServerInitialized) {
    Server_Update();
  } else {
    Client_Update();
  }
};

BOOL CCommunicationInterface::Client_Receive_Unreliable(void *pvReceive, SLONG &slReceiveSize)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  return cm_ciLocalClient.Receive(pvReceive, slReceiveSize,FALSE);
};

//0311 kwon �Լ� �߰�
void CCommunicationInterface::Client_Send_Unreliable_New(const void *pvSend, SLONG slSendSize, BOOL bLogin)
{
  CTSingleLock slComm(&cm_csComm, TRUE);
  cm_ciLocalClient.SendNew(pvSend, slSendSize);
  
  //0524 kwon
  if(!bLogin){
	  if (cci_bServerInitialized) {
		  Server_Update();
	  } else {
		  Client_Update();
	  }
  }
};

//0311 kwon �Լ��߰�. ���⼭ ������ input ���ۿ��� ��Ŷ �о�鿩 sessionstate���� ����Ѵ�.
BOOL CCommunicationInterface::Client_Receive_Unreliable_New(void *pvReceive, SLONG &slReceiveSize, INDEX &index)
{
	CTSingleLock slComm(&cm_csComm, TRUE);
	
	ASSERT (slReceiveSize>0);
	ASSERT (pvReceive != NULL);
	
	
	CPacket* ppaPacket;
	UBYTE* pubData = (UBYTE*) pvReceive;
	SLONG slDummySize;
	UWORD uwReliable;
	
	// if there are no packets in the input buffer, return
	if (cci_pbMasterInput.pb_ulNumOfPackets == 0) {
		return FALSE;	
	} 
	ppaPacket = cci_pbMasterInput.PeekFirstPacket();

	// if the first packet in the input buffer is not unreliable
	if (!ppaPacket->IsUnreliable()) {
		return FALSE;
		// if there is no complete message ready
	} else if (cci_pbMasterInput.CheckSequence(slDummySize,FALSE) == FALSE) {
		return FALSE;
		// if the ready message is longer than the expected size
	} else if ( ppaPacket->pa_slTransferSize > slReceiveSize) {
		return FALSE;
		// if everything is ok, read the packet data, and kill the packet
	} else {
		
		slReceiveSize = 0;
		do {
			ppaPacket = cci_pbMasterInput.GetFirstPacket();
			uwReliable = ppaPacket->pa_uwReliable;
			slDummySize = ppaPacket->pa_slSize - MAX_HEADER_SIZE;
			ppaPacket->ReadFromPacket(pubData,slDummySize);
			pubData += slDummySize;
			slReceiveSize += slDummySize;
			//0322 kwon
			index = ppaPacket->pa_adrAddress.adr_uwID;
			DeletePacket(ppaPacket);
		} while (!(uwReliable & UDP_PACKET_UNRELIABLE_TAIL));
		
		return TRUE;
	}
	
	return FALSE;
};

BOOL CCommunicationInterface::Client_Update(void)
{
	CTSingleLock slComm(&cm_csComm, TRUE);
	CPacket *ppaPacket;
	CPacket *ppaPacketCopy;
	CTimerValue tvNow = _pTimer->GetHighPrecisionTimer();


    //! Ŭ���̾�Ʈ�� �ƿ����� ����
	// update local client's output buffers
	if (cm_ciLocalClient.UpdateOutputBuffers() == FALSE) {
		return FALSE;
	}

	// if not playing on the server (i.e. connected to a remote server)
	if (!cci_bServerInitialized) {
		// put all pending packets in the master output buffer
		while (cm_ciLocalClient.ci_pbOutputBuffer.pb_ulNumOfPackets > 0) {
			ppaPacket = cm_ciLocalClient.ci_pbOutputBuffer.PeekFirstPacket();
			//! pa_tvSendWhen�� ��õ� ����
			if (ppaPacket->pa_tvSendWhen < tvNow) {
				//! �ٽ� ���� �ð��� �Ǿ��ٸ� �ƿ����ۿ��� �����,
				cm_ciLocalClient.ci_pbOutputBuffer.RemoveFirstPacket(FALSE);
				//! �����̾�� ��Ŷ�̶�� ��ũ���ۿ� ��Ŷ�� ������ ���´�.
				if (ppaPacket->pa_uwReliable & UDP_PACKET_RELIABLE) {
					ppaPacketCopy = CreatePacket();
					*ppaPacketCopy = *ppaPacket;
					if (cm_ciLocalClient.ci_pbWaitAckBuffer.AppendPacket(*ppaPacketCopy,FALSE,FALSE) == FALSE){
						ASSERT(FALSE);
					}
				}
				//! ��Ŷ�� �����;ƿ����ۿ� �ִ´�.
				if (cci_pbMasterOutput.AppendPacket(*ppaPacket,FALSE,FALSE) == FALSE){
					ASSERT(FALSE);
				}

			} else {
				break;
			}
		}

		//! ��ε�ĳ��Ʈ Ŭ���̾�Ʈ�� �ƿ����� ����
		// update broadcast output buffers
		// update its buffers
		cm_ciBroadcast.UpdateOutputBuffers();
        //! ��ε�ĳ��Ʈ Ŭ���̾�Ʈ�� �ƿ����ۿ� �����;ƿ����۷� ���� ��Ŷ�� �ִٸ� 
		// transfer packets ready to be sent out to the master output buffer
		while (cm_ciBroadcast.ci_pbOutputBuffer.pb_ulNumOfPackets > 0) {
			ppaPacket = cm_ciBroadcast.ci_pbOutputBuffer.PeekFirstPacket();
			//! �����ð��� �Ǿ��ٸ� �����;ƿ����۷� ������.
			if (ppaPacket->pa_tvSendWhen < tvNow) {
				cm_ciBroadcast.ci_pbOutputBuffer.RemoveFirstPacket(FALSE);
				if (cci_pbMasterOutput.AppendPacket(*ppaPacket,FALSE,FALSE) == FALSE){
					ASSERT(FALSE);
				}
			} else {
				break;
			}
		}

		//! �����͹��� ����
		// send/receive packets over the TCP/IP stack
		UpdateMasterBuffers();

		//������ input ���ۿ� ��Ŷ�� �ִٸ� 
		// dispatch all packets from the master input buffer to the clients' input buffers
		while (cci_pbMasterInput.pb_ulNumOfPackets > 0) {
			BOOL bClientFound;
			ppaPacket = cci_pbMasterInput.GetFirstPacket();
			bClientFound = FALSE;
			
			//! ��Ŷ�ּҰ� ��ε�ĳ��Ʈ�̰� �𸱶���� �����̾��ٸ�, �װ��� ��ε�ĳ��Ʈ input���ۿ� �ִ´�.
			// if the packet address is broadcast and it's an unreliable transfer, put it in the broadcast buffer
			if ((ppaPacket->pa_adrAddress.adr_uwID=='//' || ppaPacket->pa_adrAddress.adr_uwID==0) && 
				ppaPacket->IsUnreliable()) {
				if (cm_ciBroadcast.ci_pbInputBuffer.AppendPacket(*ppaPacket,FALSE,TRUE) == FALSE) {
					DeletePacket(ppaPacket);
				}
				bClientFound = TRUE;
				//! ����Ŷ�� adr_uwID�� �� Ŭ���̾�Ʈ�� adr_uwID�� ��ġ�Ѵٸ� Ŭ���̾�Ʈ Input���ۿ� �ִ´�.
				// if the packet is for this client, accept it
			} else if ((ppaPacket->pa_adrAddress.adr_uwID == cm_ciLocalClient.ci_adrAddress.adr_uwID) || 
				ppaPacket->pa_adrAddress.adr_uwID=='//' || ppaPacket->pa_adrAddress.adr_uwID==0) { 
				
				if (cm_ciLocalClient.ci_pbInputBuffer.AppendPacket(*ppaPacket,FALSE,TRUE) == FALSE) {
					DeletePacket(ppaPacket);
				}
				bClientFound = TRUE;			
			}

			if (!bClientFound) {
				// warn about possible attack
				extern INDEX net_bReportMiscErrors;
				if (net_bReportMiscErrors) {
					CPrintF(TRANS("WARNING: Invalid message from: %s\n"), AddressToString(ppaPacket->pa_adrAddress.adr_ulAddress));
				}
			}
		}

	}
    //! Ŭ���̾�Ʈ input���۸� ����.��ε�ĳ��Ʈ input���� ����
	cm_ciLocalClient.UpdateInputBuffers();
	cm_ciBroadcast.UpdateInputBuffersBroadcast();

	return TRUE;
};

// update master UDP socket and route its messages
void CCommunicationInterface::UpdateMasterBuffers() 
{
	//������ ���� ���� �α��� ó�� �۾�	07.20
	// NOTE : �α��� �� ��Ʈ��ũ �޼����� ������ �ϰԵǸ� ���� �ʴ´�!!!
	// NOTE : Send, Recv�� ���� �ʱ� ������...
	extern BOOL _bWorldEditorApp;
	extern BOOL _bUseSocket;
	extern BOOL _bLoginProcess;
	//if((_bLoginProcess && !_bUseSocket) || _bWorldEditorApp)
	//{
	//	return;
	//}
	//������ ���� �� �α��� ó�� �۾�		07.20
	UBYTE aub[MAX_PACKET_SIZE];
	CAddress adrIncomingAddress;
	SOCKADDR_IN sa;
	int size = sizeof(sa);
	SLONG slSizeReceived;
	SLONG slSizeSent;
	BOOL bSomethingDone;
	CPacket* ppaNewPacket;
	CTimerValue tvNow;
	static TIME  tmLastBandwithRecorded;
	static ULONG ulBandwidth;
	static BOOL  bInit = TRUE;
	
	if ( cci_bInitUpdateMasterBuffer ) 
	{
		//0616 kwon ��������� ����.
		ulBandwidth = 0;
		tmLastBandwithRecorded = _pTimer->GetHighPrecisionTimer().GetSeconds();
		cci_bInitUpdateMasterBuffer = FALSE;

		//0311 kwon �ӽ÷� ���� �ٿ��
		cci_bBound = TRUE;
	}
	
	//0105  
	if(m_bTcpIp && _pNetwork->IsTcpServer)
	{
		int sockaddr_size = sizeof( SOCKADDR_IN );		
		SOCKADDR_IN clientsockaddr;	
		SOCKET socket =  accept( cci_hSocket, (LPSOCKADDR)&clientsockaddr, &sockaddr_size);
		if(socket==INVALID_SOCKET)
		{
			//CPrintF(TRANS("Invalid Socket. %s\n"),(const char*)GetSocketError(socket));
		}
		else
		{
			CPrintF(TRANS("Client IP: %s  Connected\n"),inet_ntoa(clientsockaddr.sin_addr));				  
			adrIncomingAddress.adr_ulAddress = ntohl(clientsockaddr.sin_addr.s_addr);
			adrIncomingAddress.adr_uwPort = ntohs(clientsockaddr.sin_port);
			//0131	//0202	  
			
			client_socket = socket;
			client_cnt++;
			cci_bBound = TRUE;//�����~
		}
	}
	//..	
	
	//0131
	if (cci_bBound) 
	{
		// read from the socket while there is incoming data
		do 
		{			
			// initially, nothing is done
			bSomethingDone = FALSE;
			//0105 1line �����
			//			slSizeReceived = recvfrom(cci_hSocket,(char*)aub,MAX_PACKET_SIZE,0,(SOCKADDR *)&sa,&size);
			//0105
			if(m_bTcpIp&& _pNetwork->IsTcpServer)
			{//����
				//0131				
				slSizeReceived = recv(client_socket,(char*)aub,MAX_PACKET_SIZE,0);																
				
			}
			else if( m_bTcpIp )
			{//Ŭ���̾�Ʈ
			//	slSizeReceived = recv(cci_hSocket,(char*)aub,MAX_PACKET_SIZE,0);
				slSizeReceived = recv(cci_hSocket,(char*)m_inbuf.GetPoint(), m_inbuf.GetRemain(),0);
			}
			else
			{			
				slSizeReceived = recvfrom(cci_hSocket,(char*)aub,MAX_PACKET_SIZE,0,(SOCKADDR *)&sa,&size);
			}
			//..
			tvNow = _pTimer->GetHighPrecisionTimer();
			//0105 2line �����
			//			adrIncomingAddress.adr_ulAddress = ntohl(sa.sin_addr.s_addr);
			//			adrIncomingAddress.adr_uwPort = ntohs(sa.sin_port);
			//0105
			if(!m_bTcpIp)
			{
				adrIncomingAddress.adr_ulAddress = ntohl(sa.sin_addr.s_addr);
				adrIncomingAddress.adr_uwPort = ntohs(sa.sin_port);
			}
			//..	
			//On error, report it to the console (if error is not a no data to read message)
			if (slSizeReceived == SOCKET_ERROR) 
			{
				int iResult = WSAGetLastError();
				if (iResult!=WSAEWOULDBLOCK) 
				{
					// report it
					if (iResult!=WSAECONNRESET || net_bReportICMPErrors) 
					{
						CPrintF(TRANS("Socket error during UDP receive. %s\n"), 
							(const char*)GetSocketError(iResult));
						cci_bBound = FALSE; //0311 kwon
						//0611 kwon �߰�.
						//_pNetwork->ga_sesSessionState.ses_strDisconnected = TRANS("Try to Reconnect...");

						CUIManager* pUIManager = CUIManager::getSingleton();

						if( !_bLoginProcess || STAGEMGR()->GetCurStage() == eSTAGE_SELCHAR )
						{
							ShowDisconnMsg();
						}
						return;
					}
				}				
				// if block received
			} 
			else 
			{
				/* //kwon 0322 ����
				// if there is not at least one byte more in the packet than the header size
				if (slSizeReceived <= MAX_HEADER_SIZE) {
					// the packet is in error
					extern INDEX net_bReportMiscErrors;          
					if (net_bReportMiscErrors) {
						CPrintF(TRANS("WARNING: Bad UDP packet from '%s'\n"), AddressToString(adrIncomingAddress.adr_ulAddress));
					}
					// there might be more to do
					bSomethingDone = TRUE;
				} else if (net_fDropPackets <= 0  || (FLOAT(rand())/RAND_MAX) > net_fDropPackets) */{
					if ((tvNow.GetSeconds() - tmLastBandwithRecorded) <= 1.0f) {
						ulBandwidth += slSizeReceived;
					} else {
						_pNetwork->AddBandwidthGraphValue(ulBandwidth);
						double ctDelta = (tvNow.GetSeconds() - tmLastBandwithRecorded);
						tmLastBandwithRecorded += ctDelta;
						ulBandwidth = slSizeReceived;
					}

					//0322 kwon
					if (slSizeReceived == 0)
						continue;
					m_inbuf.SetPoint(slSizeReceived);
					/* //0322 kwon ����
					// if no packet drop emulation (or the packet is not dropped), form the packet 
					// and add it to the end of the UDP Master's input buffer
					ppaNewPacket = CreatePacket();
					ppaNewPacket->WriteToPacketRaw(aub,slSizeReceived);
					ppaNewPacket->pa_adrAddress.adr_ulAddress = adrIncomingAddress.adr_ulAddress;
					ppaNewPacket->pa_adrAddress.adr_uwPort = adrIncomingAddress.adr_uwPort;						
					*/
					if (net_bReportPackets) {
					//	CPrintF("%lu: Received sequence: %d from ID: %d, reliable flag: 0x%X, size: %d\n",(ULONG) tvNow.GetMilliseconds(),ppaNewPacket->pa_ulSequence,ppaNewPacket->pa_adrAddress.adr_uwID,ppaNewPacket->pa_uwReliable,ppaNewPacket->pa_slSize);
					}
					
					//0322 kwon
					while ((ppaNewPacket = m_inbuf.GetPacket()))
					{						
						if (cci_pbMasterInput.AppendPacket(*ppaNewPacket,FALSE,FALSE) == FALSE){
							ASSERT(FALSE);
						}
						// there might be more to do
						bSomethingDone = TRUE;
					}
					
				}
			}	
			
		} while (bSomethingDone);
	}
	
	// write from the output buffer to the socket
	while (cci_pbMasterOutput.pb_ulNumOfPackets > 0) 
	{
		ppaNewPacket		= cci_pbMasterOutput.PeekFirstPacket();		
		sa.sin_family		= AF_INET;
		sa.sin_addr.s_addr	= htonl(ppaNewPacket->pa_adrAddress.adr_ulAddress);
		sa.sin_port			= htons(ppaNewPacket->pa_adrAddress.adr_uwPort);
		//0105 1line �����		
		//    slSizeSent = sendto(cci_hSocket, (char*) ppaNewPacket->pa_pubPacketData, (int) ppaNewPacket->pa_slSize, 0, (SOCKADDR *)&sa, sizeof(sa));
		//0105		
		if( m_bTcpIp && _pNetwork->IsTcpServer )
		{
			//����
			//0131			
			slSizeSent = send(client_socket, (char*) ppaNewPacket->pa_pubPacketData, (int) ppaNewPacket->pa_slSize, 0);		
			
		}
		else if( m_bTcpIp )
		{
			// [2013/01/09] sykim70
			unsigned int res = htonl(m_crc.CalcCRC32(ppaNewPacket->pa_pubPacketData+MAX_HEADER_SIZE, ppaNewPacket->pa_slSize-MAX_HEADER_SIZE));
			memcpy(ppaNewPacket->pa_pubPacketData+ppaNewPacket->pa_slSize, &res, sizeof(unsigned int));
			//Ŭ���̾�Ʈ		
			slSizeSent = send(cci_hSocket, (char*) ppaNewPacket->pa_pubPacketData, (int) (ppaNewPacket->pa_slSize+sizeof(unsigned int)), 0);
			if( slSizeSent < 0 )
			{
// 				DWORD errcod = WSAGetLastError();
// 				CTString temp;
// 				temp.PrintF( "%d", errcod );
// 				MessageBox( NULL, temp, "", MB_OK );
			}

		}
		else
		{	
			slSizeSent = sendto(cci_hSocket, (char*) ppaNewPacket->pa_pubPacketData, (int) ppaNewPacket->pa_slSize, 0, (SOCKADDR *)&sa, sizeof(sa));
		}
		//..
		cci_bBound	= TRUE;   // UDP socket that did a send is considered bound
		tvNow		= _pTimer->GetHighPrecisionTimer();
		
		// if some error
		if ( slSizeSent == SOCKET_ERROR )
		{
			int iResult = WSAGetLastError();
			// if output UDP buffer full, stop sending
			if ( iResult == WSAEWOULDBLOCK ) 
			{
				return;
				// report it
			} 
			else if ( iResult != WSAECONNRESET || net_bReportICMPErrors ) 
			{
				// FIXME : �ߺ��Ǵ� �ڵ尡 ����.
				//extern BOOL _bLoginProcess;

				CUIManager* pUIManager = CUIManager::getSingleton();

				if( !_bLoginProcess || STAGEMGR()->GetCurStage() == eSTAGE_SELCHAR )
				{					
					ShowDisconnMsg();
				}

				cci_bBound = FALSE; //0311 kwon
			}
			else //0824
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				
				if( !_bLoginProcess || STAGEMGR()->GetCurStage() == eSTAGE_SELCHAR )
				{									
					ShowDisconnMsg();
				}
				cci_bBound = FALSE;
			}
			return;    
			// if all sent ok
		} 
		else 
		{
			if ((tvNow.GetSeconds() - tmLastBandwithRecorded) <= 1.0f) 
			{
				ulBandwidth += slSizeSent;
			} 
			else 
			{
				_pNetwork->AddBandwidthGraphValue(ulBandwidth);
				double ctDelta = (tvNow.GetSeconds() - tmLastBandwithRecorded);
				tmLastBandwithRecorded += ctDelta;
				ulBandwidth = slSizeSent;
			}
			if (net_bReportPackets)	
			{
				CPrintF("%lu: Sent sequence: %d to ID: %d, reliable flag: 0x%X,size: %d\n",(ULONG)tvNow.GetMilliseconds(),ppaNewPacket->pa_ulSequence,ppaNewPacket->pa_adrAddress.adr_uwID,ppaNewPacket->pa_uwReliable,ppaNewPacket->pa_slSize);
			}
			
			cci_pbMasterOutput.RemoveFirstPacket(TRUE);
			bSomethingDone=TRUE;
		}		
	}	
};

//------------------------------------------------------------------------------
// CCommunicationInterface::Is2rdLocal
// Explain: �߱� Local 2��° ������ ���õǾ����� Ȯ�� 
// Date : 2005-05-02,Author: Lee Ki-hwan
//------------------------------------------------------------------------------
BOOL CCommunicationInterface::Is2rdLocal()
{
	if ( g_iCountry != CHINA )  // �߱� Local�� �ƴϸ� ������ FALSE ( ���� �߱��������� ����� )
		return FALSE;

	return m_b2stLocal;
}


int CCommunicationInterface::ReadInfo(LoginServer* stLogin)
{
	// Define and add IPs to the filter vecto
	sIPFilter ip1;
	//sIPFilter ip1, ip2;
	
	ip1.SetIP(127, 0, 0, 1, g_iCountry);
	//ip1.SetIP(79, 143, 180, 97, g_iCountry); //79.143.180.97
	

	m_vecIPFilter.push_back(ip1);
	//m_vecIPFilter.push_back(ip2);

	std::sort(m_vecIPFilter.begin(), m_vecIPFilter.end());

	// Initialize login servers
	const int serverCount = 1;
	const char* serverNames[] = { "live"};
	//const char* serverNames[] = { "live", "test" };

 
	const char* serverAddresses[] = { "127.0.0.1"};
	//const char* serverAddresses[] = { "79.143.180.97"};

	const char* serverPorts[] = { "7777"};
	const char* fullUsers[] = { "100", "100" };
	const char* busyUsers[] = { "50", "50" };

	for (int i = 0; i < serverCount; ++i)
	{
		strncpy(stLogin[i].szName, serverNames[i], sizeof(stLogin[i].szName) - 1);
		strncpy(stLogin[i].szAddress, serverAddresses[i], sizeof(stLogin[i].szAddress) - 1);
		strncpy(stLogin[i].szPort, serverPorts[i], sizeof(stLogin[i].szPort) - 1);
		strncpy(stLogin[i].szFullUsers, fullUsers[i], sizeof(stLogin[i].szFullUsers) - 1);
		strncpy(stLogin[i].szBusyUsers, busyUsers[i], sizeof(stLogin[i].szBusyUsers) - 1);

		stLogin[i].szName[sizeof(stLogin[i].szName) - 1] = '\0';
		stLogin[i].szAddress[sizeof(stLogin[i].szAddress) - 1] = '\0';
		stLogin[i].szPort[sizeof(stLogin[i].szPort) - 1] = '\0';
		stLogin[i].szFullUsers[sizeof(stLogin[i].szFullUsers) - 1] = '\0';
		stLogin[i].szBusyUsers[sizeof(stLogin[i].szBusyUsers) - 1] = '\0';
	}

	return serverCount;
}

void CCommunicationInterface::ShowDisconnMsg()
{
	if ( _pGameState->IsRestartGame() == TRUE || _pGameState->GetGameMode() == CGameState::GM_RESTART )
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();
	// FIXME : �ߺ��Ǵ� �ڵ尡 ����.
	pUIManager->CloseMessageBox(MSGCMD_DISCONNECT);
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 299, "�ý���" ), UMBS_OK, UI_NONE, MSGCMD_DISCONNECT );
	MsgBoxInfo.AddString( _S( 300, "�������� ������ ���������ϴ�." ) );
	pUIManager->CreateMessageBox( MsgBoxInfo );
	cci_bInitUpdateMasterBuffer = FALSE;
	_pNetwork->m_bSendMessage = FALSE;
	_cmiComm.Disconnect();
}

void CCommunicationInterface::attachCRC( CPacket* packet )
{
	unsigned int res = htonl(m_crc.CalcCRC32(packet->pa_pubPacketData + MAX_HEADER_SIZE, packet->pa_slSize - MAX_HEADER_SIZE));
	memcpy(packet->pa_pubPacketData + packet->pa_slSize, &res, sizeof(unsigned int));
}

bool CCommunicationInterface::FindHosNameIP( const char* szHostName, sIPFilter &ip, INDEX iCountry )
{
	sockaddr_in sai;
	memset(&sai, 0, sizeof(sockaddr_in));
	sai.sin_addr.s_addr = inet_addr(szHostName);
	if(INADDR_NONE == sai.sin_addr.s_addr)
	{
		hostent *Hostent = gethostbyname(szHostName);

		if (Hostent == NULL)
			return false;

		sai.sin_addr.s_addr = ((struct in_addr FAR *)(Hostent->h_addr))->s_addr;
		ip.SetIP(sai.sin_addr.S_un.S_un_b.s_b1, sai.sin_addr.S_un.S_un_b.s_b2, sai.sin_addr.S_un.S_un_b.s_b3, sai.sin_addr.S_un.S_un_b.s_b4, iCountry);
	}

	return true;
}

BOOL CCommunicationInterface::GetMAC(char *mac_addr) {
  PIP_ADAPTER_INFO AdapterInfo;
  DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);

  AdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
  if (AdapterInfo == NULL) {
    printf("Error allocating memory needed to call GetAdaptersinfo\n");
    return FALSE; // it is safe to call free(NULL)
  }

  // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
  if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
    free(AdapterInfo);
    AdapterInfo = (IP_ADAPTER_INFO *) malloc(dwBufLen);
    if (AdapterInfo == NULL) {
      printf("Error allocating memory needed to call GetAdaptersinfo\n");
      return FALSE;
    }
  }

  if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
    // Contains pointer to current adapter info
    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    do {
      // technically should look at pAdapterInfo->AddressLength
      //   and not assume it is 6.
      sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
        pAdapterInfo->Address[0], pAdapterInfo->Address[1],
        pAdapterInfo->Address[2], pAdapterInfo->Address[3],
        pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
      printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
      // print them all, return the last one.
      // return mac_addr;

      printf("\n");
      pAdapterInfo = pAdapterInfo->Next;
    } while(pAdapterInfo);
  }
  free(AdapterInfo);
  return TRUE;
}

BOOL CCommunicationInterface::GetHWID(char* hwid)
{
	if (!hwid)
		return FALSE;

	// helper to test for known-bad placeholder values
	auto is_bad_value = [](const char* s) -> bool {
		if (!s || !*s) return true;
		int len = (int)strlen(s);
		if (len < 4) return true; // too short to be useful
		// trim leading/trailing whitespace
		int i = 0; while (i < len && isspace((unsigned char)s[i])) ++i;
		if (i == len) return true;
		// normalized checks
		const char* bad_values[] = {
			"Default string",
			"System Serial Number",
			"To be filled by O.E.M.",
			"To be filled by O.E.M",
			"None",
			"Unknown",
			"Not Specified",
			"Not available",
			"00000000-0000-0000-0000-000000000000",
			"00000000-0000-0000-0000",
			"0123456789",
			"XXXXXXXX",
			"00000000",
			"Not Applicable",
			"Not Present",
			"OEM",
			"None\\0",
		};
		char tmp[128];
		strncpy(tmp, s, sizeof(tmp) - 1);
		tmp[sizeof(tmp) - 1] = '\0';
		_strupr_s(tmp, sizeof(tmp));
		for (const char* bad : bad_values) {
			char bad_up[128];
			strncpy(bad_up, bad, sizeof(bad_up) - 1);
			bad_up[sizeof(bad_up) - 1] = '\0';
			_strupr_s(bad_up, sizeof(bad_up));
			if (strstr(tmp, bad_up) != NULL) return true;
		}
		// if string is mostly non-printable or all digits zeros
		bool allZeros = true;
		for (int k = 0; k < len; ++k) {
			unsigned char c = (unsigned char)s[k];
			if (c != '0' && !isspace(c)) { allZeros = false; break; }
		}
		if (allZeros) return true;
		return false;
		};

	HRESULT hres = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hres) && hres != RPC_E_CHANGED_MODE) {
		return FALSE;
	}

	hres = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE,
		NULL
	);
	if (FAILED(hres)) {
		CoUninitialize();
		return FALSE;
	}

	IWbemLocator* pLoc = NULL;
	hres = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres) || !pLoc) {
		CoUninitialize();
		return FALSE;
	}

	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"),
		NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres) || !pSvc) {
		if (pLoc) pLoc->Release();
		CoUninitialize();
		return FALSE;
	}

	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE);
	if (FAILED(hres)) {
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return FALSE;
	}

	// queries and property names to try (ordered by usefulness)
	const wchar_t* queries[] = {
		L"SELECT UUID FROM Win32_ComputerSystemProduct",
		L"SELECT SerialNumber FROM Win32_BIOS",
		L"SELECT SerialNumber FROM Win32_BaseBoard",
		L"SELECT ProcessorId FROM Win32_Processor",
		L"SELECT SerialNumber FROM Win32_DiskDrive",
		L"SELECT SerialNumber FROM Win32_PhysicalMedia"
	};
	const wchar_t* props[] = {
		L"UUID",
		L"SerialNumber",
		L"SerialNumber",
		L"ProcessorId",
		L"SerialNumber",
		L"SerialNumber"
	};

	bool found = false;
	for (size_t qi = 0; qi < _countof(queries) && !found; ++qi) {
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t(queries[qi]),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator
		);

		if (FAILED(hres) || !pEnumerator) {
			if (pEnumerator) pEnumerator->Release();
			continue;
		}

		IWbemClassObject* pclsObj = NULL;
		ULONG uReturn = 0;
		while (S_OK == pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn) && uReturn != 0) {
			VARIANT vtProp;
			VariantInit(&vtProp);
			hres = pclsObj->Get(props[qi], 0, &vtProp, 0, 0);
			if (SUCCEEDED(hres) && vtProp.vt == VT_BSTR && vtProp.bstrVal) {
				char buffer[128] = { 0 };
				int len = WideCharToMultiByte(CP_UTF8, 0, vtProp.bstrVal, -1, buffer, (int)sizeof(buffer), NULL, NULL);
				if (len > 0) {
					// sanitize: strip trailing non-printable
					for (char* p = buffer; *p; ++p) {
						if ((unsigned char)*p < 0x20 || (unsigned char)*p > 0x7E) { *p = '\0'; break; }
					}
					if (!is_bad_value(buffer)) {
						strncpy(hwid, buffer, 32);
						hwid[31] = '\0';
						found = true;
					}
				}
			}
			VariantClear(&vtProp);
			if (pclsObj) { pclsObj->Release(); pclsObj = NULL; }
			if (found) break;
		}
		pEnumerator->Release();
	}

	// If WMI did not yield a reliable identifier, fall back to MAC address (first usable)
	if (!found) {
		char macbuf[64] = { 0 };
		if (GetMAC(macbuf)) {
			// Accept MAC if not empty and not all zeros/invalid
			if (!is_bad_value(macbuf)) {
				strncpy(hwid, macbuf, 32);
				hwid[31] = '\0';
				found = true;
			}
		}
	}

	// If still not found, use volume serial of C: drive as last resort
	if (!found) {
		DWORD volSerial = 0;
		if (GetVolumeInformationA("C:\\", NULL, 0, &volSerial, NULL, NULL, NULL, 0)) {
			if (volSerial != 0 && volSerial != (DWORD)-1) {
				char vbuf[32];
				_snprintf_s(vbuf, sizeof(vbuf), _TRUNCATE, "%08X", volSerial);
				if (!is_bad_value(vbuf)) {
					strncpy(hwid, vbuf, 32);
					hwid[31] = '\0';
					found = true;
				}
			}
		}
	}

	// Clean up COM objects
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return found ? TRUE : FALSE;
}



