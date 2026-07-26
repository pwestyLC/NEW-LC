#ifndef	UI_TARGET_INFO_NEW_H_
#define	UI_TARGET_INFO_NEW_H_

class CUIImage;
class CUIText;
class CUIImageSplit;
class CUIImageArray;

// ���� Ÿ��
enum eTARGET_TOOLTIP
{
	eTOOLTIP_FAME = 0,
	eTOOLTIP_ATTRATT,
	eTOOLTIP_ATTRDEF,
	eTOOLTIP_SYNDICATE,
	eTOOLTIP_MAX
};

class CTargetInfoUI : public CUIWindow
{
public:
	CTargetInfoUI();
	~CTargetInfoUI();

	// ���� Ÿ���� �Ӽ� �ε��� üũ
	void	CheckAttrIdx();

	// Buff
	void	SetTargetBuff( BOOL bMe );
	void	ShowPKTargetHP( BOOL bOn) { m_bShowPkHp = bOn; }

	// UI function
	void	OpenUI();
	void	CloseUI();
	void	UpdateUI();
	// ��׶��� üũ
	void	UpdateFrame();
	// ���� ����
	void	UpdateTargetInfo();
	void	UpdateHPInfo();
	// �ΰ� ���� ������Ʈ
	void	UpdateFameIcon();
	void	UpdateAttrIcon();
	// �˹���
	void	UpdateSyndicateIcon();
	// ������ ����
	void	UpdateFrameSize(int nWidth);

	// ���� ��Ʈ�� set
	void	UpdateTooltip(eTARGET_TOOLTIP eType);
	// --------------------------------------------<<

	void	initialize();
	void	OnPostRender(CDrawPort* pDraw);

	void    UpdateHPInfoOnText(); // rrbkmz

	// MSG Proc
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT	OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT	OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT	OnRButtonDown(UINT16 x, UINT16 y);

	// Adjust position
	void	ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );
	void	AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ );

	BOOL	CloseWindowByEsc();

protected:
	enum eSUB_INFO_TYPE
	{
		eSUB_INFO_FAME = 0,
		eSUB_INFO_ATTR,
		eSUB_INFO_SYNDICATE
	};

	bool IsAddSubInfo(eSUB_INFO_TYPE eType);
	CTString _getFameTooltip(); // ���� ��Ʈ��
	CTString _getAttrTooltip(int attrType); // �Ӽ� ��Ʈ��
	CTString _getSyndicateTooltip(int& nWidth); // ���� ��Ʈ��

	// alan wins loses enemy
	int		_getWins();
	int		_getLoses();

	int		_getFame();
	void	_getAttr(int attrType, int& attr, int& attrLv);

	BOOL	m_bShowBuff;
	BOOL	m_bShowPkHp;
	BOOL	m_bShowHpBar;
	bool	m_bDrag;
	int		m_nOriX, m_nOriY;

	//�̹��� Ÿ��
	enum eIMG_TYPE
	{
		eIMG_MOVE = 0,  // Ÿ��Ʋ�� �̵�
		eIMG_HP,		// HP ��
		eIMG_FAMEMARK,	// ���� ������
		eIMG_MAX
	};

	CUIImage* m_pImg[eIMG_MAX];

	//��Ʈ�� Ÿ��
	enum eTEXT_TYPE
	{
		eTEXT_LEVEL = 0, // Ÿ�� ����
		eTEXT_HP,		 // ��ġ ������ ��� ȿ��
		eTEXT_MAX
	};

	CUIText* m_pText[eTEXT_MAX];

	//Frame Ÿ��
	enum eFRAME_TYPE
	{
		eFRAME_NORMAL = 0, // NPC, PC ���
		eFRAME_MOB,		// �Ϲ� �� ���
		eFRAME_PMOB,	// ����Ʈ, ����, ��Ƽ �� ���
		eFRAME_MAX
	};
	
	CUIImageSplit* m_pImgSplit[eFRAME_MAX];
	CUIText* m_pStrName[eFRAME_MAX];		
	eFRAME_TYPE m_eBackGround;

	int		m_nFrameCenterWidth[eFRAME_MAX];
	int		m_nNameWidth[eFRAME_MAX];
	int		m_nAddWidthGap;
	int		m_nHpBarWidth;

	// �̹��� ��� Ÿ��
	enum eIMG_ARRAY_TYPE
	{
		eARRAY_ATTR_ATT = 0, // ���� �Ӽ�
		eARRAY_ATTR_DEF,	// ���Ӽ�
		eARRAY_SYNDICATE,	// RVR
		eARRAY_MAX
	};

	CUIImageArray* m_pImgArr[eARRAY_MAX];
};


#endif	// UI_TARGET_INFO_NEW_H_

