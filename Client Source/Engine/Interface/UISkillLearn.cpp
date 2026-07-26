#include "stdh.h"

// ��� ����. [12/2/2009 rumist]
#include <vector>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UISkillLearn.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Contents/Base/UISkillNew.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Base/UIQuestBookNew.h>
#include <Engine/Interface/UIHelp.h>
#include <Engine/Contents/Base/UIDurability.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/function/ItemComposeUI.h>
#include <Engine/Contents/function/SSkillLearnUI.h>
#include <Engine/Contents/function/SealComposeUI.h>

#define SKILL_LEARNED_COLOR				0xF2F2F2FF
#define NOT_SATISFACTION_COL			0xFF0000FF
#define SATISFACTION_COL				0xFFFF00FF
#define EXTENSION_LEVEL					(31)
#define SKILL_NOT_EXIST					-1
// [KH_07044] 3�� ���� ���� �߰�
extern INDEX g_iShowHelp1Icon;

enum eSelection
{
	SKILL_LEARN,
	SKILL_TALK,
	SKILL_EVENT,
	SKILL_JOB_1,			// �����ϱ� 1��
	SKILL_JOB_2,			// �����ϱ� 2��
	SKILL_NPC_HELP,
	SKILL_TITAN,
	SKILL_KNIGHT,
	SKILL_HEALER,
	SKILL_MAGE,
	SKILL_ROGUE,
	SKILL_SORCERER,
	SKILL_NIGHTSHADOW,
#ifdef CHAR_EX_ROGUE
	SKILL_EX_ROGUE,	// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
	SKILL_EX_MAGE,	// 2013/01/08 jeil EX������ �߰� 
#endif
	SKILL_QUEST,
#ifdef DURABILITY
	ITEM_DURABILITY,
	ITEM_RECOVERY,
#endif	//	DURABILITY
	ITEM_COMPOSE,
	ITEM_SEAL_COMPOSE
};

enum eSatisfactionType
{
	SKILL_CONDITION_LEVEL = 0,
	SKILL_CONDITION_SP,
	SKILL_CONDITION_STR,
	SKILL_CONDITION_DEX,
	SKILL_CONDITION_INT,
	SKILL_CONDITION_CON,
	SKILL_CONDITION_SKILL_0,
	SKILL_CONDITION_SKILL_1,
	SKILL_CONDITION_SKILL_2,
	SKILL_CONDITION_ITEM_0,
	SKILL_CONDITION_ITEM_1,
	SKILL_CONDITION_ITEM_2,
};

// ----------------------------------------------------------------------------
// Name : CUISkillLearn()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUISkillLearn::CUISkillLearn()
{
	m_iSelChangeJob	= -1;
	m_iMobIdx = -1;
	m_iMobVirIdx = -1;
	m_bQuest = FALSE;
}

// ----------------------------------------------------------------------------
// Name : ~CUISkillLearn()
// Desc : Destructor
// ----------------------------------------------------------------------------
CUISkillLearn::~CUISkillLearn()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////////
//
// ���� ��ų�� ������ �����ϴ����� üũ�մϴ�.
//
//////////////////////////////////////////////////////////////////////////
int CUISkillLearn::IsSatisfiedSkill(int nSkillIndex, int nLevel, BOOL bSpecial )
{
	int nSatisfied = 0;

	if( nSkillIndex <= 0 )
		return SKILL_NOT_EXIST;

	if (nLevel > 0)
		--nLevel; // ������ ������ 1����, ��ų������ ���� �迭�� 0 ����

	if (nLevel < 0)
	{
		LOG_DEBUG("��ų ������ %d �Դϴ�.", nLevel);
		return SKILL_NOT_EXIST;
	}

	if( !bSpecial )
	{
		CSkill		&rSkill = _pNetwork->GetSkillData( nSkillIndex );

		int		nLearnSkillIndex[3];
		SBYTE	sbLearnSkillLevel[3];
		int		nLearnItemIndex[3];
		SQUAD	nLearnItemCount[3];
		BOOL	bLearnSkill = FALSE;
		BOOL	bLearnItem = FALSE;

		for( int i = 0; i < 3; i++ )
		{
			nLearnSkillIndex[i] = rSkill.GetLearnSkillIndex( nLevel, i );
			sbLearnSkillLevel[i] = rSkill.GetLearnSkillLevel( nLevel, i );
			nLearnItemIndex[i] = rSkill.GetLearnItemIndex( nLevel, i );
			nLearnItemCount[i] = rSkill.GetLearnItemCount( nLevel, i );

			if( nLearnSkillIndex[i] != -1 )
				bLearnSkill = TRUE;
			if( nLearnItemIndex[i] != -1 )
				bLearnItem = TRUE;
		}

		// �ʿ� ���� üũ
		if(_pNetwork->MyCharacterInfo.level < rSkill.GetLearnLevel( nLevel ))
			nSatisfied |= NOT_SATISFIED_LEVEL;
		// �ʿ� ���õ� üũ
		if((_pNetwork->MyCharacterInfo.sp / 10000) < rSkill.GetLearnSP( nLevel ))
			nSatisfied |= NOT_SATISFIED_SP;
		// �ʿ� �ɷ�ġ üũ

		const int iLearnStr = rSkill.GetLearnStr( nLevel );
		const int iLearnDex = rSkill.GetLearnDex( nLevel );
		const int iLearnInt = rSkill.GetLearnInt( nLevel );
		const int iLearnCon = rSkill.GetLearnCon( nLevel );

		if( iLearnStr > 0 ) 
		{
			if( _pNetwork->MyCharacterInfo.str - _pNetwork->MyCharacterInfo.opt_str  < iLearnStr )
				nSatisfied |= NOT_SATISFIED_STR;
		}

		if( iLearnDex > 0 ) 
		{
			if( _pNetwork->MyCharacterInfo.dex - _pNetwork->MyCharacterInfo.opt_dex < iLearnDex )
				nSatisfied |= NOT_SATISFIED_DEX;
		}

		if( iLearnInt > 0 ) 
		{
			if( _pNetwork->MyCharacterInfo.intel - _pNetwork->MyCharacterInfo.opt_intel < iLearnInt )
				nSatisfied |= NOT_SATISFIED_INT;
		}

		if( iLearnCon > 0 ) 
		{
			if( _pNetwork->MyCharacterInfo.con - _pNetwork->MyCharacterInfo.opt_con < iLearnCon )
				nSatisfied |= NOT_SATISFIED_CON;
		}

		CUIManager* pUIManager = CUIManager::getSingleton();

		// �ʿ� ��ų üũ
		if( bLearnSkill )
		{
			for( int i = 0; i < 3; i++ )
			{
				if (nLearnSkillIndex[i] != -1)
				{
					//�� ��ų �������� ����� ã��.
					// ĳ���� �������ΰ�?
					int nCurrentSkillLevel = MY_INFO()->GetSkillLevel(nLearnSkillIndex[i]);
					if(nCurrentSkillLevel < sbLearnSkillLevel[i])
					{
						nSatisfied |= (NOT_SATISFIED_SKILL_0 << i);
					}
				}
			}
		}

		// �ʿ� ������ üũ
		if( bLearnItem )
		{
			for( int i = 0; i < 3; i++ )
			{
				//2013/04/10 jeil
				if( nLearnItemIndex[i] != -1 )
				{
					if(nLearnItemIndex[i] == 19)
					{
						if(_pNetwork->MyCharacterInfo.money < nLearnItemCount[i])
						{
							nSatisfied |= (NOT_SATISFIED_ITEM_0 << i);
						}
					}
					else
					{
						SQUAD nCurrentItemCount = pUIManager->GetInventory()->GetItemCount(nLearnItemIndex[i]);
						if(nCurrentItemCount < nLearnItemCount[i])
						{
							nSatisfied |= (NOT_SATISFIED_ITEM_0 << i);
						}
					}
				}
			}
		}
	}
	else
	{
		CSpecialSkill* pSSkill = CSpecialSkill::getData( nSkillIndex );

		if (pSSkill == NULL)
			return SKILL_NOT_EXIST;

		// Get learning condition
		int		nLearnSkillIndex;
		SBYTE	sbLearnSkillLevel;

		nLearnSkillIndex	= pSSkill->GetLearnSkillIndex();
		sbLearnSkillLevel	= pSSkill->GetLearnSkillLevel();

		// �ʿ� ���� üũ
		if(_pNetwork->MyCharacterInfo.level < pSSkill->GetLearnLevel( nLevel ))
			nSatisfied |= NOT_SATISFIED_LEVEL;
		// �ʿ� ���õ� üũ
		if((_pNetwork->MyCharacterInfo.sp / 10000) < pSSkill->GetLearnSP( nLevel ))
			nSatisfied |= NOT_SATISFIED_SP;

		if( nLearnSkillIndex != -1 )
		{
			int nCurrentSkillLevel = MY_INFO()->GetSkillLevel(nLearnSkillIndex, true);
			if(nCurrentSkillLevel < sbLearnSkillLevel)
			{
				nSatisfied |= NOT_SATISFIED_SKILL_0;
			}
		}
	}

	return nSatisfied;
}

void CUISkillLearn::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight )
{
	CUIWindow::Create(pParentWnd, nX, nY, nWidth, nHeight);
}

// ----------------------------------------------------------------------------
// Name : OpenSkillLearn()
// Desc : nMasterType�� �Ϲ� ��ų�϶��� ����, Ư�� ��ų�϶��� Ư�� ��ųŸ���� �˴ϴ�.
// ----------------------------------------------------------------------------
void CUISkillLearn::OpenSkillLearn( int iMobIndex, int iMobVirIdx, BOOL bHasQuest, FLOAT fX, FLOAT fZ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	// If this is already exist
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_SKILLLEARN_REQ ) || IsVisible() )
		return;
	
	// Special Skill
	if( pUIManager->DoesMessageBoxLExist( MSGLCMD_SSKILLLEARN_REQ ) || IsVisible() )
		return;

	// Set position of target npc
	m_fNpcX = fX;
	m_fNpcZ = fZ;
	m_iMobIdx = iMobIndex;
	m_bQuest = bHasQuest;

	m_iMobVirIdx = iMobVirIdx;

	CMobData* MD	= CMobData::getData(iMobIndex);
	int nSSkillType	= MD->GetSpecialSkillMaster();
	CTString	strNpcName = CMobData::getData(iMobIndex)->GetName();
	m_bSpecial		= MD->IsSSkillMaster() ? TRUE : FALSE;

	if( MD->IsSSkillMaster() )		// Ư�� ��ų �������϶�...
	{
		// FIXME : �Ʒ��� ���� �޼����� �׶� �׶� �ٸ��� �뷫 ����.
		switch( nSSkillType )
		{
		case SSKILL_MINING:			// ä��
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 630, "ä�� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 631, "������ ä���ϴ°Ŵ� �׸� ����� �ʾ�." ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 632, "������ �󸶸�ŭ ���� �ð��� ���� ���� ĳ�����İ� �Ƿ��� �¿� ����." ), -1, 0xA3A1A3FF );		
			}
			break;
		case SSKILL_GATHERING:		// ä��
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 633, "ä�� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 634, "ũ���� ä���� ���� ���� ����� �ʿ�����." ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 635, "����� ������ �������� �� ���� ���� ä���ϰ� �߸� �ϸ� ���� ����ٴ� ũ���� �ɵ� ���� �� �ִٳ�." ), -1, 0xA3A1A3FF );		
			}
			break;
		case SSKILL_CHARGE:			// ����
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 636, "���� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 637, "���� ����� ���� ���� �˰� �ͽ��ϱ�?" ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 638, "�� �� ������ ���� ����� ���ٸ� �������� ���Ҹ� ���� �� ���� ���Դϴ�.  ��� ���ðڽ��ϱ�?" ), -1, 0xA3A1A3FF );	
			}
			break;
		case SSKILL_STONE:			// �������ü�
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 639, "�������� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
#ifdef DURABILITY
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 6194, "���� ��� ���°͵� �߿� ������, ��� �������� ������ �ƹ� �����ۿ��� ����." ), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 6195, "�ڳ� ��� ������ ���� ���°�? �� ��� ���� ����� ������" ), -1, 0xA3A1A3FF );

				CTString strTemp;
				strTemp.PrintF( _S( 6429, "�ռ��Ѵ�." ) );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strTemp, ITEM_COMPOSE );
				strTemp.PrintF( _S( 8427, "Combine Seal" ) );	
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strTemp, ITEM_SEAL_COMPOSE );
				strTemp.PrintF( _S( 6192, "�������� �����Ѵ�." ) );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strTemp, ITEM_DURABILITY );
				strTemp.PrintF( _S( 6193, "�ִ� �������� �����Ѵ�." ) );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strTemp, ITEM_RECOVERY );
#else	//	DURABILITY
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 640, "������ ���� �ϴ� ���� �ƹ��� �ϴ� ���� �Ƴ�! �ڳװ� ��� ���ڴٰ�?" ), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 641, "���� �����̵��� ���� ���� �ϴ� ���� �ʹ� ���� ���� ������ �־�." ), -1, 0xA3A1A3FF );

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, _S( 6429, "�ռ��Ѵ�." ), ITEM_COMPOSE );
#endif	//	DURABILITY
			}
			break;
		case SSKILL_PLANT:			// �Ĺ�������
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 642, "�Ĺ����� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 643, "ũ���� �̿��� ���� ����� �ʹٰ�? ������ ������." ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 644, "ũ������ �ʱ��� ������� ��û���� ���� �ð��� �ɷ�! ���� ����� �� �� ������?" ), -1, 0xA3A1A3FF );		
			}
			break;
		case SSKILL_ELEMENT:		// ����������
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 645, "�������� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 646, "���Ҹ� ���� �Ϸ��� ����� ������ ���� �γ��� �ʿ� �մϴ�." ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 647, "������ �������� ���⸸ �Ѵٸ� �׿� �����ϴ� ������ ���� �� ���� ���Դϴ�. �ڿ��� �������� ���� �����ϱ��." ), -1, 0xA3A1A3FF );		
			}
			break;

		case SSKILL_MAKE_WEAPON:	// ��������
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 648, "�������� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 649, "�̷�! �� ���� ������ ���� �; �� ģ����." ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 650, "�� �� �̻� ���⸦ ������ �ʾ� ! �� �̻� ������ ���� �ƴ϶��! ���� �ص� �ҿ� ����." ), -1, 0xA3A1A3FF );		
			}
			break;

		case SSKILL_MAKE_POTINO: // ���� ����
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 767, "���� ���� ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 768, "���� ������ ���ɽ������� ����� �۾��Դϴ�." ), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 769, "������ ã�� ����� ������ ���� ����� ���� �����̱⵵ �մϴ�. �������� ���� ���۱���� ��� ���ðڳ���?" ), -1, 0xA3A1A3FF );
			}
			break;
		case SSKILL_MAKE_WEAR:
		case SSKILL_MAKE_G_B:
		case SSKILL_MAKE_ARMOR:
		case SSKILL_MAKE_H_S:
			{
				// Create skill learn message box
				pUIManager->CreateMessageBoxL( _S( 651, "������ ��ų" ), UI_SKILLLEARN, MSGLCMD_SSKILLLEARN_REQ );		

				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 652, "�����̳��� ���� ��� �ʹٸ� �� ���� ����� ��� ����!" ), -1, 0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, TRUE, _S( 653, "������ ���䰡 ���Ƽ� ���� �Ҹ� �ϴٱ�!" ), -1, 0xA3A1A3FF );		
			}
			break;
		}
		
		CTString strMessage;		
		strMessage.PrintF( _S( 1218, "��ų�� �����Ѵ�." ) );		
		pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strMessage, SKILL_LEARN );

		if( bHasQuest )
		{
			// 2009. 05. 27 ������
			// �̾߱��Ѵ� ���� ó��
			CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_SSKILLLEARN_REQ);				
		}
			
		strMessage.PrintF(_S( 1748, "NPC �ȳ�" ));
		pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strMessage, SKILL_NPC_HELP );

		strMessage.PrintF( _S( 1220, "����Ѵ�." ) );		
		pUIManager->AddMessageBoxLString( MSGLCMD_SSKILLLEARN_REQ, FALSE, strMessage );
	}
	// ITS# 4252 : BUG-FIXED  [9/26/2011 rumist]
	else if( iMobIndex == 1200 || iMobIndex == 1198 )	// Ÿ���� NPC - ��ų ������ Ǫġ��
	{	// ����� ��ų ������ UI�� �����ش�
		PriorityOpen(iMobIndex, bHasQuest, FALSE);
	}
	else						// �Ϲ� ��ų �������϶�...
	{
		const int iJob = _pNetwork->MyCharacterInfo.job;
		// If job is different
		if( MD->GetSkillMaster() != iJob )
		{
			// WSS_BUG_FIX 070802 ------>><<
			if( pUIManager->DoesMessageBoxExist( MSGCMD_SKILLLEARN_NOTIFY ) ) { return;}

			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo( _S( 270, "��ų" ), UMBS_OK,
				UI_SKILLLEARN, MSGCMD_SKILLLEARN_NOTIFY );
			MsgBoxInfo.AddString( _S(3589,"�ش� ������ ��ų�� ������ �� �����ϴ�.") );
			pUIManager->CreateMessageBox( MsgBoxInfo );
			return;
		}
		
		// Create skill learn message box
		pUIManager->CreateMessageBoxL( _S( 270, "��ų" ), UI_SKILLLEARN, MSGLCMD_SKILLLEARN_REQ );

		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, TRUE, strNpcName, -1, 0xE18600FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, TRUE, _S( 271, "���Ӿ��� ����ϴ� �ڸ��� ������ ������ �տ� ���� �� �ִ� ��!\n\n�׷� ������ ������ �ִ� �ڸ� �ε��ϴ� ���� ���� �ϴ� ������.\n" ), -1, 0xA3A1A3FF );
		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, TRUE, _S( 272, "������ �ڳ� ���ؿ� �´� ��ų�� �����Ͽ� �������� �ϰԳ�." ), -1, 0xA3A1A3FF );

		CTString strMessage;
		strMessage.PrintF( _S( 1218, "��ų�� �����Ѵ�." ) );		
		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, FALSE, strMessage, SKILL_LEARN );

		if( bHasQuest )
		{
			// 2009. 05. 27 ������
			// �̾߱��Ѵ� ���� ó��
			CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_SKILLLEARN_REQ);				
		}

		// ���� ���� �����̰� ������ ���°� �ƴҶ�...
		// ����Ʈ ������� ������ �����Ƿ�. [8/6/2010 rumist]
		if( _pNetwork->MyCharacterInfo.level >= EXTENSION_LEVEL && _pNetwork->MyCharacterInfo.job2 == 0 &&
			_pNetwork->MyCharacterInfo.job != NIGHTSHADOW )
		{
			strMessage.PrintF( _S( 1223, "[%s]�� ����" ), CJobInfo::getSingleton()->GetExtensionName( iJob, 0 ) );	
			pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, FALSE, strMessage, SKILL_JOB_1 );

			strMessage.PrintF( _S( 1223, "[%s]�� ����" ), CJobInfo::getSingleton()->GetExtensionName( iJob, 1 ) );	
			pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, FALSE, strMessage, SKILL_JOB_2 );
		}

		strMessage.PrintF(_S( 1748, "NPC �ȳ�" ));
		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, FALSE, strMessage, SKILL_NPC_HELP );

		strMessage.PrintF( _S( 1220, "����Ѵ�." ) );		
		pUIManager->AddMessageBoxLString( MSGLCMD_SKILLLEARN_REQ, FALSE, strMessage );

		
	}
}

// ----------------------------------------------------------------------------
// Name : PriorityOpen()
// Desc : ����� ��ų �������� UI â
//			��ų ���� UI â���� ���� ����
// ----------------------------------------------------------------------------	
// BUF FIX : ITS# 4472 [10/13/2011 rumist]
void CUISkillLearn::PriorityOpen(int iIndex, BOOL bHasQuest, BOOL bUseCard/* =FALSE */ )
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if (pUIManager->DoesMessageBoxLExist(MSGLCMD_RESERVE_REQ)) return;
	
	CTString	strNpcName = CMobData::getData(iIndex)->GetName();
	// Create skill learn message box
	pUIManager->CreateMessageBoxL( _S( 270, "��ų" ), UI_SKILLLEARN, MSGLCMD_RESERVE_REQ );

	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, TRUE, strNpcName, -1, 0xE18600FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, TRUE, _S( 271, "���Ӿ��� ����ϴ� �ڸ��� ������ ������ �տ� ���� �� �ִ� ��!\n\n�׷� ������ ������ �ִ� �ڸ� �ε��ϴ� ���� ���� �ϴ� ������.\n" ), -1, 0xA3A1A3FF );
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, TRUE, _S( 3541,"�״� ���� ������ �Ѵ� ���ΰ�? �׷� ������ ������ �ִ� �ڸ� �ε� �ϴ� ���� �� ������! ������ �Ǿ� �ְ���?"), -1, 0xA3A1A3FF);

	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3555, "Ÿ��ź ��ų�� �����Ѵ�."),SKILL_TITAN);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3556, "����Ʈ ��ų�� �����Ѵ�."),SKILL_KNIGHT);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3557, "���� ��ų�� �����Ѵ�."),SKILL_HEALER);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3558, "������ ��ų�� �����Ѵ�."),SKILL_MAGE);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3559, "�α� ��ų�� �����Ѵ�."),SKILL_ROGUE);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 3560, "�Ҽ��� ��ų�� �����Ѵ�."),SKILL_SORCERER);
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 4797, "����Ʈ ������ ��ų�� �����Ѵ�."),SKILL_NIGHTSHADOW);
#ifdef CHAR_EX_ROGUE
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 5755, "EX�α� ��ų�� �����Ѵ�."),SKILL_EX_ROGUE);	// [2012/08/27 : Sora] EX�α� �߰�
#endif
#ifdef CHAR_EX_MAGE
	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 5843, "��ũ������ ��ų�� �����Ѵ�."),SKILL_EX_MAGE);	// 2013/01/08 jeil EX������ �߰� ��Ʈ�� ������ �߰� ���� �ʿ� 
#endif

	// 2009. 05. 27 ������
	// �̾߱��Ѵ� ���� ó��
	// quest bug FIX : ITS#4472  [10/13/2011 rumist]
	if( bHasQuest )
		CUIQuestBook::AddQuestListToMessageBoxL(MSGLCMD_RESERVE_REQ);				

	pUIManager->AddMessageBoxLString( MSGLCMD_RESERVE_REQ, FALSE, _S( 1220, "����Ѵ�." ) );
}

// ----------------------------------------------------------------------------
// Name : MsgBoxCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUISkillLearn::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	switch( nCommandCode )
	{
	case MSGCMD_SKILLLEARN_NOTIFY:
		{
			CUIManager::getSingleton()->CloseMessageBox(MSGCMD_SKILLLEARN_NOTIFY);
		}
		break;

	case MSGCMD_CHANGEJOB:			// ���� �Ҳ�����?
		if( bOK )
		{
			// ������ �޼��� ������.
			_pNetwork->ChangeJobReq( m_iSelChangeJob, m_iMobVirIdx );
		}
		break;
	}
}

// ----------------------------------------------------------------------------
// Name : MsgBoxLCommand()
// Desc :
// ----------------------------------------------------------------------------
void CUISkillLearn::MsgBoxLCommand( int nCommandCode, int nResult )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CJobInfo* pInfo = CJobInfo::getSingleton();

	CTString strMessage;

	switch( nCommandCode )
	{
	case MSGLCMD_SKILLLEARN_REQ:
		if( nResult == SKILL_LEARN )					// ��ų�� �����Ѵ�.
		{
			//pUIManager->RearrangeOrder( UI_SKILLLEARN, TRUE );

// [KH_07044] 3�� ���� ���� �߰�
			if(g_iShowHelp1Icon)
			{
				pUIManager->GetHelp3()->ClearHelpString();
				pUIManager->GetHelp3()->AddHelpString(_S(3308, "ĳ���Ͱ� ��� �� �ִ� ��ų�� ����� �������ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3309, "����� ��ų �������� Ŭ���ϸ� �ش� ��ų�� ������ �ʿ������� ǥ�õǸ� ���� ���� ��ų�� �����ߴٸ� ��ų �������� Ŭ�� �� �� ���� ��ư�� �����ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3310, "�� ��ų�� ���µ� �ʿ��� ���ǿ� ������ ��쿡�� ��ų�� ������ �� �ֽ��ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3311, "�� ��ų�� ��� ���� ��ų ���� �� ������ ���� �ʿ��� ���õ��� �ڵ� �谨�˴ϴ�."));
				pUIManager->GetHelp3()->AddHelpString(_S(3312, "�� ������ ��ų�� ĳ������ ��ų â(ALT+S)���� Ȯ���� �� �ֽ��ϴ�."));
				pUIManager->GetHelp3()->OpenHelp(this);
			}

			pUIManager->GetSkillNew()->OpenUI(m_iMobIdx, m_iMobVirIdx, m_bQuest, m_fNpcX, m_fNpcZ);

		}
		else if( nResult == SKILL_TALK )				// �̾߱� �Ѵ�.
		{
			//TODO : NewQuestSystem
			// ����Ʈ â ����
			CUIQuestBook::TalkWithNPC();
		}
		else if( nResult == SKILL_JOB_1 )				// ���� Ŭ���� 1
		{
			pUIManager->CreateMessageBoxL( _S( 1224, "���� ����" ), UI_SKILLLEARN, MSGLCMD_CHANGEJOB_REQ );		
			const int iNeedLevel	= EXTENSION_LEVEL;
			const SQUAD	llNeedNas	= 50000;
			const int iJob			= _pNetwork->MyCharacterInfo.job;

			CTString strNeedNas;
			strNeedNas.PrintF("%I64d", llNeedNas);
			pUIManager->InsertCommaToString(strNeedNas);

			// FiXME : �Ʒ� �κ��� ������ �ʿ��� �κ�.

			switch( iJob )
			{
			case TITAN:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_HIGHLANDER ), -1, 0xFFC672FF );				
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1225, "�� Ŭ���� ����� ���ݷ��� ������ Ŭ�����μ� ������ �Ͱ��� �ۺ״� ���ݼ��μ��� ���� ������ �� ���� Ŭ�����Դϴ�.\n" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1226, "��� ���� : ����" ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 1227, "���� ���� : %dlv�޼�, ���� ũ���� lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );					
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1229, "�� : ���ݻ��, ������� ���" ), -1, 0xA3A1A3FF );	
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1230, "��ø : ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );								
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1231, "���� : ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );			
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1232, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );				
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1233, "���� ���ʽ� ���� : ��" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "Ÿ���� ������ ��ü���� ���� ������ ��ȥ�� Ÿ��ź �߿����� �������� �����޴� �ڵ��� �ٷ� ���̷��� �Դϴ�." ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "�̵��� ���忡�� �� ������ ���������� ������ �����Ӱ� ��Ⱦ�����ϸ� �Ŵ��� ������ �ڽ��� ��üó�� �����Ӱ� ����մϴ�.\n" ), -1, 0xA3A1A3FF );							
				}
				break;
			case KNIGHT:		//  �ο� ����Ʈ
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_ROYALKNIGHT ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1234, "�⺻������ �ܷõ� �ܴ��� ���°� ������ ���ݷ��� ����� ���� �������� ���� �����ϸ� ���ΰ� �������� �������� ������ �����ִ� Ŭ�����Դϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1235, "��� ���� : �̵���" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 1236, "���� ���� : %dlv�޼�, ���� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1238, "�� : ���ݻ��, ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1239, "��ø : ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1240, "���� : ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1241, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1242, "���� ���ʽ� ���� : ����" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���Ǹ� ��õ�ϴ� ������μ� �����κ��� ������ ���縦 ��ȣ�ϴ� �Ϳ���, ���� ��¡�ϴ� ������ ��ȸ�� �ڵ��� �ٷ� �ο� ����Ʈ�Դϴ�. " ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "�ο� ����Ʈ�� �׵��� �����ִ� ������ ���д� �ڷ� �ϰ� ��� �����ϰ� ���� �� �� �ڷ��� ���� ���Ͽ� �׵��� ���� �ɷ� �̻����� ���ݷ��� ���� �÷Ƚ��ϴ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
			case HEALER:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_ARCHER ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1243, "���̿��� ��ó���� ȭ�� �ѹ߸����ε� �ټ��� ���� �����ϰų�, ���� �̵��ӵ�, Ȱ�� �̿��� ��Ÿ� �������� ��Ʈ �� �� ����� ���ݿ� Ưȭ�� �ɷ��� ������ �ֽ��ϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1244, "��� ���� : Ȱ" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 1245, "���� ���� : %dlv�޼�, ���� ���ü� lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1246, "�� :  ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1247, "��ø : ���� ���, ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1248, "���� : ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1249, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1250, "���� ���ʽ� ���� : ��" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���� ���̿������� �׵��� ��õ������ Ÿ���� ���� ������ �̿��� ������� ������ ���ϸ� ġ���� ����� �� ������ ���� �������� ������, �������� ���� ������ ���� �̿� �����ϴ� �ڵ��� ���̿��� ��ó�Դϴ�.\n" ), -1, 0xA3A1A3FF );							
				}
				break;
			case MAGE:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_WIZARD ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1251, "���� ���ݷ����� �ı����̰� ���� ������ �ϼ����� �ҹٴٷ� ����� ������ ���������� Ưȭ �� �ڵ�� ������ Ȱ�뿡 �־� ������ Ŭ�����Դϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1252, "��� ���� : ������" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 1253, "���� ���� : %dlv�޼�, ��� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1254, "�� :  ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1255, "��ø : ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1256, "���� : ���� ���ݻ��, ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1257, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1258, "���� ���ʽ� ���� : ����" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���ڵ�� ���� �� ��ü�� �������ϰ� �����ϴ� �������� �߿� ������ �������� �������� �̾� �Ŵ��� ���� �����ϴ� �ڵ��Դϴ�." ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���ڵ尡 ����� ���� ��ȣ�� ���� ������ ������ ���� ��ü�� �Ҹ� �� ������ ������ ���ϱ⿡ �� �� �� �� ���� �ϳ��� ���ܱ����� �򰡵ȴ�.\n" ), -1, 0xA3A1A3FF );							
				}
				break;
			case ROGUE:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_ASSASSIN ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1378, "�������� ����, ��� �ɷ°� ���� ��ų �ӵ��� ����� Ŭ�����μ� 1:1�� �������� �� Ȱ���� ��ġ�� ����� Ŭ�����Դϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1379, "��� ���� : �ܰ�" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 1380, "���� ���� : %dlv�޼�, �κ�������Ƽ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1381, "�� :  ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1382, "��ø : ���� ��� ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1383, "���� : ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1384, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1385, "���� ���ʽ� ���� : ��ø" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "����� ª�� �ܰ˰� ������ ����� �̿��� �� �������� ��ġ�� ���� �ֵ� �������̸�, ��밡 ���� �ܷ����� ���� �κ��̳� �������� ������ ���� �̼��� ƴ�� ��� �����ϸ� �����̶� ��ƴ�� ���̸� ���� �޼Ҹ� �����Ͽ� ���İ��� ����� ����� ���� ���� ����� Ư���Դϴ�.\n" ), -1, 0xA3A1A3FF );							
				}
				break;
			case SORCERER:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, 1 ), -1, 0xFFC672FF );									
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 2342,"������Ż ����Ʈ�� ���� ��ȯ�� �������Ͽ� ��, ��, �ٶ�, ������ ���еǴ� 4�� ���ɵ��� ��ȭ ��Ű�� �׵��� ��ȯ�Ͽ� �Բ� ������ ���ϴ� Ŭ�����Դϴ�."  ), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 2343,"��� ���� : ����"  ), -1, 0xA3A1A3FF );

					strMessage.PrintF( _S(2344, "���� ���� : %dlv�޼�, ���̽� ������ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2345, "�� :  ������� ���"  ), -1, 0xA3A1A3FF );	
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2346, "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2347, "���� : ���� ���� ���, ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2348, "ü�� : ����, ���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );			
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2349, "���� ���ʽ� ���� : ����"  ), -1, 0xA3A1A3FF );											
					
				}
				break;
#ifdef CHAR_EX_ROGUE
			case EX_ROGUE:	// [2012/08/27 : Sora] EX�α� �߰�
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_EX_ASSASSIN ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5739, "�������� ����, ��� �ɷ°� ���� ��ų �ӵ��� ����� Ŭ�����μ� 1:1�� �������� �� Ȱ���� ��ġ�� ����� Ŭ�����Դϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5740, "��� ���� : �ܰ�" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 5741, "���� ���� : %dlv�޼�, �κ�������Ƽ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5742, "�� :  ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5743, "��ø : ���� ��� ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5744, "���� : ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5745, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5746, "���� ���ʽ� ���� : ��ø" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "����� ª�� �ܰ˰� ������ ����� �̿��� �� �������� ��ġ�� ���� �ֵ� �������̸�, ��밡 ���� �ܷ����� ���� �κ��̳� �������� ������ ���� �̼��� ƴ�� ��� �����ϸ� �����̶� ��ƴ�� ���̸� ���� �޼Ҹ� �����Ͽ� ���İ��� ����� ����� ���� ���� ����� Ư���Դϴ�.\n" ), -1, 0xA3A1A3FF );							
				}
				break;
#endif
#ifdef CHAR_EX_MAGE
			case EX_MAGE: //2013/01/08 jeil EX������ �߰� ��Ʈ�� ������ �߰� ���� �ʿ� 
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_EX_WIZARD ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5827, "���� ���ݷ����� �ı����̰� ���� ������ �ϼ����� �ҹٴٷ� ����� ������ ���������� Ưȭ �� �ڵ�� ������ Ȱ�뿡 �־� ������ Ŭ�����Դϴ�." ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5828, "��� ���� : ������" ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 5829, "���� ���� : %dlv�޼�, ��� ��� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							
					
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5830, "�� :  ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5831, "��ø : ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5832, "���� : ���� ���ݻ��, ���� ��� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5833, "ü�� : ����,���� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5834, "���� ���ʽ� ���� : ����" ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���ڵ�� ���� �� ��ü�� �������ϰ� �����ϴ� �������� �߿� ������ �������� �������� �̾� �Ŵ��� ���� �����ϴ� �ڵ��Դϴ�." ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���ڵ尡 ����� ���� ��ȣ�� ���� ������ ������ ���� ��ü�� �Ҹ� �� ������ ������ ���ϱ⿡ �� �� �� �� ���� �ϳ��� ���ܱ����� �򰡵ȴ�.\n" ), -1, 0xA3A1A3FF );			
				}
				break;
#endif
			}

			CTString strMessage;
			strMessage.PrintF( _S( 1267, "[%s]�� �����Ѵ�." ), pInfo->GetExtensionName( _pNetwork->MyCharacterInfo.job, 0 ) );		
			pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, FALSE, strMessage, 0 );
			pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, FALSE, _S( 1268, "����ϱ�") );			

			m_iSelChangeJob = 1;
		}
		else if( nResult == SKILL_JOB_2 )				// ���� Ŭ���� 2
		{
			pUIManager->CreateMessageBoxL( _S( 1224, "���� ����" ), UI_SKILLLEARN, MSGLCMD_CHANGEJOB_REQ );		
			const int	iNeedLevel	= EXTENSION_LEVEL;
			const SQUAD	llNeedNas	= 50000;
			const int	iJob		= _pNetwork->MyCharacterInfo.job;

			CTString strNeedNas;
			strNeedNas.PrintF("%I64d", llNeedNas);
			pUIManager->InsertCommaToString(strNeedNas);
			// FiXME : �Ʒ� �κ��� ������ �ʿ��� �κ�.
			switch( iJob )
			{
			case TITAN:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_WARMASTER ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1269,  "��Ը� �������� �ܿ� ���� �ٴ� Ȱ���� �����ָ� ���̷����� ��ȸ�ϴ� ���ݷ°� �� Ŭ������ ��Ʋ�� ���� ���� ü���� ������ �ֽ��ϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1270,  "��� ���� : ���"  ), -1, 0xA3A1A3FF );							
					strMessage.PrintF( _S( 1271, "���� ���� : %dlv�޼�, ���� ũ���� lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1272,  "�� : ���ݻ��, ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1273,  "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1274,  "���� : ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1275,  "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1276,  "���� ���ʽ� ���� : ü��"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "ȣ������ �������� ���� �ð� ������ ���� ���� Ÿ��ź �߿� Ź���� �������� ������ ���� �а� ���߷��ְ� ��ó�ϰų� �Ʊ��� ��⸦ ���� �Լ����� �ѵ��� �ִ� Ŭ������ �̵� �� �������Դϴ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
			case KNIGHT:		// ���� ����Ʈ
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_TEMPLEKNIGHT ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1277,  "��Ƽ���� �����ؼ� ���ϰų�, ���͸� �����Ͽ� �ڽſ��� ������� �ϴ� ���� ��Ƽ���� ����� ���� �Ǿ� �ָ�, ��Ը� ���������� �������� ������ �����ϰ� �˴ϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1278,  "��� ���� : �˰� ����"  ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 1279, "���� ���� : %dlv�޼�, ���� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1280,  "�� : ���ݻ��, ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1281,  "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1282,  "���� : ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1283,  "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1284,  "���� ���ʽ� ���� : ü��"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "����� �ڽŵ��� ���� �ְ��� �̴����� ����� �ִ� ���ó���Ʈ�� ��Ƽ���� ���迡�� ��ȣ�ϸ� �׵��� �����Ͽ�, �� �÷��̸� ��Ȱ�ϰ� �� �ִ� ��Ȱ�� ���� ������ �� �ִ� �����Դϴ�. " ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "������ �̵��� ���ݷ��� �ο� ����Ʈ�� ���� ��� ����������, ���� ���°� ưư�� ü���� �̵��� ���� ū �����Դϴ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
			case HEALER:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_CLERIC ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1285, "���� ȸ�������� ���� ġ���ϸ�, ������ �ɷ��� �ִ�ġ�� ����÷��ִ� �������� ���� ����ϴ� �� ��Ƽ �÷����� ����� ������ ������ �����ϴ� Ŭ���� �Դϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1286, "��� ���� : �ϵ�"  ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 1287, "���� ���� : %dlv�޼�, ���� ���ü� lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1288, "�� :  ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1289, "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1290, "���� : ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1291, "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1292, "���� ���ʽ� ���� : ����"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "���̿����� ��� �ı��� �����ϰ�, â���� ����� ���� �����ϴ� ���̿��� Ŭ������ ���� ���������� ����鿡�� �������� �Ҿ� �־� �ָ�, ��, ���, �����̻��� �������� ��ü�� �����ο� �� �ֵ��� �����ݴϴ�.\n" ), -1, 0xA3A1A3FF );				
					
					
				}
				break;
			case MAGE:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_WITCH ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1293, "�����̻� ���� �� ���� ������ ����ϴ� Ŭ�����μ� ���� ������ ���� ������ �ϴ��� �� ���� ��õ������ �����ϴµ��� �������� ������ �Դϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1294, "��� ���� : �ϵ�"  ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 1295, "���� ���� : %dlv�޼�, ��� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1296,  "�� :  ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1297,  "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1298,  "���� : ���� ���ݻ��, ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1299,  "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1300,  "���� ���ʽ� ���� : ��ø"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "��ġ�� ���轺����, ġ�����̸� ������ ������ �����ϴ� �ڵ��Դϴ�. �̵��� ���ϴ� ������ ��������� �ٸ��ƴ� �ΰ��� ��ü�̸�, ���� ������ �帧���� ���� ȥ���� ���߸��ų�, ������, ��ü������ ���� ��Ű�� ���� ������ ����� ���� ������ϰ� ����ϴ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
			case ROGUE:	
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_RANGER ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1301,  "�������� �ֺ��� �ڿ������� �̿��� ������ ������ �̿��� ��Ÿ� ������ �ϸ�, �ӻ��� �����Դϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1302,  "��� ���� : ����"  ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 1303, "���� ���� : %dlv�޼�, �κ�������Ƽ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1304,  "�� :  ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1305,  "��ø : ���� ��� ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1306,  "���� : ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1307,  "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 1308,  "���� ���ʽ� : ��"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "�������� �η����� �ٰŸ��� �ƴ� ��, ���Ÿ������� ������ �پ��� ������ ������ Ȱ�뿡�� ��Ÿ����." ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "ª�� �ð� ������ �� ���� ȯ���� Ȱ���� �پ��� Ʈ���� ��ġ�ϴ� ���� ���� � ��Ȳ������ ������ �޼Ҹ� ���� ��Ȯ�� ������ ������ �������� �ڽ��� ����� Ȱ���Ͽ� ����ȹ��� ������ Ȱ���Ѵ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
			case SORCERER:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, 2 ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2350,"����ȸ���Ʈ�� ������ ���� ���� ��, �ٶ��� ���� ���Ű� ��, ���� ���� ������ ���� �ڽ��� ��ü�� ��ȭ���� ���� ������ ���ϴ� ���� ��Ÿ���� ���� Ŭ���� �Դϴ�. "), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2351, "��� ���� : ���̵�" ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S(2344, "���� ���� : %dlv�޼�, ���̽� ������ũ lv5 ����" ), iNeedLevel );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2345, "�� : ������� ���" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2346, "��ø : ����, ȸ�ǻ��" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2347, "���� : ���� ���ݻ��, ���� ��� ���, ���� ������ ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2348, "ü�� : ����,���� ���, ���� ȿ�� ����" ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S(2349, "���� ���ʽ� ���� : ����" ), -1, 0xA3A1A3FF );												
				}
				break;
#ifdef CHAR_EX_ROGUE
			case EX_ROGUE:	// [2012/08/27 : Sora] EX�α� �߰�
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_EX_RANGER ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5747,  "�������� �ֺ��� �ڿ������� �̿��� ������ ������ �̿��� ��Ÿ� ������ �ϸ�, �ӻ��� �����Դϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5748,  "��� ���� : ����"  ), -1, 0xA3A1A3FF );							

					strMessage.PrintF( _S( 5749, "���� ���� : %dlv�޼�, �κ�������Ƽ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							

					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5750,  "�� :  ������� ���"  ), -1, 0xA3A1A3FF );	
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5751,  "��ø : ���� ��� ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5752,  "���� : ���� ��� ���, ���� ������ ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5753,  "ü�� : ����,���� ���, ���� ȿ�� ����"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5754,  "���� ���ʽ� : ��"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "�������� �η����� �ٰŸ��� �ƴ� ��, ���Ÿ������� ������ �پ��� ������ ������ Ȱ�뿡�� ��Ÿ����." ), -1, 0xA3A1A3FF );							
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "ª�� �ð� ������ �� ���� ȯ���� Ȱ���� �پ��� Ʈ���� ��ġ�ϴ� ���� ���� � ��Ȳ������ ������ �޼Ҹ� ���� ��Ȯ�� ������ ������ �������� �ڽ��� ����� Ȱ���Ͽ� ����ȹ��� ������ Ȱ���Ѵ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
#endif
#ifdef CHAR_EX_MAGE		//2013/01/08 jeil EX������ �߰� ��Ʈ�� ������ �߰� ���� �ʿ� 
			case EX_MAGE:
				{
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, pInfo->GetName( iJob, JOB_2ND_EX_WITCH ), -1, 0xFFC672FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5835, "�����̻� ���� �� ���� ������ ����ϴ� Ŭ�����μ� ���� ������ ���� ������ �ϴ��� �� ���� ��õ������ �����ϴµ��� �������� ������ �Դϴ�."  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "  " ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5836, "��� ���� : �ϵ�"  ), -1, 0xA3A1A3FF );							
					
					strMessage.PrintF( _S( 5837, "���� ���� : %dlv�޼�, ��� ��� �극��ũ lv5 ����" ), iNeedLevel );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );							
					
					strMessage.PrintF( _S( 1228, "�ʿ� ���� : %s ����" ), strNeedNas );		
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, strMessage, -1, 0xE18600FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5838,  "�� :  ������� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5839,  "��ø : ����, ȸ�ǻ��"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5840,  "���� : ���� ���ݻ��, ���� ��� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5841,  "ü�� : ����,���� ���"  ), -1, 0xA3A1A3FF );							
					pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, _S( 5842,  "���� ���ʽ� ���� : ��ø"  ), -1, 0xA3A1A3FF );							
					
					//pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, TRUE, CTString( "��ġ�� ���轺����, ġ�����̸� ������ ������ �����ϴ� �ڵ��Դϴ�. �̵��� ���ϴ� ������ ��������� �ٸ��ƴ� �ΰ��� ��ü�̸�, ���� ������ �帧���� ���� ȥ���� ���߸��ų�, ������, ��ü������ ���� ��Ű�� ���� ������ ����� ���� ������ϰ� ����ϴ�.\n" ), -1, 0xA3A1A3FF );							
					
					
				}
				break;
#endif
			}
			
			
			CTString strMessage;
			strMessage.PrintF( _S( 1267, "[%s]�� �����Ѵ�." ), pInfo->GetExtensionName( _pNetwork->MyCharacterInfo.job, 1 ) );		
			pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, FALSE, strMessage, 0 );
			pUIManager->AddMessageBoxLString( MSGLCMD_CHANGEJOB_REQ, FALSE, _S( 1268, "����ϱ�" ) );			

			m_iSelChangeJob = 2;
		}
		else if(nResult == SKILL_NPC_HELP)											// ����Ѵ�.
		{
			pUIManager->RearrangeOrder( UI_NPCHELP, TRUE );
		}
		// [090527: selo] Ȯ���� ����Ʈ ����
		else if( ciQuestClassifier < nResult )	
		{
			// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
			CUIQuestBook::SelectQuestFromMessageBox( nResult );
		}
		else
		{
			pUIManager->GetSSkillLearn()->closeUI();
		}
		break;

	case MSGLCMD_CHANGEJOB_REQ:							// ���� ����â.
		{
			if( nResult == 0 )
			{				
				pUIManager->CloseMessageBox( MSGCMD_CHANGEJOB );				
				
				CTString	strMessage;
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S( 1317, "����" ), UMBS_OKCANCEL, UI_SKILLLEARN, MSGCMD_CHANGEJOB );		
				strMessage.PrintF( _S( 1318, "%s�� ���� �Ͻðڽ��ϱ�?" ), pInfo->GetExtensionName( _pNetwork->MyCharacterInfo.job, m_iSelChangeJob - 1 ) );	
				MsgBoxInfo.AddString( strMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
			else
			{
			}
		}
		break;

		// Special Skill
	case MSGLCMD_SSKILLLEARN_REQ:
		if( nResult == SKILL_LEARN )					// ��ų�� �����Ѵ�.
		{
			pUIManager->GetSSkillLearn()->openUI(m_iMobIdx, m_iMobVirIdx, m_fNpcX, m_fNpcZ);
		}
		else if( nResult == SKILL_TALK )				// �̾߱� �Ѵ�.
		{
			//TODO : NewQuestSystem
			// ����Ʈ â ����
			CUIQuestBook::TalkWithNPC();
		}
		else if( nResult == SKILL_NPC_HELP)								
		{
			pUIManager->RearrangeOrder( UI_NPCHELP, TRUE );
		}
#ifdef DURABILITY
		else if (nResult == ITEM_DURABILITY)
		{
			pUIManager->GetDurability()->Open(CUIDurability::eDURABILITY, m_iMobIdx, m_fNpcX, m_fNpcZ);
		}
		else if (nResult == ITEM_RECOVERY)
		{
			pUIManager->GetDurability()->Open(CUIDurability::eRECOVERY, m_iMobIdx, m_fNpcX, m_fNpcZ);
		}
#endif	//	DURABILITY
		else if (nResult == ITEM_COMPOSE)
		{
			pUIManager->GetItemCompose()->openUI();
		}
		else if (nResult == ITEM_SEAL_COMPOSE)
		{
			pUIManager->GetSealComposeUI()->openUI();
		}
		// [090527: selo] Ȯ���� ����Ʈ ����
		else if( ciQuestClassifier < nResult )	
		{
			// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
			CUIQuestBook::SelectQuestFromMessageBox( nResult );
		}

		else// ����Ѵ�.
		{
			pUIManager->GetSSkillLearn()->closeUI();
		}
		break;
	case MSGLCMD_RESERVE_REQ:
		{
			// [090527: selo] Ȯ���� ����Ʈ �̾߱� �Ѵ� ó�� ������ ���� ��ƾ
			int iQuestIndex = -1;
			if( ciQuestClassifier < nResult )	
			{
				iQuestIndex = nResult;
				nResult = ciQuestClassifier;
			}
			
			switch(nResult)
			{
			pUIManager->SetCSFlagOff( CSF_SHOP );

			case SKILL_TITAN:
				{
					OpenSkillLearn(75, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_KNIGHT:
				{
					OpenSkillLearn(76, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_HEALER:
				{
					OpenSkillLearn(77, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_MAGE:
				{
					OpenSkillLearn(123, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_ROGUE:
				{
					OpenSkillLearn(176, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_SORCERER:
				{
					OpenSkillLearn(255, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
			case SKILL_NIGHTSHADOW:
				{
					OpenSkillLearn(894, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
#ifdef CHAR_EX_ROGUE
			case SKILL_EX_ROGUE:	// [2012/08/27 : Sora] EX�α� �߰�
				{
					OpenSkillLearn(1504, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
#endif
#ifdef CHAR_EX_MAGE
			case SKILL_EX_MAGE:		//2013/01/08 jeil EX������ �߰� �ǹ̸� ���� ���߿� ����� �߰� ���� �ʿ� NPC ���ؽ��� ���� 
				{
					OpenSkillLearn(1521, m_iMobVirIdx, FALSE, m_fNpcX, m_fNpcZ);
				}
				break;
#endif
			case SKILL_QUEST:
				{
					CUIQuestBook::TalkWithNPC();
				}
				
				// [090527: selo] Ȯ���� ����Ʈ ����
			case ciQuestClassifier:
				{
					// ������ ����Ʈ�� ���� ���� �Ǵ� ���� â�� ����.
					CUIQuestBook::SelectQuestFromMessageBox( iQuestIndex );					
				}
				break;
			}
		}break;
	}
}

// ========================================================================= //
//                         Receive message functions                         //
// ========================================================================= //

// ----------------------------------------------------------------------------
// Name : LearnSkill()
// Desc :
// ----------------------------------------------------------------------------
void CUISkillLearn::LearnSkill( SLONG slIndex, SBYTE sbIsNew, SBYTE sbLevel, BOOL bSpecial )
{
 	CUIManager* pUIManager = CUIManager::getSingleton();
 
 	if( !bSpecial )
		return;

	CSpecialSkill* pSSkill = CSpecialSkill::getData( slIndex );

	if (pSSkill == NULL)
		return;
	
	// Close message box of skill learn
	pUIManager->CloseMessageBox( MSGCMD_SKILLLEARN_NOTIFY );
	
	// Create message box of skill learn
	CTString	strMessage;
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 270, "��ų" ), UMBS_OK, UI_SKILLLEARN, MSGCMD_SKILLLEARN_NOTIFY );
	strMessage.PrintF( _S( 277, "%s ��ų�� �����Ͽ����ϴ�" ), pSSkill->GetName() );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );

	MY_INFO()->SetSkill(slIndex, (int)sbLevel, bSpecial > 0);
	
	if( sbIsNew != 0 )
		pUIManager->GetCharacterInfo()->AddSkill( slIndex, sbLevel, bSpecial );

	pUIManager->GetSSkillLearn()->updateList();
}

// ----------------------------------------------------------------------------
// Name : LearnSkillError()
// Desc :
// ----------------------------------------------------------------------------
void CUISkillLearn::LearnSkillError( UBYTE ubError )
{
	CTString	strMessage;

	switch( ubError )
	{
	case MSG_SKILL_LEARN_ERROR_LEVEL:
		strMessage = _S( 278, "������ �����Ͽ� ��ų�� ������ �� �����ϴ�." );
		break;

	case MSG_SKILL_LEARN_ERROR_SP:
		strMessage = _S( 279, "���õ��� �����Ͽ� ��ų�� ������ �� �����ϴ�." );
		break;

	case MSG_SKILL_LEARN_ERROR_ITEM:
		strMessage = _S( 280, "�������� �������� �ʾ� ��ų�� ������ �� �����ϴ�." );
		break;

	case MSG_SKILL_LEARN_ERROR_SKILL:
		strMessage = _S( 281, "��ų ������ ���� �ʾ� ��ų�� ������ �� �����ϴ�." );
		break;

	case MSG_SKILL_LEARN_ERROR_SYSTEM:
		strMessage = _S( 282, "��ų�� ������ �� �����ϴ�." );
		break;

	case MSG_SKILL_LEARN_ERROR_STR:			// �� ����
		strMessage = _S( 1319, "���� �����Ͽ� ��ų�� ������ �� �����ϴ�." );		
		break;

	case MSG_SKILL_LEARN_ERROR_DEX:			// ���� ����
		strMessage = _S( 1320, "��ø�� �����Ͽ� ��ų�� ������ �� �����ϴ�." );		
		break;

	case MSG_SKILL_LEARN_ERROR_INT:			// ���� ����
		strMessage = _S( 1321, "������ �����Ͽ� ��ų�� ������ �� �����ϴ�." );		
		break;

	case MSG_SKILL_LEARN_ERROR_CON:			// ü�� ����
		strMessage = _S( 1322, "ü���� �����Ͽ� ��ų�� ������ �� �����ϴ�." );		
		break;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box of skill learn
	pUIManager->CloseMessageBox( MSGCMD_SKILLLEARN_NOTIFY );

	// Create message box of skill learn
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 270, "��ų" ), UMBS_OK,
								UI_SKILLLEARN, MSGCMD_SKILLLEARN_NOTIFY );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

// ----------------------------------------------------------------------------
// Name : LearnSSkillError()
// Desc :
// ----------------------------------------------------------------------------
void CUISkillLearn::LearnSSkillError( UBYTE ubError )
{
	CTString	strMessage;

	switch(ubError)
	{
	case MSG_SSKILL_LEARN_ERROR_LEVEL:
		strMessage = _S( 278, "������ �����Ͽ� ��ų�� ������ �� �����ϴ�." );
		break;
	case MSG_SSKILL_LEARN_ERROR_SP:
		strMessage = _S( 279, "���õ��� �����Ͽ� ��ų�� ������ �� �����ϴ�." );
		break;
	case MSG_SSKILL_LEARN_ERROR_SSKILL:
		strMessage = _S( 654, "�ش� ����� ���µ� �ʿ��� ����� ����� �ʾҽ��ϴ�." );			
		break;
	case MSG_SSKILL_LEARN_ERROR_SSKILL_LEVEL:
		strMessage = _S( 655, "��ų ������ �����մϴ�." );	
		break;
	case MSG_SSKILL_LEARN_ERROR_SYSTEM:
		strMessage = _S( 282, "��ų�� ������ �� �����ϴ�." );
		break;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	// Close message box of skill learn
	pUIManager->CloseMessageBox( MSGCMD_SKILLLEARN_NOTIFY );

	// Create message box of skill learn
	CUIMsgBox_Info	MsgBoxInfo;
	MsgBoxInfo.SetMsgBoxInfo( _S( 656, "���꽺ų" ), UMBS_OK,			
								UI_SKILLLEARN, MSGCMD_SKILLLEARN_NOTIFY );
	MsgBoxInfo.AddString( strMessage );
	pUIManager->CreateMessageBox( MsgBoxInfo );
}

