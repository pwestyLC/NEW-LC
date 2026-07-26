//---------------------------------------------------------------------->>
// Name : LocalDefine.h
// Desc : for localization
// Date : [6/27/2006] , Wooss
//----------------------------------------------------------------------<<

#ifndef	LOCALDEFINE_H_
#define	LOCALDEFINE_H_
#ifdef	PRAGMA_ONCE
	#pragma once
#endif

#include <map>

// #define WORLD_EDITOR
// #define HP_PERCENTAGE		// Hp ��� ��ġ���� �ۼ��������� ����
#define	CRYPT_NET_MSG_LEVEL2		// ��Ʈ��ũ ��Ŷ 2�� ��ȣȭ [trylord 11/09/29]
#define SEED_ENCIPHERMENT	// ���� ��ȣȭ

#if defined G_KOR
	#include "Define_KOR.h"
#endif

#if defined G_USA
	#include "Define_USA.h"
#endif

#if defined G_RUSSIA
	#include "Define_RUS.h"
#endif

#if defined G_GERMAN
	#include "Define_GAMIGO.h"
#endif

#if defined G_BRAZIL
	#include "Define_BRA.h"
#endif // G_BRAZIL

#if defined G_THAI
	#include "Define_THAI.h"
#endif

#include <Common/CommonDef.h>

/********************************************************************************/

// wooss 070228 ----------------------------------------------------->>
// �̺�Ʈ ���� event.lod������ ���� �̿��Ͽ� �̺�Ʈ�� �����Ѵ�.
// �߰��Ǵ� �̺�Ʈ�� ������ ����Ʈ�� ���� �̺�Ʈ �ε����� �°� ���� ��Ų��.
enum eEVENTALL
{
	TEVENT_START					=	0,	
	TEVENT_TREASUREBOX				=	1,	// ���� ���� �̺�Ʈ 
	TEVENT_TEACH					=	2,	// �İ��� �̺�Ʈ 
	TEVENT_FRUIT					=	3,	// ���� �̺�Ʈ 
	TEVENT_CHUSEOK					=	4,	// �߼� �̺�Ʈ 	
	TEVENT_SEPTEMBER				=	5,	// 9�� �̺�Ʈ 
	TEVENT_2PAN4PAN1					=	6,	// 2��4�� �̺�Ʈ 
	TEVENT_2PAN4PAN2					=	7,	// 2��4�� �̺�Ʈ 
	TEVENT_PEPERO					=	8,	// ������ �̺�Ʈ
	TEVENT_XMAS						=	9,	// ũ�������� �̺�Ʈ
	TEVENT_NEWYEAR					=	10, // �ų� �̺�Ʈ
	TEVENT_CHANGE_ARMOR				=	11,	// ����/�� ��ȯ �̺�Ʈ
	TEVENT_SEARCHFRIEND				=	12,	// ģ�� ã�� �̺�Ʈ
	TEVENT_VALENTINE_2006			=	13, // �߷�Ÿ�� �̺�Ʈ
	TEVENT_WHITEDAY					=	14, // ȭ��Ʈ ���� �̺�Ʈ
	TEVENT_OLD_SERVER				=	15,	// ������Ʈ ��� �̺�Ʈ
	TEVENT_NEW_SERVER				=	16,	// ������Ʈ ��� �̺�Ʈ
	TEVENT_SAKURA					=	17, // ������ �̺�Ʈ
	TEVENT_OX_QUIZ					=	18, // OX ���� �̺�Ʈ
	TEVENT_WORLDCUP					=	19, // ������ �̺�Ʈ
	TEVENT_RAIN						=	20, // ����� �̺�Ʈ
	TEVENT_BUDDHIST					=	21,	// �±� �ұ� �̺�Ʈ
//	TEVENT_COLLECT_BUG				=	22,	// ���� ä�� �̺�Ʈ
	TEVENT_NEWSERVER_BASTARD		=	23,	// �ż� �ٽ�Ÿ�� ���� �̺�Ʈ: �ż�
	TEVENT_NEWSERVER_BASTARD_OLD	=	24,	// �ż� �ٽ�Ÿ�� ���� �̺�Ʈ: ����
	TEVENT_CHUSEOK_2006				=	25, // �߼� �̺�Ʈ
	TEVENT_HALLOWEEN				=	26, // �ҷ��� �̺�Ʈ
	TEVENT_XMAS_2006					=   27,	// 2006 ũ�������� �̺�Ʈ
	TEVENT_CHILDREN_DAY				=	28,	// �±� Children Day �̺�Ʈ �İ��� �̺�Ʈ
//	TEVENT_VALENTINE_2007			=	29, // �߷�Ÿ�ε��� �̺�Ʈ
	TEVENT_JPN_2007_NEWSERVER		=	30, // �Ϻ� 2007�� 3�� �ű� ���� ���� ������ �̺�Ʈ
//	TEVENT_WHITEDAY2007				=	31, // ȭ��Ʈ ���� 2007
	TEVENT_SONGKRAN					=	32, // �±� ��ũ�� �̺�Ʈ
	TEVENT_PARENTS_2007				=	34, // ����̳� �̺�Ʈ 	
	TEVENT_GOMDOLI				    =	35, // ������ �̺�Ʈ
	TEVENT_CHILDREN_2007				=	36, // ��̳� �̺�Ʈ
	TEVENT_FLOWERTREE			    =	37, // �ɳ��� �̺�Ʈ 
	TEVENT_TEACHER_2007				=   38, // �����ǳ� �̺�Ʈ
	TEVENT_UCC_2007					=	39, // UCC ���׽�Ʈ �̺�Ʈ
	TEVENT_INDEPENDENCEDAY			=	40, // �̱� ��������� �̺�Ʈ
	TEVENT_SUMMER_2007				=	41, // 2007 ���� �������� �̺�Ʈ
	TEVENT_MOTHER					=	42, // 2007 �±� ��Ӵϳ� �̺�Ʈ
	TEVENT_ADULT_OPEN				=	44, // ���� ���� ���� �̺�Ʈ('����ī�带 ã�ƶ�', '��ħ���� ���!')
	TEVENT_BJMONO_2007				=	45, // SK BJ Mono �̺�Ʈ
	TEVENT_TG2007_1000DAYS			=	46, // ��Ʈ ī���� õ�� �̺�Ʈ
	TEVENT_TG2007_FRUITFULL			=	47, // ǳ�� �̺�Ʈ
	TEVENT_TG2007_SCREENSHOT			=	48, // ��ũ���� �̺�Ʈ
//	TEVENT_HOLLOWEEN2007				=	49,	// �ҷ��� �̺�Ʈ(2007)
	TEVENT_XMAS_2007					=	50, // ũ�������� �̺�Ʈ(2007)
	TEVENT_NEWYEAR_2008				=	51, // 2008 �ų� �̺�Ʈ
	TEVENT_LUNARNEWYEAR_2008			=	52,	// 2008 ���� �̺�Ʈ
	TEVENT_RED_TREASUREBOX			=	53, // ������ �������� �̺�Ʈ
	TEVENT_SAKURA_2008				=	54, // 2008 ���� �̺�Ʈ
	TEVENT_CHAOSBALL				=	55, // ī������ �̺�Ʈ
	TEVENT_NOMNOMNOM2008				=	56, // ���� �̺�Ʈ
	TEVENT_SUMMER_2008				=	57, // 2008 ���� �̺�Ʈ
	TEVENT_PHOENIX					=	58, // �Ǵн� �̺�Ʈ
	TEVENT_HANARO					=	59, // �ϳ��� �̺�Ʈ
	TEVENT_ADD_UP_AFRON_2009			=	60, // ������, ������ ���� ���� �̺�Ʈ(������ ���� �ٿ�)
	TEVENT_QUARTER_FINAL_TOUR		=	61, // ��Ʈī���� ���� ��ʸ�Ʈ 8�� ���� �̺�Ʈ
	TEVENT_GOLDWEEK					=	62,	// �Ϻ� �����ũ �̺�Ʈ
	TEVENT_WORLDCUP_2010				=	63, // ($E_WC2010) 2010 ���ư� ������ Event 1 Ȳ�� �౸���� ��ƶ�
	TEVNET_WORLDCUP_2010_ATTENDANCE	=	67, // ($E_WC2010) 2010 ���ư� ������ Event 3 ���� ���� �����ϱ�
	TEVENT_OCEANS_PROMOTION			=	68, // ��ȭ '���ǽ�' ���� �̺�Ʈ(�ܹ߼� �̺�Ʈ ������ ���) 100907 ��ĭ��� �̺�Ʈ
	TEVENT_PROMOTION2				=	69,	// ���� ��� �̺�Ʈ : ������ �Ѱ��� ���� ��� ����
	TEVENT_COMEBACK					=	70,	// �޸� ���� ���� �̺�Ʈ
	TEVENT_BIRTHDAY					=	71,	// ĳ���� 1�ֳ� �̺�Ʈ
	TEVENT_LOI_KRATHONG_TLD			=	72,	// �±� ũ���� �̺�Ʈ
	TEVENT_TLD_KING_BIRTHDAY		=	73,	// �±� ���� ź���� �̺�Ʈ
	TEVNET_WORLDCUP_2010_TOTO		=	80,	// ($E_WC2010) 2010 ���ư� ������ Event 2 ��±��� �����϶� ����
	TEVNET_WORLDCUP_2010_TOTO_STATUS =  81, // ($E_WC2010) 2010 ���ư� ������ Event 2 ��±��� �����϶�	��Ȳ
	TEVNET_WORLDCUP_2010_TOTO_GIFT	=	82, // ($E_WC2010) 2010 ���ư� ������ Event 2 ��±��� �����϶� ����
	TEVENT_END								
};

//////////////////////////////////////////////////////////////////////////
// ���� lod���� �о���� ��Ŀ��� �� �������� �˷��ִ� ������� ����. Event enum ���ε���.
//////////////////////////////////////////////////////////////////////////
typedef enum _eventAutomationList
{
	A_EVENT_COLLECT_BUG		= 22,	// ���� ä�� �̺�Ʈ
	A_EVENT_VALENTINE_DAY	= 29,	// �߷�Ÿ�� ���� �̺�Ʈ
	A_EVENT_WHITE_DAY		= 31,	// ȭ��Ʈ ����
	A_EVENT_SONGKRAN		= 32,	// �±� ��ũ�� �̺�Ʈ
	A_EVENT_EGGS_HUNT		= 33,	// ��Ȱ�� �̺�Ʈ
	A_EVENT_HOLLOWEEN		= 49,	// �ҷ��� �̺�Ʈ
	
};

extern ENGINE_API std::map<int,int> g_mapEvent;

// �̺�Ʈ�� �����Ǿ� �ִٸ� event value���� �����ϰ� �ƴϸ� FALSE(0)����...
#define IS_EVENT_ON(x) ((g_mapEvent.find(x)==g_mapEvent.end())?0:g_mapEvent[x])
// ------------------------------------------------------------------<<

// WSS_NPROTECT 070402 ------------------------------->>
#if defined( DEBUG ) || defined( _DEBUG ) || !defined ( USE_GAMEGUARD )
#define NO_GAMEGUARD
#endif
//#define NO_GAMEGUARD
// ---------------------------------------------------<<

// �𽺾�������� ���̱� ���� ������ �ڵ� ����ȭ ��ũ��
// ### This will not work in 64 bit version. Disable
#if (!defined _DEBUG) && (!defined KALYDO) && (!defined VER_TEST) && (defined __MSVC_INLINE__) && (defined  PLATFORM_32BIT) && (defined ENABLE_X86_ASM)
#define paste(a, b) a##b
#define pastesymbols(a, b) paste(a, b)
#define OBFUSCATE() \
	_asm { mov	eax, __LINE__ * 0x86f16351			}; \
	_asm { cmp	eax, __LINE__ * 0x6d489cb1			}; \
	_asm { je	pastesymbols(Junk, __LINE__)		}; \
	_asm { mov	eax, pastesymbols(After, __LINE__)	}; \
	_asm { jmp	pastesymbols(After, __LINE__)		}; \
	_asm { pastesymbols(Junk, __LINE__):			}; \
	_asm { _emit	(0xd8 + __LINE__ % 8)			}; \
	_asm { pastesymbols(After, __LINE__):			};
#else

#define OBFUSCATE() (void)0
#endif

#endif
