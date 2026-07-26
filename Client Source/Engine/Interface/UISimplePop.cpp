#include "stdh.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UITrackPopup.h>
#include <Engine/Interface/UISimplePop.h>
#include <Engine/Interface/UIMessenger.h>
#include <Engine/Contents/Base/UIPartyNew.h>
#include <Engine/Contents/Base/UIExpedition.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/Party.h>
#include <Engine/Info/MyInfo.h>

extern INDEX g_iCountry;

// ����Ʈ �ڽ� ũ�⿡ �°� �ڽ��� �׸��� ��,�Ʒ�/ ��,�� ���� 
#define SPACE_UPDONW	14
#define SPACE_LEFTRIGT	10

CUISimplePop::CUISimplePop()
{
	m_ptdMenuTexture = NULL;
	m_ptdExpeditionTexture = NULL;
	m_bTarget = true;
	m_nNoTargetCharIndex = -1;
}

CUISimplePop::~CUISimplePop()
{
	if (m_ptdMenuTexture)
	{
		_pTextureStock->Release(m_ptdMenuTexture);
		m_ptdMenuTexture = NULL;
	}

	if (m_ptdExpeditionTexture)
	{
		_pTextureStock->Release(m_ptdExpeditionTexture);
		m_ptdExpeditionTexture = NULL;
	}
}

void CUISimplePop::Create( CUIWindow *pParentWnd, int nX, int nY, int nWidth, int nHeight)
{
	SetPos( nX, nY );
	SetSize( nWidth, nHeight );

	m_ptdBaseTexture = CreateTexture( CTString( "Data\\Interface\\MessageBox.tex" ) );

	FLOAT	fTexWidth = m_ptdBaseTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdBaseTexture->GetPixHeight();

	m_rtBackUL.SetUV( 164, 45, 171, 63, fTexWidth, fTexHeight );
	m_rtBackUM.SetUV( 174, 45, 176, 63, fTexWidth, fTexHeight );
	m_rtBackUR.SetUV( 179, 45, 186, 63, fTexWidth, fTexHeight );
	m_rtBackML.SetUV( 164, 55, 171, 58, fTexWidth, fTexHeight );
	m_rtBackMM.SetUV( 174, 55, 176, 58, fTexWidth, fTexHeight );
	m_rtBackMR.SetUV( 179, 55, 186, 58, fTexWidth, fTexHeight );
	m_rtBackLL.SetUV( 164, 60, 171, 68, fTexWidth, fTexHeight );
	m_rtBackLM.SetUV( 174, 60, 176, 68, fTexWidth, fTexHeight );
	m_rtBackLR.SetUV( 179, 60, 186, 68, fTexWidth, fTexHeight );

	CUIListBox::Create( NULL, 0,  0, 100, 179, _pUIFontTexMgr->GetLineHeight()+2, 6, 3, 1, TRUE, TRUE );

	SetScrollBar( FALSE );
	SetSelBar( 100, _pUIFontTexMgr->GetLineHeight()+2, 187, 46, 204, 61, fTexWidth, fTexHeight );
	SetOverColor( 0xF8E1B5FF );
	SetSelectColor( 0xF8E1B5FF );

	m_tpList.m_rtBackUL.SetUV( 164, 45, 171, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackUM.SetUV( 174, 45, 176, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackUR.SetUV( 179, 45, 186, 63, fTexWidth, fTexHeight );
	m_tpList.m_rtBackML.SetUV( 164, 55, 171, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackMM.SetUV( 174, 55, 176, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackMR.SetUV( 179, 55, 186, 58, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLL.SetUV( 164, 60, 171, 68, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLM.SetUV( 174, 60, 176, 68, fTexWidth, fTexHeight );
	m_tpList.m_rtBackLR.SetUV( 179, 60, 186, 68, fTexWidth, fTexHeight );


	m_tpList.Create( this, 0,  0, 100, 102, _pUIFontTexMgr->GetLineHeight(), 6, 3, 1, TRUE, TRUE );
	m_tpList.SetScrollBar( FALSE );
	m_tpList.SetSelBar( 100, _pUIFontTexMgr->GetLineHeight()+2, 187, 46, 204, 61, fTexWidth, fTexHeight );
	m_tpList.SetOverColor( 0xF8E1B5FF );
	m_tpList.SetSelectColor( 0xF8E1B5FF );
	m_tpList.Hide();

	//���� �޴� ������ ���� ȭ��ǥ �ؽ��� �߰�
	m_ptdMenuTexture = CreateTexture( CTString( "Data\\Interface\\WebBoard.tex" ) );
	fTexWidth = m_ptdMenuTexture->GetPixWidth();
	fTexHeight = m_ptdMenuTexture->GetPixHeight();

	m_rtArrow.SetUV(34, 117, 42, 125, fTexWidth, fTexHeight);		//��� ȭ��ǥ

//////////////////////////////////////////////////////////////////////////
// [sora] RAID_SYSTEM
	m_ptdExpeditionTexture = CreateTexture( CTString("Data\\Interface\\Expedition.tex") );
	fTexWidth = m_ptdExpeditionTexture->GetPixWidth();
	fTexHeight = m_ptdExpeditionTexture->GetPixHeight();

	int nPosX = 474;
	for(int i=0; i<LABEL_INDEX_TOTAL; i++)
	{
		m_rtLabelIcon[i].SetUV(nPosX, 182, nPosX + 18, 200, fTexWidth, fTexHeight);

		nPosX -= 20;
	}
//////////////////////////////////////////////////////////////////////////
}

void CUISimplePop::OpenPop(CTString strUserName, BOOL bParty, BOOL bGuild, INDEX ixPos, INDEX iyPos)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	// Ÿ�� ĳ���Ͱ� �ڽ��̸� ����.
	if ( pInfo->GetTargetEntity(eTARGET) && 
		(pInfo->GetTargetServerIdx(eTARGET) == _pNetwork->MyCharacterInfo.index) )
		return;

	if( pInfo->GetTargetType(eTARGET) != CHARACTER && pInfo->GetTargetType(eTARGET) != MOB)
	{
		// ĳ���ͳ� mob�� �ƴϸ� ����
		return;
	}
	else if(pInfo->GetTargetType(eTARGET) == MOB && !pUIManager->IsCSFlagOn(CSF_EXPEDITION))
	{
		// �����뿡 �������� �������¿��� mobŬ���� ����
		return;
	}

	SetExeList(strUserName, bParty, bGuild);
	pUIManager->RearrangeOrder(UI_SIMPLE_POP, TRUE);

// [KH_070423] ũ�� ����(ȭ���� ���� �� ������ ȭ�鿡 �� �����ʿ� ���δ�)
	if(ixPos + GetWidth() > pUIManager->GetDrawPort()->GetWidth())
		ixPos = pUIManager->GetDrawPort()->GetWidth() - GetWidth();
	if(iyPos + GetHeight() > pUIManager->GetDrawPort()->GetHeight())
		iyPos = pUIManager->GetDrawPort()->GetHeight() - GetHeight();

	SetPos(ixPos, iyPos);
	m_bTarget = true;
	m_nNoTargetCharIndex = -1;
	Show();
}

ENGINE_API void CUISimplePop::OpenPopNoTarget( CTString strName, int nCharIndex, bool bParty, INDEX ixPos, INDEX iyPos )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (strName.IsEmpty() || strName == _pNetwork->MyCharacterInfo.name)
	{
		// ĳ���� �̸��� ���ų�, �ڱ� �ڽ��� ��� ����
		return;
	}

	SetExeListNoTarget(strName, bParty);
	pUIManager->RearrangeOrder(UI_SIMPLE_POP, TRUE);

	// [KH_070423] ũ�� ����(ȭ���� ���� �� ������ ȭ�鿡 �� �����ʿ� ���δ�)
	if(ixPos + GetWidth() > pUIManager->GetDrawPort()->GetWidth())
		ixPos = pUIManager->GetDrawPort()->GetWidth() - GetWidth();
	if(iyPos + GetHeight() > pUIManager->GetDrawPort()->GetHeight())
		iyPos = pUIManager->GetDrawPort()->GetHeight() - GetHeight();

	SetPos(ixPos, iyPos);
	m_bTarget = false;
	m_strNoTargetName = strName;
	m_nNoTargetCharIndex = nCharIndex;
	Show();
}

void CUISimplePop::ClosePop()
{
	CUIManager::getSingleton()->RearrangeOrder( UI_SIMPLE_POP, FALSE );
	Hide();
}

void CUISimplePop::Render()
{
	if( !IsVisible() )
		return;
	if( m_vecString.size() <= 0 )
		return;

	CUIManager* pUIManager = CUIManager::getSingleton();
	CDrawPort* pDrawPort = pUIManager->GetDrawPort();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	pDrawPort->InitTextureData( m_ptdBaseTexture );

	CUITrackPopup::Render();
	m_tpList.Render();	

	pDrawPort->FlushRenderingQueue();
	pDrawPort->EndTextEx();

// [KH_070423] ȭ��ǥ

	if(pInfo->GetTargetType(eTARGET) != MOB && !(pUIManager->IsCSFlagOn(CSF_EXPEDITION)) && m_bTarget == true)
	{
		pDrawPort->InitTextureData( m_ptdMenuTexture );

		INDEX nX = GetPosX() + 80;
		INDEX nY = GetPosY();
		INDEX nLine = 4;

		INDEX nYSpace =((_pUIFontTexMgr->GetLineHeight()+3) - 7)/2 + 2;



		pDrawPort->AddTexture( nX, nY + nYSpace +(_pUIFontTexMgr->GetLineHeight()+2)*nLine,
											nX + 7, nY + nYSpace +(_pUIFontTexMgr->GetLineHeight()+2)*nLine+7,
											m_rtArrow.U0, m_rtArrow.V0, m_rtArrow.U1, m_rtArrow.V1,
											0xFFFFFFFF );

		pDrawPort->FlushRenderingQueue();
	}
	else if (!(pUIManager->IsCSFlagOn(CSF_EXPEDITION)) && m_bTarget == false) // ��Ÿ�� ����� ���
	{
		pDrawPort->InitTextureData( m_ptdMenuTexture );

		INDEX nX = GetPosX() + 80;
		INDEX nY = GetPosY();
		INDEX nLine = 3;

		INDEX nYSpace =((_pUIFontTexMgr->GetLineHeight() + 3) - 7) / 2 + 2;
		
		pDrawPort->AddTexture( nX, nY + nYSpace +(_pUIFontTexMgr->GetLineHeight()+2)*nLine,
			nX + 7, nY + nYSpace +(_pUIFontTexMgr->GetLineHeight()+2)*nLine+7,
			m_rtArrow.U0, m_rtArrow.V0, m_rtArrow.U1, m_rtArrow.V1,
			0xFFFFFFFF );

		pDrawPort->FlushRenderingQueue();
	}

	// [sora] ��� ǥ�� ������ render
	if(m_tpList.IsVisible())
	{
		// command�� ǥ�� �����޴��� �ִٸ� �������� �׷��ش�
		if(m_tpList.GetCommandNum(0) == SPST2_SETLABEL1)
		{
			pDrawPort->InitTextureData(m_ptdExpeditionTexture);
			
			int nPosX = m_tpList.GetAbsPosX() + 6;
			int nPosY = 0;
			for(int i=0; i<LABEL_INDEX_TOTAL; i++)
			{

				nPosY = m_tpList.GetAbsPosY() + (_pUIFontTexMgr->GetLineHeight())*i + 4;
				pDrawPort->AddTexture( nPosX, nPosY, nPosX + 12, nPosY + 12,
													m_rtLabelIcon[i].U0, m_rtLabelIcon[i].V0, m_rtLabelIcon[i].U1, m_rtLabelIcon[i].V1,
													0xFFFFFFFF );

			}

			pDrawPort->FlushRenderingQueue();
		}
	}
}

// Ÿ�پ��� �˾�â ����
void CUISimplePop::SetExeListNoTarget( CTString strUserName, bool bParty)
{
	ResetAllStrings();

	CUIManager* pUIManager = CUIManager::getSingleton();
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (pParty == NULL)
		return;
	
	// �̸�
	AddMenuList(strUserName, C_YELLOW|0xff, SPSO_NAME);
	// �ӼӸ�
	AddMenuList(_S(3355, "�ӼӸ�") + _s("       "), 0xc2bac5FF, SPSO_WHISPER);
	// ģ�����
	AddMenuList(_S(2484, "ģ�����"), 0xc2bac5FF, SPSO_FRIEND);

	if(pUIManager->IsCSFlagOn(CSF_EXPEDITION))
	{
		AddMenuList(_S(4644, "�������û"), 0xc2bac5FF, SPSO_EXPEDITION_INVITE);
	}
	else
	{
		AddMenuList(_S(3357, "��Ƽ��û"), 0xc2bac5FF, SPSO_PARTY);
	}

	if(bParty)
	{
		if(pUIManager->IsCSFlagOn(CSF_PARTY))
		{
			AddMenuList(_S(3358, "��Ƽ ����"), 0xc2bac5FF, SPSO_PARTY_OUT);
			AddMenuList(_S(3359, "��Ƽ�� ����"), 0xc2bac5FF, SPSO_PARTY_JANG);
		}
	}

	if(pParty->GetExpeditionMyPosition() == 0) // MSG_EXPED_MEMBERTYPE_BOSS = 0
	{
		AddMenuList(_S(4645, "������ ����"), 0xc2bac5FF, SPSO_EXPEDITION_KICK);
	}

	if (IsBila(g_iCountry) == TRUE)
	{
		// brazil ��û ���� �˾��� ���� ä�� ����. [3/9/2011 rumist]
		AddMenuList( _S(4458, "ä�� ����"), 0xc2bac5FF, SPSO_MUTE_CHARACTER );
	}

	AddMenuList(_S(4582, "���캸��"), 0xc2bac5FF, SPSO_EXPEDITION_VIEW);

#ifdef ENABLE_ADMIN_KICKBAN
	if (_pNetwork->m_ubGMLevel >= 8)
	{
		AddMenuList(_S(9363, "Kick"), 0xc2bac5FF, SPSO_KICK_PLAYER);
		AddMenuList(_S(9364, "ban_player"), 0xc2bac5FF, SPSO_BAN_PLAYER);
		AddMenuList(_S(9365, "block_player"), 0xc2bac5FF, SPSO_BLOCK_PLAYER);
	}
#endif

	AddMenuList(_S(139, "���"), 0xc2bac5FF, SPSO_CANCEL);

}

//////////////////////////////////////////////////////////////////////////
// [sora] RAID_SYSTEM �˾�â �޴� ����
//////////////////////////////////////////////////////////////////////////
void CUISimplePop::SetExeList(CTString strUserName, BOOL bParty, BOOL bGuild)
{
//	INDEX iListNum = 0;
//	INDEX iExeNum = SPSO_NAME;

	// ������ m_iExeNum �迭�� �ܺο� �����Ǿ��ִ� command���� CUITrackPopup���ο� �����ϵ��� ����
	// (CUITrackPopupŬ���� ����)

	ResetAllStrings();

	CUIManager* pUIManager = CUIManager::getSingleton();
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();
	ObjInfo* pInfo = ObjInfo::getSingleton();

	if (pParty == NULL)
		return;

	AddMenuList(strUserName, C_YELLOW|0xff, SPSO_NAME);
	if(pInfo->GetTargetType(eTARGET) == CHARACTER)
	{
		AddMenuList(_S(3355, "�ӼӸ�") + _s("       "), 0xc2bac5FF, SPSO_WHISPER);
		AddMenuList(_S(2484, "ģ�����"), 0xc2bac5FF, SPSO_FRIEND);
		AddMenuList(_S(3356, "��ȯ��û"), 0xc2bac5FF, SPSO_TRADE);

		if(pUIManager->IsCSFlagOn(CSF_EXPEDITION))
		{
			AddMenuList(_S(4644, "�������û"), 0xc2bac5FF, SPSO_EXPEDITION_INVITE);
		}
		else
		{
			AddMenuList(_S(3357, "��Ƽ��û"), 0xc2bac5FF, SPSO_PARTY);
		}

		if(bParty)
		{
			if(pUIManager->IsCSFlagOn(CSF_PARTY))
			{
				AddMenuList(_S(3358, "��Ƽ ����"), 0xc2bac5FF, SPSO_PARTY_OUT);
				AddMenuList(_S(3359, "��Ƽ�� ����"), 0xc2bac5FF, SPSO_PARTY_JANG);
			}
		}

		if(pParty->GetExpeditionMyPosition() == 0) // MSG_EXPED_MEMBERTYPE_BOSS = 0
		{
			AddMenuList(_S(4645, "������ ����"), 0xc2bac5FF, SPSO_EXPEDITION_KICK);
		}

		AddMenuList(_S(3360, "��尡��"), 0xc2bac5FF, SPSO_GUILD_IN);

		if(bGuild)
		{
			CTString tempString;
			tempString.PrintF("%s", _S(4800, "������� ��û"));
			AddMenuList(tempString, 0xc2bac5FF, SPSO_GUILD_WAR_START);
			tempString.PrintF("%s", _S(4801, "������� �ߴ�"));
			AddMenuList(tempString, 0xc2bac5FF, SPSO_GUILD_WAR_END);
		}

		if (IsBila(g_iCountry) == TRUE)
		{
			// brazil ��û ���� �˾��� ���� ä�� ����. [3/9/2011 rumist]
			AddMenuList( _S(4458, "ä�� ����"), 0xc2bac5FF, SPSO_MUTE_CHARACTER );
		}

		AddMenuList(_S(4582, "���캸��"), 0xc2bac5FF, SPSO_EXPEDITION_VIEW);
#ifdef ENABLE_ADMIN_KICKBAN
		if (_pNetwork->m_ubGMLevel >= 8)
		{
			AddMenuList(_S(9366, "Kick"), 0xc2bac5FF, SPSO_KICK_PLAYER);
			AddMenuList(_S(9367, "Ban"), 0xc2bac5FF, SPSO_BAN_PLAYER);
			AddMenuList(_S(9368, "Block"), 0xc2bac5FF, SPSO_BLOCK_PLAYER);
		}
#endif

	}

	if(pUIManager->IsCSFlagOn(CSF_EXPEDITION))
	{

		if(pParty->GetExpeditionMyPosition() == 0 || pParty->GetExpeditionMyPosition() == 1)
		{	
			// [sora] MSG_EXPED_MEMBERTYPE_BOSS = 0, MSG_EXPED_MEMBERTYPE_MBOSS = 1 ���� ����� �δ��常 ǥ������ ����
			int isLabeled = -1;
			if(pInfo->GetTargetEntity(eTARGET)) // Ÿ���� ������ ������츸 ǥ��
			{
				isLabeled = pParty->IsLabeled(pInfo->GetTargetType(eTARGET), pInfo->GetTargetServerIdx(eTARGET));

				if(isLabeled >= 0)
				{
					AddMenuList(_S(4646,"ǥ������"), 0xc2bac5FF, SPSO_RESETLABEL);	
					
				}
				
				AddMenuList(_S(4647,"���ǥ��"), 0xc2bac5FF, SPSO_SETLABEL);	
			}
		}

	}


	AddMenuList(_S(139,  "���"), 0xc2bac5FF, SPSO_CANCEL);
}

//////////////////////////////////////////////////////////////////////////
// [sora] RAID_SYSTEM �˾�â ����޴� ����
//////////////////////////////////////////////////////////////////////////
void CUISimplePop::SetSubExeList(INDEX iCommandNum )
{
	m_tpList.ResetAllStrings();

	switch(iCommandNum)
	{
		case SPSO_PARTY:
		{
			m_tpList.AddMenuList(_S(3354, "�Ϲ�"), 0xc2bac5FF, SPST_PARTY_JOIN_A);
//#ifndef DISABLE_PARTY_TYPE_BATTLE	// [2010/07/12 : Sora] ������ ��Ƽ ����
			extern INDEX g_iCountry;

			if (IsGamigo(g_iCountry) == FALSE)
				m_tpList.AddMenuList(_S(2665, "���� ��"), 0xc2bac5FF, SPST_PARTY_JOIN_C);
//#endif
		}
			break;

		case SPSO_SETLABEL:
		{
			CTString iconTerm = CTString("   ");
			m_tpList.AddMenuList(iconTerm + _S(4648, "ǥ��:����"), 0xc2bac5FF, SPST2_SETLABEL1);
			m_tpList.AddMenuList(iconTerm + _S(4649, "ǥ��:����"), 0xc2bac5FF, SPST2_SETLABEL2);
			m_tpList.AddMenuList(iconTerm + _S(4650, "ǥ��:�߹ٴ�"), 0xc2bac5FF, SPST2_SETLABEL3);
			m_tpList.AddMenuList(iconTerm + _S(4651, "ǥ��:����Į"), 0xc2bac5FF, SPST2_SETLABEL4);
			m_tpList.AddMenuList(iconTerm + _S(4652, "ǥ��:��"), 0xc2bac5FF, SPST2_SETLABEL5);
			m_tpList.AddMenuList(iconTerm + _S(4653, "ǥ��:�Ǹ�"), 0xc2bac5FF, SPST2_SETLABEL6);
			m_tpList.AddMenuList(iconTerm + _S(4654, "ǥ��:�ذ�"), 0xc2bac5FF, SPST2_SETLABEL7);

		}
			break;

		default:
			break;
	}

}

//////////////////////////////////////////////////////////////////////////
// [sora] RAID_SYSTEM �˾�â �޴� ����
//////////////////////////////////////////////////////////////////////////
void CUISimplePop::Execution(INDEX exeNum)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	Party* pParty = GAMEDATAMGR()->GetPartyInfo();
	ObjInfo* pInfo = ObjInfo::getSingleton();
	CTString	strCharName;
	switch(exeNum)
	{
	case SPSO_NAME:
		NOTHING;
		break;
	case SPSO_WHISPER:
		{
			CTString tempInput;

			ClosePop();		// [KH_070424] �ӼӸ��� ä��â ��Ŀ���� ������ �̸� ������

			if (m_bTarget == true)
				tempInput.PrintF("!%s ", pInfo->GetTargetName(eTARGET));
			else
				tempInput.PrintF("!%s ", m_strNoTargetName);

			pUIManager->GetChattingUI()->SetInputString(tempInput);
		}
		break;
	case SPSO_FRIEND:
		{
			if (m_bTarget == true)
				pUIManager->GetMessenger()->MsgBoxCommand( MSGCMD_MESSENGER_ADD_REQ, TRUE, CTString(pInfo->GetTargetName(eTARGET)) );
			else
				pUIManager->GetMessenger()->MsgBoxCommand( MSGCMD_MESSENGER_ADD_REQ, TRUE, m_strNoTargetName );
		}
		break;
	case SPSO_KICK:
		char szCommand[512];
		sprintf(szCommand, "kick %s", m_strNick.str_String);
		_pNetwork->SendGMCommand((const char*)szCommand);
		break;
	case SPSO_TRADE:
		pUIManager->GetCharacterInfo()->UseAction( 5 );
		break;
	case SPSO_PARTY:
		NOTHING;
		break;
	case SPSO_PARTY_OUT:
		{
			if (m_bTarget == true)
				pUIManager->GetCharacterInfo()->UseAction( 12 );
			else
				pParty->SendPartyKick(m_strNoTargetName);
		}
		
		break;
	case SPSO_PARTY_JANG:
		{
			if (m_bTarget == true)
				pUIManager->GetCharacterInfo()->UseAction( 39 );
			else
				pParty->MandateBossReq(m_strNoTargetName);
		}
		break;
	case SPSO_GUILD_IN:
		pUIManager->GetCharacterInfo()->UseAction( 24 );
		break;
	case SPSO_GUILD_WAR_START:
		pUIManager->GetCharacterInfo()->UseAction( 31 );
		break;
	case SPSO_GUILD_WAR_END:
		pUIManager->GetCharacterInfo()->UseAction( 32 );
		break;

	case SPSO_EXPEDITION_INVITE:
		{
			if (m_bTarget == true)
				pParty->SendExpeditionInvite(CTString(pInfo->GetTargetName(eTARGET)));
			else
				pParty->SendExpeditionInviteReq(m_nNoTargetCharIndex, m_strNoTargetName);
		}
		break;
	case SPSO_CANCEL:
		NOTHING;
		break;
	case SPSO_END:
		ASSERTALWAYS("�̰��� ������ �ȵǴ� �̴ϴ�.");
		break;

	case SPST_PARTY_JOIN_A:
		{
			if (m_bTarget == true)
				pUIManager->GetCharacterInfo()->UseAction( 6 );
			else
			{
				if (m_nNoTargetCharIndex == _pNetwork->MyCharacterInfo.index)
					return;

				pParty->SendPartyInviteReq( PT_PEACEEVER, m_nNoTargetCharIndex, m_strNoTargetName );
			}
		}
		break;
	case SPST_PARTY_JOIN_B:
		{
			if (m_bTarget == true)
				pUIManager->GetCharacterInfo()->UseAction( 7 );
			else
			{
				if (m_nNoTargetCharIndex == _pNetwork->MyCharacterInfo.index)
					return;

				pParty->SendPartyInviteReq( PT_SURVIVAL, m_nNoTargetCharIndex, m_strNoTargetName );
			}
		}
		break;
	case SPST_PARTY_JOIN_C:
		{
			if (m_bTarget == true)
				pUIManager->GetCharacterInfo()->UseAction( 8 );
			else
			{
				if (m_nNoTargetCharIndex == _pNetwork->MyCharacterInfo.index)
					return;

				pParty->SendPartyInviteReq( PT_ATTACK, m_nNoTargetCharIndex, m_strNoTargetName );
			}
		}
		break;

	case SPSO_RESETLABEL:	// ǥ�� ����
	{
		pParty->SendTargetLabelReSet(pInfo->GetTargetType(eTARGET), pInfo->GetTargetServerIdx(eTARGET));
	}
		break;

	case SPST2_SETLABEL1:
	case SPST2_SETLABEL2:
	case SPST2_SETLABEL3:
	case SPST2_SETLABEL4:
	case SPST2_SETLABEL5:
	case SPST2_SETLABEL6:
	case SPST2_SETLABEL7:
	{
		// ǥ�� ����
		SLONG slLabelIndex = exeNum -  SPST2_START;

		pParty->SendTargetLabelSet(pInfo->GetTargetType(eTARGET), pInfo->GetTargetServerIdx(eTARGET), slLabelIndex);
	}
		break;

	case SPSO_EXPEDITION_KICK:
	{
		//���� �޽����ڽ��� ������ �ݾ��ش�
		if(pUIManager->DoesMessageBoxExist(MSGCMD_EXPEDITION_KICK))
			pUIManager->CloseMessageBox(MSGCMD_EXPEDITION_KICK);

		CTString strMessage;
		SLONG slIndex = 0;
		
		if (m_bTarget == true)
			slIndex = pParty->GetExpeditionMemberIndex(pInfo->GetTargetName(eTARGET));
		else
			slIndex = pParty->GetExpeditionMemberIndex(m_strNoTargetName);

		if(slIndex >= 0)
		{	
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo( _S(4493, "������" ), UMBS_YESNO, UI_PARTY, MSGCMD_EXPEDITION_KICK );
			
			if (m_bTarget == true)
				strMessage.PrintF( _S(4655, "%s���� �߹��Ͻðڽ��ϱ�?" ), pInfo->GetTargetName(eTARGET) );
			else
				strMessage.PrintF( _S(4655, "%s���� �߹��Ͻðڽ��ϱ�?" ), m_strNoTargetName );			

			pUIManager->GetExpedition()->SetSelectIndex(slIndex);
				
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
	}
		break;
	case SPSO_MUTE_CHARACTER:
		{
			if (m_bTarget == true)
				pUIManager->GetChatFilter()->CharacterFilterInSimplePopup( pInfo->GetTargetName(eTARGET) );
			else
				pUIManager->GetChatFilter()->CharacterFilterInSimplePopup( m_strNoTargetName );
		}
		break;
	case SPSO_EXPEDITION_VIEW: //dethunter13
		 if (pInfo->GetTargetType(eTARGET) == CHARACTER)
		strCharName = pInfo->GetTargetName(eTARGET);
		
		UIMGR()->GetExpeditionView()->SetCharInfo(strCharName, 0);
		_pNetwork->ExpeditionViewDetailReq(-1, pInfo->GetTargetServerIdx(eTARGET));
		break;
#ifdef ENABLE_ADMIN_KICKBAN
	case SPSO_KICK_PLAYER:
	{
		char szCommand[512];
		sprintf(szCommand, "kick %s", pInfo->GetTargetName(eTARGET));
		_pNetwork->SendGMCommand((const char*)szCommand);
	}
	break;
	case SPSO_BAN_PLAYER:
	{
		char szCommand[512];
		sprintf(szCommand, "ban_player %s", pInfo->GetTargetName(eTARGET));
		_pNetwork->SendGMCommand((const char*)szCommand);
	}
	break;
	case SPSO_BLOCK_PLAYER:
	{
		char szCommand[512];
		sprintf(szCommand, "block_player %s", pInfo->GetTargetName(eTARGET));
		_pNetwork->SendGMCommand((const char*)szCommand);
	}
	break;
#endif

	default:
		ASSERTALWAYS("�̰��� ������ �ȵǴ� �̴ϴ�.");
		break;
	}
}

WMSG_RESULT	CUISimplePop::MouseMessage(MSG *pMsg)
{
	static int	nOldX, nOldY;
	
	if( !IsEnabled() )
		return WMSG_FAIL;

	// Mouse point
	int	nX = LOWORD( pMsg->lParam );
	int	nY = HIWORD( pMsg->lParam );

	// Mouse message
	if(pMsg->message == WM_LBUTTONUP)
	{
		INDEX iExeNum = SPSO_END;
		if( m_tpList.MouseMessage( pMsg ) != WMSG_FAIL )
		{
			// [sora] ����޴� �޽��� ó��
			iExeNum = m_tpList.GetCommandNum(m_tpList.GetCurSel());

			Execution(iExeNum);
			
			m_tpList.Hide();
			ClosePop();

			return WMSG_SUCCESS;
		}
		if( CUITrackPopup::MouseMessage( pMsg ) != WMSG_FAIL )
		{
			// [sora] ���θ޴� �޽��� ó��
			iExeNum = GetCommandNum(GetCurSel());
			m_tpList.Hide();

			Execution(iExeNum);

			if(iExeNum != SPSO_NAME && iExeNum != SPSO_PARTY && iExeNum != SPSO_WHISPER)
				ClosePop();

			return WMSG_SUCCESS;
		}
		else
		{
			ClosePop();
			if(m_tpList.IsEnabled())
				m_tpList.Hide();
		}

	}
	else if(pMsg->message == WM_MOUSEMOVE )
	{	// [KH_070423] m_tpList.MouseMessage �� ������ ���ϸ� ����ǥ�ð� �ȵǹǷ� ���ִ� ���̴�. (if �������� �� ��� ����)
		
		// [sora] ����޴� �޽��� ó��
		if(m_tpList.MouseMessage( pMsg ) != WMSG_FAIL )
		{
			return WMSG_SUCCESS;
		}

		WMSG_RESULT wmsg = CUITrackPopup::MouseMessage(pMsg);
		if(wmsg != WMSG_FAIL)
		{
			// [sora] ���θ޴� �޽��� ó��
			if(GetCommandNum(GetCurSel()) == SPSO_PARTY || GetCommandNum(GetCurSel()) == SPSO_SETLABEL)
			{
				SetSubExeList(GetCommandNum(GetCurSel()));

				int PosX = GetWidth() - 3;
				int PosY = (_pUIFontTexMgr->GetLineHeight()+2)*GetCurSel();

				CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

				// [KH_070423] ũ����� �߰�
				if(GetPosX() + GetWidth() + m_tpList.GetWidth() > pDrawPort->GetWidth())
					PosX = 3 - m_tpList.GetWidth();

				m_tpList.SetPos( PosX, PosY );
				m_tpList.Show();
			}
		}

		return wmsg;
	}
	else
	{
		// [sora] ����޴� �޽��� ó��
		if (pMsg->message != WM_LBUTTONDOWN)
			m_tpList.Hide();

		WMSG_RESULT wmsg = m_tpList.MouseMessage(pMsg);
		
		if (wmsg != WMSG_FAIL)
			return wmsg;

		return CUITrackPopup::MouseMessage(pMsg); 
	}

	return WMSG_FAIL;
}
