#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/function/TargetInfoNewUI.h>
#include <Engine/Interface/UISimplePop.h>
#include <Engine/Interface/UITrackPopup.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Interface/UIGuild.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Syndicate.h>
#include <Engine/Object/ActorMgr.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Help/Util_Help.h>
#include <Engine/Info/MyInfo.h>

extern CFontData *_pfdDefaultFont;
extern INDEX g_iCountry;

#define DEF_ICON_GAP_FAME 37
#define DEF_ICON_GAP_ATTR 12

//--------------------------------------------------------------
// ����
class CmdTargetInfoTooltip : public Command
{
public:
	CmdTargetInfoTooltip() : pUI_(NULL), eTooltip_(eTOOLTIP_FAME) {}
	void setData(CTargetInfoUI* pUI, eTARGET_TOOLTIP eType)	{ pUI_ = pUI; eTooltip_ = eType; }
	void execute() {
		if (pUI_)
			pUI_->UpdateTooltip(eTooltip_);
	}
private:
	CTargetInfoUI* pUI_;
	eTARGET_TOOLTIP eTooltip_;
};

CTargetInfoUI::CTargetInfoUI()
	: m_bDrag(false)
	, m_nOriX(0), m_nOriY(0)
	, m_nAddWidthGap(0)
	, m_nHpBarWidth(120) // UI UV�� ���� �⺻��
{
	m_bShowBuff = FALSE;
	m_bShowPkHp = FALSE;
	m_bShowHpBar = FALSE;

	int i;
	for (i = 0; i < eIMG_MAX; ++i)
		m_pImg[i] = NULL;

	for (i = 0; i < eTEXT_MAX; ++i)
		m_pText[i] = NULL;

	for (i = 0; i < eFRAME_MAX; ++i)
	{
		m_pImgSplit[i] = NULL;
		m_pStrName[i] = NULL;
		m_nFrameCenterWidth[i] = 47; // UI UV�� ���� �⺻��
		m_nNameWidth[i] = 0;
	}

	for (i = 0; i < eARRAY_MAX; ++i)
		m_pImgArr[i] = NULL;

	setInherit(false);
}

CTargetInfoUI::~CTargetInfoUI()
{
	Destroy();
}

void CTargetInfoUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, pixMinJ );
}

void CTargetInfoUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

void CTargetInfoUI::SetTargetBuff( BOOL bMe )
{
	m_bShowBuff = FALSE;
	_pUIBuff->ResetTargetBuff();

	ObjInfo* pInfo = ObjInfo::getSingleton();

	if( bMe )
	{
		_pUIBuff->CopyMyBuffToTargetBuff();
		m_bShowBuff = TRUE;
	}
	else
	{
		if( pInfo->GetTargetType(eTARGET) == CHARACTER )
		{
			if (pInfo->GetTargetEntity(eTARGET) != NULL)
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pInfo->GetTargetServerIdx(eTARGET));

				if (pObject != NULL)
				{
					CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);

					for( SBYTE sbBuff = 0; sbBuff < pTarget->cha_BuffCount; sbBuff++ )
					{
#ifdef NEW_CHAO_SYS
						if (pTarget->cha_Buff[sbBuff].m_slSkillIndex == 1395)//�� ������ ���� ���� ����.
						{
							pInfo->SetTargetPKHide(TRUE);
						}
						else
#endif
						{
							_pUIBuff->AddTargetBuff( pTarget->cha_Buff[sbBuff] );
						}
					}
					m_bShowBuff = TRUE;
				}
			}
		}
		else if( pInfo->GetTargetType(eTARGET) == MOB )
		{
			ObjectBase* pObject = 
				ACTORMGR()->GetObject(eOBJ_MOB, pInfo->GetTargetServerIdx(eTARGET));

			if (pObject != NULL)
			{
				CMobTarget* pMT = static_cast< CMobTarget* >(pObject);

				for( SBYTE sbBuff = 0; sbBuff < pMT->mob_BuffCount; sbBuff++ )
					_pUIBuff->AddTargetBuff( pMT->mob_Buff[sbBuff] );

				if ( !( pMT->IsTotem() || pMT->IsTrap() || pMT->IsParasite() ) )
				{
					m_bShowBuff = TRUE;
				}
				return;
			}
		}
		else if( pInfo->GetTargetType(eTARGET) == SUMMON )
		{
			if (pInfo->GetTargetEntity(eTARGET) != NULL)
			{
				ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_SLAVE, pInfo->GetTargetServerIdx(eTARGET));

				if (pObject != NULL)
				{
					CSlaveTarget* pTarget = static_cast< CSlaveTarget* >(pObject);

					for( SBYTE sbBuff = 0; sbBuff < pTarget->slave_BuffCount; sbBuff++ )
						_pUIBuff->AddTargetBuff( pTarget->slave_Buff[sbBuff] );

					m_bShowBuff = TRUE;

					return;
				}
			}
		}
	}
}

BOOL CTargetInfoUI::CloseWindowByEsc()
{
	UIMGR()->LostTarget();
	return TRUE;
}

void CTargetInfoUI::OpenUI()
{
	Hide(FALSE);
	UpdateUI();
}

void CTargetInfoUI::CloseUI()
{
	Hide(TRUE);
}

void CTargetInfoUI::UpdateUI()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (pInfo->IsTargetActive(eTARGET) == FALSE)
	{
		CloseUI();
		return;
	}
	
	if (pInfo->GetTargetEntity(eTARGET) != NULL && pInfo->GetTargetEntity(eTARGET)->IsFirstExtraFlagOn(ENF_EX1_CLICK_OBJECT))
	{
		CloseUI();
		return;
	}

	CMobData* pMD = CMobData::getData(pInfo->GetTargetDBIdx(eTARGET));
	// ��� ���� (���, ����, ��Ƽ����)
	UpdateFrame();

	// ���� ���� ( Level, �̸�, HP )
	UpdateTargetInfo();

	// ���� �̹��� ���� (����, �Ӽ�)
	UpdateFameIcon();
	UpdateAttrIcon();
	// RVR üũ
	UpdateSyndicateIcon();

}

void CTargetInfoUI::initialize()
{
	std::string strImgID[eIMG_MAX] = 	{ "img_move", "img_hp", "img_FameMark" };
	std::string strTextID[eTEXT_MAX] = 	{ "str_level", "str_hp" };
	std::string strSplitID[eFRAME_MAX] = { "is_backNormal", "is_backMob", "is_backPartyMob" };
	std::string strNameID[eFRAME_MAX] = { "str_nameN", "str_nameM", "str_namePM" };
	std::string strArrID[eARRAY_MAX] = 	{ "ia_attrAtt", "ia_attrDef", "ia_syndicate" };

	int i;
	for (i = 0; i < eIMG_MAX; ++i)
	{
		m_pImg[i] = (CUIImage*)findUI(strImgID[i].c_str());

		if (m_pImg[i] != NULL)
			m_pImg[i]->Hide(TRUE);
	}

	for (i = 0; i < eTEXT_MAX; ++i)
	{
		m_pText[i] = (CUIText*)findUI(strTextID[i].c_str());

		if (m_pText[i] != NULL)
			m_pText[i]->Hide(TRUE);
	}

	for (i = 0; i < eFRAME_MAX; ++i)
	{
		m_pImgSplit[i] = (CUIImageSplit*)findUI(strSplitID[i].c_str());

		if (m_pImgSplit[i] != NULL)
		{
			m_pImgSplit[i]->Hide(TRUE);
			m_nFrameCenterWidth[i] = m_pImgSplit[i]->GetWidth() - (m_pImgSplit[i]->GetUnit() * 2); // ������ �⺻ ������ ���
		}

		m_pStrName[i] = (CUIText*)findUI(strNameID[i].c_str());

		if (m_pStrName[i] != NULL)
		{
			m_pStrName[i]->Hide(TRUE);
			m_nNameWidth[i] = m_pStrName[i]->GetWidth(); // Name �� ũ�� ���
		}
	}

	for (i = 0; i < eARRAY_MAX; ++i)
	{
		m_pImgArr[i] = (CUIImageArray*)findUI(strArrID[i].c_str());

		if (m_pImgArr[i] != NULL)
			m_pImgArr[i]->Hide(TRUE);
	}

	if (m_pImg[eIMG_HP] != NULL)
	{
		// HP �� �⺻ ũ�� ���
		m_nHpBarWidth = m_pImg[eIMG_HP]->GetWidth();
	}
}

void CTargetInfoUI::OnPostRender( CDrawPort* pDraw )
{
	// Render target buff
	if( m_bShowBuff )
		_pUIBuff->RenderTargetBuff();
}

WMSG_RESULT CTargetInfoUI::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	if( m_bDrag && ( pMsg->wParam & MK_LBUTTON ) )
	{
		int ndX = x - m_nOriX;
		int ndY = y - m_nOriY;

		m_nOriX = x;
		m_nOriY = y;

		Move( ndX, ndY );
		return WMSG_SUCCESS;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();
	WMSG_RESULT	wmsgResult;

	if( m_bShowBuff && ( wmsgResult = _pUIBuff->MouseMessageTargetBuff( pMsg ) ) != WMSG_FAIL )
	{
		pUIManager->RearrangeOrder( UI_TARGETINFO, TRUE );
		return wmsgResult;
	}

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	pUIManager->SetMouseCursorInsideUIs();

	return WMSG_FAIL;
}

WMSG_RESULT CTargetInfoUI::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pImg[eIMG_MOVE] != NULL && m_pImg[eIMG_MOVE]->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}

	CUIManager* pUIManager = CUIManager::getSingleton();

	if(pUIManager->GetSimplePop()->IsEnabled())
	{
		// SIMPLE POP�� ���� �־��ٸ� �ݾ� �ش�..
		pUIManager->GetSimplePop()->ClosePop();
	}

	pUIManager->RearrangeOrder( UI_TARGETINFO, TRUE );
	return WMSG_SUCCESS;
}

WMSG_RESULT CTargetInfoUI::OnRButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager* pUIManager = CUIManager::getSingleton();

	if(m_pImg[eIMG_MOVE] != NULL && m_pImg[eIMG_MOVE]->IsInside(x, y))
	{
		pUIManager->GetSimplePop()->OpenPop(INFO()->GetTargetName(eTARGET),
											(GAMEDATAMGR()->GetPartyInfo()->GetMemberCount() > 0 && GAMEDATAMGR()->GetPartyInfo()->AmILeader()) ? TRUE : FALSE,	// ��Ƽ���̸� TRUE
											_pNetwork->MyCharacterInfo.lGuildPosition == GUILD_MEMBER_BOSS ? TRUE : FALSE,						// ���� ������϶��� TRUE
											x, y);

		return WMSG_SUCCESS;
	}
	else // [sora] �ٸ��� Ŭ���� �˾�â �ݱ�
	{
		pUIManager->GetSimplePop()->ClosePop();
	}

	return WMSG_FAIL;
}

WMSG_RESULT CTargetInfoUI::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	CUIManager::getSingleton()->ResetHoldBtn();
	return WMSG_FAIL;
}

void CTargetInfoUI::UpdateFrame()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CMobData* pMD = CMobData::getData(pInfo->GetTargetDBIdx(eTARGET));

	if (pMD->IsPartyMob())
		m_eBackGround = eFRAME_PMOB;
	else
	{
		if ( UIMGR()->IsEnemy(pInfo->GetTargetEntity(eTARGET), TARGET_TYPE(pInfo->GetTargetType(eTARGET)), TRUE) )
			m_eBackGround = eFRAME_MOB;
		else
			m_eBackGround = eFRAME_NORMAL;
	}

	for (int i = 0; i < eFRAME_MAX; ++i)
	{
		BOOL bHide = TRUE;

		if (i == m_eBackGround)
			bHide = FALSE;

		if (m_pImgSplit[i] != NULL)
			m_pImgSplit[i]->Hide(bHide);
	}
}

void CTargetInfoUI::UpdateFameIcon()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	bool bAdd = IsAddSubInfo(eSUB_INFO_FAME);

	if (m_pImg[eIMG_FAMEMARK] != NULL)
	{
		if (bAdd == true)
		{
			m_pImg[eIMG_FAMEMARK]->Hide(FALSE);
			m_pImg[eIMG_FAMEMARK]->SetPosX(m_nWidth - DEF_ICON_GAP_FAME);

			CmdTargetInfoTooltip* pCmd = new CmdTargetInfoTooltip;
			pCmd->setData(this, eTOOLTIP_FAME);
			m_pImg[eIMG_FAMEMARK]->SetCommandEnter(pCmd);

			UpdateTooltip(eTOOLTIP_FAME);
		}
		else
		{
			m_pImg[eIMG_FAMEMARK]->Hide(TRUE);
		}
	}
}

void CTargetInfoUI::UpdateAttrIcon()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();
	bool bAdd = IsAddSubInfo(eSUB_INFO_ATTR);

	int nAttr = 0, nAttrLv = 0;
	if (m_pImgArr[eARRAY_ATTR_ATT] != NULL)
	{
#ifdef SHOW_ELEMENTAL_INFO_TARGET
		if (bAdd == true)
		{
			_getAttr(eATTR_ATT, nAttr, nAttrLv);
			m_pImgArr[eARRAY_ATTR_ATT]->SetRenderIdx(nAttr);
			m_pImgArr[eARRAY_ATTR_ATT]->Hide(FALSE);
			m_pImgArr[eARRAY_ATTR_ATT]->SetPosX(m_nWidth - DEF_ICON_GAP_ATTR);

			CmdTargetInfoTooltip* pCmd = new CmdTargetInfoTooltip;
			pCmd->setData(this, eTOOLTIP_ATTRATT);
			m_pImgArr[eARRAY_ATTR_ATT]->SetCommandEnter(pCmd);

			UpdateTooltip(eTOOLTIP_ATTRATT);
		}
		else
#endif
		{
			m_pImgArr[eARRAY_ATTR_ATT]->Hide(TRUE);
		}
	}

	if (m_pImgArr[eARRAY_ATTR_DEF] != NULL)
	{
#ifdef SHOW_ELEMENTAL_INFO_TARGET
		if (bAdd == true)
		{
			_getAttr(eATTR_DEF, nAttr, nAttrLv);
			m_pImgArr[eARRAY_ATTR_DEF]->SetRenderIdx(nAttr);
			m_pImgArr[eARRAY_ATTR_DEF]->Hide(FALSE);
			m_pImgArr[eARRAY_ATTR_DEF]->SetPosX(m_nWidth);

			CmdTargetInfoTooltip* pCmd = new CmdTargetInfoTooltip;
			pCmd->setData(this, eTOOLTIP_ATTRDEF);
			m_pImgArr[eARRAY_ATTR_DEF]->SetCommandEnter(pCmd);

			UpdateTooltip(eTOOLTIP_ATTRDEF);
		}
		else
#endif
		{
			m_pImgArr[eARRAY_ATTR_DEF]->Hide(TRUE);
		}
	}

}

void CTargetInfoUI::UpdateSyndicateIcon()
{
	bool bAdd = IsAddSubInfo(eSUB_INFO_SYNDICATE);

	if (m_pImgArr[eARRAY_SYNDICATE] != NULL)
	{
		if (bAdd == true)
		{
			m_pImgArr[eARRAY_SYNDICATE]->SetRenderIdx(INFO()->GetTargetSyndiType() - 1);
			m_pImgArr[eARRAY_SYNDICATE]->Hide(FALSE);
			
			CmdTargetInfoTooltip* pCmd = new CmdTargetInfoTooltip;
			pCmd->setData(this, eTOOLTIP_SYNDICATE);
			m_pImgArr[eARRAY_SYNDICATE]->SetCommandEnter(pCmd);
			
			UpdateTooltip(eTOOLTIP_SYNDICATE);
		}
		else
		{
			m_pImgArr[eARRAY_SYNDICATE]->Hide(TRUE);
		}
	}
}

void CTargetInfoUI::UpdateTargetInfo()
{
	CUIManager* pUIMgr = CUIManager::getSingleton();
	UtilHelp* pHelp = UtilHelp::getSingleton();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	CMobData* pMD = CMobData::getData(pInfo->GetTargetDBIdx(eTARGET));

	int nColorIdx = 0;
	int nLevel = pInfo->GetTargetLevel(eTARGET);
	CTString strName = pInfo->GetTargetName(eTARGET);
	CTString strLevel;
	CTString strHp;
	strLevel.PrintF("%d", nLevel);
	BOOL bHideLevel = TRUE;	// Level ǥ�� �ϴ���
	BOOL bHideHpString = TRUE; // ��ġ ������ ȿ�� ǥ�� ����
	m_bShowHpBar = FALSE; // HP ǥ�� ����

	int string_color = 5; // rrbkmz

	switch( pInfo->GetTargetType(eTARGET) )
	{
	case MOB:
		{
			// Text color
			nColorIdx = 4;
			m_bShowHpBar = TRUE;

			//// rrbkmz
			bHideHpString = FALSE;
			float fHealth = pInfo->GetTargetCurHP(eTARGET);
			float fHealth_max = pInfo->GetTargetMaxHP(eTARGET);

			if (fHealth_max == fHealth || (fHealth_max / fHealth) < 2)
				string_color = 8;
			else if ((fHealth_max / fHealth) >= 2 && fHealth > (fHealth_max * 0.3F))
				string_color = 13;
			else
				string_color = 5;

			strHp.PrintF("%d/%d", (int)fHealth, (int)fHealth_max);
			// rrbkmz
			
			// [2010/10/20 : Sora] ���� �뺴 ī��
			if( pInfo->GetTargetEntity(eTARGET)->IsFirstExtraFlagOn(ENF_EX1_MONSTER_MERCENARY) )
			{
				strName = _S( 5151, "[�뺴]") + strName;
				nColorIdx = 12;
			}
			else if ( pInfo->GetTargetEntity(eTARGET)->GetFirstExFlags() & ( ENF_EX1_TOTEM | ENF_EX1_TRAP | ENF_EX1_SUICIDE ) )
			{
				nColorIdx = 13;
			}
			else
			{
				int	nLevelDiff = nLevel - _pNetwork->MyCharacterInfo.level;
				if( nLevelDiff > 5 ) nColorIdx = 0;
				else if( nLevelDiff > 2 ) nColorIdx = 1;
				else if( nLevelDiff > -3 ) nColorIdx = 2;
				else if( nLevelDiff > -6 ) nColorIdx = 3;	
			}
			
			// Mob Level
			if ( !(  pInfo->GetTargetEntity(eTARGET)->GetFirstExFlags() & ( ENF_EX1_TOTEM | ENF_EX1_TRAP | ENF_EX1_SUICIDE ) ) )
			{	// ����, Ʈ��, �з�����Ʈ�� ������ ǥ������ �ʴ´�.
				bHideLevel = FALSE;
			}
		}
		break;

	case P1PET:
	case WILDPET:
		{
		// rrbkmz
			m_bShowHpBar = TRUE;
			bHideHpString = FALSE;
			float fHealth = pInfo->GetTargetCurHP(eTARGET);
			float fHealth_max = pInfo->GetTargetMaxHP(eTARGET);
			strHp.PrintF("%d/%d", (int)fHealth, (int)fHealth_max);
			if (fHealth_max == fHealth || (fHealth_max / fHealth) < 2)
				string_color = 8;
			else if ((fHealth_max / fHealth) >= 2 && fHealth > (fHealth_max * 0.3F))
				string_color = 13;
			else
				string_color = 5;
			// rrbkmz
			nColorIdx = 9;
		}
		break;

	case NPC:
		{
			nColorIdx = 5;

			m_bShowHpBar = TRUE;// rrbkmz
			bHideLevel = FALSE;//AssasinPL
			bHideHpString = FALSE;
			float fHealth = pInfo->GetTargetCurHP(eTARGET);
			float fHealth_max = pInfo->GetTargetMaxHP(eTARGET);
			if (fHealth_max == fHealth || (fHealth_max / fHealth) < 2)
				string_color = 8;
			else if ((fHealth_max / fHealth) >= 2 && fHealth > (fHealth_max * 0.3F))
				string_color = 13;
			else
				string_color = 5;
			strHp.PrintF("%d/%d", (int)fHealth, (int)fHealth_max);

			//NPC 안내시스템
			if( pUIMgr->m_nHelpNpc_Index == pInfo->GetTargetDBIdx(eTARGET) ) 
				pUIMgr->m_nHelpNpc_Index = -1;
		}
		break;

	case CHARACTER:
		{
		//	if( m_bShowPkHp )
			//{			
					float fHealth = 0;
					float fHealth_max = 0;// rrbkmz
					if (pInfo->GetTargetEntity(eTARGET) != NULL &&
						pInfo->GetTargetServerIdx(eTARGET) == _pNetwork->MyCharacterInfo.index)
					{
						fHealth = _pNetwork->MyCharacterInfo.hp;
						fHealth_max = _pNetwork->MyCharacterInfo.maxHP;// rrbkmz
					}
					else
					{
						fHealth = pInfo->GetTargetCurHP(eTARGET);
						fHealth_max = pInfo->GetTargetMaxHP(eTARGET);// rrbkmz
					}
					strHp.PrintF("%d/%d", (int)fHealth, (int)fHealth_max);
					// rrbkmz
					if (fHealth_max == fHealth || (fHealth_max / fHealth) < 2)
						string_color = 8;
					else if ((fHealth_max / fHealth) >= 2 && fHealth > (fHealth_max * 0.3F))
						string_color = 13;
					else
						string_color = 5;
						// rrbkmz
					bHideHpString = FALSE;
					m_bShowHpBar = TRUE;
		//	}
			
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pInfo->GetTargetServerIdx(eTARGET));
			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
				int reborn = pTarget->cha_reborn;
				if (reborn < 0) 
					reborn = 0;

				strLevel.PrintF("%d", reborn);
				bHideLevel = FALSE;
			}

#ifdef NEW_CHAO_SYS
			nColorIdx = 9;
			int nPKState = pInfo->GetTargetPKState(eTARGET);
			if(pInfo->IsTargetPKHide() == FALSE)
			{
				if (nPKState  > 19000 && nPKState  <= 32000)
					nColorIdx = 14;
				else if(nPKState  > 6000 && nPKState  <= 19000)
					nColorIdx = 15;
				else if(nPKState  > 0 && nPKState  <= 6000)
					nColorIdx = 16;
				else if(nPKState  >= -6000 && nPKState  < 0)
					nColorIdx = 17;
				else if(nPKState  >= -19000 && nPKState  < -6000)
					nColorIdx = 18;
				else if(nPKState  >= -32000 && nPKState  < -19000)
					nColorIdx = 19;
			}

			if (pObject != NULL) {
				CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
				if (pTarget->cha_color_name) {
					nColorIdx = pTarget->cha_color_name;
				}
			}
#else
			// Text color
			nColorIdx = 9;
			if( nPKState < -9 ) 
				nColorIdx = 11;
			else if( nPKState > 9 ) 
				nColorIdx = 7;

			if( pInfo->GetTargetPKMode(eTARGET) != 0 )
				nColorIdx--;
#endif
		}
		break;

	default:	// Product, Item
		{
			nColorIdx = 2;
		}
		break;
	};

	int nAddWidth = 0;

	if (g_iCountry == RUSSIA)
		nAddWidth = pHelp->GetNoFixedWidth(_pfdDefaultFont, strName.str_String) + 13;
	else
		nAddWidth = (strName.Length())*( _pUIFontTexMgr->GetFontWidth()+_pUIFontTexMgr->GetFontSpacing());

	if (nAddWidth > m_nFrameCenterWidth[m_eBackGround])
	{
		// �þ�� ���� ����� (HP�� ��꿡 �ʿ�)
		m_nAddWidthGap = nAddWidth - m_nFrameCenterWidth[m_eBackGround];
	}
	else
	{
		nAddWidth = m_nFrameCenterWidth[m_eBackGround];
		m_nAddWidthGap = 0;
	}

	// �̸� �� ������ ������ ������Ʈ
	UpdateFrameSize(nAddWidth);

	// �̸� ����
	if (m_pStrName[m_eBackGround] != NULL)
	{
		m_pStrName[m_eBackGround]->SetText(strName);
		m_pStrName[m_eBackGround]->setFontColor(pHelp->GetTargetNameColor(nColorIdx));
		m_pStrName[m_eBackGround]->Hide(FALSE);
	}

	// ���� ����
	if (m_pText[eTEXT_LEVEL] != NULL)
	{
		m_pText[eTEXT_LEVEL]->SetText(strLevel);
		m_pText[eTEXT_LEVEL]->Hide(bHideLevel);
	}
	// ��ġ ������ ȿ��
	if (m_pText[eTEXT_HP] != NULL)
	{
		m_pText[eTEXT_HP]->SetPos(((nAddWidth / 2) + (nAddWidth / 4)), 20);// rrbkmz
		m_pText[eTEXT_HP]->Hide(bHideHpString);
		m_pText[eTEXT_HP]->SetText(strHp);
		m_pText[eTEXT_HP]->setFontColor(pHelp->GetTargetNameColor(string_color));
	}

	// HP ������Ʈ
	UpdateHPInfo();
}

void CTargetInfoUI::UpdateFrameSize( int nWidth )
{
	// ���� Frame ������Ʈ
	if (m_pImgSplit[m_eBackGround] != NULL)
	{
		int nTotalWidth = nWidth + (m_pImgSplit[m_eBackGround]->GetUnit() * 2);

		m_pImgSplit[m_eBackGround]->SetSize( nTotalWidth, m_pImgSplit[m_eBackGround]->GetHeight() );
		m_pImgSplit[m_eBackGround]->UpdateSplit();

		if (m_pStrName[m_eBackGround] != NULL)
		{
			m_pStrName[m_eBackGround]->SetSize(m_nNameWidth[m_eBackGround] + m_nAddWidthGap, m_pStrName[m_eBackGround]->GetHeight());
		}

		// UI ������ ������Ʈ (������ ��ġ ������ ������Ʈ �ʿ�)
		SetSize(nTotalWidth, m_pImgSplit[m_eBackGround]->GetHeight());
	}
}

// rrbkmz
void CTargetInfoUI::UpdateHPInfoOnText()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	switch (pInfo->GetTargetType(eTARGET))
	{
	case MOB:
	case CHARACTER:
	case WILDPET:
		if (m_pImgSplit[m_eBackGround] != NULL)
		{
			ObjInfo* pInfo = ObjInfo::getSingleton();
			UtilHelp* pHelp = UtilHelp::getSingleton();
			CTString strHp;
			int string_color = 5;


			float fHealth = pInfo->GetTargetCurHP(eTARGET);
			float fHealth_max = pInfo->GetTargetMaxHP(eTARGET);
			strHp.PrintF("%d/%d", (int)fHealth, (int)fHealth_max);

			if (fHealth_max == fHealth || (fHealth_max / fHealth) < 2)
				string_color = 8;
			else if ((fHealth_max / fHealth) >= 2 && fHealth > (fHealth_max * 0.3F))
				string_color = 13;
			else
				string_color = 5;

			int nAddWidth = m_pImgSplit[m_eBackGround]->GetWidth();
			if (m_pText[eTEXT_HP] != NULL)
			{
				//m_pText[eTEXT_HP]->SetPos(((nAddWidth / 2) + (nAddWidth / 4)), 20);
				m_pText[eTEXT_HP]->Hide(FALSE);
				m_pText[eTEXT_HP]->SetText(strHp);
				m_pText[eTEXT_HP]->setFontColor(pHelp->GetTargetNameColor(string_color));
			}
		}
	default:
		break;
	}
}
// rrbkmz
void CTargetInfoUI::UpdateHPInfo()
{
	if (m_pImg[eIMG_HP] == NULL)
		return;

	if (m_bShowHpBar == FALSE)
	{
		m_pImg[eIMG_HP]->Hide(TRUE);
		return;
	}

	// HP
	FLOAT	fHPRatio = 0;
	ObjInfo* pInfo = ObjInfo::getSingleton();
	
	if ( pInfo->GetTargetEntity(eTARGET) != NULL &&
		pInfo->GetTargetServerIdx(eTARGET) == _pNetwork->MyCharacterInfo.index)
	{
		fHPRatio = (float)_pNetwork->MyCharacterInfo.hp / (float)_pNetwork->MyCharacterInfo.maxHP;
	}
	else
	{
		fHPRatio = pInfo->GetTargetCurHP(eTARGET) / pInfo->GetTargetMaxHP(eTARGET);
	}

	if (fHPRatio > 1.0f)
		fHPRatio = 1.0f;
	else if (fHPRatio < 0.0f)
		fHPRatio = 0.0f;

	m_pImg[eIMG_HP]->SetWidth( (m_nAddWidthGap + m_nHpBarWidth) * fHPRatio);
	m_pImg[eIMG_HP]->Hide(FALSE);

	UpdateHPInfoOnText();
}

void CTargetInfoUI::UpdateTooltip( eTARGET_TOOLTIP eType )
{
	CTString strTooltip = "";

	switch(eType)
	{
	case eTOOLTIP_FAME:
		{
			if (m_pImg[eIMG_FAMEMARK] != NULL)
			{
				strTooltip = _getFameTooltip();
				m_pImg[eIMG_FAMEMARK]->setTooltip(strTooltip);
			}
		}		
		break;
	case eTOOLTIP_ATTRATT:
		{
			if (m_pImgArr[eARRAY_ATTR_ATT] != NULL)
			{
				strTooltip = _getAttrTooltip(eATTR_ATT);			
				m_pImgArr[eARRAY_ATTR_ATT]->setTooltip(strTooltip);
			}
		}
		break;
	case eTOOLTIP_ATTRDEF:
		{
			if (m_pImgArr[eARRAY_ATTR_DEF] != NULL)
			{
				strTooltip = _getAttrTooltip(eATTR_DEF);
				m_pImgArr[eARRAY_ATTR_DEF]->setTooltip(strTooltip);
			}
		}
		break;
	case eTOOLTIP_SYNDICATE:
		{
			if (m_pImgArr[eARRAY_SYNDICATE] != NULL)
			{
				int nWidth = 0;
				strTooltip = _getSyndicateTooltip(nWidth);
				m_pImgArr[eARRAY_SYNDICATE]->setTooltip(strTooltip);
				m_pImgArr[eARRAY_SYNDICATE]->setTooltipWidth(nWidth);
			}
		}
		break;
	}
}

CTString CTargetInfoUI::_getFameTooltip()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CTString strTooltip = "";

	int wins = _getWins();
	int loses = _getLoses();

    if (wins == -1 && loses == -1)
		strTooltip.PrintF( _S(1741, "I'm newbie") );
    else
        strTooltip.PrintF( _S(1742, "Wins : %d  Loses: %d"), wins, loses );

	return strTooltip;
}

CTString CTargetInfoUI::_getAttrTooltip(int attrType)
{
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CTString strTooltip = "";

	int nAttr = 0, nAttrLv = 0;
	int nStringID;

	// �Ӽ� ���
	_getAttr(attrType, nAttr, nAttrLv);

	switch(attrType)
	{
	case eATTR_ATT:
		nStringID = 5853;			
		break;
	case eATTR_DEF:
		nStringID = 5854;
		break;
	default:
		return strTooltip;
	}
	// �Ӽ� �ý��� �Ӽ� ���� ���� ǥ��
	CTString strAtt;
	// �Ӽ� �ý��� ��ų ���� �Ӽ� ��Ʈ�� ���
	strAtt = UtilHelp::getSingleton()->GetAttributeString(nAttr);
	strTooltip.PrintF( _S( nStringID, "���� or ��� : [%s]�Ӽ� [%d]�ܰ�"), strAtt, nAttrLv);
		
	return strTooltip;
}

CTString CTargetInfoUI::_getSyndicateTooltip(int& nWidth)
{
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CTString strTooltip = "";

	GameDataManager* pGameData = GameDataManager::getSingleton();

	if (pGameData == NULL)
		return strTooltip;

	CSyndicate* pSyndicate = pGameData->GetSyndicate();

	if (pSyndicate == NULL)
		return strTooltip;

	CTString strSyndicateType = pSyndicate->GetSyndicateName(pInfo->GetTargetSyndiType());
	CTString strSyndicateGrade = pSyndicate->GetGradeName(pInfo->GetTargetSyndiType(), pInfo->GetTargetSyndiGrade());

	if (strSyndicateType.IsEmpty() == TRUE)
		return strTooltip;

	strSyndicateType = _S(6167, "�Ҽ�:") + strSyndicateType;

	CDrawPort* pDraw = CUIManager::getSingleton()->GetDrawPort();
	
	if (g_iCountry == RUSSIA)
		nWidth = UTIL_HELP()->GetNoFixedWidth(_pfdDefaultFont, strSyndicateType.str_String);
	else
		nWidth = pDraw->GetTextWidth2(strSyndicateType);

	if (strSyndicateGrade.IsEmpty() == FALSE)
	{
		strSyndicateGrade = _S(6168, "����:") + strSyndicateGrade;
	}

	strTooltip = strSyndicateType + strSyndicateGrade;
	return strTooltip;
}

bool CTargetInfoUI::IsAddSubInfo( eSUB_INFO_TYPE eType )
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	bool bAdd = false;

	switch(eType)
	{
	case eSUB_INFO_FAME:
		{
			if (pInfo->GetTargetType(eTARGET) == CHARACTER)
				bAdd = true;
		}
		break;

	case eSUB_INFO_ATTR:
		{
			if (pInfo->GetTargetType(eTARGET) == MOB || pInfo->GetTargetType(eTARGET) == NPC)
				bAdd = true;
		}
		break;

	case eSUB_INFO_SYNDICATE:
		{
			if (pInfo->GetTargetSyndiType() > 0 && 
				pInfo->GetTargetSyndiType() < CSyndicate::eTYPE_MAX)
				bAdd = true;
		}
		break;

	default:
		break;
	}

	return bAdd;
}

int CTargetInfoUI::_getWins()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	int wins = -1;

	if (pInfo->GetTargetEntity(eTARGET) == CEntity::GetPlayerEntity(0)) //�� ����
	{
		wins = _pNetwork->MyCharacterInfo.a_wins;
	}
	else
	{
		if (pInfo->GetTargetEntity(eTARGET) != NULL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pInfo->GetTargetServerIdx(eTARGET));

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
				wins = pTarget->cha_wins;
			}
		}
	}

	return wins;
}

int CTargetInfoUI::_getLoses()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	int loses = -1;

	if (pInfo->GetTargetEntity(eTARGET) == CEntity::GetPlayerEntity(0)) //�� ����
	{
		loses = _pNetwork->MyCharacterInfo.a_loses;
	}
	else
	{
		if (pInfo->GetTargetEntity(eTARGET) != NULL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pInfo->GetTargetServerIdx(eTARGET));

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
				loses = pTarget->cha_loses;
			}
		}
	}

	return loses;
}

int CTargetInfoUI::_getFame()
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	int fame = -1;

	if (pInfo->GetTargetEntity(eTARGET) == CEntity::GetPlayerEntity(0)) //�� ����
	{
		fame = _pNetwork->MyCharacterInfo.fame;
	}
	else
	{
		if (pInfo->GetTargetEntity(eTARGET) != NULL)
		{
			ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_CHARACTER, pInfo->GetTargetServerIdx(eTARGET));

			if (pObject != NULL)
			{
				CCharacterTarget* pTarget = static_cast< CCharacterTarget* >(pObject);
				fame = pTarget->cha_nFame;
			}
		}
	}

	return fame;
}

void CTargetInfoUI::_getAttr(int attrType, int& attr, int& attrLv )
{
	ObjInfo* pInfo = ObjInfo::getSingleton();

	CMobData* MD = CMobData::getData(pInfo->GetTargetDBIdx(eTARGET));

	if (MD == NULL)
		return;

	bool bPriorityAttr = false; // ���� �Ӽ� ���������� ���Ͽ� �߰���
	// �����ۿ� ���� ����� �Ӽ��� �켱������ �����

	ObjectBase* pObject = ACTORMGR()->GetObject(eOBJ_MOB, pInfo->GetTargetServerIdx(eTARGET));

	if (pObject != NULL)
	{
		if ( (pObject->GetAttrAtt() != MD->GetAttratt()) || (pObject->GetAttrDef() != MD->GetAttrdef()) )
			bPriorityAttr = true;
	}

	switch(attrType)
	{
	case eATTR_ATT:
		{
			attr = bPriorityAttr == true ? pObject->GetAttrAtt() : MD->GetAttratt();
			attrLv = bPriorityAttr == true ? pObject->GetAttrDefLv() : MD->GetAttrdefLv();
		}
		break;
	case eATTR_DEF:
		{
			attr = bPriorityAttr == true ? pObject->GetAttrDef() : MD->GetAttrdef();
			attrLv = bPriorityAttr == true ? pObject->GetAttrAttLv() : MD->GetAttrattLv();
		}
		break;
	default:
		return;
	}
}
