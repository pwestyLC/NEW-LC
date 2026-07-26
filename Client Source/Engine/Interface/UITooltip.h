#ifndef __UI_TOOLTIP_H__
#define __UI_TOOLTIP_H__

class CUIBase;
class CItems;
class CAction;
class CSkill;
class CSpecialSkill;
class CAction;

class CUIList;
class CUIImageSplit;

class CUITooltip : public CUIBase
{
public:
    CUITooltip();
    ~CUITooltip();

    enum
    {
        eCHAOS_EMPTY = 0,
        eCHAOS_FILL,
        eGENERAL_EMPTY,
        eGENERAL_FILL
    };

    void	initialize();
    void	GetTooltipSize(int& w, int& h);
	void	SetWhichUI(int nUI)	{ m_nWhichUI = nUI;	}
    bool	SetItemData(CItems* pItems, eTOOLTIP_TYPE type = eTOOLTIP_FIRST, int nWearPos = -1);
	bool	SetCashData(CItems* pItems, int nCashIndex);
	bool	SetItemEtcData(stItemEtc* pItemEtc, eUIBTN_ETC_TYPE type);
    bool	SetSkillData(CSkill* pSkill, bool bLearn = false, eTOOLTIP_TYPE type = eTOOLTIP_FIRST);
	bool	SetSSkillData(CSpecialSkill* pSSkill, bool bLearn = false, eTOOLTIP_TYPE type = eTOOLTIP_FIRST);
    bool	SetActionData(CAction* pAction, eTOOLTIP_TYPE type = eTOOLTIP_FIRST);
    bool	SetString(CUIBase* pUI);

    void	ClearData();
    int	    GetSecondPos();
	void	OnUpdate( float fDeltaTime, ULONG ElapsedTime );
private:
    void	SetIndex();

//======================================================>>
//======================================================>>
//================== ������ ���� =======================>>
//======================================================>>
//======================================================<<
	void	SetCashItemInfo();
	void	SetCashPackageItemInfo();
	void	SetAmendInfo(eUIBTN_ETC_TYPE type);		// �������� ������ �ִ� ��ġ�� ���� ����. (ex. ����ġ, ����, sp)
	void	SetAffinity(eUIBTN_ETC_TYPE type);		// ģȭ�� ����.
	void	SetWearInfo();
    void	SetName();
	void	SetCompositionInfo();	// �ɷ�ġ ���� ����.
    void	SetExpireInfo();	// �Ⱓ�� ������ ���� �ð�.
    void	SetPriceInfo();		// ����.
    void	SetRuneInfo();		// �� ����.
    void	SetReformInfo();	// ���� ����.
	void	SetCharBoundInfo(); // �ͼ� ����
    void	SetClassInfo();		// ��� ���� Ŭ���� ����.
    void    SetItemLevel();   //pwesty
    void	SetLevelInfo();		// ���� ���� ����.
    void	SetSyndicateInfo();	// ���� ����.
    void	SetPotionBuff();	// ���� ���� ������ ����.
    void	SetQuestInfo();		// ����Ʈ ����.
    void	SetDamageInfo();	// ������ ����.
    void	SetDefenceInfo();	// ��� ����.
    void	SetFlightInfo();	// ����Ʈ�ε��� ���� �ӵ�.
    void	SetPenaltyInfo();	// ����� �г�Ƽ ����.
    void	SetDurabilityInfo();// ������.
    void	SetEndureInfo();	// ����.
    void	SetFameInfo();		// ����
    void	SetUnknownInfo();	// �̰��� �ɼ�.
    void	SetPetInfo();		// ��.
    void	SetWildPetInfo();	// ���ϵ���.
    void	SetSocketInfo();	// ����.
	void	SetJewelInfo();		// ���� �ɷ�ġ
    void	SetOptionInfo();	// �ɼ�.
    void	SetBloodInfo();		// ������ �ɼ�.
    void	SetSealInfo();		// ���� ����.
    void    SetOpenBoxPrice();
    void	SetSkillInfo();		// �����ۿ� ���� ��ų ����.
    void	SetMonsterMercenaryInfo();	// ���� ī��.
    void	SetJewelDescInfo();	// ���� ����.
	void	SetItemCoolTimeInfo(bool bUpdate = false);	// ������ ��Ÿ��.
    void	SetDescInfo();		// ��ũ����.
	void	SetTitleInfo();		// ȣĪ.
	void	SetSetItemInfo();	// ��Ʈ ������ ���� ����.
	bool	SetFortuneInfo();	// ���� ����.
	void	SetSmcInfo();		// ����� ��쿡�� smc���ϸ��� �����ش�.
    void    SetItemTagText();
    void	SetItemPrice();
//======================================================>>
//======================================================>>
//================== ��ų ���� =========================>>
//======================================================>>
//======================================================<<
    void	SetSkillName();
    void	SetTypeInfo();		// �۽������� ��ų, ��� ��ų, ��Ƽ�� ��ų���� ���� ����.
    void	SetNeed4Stat();
    void	SetNeed4Skill();	// ���� ��ų.
    void	SetNeed4Item();		// �ʿ� ������.
    void	SetNeed4MPHPInfo();	// mp, hp �Ҹ�
    void	SetNeed4ItemInfo();	// �Ҹ� ������.
    void	SetNeed4GPInfo();	// �Ҹ� GP
    void	SetPowerInfo();		// ����.
    void	SetRangeInfo();		// ���� �Ÿ�.
    void	SetDurationInfo();	// ���� �ð�.
    void	SetSkillCoolTimeInfo(bool bUpdate = false);	// ���� �ð�.
    void	SetSkillDescInfo();	// ��ũ����.
    void	SetAttributeInfo();	// �Ӽ�.
	void	SetGuildSkillTarget();

//======================================================>>
//======================================================>>
//=============== ����� ��ų ���� =====================>>
//======================================================>>
//======================================================<<
	void	SetSSkillName();
	void	SetSSKillNeed4Stat();
	void	SetSSkillNeed4Skill();
	void	SetSSkillDesc();

    struct stLearnSkill
    {
        COLOR col;
        CTString str;
    };

//======================================================>>
//======================================================>>
//================== �׼� ���� =========================>>
//======================================================>>
//======================================================<<
    void	SetActionName();
    void	SetActionDescInfo();
private:

	enum eLIST_TYPE
	{
		eLIST_FIRST = 0,
		eLIST_SECOND,
		eLIST_END
	};

	// ��Ʈ �������� ��� ����Ʈ�� �ϳ� �� �ʿ��ϱ� ������ �߰�.
    CUIList*		m_pList[eLIST_END];
    // ��� �̹��� �����͸� �Ѱܹ޾Ƽ� ���.
    CUIImageSplit*	m_pImgBack;
    // ��� �̹��� ������.
    CUIImageSplit*	m_pImgTempBack[2];
    CItems*			m_pItem;
    CItemData*		m_pItemData;
	stItemEtc*		m_pItemEtc;

    CSkill*			m_pSkill;
	CSpecialSkill*	m_pSSkill;
    CAction*		m_pAction;

    CUIBase*		m_pUI;

    eTOOLTIP_TYPE	m_eType;
    int				m_nIndex;
    int				m_nSkillLv;
    bool			m_bSkillLearn;

    int				m_nSecondPos;
	int				m_nListOriWidth;
	int				m_nCooltimePos;
	int				m_nWhichUI;

	void AddText(CTString str, COLOR col = 0xFFFFFFFF, eALIGN_H alingn = eALIGN_H_LEFT, eLIST_TYPE eType = eLIST_FIRST, int nMaxChar = 0);
    void UpdateTooltip(CUIImageSplit* pBackGround);

	int calc_pet_item_plus(int orig_value, ULONG plus);
};

#endif // __UI_TOOLTIP_H__