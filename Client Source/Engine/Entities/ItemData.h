#ifndef INCL_ITEMDATA_H
#define INCL_ITEMDATA_H
#ifdef PRAGMA_ONCE
#pragma once
#endif

#include <Engine/LocalDefine.h>
#include <Engine/GlobalDefinition.h>
#include <vector>
#include <map>
#include <Engine/Base/CTString.h>
#include <Common/CommonDef.h>
#include <Common/header/def_item.h>
#include <Common/header/def_option.h>
#include <Engine/Help/LoadLod.h>

#define		MAX_MAKE_ITEM_MATERIAL		10	// ������ ���۽� �ִ� ��� ��

// Item Proto flag
#define		ITEM_FLAG_COUNT			((LONGLONG)1 << 0)	// �� �� �ִ� �������ΰ�
#define		ITEM_FLAG_DROP			((LONGLONG)1 << 1)	// ���  ���� �������ΰ���
#define		ITEM_FLAG_UPGRADE		((LONGLONG)1 << 2)	// ���׷��̵� ������ �������ΰ�
#define		ITEM_FLAG_EXCHANGE		((LONGLONG)1 << 3)	// ��ȯ ���� �������ΰ��� (������)
#define		ITEM_FLAG_TRADE			((LONGLONG)1 << 4)	// �Ÿ� ���� �������ΰ���
#define		ITEM_FLAG_NOT_DELETE	((LONGLONG)1 << 5)	// �ı� ���� �������ΰ���
#define		ITEM_FLAG_MADE			((LONGLONG)1 << 6)	// ���� ���� �������ΰ���
#define		ITEM_FLAG_MIX			((LONGLONG)1 << 7)	// ���� ������ : DB�� ����ȵ�
#define		ITEM_FLAG_CASH			((LONGLONG)1 << 8)	// ���� ������
#define		ITEM_FLAG_LORD			((LONGLONG)1 << 9)	// ���� ���� ������
#define		ITEM_FLAG_NO_STASH		((LONGLONG)1 << 10)	// â�� ���� �Ұ��� ������
#define		ITEM_FLAG_CHANGE		((LONGLONG)1 << 11)	// �ٸ� ������ ���������� ��ȯ ���� ���� //wooss 051217
#define		ITEM_FLAG_COMPOSITE		((LONGLONG)1 << 12)	// ������ �ռ� ���� ����
#define		ITEM_FLAG_DUPLICATION	((LONGLONG)1 << 13)	// �ߺ� ��� ����
#define		ITEM_FLAG_LENT			((LONGLONG)1 << 14)	// �뿩�� ����
#define		ITEM_FLAG_RARE			((LONGLONG)1 << 15)	// ���� ������
#define		ITEM_FLAG_ABS			((LONGLONG)1 << 16)	// �������� ���� �ð� ���� ����
#define		ITEM_FLAG_NOT_REFORM	((LONGLONG)1 << 17)	// ������ ���� ���� ����
#define		ITEM_FLAG_ZONEMOVE_DEL	((LONGLONG)1 << 18)	// �� �̵��� ������� ������
#define     ITEM_FLAG_ORIGIN		((LONGLONG)1 << 19)	// �������� �ɼ�(SET_ITEM_ADD [ttos_2009_5_22]: ��Ʈ ������ ����)
#define		ITEM_FLAG_TRIGGER		((LONGLONG)1 << 20)	// Ʈ���� [090707: selo]
#define		ITEM_FLAG_RAIDSPE		((LONGLONG)1 << 21)	// ���̵� ����� ������ [090707: selo]
#define		ITEM_FLAG_QUEST			((LONGLONG)1 << 22)	// ����Ʈ ������ [090616: selo]
#define		ITEM_FLAG_BOX			((LONGLONG)1 << 23)	// LuckyDrawBox
#define		ITEM_FLAG_NOTTRADEAGENT	((LONGLONG)1 << 24)	// �ŷ������ϺҰ�
#define		ITEM_FLAG_DURABILITY	((LONGLONG)1 << 25)	// ������ ������
#define		ITEM_FLAG_COSTUME2		((LONGLONG)1 << 26)	// �ڽ�Ƭ2 ������
#define		ITEM_FLAG_SOCKET		((LONGLONG)1 << 27)	// socket flag. [6/22/2010 rumist]
#define		ITEM_FLAG_SELLER		((LONGLONG)1 << 28)		// [2010/08/27 : Sora] ADD_SUBJOB �����߰�
#define		ITEM_FLAG_CASTLLAN		((LONGLONG)1 << 29)		// ���ָ� ���� ������ ������
#define		ITEM_FLAG_NONRVR		((LONGLONG)1 << 31)	// RVR�� ��� ��� �Ұ� ������ �÷���.
#define		ITEM_FLAG_QUESTGIVE		((LONGLONG)1 << 32)	// ����Ʈ ��� ���� ������
#define		ITEM_FLAG_TOGGLE		((LONGLONG)1 << 33)	// ��� ������.
#define		ITEM_FLAG_COMPOSE		((LONGLONG)1 << 34)	// �ռ� ������.
#define		ITEM_FLAG_NOTSINGLE		((LONGLONG)1 << 35) // �̱� �������� ��� �Ұ�.
#define		ITEM_FLAG_INVISIBLE_COSTUME ((LONGLONG)1 << 36)	// ���� �ڽ�Ƭ
#define     ITEM_FLAG_PHOENIX  ((LONGLONG)1 << 37)	

// Item Flag : �ֻ��� 1��Ʈ�� ��� �Ұ�!!! 
// 6��Ʈ���� �ɸ�, ��, �Ϲ� ���ü��� ������, �÷�Ƽ�� ���ü��� �ٸ� �������� ������ ��� 
#define		PLATINUM_MAX_PLUS 127 
#define		FLAG_ITEM_PLATINUM_GET(a, b) (b = a & PLATINUM_MAX_PLUS) 
#define		FLAG_ITEM_PLATINUM_SET(a, b) (a = ( (a &~ PLATINUM_MAX_PLUS) | b )) 
#define		FLAG_ITEM_OPTION_ENABLE			(1 << 7)	// ������ �÷��׿� �ɼ��� ���� �� �ִ� ���¸� ����, Bit ����
#define		FLAG_ITEM_SEALED				(1 << 8)	// ������ ����
#define		FLAG_ITEM_SUPER_STONE_USED		(1 << 9)	// ���۰����� ���׷��̵� ����..//0627
#define		FLAG_ITEM_BOOSTER_ADDED			(1 << 10)	// �ν��� ���� ����
#define		FLAG_ITEM_SILVERBOOSTER_ADDED	(1 << 11)	// �ǹ� �ν��� ���� ����
#define		FLAG_ITEM_GOLDBOOSTER_ADDED		(1 << 12)	// ��� �ν��� ���� ����
#define		FLAG_ITEM_PLATINUMBOOSTER_ADDED	(1 << 13)	// �÷�Ƽ�� �ν��� ���� ����
#define		FLAG_ITEM_COMPOSITION			(1 << 14)	// �ռ� ������ ���� ����
#define		FLAG_ITEM_LENT					(1 << 15)	// �뿩�� ������
#define		FLAG_ITEM_LEVELDOWN				(1 << 16)	// ���� �ٿ�� ������
#define		FLAG_ITEM_BELONG				(1 << 17)	// �ͼ� ������ �ͼ� ����(SET_ITEM_ADD [ttos_2009_5_22]: ��Ʈ ������ ����)
#define		FLAG_ITEM_SOCKET				(1 << 18)	// ���� �����ߴ��� ���� [5/10/2010 rumist]
#define		FLAG_ITEM_SUPER_RUNE_USED		(1 << 19)	// ���̰� ��û���� ���� �ʰ��� �� ������ �÷��� [8/24/2012 ����] 
#define		FLAG_ITEM_TRANSMOGRIFY			(1 << 20)
#define     FLAG_ITEM_OPAL_MINUS_USED       (1 << 21)
#define     FLAG_ITEM_ENCHANTED_USED	    (1 << 22)
// SOCKET_SYSTEM_S2 ���� ���� ��ġ ���� [4/2/2013 Ranma]
#define		JEWEL_COMPOSITE_POSITION_WEAPON		(1 << 0)
#define		JEWEL_COMPOSITE_POSITION_HELMET		(1 << 1)
#define		JEWEL_COMPOSITE_POSITION_ARMOR		(1 << 2)
#define		JEWEL_COMPOSITE_POSITION_PANTS		(1 << 3)
#define		JEWEL_COMPOSITE_POSITION_GLOVES		(1 << 4)
#define		JEWEL_COMPOSITE_POSITION_SHOES		(1 << 5)
#define		JEWEL_COMPOSITE_POSITION_SHIELD		(1 << 6)
#define		JEWEL_COMPOSITE_POSITION_BACKWING	(1 << 7)

//SET_ITEM_ADD				//[ttos_2009_5_22]: ��Ʈ ������ ����
#define MAX_SET_OPTION  11
#define MAX_ITEM_SKILL			3			// ��Ʈ �������� �ִ� ��ų 
#define RUNE_ITEM_LEVEL			146			// �� ���� �����۷���		

struct ItemSmcParseInfo 
{
	INDEX	iItemIndex;
	INDEX	iCount;
	INDEX	iTexCnt[3];
	CTString BmFileName[3];
	CTString ItemTEXFileName[3];
	CTString ItemTEXNormalFileName[3];

	ItemSmcParseInfo() : iItemIndex(0),iCount(0) 
	{
		iTexCnt[0] = 0; iTexCnt[1] = 0; iTexCnt[2];
	}
};

struct sPetItem_Info 
{
	//���� �� ������
	CTString	pet_name;
	INDEX		pet_index;
	INDEX		pet_level;
	INDEX		pet_str;
	INDEX		pet_con;
	INDEX		pet_dex;
	INDEX		pet_int;
	INDEX		pet_cooltime;
	__int64		pet_accexp;
};

struct JewelComosInfo
{
	int index;
	int nor_comp_nas;
	int ca_comp_nas;
	int ca_jew_create;
	int nor_comp_val;
	int ca_comp_val;
	int nor_up_2;
	int nor_up_3;
	int ca_up_2;
	int ca_up_3;
	int nor_down_1;
	int nor_down_2;
	int nor_down_3;
	int ca_down_1;
	int ca_down_2;
	int ca_down_3;
};

class CFortuneData : public stFortune, public LodLoader<CFortuneData>
{
public:
	static bool loadFortuneEx(const char* FileName);
};

class ENGINE_API CItemData : public stItem, public LodLoader<CItemData>
{
private:
	// ITEM ������ ����ϰ� �ִ� ����ü
	// CItemData�� ���ο����� ���˴ϴ�.
	int transFlag;
	std::string name;		// ������ �̸�.
	std::string descr;		// ����.

	//0601 kwon �߰�.
	char	fileBm[255];
	char	fileTex[255];
	char	fileTexNormal[255];
	char	fileBm2[255];
	char	fileTex2[255];
	char	fileTex2Normal[255];
	char	fileBm3[255];
	char	fileTex3[255];
	char	fileTex3Normal[255];
	int		Item_MeshCnt;
	int		Item_TexCnt;
	int		Item_Tex2Cnt;
	int		Item_Tex3Cnt;
	BOOL	bCreateSet;
	
public:
	DOUBLE	StartTime;

	enum ITEMTYPE
	{
		ITEM_WEAPON			= 0,	// ����
		ITEM_SHIELD			= 1,	// ��
		ITEM_ONCEUSE		= 2,	// ��ȸ��
		ITEM_BULLET			= 3,	// źȯ
		ITEM_ETC			= 4,	// ��Ÿ
		ITEM_ACCESSORY		= 5,	// �Ǽ�����
		ITEM_POTION			= 6,	// ����			// Date : 2005-01-07,   By Lee Ki-hwan
	};

	enum ITEMWEAPONTYPE
	{
		ITEM_WEAPON_KNIFE	= 0,	// ��絵(����Ʈ)
		ITEM_WEAPON_CROSSBOW= 1,	// ����(�α�)
		ITEM_WEAPON_STAFF	= 2,	// ������(������)
		ITEM_WEAPON_BIGSWORD= 3,	// ���(Ÿ��ź)
		ITEM_WEAPON_AXE		= 4,	// ����(Ÿ��ź)
		ITEM_WEAPON_SSTAFF	= 5,	// ��������(������)
		ITEM_WEAPON_BOW		= 6,	// Ȱ(����)
		ITEM_WEAPON_DAGGER	= 7,	// �ܰ�(�α�)
		ITEM_WEAPON_MINING	= 8,	// ä������
		ITEM_WEAPON_GATHERING= 9,	// ä������
		ITEM_WEAPON_CHARGE	= 10,	// ��������
		ITEM_WEAPON_TWOSWORD= 11,	// �̵���(����Ʈ)
		ITEM_WEAPON_WAND	= 12,	// �ϵ�(����)
		ITEM_WEAPON_SCYTHE	= 13,	// ���̵�
		ITEM_WEAPON_POLEARM	= 14,	// ����.		
		ITEM_WEAPON_SOUL	= 15,	// ȥ(����Ʈ������)
	};

	// źȯ ����
	enum ITEMBULLETTYPE
	{
		ITEM_BULLET_ATTACK	= 0,	// Attack Bullet
		ITEM_BULLET_MANA	= 1,	// Mana Bullet
		ITEM_BULLET_ARROW	= 2,	// Arrow
	};

	// ��Ÿ Ÿ��
	enum ITEMETCTYPE
	{
		ITEM_ETC_QUEST			= 0,	// ����Ʈ
		ITEM_ETC_EVENT			= 1,	// �̺�Ʈ
		ITEM_ETC_SKILL			= 2,	// ��ų ����
		ITEM_ETC_REFINE			= 3,	// ����
		ITEM_ETC_MATERIAL		= 4,	// ���.
		ITEM_ETC_MONEY			= 5,	// ��
		ITEM_ETC_PRODUCT		= 6,	// ����ǰ
		ITEM_ETC_PROCESS		= 7,	// ����ǰ
		ITEM_ETC_OPTION			= 8,	// �ɼ� ������
		ITEM_ETC_SAMPLE			= 9,	// �÷�
		// 10���� Texture���̱� ���ؼ� ���.
		IETC_MIX_TYPE1			= 11, // ��������1
		IETC_MIX_TYPE2			= 12, // ��������2
		IETC_MIX_TYPE3			= 13, // ��������3
		ITEM_PET_AI				= 14,	// �� AI
		ITEM_ETC_QUESTTRIGGER	= 15,	// quest trigger. server used only.
		// ������ ����ϴ� ����Ʈ Ʈ����
		ITEM_ETC_JEWEL			= 16,	// jewels in socket system.
		ITEM_ETC_STABILIZER		= 17,	// stabilize about jewels combine.
		ITEM_ETC_PROC_SCROLL	= 18,	// process about socket creation.	
		ITEM_ETC_MONSTER_MERCENARY_CARD = 19, // ���� �뺴 ī��
		ITEM_ETC_GUILD_MARK		= 20,	// [sora] GUILD_MARK
		ITEM_ETC_REFORMER		= 21, //���� ������
		ITEM_ETC_CHAOSJEWEL		= 22,
		ITEM_ETC_FUNCTIONS		= 23, // ��ɼ� ������
		ITEM_ETC_SYNDICATEJEWEL = 24, // ���� â���� ���� ������
	};

	enum ITEMREFORMERTYPE
	{
		ITEM_ETC_REFORMER_MID_GRADE		= 0,
		ITEM_ETC_REFORMER_HIGH_GRADE	= 1,
	#ifdef PREMIUM_REFORMER_11072021
		ITEM_ETC_MEGA_REFORMER_GRADE	= 2,
	#endif
	};

	// �ɼ� ������ ����.
	enum ITEMOPTIONTYPE
	{
		ITEM_OPTION_BLOOD	= 0,	// Blood Item
		ITEM_OPTION_CLEAR	= 1,	// Clear Item
	};

	// �� ����.
	enum ITEMSHIELDTYPE
	{
		ITEM_SHIELD_HEAD	= 0,	// �Ӹ�
		ITEM_SHIELD_COAT	= 1,	// ����
		ITEM_SHIELD_PANTS	= 2,	// ����
		ITEM_SHIELD_GLOVE	= 3,	// �尩
		ITEM_SHIELD_SHOES	= 4,	// �Ź�
		ITEM_SHIELD_SHIELD	= 5,	// ����	
		ITEM_SHIELD_BACKWING = 6,	// ����
		ITEM_SHIELD_ONE_SUIT  = 7,   // �� �� �ǻ� added by sam 11/01/31 [SAM]		
	};

	// ��ȸ��
	enum ITEMSUBTYPE		// Date : 2005-01-07,   By Lee Ki-hwan : ���� ����
	{
		ITEM_SUB_WARP			= 0,// ����
	
		// ���� �ý���
		ITEM_SUB_PROCESS_DOC		= 1,	// ���� ����
		ITEM_SUB_MAKE_TYPE_DOC		= 2,	// ���� ����, ���� ����
		ITEM_SUB_BOX				= 3,	// ����
		ITEM_SUB_MAKE_POTION_DOC	= 4,	// ���� ���� ���� // Date : 2005-01-07,   By Lee Ki-hwan
		ITEM_SUB_CHANGE_DOC			= 5,
		ITEM_SUB_QUEST_SCROLL		= 6,
		ITEM_SUB_CASH_ITEM			= 7,	// ��ȸ�� ĳ��������
		ITEM_SUB_ETC				= 9,	// ��Ÿ ��ȸ
		ITEM_SUB_TARGET				= 10,	// Ÿ�� �����ۿ�
		ITEM_SUB_TITLE				= 11,	// ȣĪ ������
		ITEM_SUB_JUMPING_PAKAGE		= 12,	// ���� ��Ű�� : ����ϸ� ���� ���ǰ� ���� �������� �������ش�.
		ITEM_SUB_JUMPING_POTION		= 13,	// ���� ���� : ����ϸ� ĳ���� ������ Ư�� ������ �÷��ִ� ������
		ITEM_SUB_CHAR_SLOT_EXTEND	= 14,	// ĳ���� ���� Ȯ��
		ITEM_SUB_CHAR_SERVER_MOVE	= 15,	// ĳ���� ���� ���� [Ranma]
		ITEM_SUB_EXPRESS_REMOTE		= 16,	// LCE ���� 
		ITEM_SUB_JEWEL_POCKET		= 17,	// �Ϲ� ���� �ָӴ�
		ITEM_SUB_CHAOS_JEWEL_POCKET	= 18,	// ī���� ���� �ָӴ�
		ITEM_SUB_INVEN_CASH_BAG_KEY	= 19,	// ĳ�� �κ��丮 ���� ������.
		ITEM_SUB_PET_STASH_USE_ITEM = 20,	// �� â�� �̿��
		ITEM_SUB_GPS				= 21,	// GPS
		ITEM_SUB_HOLY_WATER			= 22,	// ���� ������.
		ITEM_SUB_PROTECT_PVP		= 23,	// PVP ��������.
		ITEM_SUB_SEAL				= 24,
	};

	enum ACCESSORYTYPE
	{
		ACCESSORY_CHARM			= 0,	// ����
		ACCESSORY_MAGICSTONE	= 1,	// ���ü�
		ACCESSORY_LIGHTSTONE	= 2,	// ��¦�̴µ�
		ACCESSORY_EARING		= 3,	// �Ͱ���.
		ACCESSORY_RING			= 4,	// ����
		ACCESSORY_NECKLACE		= 5,	// �����
		ACCESSORY_PET			= 6,	// ��
		ACCESSORY_WILDPET		= 7,	// ������ ��
		ACCESSORY_RELIC			= 8,	// ����
	};

	// SubType : ����  // Date : 2005-01-07,   By Lee Ki-hwan
	enum POTIONTYPE
	{
		POTION_STATE	= 0,	// �����̻�ġ��
		POTION_HP		= 1,	// ����ȸ��
		POTION_MP		= 2,	// ����ȸ��
		POTION_DUAL		= 3,	// HP+MP ȸ��
		POTION_STAT		= 4,	// Stat ���
		POTION_ETC		= 5,	// ��Ÿ (�̵����)	
		POTION_UP		= 6,	// �������
		POTION_TEARS	= 7,	// ����
		POTION_CRYSTAL	= 8,	// ����
		POTION_POTAL_SCROLL = 9, // NPC��Ż ��ũ��
		POTION_INC_HEAL_HP, // HP ȸ���ӵ� ����.
		POTION_INC_HEAL_MP, // MP ȸ���ӵ� ����.
		POTION_PET_HEAL_HP,		// �� HPȸ��.
		POTION_INC_PET_MOVE_SPD, // �� �̵��ӵ� ����.
		POTION_TOTEM,			// ���� ������.
		POTION_PET_HEAL_MP		// �� MPȸ��
	};

	enum POTIONSUBTYPE_UP
	{
		POTION_UP_PHYSICAL	= 0,	// ����
		POTION_UP_MAGIC		= 1,	// ����
		POTION_UP_ATTACK	= 0,	// ����
		POTION_UP_DEFENSE	= 1,	// ���
	};

	// IONCE_PROCESS_DOC ���� 1
	enum PROCESSDOCTYPE
	{
		PROCESS_DOC_STONE		= 0,   // ���� ���� ����
		PROCESS_DOC_PLANT		= 1,   // �Ĺ� ���� ����
		PROCESS_DOC_ELEMENT		= 2,   // ���� ���� ����
	};

	// ���� ���� ���� ����
	enum PROCESSDOCSUBTYPE_STONE 
	{
		PROCESS_DOC_SUB_STONE0	= 0,		// ���� �� ���� ����
		PROCESS_DOC_SUB_STONE1	= 1,		// ���� ���� ���� ����
		PROCESS_DOC_SUB_STONE2	= 2,		// ���� ���� ���� ����
		PROCESS_DOC_SUB_STONE3	= 3,		// ���� ��Ʈ ���� ����
		PROCESS_DOC_SUB_STONE4	= 4,		// ���� ������ ���� ����
	};
	
	// �Ĺ� ���� ���� ����
	enum PROCESSDOCSUBTYPE_PLANT
	{
		PROCESS_DOC_SUB_PLANT0	= 0,		// ũ���� ����� ���� ����
		PROCESS_DOC_SUB_PLANT1	= 1,		// ũ���� �ٱ� ���� ����
		PROCESS_DOC_SUB_PLANT2	= 2,		// ũ���� �Ķ��� ���� ����
		PROCESS_DOC_SUB_PLANT3	= 3,		// ũ���� ���� ���� ����
		PROCESS_DOC_SUB_PLANT4	= 4,		// ũ���� �� ���� ����
	};

	// ���� ���� ���� ����
	enum PROCESSDOCSUBTYPE_ELEMENT
	{
		PROCESS_DOC_SUB_ELEMENT0	= 0,	// E��� ���� ���� ����
		PROCESS_DOC_SUB_ELEMENT1	= 1,	// D��� ���� ���� ����
		PROCESS_DOC_SUB_ELEMENT2	= 2,	// C��� ���� ���� ����
		PROCESS_DOC_SUB_ELEMENT3	= 3,	// B��� ���� ���� ����
		PROCESS_DOC_SUB_ELEMENT4	= 4,	// A��� ���� ���� ����
	};

	// ONCE_BOX  ���� // Date : 2005-01-12,   By Lee Ki-hwan
	enum BOXTYPE
	{
		BOX_REMAKE		= 0,		// ��Ȱ�ǻ���
		BOX_ARCANE		= 1,		// ����ǻ���
	};

	enum REFINE_TYPE // Date : 2005-01-12,   By Lee Ki-hwan
	{
		REFINE_GENERAL	= 0,		// �Ϲ����ü�
		REFINE_SPECIAL	= 1,		// �������ü�
		REFINE_SUPER_SPECIAL = 2,	// �ʰ������ü�
		REFINE_BOOSTER	= 3,		// �ν���
		REFINE_LUCKY	= 4,		// ����� ���� ���ü�
		REFINE_PLATINUM	= 5,		// �÷�Ƽ�� ���ü�
		REFINE_CHAOS	= 6,		// Ư�� ���ü�
		REFINE_PURITY_RUNE = 7,		// ��ȭ�� ��
		REFINE_DEVIL_RUNE = 8,		// �Ǹ��� �� 
		REFINE_CHAOS_RUNE = 9,		// ī���� �� [8/24/2012 ����] 
		REFINE_SUPER_RUNE = 10,		// �ʰ��� ��
		REFINE_LUCKY_RUNE = 11,		// ��� ��
		REFINE_OPAL_RUNE = 12,
		REFINE_LETSPLAY_RUNE = 13,
		REFINE_ENCHANT_RUNE	=	14
	};

	enum LORD_ITEM_TYPE
	{
		LORD_ITEM_BIGSWORD	= 0,	// ���(Ÿ��ź)
		LORD_ITEM_AXE		= 1,	// ����(Ÿ��ź)
		LORD_ITEM_KNIFE		= 2,	// ��絵(����Ʈ)
		LORD_ITEM_TWOSWORD	= 3,	// �̵���(����Ʈ)
		LORD_ITEM_BOW		= 4,	// Ȱ(����)
		LORD_ITEM_WAND		= 5,	// �ϵ�(����)
		LORD_ITEM_SSTAFF	= 6,	// ��������(������)
		LORD_ITEM_STAFF		= 7,	// ������(������)
		LORD_ITEM_DAGGER	= 8,	// �ܰ�(�α�)
		LORD_ITEM_CROSSBOW	= 9,	// ����(�α�)
		LORD_ITEM_SCYTHE    = 10,   // ���̵�(�Ҽ���)
		LORD_ITEM_POLARM    = 11,	// ����(�Ҽ���)
		LORD_ITEM_TOTAL		= 12
	};

	// AI ���� ����
	enum PET_AI_SET0 
	{
		PET_AI_RANGE_3M		= 1,		
		PET_AI_RANGE_5M		= 2,		
		PET_AI_RANGE_10M	= 3,
		PET_AI_RANGE_20M	= 4,
		PET_AI_RANGE_30M	= 5,
	};
	// AI ���μ���
	enum PET_AI_SET1
	{
		PET_AI_HP		= 1,
		PET_AI_MP		= 2,
		PET_AI_STM		= 3,
		PET_AI_FAITH	= 4,
	};

	// AI ���μ��� ����( %���� )
	enum PET_AI_SET2
	{
		PET_AI_PERCENT_99	= 1,
		PET_AI_PERCENT_90	= 2,
		PET_AI_PERCENT_80	= 3,
		PET_AI_PERCENT_70	= 4,
		PET_AI_PERCENT_60	= 5,
		PET_AI_PERCENT_50	= 6,
	};

	// AI ���� Ÿ��
	enum PET_AI_SET3
	{
		PET_AI_OWNER_ATTACK_ENEMY	= 1,	// ������ �����ϴ� ��
		PET_AI_ENEMY_ATTACK_OWNER	= 2,	// ������ �����ϴ� ��
		PET_AI_ENEMY_ATTACK_PET		= 3,	// ���� �����ϴ� ��
		PET_AI_ENEMY				= 4,	// ��
		PET_AI_PET					= 5,	// ��
		PET_AI_OWNER				= 6,	// ����
		PET_AI_ITEM					= 7,	// ������
	};

	// ������ ITEM ���
	enum eCASTLE_WAR
	{
		eANYWHERE = 0,		//	0	��𼭵� ��� ����
		eSIEGEAREA_ALL,		//	1	��ü ���������� ��� ����
		eSIEGEAREA_MERAC,	//	2	�޶�ũ ���������� ��� ����
		eSIEGEAREA_DRATAN,	//	3	���ź ���������� ��� ����
	};
	
	/* Default constructor. */
	CItemData(void);
	/* Destructor. */
	~CItemData(void);

	CItemData& operator = (const CItemData& data);

	//----------------------------------------------------
	// Properties
	// - ItemData�� ItemTool���� ������ �����͸� �޾Ƽ� ó���ϴµ�,
	// - ���� ���ο��� �����Ͱ� ����� ���� ���� ���� ���̴�.
	// - ����, ���Ŀ��� ������Ƽ �Լ��� ���� �ִ� �ͺ��ٴ� ����ü�� 
	// - public���� �����ϴ°� ������.	
	// - �ƴϸ�, ItemData ����ü�� ��ȯ�ϴ� �͵� ������ ������...
	// - ����, ���� ������ �����Ͱ� ����� ���� �����Ƿ�, Set �޼ҵ���� �ʿ䰡 ������...
	//----------------------------------------------------	

	// �̱� ��� ����.
	inline BOOL IsExclusiveSingleMode()
	{	return FALSE; };

	inline BOOL	CanUse(int iPlayerID)	
	{	return ( job & (1 << iPlayerID) );	};
	
	inline BOOL IsProductionItem()
	{
		return ( subType == ITEM_WEAPON_MINING ||
			subType == ITEM_WEAPON_GATHERING ||
			subType == ITEM_WEAPON_CHARGE );
	}

	inline void SetItemSmcFileName(const char* FileName)
	{	strcpy(fileSMC, FileName);}

	inline void SetArmorEffectName(const char* FileName)
	{	strcpy(efffectName, FileName);	}

	inline void SetItemBMFileName(const char* FileName)
	{	strcpy(fileBm, FileName);}
	
	inline void SetItemTEXFileName(const char* FileName)
	{	strcpy(fileTex, FileName);}
	
	inline void SetItemTEXNormalFileName(const char* FileName)
	{	strcpy(fileTexNormal, FileName);}
	
	inline void SetItemBM2FileName(const char* FileName)
	{	strcpy(fileBm2, FileName);}
	
	inline void SetItemTEX2FileName(const char* FileName)
	{	strcpy(fileTex2, FileName);	}
	
	inline void SetItemTEX2NormalFileName(const char* FileName)
	{	strcpy(fileTex2Normal, FileName);}

	inline void SetItemBM3FileName(const char* FileName)
	{	strcpy(fileBm3, FileName);}
	
	inline void SetItemTEX3FileName(const char* FileName)
	{	strcpy(fileTex3, FileName);	}
	
	inline void SetItemTEX3NormalFileName(const char* FileName)
	{	strcpy(fileTex3Normal, FileName);}
	
	inline void SetMeshCnt(int Index)
	{	Item_MeshCnt = Index;}
	
	inline void SetTexCnt(int Index) //ù��° �޽��� �ؽ��� ī��Ʈ.
	{	Item_TexCnt = Index;}
	
	inline void SetTex2Cnt(int Index) //�ι�° �޽��� �ؽ��� ī��Ʈ.
	{	Item_Tex2Cnt = Index;}
	
	inline void SetTex3Cnt(int Index) //����° �޽��� �ؽ��� ī��Ʈ.
	{	Item_Tex3Cnt = Index;}
	
	inline void SetCreateSet(BOOL bSet)
	{ bCreateSet = bSet; }

	//--------------------------------------------------------------
	inline const char* GetItemSmcFileName()
	{	return fileSMC;}

	inline const char* GetArmorEffectName()
	{	return efffectName;	}

	inline const char* GetMissileShotEffect()
	{	return attackEffectName; }

	inline const char* GetShotHitEffect()
	{	return damageEffectName;	}
	
	inline const char* GetItemBMFileName()
	{	return fileBm;}
	
	inline const char* GetItemTEXFileName()
	{	return fileTex;}
	
	inline const char* GetItemTEXNormalFileName()
	{	return fileTexNormal;}
	
	inline const char* GetItemBM2FileName()
	{	return fileBm2;}
	
	inline const char* GetItemTEX2FileName()
	{	return fileTex2;}
	
	inline const char* GetItemTEX2NormalFileName()
	{	return fileTex2Normal;}

	inline const char* GetItemBM3FileName()
	{	return fileBm3;}
	
	inline const char* GetItemTEX3FileName()
	{	return fileTex3;}
	
	inline const char* GetItemTEX3NormalFileName()
	{	return fileTex3Normal;}
	
	inline __int64 GetFlag()		const
	{	return flag;}

	inline bool IsFlag( __int64 nFlag ) const 
	{
		if( flag & nFlag ) return true;
		return false;
	}

	inline BOOL GetCreateSet( void ) const
	{ return bCreateSet; }
	
	inline int GetMeshCnt()		const
	{	return Item_MeshCnt;}
	
	inline int GetTexCnt()		const
	{	return Item_TexCnt;}
	
	inline int GetTex2Cnt()		const
	{	return Item_Tex2Cnt;}

	inline int GetTex3Cnt()		const
	{	return Item_Tex3Cnt;}
	
	inline int	GetNum0() const		
	{	return num0;	}

	inline int	GetNum1() const		
	{	return num1;	}

	inline int	GetNum2() const		
	{	return num2;	}

	inline int	GetNum3() const		
	{	return num3;	}

	inline int GetItemIndex()	const
	{	return index;	}
	
	inline int GetGrade()		const
	{	return num2;}

	inline int GetJob()			const
	{	return job; }

	inline int GetLevel()		const
	{	return level;	}
	inline int GetStack() const { return stack;	}

	inline int GetFame()		const
	{	return fame;	}
	
	// ���� ��ġ�� ��ȯ�մϴ�.
	inline int GetWearingPosition()	const
	{	return wearing;}
	
	inline int	GetType()		const
	{	return type;	}
	
	inline int	GetSubType()	const
	{	return subType;	}
	
	inline int	GetZoneNum()	const
	{	return num1;	}

	inline int	GetExtraNum()	const
	{	return num2;	}

	inline int	GetQuestNum()	const
	{	return	num0;	}

	inline int	GetPetType()	const
	{	return num0;	}
	
	inline int	GetPrice()		const
	{	return price;}

	inline int	GetProcessType()	const		// ���� Ÿ��
	{	return num0;	}

	inline int	GetProcessSubType()	const		// ���� Ÿ��
	{	return num1;	}

	inline int	GetProductType()	const		// ���� Ÿ��
	{	return num0;	}

	inline int	GetProductSubType()	const		// ���� ���� Ÿ��
	{	return num1;	}

	inline int	GetProcessSkill()	const		// ���� ��ų
	{	return num2;	}

	inline int	GetBoxType()	const		// Box type
	{	return num0;	}

	inline int	GetRefineType()	const		// Refinetype type
	{	return num0;	}

	inline int GetMakePotionCount () const 
	{	return num3;	}

	inline int	GetNeedItemIndex( int nIndex )	const	
	{	return needItemIndex[nIndex];	}

	inline int	GetNeedItemCount( int nIndex )	const
	{	return needItemCount[nIndex];	}

	inline int	GetNeedSSkillIndex()	const
	{	return needSSkillIndex;	}

	inline int	GetNeedSSkillCount()	const
	{	return needSSkillCount;	}

	inline int	GetNeedSSkillIndex2()	const
	{	return needSSkillIndex2;	}

	inline int	GetNeedSSkillCount2()	const
	{	return needSSkillCount2;	}
	
	inline int	GetPhysicalDefence()	const
	{	return num0;	}
	
	int	GetPhysicalAttack();		// ���� ���� �۾� �߰��� �Ϲ� �Լ��� ��ȯ 
	int	GetMagicAttack();
		
	inline int	GetMagicDefence()		const
	{	return num1;	}
	
	inline int	GetAttackSpeed()		const
	{	return num2;}
	
	inline int	GetRecoverSec()			const
	{	return num0;		}

	inline int	GetRecoverHP()			const
	{	return num1;	}
	
	inline int	GetRecoverMP()			const
	{	return num2;	}
	
	inline int	GetSkillType()			const
	{	return num0;	}
	
	inline int	GetSkillLevel()			const
	{	return num1;}

	inline int	GetOptionType()			const
	{	return num0;}
	
	inline const char* GetName()
	{	return name.c_str();	}

	inline void SetName(const char* str)	{ name = str; }

	inline const char* GetDesc()
	{	return descr.c_str();	}

	inline void SetDesc(const char* str)	{ descr = str; }

	inline int	GetWarpType() const 
	{ return num0; }
	
	inline int GetIconTexID()			const
	{	return textureID;}
	
	inline int GetIconTexRow()			const
	{	return textureRow;}
	
	inline int GetIconTexCol()			const
	{	return textureCol;	}

	inline int GetPetAISet0() const // SOCKET_SYSTEM_S2 ���� ������ ��� ���� ��ġ�� �Ѿ�� [4/2/2013 Ranma]
	{ return set0; }

	inline int GetPetAISet1() const
	{ return set1; }

	inline int GetPetAISet2() const
	{ return set2; }

	inline int GetPetAISet3() const
	{ return set3; }

	//SET_ITEM_ADD				//[ttos_2009_5_22]: ��Ʈ ������ ����
	inline int GetSetItemIndex() const
	{ return set4; }


	// [090608: selo] ����Ʈ ������ ��� ����
	inline int GetRestrictionZoneNo() const		// ������� �� ��ȣ
	{ return set0; }

	inline int GetRestrictionPosX() const		// ������� X��ǥ
	{ return set1; }

	inline int GetRestrictionPosY() const		// ������� Y��ǥ
	{ return set3; }

	inline int GetRestrictionPosZ() const		// ������� Z��ǥ
	{ return set2; }

	inline int GetRestrictionRadius() const		// ������� �ݰ�
	{ return set4; }
	
	// socket system [7/16/2010 rumist]
	inline int GetSocketOptionIndex()	const
	{ return rareOptionType[0];	}

	inline int GetSocketOptionLevel()	const
	{ return rareOptionLevel[0];	}

	inline	int GetJumpingLevel() const
	{ return num0;	}

	// [2013/02/13] sykim70 Fortune System
	inline int GetFortuneIndex() const
	{ return fortuneIndex; }

	static bool IsLordItem( int nIndex ) ; // ���� ���� ���� �ƴ��� �Ǵ�. 
	static bool IsUniqueItem( int nIndex ) ; // ����ũ ���� ���� �ƴ��� �Ǵ�. 
	static bool IsPremiumPheonixItem( int nIndex ) ;

	// [2010/10/20 : Sora] �뺴 ī���� üũ
	bool IsMercenaryCardHolder();

	inline int GetItemBelong()	{ return rareOptionType[0]; }

	inline int GetOptionOriginType(int idx)
	{ 
		if (idx < 0 || idx >= MAX_ORIGIN_OPTION)
			return 0;
		return rareOptionType[idx + 1];
	}
	inline int GetOptionOriginLevel(int idx)
	{ 
		if (idx < 0 || idx >= MAX_ORIGIN_OPTION)
			return 0;
		return rareOptionLevel[idx + 1];
	}

	inline int GetOptionSkillType(int idx)
	{ 
		if (idx < 0 || idx >= MAX_ITEM_SKILL)
			return 0;
		return rareOptionType[idx + MAX_ORIGIN_OPTION + 1];
	}
	inline int GetOptionSkillLevel(int idx)
	{ 
		if (idx < 0 || idx >= MAX_ITEM_SKILL)
			return 0;
		return rareOptionLevel[idx + MAX_ORIGIN_OPTION + 1];
	}

	inline char GetCastleWar()
	{ 
		return castleWar;
	}

	int& GetTransFlag() {
		return transFlag;
	}

	inline int GetSyndicateType()
	{ 
		return syndicate_type;
	}

	inline int GetSyndicateGrade()
	{ 
		return syndicate_grade;
	}

	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslate();
	void ClearNoTranslate();

	static int LoadItemNameFromFile(const char* FileName);
	
	//-----------------------------------------------------------------------------
	// Purpose: ������ �����͸� ȭ�Ϸκ��� �о���Դϴ�.
	// Input  : &apItemData - ����� �迭.
	//			FileName - ���ϸ�
	// Output : 	static int
	//-----------------------------------------------------------------------------
	static bool loadItemEx(const char* FileName);
	static int LoadJewelItemDataFromFile(CStaticArray<JewelComosInfo> &apJewelData, const char* FileName);
	static void LoadItemSmcDataFromFile(CStaticArray<ItemSmcParseInfo> &apItemSmcData, const char* FileName);

#if		(_MSC_VER <= 1200)

	static int getsize()	{ return (int)_mapdata.size(); }

	static CItemData* getDataSeq(int Idx)
	{
		if (Idx < 0 || Idx >= _vecdata.size())
			return m_dummy;

		return _vecdata[Idx];
	}

#endif	// (_MSC_VER <= 1200)
};

class CItemRareOption : public stRareOption, public LodLoader<CItemRareOption>
{
private:
	std::string m_strPrefix;			// ���ξ�
public:
	CItemRareOption();
	~CItemRareOption();

	inline const int GetIndex()				
	{	return getindex(); }
	inline const int GetGrade()				
	{	return a_grade;		}	
	inline const int GetType()				
	{	return a_type; }
	void SetPrefix(const char* str)			{ m_strPrefix = str;		}
	inline const char* GetPrefix()			{ return m_strPrefix.c_str(); }
	inline const int GetPhysicalAttack()	
	{	return a_attack;	}
	inline const int GetPhysicalDefence()	
	{	return a_defense;	}
	inline const int GetMagicAttack()		
	{	return a_magic;		}
	inline const int GetMagicDefence()		
	{	return a_resist;	}

	static bool loadEx(const char* FileName);

	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslate()
	{
		char buff[MAX_PATH] = {0,};
		sprintf( buff, "[%d] : rare option", getindex() );
		m_strPrefix = buff;
	}

	void ClearNoTranslate()
	{
		m_strPrefix = "";
	}
};

//SET_ITEM_ADD				//[ttos_2009_5_22]: ��Ʈ ������ ����
class CSetItemData : public stSetItem, public LodLoader<CSetItemData>
{
private:
	struct SetOption
	{
		int nSetCount;
		int nSetType;
		int nSetOptionIndex;
		int nOptionLevel;
	};
	std::string	m_strSetItemName;	// SetItem Name

public:
	enum SET_OPTION_TYPE
	{
		SET_ITEM_TYPE_NONE = -1,
		SET_ITEM_TYPE_OPTION = 0,
		SET_ITEM_TYPE_SKILL = 1,
	};
	CSetItemData();
	~CSetItemData();

	inline const int GetSetItemIndex()		{ return getindex(); }
	void SetName(const char* str)			{ m_strSetItemName = str; }
	inline const char* GetName()			{ return m_strSetItemName.c_str(); }
	inline const LONG GetApplyItemIndex(int nWearPos)	{ return item[nWearPos]; }
	inline const SetOption GetOption(int OptionNum)		
	{
		SetOption setOpdata;
		
		setOpdata.nSetCount = wearCnt[OptionNum];
		setOpdata.nSetType = optionType[OptionNum];
		setOpdata.nSetOptionIndex = option[OptionNum];
		setOpdata.nOptionLevel = optionLevel[OptionNum];
			
		return setOpdata;
	}
	inline const int GetMaxOption()		{ return optionCnt; }
	static bool loadSetItemEx(const char* FileName);
};

#define  MAX_STUFF_ITEM	5

class CMakeItemData
{
private:
	struct SetStuff
	{
		int nStuff_Index;
		int	nStuff_Count;
	};

	int		m_nFactory_Index;				// ���� ������ �ε���
	char	m_strFactory_Name[50];			// ���� ������ �̸�
	int		m_nFactory_Type;				// ���� Ÿ��
	int		m_nFactory_Subtype;				// ���� ���� Ÿ��
	int		m_nItemIndex;					// ������ ������ �ε���
	UQUAD	m_nMakeExp;						// ���� ���õ�
	UQUAD	m_nNeedExp;						// �ʿ� ���õ�
	UQUAD	m_nNeedNas;						// �ʿ� ����
	SetStuff m_StuffItem[MAX_STUFF_ITEM];	// ��� ������

public:
	CMakeItemData();
	~CMakeItemData();

	int GetMakeItemType() { return m_nFactory_Type; }
	int	GetMakeItemSubType() { return m_nFactory_Subtype; }
	char* GetName()	{ return m_strFactory_Name; }
	int GetFactoryIndex()	{ return m_nFactory_Index; }
	UQUAD GetMakeExp()		{ return m_nMakeExp; }
	UQUAD GetNeedNas()		{ return m_nNeedNas; }
	UQUAD GetNeedExp()		{ return m_nNeedExp; }
	int GetItemButtonIndex() { return m_nItemIndex; }
	SetStuff GetStuffItem(int Col)	{ return m_StuffItem[Col]; }
	int	GetStuffItemIndex(int Col)	{ return m_StuffItem[Col].nStuff_Index; }
	int	GetStuffItemCount(int Col)	{ return m_StuffItem[Col].nStuff_Count; }

	static int LoadMakeItemFromFile(CStaticArray<CMakeItemData> &apMakeItem, const char* FileName);
};

#endif