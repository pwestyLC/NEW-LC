#ifndef __CHARACTERTARGET_H__
#define __CHARACTERTARGET_H__


//#include <Engine/Network/NetworkMessage.h>
#include <Engine/Object/ObjectBase.h>
#include <Engine/Base/CTString.h>
#include <Engine/Interface/UIBuff.h>
#include <Engine/Entities/StatusEffect.h>
#include <Engine/Entities/ItemEffect.h>
#include <Engine/Network/ChatMsgBuffer.h>
#include <Engine/Interface/UIGuildMark.h>
#include <Engine/Contents/function/TitleData.h>

#define WEAR_COSTUME	8

#define		PLAYER_STATE_PKMODE			(1 << 3)	// PK ���
#define		PLAYER_STATE_PKMODEDELAY	(1 << 4)	// PK ��� ���� ������

class CUIGuildMarkIcon;

// FIXME : ���� ���� �ʿ�...��.��
class ENGINE_API CCharacterTarget : public ObjectBase
{
public:
	INDEX			cha_iJob2;
	SLONG			cha_pkstate;
	UWORD			cha_state;//0:��ȭ��� 1:PK��� 2: ����������.//1210
	SBYTE			cha_sbShopType;	
	SBYTE			cha_yLayer;
	SBYTE			cha_BuffCount;
	LONG			cha_lGuildIndex;		// �ӽ�	����� �ε���
	LONG			cha_lGuildLevel;		// �ӽ� ����� ����
	LONG			cha_lGuildPosition;		// �ӽ� ��忡���� ĳ������ ����
	CTString		cha_strGuildName;		// ��� ��.
	UBYTE			cha_ubGuildNameColor;	// ��� �� ����		[071123: Su-won] DRATAN_SIEGE_DUNGEON
	SBYTE			cha_sbGuildRank;		// ��� ��ũ WSS_GUILDMASTER 070517
											//  - ����̳� �̺�Ʈ�� �߰���(���� �ٸ� �뵵�� �̿� ����) 
	BOOL			cha_bExtension;			// ���� �� ���� �߰��Ȱ� ���� �ֳ�???
	BuffInfo		cha_Buff[BUFF_MAX_COUNT];
	ChatMsgBuffer	ChatMsg;		// yjpark
	ChatMsgBuffer	ShopMsg;		// yjpark
	BOOL			cha_bLegit; //�������
	CStatusEffect	cha_statusEffect;
	SLONG			cha_nChangeMobId;
	SLONG			cha_nTransformIndex;		// ����ü ID?
	CItemEffect		cha_itemEffect;
	SBYTE			cha_sbItemEffectOption;
	SLONG			cha_nFame;
	SLONG			cha_hp; //dethunter12
	SLONG			cha_maxhp; //dethunter12
	SBYTE			cha_sbJoinFlagMerac;
	SBYTE			cha_sbJoinFlagDratan;	// WSS_DRATAN_SIEGEWARFARE 070720	
	UWORD			cha_sbAttributePos;
	INDEX			cha_iPetType;			// �ֿϵ��� ����
	INDEX			cha_iPetAge;			// �ֿϵ��� ����?
	BOOL			cha_bPetRide;			// �ֿϵ����� Ÿ�� �ִ°�?

	// alan wins loses enemy
	INDEX			cha_wins;
	INDEX			cha_loses;

	INDEX			cha_reborn;
	INDEX			cha_color_name;

//	CEntity			*cha_pPet;
	//CEntity			*cha_pFirstSummon;
	//CEntity			*cha_pSecondSummon;

	SBYTE			cha_sbPresscorps;
	SLONG			cha_Label;				// [sora] Ÿ�� ��
	
	INDEX			cha_NickType;			// ȣĪ
#ifdef REZABOT
	char			cha_botting;
#endif
	INDEX			cha_CosWear[WEAR_COSTUME_TOTAL];	// �ڽ�Ƭ2 Item Index ( -1 : ����)
	INDEX			cha_itemPlus[WEAR_COSTUME_TOTAL];	// �Ϲ� ��� Plus ��ġ
	INDEX			cha_itemAccessory[WEAR_ACCESSORY_MAX]; // �Ǽ����� ����
	INDEX			cha_iSyndicateType;		// ����(RVR) �ý��� : 0 ���Ҽ�, 1 ī�̷轺, 2 ����, 3 �÷η�
	INDEX			cha_iSyndicateGrade;	// ���� ����.
	INDEX			cha_iHitType;			// 
	
	CUIGuildMarkIcon* pGuildmark;
	stCustomTitleStatForPc cha_CustomTitle;
public:
	
	/* Default constructor. */
	CCharacterTarget(void);
	/* Destructor. */
	~CCharacterTarget(void);

	CCharacterTarget(const CCharacterTarget &other);
	CCharacterTarget &operator=(const CCharacterTarget &other);
	
	void	Init(void);
	void	SetData( INDEX index, INDEX type, CTString &name, CEntity *pEntity, SBYTE sbyLayer,UWORD state,  SLONG pkstate, INDEX wins, INDEX loses, INDEX reborn, INDEX colorName);
	void	SetSyndicate(INDEX iType, INDEX iGrade);
	void	SetShopType( SBYTE sbType);
	void	SetClientChaId( INDEX index );
	void	SetyLayer( SBYTE sbyLayer ) { cha_yLayer = sbyLayer; }
	void	AddBuff( BuffInfo &rBuffInfo )
	{
		cha_Buff[cha_BuffCount++] = rBuffInfo;
	}
	void	RemoveBuff( SLONG slItemIndex, SLONG slSkillIndex );

	int		GetPkState();
	void	SetChaState(SLONG state);
	void	SetChaPkState(SLONG pkstate);
	BOOL	IsLegitimate(){ return cha_bLegit;}
	void    SetLegitimate(BOOL legit){ cha_bLegit = legit;}

	void	ChangeStatus(CTagManager* pTM, SQUAD status, CStatusEffect::eRelation rel)
	{
		if(cha_statusEffect.IsStatusChanged(status))
			cha_statusEffect.ChangeStatus(pTM, status, rel);
	}
	void	ResetStatus()
	{
		cha_statusEffect.Reset();
	}
	void	SetItemEffectOption( SBYTE sbOption ) { cha_sbItemEffectOption = sbOption; }

	int		GetSyndiType() { return cha_iSyndicateType; }
	int		GetSyndiGrade() { return cha_iSyndicateGrade; }

	int		GetShowAnotherRelicEffect();

	// wooss 070310 --------------------------------------------------------------->><<
	// kw : WSS_WHITEDAY_2007
	BOOL	IsBuff( SLONG itemIndex );
	CEffectGroup*	IsBuffBySkill( SLONG skillIndex );
};


#define CHA_PVP_STATE_PEACE		0
#define CHA_PVP_STATE_PK		1
#define CHA_PVP_STATE_RELEASE	2

#endif //__CHARACTERTARGET_H__