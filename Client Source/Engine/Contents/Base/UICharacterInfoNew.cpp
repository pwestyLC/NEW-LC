#include "stdh.h"

// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½. [12/1/2009 rumist]
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Contents/Base/UICalendar.h>
#include <Engine/Contents/function/SSkillLearnUI.h>
#include <Engine/Interface/UIPlayerInfo.h>
#include <Engine/Interface/UIMap.h>
#include <Engine/Contents/function/ExChangeUI.h>
#include <Engine/Contents/function/HelperManager.h>
#include <Engine/Interface/UIMonsterCombo.h>
#include <Engine/Contents/function/ItemProductUI.h>
#include <Engine/Contents/function/AffinityInfoUI.h>
#include <Engine/Interface/UINickName.h>
#include <Engine/Contents/Base/UIRankingSystem.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Interface/UIPartyAuto.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/Interface/UIGuildBattle.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Contents/Login/ServerSelect.h>
#include <Engine/Contents/Base/UIMySyndicateInfo.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Syndicate.h>
#include "CharacterInfoCmd.h"
#include <Engine/Object/ActorMgr.h>
#include <Engine/TransformInfo.h>
#include <Engine/Info/MyInfo.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Contents/function/TitleData.h>
#include <Engine/Contents/Base/PersonalshopUI.h>
#include <Engine/Contents/function/GuildBattleMatchUI.h>
#include <Engine/Interface/UIManager.h>

#ifdef QUICK_PANEL
#include <Engine/Contents/function/UIQuickPanel.h>
#endif
#ifdef REZABOT
#include <Engine/ReZaBot.h>
#endif
#ifdef DAILY_LOGIN
#include <Engine/DailyLogin.h>
#endif
#include <Engine/Contents/function/UICraft.h> //Craft system
#include "Contents/function/UIPassiveSystemRST.h"
#define PARTY_AUTO_ENABLE	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½Ã½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½

#define ACTION_NUM_SELL		(28)
#define DEF_MAX_SHOW_ROW	(6)

// ï¿½ï¿½ï¿½ï¿½ È°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define DEF_MAX_LIST (30)
#define DEF_SHOW_LSIT (4)
#define DEF_SHOW_MAX  (8)

// Date : 2005-03-07,   By Lee Ki-hwan
static int	_iMaxActionStringChar = 0;
static int	_iMaxSkillStringChar = 0;

extern INDEX g_iCountry;
extern UINT	g_uiEngineVersion;

extern INDEX g_iXPosInCharInfo;
extern INDEX g_iYPosInCharInfo;

CTString _ClassName[11];

extern int _aSummonSkill[5] = { 293, 294, 300, 301, 307 };
//////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// Name : CUICharacterInfo()
// Desc : Constructor
// ----------------------------------------------------------------------------
CUICharacterInfo::CUICharacterInfo()
	:	m_pstrTitle(NULL)
	,	m_pMoveTitle(NULL)
	,	m_pBtnClose(NULL)
	,	m_pMainTab(NULL)
	,	m_bDrag(false)
	,	m_nOriX(0), m_nOriY(0)
	,	m_nMouseX(0)
	,	m_nMouseY(0)
	// PKï¿½ï¿½ï¿½ï¿½, ï¿½Ó¼ï¿½ï¿½ï¿½ï¿½ï¿½
	,	m_pstrPk(NULL)
	,	m_pstrPkPoint(NULL)
	,	m_pstrPkPointAcc(NULL)
	//,	m_pImgArrAtt(NULL)
	//,	m_pImgArrDef(NULL)
	//,	m_pstrAttlv(NULL)
	//,	m_pstrDeflv(NULL)

	,	m_opResistStone(NULL)
	,	m_opResistSturn(NULL)
	,	m_opResistSilent(NULL)
	,	m_absorbPVPDamageRate(NULL)
	,	m_opDecreaseSkillMP(NULL)
	,	m_skillSpeed(NULL)

	,	m_PVP_Winer(NULL)
	,	m_PVP_Lose(NULL)
	,	m_pImgArrWiner(NULL)
	,	m_pImgArrLose(NULL)

	,	m_honor(NULL)

	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½, Æ¯ï¿½ï¿½, ï¿½ï¿½Ç¥, ï¿½ï¿½Æ¼, ï¿½ï¿½ï¿½, ï¿½×¼ï¿½, ï¿½Ò¼ï¿½
	,	m_pTabAction(NULL)
	,	m_pTabCommunity(NULL)
	,	m_pTabSkill(NULL)
	// ï¿½ï¿½ï¿½ï¿½
	,	m_pBtnSyndicateInfo(NULL)
	,	m_pImgNoJoin(NULL)
	,	m_pTextMyPos(NULL)
	,	m_pPbSyndicateExp(NULL)
	,	m_pPbHonorPoints(NULL)
	,	m_pTbHistory(NULL)
	,	m_pScrollSyndiHistory(NULL)
	,   m_pstrTooltip(NULL)
	,   m_nTooltipMax(0)
	,	m_pImgSelect(NULL)
{
	m_ucipCurrentPage	= PAGE_CHARINFO_NEW_STATUS;
	m_bLockStatPoint	= FALSE;
	
	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½Ì¸ï¿½
	_ClassName[0] = _S(4050, "Ä«ï¿½ï¿½ï¿½ï¿½ Å·"); _ClassName[1] = _S(4051, "ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½Æ®"); _ClassName[2] = _S(1196, "ï¿½ï¿½Ø½ï¿½");
	_ClassName[3] = _S(4052, "ï¿½Ó´ï¿½"); _ClassName[4] = _S(4053, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½"); _ClassName[5] = _S(92, "ï¿½Ï¹ï¿½");
	_ClassName[6] = _S(4054, "ï¿½ï¿½ï¿½ï¿½"); _ClassName[7] = _S(4055, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½"); _ClassName[8] = _S(4056, "ï¿½ï¿½ï¿½ï¿½Æ®");
	_ClassName[9] = _S(4057, "ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½Æ®"); _ClassName[10] =_S(4058, "ï¿½ï¿½ï¿½ï¿½ï¿½");

	m_strTitleName = _S(69, "Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
	
	int i = 0;
	for (i = 0; i < PAGE_CHARINFO_NEW_MAX; i++)
	{
		m_pBtnMainCheckBtn[i] = NULL;
		m_pImgCheck[i] = NULL;
		m_pImgUnCheck[i] = NULL;
	}

	for (i = 0; i < eCHARINFO_BASE_MAX; i++) {
		m_ptxtBase[i] = NULL;
	}

	for (i = 0; i < eCHARINFO_STAT_MAX; i++) {
		m_ptxtStat[i] = NULL;
	}

	for (i = 0; i < eTAB_SKILL_MAX; i++) 
	{
		m_pArrSkill[i] = NULL;
		m_pScrollSkill[i] = NULL;
	}

	for (i = 0; i < eTAB_ACTION_MAX; i++) 
	{
		m_pArrAction[i] = NULL;
		m_pScrollAction[i] = NULL;
	}

	for (i = 0; i < eTAB_COMMUNITY_MAX; i++) 
	{
		m_pArrCommunity[i] = NULL;
		m_pScrollCommunity[i] = NULL;
	}

	for( i = 0; i < 3; i++)	{
		m_nSkillActionUpperTab[i] = 0;
	}

	for ( i = 0; i < eTAB_SYNDICATE_MAX; i++)
	{
		m_pProgressBar[i] = NULL;
		m_pImgMark[i] = NULL;
	}

	for ( i = 0; i < eBTN_MAX; i++)
	{
		m_pBtnStatus[i] = NULL;
	}

	m_pBtnResetStats = NULL;
	
	setInherit(false);
	LoadTooltipString();
}

CUICharacterInfo::~CUICharacterInfo()
{
	Destroy();

	SAFE_ARRAY_DELETE(m_pstrTooltip);
}
// ----------------------------------------------------------------------------
// Name : ResetPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
}

void CUICharacterInfo::ResetSavePosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
	g_iXPosInCharInfo = GetPosX();
	g_iYPosInCharInfo = GetPosY();
}

// ----------------------------------------------------------------------------
// Name : AdjustPosition()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

////////////////////////////////////  MSG  /////////////////////////////////////////////////
void CUICharacterInfo::MsgBoxCommand( int nCommandCode, BOOL bOK, CTString &strInput )
{
	switch( nCommandCode )
	{
	case MSGCMD_EVENT_PRIZE:
		if( bOK )
		{
			_pNetwork->SendEventPrize();
		}
		break;
	case MSGCMD_QUEST_COMPLETE:
		if( bOK )
		{			
			_pNetwork->GoZone(0, 0);
		}
		break;
	}
}

void CUICharacterInfo::MsgBoxLCommand( int nCommandCode, int nResult )
{
	switch( nCommandCode )
	{	
	case MSGLCMD_QUEST_TUTORIAL: // MSG_QUEST_PRIZE ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½
		{
			_pNetwork->GoZone(0, 0); // ï¿½ï¿½ï¿½Î¿ï¿½ Æ©ï¿½ä¸®ï¿½ï¿½ ï¿½ï¿½å¿¡ï¿½ï¿½ ï¿½Å±ï¿½ Ä³ï¿½ï¿½ï¿½Í´ï¿½ ï¿½Ìµï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½Î¿ï¿½ ï¿½ï¿½Ä¡ï¿½Ì´ï¿½.(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ø´ï¿½.)
		}
		break;
	}
}

// ï¿½Ã½ï¿½ï¿½ï¿½ ï¿½Þ½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½)
void CUICharacterInfo::UseStatPoint( UBYTE ubStatType, SLONG slStatChange )
{
	// Update states of buttons & strings of stats
	NotifyStatPoint();

	// System message
	CTString	strMessage;
	switch( ubStatType )
	{
	case MSG_STATPOINT_USE_STR:
	case MSG_STATPOINT_USE_STR_10:
		{
			strMessage.PrintF( _S( 438, "ï¿½ï¿½ï¿½ï¿½ %d ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½." ), slStatChange );
			updateStatusPt(MSG_STATPOINT_USE_STR, slStatChange);
		}
		break;
	case MSG_STATPOINT_USE_DEX:
	case MSG_STATPOINT_USE_DEX_10:
		{
			strMessage.PrintF( _S( 439, "ï¿½ï¿½Ã¸ï¿½ï¿½ %d ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½." ), slStatChange );
			updateStatusPt(MSG_STATPOINT_USE_DEX, slStatChange);
		}
		break;
	case MSG_STATPOINT_USE_INT:
	case MSG_STATPOINT_USE_INT_10:
		{
			strMessage.PrintF( _S( 440, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ %d ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½." ), slStatChange );
			updateStatusPt(MSG_STATPOINT_USE_INT, slStatChange);
		}
		break;
	case MSG_STATPOINT_USE_CON:
	case MSG_STATPOINT_USE_CON_10:
		{
			strMessage.PrintF( _S( 441, "Ã¼ï¿½ï¿½ï¿½ï¿½ %d ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½." ), slStatChange );
			updateStatusPt(MSG_STATPOINT_USE_CON, slStatChange);
		}
		break;
	}

	CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( strMessage );

	UnlockStatPoint();
}

// ï¿½Ã½ï¿½ï¿½ï¿½ ï¿½Þ½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½)
void CUICharacterInfo::StatPointError( SBYTE sbError )
{
	// System message
	CTString	strMessage;	

	switch( sbError )
	{
	case MSG_STATPOINT_ERROR_NOTENOUGH:
		strMessage = _S( 1092, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Õ´Ï´ï¿½." );		
		break;
	case MSG_STATPOINT_ERROR_CANTUSE:
		strMessage = _S( 1093, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½." );		
		break;
	case MSG_STATPOINT_ERROR_WRONGPACKET:
		strMessage = _S( 5608, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½." );		
		break;
	case MSG_STATPOINT_ERROR_NOMONEY:
		strMessage = _S( 1095, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Õ´Ï´ï¿½." );		
		break;
	default:
		ASSERTALWAYS("Invalid Stat Point Message!!!");
		break;
	}

	CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_ERROR );

	UnlockStatPoint();
}

////////////////////////////////////  NETWORK  /////////////////////////////////////////////////

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½
void CUICharacterInfo::SendUseStatPoint( UBYTE ubStatType )
{
	if( m_bLockStatPoint == TRUE )
		return;

	_pNetwork->SendUseStatPoint( ubStatType );
	m_bLockStatPoint = TRUE;
}

////////////////////////////////////  Data  /////////////////////////////////////////////////

// ï¿½ï¿½Å³ ï¿½ß°ï¿½
void CUICharacterInfo::AddSkill( int nSkillIndex, SBYTE sbSkillLevel, BOOL bSpecial )
{
	if(!bSpecial)
	{
		const int iSummonSkillCount = sizeof( _aSummonSkill ) / sizeof(int);
		CSkill	&rSelSkill = _pNetwork->GetSkillData( nSkillIndex );

		const int iJob = _pNetwork->MyCharacterInfo.job;
		const int iJob2 = _pNetwork->MyCharacterInfo.job2;

		// ï¿½ï¿½È¯ï¿½ï¿½Å³ ï¿½Îµï¿½ï¿½ï¿½ Ã£ï¿½ï¿½,
		// ï¿½ï¿½È¯ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½Å³.
		if( iJob == SORCERER && 
			iJob2 == 2 && rSelSkill.GetType() != CSkill::ST_PASSIVE )
		{
			if( ( rSelSkill.GetSorcererFlag() & ( SSF_USE_FIRE | SSF_USE_WIND | SSF_USE_EARTH | SSF_USE_WATER ) ) )		
				return;		
			else
			{
				for( int i = 0; i < iSummonSkillCount; ++i )
				{
					if( _aSummonSkill[i] == nSkillIndex )
					{					
						return;
					}
				}
			}
		}

		switch( rSelSkill.GetType() )
		{
		case CSkill::ST_MELEE:			// Active skill
		case CSkill::ST_RANGE:			// Active skill
		case CSkill::ST_MAGIC:			// Active skill
		case CSkill::ST_SUMMON_TOTEM_SKILL:
			{
				int	iRow;
				for( iRow = 0; iRow < SKILL_ACTIVE_SLOT_ROW_TOTAL; iRow++ )
				{
					if (rSelSkill.GetFlag() & SF_ITEM_SPECIAL_SKILL)
					{
						if (iRow >= SKILL_SPECIAL_SLOT_ROW_TOTAL)
							continue;

						if (m_nIdxItemSpecialSkill[iRow] < 0)
						{
							m_nIdxItemSpecialSkill[iRow] = nSkillIndex;
							SetItemSkill();
							break;
						}
					}
				}
			}
			break;
		case CSkill::ST_PASSIVE:		// Passive skill
			{
				int	iRow;
				for( iRow = 0; iRow < SKILL_PASSIVE_SLOT_ROW_TOTAL; iRow++ )
				{
					if (rSelSkill.GetFlag() & SF_ITEM_SPECIAL_SKILL)
					{
						if (iRow >= SKILL_SPECIAL_SLOT_ROW_TOTAL)
							continue;

						if (m_nIdxItemSpecialSkill[iRow] < 0)
						{
							m_nIdxItemSpecialSkill[iRow] = nSkillIndex;
							SetItemSkill();
							break;
						}
					}
				}
			}
			break;
		case CSkill::ST_SEAL:
			{
				int	iRow;
				for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
				{
					if (m_nIdxVoucherSkill[iRow] < 0)
					{
						m_nIdxVoucherSkill[iRow] = nSkillIndex;
						SetSeal();
						break;
					}
				}

			}break;
		}
	}	
	else
	{
		int	iRow;
		for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
		{
			if (m_nIdxSpecialSkill[iRow] < 0)
			{
				m_nIdxSpecialSkill[iRow] = nSkillIndex;
				SetSSkill();
				break;
			}
		}
	}
}

// ï¿½ï¿½Ç¥ ï¿½ß°ï¿½
void CUICharacterInfo::AddSeal( int nSkillIndex, SQUAD nSealExp )
{
	int	iRow;
	for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
	{
		if (m_nIdxVoucherSkill[iRow] < 0)
		{
			m_nIdxVoucherSkill[iRow] = nSkillIndex;
			MY_INFO()->SetSkillExp(nSkillIndex, nSealExp);
			SetSeal();
			break;
		}
	}
}

// Desc : Æ¯ï¿½ï¿½ ï¿½ï¿½Å³ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ï¿½ï¿½ È®ï¿½ï¿½ï¿½Õ´Ï´ï¿½.
int CUICharacterInfo::CheckSSkill( int nSSkillType )
{
	int	iRow;
	for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
	{
		if (m_nIdxSpecialSkill[iRow] > 0)
		{
			const int iSSkillIndex		= m_nIdxSpecialSkill[iRow];
			CSpecialSkill* pSSkillData	= CSpecialSkill::getData(iSSkillIndex);

			if (pSSkillData == NULL)
				return -1;

			if(pSSkillData->GetType() == nSSkillType)
				return iSSkillIndex;
		}
	}
	return -1;
}

// Desc : Æ¯ï¿½ï¿½ ï¿½ï¿½Å³ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ï¿½ï¿½ ï¿½Îµï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ È®ï¿½ï¿½ï¿½Õ´Ï´ï¿½.
BOOL CUICharacterInfo::CheckSSkillByIndex( int iIndex, int nNeedLevel, BOOL* bNeedLevel )
{
	int	iRow;
	CSpecialSkill*  NeedSSkill = CSpecialSkill::getData( iIndex );

	if (NeedSSkill == NULL)
		return FALSE;

	*bNeedLevel = FALSE;

	for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
	{
		if (m_nIdxSpecialSkill[iRow] > 0)
		{
			CSpecialSkill*  CharSSkill = CSpecialSkill::getData(m_nIdxSpecialSkill[iRow]);

			if (CharSSkill == NULL)
				continue;

			// Å¸ï¿½ï¿½ Ã¼Å© 
			if ( NeedSSkill->GetType() == CharSSkill->GetType() )
			{
				// Preference Ã¼Å© 
				if ( NeedSSkill->GetPreference() != -1 ) 
				{
					if ( NeedSSkill->GetPreference() < CharSSkill->GetPreference() ) 
					{
						*bNeedLevel = TRUE;
						return TRUE;
					}
					else if ( NeedSSkill->GetPreference() == CharSSkill->GetPreference() )
					{
						// ï¿½ï¿½ï¿½ï¿½ Ã¼Å© 
						if (MY_INFO()->GetSkillLevel(CharSSkill->GetIndex(), true) >= nNeedLevel)
						{
							*bNeedLevel = TRUE;
							return TRUE;
						}
					}
				}
				else // ï¿½Æ´Ï¸ï¿½ ï¿½Îµï¿½ï¿½ï¿½ Ã¼Å© 
				{
					if (CharSSkill->GetIndex() == iIndex)
					{
						// ï¿½ï¿½ï¿½ï¿½ Ã¼Å© 
						if (MY_INFO()->GetSkillLevel(CharSSkill->GetIndex(), true) >= nNeedLevel)
						{
							*bNeedLevel = TRUE;
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

// ï¿½×¼ï¿½ ï¿½ï¿½ï¿½
void CUICharacterInfo::UseAction( int nIndex )
{
	if( _pNetwork->MyCharacterInfo.sbShopType != PST_NOSHOP && nIndex != ACTION_NUM_SELL)
	{
		return;
	}

	if( CUIManager::getSingleton()->IsCSFlagOn( CSF_WAREHOUSE ) )
	{
		return;
	}
	
	if (_pNetwork->MyCharacterInfo.ulPlayerState & PLAYER_STATE_FLYING)
	{ // ï¿½ï¿½ï¿½ï¿½ï¿½å¿¡ï¿½ï¿½ï¿½ï¿½ ï¿½×¼ï¿½ ï¿½Èµï¿½
		return;
	}

	if ( CUIManager::getSingleton()->IsCSFlagOn( CSF_ITEMWEARING ) )
	{
		return; // ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ß¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½Ò°ï¿½
	}
	
	// [100311: selo] OX ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ ï¿½Þºï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½É±ï¿½ ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½
	// [100510: selo] Å¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½Ìµï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	if( nIndex == 3 )
	{
		ULONG zoneNo = _pNetwork->MyCharacterInfo.zoneNo;
		if( zoneNo == 14 || zoneNo == 22 || zoneNo == 25 || zoneNo == 33 || zoneNo == 35 || zoneNo == 36)
			return;
	}

	CAction* pActionData = CAction::getData(nIndex);
	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (pActionData == NULL)
		return;
	
	switch( pActionData->GetType() )
	{
	case ACTION_NORMAL:
		{
			CEntity			*penPlEntity;
			CPlayerEntity	*penPlayerEntity;
			penPlEntity = CEntity::GetPlayerEntity( 0 );
			penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);

			switch (nIndex)
			{
			case 2:		// ï¿½È±ï¿½, ï¿½Ù±ï¿½
			case 3:		// ï¿½É±ï¿½, ï¿½ï¿½ï¿½ï¿½
			case 23:	// ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			{
				penPlayerEntity->UseAction(nIndex);
			}
			break;

			case 1:		// ï¿½ï¿½ï¿½ï¿½
			{
				if (IsBila(g_iCountry) == FALSE)
					penPlayerEntity->CommandAttack();
			}
			break;

			case 4:		// ï¿½Ý±ï¿½	//0826
			{
				penPlayerEntity->SearchNearItem();
			}
			break;

			case 5:		// ï¿½ï¿½È¯
			{
				if (pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER)
				{
					CTString	strTarget = pInfo->GetTargetName(eTARGET);
					CUIManager::getSingleton()->GetExchange()->SendExchangeReq_Req(strTarget);
				}
			}
			break;

			case 27:	// ï¿½ï¿½ï¿½ï¿½
			{
				CUIManager::getSingleton()->GetMap()->ToggleVisible();
			}
			break;

			case 28:	// ï¿½Ç¸ï¿½ï¿½Ï±ï¿½
			{
				// ï¿½Îºï¿½ï¿½ä¸® ï¿½ï¿½ï¿½ï¿½ ï¿½É¾ï¿½ï¿½Ù°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ß´Ù°ï¿½ ï¿½Ø¾ï¿½ï¿½Ï±ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½,
				// ToggleVisible()ï¿½ï¿½ ï¿½Ï¸ï¿½ ï¿½ÈµÉ°ï¿½ ï¿½ï¿½ï¿½ï¿½...
				if (_pNetwork->MyCharacterInfo.bWildPetRide)
				{
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(757, "ï¿½ï¿½ï¿½Î»ï¿½ï¿½ï¿½"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(_S(5314, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½."));
					CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);
					break;
				}

				if (_pNetwork->MyCharacterInfo.sbAttributePos & MATT_FREEPKZONE)
				{
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(757, "ï¿½ï¿½ï¿½Î»ï¿½ï¿½ï¿½"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(_S(785, "ï¿½ï¿½ï¿½Î»ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½."));
					CUIManager::getSingleton()->CreateMessageBox(MsgBoxInfo);
					break;
				}

				CUIManager::getSingleton()->GetPersonalShop()->OpenPersonalShop(TRUE);
			}
			break;
#ifdef ENABLE_GUARDIAN	
			case 30:	// ï¿½Ä°ï¿½ï¿½ï¿½ ï¿½ï¿½Ã».
			{
				CHelperManager* pHelperMgr = GameDataManager::getSingleton()->GetHelperManager();
				pHelperMgr->OpenDialog();
			}
			break;
#endif
			case 43:	//ttos ï¿½ï¿½ï¿½ï¿½ ï¿½Þºï¿½
			{
				CUIManager::getSingleton()->GetCombo()->SendComboMessage(MSG_EX_MONSTERCOMBO_EDIT_CONTEXT_REQ);
			}
			break;
			case 46:	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
			{
				CUIManager* pUIManager = CUIManager::getSingleton();

				if (pUIManager->GetItemProduct()->GetHide() == FALSE ||
					pUIManager->GetItemProduct()->IsVisible() == TRUE)
					break;

				pUIManager->GetItemProduct()->OpenUI();

				for (int i = 0; i < SKILL_SPECIAL_SLOT_ROW_TOTAL; i++)
				{
					if (m_nIdxVoucherSkill[i] > 0 &&
						m_nIdxVoucherSkill[i] != 655)
					{
						pUIManager->GetItemProduct()->AddData(m_nIdxVoucherSkill[i]);
					}

				}
				CloseUI();

			}break;
#ifdef ENABLE_AFFINITY
			case 47:
			{
				//CUIManager::getSingleton()->GetAffinityInfo()->SetAffinityData();
				CUIManager::getSingleton()->GetAffinityInfo()->OpenAffinityInfo();
			}
			break;
#endif
			case 48:
			{
				CUIManager::getSingleton()->GetChatFilter()->OpenChatFilter();
			}break;
			case 49:
			{
				if (!CUIManager::getSingleton()->GetNickName()->IsVisible())
				{
					TitleNetwork* pTitle = GAMEDATAMGR()->GetTitleNetwork();
					if (pTitle != NULL)
						pTitle->SendTitleListReq();
				}
			}
			break;
			case 51:
			{
				CUIManager::getSingleton()->GetRankingViewEx()->ToggleVisible();
				
			}
			break;
#ifdef BATTLE_PASS_SYSTEM
			case 53:
			{
				_pNetwork->SendBattlePassInfoReq(NONE);
				break;
			}
#endif
#ifdef QUICK_PANEL//54
			case 54:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();

				if (pUIManager->GetQuickPanel()->IsVisible())
					CUIManager::getSingleton()->GetQuickPanel()->Close();
				else
					CUIManager::getSingleton()->GetQuickPanel()->Open();
			}
			break;
#endif

			case 52:
			{
				//if( )
				CUIManager::getSingleton()->GetCalendar()->OpenCalendar();

			}
			break;
#ifdef DAILY_LOGIN
			case 55:
			{
				CUIManager::getSingleton()->GetRezaDailyLogin()->OpenDailyLoginReq();

						}
						break;
#endif
#ifdef REZABOT
					case 66: 
						
						{
							CUIManager::getSingleton()->GetReZaBotUI()->OpenReZaBotUI();
						}
						break;

#endif 
           case 62:
				{
					CUIManager::getSingleton()->GetCraft()->ToogleVisible(); //Craft system
				}
				break;
			#ifdef PRESTIGE_SYSTEM
			case 61:
				{
					_pNetwork->SendPrestigeInfoReq(NONE);
					break;
				}
			#endif
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS
			case 63:
			{
				_pNetwork->ExpeditionDungeonDetailReq(0);
				
			}
			break;
#endif
#ifdef PASSIVE_SYSTEM
			case 64:
			{
				CUIManager* pUIManager = CUIManager::getSingleton();
				pUIManager->GetPassiveSystem()->ToogleVisible();
			}
			break;
#endif

			}
		}

break;

	case ACTION_PET:		// ï¿½Ö¿Ïµï¿½ï¿½ï¿½...
		{
			switch( nIndex )
			{
			case 35:		// ï¿½ï¿½ ï¿½ï¿½È¯
				{
					if( _pNetwork->MyCharacterInfo.bPetRide )
					{
						return;
					}					
					_pNetwork->CallPet(MY_PET_INFO()->lIndex);
				}
				break;
			case 36:		// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½È¯
				{
					if( !_pNetwork->MyCharacterInfo.bPetRide )
					{
						return;
					}
	//add 03092022				
					//Macabre Block teleport em pvp
					if (_pNetwork->MyCharacterInfo.pk_mode != 0 || _pNetwork->IsRvrZone() || _pNetwork->MyCharacterInfo.sbAttributePos == MATT_FREEPKZONE || _pNetwork->MyCharacterInfo.sbAttributePos == MATT_WAR)//Cloud relog em pvp
					{
						CUIManager* pUIMgr = UIMGR();
						pUIMgr->GetChattingUI()->AddSysMessage(_S(9352, "이미 사용중입니다."), SYSMSG_ERROR);
						return;
					}
					//Macabre Block teleport em pvp

					_pNetwork->SendPetWarpTown();
				}
				break;
			case 37:		// ï¿½ï¿½ ï¿½Ö¿Ïµï¿½ï¿½ï¿½ ï¿½Þ½ï¿½
				{
					if( !_pNetwork->MyCharacterInfo.bPetRide )
					{
						return;
					}
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UseAction( 3 );
				}
				break;
			case 38:		// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ìµï¿½.
				{
					if( !_pNetwork->MyCharacterInfo.bPetRide )
					{
						return;
					}
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UseAction( 2 );					
				}
				break;
				
			case 40:		// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ý±ï¿½.
				{
					if( _pNetwork->MyCharacterInfo.bPetRide )
					{
						return;
					}
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UsePetPickItem();					
				}
				break;
			}
		}
		break;
	case ACTION_WILDPET:
		{
			switch( nIndex )
			{
			case 50:
				{
					if( CUIManager::getSingleton()->GetInventory()->IsWearing( WEAR_PET ) )
					{
						CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( _S(2189,"ï¿½Ö¿Ïµï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ô¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï¿ï¿½ï¿½ß¸ï¿½ ï¿½Õ´Ï´ï¿½."), SYSMSG_ERROR );
						return;
					}
					if (_pNetwork->MyWearItem[WEAR_PET].Item_Flag& FLAG_ITEM_SEALED)
 					{
						CUIManager::getSingleton()->GetChattingUI()->AddSysMessage( _S(5348,"ï¿½ï¿½ï¿½Îµï¿½ ï¿½ï¿½ï¿½Â¿ï¿½ï¿½ï¿½ï¿½ï¿½ Å¾ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½."), SYSMSG_ERROR );
						return;
					}
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UseAction( nIndex );					
				}break;
			}
		}break;

	case ACTION_SOCIAL:
		{
			// ï¿½Ö¿Ïµï¿½ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ò¼ï¿½ ï¿½×¼ï¿½ï¿½ï¿½ ï¿½Ò°ï¿½ï¿½ï¿½.
			if( !_pNetwork->MyCharacterInfo.bPetRide )
			{
				//ï¿½ï¿½ï¿½Ñ¸ï¿½ï¿½ï¿½ ï¿½×¼ï¿½ï¿½ï¿½ ï¿½ï¿½...
				if( nIndex ==42 )
				{
					CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
					if( penPlayerEntity->CommandAction() )
						penPlayerEntity->UseSkill( 436 );
				}
				else
					((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UseAction( nIndex );


				// [071211: Su-won] EVENT_NEWYEAR_2008
				if( IS_EVENT_ON(TEVENT_NEWYEAR_2008) )
				{
					if( nIndex == 10 ) 
					{
						if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER &&
							_pNetwork->MyCharacterInfo.index != pInfo->GetTargetServerIdx(eTARGET))
						{
							_pNetwork->ClientSystemMessage( _S(3964, "ï¿½ï¿½ï¿½Øºï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½!"), SYSMSG_ERROR );

							CNetworkMessage nmSkill((UBYTE)MSG_SKILL);
							nmSkill << (UBYTE)MSG_SKILL_NEWYEAR_2008;
							nmSkill << _pNetwork->MyCharacterInfo.index;
							nmSkill << (LONG)pInfo->GetTargetServerIdx(eTARGET);

							_pNetwork->SendToServerNew(nmSkill);
						}
					}
				}
			}
		}
		break;

	case ACTION_PARTY:
		{
			int nTargetIndex = 0;
			if (pInfo->GetTargetEntity(eTARGET) != NULL)
			{
				nTargetIndex = pInfo->GetTargetServerIdx(eTARGET);
			}

			Party* pParty = GAMEDATAMGR()->GetPartyInfo();

			if (pParty == NULL)
				return;
				
			switch( nIndex )
			{
			case 6:		// ï¿½ï¿½Æ¼ ï¿½ï¿½Ã»(ï¿½Õµï¿½ ï¿½Ð¹ï¿½)
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						CTString	strTarget = pInfo->GetTargetName(eTARGET);
						pParty->SendPartyInvite( PT_PEACEEVER, strTarget );
					}
				}
				break;
			case 7:		// ï¿½ï¿½Æ¼ ï¿½ï¿½Ã»(ï¿½Ô¼ï¿½ ï¿½ì¼±)
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						CTString	strTarget = pInfo->GetTargetName(eTARGET);
						pParty->SendPartyInvite( PT_SURVIVAL, strTarget );
					}
				}
				break;
			case 8:		// ï¿½ï¿½Æ¼ ï¿½ï¿½Ã»(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						CTString	strTarget = pInfo->GetTargetName(eTARGET);
						pParty->SendPartyInvite( PT_ATTACK, strTarget );
					}
				}
				break;

			case 9:		// ï¿½ï¿½Æ¼ Å»ï¿½ï¿½
				{
					pParty->SendPartyQuit();
				}
				break;

			case 39:	// ï¿½ï¿½Æ¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ 
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						CUIManager* pUIManager = CUIManager::getSingleton();

						if( pParty->GetMemberCount() <= 0 ) // ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´Ï¶ï¿½ï¿½
						{
							break;
						}
						if( !pParty->AmILeader() ) // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´Ï¶ï¿½ï¿½
						{
							pParty->PartyError( MSG_PARTY_ERROR_NOT_BOSS );
							break;
						}
							
						CTString	strTarget = pInfo->GetTargetName(eTARGET);
						
						if( pParty->IsOurParty( strTarget ) ) // ï¿½ì¸® ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã³ï¿½ï¿½ 
						{		
							pParty->MandateBossReq( strTarget );
						}
						else  // ï¿½ì¸® ï¿½ï¿½Æ¼ï¿½ï¿½ï¿½Æ´Ï¶ï¿½ï¿½...
						{
							pParty->PartyError( MSG_PARTY_ERROR_NOT_PARTY_MEMBER );
						}
						
						
					}
				}
				break;

			case 12:		// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						CTString	strTarget = pInfo->GetTargetName(eTARGET);
						pParty->SendPartyKick( strTarget );
					}
				}
				break;

			case 33:	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½Ã¢ ï¿½ï¿½ï¿½
				{
					CUIManager::getSingleton()->GetParty()->ToggleVisible();
				}
				break;
#ifdef PARTY_AUTO_ENABLE
			case 41:	// ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Äª ï¿½Ã½ï¿½ï¿½ï¿½
				{
					if( IsVisible() ) { ToggleVisible(); }
					CUIManager::getSingleton()->GetPartyAuto()->OpenPartyMatching();
				}
				break;
#endif
			}
		}
		break;

	case ACTION_GUILD:
		{
			int nTargetIndex = 0;
			if (pInfo->GetTargetEntity(eTARGET) != NULL)
			{
				nTargetIndex = pInfo->GetTargetServerIdx(eTARGET);
			}

			switch( nIndex )
			{
				case 24:	// ï¿½ï¿½ï¿½ï¿½ï¿½Ï±ï¿½
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					// ï¿½Ù¸ï¿½ ï¿½ï¿½å¿¡ ï¿½ï¿½ï¿½ÔµÇ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Å»ï¿½ï¿½ ï¿½ï¿½ï¿½îº»ï¿½ï¿½.
					if( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_NOMEMBER )
					{
						CUIManager* pUIManager = CUIManager::getSingleton();

						pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
						pUIManager->CloseMessageBox(MSGCMD_GUILD_DESTROY);
						pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN);
						pUIManager->CloseMessageBox(MSGCMD_GUILD_JOIN_REQ);
						pUIManager->CloseMessageBox(MSGCMD_GUILD_QUIT);
						pUIManager->CloseMessageBox(MSGCMD_GUILD_APPLICANT_JOIN);	
						
						CTString		strMessage;
						CUIMsgBox_Info	MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo( _S( 865, "ï¿½ï¿½ï¿½" ), UMBS_OK,		
							UI_GUILD, MSGCMD_GUILD_ERROR );
						if( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_NOMEMBER)
						{
							strMessage.PrintF( _S( 866, "ï¿½Ì¹ï¿½ ï¿½ï¿½å¿¡ ï¿½ï¿½ï¿½ÔµÇ¾ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½.\nï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ÔµÇ¾ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½å¿¡ï¿½ï¿½ Å»ï¿½ï¿½ï¿½Ï¿ï¿½ ï¿½Ö½Ê½Ã¿ï¿½." ) );	
						}
						MsgBoxInfo.AddString( strMessage );
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					else if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						// Find index of character
						SLONG	slIndex = -1;

						CEntity	*pEntity		= pInfo->GetTargetEntity(eTARGET);
						if (pEntity != NULL)
						{
							ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pEntity->GetNetworkID());

							if (pObject != NULL)
							{
								CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

								CUIManager* pUIManager = CUIManager::getSingleton();

								// FIXME : ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ ï¿½Ó½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Îºï¿½ï¿½Ô´Ï´ï¿½.
								if( pTarget->cha_lGuildPosition == GUILD_MEMBER_BOSS || 
									pTarget->cha_lGuildPosition == GUILD_MEMBER_VICE_BOSS )
								{
									slIndex = pTarget->m_nIdxServer;		
									pUIManager->GetGuild()->JoinGuild( pTarget->cha_lGuildIndex, pTarget->m_nIdxServer, 
										pTarget->cha_strGuildName, pTarget->cha_iSyndicateType );
								}
								else
								{
									pUIManager->CloseMessageBox(MSGCMD_GUILD_ERROR);
									CUIMsgBox_Info	MsgBoxInfo;
									MsgBoxInfo.SetMsgBoxInfo( _S( 865, "ï¿½ï¿½ï¿½" ), UMBS_OK, UI_GUILD, MSGCMD_GUILD_ERROR );		
									MsgBoxInfo.AddString( _S( 867, "ï¿½ï¿½ï¿½ï¿½å¿¡ï¿½Ô¸ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Õ´Ï´ï¿½." ) );	
									pUIManager->CreateMessageBox( MsgBoxInfo );		
								}
							}
						}						
					}
				}
				break;

			case 25:	// Å»ï¿½ï¿½ï¿½Ï±ï¿½
				{
					// Ä³ï¿½ï¿½ï¿½Í°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ì¶ï¿½ï¿½ Å»ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
					if( _pNetwork->MyCharacterInfo.lGuildPosition > 0 && _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS)
					{	
						CUIManager::getSingleton()->GetGuild()->QuitGuild();
					}
				}
				break;
			
			case 26:	// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
				{
					// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Þ¼ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ä¿ï¿½, Receiveï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ È£ï¿½ï¿½ï¿½Ø¾ï¿½ ï¿½ï¿½.
					// WSS_NEW_GUILD_SYSTEM 070704
					// WSS_TEST 
					// TODO : ï¿½Ó½ï¿½ ï¿½ï¿½ï¿½ Ã¢
					if( _pNetwork->MyCharacterInfo.lGuildLevel < LIMIT_GUILD_LEVEL )
						CUIManager::getSingleton()->GetGuild()->OpenGuildManager( _pNetwork->MyCharacterInfo.lGuildPosition );						
					else 
						CUIManager::getSingleton()->GetGuild()->OpenGuildManagerNew();
				}
				break;
			
			case 34:// ï¿½Ó½ï¿½ ï¿½Úµï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½×½ï¿½Æ® 
				{
					if( !_pNetwork->IsLord() ) 
					{
						return;
					}


					CTString strSysMessage;
					CUIMsgBox_Info	MsgBoxInfo;

					MsgBoxInfo.SetMsgBoxInfo( _S( 1886, "ï¿½ï¿½ï¿½Ö°ï¿½ï¿½ï¿½" ), UMBS_USER_12 | UMBS_INPUT_MASK | UMBS_ALIGN_RIGHT, UI_NONE, MSGCMD_GUILD_LORD_NOTICE, 300 ); 
					MsgBoxInfo.SetUserBtnName( _S( 1887, "ï¿½ï¿½ï¿½ï¿½" ), _S( 870, "ï¿½Ý±ï¿½" ) ); 
					MsgBoxInfo.SetInputBox( 2, 2, 80, 235 );	
				
					strSysMessage.PrintF( _S( 1889, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ô·ï¿½ï¿½Ï½Ê½Ã¿ï¿½." ) ); 
					MsgBoxInfo.AddString( strSysMessage, 0xF3F3F3FF, TEXT_CENTER );
					
					CUIManager::getSingleton()->CreateMessageBox( MsgBoxInfo );
					
				}
				break;

			case 31 : // ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã» 
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					// Å¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Å³ï¿½ ï¿½Ã¹Ù¸ï¿½ï¿½ï¿½ ï¿½Ê´Ù¸ï¿½
					if( pInfo->IsTargetActive(eTARGET) == FALSE || !pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						return;
					}
					
					/*****
					// ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã¼Å© 
					if ( ZoneInfo().GetZoneType( g_slZone ) != ZONE_FIELD )
					{
						CUIManager::getSingleton()->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, 
										_S( 1085, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´Õ´Ï´ï¿½." ) );	
						return;
					}
					*****/
					
					// ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã¼Å© 
					if( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS )
					{
						CUIManager::getSingleton()->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, 
								_S( 1086, "ï¿½ï¿½ï¿½ï¿½å¸¸ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½." ) );	
						return;
					}
									
					//!! ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã» 
					CEntity	*pEntity		= pInfo->GetTargetEntity(eTARGET);

					if (pEntity != NULL)
					{
						ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pEntity->GetNetworkID());

						if (pObject != NULL)
						{
							CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

							CUIManager* pUIManager = CUIManager::getSingleton();

							if( pTarget->cha_lGuildPosition != GUILD_MEMBER_BOSS )
							{
								pUIManager->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, 
									_S( 1088, "ï¿½ï¿½ï¿½ï¿½å¿¡ï¿½Ô¸ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½." ) );	
								return;
							}
							else 
							{
								pUIManager->GetGuildBattle()->OpenGBReq( pTarget->m_nIdxServer, pTarget->cha_strGuildName );
							}
						}
					}
				}
				break;

			case 32 : // ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ß´ï¿½ ï¿½ï¿½Ã» 
				{
					if (nTargetIndex == _pNetwork->MyCharacterInfo.index)
						return;

					// Å¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Å³ï¿½ ï¿½Ã¹Ù¸ï¿½ï¿½ï¿½ ï¿½Ê´Ù¸ï¿½
					if( pInfo->IsTargetActive(eTARGET) == FALSE || !pInfo->GetTargetType(eTARGET) == CHARACTER )
					{
						return;
					}

					CUIManager* pUIManager = CUIManager::getSingleton();

					// ï¿½ï¿½ï¿½ ï¿½ß´ï¿½ ï¿½ï¿½Ã» 
					// ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã¼Å© 
					if( _pNetwork->MyCharacterInfo.lGuildPosition != GUILD_MEMBER_BOSS )
					{
						pUIManager->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, 
								_S( 1089, "ï¿½ï¿½ï¿½ï¿½å¸¸ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ß´ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½." ) );	
						return;
					}
					
					if( pUIManager->GetGuildBattle()->IsInBattle() == FALSE )
					{
						pUIManager->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, _S( 1090, "ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´Õ´Ï´ï¿½." ) ); 
						return;
					}

					// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»
					CEntity	*pEntity		= pInfo->GetTargetEntity(eTARGET);

					if (pEntity != NULL)
					{
						ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pEntity->GetNetworkID());

						if (pObject != NULL)
						{
							CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

							if( pTarget->cha_lGuildPosition != GUILD_MEMBER_BOSS )
							{
								pUIManager->GetGuildBattle()->GBErrorMessage ( MSGCMD_GUILD_BATTLE_ERROR, 
									_S( 1091, "ï¿½ï¿½ï¿½ï¿½å¿¡ï¿½Ô¸ï¿½ ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ß´ï¿½ï¿½ï¿½ ï¿½ï¿½Ã»ï¿½ï¿½ ï¿½ï¿½ ï¿½Ö½ï¿½ï¿½Ï´ï¿½." ) );	
								return;
							}
							else 
							{
								pUIManager->GetGuildBattle()->GBStopReq( pTarget->m_nIdxServer, pTarget->cha_strGuildName );
							}
						}
					}
				}
				break;

			case 53:	// ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã§ï¿½ï¿½ï¿½ï¿½
				{
					UIMGR()->GetGuildBattleMatch()->open();
				}
				break;
			}
		}
		break;
	}
}

// ï¿½ï¿½Å³ ï¿½ï¿½ï¿½
void CUICharacterInfo::UseSkill( int nIndex )
{
	if( _pNetwork->MyCharacterInfo.sbShopType != PST_NOSHOP || 
		CUIManager::getSingleton()->IsCSFlagOn( CSF_TELEPORT ) )
		return;

	// ï¿½ï¿½ï¿½Î»ï¿½ï¿½ï¿½ ï¿½Ãµï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½Å³ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	if(_pNetwork->m_iNetworkResponse[MSG_PERSONALSHOP] != 0)
		return;

	// ï¿½×½ï¿½Æ®ï¿½ï¿½.
	((CPlayerEntity*)CEntity::GetPlayerEntity(0))->UseSkill( nIndex );
	//_pNetwork->CreateSlave( 0, CEntity::GetPlayerEntity(0), 1 );
}

// ï¿½ï¿½Å³ ï¿½ï¿½Æ° ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å¸Æ®
void CUICharacterInfo::StartSkillDelay( int nIndex )
{
	for( int iRow = 0; iRow < SKILL_ACTIVE_SLOT_ROW_TOTAL; iRow++ )
	{
		if( iRow < SKILL_ACTIVE_SLOT_ROW_TOTAL && m_nIdxItemSpecialSkill[iRow] == nIndex )
		{
//			m_nIdxItemSpecialSkill[iRow]->setCooltime(true);
			SetItemSkill();
			break;
		}
	}
}

// ï¿½ï¿½Å³ ï¿½Ê±ï¿½È­ (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½Å³, ï¿½ï¿½ï¿½ï¿½)
void CUICharacterInfo::ClearSkills()
{
	int		iRow;

	for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
		m_nIdxVoucherSkill[iRow] = -1;

	SetSeal();

	for( iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
		m_nIdxItemSpecialSkill[iRow] = -1;

	SetItemSkill();
}

// Æ¯ï¿½ï¿½ ï¿½ï¿½Å³ ï¿½Ê±ï¿½È­
void CUICharacterInfo::ClearSSkills()
{
	for( int iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
		m_nIdxSpecialSkill[iRow] = -1;

	SetSSkill();
}

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®
void CUICharacterInfo::updateStatusPt(int type, int value)
{
	CTString strString = CTString("");
	COLOR strColor;
	int added = 0;
	
	switch( type )
	{
	case MSG_STATPOINT_USE_STR:
		{
			_pNetwork->MyCharacterInfo.str += value;

			strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.str,
				_pNetwork->MyCharacterInfo.opt_str );
			strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_str);

			if (m_ptxtStat[eCHARINFO_STAT_STR] != NULL)
			{
				m_ptxtStat[eCHARINFO_STAT_STR]->SetText(strString);
				m_ptxtStat[eCHARINFO_STAT_STR]->setFontColor(strColor);
			}
		}
		break;
	case MSG_STATPOINT_USE_DEX:
		{
			_pNetwork->MyCharacterInfo.dex += value;

			strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.dex,
				_pNetwork->MyCharacterInfo.opt_dex );
			strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_dex);

			if (m_ptxtStat[eCHARINFO_STAT_DEX] != NULL)
			{
				m_ptxtStat[eCHARINFO_STAT_DEX]->SetText(strString);
				m_ptxtStat[eCHARINFO_STAT_DEX]->setFontColor(strColor);
			}
		}
		break;
	case MSG_STATPOINT_USE_INT:
		{
			_pNetwork->MyCharacterInfo.intel += value;

			strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.intel,
				_pNetwork->MyCharacterInfo.opt_intel );
			strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_intel);

			if (m_ptxtStat[eCHARINFO_STAT_INT] != NULL)
			{
				m_ptxtStat[eCHARINFO_STAT_INT]->SetText(strString);
				m_ptxtStat[eCHARINFO_STAT_INT]->setFontColor(strColor);
			}
		}
		break;
	case MSG_STATPOINT_USE_CON:
		{
			_pNetwork->MyCharacterInfo.con += value;

			strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.con,
				_pNetwork->MyCharacterInfo.opt_con );
			strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_con);

			if (m_ptxtStat[eCHARINFO_STAT_CON] != NULL)
			{
				m_ptxtStat[eCHARINFO_STAT_CON]->SetText(strString);
				m_ptxtStat[eCHARINFO_STAT_CON]->setFontColor(strColor);
			}
		}
		break;
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPoint );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT] != NULL)
		m_ptxtStat[eCHARINFO_STAT_STATPOINT]->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPointAddition );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION] != NULL) {
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->setFontColor(GetStrColor(0));
	}
}

void CUICharacterInfo::UpdateExpAndSp(void)
{
	CUIManager* pUIMgr = CUIManager::getSingleton();
	CTString strString = CTString("");
	CTString strCur, strNeed;

	strCur.PrintF("%I64d", _pNetwork->MyCharacterInfo.curExp);
	strNeed.PrintF("%I64d", _pNetwork->MyCharacterInfo.needExp);

	pUIMgr->InsertCommaToString(strCur);
	pUIMgr->InsertCommaToString(strNeed);

	strString.PrintF( "%s/%s", strCur, strNeed );

	if (m_ptxtBase[eCHARINFO_BASE_EXP] != NULL)
		m_ptxtBase[eCHARINFO_BASE_EXP]->SetText(strString);

	strString.PrintF("%I64d", _pNetwork->MyCharacterInfo.sp / 10000);
	pUIMgr->InsertCommaToString(strString);

	if (m_ptxtBase[eCHARINFO_BASE_SP] != NULL)
		m_ptxtBase[eCHARINFO_BASE_SP]->SetText(strString);	
}

void CUICharacterInfo::UpdateSealExp(int nSealIndex, SQUAD lSealExp )
{
	for(int iRow = 0; iRow < SKILL_SPECIAL_SLOT_ROW_TOTAL; iRow++ )
	{
		if (m_nIdxVoucherSkill[iRow] == nSealIndex)
		{
			m_nIdxVoucherSkill[iRow] = nSealIndex;
			MY_INFO()->SetSkillExp(nSealIndex, lSealExp);
			break;
		}
	}
	SetSeal();
}

void CUICharacterInfo::UpdateSkillInfo(int nType, int nTotal)
{
	if(nType < BTN_ACTION_NORMAL)
	{
		BOOL bSpecial = FALSE;
		if(nType == BTN_SKILL_SPECIAL)
		{
			bSpecial = TRUE;
		}

		CUIManager* pUIManager = CUIManager::getSingleton();
		CUISkillLearn* pUISkillLearn = pUIManager->GetSkillLearn();
		int nIdx;

		for(int i=0; i<nTotal; i++)
		{
			nIdx = m_pIdxSelectedSkill[i];
			m_pSelectedSkillSatisfied[i] = 
				pUISkillLearn->IsSatisfiedSkill( nIdx, MY_INFO()->GetSkillLevel(nIdx), bSpecial);
		}
	}

	int nItemTotal = 0;
	for(int i = 0; i<nTotal; i++)
	{
		if (m_pIdxSelectedSkill[i] < 0)
		{
			break;
		}
		nItemTotal++;
	}


	m_nBtnTotal = nTotal;

	SetItemSkill();
	SetSeal();
	SetSSkill();
}

void CUICharacterInfo::UpdateStatus( int iAttack, int iMagic, int iDefense, int iResist )
{
	CTString strString = CTString("");
	COLOR strColor;
	int added = 0;

	strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.str,
		_pNetwork->MyCharacterInfo.opt_str );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_str);

	if (m_ptxtStat[eCHARINFO_STAT_STR] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_STR]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_STR]->setFontColor(strColor);
	}

	strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.dex,
		_pNetwork->MyCharacterInfo.opt_dex );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_dex);

	if (m_ptxtStat[eCHARINFO_STAT_DEX] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_DEX]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_DEX]->setFontColor(strColor);
	}
	
	strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.intel,
		_pNetwork->MyCharacterInfo.opt_intel );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_intel);

	if (m_ptxtStat[eCHARINFO_STAT_INT] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_INT]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_INT]->setFontColor(strColor);
	}

	strString.PrintF( "%3d (%2d)", _pNetwork->MyCharacterInfo.con,
		_pNetwork->MyCharacterInfo.opt_con );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.opt_con);

	if (m_ptxtStat[eCHARINFO_STAT_CON] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_CON]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_CON]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPoint );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT] != NULL)
		m_ptxtStat[eCHARINFO_STAT_STATPOINT]->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPointAddition );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION] != NULL) {
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->setFontColor(GetStrColor(0));
	}

	strString.PrintF( "%d", iAttack );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.addedAttack);

	if (m_ptxtStat[eCHARINFO_STAT_ATTACK] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_ATTACK]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_ATTACK]->setFontColor(strColor);
	}

	strString.PrintF( "%d", iMagic );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.addedMagic);

	if (m_ptxtStat[eCHARINFO_STAT_MAGICATTACK] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_MAGICATTACK]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_MAGICATTACK]->setFontColor(strColor);
	}

	strString.PrintF( "%d", iDefense );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.addedDefense);

	if (m_ptxtStat[eCHARINFO_STAT_DEFENSE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_DEFENSE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_DEFENSE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", iResist );
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.addedResist);

	if (m_ptxtStat[eCHARINFO_STAT_MAGICDEFENSE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_MAGICDEFENSE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_MAGICDEFENSE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.hitRate );	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ßµï¿½
	added = _pNetwork->MyCharacterInfo.hitRate - _pNetwork->MyCharacterInfo.baseHitRate;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_HITRATE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_HITRATE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_HITRATE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.dodgeRate );	//ï¿½ï¿½ï¿½ï¿½ È¸ï¿½Çµï¿½
	added = _pNetwork->MyCharacterInfo.dodgeRate - _pNetwork->MyCharacterInfo.baseDodgeRate;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_DODGERATE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_DODGERATE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_DODGERATE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.critical );	//Å©ï¿½ï¿½Æ¼ï¿½ï¿½
	added = _pNetwork->MyCharacterInfo.critical - _pNetwork->MyCharacterInfo.baseCritical;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_CRITICAL] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_CRITICAL]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_CRITICAL]->setFontColor(strColor);
	}

	strString.PrintF( "%64.1f", _pNetwork->MyCharacterInfo.runspeed );			//ï¿½Ìµï¿½ï¿½Óµï¿½
	added = ( _pNetwork->MyCharacterInfo.runspeed * 10 ) - ( _pNetwork->MyCharacterInfo.baseRunSpeed * 10 );
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_MOVESPEED] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_MOVESPEED]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_MOVESPEED]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.magicHitRate );	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ßµï¿½
	added = _pNetwork->MyCharacterInfo.magicHitRate - _pNetwork->MyCharacterInfo.baseMagicHitRate;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_MAGICHITRATE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_MAGICHITRATE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_MAGICHITRATE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.magicDodgeRate );		//ï¿½ï¿½ï¿½ï¿½ È¸ï¿½Çµï¿½
	added = _pNetwork->MyCharacterInfo.magicDodgeRate - _pNetwork->MyCharacterInfo.baseMagicDodgeRate;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_MAGICDODGERATE] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_MAGICDODGERATE]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_MAGICDODGERATE]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.deadly );		//ï¿½ï¿½ï¿½é¸®
	added = _pNetwork->MyCharacterInfo.deadly - _pNetwork->MyCharacterInfo.baseDeadly;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_DEADLY] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_DEADLY]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_DEADLY]->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.attackspeed );			//ï¿½ï¿½ï¿½Ý¼Óµï¿½
	added = _pNetwork->MyCharacterInfo.attackspeed - _pNetwork->MyCharacterInfo.baseAttackSpeed;
	strColor = GetStrColor(added);

	if (m_ptxtStat[eCHARINFO_STAT_ATTACKSPEED] != NULL)
	{
		m_ptxtStat[eCHARINFO_STAT_ATTACKSPEED]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_ATTACKSPEED]->setFontColor(strColor);
	}
	
	CUIManager* pUIManager = UIMGR();
	CTString strTemp = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.pkcount);
	strString.PrintF( "%s", strTemp );

	if (m_pstrPkPointAcc != NULL)
		m_pstrPkPointAcc->SetText(strString);

	strTemp = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.fame);
	strString.PrintF( "%s", strTemp );

	if (m_ptxtBase[eCHARINFO_BASE_FRAME] != NULL)
		m_ptxtBase[eCHARINFO_BASE_FRAME]->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.attrattLv );		// ï¿½ï¿½ï¿½ï¿½ ï¿½Ó¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	//if (m_pstrAttlv != NULL)
	//	m_pstrAttlv->SetText(strString);

	//strString.PrintF( "%d", _pNetwork->MyCharacterInfo.attrdefLv );		// ï¿½ï¿½ï¿½ ï¿½Ó¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	//if (m_pstrDeflv != NULL)
	//	m_pstrDeflv->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.a_wins );		// ï¿½ï¿½ï¿½ ï¿½Ó¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	if (m_PVP_Winer != NULL)
		m_PVP_Winer->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.a_loses );		// ï¿½ï¿½ï¿½ ï¿½Ó¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	if (m_PVP_Lose != NULL)
		m_PVP_Lose->SetText(strString);
	 //this isn't reading anything atm.  i dont think its working also not progress bar either.
	strString.PrintF("%d", _pNetwork->MyCharacterInfo.a_honor);		// ï¿½ï¿½ï¿½ ï¿½Ó¼ï¿½ ï¿½ï¿½ï¿½ï¿½
	if (m_honor != NULL)
		m_honor->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.opResistStone );
	added = _pNetwork->MyCharacterInfo.opResistStone;
	strColor = GetStrColor(added);

	if (m_opResistStone != NULL) {
		m_opResistStone->SetText(strString);
		m_opResistStone->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.opResistSturn );
	added = _pNetwork->MyCharacterInfo.opResistSturn;
	strColor = GetStrColor(added);

	if (m_opResistSturn != NULL) {
		m_opResistSturn->SetText(strString);
		m_opResistSturn->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.opResistSilent );
	added = _pNetwork->MyCharacterInfo.opResistSilent;
	strColor = GetStrColor(added);

	if (m_opResistSilent != NULL) {
		m_opResistSilent->SetText(strString);
		m_opResistSilent->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.opabsorbPVPDamageRate );
	added = _pNetwork->MyCharacterInfo.opabsorbPVPDamageRate;
	strColor = GetStrColor(added);

	if (m_absorbPVPDamageRate != NULL) {
		m_absorbPVPDamageRate->SetText(strString);
		m_absorbPVPDamageRate->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.opDecreaseSkillMP );
	added = _pNetwork->MyCharacterInfo.opDecreaseSkillMP;
	strColor = GetStrColor(added);

	if (m_opDecreaseSkillMP != NULL) {
		m_opDecreaseSkillMP->SetText(strString);
		m_opDecreaseSkillMP->setFontColor(strColor);
	}

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.skillSpeed );
	added = _pNetwork->MyCharacterInfo.skillSpeed;
	strColor = GetStrColor(added);

	if (m_skillSpeed != NULL) {
		m_skillSpeed->SetText(strString);
		m_skillSpeed->setFontColor(strColor);
	}

	/*int nAtt = _pNetwork->MyCharacterInfo.attratt;
	int nDef = _pNetwork->MyCharacterInfo.attrdef;

	if (m_pImgArrAtt != NULL)
		m_pImgArrAtt->SetRenderIdx(nAtt);

	if (m_pImgArrDef != NULL)
		m_pImgArrDef->SetRenderIdx(nDef)*/;
	
	if (m_pImgArrWiner != NULL)
		m_pImgArrWiner->SetRenderIdx(1);  //pwesty

	if (m_pImgArrLose != NULL)
		m_pImgArrLose->SetRenderIdx(5);

	UpdateExpAndSp();
}

////////////////////////////////////  UI  /////////////////////////////////////////////////

// ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ã·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
COLOR CUICharacterInfo::GetStrColor(int nAdded)
{
	if(nAdded == 0)
	{
		return 0xFFC000FF;
	}
	else if(nAdded > 0)
	{
		return 0x00B050FF;
	}
	else if(nAdded < 0)
	{
		return 0xFF0000FF;
	}

	return 0xFF0000FF;
}

// ï¿½Ç¿ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ° ï¿½ï¿½ï¿½ï¿½
void CUICharacterInfo::SetCurrentSkillInfo(int nSideTab, int nUpperTab)
{
	if(nSideTab == PAGE_CHARINFO_NEW_SKILL)
	{
		switch(nUpperTab)
		{
		case eTAB_SKILL_ITEM:
			m_nCurrentSkillType = BTN_SKILL_ITEM;
			m_nBtnTotal = SKILL_SPECIAL_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxItemSpecialSkill;
			SetItemSkill();
			break;
		case eTAB_SKILL_SSKILL:
			m_nCurrentSkillType = BTN_SKILL_SPECIAL;
			m_nBtnTotal = SKILL_SPECIAL_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxSpecialSkill;
			SetSSkill();
			break;
		case eTAB_SKILL_SEAL:
			m_nCurrentSkillType = BTN_SKILL_VOUCHER;
			m_nBtnTotal = SKILL_SPECIAL_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxVoucherSkill;
			SetSeal();
			break;
		}

	}
	else if(nSideTab == PAGE_CHARINFO_NEW_ACTION_SOCIAL)
	{
		switch(nUpperTab)
		{
		case 0:
			m_nCurrentSkillType = BTN_ACTION_NORMAL;
			m_nBtnTotal = ACTION_NORAML_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxNormalAction;
			SetAction();
			break;
		case 1:
			m_nCurrentSkillType = BTN_ACTION_SOCIAL;
			m_nBtnTotal = ACTION_SOCIAL_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxSocialAction;
			SetSocial();
			break;
		}	
	}
	else if(nSideTab == PAGE_CHARINFO_NEW_GUILD_PARTY)
	{
		switch(nUpperTab)
		{
		case 0:
			m_nCurrentSkillType = BTN_ACTION_PARTY;
			m_nBtnTotal = ACTION_PARTY_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxPartyAction;
			SetParty();
			break;
		case 1:
			m_nCurrentSkillType = BTN_ACTION_GUILD;
			m_nBtnTotal = ACTION_GUILD_SLOT_ROW_TOTAL;
			m_pIdxSelectedSkill = m_nIdxGuildAction;
			SetGuild();
			break;
		}	
	}


	m_nSkillActionUpperTab[nSideTab - 1] = nUpperTab;

	if(m_nCurrentSkillType < BTN_ACTION_NORMAL)
	{
		BOOL bSpecial = FALSE;
		if(m_nCurrentSkillType == BTN_SKILL_SPECIAL)
		{
			bSpecial = TRUE;
		}
		for(int i=0; i<m_nBtnTotal; i++)
		{
			m_pSelectedSkillSatisfied[i] = 
				UIMGR()->GetSkillLearn()->IsSatisfiedSkill(m_pIdxSelectedSkill[i], 
											MY_INFO()->GetSkillLevel(m_pIdxSelectedSkill[i]), bSpecial);
		}
	}

	int nItemTotal = 0;
	for(int i = 0; i<m_nBtnTotal; i++)
	{
		if (m_pIdxSelectedSkill[i] < 0)
		{
			break;
		}
		nItemTotal++;
	}

	UpdateSelectImage(NULL);
}

// Å¸ï¿½ï¿½Æ² ï¿½Ì¸ï¿½ ï¿½ï¿½ï¿½ï¿½
void CUICharacterInfo::SetCurrentPageNewCharacterInfo(int nTabNum)
{
	m_ucipCurrentPage = nTabNum;
	
	if(m_ucipCurrentPage == PAGE_CHARINFO_NEW_SKILL)
	{
		m_strTitleName.PrintF("%s", _S(6077, "Æ¯ï¿½ï¿½ ï¿½ï¿½Å³") );
		SetCurrentSkillInfo(PAGE_CHARINFO_NEW_SKILL, m_nSkillActionUpperTab[0]);
	}
	else if(m_ucipCurrentPage == PAGE_CHARINFO_NEW_ACTION_SOCIAL)
	{
		m_strTitleName.PrintF( "%s,%s",_S(94, "ï¿½×¼ï¿½") ,_S(96, "ï¿½Ò¼ï¿½") );
		SetCurrentSkillInfo(PAGE_CHARINFO_NEW_ACTION_SOCIAL, m_nSkillActionUpperTab[1]);	
	}
	else if(m_ucipCurrentPage == PAGE_CHARINFO_NEW_GUILD_PARTY)
	{
		m_strTitleName.PrintF("%s,%s",_S(97, "ï¿½ï¿½Æ¼") ,_S(98, "ï¿½ï¿½ï¿½") );
		SetCurrentSkillInfo(PAGE_CHARINFO_NEW_GUILD_PARTY, m_nSkillActionUpperTab[2]);	
	}
	else if(m_ucipCurrentPage == PAGE_CHARINFO_NEW_SYNDICATE)
	{
		GameDataManager* pGameDataManager = GameDataManager::getSingleton();
		CSyndicate* pSyndi = pGameDataManager->GetSyndicate();

		if (pSyndi != NULL)
			pSyndi->SendSyndicateInfoUser();

		m_strTitleName.PrintF("%s", _S(6130, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½"));
		UpdateSyndicateMark();
		UpdateMySyndiPos();
		UpdateSyndiHistory();

		UpdateSelectImage(NULL);
	}
	else
	{
		m_strTitleName.PrintF("%s", _S(69, "Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½") );
		UpdateStatTooltip();

		UpdateSelectImage(NULL);
	}

	UpdateHonorPoints();

	ChangeCheckImg(m_ucipCurrentPage);
}

// ï¿½ï¿½Æ° ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ¼, ï¿½ï¿½ï¿½, ï¿½×¼ï¿½, ï¿½Ò¼ï¿½
void CUICharacterInfo::RegisterActions()
{
	// Clear action buttons
	int		iAct;
	for( iAct = 0; iAct < ACTION_NORAML_SLOT_ROW_TOTAL; iAct++ )
		m_nIdxNormalAction[iAct] = -1;
	for( iAct = 0; iAct < ACTION_SOCIAL_SLOT_ROW_TOTAL; iAct++ )
		m_nIdxSocialAction[iAct] = -1;
	for( iAct = 0; iAct < ACTION_PARTY_SLOT_ROW_TOTAL; iAct++ )
		m_nIdxPartyAction[iAct] = -1;
	for( iAct = 0; iAct < ACTION_GUILD_SLOT_ROW_TOTAL; iAct++ )
		m_nIdxGuildAction[iAct] = -1;

	int	ctNormalAction = 0;
	int	ctSocialAction = 0;
	int	ctPartyAction = 0;
	int	ctGuildAction = 0;

	// Register action data
	CAction::_map::iterator	iter = CAction::_mapdata.begin();
	CAction::_map::iterator	eiter = CAction::_mapdata.end();

	for (;iter != eiter; ++iter)
	{
		CAction* pActionData = (*iter).second;

		if (pActionData == NULL)
			continue;

		// If job is different
		if( !( pActionData->GetJob() & ( 1 << _pNetwork->MyCharacterInfo.job ) ) )
			continue;

		if ( _pNetwork->m_iServerType == SERVER_TYPE_HARDCORE &&
			pActionData->GetType() == ACTION_NORMAL &&
			pActionData->GetIndex() == 30 /*ï¿½Ä°ï¿½ï¿½ï¿½ ï¿½Ã½ï¿½ï¿½ï¿½*/)
			continue;

		switch( pActionData->GetType() )
		{
		case ACTION_WILDPET:
		case ACTION_PET:
		case ACTION_NORMAL:
			m_nIdxNormalAction[ctNormalAction++] = pActionData->GetIndex();
			break;

		case ACTION_SOCIAL:		
			m_nIdxSocialAction[ctSocialAction++] = pActionData->GetIndex();
			break;

		case ACTION_PARTY:
			m_nIdxPartyAction[ctPartyAction++] = pActionData->GetIndex();
			break;

		case ACTION_GUILD:
			m_nIdxGuildAction[ctGuildAction++] = pActionData->GetIndex();
			break;
		}
	}

	SetAction();
	SetParty();
	SetSocial();
	SetGuild();
}

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½Æ° ï¿½ï¿½ï¿½ï¿½
void CUICharacterInfo::NotifyStatPoint()
{

	BOOL bEnable = FALSE;

	// Update states of buttons
	if( _pNetwork->MyCharacterInfo.StatPoint > 0 )
		bEnable = TRUE;		

	for ( int i = 0; i < eBTN_MAX; i++)
	{
		if (m_pBtnStatus[i] != NULL)
			m_pBtnStatus[i]->SetEnable(bEnable);
	}

	// Update strings of stats
	CTString strString = CTString("");
	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPoint );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT] != NULL)
		m_ptxtStat[eCHARINFO_STAT_STATPOINT]->SetText(strString);

	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.StatPointAddition );

	if (m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION] != NULL) {
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->SetText(strString);
		m_ptxtStat[eCHARINFO_STAT_STATPOINT_ADDITION]->setFontColor(GetStrColor(0));
	}
}

// ï¿½Å±ï¿½ UI ï¿½ï¿½ï¿½ï¿½
void CUICharacterInfo::initialize()
{
	// ï¿½ï¿½ï¿½ï¿½ UI ï¿½ï¿½ï¿½ï¿½
	m_pstrTitle = (CUIText*)findUI("str_title");
	m_pMoveTitle = (CUIText*)findUI("str_movetitle");

	m_pBtnClose = (CUIButton*)findUI("btn_close");

	if (m_pBtnClose != NULL)
	{
		CmdCharInfoClose* pCmd = new CmdCharInfoClose;
		pCmd->setData(this);
		m_pBtnClose->SetCommandUp(pCmd);
	}

	m_pMainTab = (CUITab*)findUI( "tab_main" );

	if (m_pMainTab != NULL)
	{
		CmdCharInfoChangeTab* pCmd = new CmdCharInfoChangeTab;
		pCmd->setData(this);
		m_pMainTab->SetCommandChange(pCmd);
	}

	CTString strTooltip = CTString("");

	m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_STATUS] = (CUICheckButton*)findUI( "check_1" );

	if (m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_STATUS] != NULL)
	{
		strTooltip.PrintF("%s", _S(69, "Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½") );
		m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_STATUS]->setTooltip(strTooltip);
	}

	m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SKILL] = (CUICheckButton*)findUI( "check_2" );

	if (m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SKILL] != NULL)
	{
		strTooltip.PrintF("%s", _S(6077, "Æ¯ï¿½ï¿½ ï¿½ï¿½Å³") );
		m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SKILL]->setTooltip(strTooltip);
	}

	m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_ACTION_SOCIAL] = (CUICheckButton*)findUI( "check_3" );

	if (m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_ACTION_SOCIAL] != NULL)
	{
		strTooltip.PrintF( "%s,%s",_S(94, "ï¿½×¼ï¿½") ,_S(96, "ï¿½Ò¼ï¿½") );
		m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_ACTION_SOCIAL]->setTooltip(strTooltip);
	}

	m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_GUILD_PARTY] = (CUICheckButton*)findUI( "check_4" );

	if (m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_GUILD_PARTY] != NULL)
	{
		strTooltip.PrintF("%s,%s",_S(97, "ï¿½ï¿½Æ¼") ,_S(98, "ï¿½ï¿½ï¿½") );
		m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_GUILD_PARTY]->setTooltip(strTooltip);
	}

	m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SYNDICATE] = (CUICheckButton*)findUI( "check_5" );

	if (m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SYNDICATE] != NULL)
	{
		strTooltip.PrintF("%s", _S(6130, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½"));
		m_pBtnMainCheckBtn[PAGE_CHARINFO_NEW_SYNDICATE]->setTooltip(strTooltip);
	}

	CTString strfindName = CTString("");
	for (int i = 0; i < PAGE_CHARINFO_NEW_MAX; i++)
	{
		strfindName.PrintF("img_check%d", i+1);
		m_pImgCheck[i] = (CUIImage*)findUI(strfindName);
		strfindName.PrintF("img_uncheck%d", i+1);
		m_pImgUnCheck[i] = (CUIImage*)findUI(strfindName);
	}

	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 1ï¿½ï¿½ Ä³ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	initCahrInfo();

	
	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 2ï¿½ï¿½ ï¿½ï¿½Å³ ï¿½ï¿½ï¿½ï¿½ (ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½, Æ¯ï¿½ï¿½, ï¿½ï¿½Ç¥)
	initSecondTab();

	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 3ï¿½ï¿½ ï¿½×¼ï¿½, ï¿½Ò¼ï¿½
	initThirdTab();

	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ 4ï¿½ï¿½ ï¿½ï¿½Æ¼ ï¿½ï¿½ï¿½
	initCommunity();

	initSyndicateInfo();

	m_pImgSelect = UISUPPORT()->clone_Image(eIMG_TYPE_SELECT);
	addChild((CUIBase*)m_pImgSelect);
}

void CUICharacterInfo::SendResetStatPoint()
{
	int	iStrength		= _pNetwork->MyCharacterInfo.str - _pNetwork->MyCharacterInfo.opt_str;
	int	iDexterity		= _pNetwork->MyCharacterInfo.dex - _pNetwork->MyCharacterInfo.opt_dex;
	int	iIntelligence	= _pNetwork->MyCharacterInfo.intel - _pNetwork->MyCharacterInfo.opt_intel;
	int	iConstitution	= _pNetwork->MyCharacterInfo.con - _pNetwork->MyCharacterInfo.opt_con;
	_pNetwork->StatReset(iStrength, iDexterity, iIntelligence, iConstitution);
}

void CUICharacterInfo::initCahrInfo()
{
	int i = 0;
	CTString strBaseName[eCHARINFO_BASE_MAX] = 	{ "str_name", "str_class", "str_level", "str_guild", "str_guildpos",
		"str_sub", "str_sub2", "str_sp", "str_frame", "str_exp" };

	for (i = 0; i < eCHARINFO_BASE_MAX; i++)
	{
		m_ptxtBase[i] = (CUIText*)findUI(strBaseName[i]);
	}

	CTString strBtnName[eBTN_MAX] = { "btn_str", "btn_dex", "btn_int", "btn_con", "btn_str10", "btn_dex10", "btn_int10", "btn_con10" };

	for (i = 0; i < eBTN_MAX; i++)
	{
		m_pBtnStatus[i] = (CUIButton*)findUI(strBtnName[i]);

		if (m_pBtnStatus[i] != NULL) 
		{
			CmdCharInfoStatpoint* pCmd = new CmdCharInfoStatpoint;
			pCmd->setData(this, (MSG_STATPOINT_USE_TYPE)i);
			m_pBtnStatus[i]->SetCommand(pCmd);

			CmdCharInfoStatpoint* pCmd1 = new CmdCharInfoStatpoint;
			pCmd1->setData(this, (MSG_STATPOINT_USE_TYPE)i);
			m_pBtnStatus[i]->SetCommandDBL(pCmd1);

			m_pBtnStatus[i]->SetEnable(FALSE);
		}
	}

	m_pBtnResetStats = (CUIButton*)findUI("btn_reset_stats");
	if (m_pBtnResetStats != NULL) {
		CmdCharInfoStatpointReset * pCmdResetStats = new CmdCharInfoStatpointReset();
		pCmdResetStats->setData(this);
		m_pBtnResetStats->SetCommand(pCmdResetStats);
	}

	// PKï¿½ï¿½ï¿½ï¿½, ï¿½Ó¼ï¿½ï¿½ï¿½ï¿½ï¿½
	m_pstrPk = (CUIText*)findUI("str_pk");
	m_pstrPkPoint = (CUIText*)findUI("str_pkpoint");
	m_pstrPkPointAcc = (CUIText*)findUI("str_pkpointAcc");
	//m_pImgArrAtt = (CUIImageArray*)findUI("imgarray_att");
	//m_pImgArrDef = (CUIImageArray*)findUI("imgarray_def");
	//m_pstrAttlv = (CUIText*)findUI("str_attlevel");
//	m_pstrDeflv = (CUIText*)findUI("str_deflevel");
	m_opResistStone = (CUIText*)findUI("str_opResistStone");
	m_opResistSturn = (CUIText*)findUI("str_opResistSturn");
	m_opResistSilent = (CUIText*)findUI("str_opResistSilent");
	m_absorbPVPDamageRate = (CUIText*)findUI("str_opabsorbPVPDamageRate");
	m_opDecreaseSkillMP = (CUIText*)findUI("str_opDecreaseSkillMP");
	m_skillSpeed = (CUIText*)findUI("str_SkillSpeed");
	m_PVP_Winer = (CUIText*)findUI("str_PVP_Winer");
	m_PVP_Lose = (CUIText*)findUI("str_PVP_Lose");
	m_pImgArrWiner = (CUIImageArray*)findUI("imgarray_winer");
	m_pImgArrLose = (CUIImageArray*)findUI("imgarray_lose");
	m_pPbHonorPoints = (CUIProgressBar*)findUI("pbHonor");
	//just display on progress bar the text one isn't necessary.
	m_honor = (CUIText*)findUI("strHonor");

	CTString strStatName[eCHARINFO_STAT_MAX] = 	{ "str_str", "str_dex", "str_int", "str_con", "str_statpoint", 
		"str_statpoint_addition", "str_hp", "str_mp", "str_attack", "str_defense", "str_hitrate",
		"str_dodgerate", "str_critical"	, "str_movespeed", "str_magicattack", "str_magicdefense",
		"str_magichitrate", "str_magicdodgerate", "str_deadly", "str_attackspeed"};

	for (i = 0; i < eCHARINFO_STAT_MAX; i++)
	{
		m_ptxtStat[i] = (CUIText*)findUI(strStatName[i]);
	}
}

// ï¿½ï¿½Å³ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½, Æ¯ï¿½ï¿½, ï¿½ï¿½Ç¥
void CUICharacterInfo::initSecondTab()
{
	CTString strName[eTAB_SKILL_MAX] = {"arr_item", "arr_sskill", "arr_seal"};
	CTString strScrollName[eTAB_SKILL_MAX] = {"scroll_item", "scroll_sskill", "scroll_seal"};

	m_pTabSkill = (CUITab*)findUI("tab_2_sub");

	if (m_pTabSkill != NULL)
	{
		CmdCharSkillChangeTab* pCmd = new CmdCharSkillChangeTab;
		pCmd->setData(this);
		m_pTabSkill->SetCommandChange(pCmd);
	}	

	for (int i = 0; i < eTAB_SKILL_MAX; i++)
	{
		m_pArrSkill[i] = (CUIArray*)findUI(strName[i]);

		m_pScrollSkill[i] = (CUIScrollBar*)findUI(strScrollName[i]);

		if (m_pArrSkill[i] != NULL)
		{
			m_pArrSkill[i]->SetShowRowCount(0);
			m_pArrSkill[i]->UpdateItem();
		}
	}
}

void CUICharacterInfo::initThirdTab()
{
	CTString strName[eTAB_ACTION_MAX] = {"arr_action", "arr_social"};
	CTString strScrollName[eTAB_ACTION_MAX] = {"scroll_action", "scroll_social"};

	m_pTabAction = (CUITab*)findUI("tab_3_sub");

	if (m_pTabAction != NULL)
	{
		CmdCharActionChangeTab* pCmd = new CmdCharActionChangeTab;
		pCmd->setData(this);
		m_pTabAction->SetCommandChange(pCmd);
	}	

	for (int i = 0; i < eTAB_ACTION_MAX; i++)
	{
		m_pArrAction[i] = (CUIArray*)findUI(strName[i]);

		m_pScrollAction[i] = (CUIScrollBar*)findUI(strScrollName[i]);

		if (m_pArrAction[i] != NULL)
		{
			m_pArrAction[i]->SetShowRowCount(0);
			m_pArrAction[i]->UpdateItem();
		}
	}
}

void CUICharacterInfo::initCommunity()
{
	CTString strName[eTAB_COMMUNITY_MAX] = {"arr_party", "arr_guild"};
	CTString strScrollName[eTAB_COMMUNITY_MAX] = {"scroll_party", "scroll_guild"};

	m_pTabCommunity = (CUITab*)findUI("tab_4_sub");

	if (m_pTabCommunity != NULL)
	{
		CmdCharCommunityChangeTab* pCmd = new CmdCharCommunityChangeTab;
		pCmd->setData(this);
		m_pTabCommunity->SetCommandChange(pCmd);
	}	

	for (int i = 0; i < eTAB_COMMUNITY_MAX; i++)
	{
		m_pArrCommunity[i] = (CUIArray*)findUI(strName[i]);

		m_pScrollCommunity[i] = (CUIScrollBar*)findUI(strScrollName[i]);

		if (m_pArrCommunity[i] != NULL)
		{
			m_pArrCommunity[i]->SetShowRowCount(0);
			m_pArrCommunity[i]->UpdateItem();
		}
	}
}


void CUICharacterInfo::initSyndicateInfo()
{
	m_pProgressBar[eTAB_SYNDICATE_KAY] = (CUIProgressBar*)findUI("pb_kay");
	m_pProgressBar[eTAB_SYNDICATE_DEAL] = (CUIProgressBar*)findUI("pb_deal");

	for (int i = 0; i < eTAB_SYNDICATE_MAX; i++)
	{
		if (m_pProgressBar[i] != NULL)
			m_pProgressBar[i]->OffsetProgressPos(0);
	}

	m_pBtnSyndicateInfo = (CUIButton*)findUI("btn_rvrposinfo");

	if (m_pBtnSyndicateInfo != NULL)
	{
		CmdCharMySyndiCateInfo* pCmd = new CmdCharMySyndiCateInfo;
		m_pBtnSyndicateInfo->SetCommandUp(pCmd);
		m_pBtnSyndicateInfo->SetEnable(FALSE);
	}

	m_pImgMark[eTAB_SYNDICATE_KAY] = (CUIImage*)findUI("img_mark_kay");
	m_pImgMark[eTAB_SYNDICATE_DEAL] = (CUIImage*)findUI("img_mark_deal");
	m_pImgNoJoin = (CUIImage*)findUI("img_nojoin");
	m_pTextMyPos = (CUIText*)findUI("str_myrvrpos");
	m_pPbSyndicateExp = (CUIProgressBar*)findUI("pb_myrvrexp");
	m_pTbHistory = (CUITextBox*)findUI("tb_myhistory");
	m_pScrollSyndiHistory = (CUIScrollBar*)findUI("scroll_history");

	if (m_pScrollSyndiHistory != NULL)
		m_pScrollSyndiHistory->SetItemsPerPage(DEF_SHOW_MAX);
}

void CUICharacterInfo::ChangeTab()
{
	if (m_pMainTab == NULL)
		return;

	int nSel = m_pMainTab->getCurSelTab();

	SetCurrentPageNewCharacterInfo(nSel);

	if (m_pstrTitle != NULL)
		m_pstrTitle->SetText(m_strTitleName);
}

void CUICharacterInfo::ChangeTabSkill()
{
	if (m_pTabSkill == NULL)
		return;

	int nSel = m_pTabSkill->getCurSelTab();

	SetCurrentSkillInfo(m_ucipCurrentPage, nSel);
}

void CUICharacterInfo::ChangeTabAction()
{
	if (m_pTabAction == NULL)
		return;

	int nSel = m_pTabAction->getCurSelTab();

	SetCurrentSkillInfo(m_ucipCurrentPage, nSel);
}

void CUICharacterInfo::ChangeTabCommunity()
{
	if (m_pTabCommunity == NULL)
		return;

	int nSel = m_pTabCommunity->getCurSelTab();

	SetCurrentSkillInfo(m_ucipCurrentPage, nSel);
}

void CUICharacterInfo::OpenUI(int nTabNum)
{
	SetVisible(TRUE);
	Hide(FALSE);

	SetPos( g_iXPosInCharInfo, g_iYPosInCharInfo );

	CUIManager* pUIManager = CUIManager::getSingleton();
	ChangePage(nTabNum);
	pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
}

void CUICharacterInfo::CloseUI()
{
	SetVisible(FALSE);
	Hide(TRUE);

	g_iXPosInCharInfo = GetPosX();
	g_iYPosInCharInfo = GetPosY();

	CUITooltipMgr::getSingleton()->clearTooltip();

	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->RearrangeOrder( UI_CHARACTERINFO, FALSE );
}

// ----------------------------------------------------------------------------
// Name : ToggleVisible()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ToggleVisible()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( IsVisible() )
	{
		CloseUI();
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_STATUS);	
	}
}

// ----------------------------------------------------------------------------
// Name : ToggleVisibleStatus()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ToggleVisibleStatus()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if ( IsVisible() )
	{
		if( m_ucipCurrentPage == PAGE_CHARINFO_NEW_STATUS )
		{
			CloseUI();
		}
		else
		{
			ChangePage(PAGE_CHARINFO_NEW_STATUS);
			pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
		}
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_STATUS);
	}	
}

// ----------------------------------------------------------------------------
// Name : ToggleVisibleAction()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ToggleVisibleAction()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if ( IsVisible() )
	{
		if( m_ucipCurrentPage == PAGE_CHARINFO_NEW_ACTION_SOCIAL && m_nSkillActionUpperTab[1] == 0 )
		{
			CloseUI();
		}
		else
		{
			ChangePage(PAGE_CHARINFO_NEW_ACTION_SOCIAL);
			m_nSkillActionUpperTab[1] = 0;
			ChangeTabPage(m_nSkillActionUpperTab[1]);
			pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
		}
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_ACTION_SOCIAL);
		ChangeTabPage(m_nSkillActionUpperTab[1]);
	}	
}

// ----------------------------------------------------------------------------
// Name : ToggleVisibleSocial()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ToggleVisibleSocial()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if ( IsVisible() )
	{
		if( m_ucipCurrentPage == PAGE_CHARINFO_NEW_ACTION_SOCIAL && m_nSkillActionUpperTab[1] == 1 )
		{
			CloseUI();
		}
		else
		{
			ChangePage(PAGE_CHARINFO_NEW_ACTION_SOCIAL);
			m_nSkillActionUpperTab[1] = 1;
			ChangeTabPage(m_nSkillActionUpperTab[1]);
			pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
		}
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_ACTION_SOCIAL);
		ChangeTabPage(m_nSkillActionUpperTab[1]);
	}	
}

// ----------------------------------------------------------------------------
// Name : ToggleVisibleGroup()
// Desc :
// ----------------------------------------------------------------------------
void CUICharacterInfo::ToggleVisibleGroup()
{

	CUIManager* pUIManager = CUIManager::getSingleton();

	if ( IsVisible() )
	{
		if( m_ucipCurrentPage == PAGE_CHARINFO_NEW_GUILD_PARTY && m_nSkillActionUpperTab[2] == 0)
		{
			CloseUI();
		}
		else
		{
			ChangePage(PAGE_CHARINFO_NEW_GUILD_PARTY);
			m_nSkillActionUpperTab[2] = 0;
			ChangeTabPage(m_nSkillActionUpperTab[2]);
			pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
		}
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_GUILD_PARTY);
		ChangeTabPage(m_nSkillActionUpperTab[2]);
	}	
}


void CUICharacterInfo::ToggleVisibleSyndicate()
{

	CUIManager* pUIManager = CUIManager::getSingleton();

	if ( IsVisible() )
	{
		if( m_ucipCurrentPage == PAGE_CHARINFO_NEW_SYNDICATE )
		{
			CloseUI();
		}
		else
		{
			ChangePage(PAGE_CHARINFO_NEW_SYNDICATE);
			pUIManager->RearrangeOrder( UI_CHARACTERINFO, TRUE );
		}
	}
	else
	{
		OpenUI(PAGE_CHARINFO_NEW_SYNDICATE);
	}	
}


WMSG_RESULT CUICharacterInfo::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pMoveTitle && m_pMoveTitle->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager::getSingleton()->RearrangeOrder(UI_CHARACTERINFO, TRUE);

	return WMSG_FAIL;
}

WMSG_RESULT CUICharacterInfo::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

WMSG_RESULT CUICharacterInfo::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_nMouseX = x;
	m_nMouseY = y;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager::getSingleton()->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

void CUICharacterInfo::ChangeCheckImg( int nTabNum )
{
	for (int i = 0; i < PAGE_CHARINFO_NEW_MAX; i++)
	{
		if (m_pImgUnCheck[i] != NULL)
			m_pImgUnCheck[i]->Hide(FALSE);

		if (m_pImgCheck[i] != NULL)
			m_pImgCheck[i]->Hide(TRUE);
	}

	if (m_pImgUnCheck[nTabNum] != NULL)
		m_pImgUnCheck[nTabNum]->Hide(TRUE);

	if (m_pImgCheck[nTabNum] != NULL)
		m_pImgCheck[nTabNum]->Hide(FALSE);
}

void CUICharacterInfo::ChangePage( int nTabNum )
{
	if (m_pMainTab == NULL)
		return;

	int curTabIdx = m_pMainTab->getCurSelTab();

	if (curTabIdx == nTabNum)
		ChangeTab();
	else
		m_pMainTab->OnChangeTab(nTabNum);
}

void CUICharacterInfo::ChangeTabPage( int nSubNum )
{
	switch (m_ucipCurrentPage)
	{
	case PAGE_CHARINFO_NEW_SKILL:
		{
			if (m_pTabSkill != NULL)
				m_pTabSkill->OnChangeTab(nSubNum);
		}
		break;

	case PAGE_CHARINFO_NEW_ACTION_SOCIAL:
		{
			if (m_pTabAction != NULL)
				m_pTabAction->OnChangeTab(nSubNum);
		}
		break;

	case PAGE_CHARINFO_NEW_GUILD_PARTY:
		{
			if (m_pTabCommunity != NULL)
				m_pTabCommunity->OnChangeTab(nSubNum);
		}
		break;
	}	
}

void CUICharacterInfo::OnUpdate( float fDeltaTime, ULONG ElapsedTime )
{
	if (m_ucipCurrentPage == PAGE_CHARINFO_NEW_STATUS)
	{
		UpdateBaseInfo();
	}
}

void CUICharacterInfo::UpdateBaseInfo()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	CTString strString = CTString("");
	COLOR strColor;
	int added = 0;

	// ï¿½Ì¸ï¿½
	strString.PrintF( "%s", _pNetwork->MyCharacterInfo.name);
	
	if (m_ptxtBase[eCHARINFO_BASE_NAME] != NULL)
		m_ptxtBase[eCHARINFO_BASE_NAME]->SetText(strString);
	
	// Å¬ï¿½ï¿½ï¿½ï¿½
	strString.PrintF( "%s", CJobInfo::getSingleton()->GetName(_pNetwork->MyCharacterInfo.job, _pNetwork->MyCharacterInfo.job2));

	if (m_ptxtBase[eCHARINFO_BASE_CLASS] != NULL)
		m_ptxtBase[eCHARINFO_BASE_CLASS]->SetText(strString);

	// ï¿½ï¿½ï¿½ï¿½
	strString.PrintF( "%d", _pNetwork->MyCharacterInfo.level);

	if (m_ptxtBase[eCHARINFO_BASE_LEVEL] != NULL)
		m_ptxtBase[eCHARINFO_BASE_LEVEL]->SetText(strString);

	// ï¿½ï¿½ï¿½
	if (_pNetwork->MyCharacterInfo.lGuildIndex == -1)
		strString.PrintF( _S( 76, "ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½" ) );
	else
		strString.PrintF( "%s", _pNetwork->MyCharacterInfo.strGuildName);

	if (m_ptxtBase[eCHARINFO_BASE_GUILD] != NULL)
		m_ptxtBase[eCHARINFO_BASE_GUILD]->SetText(strString);
	
	// ï¿½ï¿½ï¿½ï¿½
	if ( _pNetwork->MyCharacterInfo.guildPosName.Length() == 0 )
		strString.PrintF( _S( 4177, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½") );
	else
		strString.PrintF( "%s", _pNetwork->MyCharacterInfo.guildPosName);

	if (m_ptxtBase[eCHARINFO_BASE_GUILDPOS] != NULL)
		m_ptxtBase[eCHARINFO_BASE_GUILDPOS]->SetText(strString);

	// ï¿½ï¿½ï¿½ï¿½
	CTString strSubJobName;
#ifdef ADD_SUBJOB
	//strString.PrintF( _S( 8374, "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½" ) );
		
	if(_pNetwork->MyCharacterInfo.reborn > 0 )
	{
		
		strSubJobName.PrintF("%d", _pNetwork->MyCharacterInfo.reborn); //pwesty reborn level show
	}

	strColor = 0x3fb9f2FF;
#else
	strString = _S( 77, "ï¿½ï¿½ï¿½ï¿½" ) ;
	strSubJobName = _S( 78, "ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½" );
	strColor = 0xABC98AFF;
#endif
	//if (m_ptxtBase[eCHARINFO_BASE_SUB] != NULL)
		//m_ptxtBase[eCHARINFO_BASE_SUB]->SetText(strString);

	if (m_ptxtBase[eCHARINFO_BASE_SUB2] != NULL)
	{
		m_ptxtBase[eCHARINFO_BASE_SUB2]->SetText(strSubJobName);
		m_ptxtBase[eCHARINFO_BASE_SUB2]->setFontColor(strColor);
	}

	// hp
	CTString strCur, strMax;
	strCur = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.hp);
	strMax = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.maxHP);

	strString.PrintF("%s/%s", strCur, strMax);

	if (m_ptxtStat[eCHARINFO_STAT_HP] != NULL)
		m_ptxtStat[eCHARINFO_STAT_HP]->SetText(strString);
	
	// mp
	strCur = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.mp);
	strMax = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.maxMP);

	strString.PrintF("%s/%s", strCur, strMax);
	
	if (m_ptxtStat[eCHARINFO_STAT_MP] != NULL)
		m_ptxtStat[eCHARINFO_STAT_MP]->SetText(strString);


	CTString pkname;
	int		 pkcolor = 0;
	int		 nTooltipIndex = -1;
#ifdef NEW_CHAO_SYS
	if(_pNetwork->MyCharacterInfo.pkpenalty > 0)
	{
		pkname = _S(4054,"ï¿½ï¿½ï¿½ï¿½");
		pkcolor = 0x0070C0FF;
		nTooltipIndex = 7072;
	}
	else if(_pNetwork->MyCharacterInfo.pkpenalty < 0)
	{
		pkname = _S(5582,"Ä«ï¿½ï¿½");
		pkcolor = 0xFF0000FF;
		nTooltipIndex = 7073;
	}
	else
	{
		pkname = _S(92,"ï¿½Ï¹ï¿½");
		pkcolor = 0xFFFFFFFF;
	}
	strColor = GetStrColor(0);
#else
	pkname.PrintF("%s" , _ClassName[_pNetwork->MyCharacterInfo.pktitle + 5]);
	pkcolor = 0xFFFFFFFF;
	
	strColor = GetStrColor(_pNetwork->MyCharacterInfo.pkpenalty);
#endif
	if (m_pstrPk != NULL)
	{
		m_pstrPk->SetText(pkname);
		m_pstrPk->setFontColor(pkcolor);

		if (nTooltipIndex > 0)
			m_pstrPk->setTooltip(_S(nTooltipIndex, "(Ä«ï¿½ï¿½orï¿½ï¿½ï¿½) ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ï¿½ PVPï¿½ï¿½ ï¿½Ú½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ý·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ë´Ï´ï¿½."));
		else
			m_pstrPk->setTooltip("");
	}

	strCur = pUIManager->IntegerToCommaString(_pNetwork->MyCharacterInfo.pkpenalty);
	strString.PrintF( "%s", strCur );

	if (m_pstrPkPoint != NULL)
	{
		m_pstrPkPoint->SetText(strString);
		m_pstrPkPoint->setFontColor(strColor);
	}
}

void CUICharacterInfo::SetChildVisible( CUIArrayItem* pItem, bool bVisible )
{
	if( pItem == NULL )
		return;

	int i, max = pItem->getChildCount();

	for( i = 0; i < max; ++i )
	{
		if ( CUIBase* pBase = (CUIBase*)pItem->getChildAt(i) )
			pBase->Hide(bVisible ? FALSE : TRUE);
	}
}

void CUICharacterInfo::SetSSkill()
{
	if (m_pArrSkill[eTAB_SKILL_SSKILL] == NULL)
		return;
	
	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = SKILL_SPECIAL_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrSkill[eTAB_SKILL_SSKILL]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrSkill[eTAB_SKILL_SSKILL]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;
	
	for( i = 0; i < max; ++i )
	{
		if (m_nIdxSpecialSkill[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrSkill[eTAB_SKILL_SSKILL]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrSkill[eTAB_SKILL_SSKILL]->GetArrayChildCount();
		}

		pItem = m_pArrSkill[eTAB_SKILL_SSKILL]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		pIcon = (CUIIcon*)pItem->findUI("icon_sskill");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setSkill(m_nIdxSpecialSkill[i], true);
			pIcon->setCooltime(MY_INFO()->GetSkillDelay(m_nIdxSpecialSkill[i], true));
			
			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

		}

		CSpecialSkill* pSSkill = CSpecialSkill::getData( m_nIdxSpecialSkill[i] );
		SBYTE	sbLevel = MY_INFO()->GetSkillLevel(m_nIdxSpecialSkill[i], true);

		if (pSSkill == NULL)
			continue;

		pText = (CUIText*)pItem->findUI("str_sskill_name");

		if( pText != NULL )
		{
			strString.PrintF( "%s", pSSkill->GetName() );
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}

		pText = (CUIText*)pItem->findUI("str_sskill_info");

		if( pText != NULL )
		{
			strString.PrintF( "%s %2d   %s %2d",_S( 4414, "LV" ), sbLevel, _S( 4415, "SP" ), pSSkill->GetLearnSP( sbLevel - 1 ) );

			pText->SetText(strString);
			strColor = 0xBDA99FFF;
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrSkill[eTAB_SKILL_SSKILL]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrSkill[eTAB_SKILL_SSKILL], cnt);

	if (m_pScrollSkill[eTAB_SKILL_SSKILL] != NULL)
		m_pScrollSkill[eTAB_SKILL_SSKILL]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrSkill[eTAB_SKILL_SSKILL]->UpdateItem();
}

void CUICharacterInfo::SetItemSkill()
{
	if (m_pArrSkill[eTAB_SKILL_ITEM] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = SKILL_SPECIAL_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrSkill[eTAB_SKILL_ITEM]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrSkill[eTAB_SKILL_ITEM]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxItemSpecialSkill[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrSkill[eTAB_SKILL_ITEM]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrSkill[eTAB_SKILL_ITEM]->GetArrayChildCount();
		}

		pItem = m_pArrSkill[eTAB_SKILL_ITEM]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		int nIndex = m_nIdxItemSpecialSkill[i];
		CSkill&	rSkill = _pNetwork->GetSkillData(nIndex);
		bool bPassive = false;

		if( rSkill.GetType() == CSkill::ST_PASSIVE )
			bPassive = true;

		pIcon = (CUIIcon*)pItem->findUI("icon_item");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setSkill(m_nIdxItemSpecialSkill[i]);
			pIcon->SetWhichUI(UI_CHARACTERINFO);
			pIcon->setCooltime(MY_INFO()->GetSkillDelay(nIndex));
			
			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

			if (bPassive == true)
			{
				pIcon->SetCommandUp(NULL);
				pIcon->SetCommandDrag(NULL);
			}
			else
			{
				CmdCharSkillFire* pCmdFire = new CmdCharSkillFire;
				pCmdFire->setData(nIndex);
				pIcon->SetCommandUp(pCmdFire);

				CmdDragIcon* pCmd = new CmdDragIcon;
				pCmd->setData(pIcon);
				pIcon->SetCommandDrag(pCmd);
			}
		}

		SBYTE	sbLevel = MY_INFO()->GetSkillLevel(nIndex);

		pText = (CUIText*)pItem->findUI("str_item_name");

		if( pText != NULL )
		{
			strString.PrintF( "%s", rSkill.GetName() );
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);		
		}

		pText = (CUIText*)pItem->findUI("str_item_info");

		if( pText != NULL )
		{
			strString.PrintF( "%s %2d   %s %2d",_S( 4414, "LV" ), sbLevel, _S( 4415, "SP" ), rSkill.GetLearnSP( sbLevel - 1 ) );

			strColor = 0xBDA99FFF;
			pText->SetText(strString);
			pText->setFontColor(strColor);	
		}

		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrSkill[eTAB_SKILL_ITEM]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrSkill[eTAB_SKILL_ITEM], cnt);

	if (m_pScrollSkill[eTAB_SKILL_ITEM] != NULL)
		m_pScrollSkill[eTAB_SKILL_ITEM]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrSkill[eTAB_SKILL_ITEM]->UpdateItem();
}

void CUICharacterInfo::SetSeal()
{
	if (m_pArrSkill[eTAB_SKILL_SEAL] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = SKILL_SPECIAL_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrSkill[eTAB_SKILL_SEAL]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrSkill[eTAB_SKILL_SEAL]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxVoucherSkill[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrSkill[eTAB_SKILL_SEAL]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrSkill[eTAB_SKILL_SEAL]->GetArrayChildCount();
		}

		pItem = m_pArrSkill[eTAB_SKILL_SEAL]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		pIcon = (CUIIcon*)pItem->findUI("icon_seal");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setData(UBET_SKILL, m_nIdxVoucherSkill[i]);
			pIcon->SetWhichUI(UI_CHARACTERINFO);

			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);
		}

		CSkill&	rSkill = _pNetwork->GetSkillData(m_nIdxVoucherSkill[i]);
		SBYTE	sbLevel = MY_INFO()->GetSkillLevel(rSkill.GetIndex());

		pText = (CUIText*)pItem->findUI("str_seal_name");

		if( pText != NULL )
		{
			strString.PrintF( "%s", rSkill.GetName() );
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);			
		}

		pText = (CUIText*)pItem->findUI("str_seal_info");

		if( pText != NULL )
		{
			CTString strExp;
			strExp.PrintF("%I64d", MY_INFO()->GetSkillExp(rSkill.GetIndex()));
			UIMGR()->InsertCommaToString(strExp);

			strString.PrintF(_S(4491, "ï¿½ï¿½ï¿½Ãµï¿½ : %s"), strExp);
			
			strColor = 0xBDA99FFF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrSkill[eTAB_SKILL_SEAL]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrSkill[eTAB_SKILL_SEAL], cnt);

	if (m_pScrollSkill[eTAB_SKILL_SEAL] != NULL)
		m_pScrollSkill[eTAB_SKILL_SEAL]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrSkill[eTAB_SKILL_SEAL]->UpdateItem();
}

void CUICharacterInfo::SetAction()
{
	if (m_pArrAction[eTAB_ACTION_ACTION] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = ACTION_NORAML_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrAction[eTAB_ACTION_ACTION]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrAction[eTAB_ACTION_ACTION]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxNormalAction[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrAction[eTAB_ACTION_ACTION]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrAction[eTAB_ACTION_ACTION]->GetArrayChildCount();
		}

		pItem = m_pArrAction[eTAB_ACTION_ACTION]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		int nIndex = m_nIdxNormalAction[i];

		pIcon = (CUIIcon*)pItem->findUI("icon_action");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setData(UBET_ACTION, m_nIdxNormalAction[i]);
			pIcon->SetWhichUI(UI_CHARACTERINFO);
			
			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

			{
				CmdCharActionFire* pCmd = new CmdCharActionFire;
				pCmd->setData(nIndex);
				pIcon->SetCommandUp(pCmd);
			}
			
			{
				CmdDragIcon* pCmd = new CmdDragIcon;
				pCmd->setData(pIcon);
				pIcon->SetCommandDrag(pCmd);
			}
		}

		CAction* pSelAction = CAction::getData(nIndex);
		
		pText = (CUIText*)pItem->findUI("str_action_name");

		if( pText != NULL )
		{
			if (pSelAction != NULL)
				strString.PrintF("%s", pSelAction->GetName());
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrAction[eTAB_ACTION_ACTION]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrAction[eTAB_ACTION_ACTION], cnt);

	if (m_pScrollAction[eTAB_ACTION_ACTION] != NULL)
	{
		m_pScrollAction[eTAB_ACTION_ACTION]->SetItemsPerPage(DEF_MAX_SHOW_ROW);
		m_pScrollAction[eTAB_ACTION_ACTION]->SetScrollPos(0);
	}

	m_pArrAction[eTAB_ACTION_ACTION]->UpdateItem();
}

void CUICharacterInfo::SetSocial()
{
	if (m_pArrAction[eTAB_ACTION_SOCIAL] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = ACTION_SOCIAL_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrAction[eTAB_ACTION_SOCIAL]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrAction[eTAB_ACTION_SOCIAL]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxSocialAction[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrAction[eTAB_ACTION_SOCIAL]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrAction[eTAB_ACTION_SOCIAL]->GetArrayChildCount();
		}

		pItem = m_pArrAction[eTAB_ACTION_SOCIAL]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		int nIndex = m_nIdxSocialAction[i];

		pIcon = (CUIIcon*)pItem->findUI("icon_social");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();			
			pIcon->setData(UBET_ACTION, nIndex);
			pIcon->SetWhichUI(UI_CHARACTERINFO);

			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

			{
				CmdCharActionFire* pCmd = new CmdCharActionFire;
				pCmd->setData(nIndex);
				pIcon->SetCommandUp(pCmd);
			}

			{
				CmdDragIcon* pCmd = new CmdDragIcon;			
				pCmd->setData(pIcon);
				pIcon->SetCommandDrag(pCmd);
			}
		}

		CAction* pSelAction = CAction::getData(nIndex);

		pText = (CUIText*)pItem->findUI("str_social_name");

		if( pText != NULL )
		{
			if (pSelAction != NULL)
				strString.PrintF("%s", pSelAction->GetName());
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrAction[eTAB_ACTION_SOCIAL]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrAction[eTAB_ACTION_SOCIAL], cnt);

	if (m_pScrollAction[eTAB_ACTION_SOCIAL] != NULL)
		m_pScrollAction[eTAB_ACTION_SOCIAL]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrAction[eTAB_ACTION_SOCIAL]->UpdateItem();
}

void CUICharacterInfo::SetGuild()
{
	if (m_pArrCommunity[eTAB_COMMUNITY_GUILD] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = ACTION_GUILD_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrCommunity[eTAB_COMMUNITY_GUILD]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrCommunity[eTAB_COMMUNITY_GUILD]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxGuildAction[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrCommunity[eTAB_COMMUNITY_GUILD]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrCommunity[eTAB_COMMUNITY_GUILD]->GetArrayChildCount();
		}

		pItem = m_pArrCommunity[eTAB_COMMUNITY_GUILD]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		int nIndex = m_nIdxGuildAction[i];

		pIcon = (CUIIcon*)pItem->findUI("icon_guild");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setData(UBET_ACTION, nIndex);
			pIcon->SetWhichUI(UI_CHARACTERINFO);

			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

			{
				CmdCharActionFire* pCmd = new CmdCharActionFire;
				pCmd->setData(nIndex);
				pIcon->SetCommandUp(pCmd);
			}

			{
				CmdDragIcon* pCmd = new CmdDragIcon;
				pCmd->setData(pIcon);
				pIcon->SetCommandDrag(pCmd);
			}
		}

		CAction* pSelAction = CAction::getData(nIndex);

		pText = (CUIText*)pItem->findUI("str_guild_name");

		if( pText != NULL )
		{
			if (pSelAction != NULL)
				strString.PrintF("%s", pSelAction->GetName());
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrCommunity[eTAB_COMMUNITY_GUILD]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrCommunity[eTAB_COMMUNITY_GUILD], cnt);

	if (m_pScrollCommunity[eTAB_COMMUNITY_GUILD] != NULL)
		m_pScrollCommunity[eTAB_COMMUNITY_GUILD]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrCommunity[eTAB_COMMUNITY_GUILD]->UpdateItem();
}

void CUICharacterInfo::SetParty()
{
	if (m_pArrCommunity[eTAB_COMMUNITY_PARTY] == NULL)
		return;

	CUIArrayItem* pTmpItem;
	CUIArrayItem* pItem;
	CUIIcon* pIcon;
	CUIText* pText;
	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = ACTION_PARTY_SLOT_ROW_TOTAL;
	int i;

	int Skillcount = 0;
	int cnt = m_pArrCommunity[eTAB_COMMUNITY_PARTY]->GetArrayChildCount();

	pTmpItem = (CUIArrayItem*)m_pArrCommunity[eTAB_COMMUNITY_PARTY]->GetArrayItemTemplate();

	if (pTmpItem == NULL)
		return;

	for( i = 0; i < max; ++i )
	{
		if (m_nIdxPartyAction[i] < 0)
			continue;

		if (Skillcount >= cnt)
		{
			m_pArrCommunity[eTAB_COMMUNITY_PARTY]->AddArrayItem((CUIArrayItem*)pTmpItem->Clone());
			cnt = m_pArrCommunity[eTAB_COMMUNITY_PARTY]->GetArrayChildCount();
		}

		pItem = m_pArrCommunity[eTAB_COMMUNITY_PARTY]->GetArrayItem(Skillcount);

		if( pItem == NULL )
			continue;

		CmdCharTooltipClear* pCmd = new CmdCharTooltipClear;
		pItem->SetCommandLeave(pCmd);

		int nIndex = m_nIdxPartyAction[i];
		pIcon = (CUIIcon*)pItem->findUI("icon_party");
		if( pIcon != NULL )
		{
			pIcon->clearIconData();
			pIcon->setData(UBET_ACTION, nIndex);
			pIcon->SetWhichUI(UI_CHARACTERINFO);
			
			CmdCharSelectImg* pCmdImg = new CmdCharSelectImg;
			pCmdImg->setData(this, pIcon);
			pIcon->SetCommand(pCmdImg);

			{
				CmdCharActionFire* pCmd = new CmdCharActionFire;
				pCmd->setData(nIndex);
				pIcon->SetCommandUp(pCmd);
			}

			{
				CmdDragIcon* pCmd = new CmdDragIcon;
				pCmd->setData(pIcon);
				pIcon->SetCommandDrag(pCmd);
			}
		}

		CAction* pSelAction = CAction::getData(nIndex);

		pText = (CUIText*)pItem->findUI("str_party_name");

		if( pText != NULL )
		{
			if (pSelAction != NULL)
				strString.PrintF("%s", pSelAction->GetName());
			strColor = 0xFFC672FF;
			pText->SetText(strString);
			pText->setFontColor(strColor);
		}
		SetChildVisible(pItem, true);
		Skillcount++;
	}

	if (Skillcount < cnt)
	{
		for (i = Skillcount; i < cnt; i++)
		{
			pItem = m_pArrCommunity[eTAB_COMMUNITY_PARTY]->GetArrayItem(i);

			if( pItem == NULL )
				continue;

			SetChildVisible(pItem, false);
		}		
	}

	UpdateArr(m_pArrCommunity[eTAB_COMMUNITY_PARTY], cnt);

	if (m_pScrollCommunity[eTAB_COMMUNITY_PARTY] != NULL)
		m_pScrollCommunity[eTAB_COMMUNITY_PARTY]->SetItemsPerPage(DEF_MAX_SHOW_ROW);

	m_pArrCommunity[eTAB_COMMUNITY_PARTY]->UpdateItem();
}

void CUICharacterInfo::UpdateSyndicateMark()
{
	BOOL bJoin = TRUE;
	BOOL bKay = FALSE;

	switch (_pNetwork->MyCharacterInfo.iSyndicateType)
	{
	case CSyndicate::eTYPE_NONE:
		bJoin = FALSE;
		break;
	case CSyndicate::eTYPE_KAILUX:
		bKay = TRUE;
		break;
	case CSyndicate::eTYPE_DEALERMOON:
		bKay = FALSE;
		break;
	default:
		return;
	}
	
	if (m_pImgNoJoin != NULL)
		m_pImgNoJoin->Hide(bJoin);

	if (m_pBtnSyndicateInfo != NULL)
		m_pBtnSyndicateInfo->SetEnable(bJoin);

	if (m_pScrollSyndiHistory != NULL)
		m_pScrollSyndiHistory->Hide(!bJoin);

	for (int i = 0; i < eTAB_SYNDICATE_MAX; i++)
	{
		if (m_pImgMark[i] == NULL)
			return;
	}

	if (bJoin == FALSE)
	{
		m_pImgMark[eTAB_SYNDICATE_KAY]->Hide(!bJoin);
		m_pImgMark[eTAB_SYNDICATE_DEAL]->Hide(!bJoin);
	}
	else
	{
		m_pImgMark[eTAB_SYNDICATE_KAY]->Hide(!bKay);
		m_pImgMark[eTAB_SYNDICATE_DEAL]->Hide(bKay);
	}
}

void CUICharacterInfo::UpdateTotalJewel()
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	CSyndicate* pSyndiInfo = pGameDataManager->GetSyndicate();

	if (pSyndiInfo == NULL)
 		return;

	UpdateClient::SyndicatePercentageData* pData = pSyndiInfo->GetJewelInfo();

	if (pData == NULL)
		return;

	float fKay = 0.0f, fDeal = 0.0f;

	if (pData->percentage >= 0.0f)
	{
		switch (pData->syndicateType)
		{
		case CSyndicate::eTYPE_KAILUX:
			fKay = pData->percentage;
			fDeal = 100.0f - fKay;
			break;

		case CSyndicate::eTYPE_DEALERMOON:
			fDeal = pData->percentage;
			fKay = 100.0f - fDeal;
			break;

		default:
			return;
		}
	}

	if (m_pProgressBar[eTAB_SYNDICATE_KAY] != NULL)
		m_pProgressBar[eTAB_SYNDICATE_KAY]->OffsetProgressPos(fKay);

	if (m_pProgressBar[eTAB_SYNDICATE_DEAL] != NULL)
		m_pProgressBar[eTAB_SYNDICATE_DEAL]->OffsetProgressPos(fDeal);

	CTString strKay, strDeal;
	
	strKay.PrintF( "%.1f%%", fKay );
	strDeal.PrintF( "%.1f%%", fDeal );

	for( int i = 0; i < PR_STAT_TAG_END; i++ )
	{
		m_pProgressBar[eTAB_SYNDICATE_KAY]->setProgressText( (_tagProgressStatus)i, strKay, FALSE, 0xFFFFFFFF);
		m_pProgressBar[eTAB_SYNDICATE_DEAL]->setProgressText( (_tagProgressStatus)i, strDeal, FALSE, 0xFFFFFFFF );
	}
}

void CUICharacterInfo::UpdateMySyndiPos()
{
	int nSyndiType = _pNetwork->MyCharacterInfo.iSyndicateType;
	int nGrade = _pNetwork->MyCharacterInfo.iSyndicateGrade;

	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	CSyndicate* pSyndiInfo = pGameDataManager->GetSyndicate();

	if (pSyndiInfo == NULL)
		return;

	CTString strString = pSyndiInfo->GetGradeName(nSyndiType, nGrade);

	if (m_pTextMyPos != NULL)
		m_pTextMyPos->SetText(strString);

	CTString strExp = "0/0 (0.0%%)";
	float fPercentage = 0.0f;

	if (nSyndiType > 0)
	{
		LONGLONG llCurExp = _pNetwork->MyCharacterInfo.lSyndicateAccPoint;
		LONGLONG llMaxExp = pSyndiInfo->GetAccMaxPoint();

		if (llMaxExp > 0 && llMaxExp >= llCurExp)
			fPercentage = ((float)llCurExp / (float)llMaxExp) * 100.0f;

		fPercentage = Clamp<FLOAT>(fPercentage, 0.f, 100.f);

		bool bPercentage = true;

		if (nSyndiType == CSyndicate::eTYPE_KAILUX)
		{
			if (nGrade >= CSyndicate::eGRADE_9TH)
				bPercentage = false;

		}
		else
		{
			if (nGrade >= CSyndicate::eGRADE_6TH)
				bPercentage = false;
		}

		CUIManager* pUIMgr = UIMGR();
		CTString strCurExp;
		strCurExp.PrintF("%I64d", llCurExp);
		pUIMgr->InsertCommaToString(strCurExp);

		if (bPercentage)
		{
			CTString strMaxExp;
			strMaxExp.PrintF("%I64d", llMaxExp);
			pUIMgr->InsertCommaToString(strMaxExp);

			strExp.PrintF( "%s/%s (%.1f%%)", strCurExp, strMaxExp, fPercentage );
		}
		else
		{
			fPercentage = 100.f;
			strExp.PrintF( "%s (%.1f%%)", strCurExp, fPercentage );
		}
	}

	if (m_pPbSyndicateExp != NULL)
		m_pPbSyndicateExp->OffsetProgressPos(fPercentage);

	for( int i = 0; i < PR_STAT_TAG_END; i++ )
	{
		m_pPbSyndicateExp->setProgressText( (_tagProgressStatus)i, strExp );
	}
}

void CUICharacterInfo::UpdateHonorPoints()
{
	CTString strExp = "0/0 (0.0%%)";
	float fPercentage = 0.0f;

	LONGLONG llHonorPoints = _pNetwork->MyCharacterInfo.a_honor;

	if (MAX_HONOR_POINTS >= llHonorPoints)
		fPercentage = ((float)llHonorPoints / (float)MAX_HONOR_POINTS) * 100.0f;

	fPercentage = Clamp<FLOAT>(fPercentage, 0.f, 100.f);

	CUIManager* pUIMgr = UIMGR();
	CTString strCurExp;

	//strCurExp.PrintF("%.2f", fPercentage);
	//UIMGR()->GetChattingUI()->AddSysMessage(strCurExp);

	strCurExp.PrintF("%I64d", llHonorPoints);
	pUIMgr->InsertCommaToString(strCurExp);

	CTString strMaxExp;
	LONGLONG llMaxPoints = MAX_HONOR_POINTS;
	strMaxExp.PrintF("%I64d", llMaxPoints);
	pUIMgr->InsertCommaToString(strMaxExp);

	//strExp.PrintF("%s/%s (%.2f%%)", strCurExp, strMaxExp, fPercentage);
	strExp.PrintF("%s/%s", strCurExp, strMaxExp);

	if (m_pPbHonorPoints != NULL)
		m_pPbHonorPoints->OffsetProgressPos(fPercentage);

	for (int i = 0; i < PR_STAT_TAG_END; i++)
	{
		m_pPbHonorPoints->setProgressText((_tagProgressStatus)i, strExp, TRUE, 0xFFFFFFFF);
	}
}

void CUICharacterInfo::UpdateArr( CUIArray* pArr, int nItemCnt )
{
	if (pArr == NULL)
		return;

	int nRow, nCol, nShowRow;  
	pArr->GetRowCol(nRow, nCol);

	int nItemRow = nItemCnt % nCol;
	int nItemCount = nItemCnt / nCol;

	if (nRow < nItemCount + nItemRow)
	{
		nRow = nItemCount + nItemRow;
	}

	pArr->SetRowCol(nRow, nCol);


	if (nRow > DEF_MAX_SHOW_ROW)
		nShowRow = DEF_MAX_SHOW_ROW;
	else
		nShowRow = nRow;

	pArr->SetShowRowCount(nShowRow);
}

CTString CUICharacterInfo::GetHistoryText( eSTRING_TYPE eType, int nIdx )
{
	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	CSyndicate* pSyndi = pGameDataManager->GetSyndicate();
	CTString strString = CTString("");

	if (pSyndi == NULL)
		return strString;

 	if (nIdx < 0 || nIdx >= pSyndi->GetHistoryCount())
 		return strString;

	UpdateClient::SyndicateHistoryData::historys* pData = pSyndi->GetHistoryData(nIdx);

	if (pData == NULL)
		return strString;

	if (eType == eSTRING_TYPE_TIME)
	{
		tm*	pTime = NULL;
		pTime = localtime((time_t*)&pData->time);
		if (pTime != NULL)  //new2022 ??
		strString.PrintF(_S(6068,"%d년 %d월 %d일 %d시"), pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday, pTime->tm_hour);
	}
	else
	{
		switch(pData->type)
		{
		case JOIN:		// ï¿½ï¿½ï¿½ï¿½			
			strString.PrintF( _S(6159,"%s ï¿½ï¿½ï¿½ë¿¡ ï¿½ï¿½ï¿½ï¿½ï¿½Ï¼Ì½ï¿½ï¿½Ï´ï¿½."), pSyndi->GetSyndicateName(pData->syndicateType));
			break;
		case REMOVE:	// Å»ï¿½ï¿½
			strString.PrintF( _S(6160,"%s ï¿½ï¿½ï¿½ë¿¡ï¿½ï¿½ Å»ï¿½ï¿½ï¿½Ï¼Ì½ï¿½ï¿½Ï´ï¿½."), pSyndi->GetSyndicateName(pData->syndicateType));
			break;
		case DEGRADE:	// ï¿½ï¿½ï¿½ï¿½
			strString.PrintF( _S(6158,"%sï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ï¿½ï¿½ï¿½Ï´ï¿½."), pSyndi->GetGradeName(pData->syndicateType, pData->grade));
			break;
		case PROMOTION:	// ï¿½Â±ï¿½
			strString.PrintF( _S(6157,"%sï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Â±ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½."), pSyndi->GetGradeName(pData->syndicateType, pData->grade));
			break;
		case WIN:		// ï¿½Â¸ï¿½
			strString.PrintF( _S(6161,"%s [%sï¿½ï¿½ï¿½ï¿½] ï¿½ï¿½ï¿½ï¿½ ï¿½Â¸ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½."), pData->targetName, pSyndi->GetSyndicateName(pData->targetSyndicateType));
			break;
		case LOSE:		// ï¿½ï¿½ï¿½ï¿½
			strString.PrintF( _S(6162,"%s [%sï¿½ï¿½ï¿½ï¿½] ï¿½ï¿½ï¿½ï¿½ ï¿½Ð¹ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ï¿½Ï´ï¿½."), pData->targetName, pSyndi->GetSyndicateName(pData->targetSyndicateType));
			break;
		}
	}

	return strString;
}

void CUICharacterInfo::UpdateSyndiHistory()
{
	if (m_pTbHistory == NULL)
		return;

	GameDataManager* pGameDataManager = GameDataManager::getSingleton();
	CSyndicate* pSyndi = pGameDataManager->GetSyndicate();

	if (pSyndi == NULL)
		return;

	CTString strString = CTString("");
	COLOR strColor = 0xFFFFFFFF;

	int max = pSyndi->GetHistoryCount();
	int i;

	for( i = 0; i < max; ++i )
	{
		if (i >= DEF_MAX_LIST)
			break;

		strString += ("[" + GetHistoryText(eSTRING_TYPE_TIME, i) + "]");
		strString += "\\n";
		strString += GetHistoryText(eSTRING_TYPE_HISTORY, i);
		strString += "\\n";
	}

	m_pTbHistory->SetText(strString);

	if (m_pScrollSyndiHistory != NULL)
		m_pScrollSyndiHistory->SetScrollPos(0);
}

void CUICharacterInfo::LoadTooltipString()
{
	CTString fnTemp; 
	CTString strFullPath = _fnmApplicationPath.FileDir();

	int iReadBytes = 0;

	if (m_nTooltipMax <= 0)
	{
		fnTemp = strFullPath + "data\\statTooltip.bin";

		FILE *fp		= NULL;	

		if ((fp = fopen(fnTemp, "rb")) == NULL) 
		{
			iReadBytes = -1;
		}

		fflush(fp);

		iReadBytes = fread(&m_nTooltipMax, sizeof(int), 1, fp);

		m_pstrTooltip = new stStatTooltip[m_nTooltipMax];

		iReadBytes = fread(m_pstrTooltip, sizeof(stStatTooltip) * m_nTooltipMax, 1, fp);

		fclose(fp);
	}
}

CTString CUICharacterInfo::GetTooltipString( int nJob, int _2nd, int index )
{
	if (m_pstrTooltip == NULL)
		return CTString("");

	int nTooltipNum = (nJob * 3) + _2nd;

	if (nTooltipNum < 0 || nTooltipNum >= m_nTooltipMax)
		return CTString("");

	return CUIBase::getText(m_pstrTooltip[nTooltipNum].nStrIndex[index]);
}

void CUICharacterInfo::UpdateStatTooltip()
{
	CUIText* pText = NULL;

	char* strTmp[4] = {"text_str", "text_dex", "text_int", "text_con"};

	for (int i = 0; i < 4; ++i)
	{
		pText = (CUIText*)findUI(strTmp[i]);

		if (pText == NULL)
			continue;

		pText->setTooltip(GetTooltipString(_pNetwork->MyCharacterInfo.job,
			_pNetwork->MyCharacterInfo.job2, i));
	}
}

void CUICharacterInfo::UpdateSelectImage( CUIIcon* pIcon )
{
	if (m_pImgSelect == NULL)
		return;

	if (pIcon == NULL)
	{
		m_pImgSelect->Hide(TRUE);
		return;
	}

	int x, y;

	pIcon->GetAbsPos(x, y);
	m_pImgSelect->SetPos(x - m_nPosX, y - m_nPosY);
	m_pImgSelect->Hide(FALSE);
}
