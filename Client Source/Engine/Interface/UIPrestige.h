#ifndef _UI_PRESTIGE_H_
#define _UI_PRESTIGE_H_

#ifdef PRESTIGE_SYSTEM
#define MAX_PRESTIGE 10

typedef struct __typePrestigeRewardItem {
	int itemIdx;
	int itemCount;
} PrestigeRewardItem;

typedef struct __typePrestigeItem {
	int type;
	int level;
	int points;
	CTString name;
	PrestigeRewardItem reward;
} PrestigeItem;
class CUIPrestige : public CUIWindow
{
public:
	CUIPrestige();
	~CUIPrestige();

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

	//BOOL SetHasNext(BOOL next) { m_bHasNext = next; }
	//BOOL HasNext() const { return m_bHasNext; }
	void SetHasNext(BOOL next);
	BOOL HasNext() const;



	int GetCurrentPage() { return m_nCurrentPage; }

	void AddItemFree(PrestigeItem item);
	void AddItemPremium(PrestigeItem item);

	void UpdateListItem();
	void UpdateInfo(int premium, int points, int progress, int level, int season);
	void SendPageChanged(int page);
	void RefreshUI();

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);

	void ResetSavePosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
    void ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
    void AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);

private:

	BOOL 		m_bHasNext;

	CUIBase* m_pDragArea;
	CUIButton* m_pBtnOk;
	CUIButton* m_pBtnPageLeft;
	CUIButton* m_pBtnPageRight;
	CUIText* m_pTextTitle;
	CUIText* m_pTextProgress;
	CUIImage* m_pImgBarProgrss;
	CUIProgressBar* m_pointBarProgress;//Cloud add
	CUIText* m_pTextCurrentLevel;
	CUIText* m_pTextNextLevel;//Cloud add

	CUIBase* m_pBaseInfo;

	CUIText* m_pTextLevel[MAX_PRESTIGE];

	CUIIcon* m_iconFree[MAX_PRESTIGE];
	CUIImage* m_pImgFreeCheck[MAX_PRESTIGE];

	CUIIcon* m_iconPremium[MAX_PRESTIGE];
	CUIImage* m_pImgPremiumCheck[MAX_PRESTIGE];
	CUIImage* m_pImgPremiumLock[MAX_PRESTIGE];

	int m_nOriX;
	int m_nOriY;
	bool m_bDrag;

	int m_nProgress;
	int m_nPoints;
	int m_nLevel;
	int m_nPremium;
	int m_nCurrentPage;
	int m_nSeason;

	std::vector<PrestigeItem> m_items_free;
	std::vector<PrestigeItem> m_items_premium;
};
#endif

#endif // _UI_PRESTIGE_H_