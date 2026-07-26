
#ifndef _UISIEGE_WARFARE_NEW_H
#define _UISIEGE_WARFARE_NEW_H

#define DRATAN_TOWER_MAX		(5)
#define DRATAN_TOWER_KIND_MAX	(7)
#define TOWER_UPGRADE_MAX	(3)

enum UPGRADE_TYPE {
	SWUT_ATTACK,
	SWUT_GUARD,
	SWUT_GATE,
};

// #include <Engine/Interface/UIWindow.h>
// #include <Engine/Interface/UIDrawFigure.h>
// #include <Engine/Interface/UICheckButton.h>
// #include <Engine/Interface/UISpinButton.h>

class CUISiegeWarfareNew : public CUIWindow
{
	// ���� ----------------------------------------------------------------->>
	BOOL					m_bOnWar;						// ���� ��
	// Ÿ��Ʋ
	UIRect					m_rcTitle;						// Title Rect
	CUIDrawBox				m_bxBox1;						// Box(1) - ���� �� �ڽ�
	CUIDrawBox				m_bxBox2;						// Box(2) - £�� �� �ڽ�
	CUIDrawBox				m_bxBackGroundBox;				// Box of Top Background
	CUIDrawBox				m_bxBackGroundBox2;				// Box of Bottom Background	
	// ----------------------------------------------------------------------<<

	// Ÿ�� �����ϱ� -------------------------------------------------------->>
	// ��ư	
	CUIButton				m_btnApply;													// �����ϱ�
	CUIButton				m_btnReturn;												// ���ư���
	CUICheckButton			m_cbtnTowerOn[DRATAN_TOWER_KIND_MAX][DRATAN_TOWER_MAX];		// ���� ���� ��ư
	CHAR					m_cTowerSet[DRATAN_TOWER_KIND_MAX];							// ���� ���� �V( Ÿ�� ������ ������� )
	// UV of Lines
	UIRectUV				m_uvLineV;						// UV of vertical line
	UIRectUV				m_uvLineH;						// UV of Horizon line
	// ----------------------------------------------------------------------<<
	
	// Ÿ�� ��ȭ�ϱ� -------------------------------------------------------->>
	INDEX					m_iUpgradeLevelOld;				// �̹� ��ȭ�� ����
	INDEX					m_iUpgradeLevel;				// ��ȭ ����
	INDEX					m_iUpgradeType;					// ��ȭ ����
	CUISpinButton			m_sbtnUpgrade;					// ��ȭ ���� ��ư
	CUIButton				m_btnOK;						// Ȯ��
	CUIButton				m_btnCancel;					// ���
	// ----------------------------------------------------------------------<<

	// Ÿ�� �����ϱ� -------------------------------------------------------->>
	SQUAD					m_iRepairMoney;
	INDEX					m_iRepairTowerIndex;

	// ���� �ϱ� ------------------------------------------------------------>>
	DWORD					m_tmWaitTime;
	DWORD					m_tmStartTime;					// ���� ���� �ð�	
	INDEX					m_iConsensusBarSize;			// ���� ����
	WRect					m_rcPuple;						// ���� ���� ��(������)
	CUIDrawBox				m_bxPurple;						// ���� ���� �ڽ�

	// ----------------------------------------------------------------------<<

	// ��Ȱ ���� ------------------------------------------------------------>>
	INDEX					m_iNpcIdx;						// ��Ȱ ���� NPC
	// ----------------------------------------------------------------------<<

	// ��Ȱ ��� ------------------------------------------------------------>>
	BOOL					m_bReceivedTime;				// ���� ���� ��� // WSS_DRATAN_SIEGEWARFARE 2007/10/16
	INDEX					m_iWaitTime;					// ��� �ð�(sec)	
	INDEX					m_iWaitTime_const;				// ��� �ð�(sec) - ����	
	DWORD					m_tmInitTime;					// ��� ó�� �ð�
	UIRect					m_rcWaitTime;					// �ð� ��� ��ġ
	// ----------------------------------------------------------------------<<
	
public:	
	CUISiegeWarfareNew();
	virtual ~CUISiegeWarfareNew();
	
	// Create Window
	void	Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight );
	
	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	// Message
	WMSG_RESULT MouseMessage( MSG *pMsg );
	WMSG_RESULT CheckCBMouseMessage( MSG * pMsg);

	// Open SiegeWarfare
	void	OpenCheckTower();
	void	OpenUpgradeTower();
	void	OpenConsensus();
	void	OpenRepairTower();
	
	// Close
	void	Clear();
	void	CloseSiegeWarfare();	
	
	// Render
	void	Render();	
	void	RenderCheckTower();
	void	RenderUpgradeTower();
	void	RenderRepairTower();
	void	RenderConsensus();
	void	RenderWaitTime();
	
	// MessageBox	
	void	Message( int nCommandCode, CTString strMessage, DWORD dwStyle );	// �޼��� �ڽ�
	
	// Etc	
	ENGINE_API void	StartConsensusAni(int charIdx);
	ENGINE_API void	WaitConsensus(ULONG charIdx);

	inline int	GetUpgradeType() { return m_iUpgradeType; }	
	inline int	GetUpgradeLevel() { return m_iUpgradeLevel; }	
	void		SetUpgradePos(INDEX tPos);
	inline void	SetUpgradeType(INDEX tType) { m_iUpgradeType = tType; }	
	inline void	SetUpgradeLevel(INDEX tLevel) { m_iUpgradeLevel = tLevel; }		
	inline void	SetUpgradedLevel(INDEX tLevel) { m_iUpgradeLevelOld = tLevel; }		
	void		SetTowerSetFromCB();
	void		SetCBFromTowerSet();
	ENGINE_API inline void SetTowerSet(int iIdx,char tValue) {m_cTowerSet[iIdx] = tValue;}
	SQUAD GetTowerPay();
	SQUAD GetTowerUpgradePay(int iType,int iLevel);

	void SetRepairMoney(int tIdx,SQUAD tMoney);
	inline SQUAD	GetRepairMoney() { return m_iRepairMoney; }
	inline void SetRepairTowerIndex(int tIdx) { m_iRepairTowerIndex = tIdx; }
	inline int	GetRepairTowerIndex() { return m_iRepairTowerIndex; }

	inline void SetTimeReply(BOOL bReceived) { m_bReceivedTime = bReceived; } // WSS_DRATAN_SIEGEWARFARE 2007/10/16
	inline BOOL GetTimeReply() { return m_bReceivedTime; }
	inline void SetWaitTime(int tWaitTime) { m_iWaitTime_const = m_iWaitTime = tWaitTime , m_tmStartTime = (unsigned int(_pTimer->GetLerpedCurrentTick()*1000)); /*timeGetTime();*/}
	inline int	GetWaitTime() { return m_iWaitTime;}
	inline void SetWarState(BOOL bOnWar) { m_bOnWar = bOnWar; }
	inline BOOL GetWarState() { return m_bOnWar; }
	
	// Consensus	
	void StartConsensus(ULONG charIdx);								
	ENGINE_API void StopConsensus(ULONG charIdx);
	ENGINE_API void CompleteConsensus(ULONG charIdx);
	int CheckConsensus();	

	// Rebirth Quarters
	ENGINE_API void CreateBuyQuarterBox(int iNpcIdx);
	ENGINE_API void CreateWaitQuarterBox();

	// MessageBox Command
	void MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput );

	// Send Messages
	ENGINE_API void SendConsensus(UBYTE tSubType);
	ENGINE_API void SendApplyTowerSet();
	ENGINE_API void SendRequestTowerSet();
	void SendTowerReinforce(int iType,int iLevel);
	void SendTowerStateRequest(int tType);
	void SendTowerRepair(int tIdx);
	ENGINE_API void SendTowerRepairStateRequest(int tIdx);
	ENGINE_API void SendDratanPortalMessage( int iMobIndex );
	void SendSiegewarfareRebirth(int tSubType);

	// Rebirth Quarter
	void SendBuyQuarter(int iNpcIdx);
     
	// [2011/07/13 : Sora] ��Ȱ���â ���� �Լ� �߰�
	ENGINE_API void	OpenWaitTime();
};



  
#endif // _UISIEGE_WARFARE_H