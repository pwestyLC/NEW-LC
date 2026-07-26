#ifndef UI_QuickPanel_H_
#define UI_QuickPanel_H_

#include <functional>
#include <Engine/Interface/UIWindow.h>

class CUIEditBox;
class CUIList;
class CUIImage;
class CUIText;
class CUITextBox;
class CUIButton;
class CUIBase;
class CUIScrollBar;
class CUIIcon;

class CAction;
class CSkill;
class CSpecialSkill;
class CAction;

class CUIQuickPanel : public CUIWindow
{
public:
	CUIQuickPanel();

	void initialize();
	void Open();
	void Close();
	void	ResetQuickSLotSKill();
	bool _CheckDuplicate(CUIIcon * pIcon);
	BOOL CloseWindowByEsc();
	void SendItemUsed();
	void ErrMessage(int errCode);

	void	UseQuickSlot(int iconcount);
	void    UseBuffReq(int nSkillIndex, int sbLevel) ;
	void    SendSaveItens();
	void    ResetallBtns();

	void	UseQuickSlot0();
	BOOL	ProcessShortCut( MSG *pMsg );

protected:
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);

	int m_count_command;
	int m_nOldSelectIdx;
	int m_selected_command;

	CUIText*  m_NazwaPostaci;
	BOOL				m_bIsInside;
	void	AddBtn( int nSlotType = -1, int nData0 = -1, int nData1 = -1 );
	// Network message functions ( send )
	void	SendAddBtn( int nSlotType = -1, int nData0 = -1, int nData1 = -1 );

private:
	int						m_nIdxItemSpecialSkill;
	CSkill*			m_pSkill;
	enum eERR_MSG
	{
		eERR_CAN_NOT_OPEN_KEY = 0,
		eERR_EMPTY_KEY,
		eERR_MAX
	};

	CUIButton* m_pBtnInput;				// ConsoleGM
	CUIButton* m_pbtnClose;				// ConsoleGM
	CUIButton* m_pbtnUse;				// ConsoleGM
	CUIImage* m_pConsoleGM;				// ConsoleGM

	
	CUIIcon*		m_pIcon[25]; // EXTEND_CASH_BAG_50
	CUIText* m_pDrag;
	CItems* m_pSendItems;
	

	ENGINE_API void	SetToggle( int nType, int nIndex, bool bToggle );
	bool		m_bDrag;
	int			m_nOriX, m_nOriY;
	void SetPutOnItemData(int iconcount);

	int	 m_nCashBagNum;
};


#endif // UI_QuickPanel_H_
