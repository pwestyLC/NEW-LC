#ifndef __SKILL_H__
#define __SKILL_H__

#include "../ShareLib/MemoryPoolBase.h"

#define SKILL_RATE_UNIT		100		// ��ų rate ���� 10000

#define CUBE_BUF_ITEM 11024

#define CUBE_BUF 1075
#define IGNI1_BUF 1062
#define IGNI2_BUF 1063
#define IGNI3_BUF 1064
#define IGNI4_BUF 1065
#define VELOCITY_BUF 465
#define INVISIBILITY 131
#define CAST_POTION 2018

////////////////////////
// ��ų ����
#define MAX_SKILL_LEARN_SKILL			3			// ��ų ���µ� �ʿ��� ��ų �ִ� ����
#define MAX_SKILL_LEARN_ITEM			3			// ��ų ���µ� �ʿ��� ������ �ִ� ����
#define MAX_SKILL_CHANGE				4			// �ϳ��� ��ų�� ���� ���� ��ȭ �ִ� ����
#define MAX_SKILL_NEED_ITEM				2			// ��ų ���� �Ҹ�Ǵ� ������ ����
#define MAX_SKILL_APP_MAGIC				3			// ��ų�� �������� ȿ�� ��
#define MAX_SKILL_USE_MAGIC				3			// ��ų�� ������� ȿ�� ��
#define MAX_SKILL_MAGIC					3			// ��ų�� ȿ�� ��
#define MAX_SKILL_LEVEL					10			// ��ų �ִ� ����
#define UNIT_SKILLPOINT					10000		// ��ų ����Ʈ ��� ����
#define MAX_SOUL_COUNT					10			// ����Ʈ ������ ��ȥ �ִ� ���� ����

#define FACTORY_UNION_REG_SKILL			655			// ���� ���� ��� ��ų ��ȣ

////////////
// ��ų ����
#define SKILL_CON_NORMAL				0			// �Ϲ� ����
#define SKILL_CON_READY					1			// ���� ����
#define SKILL_CON_FIRE					2			// �ߵ� ����

// OLD ATTRIBUTE VARIABLE REUSE, Elenoa 2013.01.09
// �Ӽ� ���
#define	AT_NONE					0			// ��
#define	AT_FIRE					1			// ȭ
#define	AT_WATER				2			// ��
#define	AT_EARTH				3			// ��
#define	AT_WIND					4			// ǳ
#define	AT_DARK					5			// ��
#define	AT_LIGHT				6			// ��
#define AT_RANDOM				7			// random ����Ÿ��
#define AT_LEVELMAX				5
#define AT_MASK			0xFL
#define AT_LVVEC		4
#define AT_MIX(a, l)	(((l) & AT_MASK) << AT_LVVEC) | ((a) & AT_MASK)
#define GET_AT_VAR(m)	((m) & AT_MASK)
#define GET_AT_LV(m)	(((m) >> AT_LVVEC) & AT_MASK)
#define AT_AD_MASK		0xFFL
#define AT_ADVEC		8
#define AT_ADMIX(a, d)	((((a) & AT_AD_MASK) << AT_ADVEC) | ((d) & AT_AD_MASK))
#define GET_AT_DEF(m)	((m) & AT_AD_MASK)
#define GET_AT_ATT(m)	(((m) >> AT_ADVEC) & AT_AD_MASK)

///////////
// ȿ�����

// ȿ�� Ÿ��
#define MT_STAT					0			// ����
// OLD ATTRIBUTE VARIABLE REUSE, Elenoa 2013.01.09
#define MT_ATTRIBUTE			1			// �Ӽ�����
#define MT_ASSIST				2			// ���º�ȭ
#define MT_ATTACK				3			// ����
#define MT_RECOVER				4			// ȸ��
#define MT_CURE					5			// ġ��
#define MT_OTHER				6			// �׿�
#define MT_REDUCE				7			// ����� ����
#define MT_IMMUNE				8			// �鿪
#define MT_CASTLE_WAR			9			// ���� ����
#define MT_MONEY				10			// ��

// ȿ�� ����Ÿ�� - ����
#define MST_STAT_ATTACK			0			// ����
#define MST_STAT_DEFENSE		1			// ���
#define MST_STAT_MAGIC			2			// ����
#define MST_STAT_RESIST			3			// ����
#define MST_STAT_HITRATE		4			// ����
#define MST_STAT_AVOID			5			// ȸ��
#define MST_STAT_CRITICAL		6			// ũ��
#define MST_STAT_ATTACKSPD		7			// ����
#define MST_STAT_MAGICSPD		8			// ����
#define MST_STAT_MOVESPD		9			// �̼�
#define MST_STAT_RECOVERHP		10			// HPȸ��
#define MST_STAT_RECOVERMP		11			// MPȸ��
#define MST_STAT_MAXHP			12			// �ִ�HP ����
#define MST_STAT_MAXMP			13			// �ִ�MP ����
#define MST_STAT_DEADLY			14			// ���鸮 Ȯ�� ����
#define MST_STAT_MAGICHITRATE	15			// ���� ����
#define MST_STAT_MAGICAVOID		16			// ���� ȸ��
#define MST_STAT_ATTACKDIST		17			// ���ݰŸ� ����
#define MST_STAT_ATTACK_MELEE	18			// �������� ����
#define MST_STAT_ATTACK_RANGE	19			// ���⸮���� ���� ����
#define MST_STAT_HITRATE_SKILL	20			// ��ų ���߷�
#define MST_STAT_ATTACK_80		21			// ���ݷ� 80
#define MST_STAT_MAXHP_450		22			// �ִ�HP ���� 450
#define MST_STAT_SKILLSPD		23			// ��ų ���� �ӵ�����
#define	MST_STAT_VALOR			24			// ��Ƽ������ ����Ͽ� ���ݷ� ���
#define MST_STAT_STATPALL		25			// ���� ����
#define MST_STAT_ATTACK_PER		26			// ���� %
#define MST_STAT_DEFENSE_PER	27			// ��� %
#define MST_STAT_STATPALL_PER	28			// ���� ���� %
#define MST_STAT_STR			29			// ��
#define MST_STAT_DEX			30			// ��ø
#define MST_STAT_INT			31			// ����
#define MST_STAT_CON			32			// ü��
//  [5/21/2009 KwonYongDae]
#define MST_STAT_HARD			33			// ���Ѱ���
#define MST_STAT_STRONG			34			// ������
#define MST_STAT_NPCATTACK		35			// NPC ���Ը� ����/���Ÿ� ���ݷ� ����
#define MST_STAT_NPCMAGIC		36			// NPC ���Ը� ���� ���ݷ� ����
#define MST_STAT_SKILLCOOLTIME	37			// ��ų ��Ÿ��
#define MST_STAT_DECREASE_MANA_SPEND 38		// �����Һ� ����
#define MST_STAT_STONE			39
#define MST_STAT_SILEN			40
#define MST_STAT_STURN			41
#define MST_STAT_ABSORB			42
// ȿ�� ����Ÿ�� - �����̻�
#define MST_ASSIST_POISON		0			// ��
#define MST_ASSIST_HOLD			1			// Ȧ��
#define MST_ASSIST_CONFUSION	2			// ȥ��
#define MST_ASSIST_STONE		3			// ��ȭ
#define MST_ASSIST_SILENT		4			// ����
#define MST_ASSIST_BLOOD		5			// ����
#define MST_ASSIST_BLIND		6			// �����ε�
#define MST_ASSIST_STURN		7			// ����
#define MST_ASSIST_SLEEP		8			// ����
#define MST_ASSIST_HP			9			// HPȸ��
#define MST_ASSIST_MP			10			// MPȸ��
#define MST_ASSIST_MOVESPD		11			// �̼� ���
#define MST_ASSIST_HP_CANCEL	12			// HP��ȭ(0, MAX���� ���)
#define MST_ASSIST_MP_CANCEL	13			// MP��ȭ(0, MAX���� ���)
#define MST_ASSIST_DIZZY		14			// ������
#define MST_ASSIST_INVISIBLE	15			// �κ�����
#define MST_ASSIST_SLOTH		16			// ���ν� : �����϶�
#define MST_ASSIST_FEAR			17			// ���� : �ش� NPC�� ����
#define MST_ASSIST_FAKEDEATH	18			// ����ô
#define MST_ASSIST_PERFECTBODY	19			// Ÿ��ź ���� �ٵ�
#define MST_ASSIST_FRENZY		20			// Ÿ��ź ������
#define MST_ASSIST_DAMAGELINK	21			// �������ũ
#define MST_ASSIST_BERSERK		22			// ����ũ
#define MST_ASSIST_DESPAIR		23			// ����
#define MST_ASSIST_MANASCREEN	24			// ���� ��ũ��
#define MST_ASSIST_BLESS		25			// ������
#define MST_ASSIST_SAFEGUARD	26			// ��ȣ��(�����Ұ���)
#define MST_ASSIST_MANTLE		27			// ����
#define MST_ASSIST_GUARD		28			// ��� ��ȯ

#define MST_ASSIST_CHARGEATC	29			// ��ź(attack)
#define MST_ASSIST_CHARGEMGC	30			// ��ź(magic)

#define MST_ASSIST_DISEASE		31			// ����
#define MST_ASSIST_CURSE		32			// ����
#define MST_ASSIST_CONFUSED			33			// ���͸� ȥ���� �ɸ��� ��
#define MST_ASSIST_TAMING			34			// ���͸� �����ð� �Ʊ����� ����
#define MST_ASSIST_FREEZE			35			// ��� (���� ���� ����, �ɸ� ���� �̵� ����)
#define MST_ASSIST_INVERSE_DAMAGE	36			// �ǰݴ��ϸ� ������ ��ŭ HP ȸ��
#define MST_ASSIST_HP_DOT			37			// ���ӵ����� ����
#define MST_ASSIST_REBIRTH			38			// ��Ȱ
#define MST_ASSIST_DARKNESS_MODE	39			// �絵 ���
#define MST_ASSIST_AURA_DARKNESS	40			// ������ - ��ũ�Ͻ�
#define MST_ASSIST_AURA_WEAKNESS	41			// ������ - ��ũ�Ͻ�
#define MST_ASSIST_AURA_ILLUSION	42			// ������ - �Ϸ���
#define MST_ASSIST_MERCENARY		43		// ���͸� �뺴���� �ٲ�.
#define MST_ASSIST_SOUL_TOTEM_BUFF	44		// ���� ����(����))�� ����(������)
#define MST_ASSIST_SOUL_TOTEM_ATTK	45		// ���� ����(����)�� ����(������)
#define MST_ASSIST_TRAP				46		// ���͸� Ʈ������
#define MST_ASSIST_PARASITE			47		// �з�����Ʈ ���� (������ ���·� ������ �������͸� ��ȯ�Ͽ� ������ ����)
#define MST_ASSIST_SUICIDE			48		// ���͸� ������Ŵ
#define MST_ASSIST_INVINCIBILITY	49		// ���� ���
#define MST_ASSIST_GPS				50		// GPS
#define MST_ASSIST_ATTACK_TOWER		51		// ���� Ÿ�� ������ �߰�
#define MST_ASSIST_ARTIFACT_GPS		52		// ���� gps
#define MST_ASSIST_TOTEM_ITEM_BUFF	53		// ���� ������ ����
#define MST_ASSIST_TOTEM_ITEM_ATTK	54		// ���� ������ ����
#ifdef HP_REDUCE_10222021
#define MSG_ASSIST_HEAL_REDUCE		55
#endif
// ȿ�� ����Ÿ�� - ����
#define MST_ATTACK_NORMAL		0			// �Ϲ� ����
#define MST_ATTACK_CRITICAL		1			// ũ��Ƽ�� ����
#define MST_ATTACK_DRAIN		2			// �巹�� : �� hp�� �������� ����
#define MST_ATTACK_ONESHOTKILL	3			// ���
#define MST_ATTACK_DEADLY		4			// ���鸮 ����
#define MST_ATTACK_HARD			5			// �ſ� ���� ����

// ȿ�� ����Ÿ�� - ȸ��
#define MST_RECOVER_HP			0			// HPȸ��
#define MST_RECOVER_MP			1			// MPȸ��
#define MST_RECOVER_STM			2			// ������ �� ���׹̳� ȸ��
#define MST_RECOVER_FAITH		3			// ������ �� �漺�� ȸ��
#define MST_RECOVER_EXP			4			// ����ġ ����
#define MST_RECOVER_SP			5			// ���õ� ����

// ȿ�� ����Ÿ�� - ġ��
#define MST_CURE_POISON			0			// ��
#define MST_CURE_HOLD			1			// Ȧ�� : TODO : ������� ����
#define MST_CURE_CONFUSION		2			// ȥ��
#define MST_CURE_STONE			3			// ��ȭ
#define MST_CURE_SILENT			4			// ����
#define MST_CURE_BLOOD			5			// ����
#define MST_CURE_REBIRTH		6			// ��Ȱ
#define MST_CURE_INVISIBLE		7			// �κ����� ���¸� ����
#define MST_CURE_STURN			8			// ���� ����
#define MST_CURE_SLOTH			9			// ���ν� ����
#define MST_CURE_NOTHELP		10			// not help�� assist�� ��� ����
#define MST_CURE_BLIND			11			// �����ε�

#define MST_CURE_DISEASE		12			// ���� ����
#define MST_CURE_CURSE			13			// ���� ����
#define MSG_CURE_ALL			14			// ����� ��� ���� <<-- MST_CURE_NOTHELP �� �ߺ�Ȯ�� �ʿ�
#define MST_CURE_INSTANTDEATH	15			// ���(������ ���� ����)

// ȿ�� ����Ÿ�� - �׿�
#define MST_OTHER_INSTANTDEATH	0			// ���
#define MST_OTHER_SKILLCANCEL	1			// ��ų ���� ���
#define MST_OTHER_TACKLE		2			// ��Ŭ
#define MST_OTHER_TACKLE2		3			// ��Ŭ2
#define MST_OTHER_REFLEX		4			// �ݻ� ����� (�Ϲ� ����, 25m��)
#define MST_OTHER_DEATHEXPPLUS	5			// ������ ����ġ �г�Ƽ �ٿ�
#define MST_OTHER_DEATHSPPLUS	6			// ������ SP �г�Ƽ �ٿ�
#define MST_OTHER_TELEKINESIS	7			// �ڷ�Ű�׽ý�
#define MST_OTHER_TOUNT			8			// Ÿ��Ʈ : ����Ʈ ����
#define MST_OTHER_SUMMON		9			// ��ȯ
#define MST_OTHER_EVOCATION		10			// ����
#define MST_OTHER_TARGETFREE	11			// Ÿ�� ����
#define MST_OTHER_CURSE			12			// Ÿ�� ���� �϶�
#define MST_OTHER_PEACE			13			// ��ȭ�� ¡ǥ
#define MST_OTHER_SOUL_DRAIN	14			// ��ȥ ����, ���� ä��
#define MST_OTHER_KNOCKBACK		15			// �˹�
#define MST_OTHER_WARP			16			// ����
#define MST_OTHER_FLY			17			// ����
#define MST_OTHER_EXP			18			// EXP
#define MST_OTHER_SP			19			// SP
#define MST_OTHER_ITEMDROP		20			// ������ �ٴڿ� ���
#define MST_OTHER_SKILL			21			// ��ų���
#define MST_OTHER_PK_DISPOSITION 22			// PK ���� ����Ʈ
#define MST_OTHER_AFFINITY		23			// ģȭ�� �ν���
#define MST_OTHER_AFFINITY_QUEST	24		// ģȭ�� ����Ʈ
#define MST_OTHER_AFFINITY_MONSTER	25		// ģȭ�� ����
#define MST_OTHER_AFFINITY_ITEM		26		// ģȭ�� ������
#define MST_OTHER_QUEST_EXP			27		// ����Ʈ ����ġ
#define MST_OTHER_GUILD_PARTY_EXP	28		// ���� ��Ƽ ����ġ ȹ�淮
#define MST_OTHER_GUILD_PARTY_SP	29		// ���� ��Ƽ ��ų����Ʈ ȹ�淮
#define MSG_OTHER_SUMMON_NPC		30		// NPC ��ȯ

// ȿ�� ����Ÿ�� - ����� ����
#define MST_REDUCE_MELEE		0			// ���� ���� ����
#define MST_REDUCE_RANGE		1			// ���Ÿ� ���� ����
#define MST_REDUCE_MAGIC		2			// ���� ���� ����
#define MST_REDUCE_SKILL		3			// ��ų ���� ����

// ȿ�� ����Ÿ�� - �鿪
#define MST_IMMUNE_BLIND		0			// �����ε�

// ȿ�� ����Ÿ�� - ����
#define MST_WAR_REDUCE_MELEE	0
#define MST_WAR_REDUCE_RANGE	1
#define MST_WAR_REDUCE_MAGIC	2
#define MST_WAR_MAX_HP			3
#define MST_WAR_DEFENCE			4
#define MST_WAR_RESIST			5
#define MST_WAR_TOWER_ATTACK	6

// ����� Ÿ��
#define MDT_ONLYPOWER			0			// ��ų ���¸�
#define MDT_ADDITION			1			// ���ȿ� ����
#define MDT_RATE				2			// ���ȿ� ������ ����

// �Ӽ� ������ Ÿ��
#define MDT_NONE				0
#define MDT_ATTACK				1
#define MDT_DEFENCE				2

// ���� Ÿ��
#define MHT_CONSTANT			0			// ����
#define MHT_VARIABLE			1			// ����

// ȿ�� ����Ÿ�� - ��(MONEY)
#define MST_MONEY_BUY		0			// ����
#define MST_MONEY_SELL		1			// �Ǹ�
#define MST_MONEY_NAS		2			// �߰� ����

////////////
// ��ų ���

// ��ų ����
#define ST_MELEE				0			// ����
#define ST_RANGE				1			// ���Ÿ�
#define ST_MAGIC				2			// ����
#define ST_PASSIVE				3			// �нú�
#define ST_PET_COMMAND			4			// �� Ŀ�ǵ�
#define ST_PET_SKILL_PASSIVE	5			// �� ��ų(�нú�)
#define ST_PET_SKILL_ACTIVE		6			// �� ��ų(��Ƽ��)
#define ST_GUILD_SKILL_PASSIVE	7			// ��� ��ų(�нú�)
#define ST_SEAL					8			// ���� �ý��� ��ų(��ǥ)
#define ST_SUMMON_SKILL			9			// ���� ��ȯ ��ų

// Ÿ���� ���
#define STT_SELF_ONE			0			// ����
#define STT_SELF_RANGE			1			// ���� ����
#define STT_TARGET_ONE			2			// Ÿ��
#define STT_TARGET_RANGE		3			// Ÿ�� ����
#define STT_PARTY_ONE			4			// ��Ƽ 1��
#define STT_PARTY_ALL			5			// ��Ƽ ��ü
#define STT_TARGET_D120			6			// Ÿ�� 120��
#define STT_TARGET_RECT			7			// Ÿ�� ���簢
#define STT_ELEMENTAL_ONE		8			// ������Ż ��� ��ų
#define STT_GUILD_ALL			9			// ��� ��ü���� �ִ� HELP ��ų
#define STT_GUILD_ONE			10			// ��� �Ѹ����� �ִ� HELP ��ų
#define STT_GUILD_SELF_RANGE	11			// ������ ���� NPC���� �ִ� ATTACK SKILL
#define STT_GUILD_MEMBER_SELF	12			// ����� ����

// �÷���
#define	SF_SINGLEMODE			(1 << 0)	// �̱۸��
#define	SF_HELP					(1 << 1)	// ������ �ִ� ��ų
#define	SF_NOTHELP				(1 << 2)	// �ز��� ��ų
#define SF_ABSTIME				(1 << 3)	// 060227 : bs : ����ð� ���
#define SF_NOTDUPLICATE			(1 << 4)	// 060227 : bs : �ߺ� ��� �Ұ� : �ߺ��Ǵ� ��ų�� ������ ������ ������� ����� �ȵ�
#define SF_NOCANCEL				(1 << 5)	// �ٸ� ��ų/����� ���� ��� �ȵ�
#define	SF_COMBO				(1 << 6)	// �ð�������� �����(��������, �����̵�, �׾��� �� �����)
#define	SF_LOGOUT				(1 << 7)	// �������� �� �����
#define SF_INSTANT				(1 << 8)	// 100420 : swkwon : ������ ��ų �α׾ƿ��Ҷ� ��ų ����Ʈ���� ������.
#define SF_GUILD				(1 << 9)	// 100615 : swkwon : ��彺ų
#define SF_INFINITE				(1 << 10)	// ���ѽ�ų - ��ų �ð��� ����Ǹ� �ٽ� ��ų�� �����
#define SF_ZONE					(1 << 11)	// ���̵��� ���� ����
#define SF_SUMMON_NPC			(1 << 12)	// summon Npc�� ����ϴ� ��ų���� üũ // üũ�ϸ� ����Ʈ�� �����ش�.
#define SF_NOTBLESS				(1 << 13)	// �÷��װ� ������ �Ҽ��� �������� ������ ���� �ʴ´�.
#define SF_ITEMSKILL			(1 << 14)	// ������ ��ų
#define SF_NOT_BOSS				(1 << 15)	// �÷��װ� ������ �������� ����� �� ���� ��ų�̴�.
#define SF_NOT_SINGLE			(1 << 16)	// �÷��װ� ������ ���δ��������� ��ų����� �� �� ����.
#define SF_TOGGLE				(1 << 17)	// ��� ��ų

// ���/���� ����
#define SCT_DEATH				(1 << 0)	// ���
#define SCT_WEAPON				(1 << 1)	// �������
#define SCT_SITDOWN				(1 << 2)	// �ɱ�
#define SCT_PEACEZONE			(1 << 3)	// ��ȭ����
#define SCT_SHIELD				(1 << 4)	// ��������
#define SCT_STAND				(1 << 5)	// ����
#define SCT_DARKNESS			(1 << 6)    // ����Ʈ ������ �絵 ��忡���� ����ϴ� ��ų���� Ȯ��
#define SCT_NO_COOL_TIME		(1 << 7)	// ��Ÿ�Ӱ��� ���� �Ұ�

// �����̻� ��Ʈ �ʵ� ��
#define AST_POISON				((LONGLONG)1 << MST_ASSIST_POISON)		// ��
#define AST_HOLD				((LONGLONG)1 << MST_ASSIST_HOLD)			// Ȧ��
#define AST_CONFUSION			((LONGLONG)1 << MST_ASSIST_CONFUSION)		// Ȧ��
#define AST_STONE				((LONGLONG)1 << MST_ASSIST_STONE)			// ��ȭ
#define AST_SILENT				((LONGLONG)1 << MST_ASSIST_SILENT)		// ����
#define AST_BLOOD				((LONGLONG)1 << MST_ASSIST_BLOOD)			// ����
#define AST_BLIND				((LONGLONG)1 << MST_ASSIST_BLIND)			// �����ε�
#define AST_STURN				((LONGLONG)1 << MST_ASSIST_STURN)			// ����
#define AST_SLEEP				((LONGLONG)1 << MST_ASSIST_SLEEP)			// ����
#define AST_HP					((LONGLONG)1 << MST_ASSIST_HP)			// ü��
#define AST_MP					((LONGLONG)1 << MST_ASSIST_MP)			// ����
#define AST_MOVESPD				((LONGLONG)1 << MST_ASSIST_MOVESPD)		// �̼� ���
#define AST_HP_CANCEL			((LONGLONG)1 << MST_ASSIST_HP_CANCEL)		// HP��ȭ(0, MAX���� ���)
#define AST_MP_CANCEL			((LONGLONG)1 << MST_ASSIST_MP_CANCEL)		// MP��ȭ(0, MAX���� ���)
#define AST_DIZZY				((LONGLONG)1 << MST_ASSIST_DIZZY)			// ������
#define AST_INVISIBLE			((LONGLONG)1 << MST_ASSIST_INVISIBLE)		// �κ�������Ƽ
#define AST_SLOTH				((LONGLONG)1 << MST_ASSIST_SLOTH)			// ���ν�(�����϶�)
#define AST_FEAR				((LONGLONG)1 << MST_ASSIST_FEAR)			// ����
#define AST_FAKEDEATH			((LONGLONG)1 << MST_ASSIST_FAKEDEATH)		// ����ô�ϱ�
#define AST_PERFECTBODY			((LONGLONG)1 << MST_ASSIST_PERFECTBODY)	// Ÿ��ź ���� �ٵ�
#define AST_FRENZY				((LONGLONG)1 << MST_ASSIST_FRENZY)		// Ÿ��ź ������
#define AST_DAMAGELINK			((LONGLONG)1 << MST_ASSIST_DAMAGELINK)	// ������ ��ũ
#define AST_BERSERK				((LONGLONG)1 << MST_ASSIST_BERSERK)		// ����ũ
#define AST_DESPAIR				((LONGLONG)1 << MST_ASSIST_DESPAIR)		// ����
#define AST_MANASCREEN			((LONGLONG)1 << MST_ASSIST_MANASCREEN)	// ���� ��ũ��
#define AST_BLESS				((LONGLONG)1 << MST_ASSIST_BLESS)			// ������
#define AST_SAFEGUARD			((LONGLONG)1 << MST_ASSIST_SAFEGUARD)		// ��ȣ��
#define AST_MANTLE				((LONGLONG)1 << MST_ASSIST_MANTLE)		// ����
#define AST_GUARD				((LONGLONG)1 << MST_ASSIST_GUARD)			// ��� ��ȯ
//-- (-2) ��ź 2�� ������
#define AST_DISEASE				((LONGLONG)1 << (MST_ASSIST_DISEASE-2) )	// ����
#define AST_CURSE				((LONGLONG)1 << (MST_ASSIST_CURSE-2) )		// ��� ��ȯ
#define AST_CONFUSED			((LONGLONG)1 << MST_ASSIST_CONFUSED)		// ���͸� ȥ���� �ɸ��� ��
#define AST_TAMING				((LONGLONG)1 << MST_ASSIST_TAMING)			// ���͸� �����ð� �Ʊ����� ����
#define AST_FREEZE				((LONGLONG)1 << MST_ASSIST_FREEZE)			// ��� (���� ���� ����, �ɸ� ���� �̵� ����)
#define AST_INVERSE_DAMAGE		((LONGLONG)1 << MST_ASSIST_INVERSE_DAMAGE)	// �ǰݴ��ϸ� ������ ��ŭ HP ȸ��
#define AST_HP_DOT				((LONGLONG)1 << MST_ASSIST_HP_DOT)			// ���ӵ����� ����
#define AST_REBIRTH				((LONGLONG)1 << MST_ASSIST_REBIRTH)			// ������ �� ������ ������ �ٷ� ��Ȱ
#define AST_DARKNESS_MODE		((LONGLONG)1 << MST_ASSIST_DARKNESS_MODE)	// �絵 ���
#define AST_AURA_DARKNESS		((LONGLONG)1 << MST_ASSIST_AURA_DARKNESS)	// ������ - ��ũ�Ͻ�
#define AST_AURA_WEAKNESS		((LONGLONG)1 << MST_ASSIST_AURA_WEAKNESS)	// ������ - ��ũ�Ͻ�
#define AST_AURA_ILUSYON		((LONGLONG)1 << MST_ASSIST_AURA_ILLUSION)	// ������ - �Ϸ���
#define AST_MERCENARY			((LONGLONG)1 << MST_ASSIST_MERCENARY)		// ���͸� �뺴���� ����
#define AST_SOUL_TOTEM_BUFF		((LONGLONG)1 << MST_ASSIST_SOUL_TOTEM_BUFF)	// ���� ���� ������
#define AST_SOUL_TOTEM_ATTK		((LONGLONG)1 << MST_ASSIST_SOUL_TOTEM_ATTK)	// ���� ���� ������
#define AST_TRAP				((LONGLONG)1 << MST_ASSIST_TRAP)			// Ʈ��
#define AST_PARASITE			((LONGLONG)1 << MST_ASSIST_PARASITE)		// ����� ����
#define AST_SUICIDE				((LONGLONG)1 << MST_ASSIST_SUICIDE)			// ����
#define AST_INVINCIBILITY		((LONGLONG)1 << MST_ASSIST_INVINCIBILITY)	// ����
#define AST_TOWER_ATTACK		((LONGLONG)1 << MST_ASSIST_ATTACK_TOWER)	// ���� Ÿ�� ������ �߰�
#ifdef HP_REDUCE_10222021
#define AST_HEAL_REDUCE			((LONGLONG)1 << MSG_ASSIST_HEAL_REDUCE)
#endif
#define SKILL_PARAM_MIN			75
#define SKILL_PARAM_MAX			125

#define SPARAM_NONE				0
#define SPARAM_STR				1
#define SPARAM_DEX				2
#define SPARAM_INT				3
#define SPARAM_CON				4

// �Ҽ��� �÷���
#define SSF_APP_CHARACTER		(1 << 0)	// ĳ����
#define SSF_APP_FIRE			(1 << 1)	// ��������
#define SSF_APP_WIND			(1 << 2)	// �ٶ�������
#define SSF_APP_EARTH			(1 << 3)	// ����������
#define SSF_APP_WATER			(1 << 4)	// ��������
#define SSF_APP_HELLOUND		(1 << 5)	// ����
#define SSF_APP_ELENEN			(1 << 6)	// ������
#define SSF_APP_APET			(1 << 7)	// ������ ��
#define SSF_APP_ALL				(SSF_APP_CHARACTER | SSF_APP_FIRE | SSF_APP_WIND | SSF_APP_EARTH | SSF_APP_WATER | SSF_APP_HELLOUND | SSF_APP_ELENEN | SSF_APP_APET)
#define SSF_USE_CHARACTER		(1 << 16)	// ĳ����
#define SSF_USE_FIRE			(1 << 17)	// ��������
#define SSF_USE_WIND			(1 << 18)	// �ٶ�������
#define SSF_USE_EARTH			(1 << 19)	// ����������
#define SSF_USE_WATER			(1 << 20)	// ��������
#define SSF_USE_HELLOUND		(1 << 21)	// ����
#define SSF_USE_ELENEN			(1 << 22)	// ������
#define SSF_USE_APET			(1 << 23)	// ������ ��
#define SSF_USE_ALL				(SSF_USE_CHARACTER | SSF_USE_FIRE | SSF_USE_WIND | SSF_USE_EARTH | SSF_USE_WATER | SSF_USE_HELLOUND | SSF_USE_ELENEN | SSF_USE_APET)

#define IMMOTAL_BUF				469			//���� ���� ��ų�ε���
#define FLY_SKILL				688
#define DARKNESS_SKILL			682
#define PVP_PROTECT_SKILL_INDEX	1791

#define SKILL_GUILD_ROOM_WARP 1831
#define SKILL_GUILD_ROOM_RECALL 1827
#define SKILL_GUILD_PARTY_EXP	1825

// --- skill

class CCharacter;
class CPC;
class CPet;
class CAPet;

/////////////////////
// Class name	    : CMagicLevelProto
// Description	    : ȿ�� ������ ����
class CMagicLevelProto
{
public:
	int				m_nPowerValue;		// ����
	int				m_nHitrateValue;	// ���߷�
	int	GetSummonNpcIndex()
	{
		return m_nPowerValue;
	}
	CMagicLevelProto(int nPower, int nHitrate);
};

/////////////////////
// Class name	    : CMagicProto
// Description	    : ȿ�� ����
class CMagicProto
{
public:
	int					m_index;		// ��ȣ
	char				m_maxlevel;		// �ִ뷹��
	char				m_type;			// Ÿ��
	char				m_subtype;		// ����Ÿ��
	char				m_damagetype;	// ����� Ÿ��
	char				m_hittype;		// ���� Ÿ��
	char				m_attribute;	// �Ӽ�
	int					m_psp;			// ��ų ������� ����� �Ķ����
	int					m_ptp;			// ��ų ����� ����� �Ķ����
	int					m_hsp;			// ��ų ������� ���� �Ķ����
	int					m_htp;			// ��ų ����� ���� �Ķ����
	int					m_bTogel;		// ��ų ����� �����Ѱ�?

	CMagicLevelProto**	m_levelproto;	// ���� ����

	CMagicProto(int index, char maxlevel, char type, char subtype, char damagetype, char hittype, char attribute, int psp, int ptp, int hsp, int htp, int bTogel, CMagicLevelProto** levelproto);

	~CMagicProto();

	const CMagicLevelProto* Level(char level) const;
};

/////////////////////
// Class name	    : CSkillLevelProto
// Description	    : ��ų ���� ����
class CSkillLevelProto
{
public:
	int					m_needHP;
	int					m_needMP;
	int					m_needGP;
	int					m_durtime;
	int					m_hate;
	int					m_needItemIndex[MAX_SKILL_NEED_ITEM];
	int					m_needItemCount[MAX_SKILL_NEED_ITEM];
	int					m_learnLevel;
	LONGLONG			m_learnSP;
	int					m_learnSkillIndex[MAX_SKILL_LEARN_SKILL];
	char				m_learnSkillLevel[MAX_SKILL_LEARN_SKILL];
	int					m_learnItemIndex[MAX_SKILL_LEARN_ITEM];
	int					m_learnItemCount[MAX_SKILL_LEARN_ITEM];
	int					m_learnstr;
	int					m_learndex;
	int					m_learnint;
	int					m_learncon;
	int					m_appMagicIndex[MAX_SKILL_APP_MAGIC];
	char				m_appMagicLevel[MAX_SKILL_APP_MAGIC];
	const CMagicProto*	m_magic[MAX_SKILL_MAGIC];
	char				m_magicLevel[MAX_SKILL_MAGIC];
	int					m_useCount;
	int					m_targetNum;
	LONGLONG					m_learnGP;
	CSkillLevelProto(int needHP, int needMP, int needGP, int durtime, int hate, int needItemIndex[2], int needItemCount[2], int learnLevel, LONGLONG learnSP, int learnSkillIndex[3], char learnSkillLevel[3], int learnItemIndex[3], int learnItemCount[3], int learnstr, int learndex, int learnint, int learncon, int appMagicIndex[3], char appMagicLevel[3], const CMagicProto* magic[3], char magicLevel[3], LONGLONG learnGP
					 , int useCount
					 , int targetNum
					);
};

/////////////////////
// Class name	    : CSkillProto
// Description	    : ��ų ����
class CSkillProto
{
public:
	int					m_index;
	char				m_type;
	int					m_flag;
	char				m_maxLevel;
	float				m_appRange;
	char				m_targetType;
	int					m_readyTime;
	int					m_stillTime;
	int					m_fireTime;
	int					m_reuseTime;
	int					m_selfparam;
	int					m_targetparam;

	int					m_applyState;
	int					m_applyWeaponType0;
	int					m_applyWeaponType1;

	int					m_nAPetIndex;

	int					m_soul_consum;
	int					m_useWearing;
	int					m_appWearing;

	int					m_summonIDX;

private:
	int					m_job;
	int					m_job2;
	float				m_fireRange;
	float				m_fireRange2;
	float				m_minRange;
	int					m_useState;
	int					m_useWeaponType0;
	int					m_useWeaponType1;
	int					m_useMagicIndex[MAX_SKILL_USE_MAGIC];
	char				m_useMagicLevel[MAX_SKILL_USE_MAGIC];
	int					m_sorcerer_flag;

	bool				is_active_flag;
	bool				is_passive_flag;
	bool				is_summon_flag;
	bool				is_rvr_zone_not_use;
public:

	CSkillLevelProto**	m_levelproto;

	CSkillProto(int index, int job, int job2, char type, int flag, int sorcerer_flag, char maxLevel, float appRange, float fireRange, float fireRange2, float minRange, char targetType, int useState, int useWeaponType0, int useWeaponType1, int useMagicIndex[3], char useMagicLevel[3], int appState, int appWeaponType0, int appWeaponType1, int readyTime, int stillTime, int fireTime, int reuseTime, int selfparam, int targetparam, CSkillLevelProto** levelproto, int nAPetIndex, int soul_consum, int useWearing, int appWearing, int summonIdx );

	~CSkillProto();

	const CSkillLevelProto* Level(char level) const;

	/////////////////////
	// Function name	: IsActive
	// Description	    : ��Ƽ�� ��ų �˻�
	bool IsActive() const
	{
		return is_active_flag;
	}

	/////////////////////
	// Function name	: IsPassive
	// Description	    : �нú� ��ų �˻�
	bool IsPassive() const
	{
		return is_passive_flag;
	}

	/////////////////////
	// Function name	: IsSummon
	// Description	    : ���� ��ų �˻�
	bool IsSummon() const
	{
		return is_summon_flag;
	}

	bool isRVRNotUse() const
	{
		return is_rvr_zone_not_use;
	}

	bool IsSeal() const;

	////////////////////
	// Function name	: IsSameJob
	// Description	    : ���� �������� �˻�
	bool IsSameJob(CPC* pc) const;
	bool IsSameJob(CPet* pet) const;

	bool IsSameJob(CAPet* apet) const;

	////////////////////
	// Function name	: GetFireRange
	// Description	    : �����Ÿ� �˻�, NPC�� 1��, PC�� ���⿡ ����
	float GetFireRange(CCharacter* ch) const;

	////////////////////
	// Function name	: CheckUseState
	// Description	    : ��� ���� �˻�
	// Return type		: int
	//                  : ��� �Ұ��ɽÿ� ������� ���� ��ȯ, -1�� magic �Ҵɿ���
	int CheckUseState(CCharacter* ch) const;

	// a_minRange
	float GetMinRange() const;

	int Get2ndJob() const
	{
		return m_job2;
	}

	int getJob() const
	{
		return m_job;
	}

	// �Ҽ����� �÷��� Ȯ��
	int CheckSorcererFlag(int mask) const
	{
		return (m_sorcerer_flag & mask);
	}

#ifdef EXTREME_CUBE_VER2
	bool CheckAllowZone(char zoneindex) const;
	bool LoadAllowZone(const char* strZoneList);

private:
	struct SKILLALLOWZONE
	{
		char	count;
		char*	zoneindex;
		SKILLALLOWZONE(char nCount)
		{
			count = nCount;
			zoneindex = new char[nCount];
			memset(zoneindex, -1, sizeof(char) * nCount);
		}
		~SKILLALLOWZONE()
		{
			count = 0;
			if(zoneindex)
			{
				delete [] zoneindex;
				zoneindex = NULL;
			}
		}
	};

	SKILLALLOWZONE* m_allowzone;
#endif // EXTREME_CUBE_VER2
};

/////////////////////
// Class name	    : CMagicProtoList
// Description	    : ȿ�� ���� ����Ʈ
class CMagicProtoList
{
public:
	typedef std::map<int, CMagicProto*> map_t;

	map_t			map_;
	CMagicProto**	m_list;
	int				m_count;

public:
	CMagicProtoList();
	~CMagicProtoList();

	/////////////////////
	// Function name	: Load
	// Description	    : ȿ�� ����Ʈ �б�
	// Return type		: bool
	//            		: ���� ����
	bool Load();

	bool Free();

	/////////////////////
	// Function name	: Find
	// Description	    : Ư�� �ε����� ȿ�� ã��
	// Return type		: const CMagicProto*
	//            		: ã�� ȿ�� ������, ���н� NULL
	// Argument         : int index
	//                  : ã���� �ϴ� ȿ�� ��ȣ
	const CMagicProto* Find(int index);
};

// ���� ��ƼŸ�ٿ� ����ü
struct MultiTarget : public MemoryPoolBase<MultiTarget>
{
	CCharacter*		mtarget;
	char			mtargettype;
	int				mtargetindex;
	float			mdist;

	MultiTarget()
		: mtarget(NULL)
		, mtargettype(-1)
		, mtargetindex(0)
		, mdist(9999)
	{
	}
};

/////////////////////
// Class name	    : CSkill
// Description	    : ��ų
class CSkill : public MemoryPoolBaseWithMutex<CSkill>
{
public:
	const CSkillProto*	m_proto;			// ��ų ������
	char				m_level;			// ��ų ����

	int					m_state;
	int					m_usetime;
	MSG_CHAR_TYPE		m_targetType;
	int					m_targetIndex;
	int					m_enable;

	struct guild_skill_cooltime_data
	{
		int char_index;
		int usetime;
	};

	typedef std::map<int/*char_index*/, int/*usetime*/> GUILD_SKILL_USETIME_DATA;
	GUILD_SKILL_USETIME_DATA m_gskill_usetime;

	int					m_optionSkillProb;	//�ɼ� ��ų �ߵ� Ȯ��

	bool				m_toggle;

	CSkill(const CSkillProto* proto, char level);

	/////////////////////
	// Function name	: IsReady
	// Description	    : ��ų ���� ���� �˻�
	// Argument         : CCharacter* ch
	//                  : ��ų ���� ���
	bool IsReady(CCharacter* ch);

	/////////////////////
	// Function name	: Ready
	// Description	    : ���� ���·� ����
	void Ready(CCharacter* tch);

	/////////////////////
	// Function name	: Fire
	// Description	    : �߻� ���ʷ� ����
	void Fire();

	/////////////////////
	// Function name	: Cancel
	// Description	    : ���� ���
	void Cancel(CCharacter* pCharSkill);
};

/////////////////////
// Class name	    : CSkillProtoList
// Description	    : ��ų ����Ʈ
class CSkillProtoList
{
public:
	typedef std::map<int, CSkillProto*> map_t;

	CSkillProtoList();
	~CSkillProtoList();

	/////////////////////
	// Function name	: Load
	// Description	    : ��ų ����Ʈ �б�
	// Return type		: bool
	//            		: ���� ����
	bool Load();

	bool Free();
	
	/////////////////////
	// Function name	: Find
	// Description	    : Ư�� ��ų ã��
	// Return type		: const CSkillProto*
	//            		: ã�� ��ų ������, ���н� NULL
	// Argument         : int skillIndex
	//                  : ã���� �ϴ� ��ų ��ȣ
	const CSkillProto* Find(int skillIndex);

	/////////////////////
	// Function name	: Create
	// Description	    : ��ų ����
	// Return type		: CSkill*
	//            		: ������ ��ų ������
	// Argument         : int skillIndex
	//                  : ������ ��ų ��ȣ
	// Argument         : int level = 1
	//                  : ������ ��ų ����
	CSkill* Create(int skillIndex, int level = 1);

	void LearnAllSkill(CPC* ch);

private:
	map_t			map_;
	CSkillProto**	m_list;		// ��ų ����
	int				m_count;	// ��ų ���� ����
};

class CSkillListNode
{
	CSkill*			m_skill;	// ��ų ������
	CSkillListNode*	m_prev;		// ���� ������
	CSkillListNode* m_next;		// ���� ������

public:
	CSkillListNode(CSkill* skill);
	~CSkillListNode()
	{
		if (m_skill) delete m_skill;
		m_skill = NULL;
	}

	CSkillListNode* prev();
	void prev(CSkillListNode* p);
	CSkillListNode* next();
	void next(CSkillListNode* p);

	CSkill* skill();
	void skill(CSkill* p);

	int m_wearPos;
};

/////////////////////
// Class name	    : CSkillList
// Description	    : ĳ���� ��ų ����Ʈ
class CSkillList
{
	CSkillListNode*		m_head;		// ���
	CSkillListNode*		m_tail;		// ����
	int					m_count;	// ����

public:
	void DeleteInstantSkill(int flag);
	CSkillList();
	~CSkillList();

	/////////////////////
	// Function name	: Add
	// Description	    : ��ų �߰�, ������ ��ų�� �ߺ� �� ��� ������ �缳��
	// Return type		: bool
	//            		: ��������
	// Argument         : CSkill* skill
	//                  : �߰��� ��ų, ���� ��ų�� �ߺ� �� ��� �޸� ������, ���� ��ų�� ������
	bool Add(CSkill*& skill);

	/////////////////////
	// Function name	: Find
	// Description	    : ��ų ã��
	// Return type		: CSkill*
	//            		: ã�� ��ų, ���н� NULL
	// Argument         : int index
	//                  : ã�� ��ų ��ȣ
	CSkill* Find(int index);
	//node ã��
	CSkillListNode* FindNode(int index);

	/////////////////////
	// Function name	: count
	// Description	    : ��ų ����
	int count();

	/////////////////////
	// Function name	: GetIndexString
	// Description	    : ��ų �ε��� ��Ʈ�� ���
	// Return type		: char*
	//            		: �Էµ� ���ڿ� ������
	// Argument         : char* buf
	//                  : ��Ʈ�� ����
	char* GetIndexString(char* buf);
	void GetIndexString(std::string& bnf);

	/////////////////////
	// Function name	: GetLevelString
	// Description	    : ��ų ���� ��Ʈ�� ���
	// Return type		: char*
	//            		: �Էµ� ��Ʈ�� ������
	// Argument         : char* buf
	//                  : ��Ʈ�� ����
	char* GetLevelString(char* buf);
	void GetLevelString(std::string& bnf);

	/////////////////////
	// Function name	: GetHeadPosition
	// Description	    : ����Ʈ ó�� ��ġ�� ��ȯ, ������� NULL
	void* GetHeadPosition();

	/////////////////////
	// Function name	: GetNext
	// Description	    : ����Ʈ�� ��ų�� ��ȯ
	// Argument         : void*& p
	//                  : in: ���� ������ ��ġ, out: ���� ������ ��ġ, ���̻� ������ NULL
	CSkill* GetNext(void*& p);

	////////////////////
	// Function name	: RemoveSkillFor2ndJob
	// Description	    : ���� ������ ��ų �����
	int RemoveSkillFor2ndJob();		// reutrn �ҿ�� skillpoint

	// ��ų �ʱ�ȭ
	void Clear();
	void clearReadySkill();

	/////////////////////
	// Function name	: Remove
	// Description	    : ��ų ���� (�������� �ɼ�/��Ʈ ���������� ���� ��ų ����)
	// Return type		: bool
	//            		: ��������
	// Argument         : CSkill* skill
	//                  : ������ ��ų
	bool Remove(CSkill* skill);

	bool Disable(CSkill* skill);

	bool AddOptionSkill(CSkill* skill, int prob, int wearPos);

	void SaveSkillCoolTime(CPC* pc, std::vector<std::string>& vec);
};

int ApplySkill(CCharacter* ch, CCharacter* tch, CSkill* skill, int itemidx, bool& bApply);
void ApplySkillParty(CPC* ch, CSkill* skill, int itemidx, bool& bApply);
int CalcSkillParam(const CCharacter* ch, const CCharacter* tch, int selfparam, int targetparam);

void ApplySkillExped(CPC* ch, CSkill* skill, int itemidx, bool& bApply);
void ApplySkillGuild(CPC* ch, CSkill* skill, int itemidx, bool& bApply);

bool ApplyWarSkill(CPC* ch, int zone_index);
void ClearWarSkill(CPC* ch);
void ClearWarItemSkill(CPC* ch);
#endif
//
