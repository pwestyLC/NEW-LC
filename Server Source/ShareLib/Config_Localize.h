#ifndef __CONFIG_LOCALIZE_H__
#define __CONFIG_LOCALIZE_H__
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

// ������ ���ö����� ���Ϸ� ����


#include "Config_Localize_USA.h"

#include "HunterDefines.h"
//#include "Config_Localize_USA_CLASSIC.h"
// �̺�Ʈ�� ��⼭ ã����.
#include "Config_Localize_event.h"

/////////////////////////////////////////////////////////////////////////////////

// ---------------- ��ü ���� ��� ������  ----------------- //

#define USE_GROCERY_ITEM1               2458    // ��ȭ�� �̿� �ֹ��� 1��
#define USE_GROCERY_ITEM2               2459    // ��ȭ�� �̿� �ֹ��� 7��
#define USE_GROCERY_ITEM3               2460    // ��ȭ�� �̿� �ֹ��� 30��

#define USE_WAREHOUSE_ITEM1             2455    // â�� �̿� �ֹ��� 1��
#define USE_WAREHOUSE_ITEM2             2456    // â�� �̿� �ֹ��� 7��
#define USE_WAREHOUSE_ITEM3             2457    // â�� �̿� �ֹ��� 30��

#define SHOW_HP_ITEM1                   2461    // ��ġ ������ ( ĳ������ HP�� ��  ���� ) 1��
#define SHOW_HP_ITEM2                   2462    // ��ġ ������ ( ĳ������ HP�� ��  ���� ) 7��
#define SHOW_HP_ITEM3                   2463    // ��ġ ������ ( ĳ������ HP�� ��  ���� ) 30��

#define ONE_PERIOD_ITEM                 2404
#define SEVEN_PERIOD_ITEM               2405
#define THIRTY_PERIOD_ITEM              2406

#define EXPERIENCE_COMPETITION_ITEM     2407
#define PERIOD_COMPETITION_ITEM         2408
#define USE_COMPETITION_ITEM_NAS        1000

#define SKILL_POTION_ITEM               2452    // ������ ����
#define PLATINUM_SKILL_POTION_ITEM      2453    // �÷�Ƽ�� ������ ����
#define PET_HPRECOVER_ITEM              2454    // �� HP ȸ�� ����
#define FIRECRACKER_ITEM                2403    //���� ������

#define LOW_RUNE_PROTECTION_ITEM        2394
#define HIGH_RUNE_PROTECTION_ITEM       2395
#define HIGH_RUNE_PROTECTION_ITEM_LEVLEL_LIMIT_1_60		5091
#define HIGH_RUNE_PROTECTION_ITEM_LEVLEL_LIMIT_61_90	5092
#define SUPER_HIGH_RUNE_PROTECTION_ITEM	6218
#define MIDDLE_HIGH_RUNE_PROTECTION_ITEM		11023

#define PET_RED_COLOR_ITEM              2396    // ������
#define PET_SCARLET_COLOR_ITEM          2397    // ��ȫ
#define PET_YELLOW_COLOR_ITEM           2398    // ���
#define PET_GREEN_COLOR_ITEM            2399    // �ʷ�
#define PET_BLUE_COLOR_ITEM             2400    // �Ķ�
#define PET_DEEP_BLUE_COLOR_ITEM        2401    // ����
#define PET_VIOLET_COLOR_ITEM           2402    // ����
#define PET_WHITE_COLOR_ITEM            2568    // ��
#define PET_BLACK_COLOR_ITEM            2569    // ����
#define PET_NON_COLOR_ITEM              2869    // �⺻��
#define PET_BLACK_HEART_COLOR_ITEM      3548    // ������ ��Ʈ
#define PET_WHITE_HEART_COLOR_ITEM      3549    // �Ͼ縻 ��Ʈ
#define PET_YELLOW_HEART_COLOR_ITEM     3550    // ����� ��Ʈ
#define HORSE_COLOR_CHANGE_ITEM			740		// �� ���󹮾� ����
#define DRAGON_COLOR_CHANGE_ITEM		741		// �� ���󹮾� ����
#define HORSE_WILLIAM_COLOR_ITEM		6728	// Ÿ�¸� ���� ������ WILLIAM
#define HORSE_ALBER_COLOR_ITEM			6729	// Ÿ�¸� ���� ������ ALBER
#define HORSE_REDEYE_COLOR_ITEM			6730	// Ÿ�¸� ���� ������ REDEYE
#define HORSE_ZEBRA_COLOR_ITEM			6731	// Ÿ�¸� ���� ������ ZEBRA
#define HORSE_HAROLD_COLOR_ITEM			6732	// Ÿ�¸� ���� ������ HAROLD
#define HORSE_VIOLET_COLOR_ITEM			6733	// Ÿ�¸� ���� ������ VIOLET

// ---------------- ������ ���� �ý��� --------------------- //

// ��밳������ 5,6�̺�Ʈ ��Ʈ�ʵ� ��� ���� �������� �����
#define		ETC_EVENT_JUNO_RENEWAL_MESSAGEBOX_POPUP	(1 << 5)  // �˾� üũ
#define		ETC_EVENT_JUNO_RENEWAL_QUESTCOMPLETE	(1 << 6)  // ����Ʈ �Ϸ� üũ

// �̺�Ʈ �ڵ�ȭ �ý���

// ----------------- ���� define ���� start -------------- //

// -------------------- �̺�Ʈ ���� start -------------------- //

#define     NOTADULTMIN                 6
#define     NOTADULTMAX                 22
#define     NOTADULTNOTICE              21
#define     NOTADULTNOTICE_INTERVAL     10

#endif
