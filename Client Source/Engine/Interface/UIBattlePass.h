#ifndef _UI_BATTLE_PASS_H_
#define _UI_BATTLE_PASS_H_

#ifdef BATTLE_PASS_SYSTEM
#define MAX_BATTLE_PASS 30

typedef struct __typeBattlePassRewardItem {
	int itemIdx;
	int itemCount;
} BattlePassRewardItem;

typedef struct __typeBattlePassItem {
	int type;
	int level;
	int points;
	CTString name;
	BattlePassRewardItem reward;
} BattlePassItem;

class CUIBattlePass : public CUIWindow
{
public:
	CUIBattlePass();
	~CUIBattlePass();

	void initialize();
	void OpenUI();
	void CloseUI();
	void BackPage();
	void ForwardPage();
	
	BOOL CloseWindowByEsc()		{ CloseUI();	return TRUE;	}

	void SendExchangeExp();

	void ClearItems() { 
		m_items_free.clear(); 
		m_items_premium.clear();
	}

 void SetHasNext(BOOL next) { m_bHasNext = next; }
	BOOL HasNext() { return m_bHasNext; }

	int GetCurrentPage() { return m_nCurrentPage; }
	
	void AddItemFree(BattlePassItem item);
	void AddItemPremium(BattlePassItem item);

	void UpdateListItem();
	void UpdateInfo(int premium, int points, int progress, int level, int season);
	void SendPageChanged(int page);
	void RefreshUI();

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseWheel(UINT16 x, UINT16 y, int wheel);

	void ResetSavePosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
    void AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);

private:

	BOOL 		m_bHasNext;

	CUIBase*	m_pDragArea;
	CUIButton*	m_pBtnOk;
	CUIButton*	m_pBtnPageLeft;
	CUIButton*	m_pBtnPageRight;
	CUIText*	m_pTextTitle;
	CUIText*	m_pTextProgress;
	CUIImage*	m_pImgBarProgrss;
	CUIProgressBar* m_pointBarProgress;//Cloud add
	CUIText*	m_pTextCurrentLevel;
	CUIText*    m_pTextNextLevel;//Cloud add

	CUIBase*	m_pBaseInfo;

	CUIText*	m_pTextLevel[MAX_BATTLE_PASS];

	CUIIcon*	m_iconFree[MAX_BATTLE_PASS];
	CUIImage*	m_pImgFreeCheck[MAX_BATTLE_PASS];

	CUIIcon*	m_iconPremium[MAX_BATTLE_PASS];
	CUIImage*	m_pImgPremiumCheck[MAX_BATTLE_PASS];
	CUIImage*	m_pImgPremiumLock[MAX_BATTLE_PASS];

	int m_nOriX;
	int m_nOriY;
	bool m_bDrag;

	int m_nProgress;
	int m_nPoints;
	int m_nLevel;
	int m_nPremium;
	int m_nCurrentPage;
	int m_nSeason;

	std::vector<BattlePassItem> m_items_free;
	std::vector<BattlePassItem> m_items_premium;
};
#endif

#endif // _UI_PRESTIGE_H_