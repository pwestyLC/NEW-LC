

#ifndef		UI_ICON_H_
#define		UI_ICON_H_

#include <Engine/Help/UISupport.h>

class CUIText;
class CUIImageFont;
struct stItemEtc;
class CItems;

class ENGINE_API CUIIcon : public CUIBase
{
public:
	CUIIcon();
	~CUIIcon();	

	void initialize();

	void Create(CUIWindow* pParent, int x, int y, int width, int height, int nWhich, int nBtnType, int nQuickID = -1);

	void setInfo(UIBtnExType type, SBYTE cTexID, int row, int col);
	void setData(CItems* pItems, bool bRef = true, bool isChat = false);
	void setData(UIBtnExType type, int nIndex, int nVIndex = -1);
	void setAffinity(int nIndex);
	void setAffinity(eUIBTN_ETC_TYPE eType,	int nIndex,	int nPoint, int nTexItemIndex = -1);
	// ģȭ�� ���� ������.
	void setAffinityM(int nIndex
		, int nPoint
		, SBYTE cTexID
		, int row
		, int col);
	void setSkill(int nSkill_idx, bool bSpecial = false, bool bDisable = false);	
	void setCash(int nCashIdx);
	// ����, ����ġ, ��ų����Ʈ ������ ������ ���� �߰�.
	void setDataEtc(eUIBTN_ETC_TYPE type, int nIndex = 0, SQUAD llCount = 0);

	UIBtnExType getBtnType()		{ return m_BtnType; }
	eUIBTN_ETC_TYPE getBtnEtcType()	{ return m_BtnEtctype;	}
	void setCooltime(bool bCool)	{ m_bCooltime = bCool; }

	// -----------------------------------------------------------------------

	INDEX getIndex()			{ return m_nIndex; }
	CItems* getItems()			{ return m_pItems; }
	stItemEtc* getItemEtc()		{ return m_pItemEtc;	}

	bool isRef()				{ return m_bRef; }
	void copyItem(CUIIcon* pIcon);
	void cloneItem(CUIIcon* pIcon);
	void setImage(eIMG_TYPE eType, bool bOn);
	void setImageHide(eIMG_TYPE eType, BOOL bHide);	

	// ------------------------------------------------------------------------
	// Clone
	void setPointAttr(CUIBase* p)		{ m_pAttribute = p; addChild(p); }
	void setPointUpgrade(CUIImageFont* p)	{ m_pUpgrade = p; addChild((CUIBase*)p);}
	void setPointStack(CUIImageFont* p)	{ m_pStack = p; addChild((CUIBase*)p);}
	void setPointStackError(CUIBase* p)	{ m_pStackError = p; addChild((CUIBase*)p);}
	void setPointPlus(CUIText* p)		{ m_pPlus = p; addChild((CUIBase*)p);}
	void setPointJewel(CUIBase* p)		{ m_pJewelGrade = p; addChild((CUIBase*)p);}
	void setPointToggle(CUISpriteAni* p){ m_pToggle = p; addChild((CUIBase*)p);}
	void setPointImage(eIMG_TYPE eType, CUIImage* p) { m_pImage[eType] = p; addChild((CUIBase*)p);}

	bool IsEmpty()		{ return (m_nIndex < 0); }

	void setUIType(int nType)		{ m_nUIType = nType; }
	int getUIType()					{ return m_nUIType; }

	void SetSelectIcon(BOOL bSelect)		{ m_bSelectIcon = bSelect; }

	void Hide( BOOL bHide ) {
		if (bHide == TRUE)
			CloseProc();

		CUIBase::Hide(bHide);
	}

	bool	IsWearTab()				{ return m_bWearTab; }
	void	setWearTab(bool bVal)	{ m_bWearTab = bVal; }

	bool	IsSpecial()				{ return m_bSpecialSkill;	}
	bool	IsSuit()				{ return m_bSuit; }
	bool	IsRestritionItem();		//	����Ʈ ������ ��� ���� üũ

	void setStack();
	void setUpgrade();

	void SetWhichUI(int nUI)	{ m_eWhichUI = (UI_TYPE)nUI; }
	int GetWhichUI()			{ return (int)m_eWhichUI; }
	int GetQuickSlotID()		{ return m_nQuickSlotID; }

	__int64 GetUseItemStartTime()		{ return m_nStartTime; }
	void SetUseItemStartTime(__int64 time) { m_nStartTime = time; }

	void SetQuickSlotWearType(int nType)	{ m_nQuickSlotWearType = nType; }
	int	GetQuickSlotWearType()				{ return m_nQuickSlotWearType; }
	void SetSuit(bool bSuit)			{ m_bSuit = bSuit; }
	int GetCashIndex()					{ return m_nCashIndex; }

protected:
	void renderDefault(int x, int y, CDrawPort* pDraw, 
		COLOR color = DEF_UI_COLOR_WHITE, float delta = 0.f, const ULONG ulPBT = PBT_BLEND);
	void renderCooltime(int x, int y, CDrawPort* pDraw);
	void setIconUV(int nRow, int nCol);

	WMSG_RESULT OnCloseProc();

private:
	void setItem(int nIndex, int nVIndex);
	void setQuest(int nIndex);
	void setAction(int nIndex);
	void setMCombo(int nIndex);	

	// ------------------------------------------------------------------------	
public:
	void clearIconData();
	void setCount(__int64 count);

	void SetCustomTooltip(BOOL bShow)	{ m_bCustomShowInfo = bShow ? true : false; }
	void SetToggle(bool bToggle);
	
	void SetCommandDrag(Command* pCmd)		{ SAFE_DELETE(m_pCmdDrag); m_pCmdDrag = pCmd; }

	void SetHighLightMode(bool bOnOff);
	void SetHighLight(bool bOnOff) { m_bHighlight = bOnOff; }
	bool GetHighLightMode() { return m_bHighlightMode; }	

	void SetDisable(bool bDisable)	{ m_bDisable = bDisable; }
	bool GetDisable()				{ return m_bDisable; }

	CUIBase* Clone();

	void OnEnter(UINT16 x, UINT16 y);
	void OnLeave(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonDBLClick(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	// --------------------------------------------------------------------

	void OnRender(CDrawPort* pDraw);
	void OnUpdate( float fDeltaTime, ULONG ElapsedTime );

	// --------------------------------------------------------------------

	void HideTooltip();

private:
	int				m_nSize;
	bool			m_bRef;			// CItems �� ������ �ƴ� ������ ��� ǥ�� (delete ����)
	CItems*			m_pItems;

	// ����, ����ġ, sp�� ������ ��� ����ü.
	// ���� ��� ������ ����Ҽ��� ���� ������ �߰�
	stItemEtc*		m_pItemEtc;
	int				m_nIndex;
	int				m_nSkillDisable;	// Disable Tex Offset
	bool			m_bCooltime;

	bool			m_bCustomShowInfo;
	bool			m_bHighlight;
	bool			m_bHighlightMode;

	BOOL			m_bSelectIcon;
	Command*		m_pCmdDrag;
	DWORD			m_dwAniStartTime;

	CUIBase*		m_pAttribute;
	CUIImageFont*	m_pUpgrade;
	CUIImageFont*	m_pStack;
	CUIBase*		m_pStackError;
	CUIText*		m_pPlus;
	CUIBase*		m_pJewelGrade;
	CUISpriteAni*	m_pToggle;
	CUIImage*		m_pImage[eIMG_TYPE_MAX];

	UIBtnExType		m_BtnType;
	eUIBTN_ETC_TYPE	m_BtnEtctype;
	SBYTE			m_TexID;
	UIRectUV		m_uv;
	COLOR			m_color;
	int				m_nUIType;			// ex) UI_INVENTORY
	bool			m_bWearTab;
	bool			m_bSpecialSkill;
	UI_TYPE			m_eWhichUI;
	int				m_nQuickSlotID;
	int				m_nQuickSlotWearType;
	__int64			m_nStartTime;
	bool			m_bSuit;
	int				m_nCashIndex;
	int				m_nPetKind;
	// �� �����ܿ��� LBTNDown�� �߻��� ��쿡�� �巡�� Ŀ�ǵ� ����.
	bool			m_bDrag;
#ifdef DURABILITY
	bool			m_bDurItem;
#endif	//	DURABILITY
	bool			m_bDisable; // ���������� ����, ���������� ����� ������ �ѷ����� �ʴ´�.
#ifdef UI_TOOL
	
	int			m_nRow;
	int			m_nCol;

public: 
	void getInfo(int& type, SBYTE& texId, int& row, int& col)
	{
		type	= (int)m_BtnType;
		texId	= m_TexID;
		row		= m_nRow;
		col		= m_nCol;
	}
#endif	// UI_TOOL
};

#endif		// UI_ICON_H_