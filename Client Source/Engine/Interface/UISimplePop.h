#ifndef	UISIMPLEPOP_H_
#define	UISIMPLEPOP_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <Engine/Interface/UITrackPopup.h>

// [sora] ������ command �߰�
typedef enum _SimplePopState
{
	SPSO_NAME				= 0,			// �����̸�
	SPSO_WHISPER			= 1,			// �ӼӸ�
	SPSO_FRIEND				= 2,			// ģ�� ���
	SPSO_TRADE				= 3,			// ��ȯ ��û
	SPSO_PARTY				= 4,			// ��Ƽ ��û (�Ϲ� / �Լ��켱 / ������)
	SPSO_PARTY_OUT			= 5,			// ��Ƽ ����
	SPSO_PARTY_JANG			= 6,			// ��Ƽ�� ����
	SPSO_GUILD_IN			= 7,			// ��� ����
	SPSO_GUILD_WAR_START	= 8,			// ������� ��û
	SPSO_GUILD_WAR_END		= 9,			// ������� �ߴ�
	SPSO_SETLABEL			= 10,
	SPSO_RESETLABEL			= 11,
	SPSO_CANCEL				= 12,			// ���
	SPSO_END				= 13,			// SimplePopStateOne End

	SPST_START				= 14,			// SimplePopStateTwo End
	SPST_PARTY_JOIN_A		= SPST_START,	// �Ϲ� ��Ƽ ��û
	SPST_PARTY_JOIN_B		= 15,			// �Լ��켱 ��Ƽ ��û
	SPST_PARTY_JOIN_C		= 16,			// ������ ��Ƽ ��û

	SPST2_START				= 17,
	SPST2_SETLABEL1			= SPST2_START,
	SPST2_SETLABEL2			= 18,
	SPST2_SETLABEL3			= 19,
	SPST2_SETLABEL4			= 20,
	SPST2_SETLABEL5			= 21,
	SPST2_SETLABEL6			= 22,
	SPST2_SETLABEL7			= 23,
	SPSO_EXPEDITION_INVITE	= 24,			// ������ �ʴ�
	SPSO_EXPEDITION_KICK	= 25,			// ������ ����
	// brazil ��û ���� �˾��� ���� ä�� ����. [3/9/2011 rumist]
	SPSO_MUTE_CHARACTER		= 26,
	SPSO_EXPEDITION_VIEW	= 27,
	SPSO_KICK				= 28,
#ifdef ENABLE_ADMIN_KICKBAN
	SPSO_KICK_PLAYER = 30,
	SPSO_BAN_PLAYER = 31,
	SPSO_BLOCK_PLAYER = 32,
#endif

} SIMPLE_POP_STATE;

class CUISimplePop : public CUITrackPopup
{
public:
//	INDEX m_iExeNum[SPSO_END];

	CUITrackPopup m_tpList;

	CTextureData*			m_ptdMenuTexture;			//������ ���� ȭ��ǥ�� ���� �ؽ���
	CTextureData*			m_ptdExpeditionTexture;
	UIRectUV				m_rtArrow;					//ȭ��ǥ �ؽ��� ��ǥ
// [sora] RAID_SYSTEM	
	UIRectUV				m_rtLabelIcon[7];	// ǥ������ 0 ����, 1 ����, 2 �߹ٴ�, 3 ����Į, 4 ��, 5 �Ǹ�, 6 �ذ� 			
	bool					m_bTarget;
	CTString				m_strNoTargetName;
	int						m_nNoTargetCharIndex;
	CTString 				m_strNick;
public:
	CUISimplePop();
	~CUISimplePop();

	void Create(CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight);

	ENGINE_API void OpenPop(CTString strName, BOOL bParty, BOOL bGuild, INDEX ixPos, INDEX iyPos);
	ENGINE_API void OpenPopNoTarget(CTString strName, int nCharIndex, bool bParty, INDEX ixPos, INDEX iyPos); // Ÿ�پ��� �˾�â ����
	void ClosePop();

	void Render();

	void SetExeList(CTString strUserName, BOOL bParty, BOOL bGuild);
	void SetExeListNoTarget(CTString strUserName, bool bParty);
	void SetSubExeList( INDEX iCommandNum );

	void Execution(INDEX exeNum);

	WMSG_RESULT	MouseMessage( MSG *pMsg );
};

#endif	// UISIMPLEPOP_H_