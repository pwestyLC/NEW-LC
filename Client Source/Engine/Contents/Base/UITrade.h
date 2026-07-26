#ifndef _UI_TRADE_H_
#define _UI_TRADE_H_

class CUITrade : public CUIWindow
{
public:
	CUITrade();
	~CUITrade();

	void initialize();
	void OpenUI(int npc_index); //dethunter12 item check 
	void CloseUI();
	
	BOOL CloseWindowByEsc()		{ CloseUI();	return TRUE;	}

	void SetTitle(std::string strTitle);

	// º¸»ó ¹Þ°Ú´Ù.
	void SendTrade();

	// º¸»ó ¾ÆÀÌÅÛ ¸®½ºÆ®.
	void UpdateItemList(int npc_index); //dethunter12 add 11/13/2019
	// º¸»óÇ°À» ¹Þ±â À§ÇÑ ÇÊ¿ä ¾ÆÀÌÅÛ.
	void UpdateAmendCondition(int nAmendIndex);
	// º¸»óÇ°À» ¹Þ±â À§ÇÑ ÇÊ¿ä ¾ÆÀÌÅÛ °¹¼ö. 
	// amendindex°¡ 0º¸´Ù ÀÛÀ» °æ¿ì ÇöÀç ¼±ÅÃµÈ ¾ÆÀÌÅÛ Ä«¿îÆ®¸¦ ¾÷µ¥ÀÌÆ®.
	void UpdateAmendConditionCount(int nAmendIndex);
	// º¸»ó ¾ÆÀÌÅÛ »ó¼¼ Á¤º¸.
	void UpdateAmendItem(int nAmendIndex);
	// º¸»ó ¾ÆÀÌÅÛ °¹¼ö.
	void UpdateAmendItemCount(int nAmendIndex);
	
	// º¸»ó ¹ÞÀ»¼ö ÀÖ´ÂÁö °Ë»ç.
	bool IsAmend(int nAmendIndex);

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);

    void ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
    void AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);

private:
	enum
	{
		eLIST_AMEND_ITEM = 0,
		eLIST_AMEND_CONDITION,
		eLIST_END
	};

	bool CheckItem(int nAmendIndex, int nConditionIndex);

	CUIBase*	m_pDragArea;
	CUIButton*	m_pBtnOk;
	CUIText*	m_pTextTitle;

	CUIList*	m_pList[eLIST_END];
	CUIBase*	m_pBaseAmendInfo;
	CUIScrollBar* m_plistScroll;
	

	int m_nOriX;
	int m_nOriY;
	bool m_bDrag;

	std::vector<int> m_currentItems;
};
#endif // _UI_TRADE_H_