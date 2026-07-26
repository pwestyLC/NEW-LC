
#include "StdH.h"
#include <Engine/Network/CNetwork.h>
#include <Engine/Interface/UIManager.h>
#include "SessionState.h"
#include <Engine/Interface/UISelectWord.h>
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIProcess.h>
#include <Engine/Interface/UIGamble.h>
#include <Engine/Contents/Base/UIChangeWeaponNew.h>
#include <Engine/Contents/Base/UIQuestNew.h>
#include <Engine/Interface/UISelectList.h>
#include <Engine/Contents/function/InsectCollectUI.h>
#include <Engine/Interface/UIOXQuizEvent.h>
#include <Engine/Interface/UIAutoHelp.h>
#include <Engine/Contents/function/BingoBoxUI.h>
#include <Engine/Interface/UIMinigame.h>
#include <Engine/Interface/UIFlowerTree.h>
#include <Engine/Ska/Render.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/GameDataManager/GameDataManager.h>
#include <Engine/Contents/Base/UINoticeNew.h>
#include <Engine/Contents/Base/Notice.h>
#include <Engine/Contents/Login/ServerSelect.h>
#include <Engine/Contents/Login/UIServerSelect.h>

// ���� ���ڿ��� �����ϴ� ������ ����
#define TREASUREBOX_ITEM_COUNT	3

int GuildMasterErrChk(SBYTE errType)
{
	CTString strMessage;
	BOOL nResult = FALSE;
	switch(errType)
	{
	case MSG_ERROR_PARENTSDAY_2007_FULLINVEN:
		strMessage =_S( 265, "�κ��丮 ������ �����մϴ�.");
		break;
	case MSG_ERROR_PARENTSDAY_2007_NO_EXCHAGNE_ITEM:
		strMessage =_S( 2236, "�̺�Ʈ �������� �������� �ʽ��ϴ�.");
		break;		
	case MSG_ERROR_PARENTSDAY_2007_NOT_GUILD_OWNER:
		strMessage =_S(3470,"��� �����Ͱ� �ƴմϴ�.");
		break;
	case MSG_ERROR_ACCUMULATEPOINT_NOT_RANKING:
		strMessage =_S(3471, "��ŷ �����Ͱ� �����ϴ�.");
		break;

	case MSG_ERROR_ADD_POINT:					
		strMessage =_S(3472,"����Ʈ�� �������� ���߽��ϴ�.");
		break;
	case MSG_ERROR_NOT_ENOUGH_POINT:
		strMessage =_S(3473, "����Ʈ�� ���� �մϴ�.");
		break;
	case MSG_ERROR_NOT_FOUND_ACCUMULATEPOINT_LIST:
		strMessage =_S(3474, "���� ����Ʈ ������ �����ϴ�.");
		break;
	case MSG_ERROR_PARENTSDAY_2007_ERROR_NOITEM :
		strMessage =_S(3475,"��ȯ���� �������� �ʽ��ϴ�.");
		break;
	case MSG_PARENTSDAY_2007_SUCCESS:
		return TRUE;
	default :
		nResult = TRUE;
		break;
	}
	if(strMessage.str_String!=NULL)
		_pNetwork->ClientSystemMessage(strMessage,SYSMSG_ERROR);

	return nResult;
}

int EasterEggs2007ErrChk(ULONG errType)
{
	CTString strMessage;
	BOOL nResult = FALSE;
	switch(errType)
	{
	case MSG_EVENT_EGGS_HUNT_2007_GIFT_REP_OK:
		nResult = TRUE;
		break;
	case MSG_EVENT_EGGS_HUNT_2007_ERROR_ALREADY_EXIST:
		strMessage =_S( 3265, "1�� �̻��� ��Ȱ�� �ް��� ������ �� �����ϴ�.");
		break;
	case MSG_EVENT_EGGS_HUNT_2007_ERROR_GIFT_FULLINVEN:
		strMessage =_S( 265, "�κ��丮 ������ �����մϴ�.");
		break;
	case MSG_EVENT_EGGS_HUNT_2007_ERROR_NOITEM:
		strMessage =_S( 3257, "��û�� �۾��� ���� �Ͽ����ϴ�.");
		break;
	}

	_pNetwork->ClientSystemMessage(strMessage);
	return nResult;

}

int Whiteday2007ErrChk(ULONG errType)
{
	CTString strMessage;
	BOOL nResult = FALSE;
	switch(errType)
	{
	case MSG_EVENT_WHITEDAY_2007_EXCHANGE_OK:
		//  ������ �޽��� ����� �ʿ� ������ ����...
		//	strMessage =_s( "��û�� �۾��� �Ϸ� �Ǿ����ϴ�.");
		nResult = TRUE;
		break;
	case MSG_EVENT_WHITEDAY_2007_EXCHANGE_FAILED:
		strMessage =_S( 3257, "��û�� �۾��� ���� �Ͽ����ϴ�.");
		break;
	case MSG_EVENT_WHITEDAY_2007_EXCHANGE_NOITEM:
		strMessage =_S( 3258, "������ �ޱ� ���� ������ ������ �����մϴ�.");
		break;		
	case MSG_EVENT_WHITEDAY_2007_EXCHANGE_FULLINVEN:
		strMessage =_S( 265, "�κ��丮 ������ �����մϴ�.");
		break;
	case MSG_EVENT_WHITEDAY_2007_EXCHANGE_MAXITEM:
		strMessage =_S( 3260, "�������� �ִ� 5������ ������ �� �ֽ��ϴ�.");
		break;
	}

	_pNetwork->ClientSystemMessage(strMessage);
	return nResult;

}

int WorldCupErrChk(ULONG errType) 		
{
	CTString strMessage;
	BOOL nResult = FALSE;
	switch(errType)
	{
	case MSG_EVENT_WORLDCUP_ERROR_VOTE_OK :			// �¸� ���� ���� : ����
		strMessage =_S( 2835, "������� ������ ������ ����� ��ȯ�Ǿ����ϴ�.");
		nResult = TRUE;
		break;
	case MSG_EVENT_WORLDCUP_ERROR_VOTE_NOITEM :		// �¸� ���� ���� : FIFA �� ����
		strMessage =_S( 2836, "������� �����մϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_VOTE_NOTCHANGE :	// �¸� ���� ���� : ���� �Ⱓ �ƴ�
		strMessage =_S( 2837, "����� ��ȯ�Ⱓ�� �ƴմϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_VOTE_FULLINVEN :	// �¸� ���� ���� : �κ� ���� ����
		strMessage =_S( 2838, "�¸� ���� ���� : �κ� ������ �����մϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_VOTE_ALREADY :		// �¸� ���� ���� : �̹� ������ ����
		strMessage =_S( 2839, "�¸� ���� ���� ��÷ Ȯ�� : �̹� ������ �����Դϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_GIFT_OK :			// �¸� ���� ���� ��÷ Ȯ�� : ���� ����
		strMessage =_S( 2840, "��±��� ���߱� �̺�Ʈ ����ǰ�� ��� ���޵Ǿ����ϴ�. ������ �ּż� �����մϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_GIFT_NOTCHANGE :	// �¸� ���� ���� ��÷ Ȯ�� : ��ȯ �Ⱓ �ƴ�
		strMessage =_S( 2841, "����Ⱓ�� �ƴմϴ�. �������� ����� ���Ŀ� Ȯ���Ͻñ� �ٶ��ϴ�.");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_GIFT_NOITEM :		// �¸� ���� ���� ��÷ Ȯ�� : ���� ������ ����
		strMessage =_S( 2842, "�ش� ������ ���⸦ ������ ���� �ʽ��ϴ�. �ٽ� Ȯ���� �ּ���");
		break;
	case MSG_EVENT_WORLDCUP_ERROR_GIFT_FULLINVEN :	// �¸� ���� ���� ��÷ Ȯ�� : �κ� ���� ����
		strMessage =_S( 2843, "�¸� ���� ���� ��÷ Ȯ�� : �κ������� �����մϴ�.");
		break;

	}
	_pNetwork->ClientSystemMessage(strMessage);
	return nResult;
}

//wooss 060201 inner Function
void FindFriendErrChk1(ULONG errType) 		
{
	CTString strMessage;

	switch(errType)
	{
	case MSG_EVENT_SEARCHFRIEND_ERROR_OK :				 //����.(ģ�����OK, ���� OK)
		strMessage=_S( 2495, "ģ����Ͽ� �����Ͽ����ϴ�.");
		CUIManager::getSingleton()->GetSelectList()->ResetSelectList();
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_PACKET :			 //��Ŷ����
		strMessage =_S(854,"��Ŷ ������ �߻��Ͽ����ϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_NOT_EXIST :			 //�������� �ʴ´�.
		strMessage =_S(11, "�������� �ʴ� ĳ���� �Դϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_FULLMEMBER :		 //ģ�� ���� �ʰ�.
		strMessage =_S( 2496, "����ο��� �ʰ� �Ǿ����ϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_ALREADY_EXIST :		 //�̹� ģ������Ʈ�� ����.
		strMessage =_S( 2497, "�̹� ��ϵ� ģ���Դϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_NOT_MATCH_INDEX :	 //���ΰ�  ��û,���� ���̵� ��ġ�ϸ� �ȵ�.
		strMessage = _S( 2498, "���� ������ ĳ���ʹ� ����� �� �����ϴ�.  ");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_HELPER_SERVER :		 //���ۼ������� ���ӿ���.
		strMessage = _S(2133,"���ۼ��� ���� �Դϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_GAMESERVER :		 //�Ⱓ�� ������.
		strMessage = _S( 2499, "�Ѵ� �̻� ���ӿ� ������ �� �� ĳ���͸� ����� �����մϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_ERROR_FRIENDNAME :		 //�̸��� �߸��Ǿ���.
		strMessage = _S( 2500, "�߸��� �̸��Դϴ�.");
		break;							
	}
	_pNetwork->ClientSystemMessage(strMessage);
}

void FindFriendErrChk2(ULONG errType) 		
{
	CTString strMessage;

	switch(errType)
	{
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_OK :				// ���� ����
		{
			CUIManager* pUIManager = CUIManager::getSingleton();

			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage;
			strSysMessage = _S(1840,"�������� ���������� ���޵Ǿ����ϴ�.");
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 169, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

			strMessage = CTString("");
			pUIManager->GetSelectList()->ResetSelectList();
		}
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_TIME :			// ���� ���� : �ð� ����
		strMessage = _S( 2501, "�ð��� �����մϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_END :				// ���� ���� : �Ⱓ �ƴ�
		strMessage = _S(945,"������ �̺�Ʈ �Ⱓ�� �ƴմϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_SOMEREMAIN :		// ���� ����, �Ϻ� ������ ������
		strMessage = _S(2235,"�̺�Ʈ �������� �Ϻ� ���� �޾ҽ��ϴ�.");
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_NOGOODS :			// ���� ����, ���� ������ ����
		strMessage = _S( 2502,"���� ���� �������� �����ϴ�." );
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_ERROR_NOSPACE :			// ���� ���� : ������ ĭ�� ���ڸ�.
		strMessage = _S(116,"�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�.");
		break;
	}
	_pNetwork->ClientSystemMessage(strMessage);
}

void CSessionState::ReceiveEventMessage(CNetworkMessage *istr)
{
	UBYTE	ubType;
	(*istr) >> ubType;	

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(ubType)
	{
	case MSG_EVENT_2PAN4PAN_LETTER:
		{
			LONG lError;
			(*istr) >> lError;

			pUIManager->GetSelectWord()->ResultProcess( lError );

		}
		break;
	case MSG_EVENT_ERROR:
		{
			SBYTE	sbError;
			(*istr) >> sbError;

			_pNetwork->m_iLastError = sbError;
			CTString strMessage;
			switch(sbError)
			{
			case MSG_EVENT_ERROR_ALREADY_GIVE:
				strMessage.PrintF( _S( 673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�." ) );		
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_INSUFF_CONDITION:
				strMessage.PrintF( _S( 674, "�̺�Ʈ �������� ���� �� �����ϴ�." ) );			
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_FULLINVENTORY:
				strMessage.PrintF( _S( 675, "�κ��丮 ������ �����ؼ� �̺�Ʈ �������� ���� �� �����ϴ�." ) );		
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_WRONG_PACKET:
				strMessage.PrintF( _S( 1341, "�߸��� ��Ŷ�Դϴ�." ) );				
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_NO_MATCH:
				strMessage.PrintF( _S( 1342, "���� ������ �������� �����ϴ�." ) );		
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_CANT_OPTION:
				strMessage.PrintF( _S( 1343, "������ �ɼ��� �ű� �� �����ϴ�." ) );	
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_CHUSEOK_NO_CROP:
				strMessage.PrintF( _S( 1879, "�۹��� �����ϴ�." ) );	
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;

			case MSG_EVENT_ERROR_CHUSEOK_NO_SOIL:
#if defined (G_THAI)
				ULONG	tv_index;
				(*istr) >> tv_index;
				strMessage.PrintF( _S( 1880, "�۹��� ���׷��̵� �ϱ� ���ؼ��� [%s] 10���� �ʿ��մϴ�." ), 
					CItemData::getData(tv_index)->GetName());	
#else	// else about (G_THAI)
				strMessage.PrintF( _S( 1880, "�۹��� ���׷��̵� �ϱ� ���ؼ��� '�����'�� �ʿ��մϴ�." ) );	
#endif	// end (G_THAI)
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;

			case MSG_EVENT_ERROR_CHUSEOK_ALREADY_UPGRADE:
				strMessage.PrintF( _S( 1881, "�̹� �۹��� ���׷��̵� �����ܰ��� ���Ŵܰ���� �����ϼ̽��ϴ�. ����ǰ���� ��ȯ�Ͻʽÿ�." ) );	
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_CHUSEOK_UPGRADE_OK:
				strMessage.PrintF( _S( 1882, "�۹� ���׷��̵忡 �����Ͽ����ϴ�." ) );	
				break;
			case MSG_EVENT_ERROR_CHUSEOK_UPGRADE_FAIL:
				strMessage.PrintF( _S( 1883, "�۹� ���׷��̵忡 �����Ͽ����ϴ�." ) );	
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				break;
			case MSG_EVENT_ERROR_CHUSEOK_EXCHANGE_OK:
				strMessage.PrintF( _S( 1884, "�߼� �̺�Ʈ ����ǰ�� ���޵Ǿ����ϴ�. �̺�Ʈ�� ������ �ּż� �����մϴ�." ) );	
				//	_pNetwork->ClientSystemMessage( strMessage );
				break;

				// 060118 wooss japan package item...
			case MSG_EVENT_ERROR_NOT_COUPON :					// ��Ű�� ������ ����, ���� �ø���
				strMessage.PrintF( _S( 2405, "��û�� ���� ��ȣ�� �������� �ʽ��ϴ�." ) );	
				break;

			case MSG_EVENT_ERROR_ALREADY_USE_COUNPON :		// ��Ű�� ������ ����, �̹� ���� ���� ����
				strMessage.PrintF( _S( 2406, "�̹� ���޹��� ���� ��ȣ �Դϴ�." ) );	
				break;

			case MSG_EVENT_ERROR_COUPON_SUCCESS :				// ��Ű�� ������ ����, ���� ����
				strMessage.PrintF( _S( 1840, "�������� ���������� ���� �Ǿ����ϴ�" ) );	
				break;		
			case MSG_EVENT_ERROR_SAKURABUD_SUCCESS: // 060322 eons �Ϻ� �����ǻ� ��ȯ �̺�Ʈ
				strMessage.PrintF( _S( 2545, "���� ���츮 ��ȯ �������� ���������� ���� �Ǿ����ϴ�." ) );
				break;
			case MSG_EVENT_ERROR_SAKURABUD_LEAKITEM: // 060322 eons
				strMessage.PrintF( _S( 2546, "���� ���츮�� �����մϴ�. Ȯ�� �� �ٽ� �õ��� �ּ���." ) );
				break;

			case MSG_EVENT_ERROR_SEPTEMBER_NAS:
				{
					strMessage.PrintF( _S( 2073, "���� ��÷(����)" ) );	
					//_pNetwork->ClientSystemMessage( strMessage );

					CEntity* penEntity = CEntity::GetPlayerEntity(0);
					StartEffectGroup( "UpSkill", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}
				return;
			case MSG_EVENT_ERROR_SEPTEMBER_DROP:
				{
					strMessage.PrintF( _S( 2074, "����� ��÷(����)" ) );	
					//	_pNetwork->ClientSystemMessage( strMessage );

					CEntity* penEntity = CEntity::GetPlayerEntity(0);
					StartEffectGroup( "UpSkill", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}
				return;
			case MSG_EVENT_ERROR_SEPTEMBER_EXP:
				{	
					strMessage.PrintF( _S( 2075, "����ġ ��÷(����)" ) );	
					//	_pNetwork->ClientSystemMessage( strMessage );

					CEntity* penEntity = CEntity::GetPlayerEntity(0);
					StartEffectGroup( "UpSkill", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}
				return;
			case MSG_EVENT_ERROR_SEPTEMBER_SP:
				{
					strMessage.PrintF( _S( 2076, "���õ� ��÷(����)" ) );	
					//	_pNetwork->ClientSystemMessage( strMessage );

					CEntity* penEntity = CEntity::GetPlayerEntity(0);
					StartEffectGroup( "UpSkill", &penEntity->en_pmiModelInstance->m_tmSkaTagManager, _pTimer->GetLerpedCurrentTick());
				}
				return;
			case MSG_EVENT_AKAN_TEMPLE_ERROR_NO_ITEM:
				{
					strMessage.PrintF(_S(5099, "��ȯ ������ �������� �����ϴ�."));
				}
				break;
			case MSG_EVENT_AKAN_TEMPLE_ERROR_LACK_ITEM:
				{
					strMessage.PrintF(_S(5100, "��ȯ ������ �������� �����մϴ�."));
				}
				break;

			case MSG_EVENT_ERROR_LOI_KRATHONG_NO_ITEM:
				{
					strMessage.PrintF(_S(5100, "��ȯ ������ �������� �����մϴ�."));
				}
				break;

			case MSG_EVENT_ERROR_KB_NO_ITEM:	// [2011/11/14 : Sora] �±� ���� ź���� �̺�Ʈ
				{
					UCHAR	ucCommand;
					(*istr) >> ucCommand;
					if( ucCommand == 0 )	// ��Ʈ ������
						strMessage.PrintF( _S(5606, "��Ʈ�� �����ϴ�. Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�." ) );
					else					// ucCommand == 1 Father Flag ������
						strMessage.PrintF( _S(5607, "Father Flag �������� �����ϴ�. Ȯ�� �� �ٽ� �õ��Ͽ� �ֽʽÿ�." ) );
				}
				break;
			}			

			CUIMsgBox_Info	MsgBoxInfo;	
			MsgBoxInfo.SetMsgBoxInfo( _S( 585, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_EVENT_PRIZE);		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSG_EVENT_PREOPEN_GIFT:
		{
			SLONG slIndex;
			(*istr) >> slIndex;

			pUIManager->CloseMessageBox(MSGCMD_EVENT_PRIZE);
			CTString		strMessage;
			CUIMsgBox_Info	MsgBoxInfo;	
			MsgBoxInfo.SetMsgBoxInfo( _S( 585, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_EVENT_PRIZE);		
			//CItemData& ID = _pNetwork->GetItemData(slIndex);
			strMessage.PrintF( _S( 676, "[%s] �̺�Ʈ �������� ������ϴ�." ), _pNetwork->GetItemName(slIndex) );	
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
		// Date : 2005-01-28,   By Lee Ki-hwan
	case MSG_EVENT_LATTO:
		{
			unsigned char ucIndex;
			(*istr) >> ucIndex;

			CTString		strMessage;

			switch ( ucIndex )
			{
			case MSG_EVENT_LATTO_UPGRADE_SUCCESS: // "��þƮ ���� ��� ������ +2�� ��÷ �Ǿ����ϴ�"
				strMessage = "��þƮ ���� ��� ������ +2�� ��÷ �Ǿ����ϴ�";
				pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_UPGRADE_ITEM  );
				break;
			case MSG_EVENT_LATTO_BLOOD_SUCCESS:	// "������ ���� ��� ������ �ɼǿ� ��÷ �Ǿ����ϴ�"
				strMessage = "������ ���� ��� ������ �ɼǿ� ��÷ �Ǿ����ϴ�";
				pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_BLOOD_OPTION  );
				break;
			case MSG_EVENT_LATTO_PROCESS_SUCCESS:// "���� ���� ��� �����ۿ� ��÷ �Ǿ����ϴ�"
				strMessage = "���� ���� ��� �����ۿ� ��÷ �Ǿ����ϴ�";
				pUIManager->GetInventory()->Lock( FALSE, FALSE, LOCK_PROCESS  );
				// ����â �ݱ� 
				pUIManager->GetProcess()->CloseProcess();
				break;	
			case MSG_EVENT_LATTO_EXPSP_SUCCESS:	// "���� ���� ��� (����ġ *%: ���õ� *)�� ��÷ �Ǿ����ϴ�" : exp(n) sp(n)
				{
					SLONG Exp; //1013
					SLONG Sp;

					(*istr) >> Exp;
					(*istr) >> Sp;
					strMessage.PrintF ( "���� ���� ��� (����ġ %ld%%, ���õ� %ld)�� ��÷ �Ǿ����ϴ�", Exp, Sp );
				}
				break;

			case MSG_EVENT_LATTO_PARTY_SUCCESS:	// "��Ƽ ���� ��� ������ ���ָӴϿ� ��÷ �Ǿ����ϴ�" : �ý��� â���� msg ó��
				{
					strMessage = "��Ƽ ���� ��� ������ ���ָӴϿ� ��÷ �Ǿ����ϴ�";
					pUIManager->GetChattingUI()->AddSysMessage( strMessage );
					return;
				}
				break;


			case MSG_EVENT_LATTO_CHANGE_LUCKYBAG_REP : 	// ���ָӴ� ��ȯ ����		: type (c)
				{
					UBYTE	ubType;
					(*istr) >> ubType;

					switch ( ubType )
					{
					case MSG_CHANGE_26LEVEL_GENERAL_STONE:			// 26���� �Ϲ� ���ü�
						strMessage = "26���� �Ϲ� ���ü��� ������ϴ�.";
						break;
					case MSG_CHANGE_SPECIAL_STONE:					// �������ü�
						strMessage = "���� ���ü��� ������ϴ�.";	
						break;
					case MSG_CHANGE_22LEVEL_EVENT_WEAPON:			// 22���� �̺�Ʈ ���� (������)
						strMessage = "22���� �̺�Ʈ ������ ������ϴ�.";
						break;
					case MSG_CHANGE_31LEVEL_ARMOR:					// 31���� �� ���� (������)
						strMessage = "31���� �� ������ ������ϴ�.";
						break;
					case MSG_CHANGE_ATTACK_UP:						// ���ݷ� �����
						strMessage = "���ݷ� ������� ������ϴ�.";
						break;
					case MSG_CHANGE_DEFENSE_UP:						// ���� �����
						strMessage = "���� ������� ������ϴ�.";
						break;
					case MSG_CHANGE_50000NAS:						// 5�� ����
						strMessage = "5�� ������ ������ϴ�.";
						break;
					case MSG_CHANGE_NO_LUCKYBAG:					// ��ȯ�� ���ָӴϰ� ����
						strMessage = "��ȯ�� �� �ָӴϰ� �����ϴ�.";
						break;
					}

				}
				break;
			}

			pUIManager->CloseMessageBox(MSGCMD_EVENT_PRIZE);

			CUIMsgBox_Info	MsgBoxInfo;	
			MsgBoxInfo.SetMsgBoxInfo( _S( 585, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_EVENT_PRIZE);		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}
		break;
	case MSG_EVENT_CHANGEWEAPON:		// ���� ��ü �̺�Ʈ
		{
			LONG lOldIndex;
			LONG lNewIndex;

			(*istr) >> lOldIndex;
			(*istr) >> lNewIndex;

			CTString strOldItem = _pNetwork->GetItemName(lOldIndex);
			CTString strNewItem = _pNetwork->GetItemName(lNewIndex);

			CTString strMessage;
			strMessage.PrintF( _S( 1344, "[%s] ���Ⱑ [%s] ����� ��ü�Ǿ����ϴ�." ), strOldItem, strNewItem );		
			pUIManager->GetChattingUI()->AddSysMessage( strMessage );			
		}
		break;
	case MSG_EVENT_MOONSTONE:				// ������ �̺�Ʈ...
		{
			unsigned char ucIndex;
			(*istr) >> ucIndex;

			switch ( ucIndex )
			{
			case MSG_EVENT_MOONSTONE_START_REP:
				{
					SBYTE sbType;
					LONG lAccumulate;
					(*istr) >> sbType;
					(*istr) >> lAccumulate;
					pUIManager->GetGamble()->SetAccumulate( lAccumulate );
					pUIManager->GetGamble()->ShowGamble();
					pUIManager->SetCSFlagOn( CSF_MOONSTONE );
				}
				break;

			case MSG_EVENT_MOONSTONE_TRY_REP:		// ������ ���� ����
				{
					unsigned char ucSubType;
					(*istr) >> ucSubType;
					switch( ucSubType )
					{
					case MSG_CHANGE_NO_MOONSTONE:
						{
							if (pUIManager->DoesMessageBoxExist(MSGCMD_MOONSTONE_MIX))
								pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);

							CTString strMessage;
							strMessage.PrintF( _S( 1439, "�������� �����ϴ�." ) );		
							_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
							pUIManager->GetGamble()->ResetGamble();
						}
						break;					
					case MSG_CHANGE_MOONSTONE_RULLET:
						{
							LONG lSelectedMarker;
							LONG lSelectedCount;
							LONG lAccumulate;
							(*istr) >> lSelectedMarker;
							(*istr) >> lSelectedCount;
							(*istr) >> lAccumulate;

							pUIManager->GetGamble()->SetSelectedMarker( lSelectedMarker, lSelectedCount );
							pUIManager->GetGamble()->Start();
							pUIManager->GetGamble()->SetAccumulate( lAccumulate );
							//pUIManager->SetCSFlagOn( CSF_MOONSTONE );
							//pUIManager->GetGamble()->Stop();
						}
						break;
					}
				}
				break;
			case MSG_EVENT_MOONSTONE_RESULT_REP:	// ������ ���� ��� ����.��
				{
					SBYTE	sbPrizeType;					
					(*istr) >> sbPrizeType;
					pUIManager->GetGamble()->Stop();
					switch( sbPrizeType )
					{										
					case MSG_CHANGE_150000_EXP:					    // ����ġ 150,000
						{
							CTString strMessage;
							strMessage.PrintF( _S( 1442, "����ġ 150,000�� ������ϴ�." ) );		
							//	_pNetwork->ClientSystemMessage( strMessage );
							pUIManager->GetGamble()->ShowPrizeEffect();
						}
						break;
					case MSG_CHANGE_70000_EXP:					    // ����ġ 70,000	
						{
							CTString strMessage;
							strMessage.PrintF(_S( 1443, "����ġ 70,000�� ������ϴ�." ) );
							//	_pNetwork->ClientSystemMessage( strMessage );
							pUIManager->GetGamble()->ShowPrizeEffect();
						}
						break;
					case MSG_CHANGE_25000_EXP:					    // ����ġ 25,000							
						{
							CTString strMessage;
							strMessage.PrintF(_S( 1444, "����ġ 25,000�� ������ϴ�." ));		
							//	_pNetwork->ClientSystemMessage( strMessage );
							pUIManager->GetGamble()->ShowPrizeEffect();
						}
						break;

					case MSG_CHANGE_JACK_POT:						// ����.
					case MSG_CHANGE_5PLUS_41LEVEL_WEAPON:			// 41���� +5 ����(������)	
					case MSG_CHANGE_3PLUS_41LEVEL_WEAPON:			// 41���� +3 ����(������)	
					case MSG_CHANGE_41LEVEL_WEAPON:					// 41���� ���� (������)
					case MSG_CHANGE_3_SPECIAL_STONE:				// �������ü� 3��
					case MSG_CHANGE_2_SPECIAL_STONE:				// �������ü� 2��
					case MSG_CHANGE_1_SPECIAL_STONE:				// �������ü� 1��						
					case MSG_CHANGE_CRYSTAL_OF_EFFORT:				// ����� ����.
					case MSG_CHANGE_HIGH_CRYSTAL_OF_EXPERIMENCE:	// ��� ������ ����.					
					case MSG_CHANGE_MIDDLE_CRYSTAL_OF_EXPERIMENCE:	// �߱� ������ ����
					case MSG_CHANGE_10_PURE_STONE:
					case MSG_CHANGE_3_MIDDLE_CRYSTAL_OF_EXPERIMENCE:
					case MSG_CHANGE_5_12GRADE_RED_KER:				//12���� ���� �ɸ� 5��
					case MSG_CHANGE_5_12GRADE_RED_NEN:				//12���� ���� �� 5��
					case MSG_CHANGE_5_12GRADE_BLUE_KER:				//12���� Ǫ�� �ɸ� 5��
					case MSG_CHANGE_5_BIG_MP_POTION:				//���� MP���� 5��
					case MSG_CHANGE_5_12GRADE_BLUE_NEN:				//12���� Ǫ�� �� 5��
					case MSG_CHANGE_5_MOONSTONE:					//������ 5��
					case MSG_CHANGE_3_6GRADE_RED_KER:				//6���� ���� �ɸ� 3�� 
					case MSG_CHANGE_3_6GRADE_RED_NEN:				//6���� ���� �� 3��
					case MSG_CHANGE_3_6GRADE_BLUE_KER:				//6���� Ǫ�� �ɸ� 3��
					case MSG_CHANGE_3_BIG_HEAL_POTION:				//���� HP���� 3��
					case MSG_CHANGE_3_6GRADE_BLUE_NEN:				//6���� Ǫ���� 3��
					case MSG_CHANGE_3_MIDDLE_MP_POTION:				//���� MP���� 3��
					case MSG_CHANGE_3_MEMORY_SCROLL:				//�޸� ��ũ�� 3��
					case MSG_CHANGE_3_C_GRADE_ELEMENTAL:			//c��� ���� 3��
					case MSG_CHANGE_3_CRAK_BLUE_LEAF:			 	//ũ�� �Ķ��� 3��
					case MSG_CHANGE_3_STONE_WEAVER:					//���� ���� 3��
					case MSG_CHANGE_3_D_GRADE_ELEMENTAL:			//D��� ���� 3��
					case MSG_CHANGE_3_MIDIUM_HEAL_POTION:			//����ȸ������ 5��
					case MSG_CHANGE_3_CRAK_BRANCH:					//ũ�� �ٱ� 3��
					case MSG_CHANGE_3_STONELISE:					//���� ����
						{
							pUIManager->GetGamble()->ShowPrizeEffect();
							//CTString strMessage;
							//strMessage.PrintF( _S( 1452, "��÷ �Ǿ����ϴ�!!!" ));		
							//_pNetwork->ClientSystemMessage( strMessage );							
						}
						break;
					}					
				}
				break;
			}
		}
		break;

	case MSG_EVENT_TREASUREBOX:
		{
			unsigned char ucSubType;
			(*istr) >> ucSubType;
			switch( ucSubType )
			{
			case MSG_EVENT_TREASUREBOX_TRY_REP:
				{
					int iTreasureBoxLevel	= -1;
					CTString strMessage;
					LONG lTreasureBoxType;
					(*istr) >> lTreasureBoxType;

					switch( lTreasureBoxType )
					{
					case MSG_EVENT_TREASUREBOX_ERROR_NOT_LEVEL:
						{
							strMessage = _S( 1757, "������ �����Ͽ� ���� ���ڸ� ���� �����ϴ�." );		
							_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
							return;
						}
						break;
					case MSG_EVENT_TREASUREBOX_ERROR_NO_BOX:
						{
							strMessage = _S( 1758, "���� ���ڰ� �����ϴ�." );		
							_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
							return;
						}
						break;
					case MSG_EVENT_TREASUREBOX_10LEVEL:
						{
							iTreasureBoxLevel	= 10;
						}
						break;
					case MSG_EVENT_TREASUREBOX_14LEVEL:
						{
							iTreasureBoxLevel	= 14;
						}
						break;
					case MSG_EVENT_TREASUREBOX_18LEVEL:
						{
							iTreasureBoxLevel	= 18;
						}
						break;
					case MSG_EVENT_TREASUREBOX_22LEVEL:
						{
							iTreasureBoxLevel	= 22;
						}
						break;
					case MSG_EVENT_TREASUREBOX_26LEVEL:
						{
							iTreasureBoxLevel	= 26;
						}
						break;
					case MSG_EVENT_TREASUREBOX_30LEVEL:
						{
							iTreasureBoxLevel	= 30;
						}
						break;
					}

					ASSERT( iTreasureBoxLevel != -1 && "Invalid Treasure Box Level!" );

					CTString	strItemName[TREASUREBOX_ITEM_COUNT+1];
					LONG		lItemCount[TREASUREBOX_ITEM_COUNT+1];

					int nTreasureBoxCount = TREASUREBOX_ITEM_COUNT;
					int nGiftCount = 1;

					if (pUIManager->m_JapanTempEvent == 1)
					{
						nTreasureBoxCount = TREASUREBOX_ITEM_COUNT+1;
						nGiftCount = 2;
					}

					int		i;
					for( i = 0; i < nTreasureBoxCount ; ++i )
					{
						SBYTE sbTreasureItem;
						(*istr) >> sbTreasureItem;
						(*istr) >> lItemCount[i];

						switch( sbTreasureItem )
						{
						case MSG_EVENT_CHANGE_13LEVEL_WEAPON:		//+4 13���� ����
							strItemName[i] = _S( 1759, "+4 13���� ����" );	
							break;
						case MSG_EVENT_CHANGE_21LEVEL_WEAPON:		//+4 21���� ����
							strItemName[i] = _S( 1760, "+4 21���� ����" );	
							break;
						case MSG_EVENT_CHANGE_29LEVEL_WEAPON:		//+4 29���� ����
							strItemName[i] = _S( 1761, "+4 29���� ����" );	
							break;
						case MSG_EVENT_CHANGE_NAS:					//����
							strItemName[i] =_S( 1762,  "����" );	
							break;
						case MSG_EVENT_CHANGE_CANDY:				//����
							strItemName[i] = _S( 1763, "����" );	
							break;
						case MSG_EVENT_CHANGE_ATTACK_POTION:		//���ݷ���󹰾�
							strItemName[i] = _S( 1764, "���ݷ� ��� ����" );	
							break;
						case MSG_EVENT_CHANGE_DEFENSE_POTION:		//������󹰾�
							strItemName[i] = _S( 1765, "���� ��� ����" );	
							break;
						case MSG_EVENT_CHANGE_HP_POTION:   // ����  HP Ȯ�� ����
							strItemName[i] = _pNetwork->GetItemName(1289);
							break;
						case MSG_EVENT_CHANGE_MP_POTION:   // ����  MP Ȯ�� ����
							strItemName[i] = _pNetwork->GetItemName(1292);
							break;
						case MSG_EVENT_CHANGE_EX_MEMORY:   // �޸� ��ũ�� Ȯ�� ī��
							strItemName[i] = _pNetwork->GetItemName(840);
							break;
						case MSG_EVENT_CHANGE_HPMP_POTION:  // ����  HP/MP Ȯ�� ����
							strItemName[i] = _pNetwork->GetItemName(1295);
							break;
						case MSG_EVEVNT_CHAGE_EX_STAT:  // ���� â�� Ȯ�� ī��
							strItemName[i] = _pNetwork->GetItemName(841);
							break;
						case MSG_EVENT_CHANGE_PINK_DRAGON:		//��ũ �巹��ũ ��
							strItemName[i] = _pNetwork->GetItemName(1706);
							break;
						case MSG_EVENT_CHANGE_BLUE_HORSE:		//�Ķ� ���� �Ǹ�
							strItemName[i] = _pNetwork->GetItemName(1707);
							break;
						case MSG_EVENT_CHANGE_NO_TREASUREBOX:		//�������ڰ� ����
							break;
						}
					}
					pUIManager->CloseMessageBoxL( MSGLCMD_TREASUREBOX_EVENT );

					pUIManager->CreateMessageBoxL( _S( 1766, "���� ����" ), UI_QUEST, MSGLCMD_TREASUREBOX_EVENT );			

					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, TRUE, _S( 1766, "���� ����" ), -1, 0xE18600FF );	
					strMessage.PrintF( _S( 1767, "%d Lv �������ڸ� ���� �Ʒ� ������ �׸��� %d������ ���޵˴ϴ�.  %d Lv �������ڸ� ����ðڽ��ϱ�?" ), iTreasureBoxLevel, nGiftCount, iTreasureBoxLevel );	
					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, TRUE, CTString("  "), -1, 0xA3A1A3FF );
					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, TRUE, _S( 1768, "������ ���� ǰ��" ), -1, 0xE18600FF );			

					CTString strCount;
					for( i = 0; i < nTreasureBoxCount; ++i )
					{
						strCount = pUIManager->IntegerToCommaString(lItemCount[i]);
						strMessage.PrintF( _S( 61, "%s %s��" ), strItemName[i], strCount );
						pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, TRUE, strMessage, -1, 0xA3A1A3FF );
					}

					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, FALSE, _S( 1769, "�������ڸ� ����." ), 1 );
					pUIManager->AddMessageBoxLString( MSGLCMD_TREASUREBOX_EVENT, FALSE, _S( 1220, "����Ѵ�." ) );	
				}
				break;
			case MSG_EVENT_TREASUREBOX_OPEN_REP:
				{
					LONG lTreasureItem;
					(*istr) >> lTreasureItem;
				}
				break;
			}
		}
		break;
	case MSG_EVENT_SUPERSTONE:
		{
			unsigned char ucSubType;
			(*istr) >> ucSubType;
			switch(ucSubType)
			{
			case MSG_EVENT_SUPERSTONE_REP:
				{
				} break;
			}
		} break;

	case MSG_EVENT_CHANGE_WITHOUT_OPTION:
		{			
			// MSG_EVENT_CHANGE_WITHOUT_OPTION,			// 2��4�� ������ ���� ��ü �̺�Ʈ : old_itemindex(n) new_subtype(n)	
			LONG lOldItemIndex;
			LONG lNewSubType;
			(*istr) >> lOldItemIndex;
			(*istr) >> lNewSubType;
			pUIManager->GetChangeWeapon()->close();
		}
		break;

	case MSG_EVENT_2PAN4PAN_GOODS_CHECK:
		{
			ULONG count;
			CTString strMessage;
			(*istr) >> count;
			if(count>0){
				strMessage.PrintF( _S(2232, "����ǰ�� ��û ���Դϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );				
				_pNetwork->SendEvent24(0,MSG_EVENT_2PAN4PAN_GOODS_REQ);

			} else {				
				strMessage.PrintF( _S(2233, "��û�� ����ǰ�� �������� �ʽ��ϴ�" ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
			}

		}
		break;

	case MSG_EVENT_2PAN4PAN_GOODS_REP:
		{
			ULONG errType,count;
			CTString strMessage;
			(*istr) >> errType;
			(*istr) >> count;

			switch(errType)
			{
			case MSG_EVENT_2PAN4PAN_GOODS_ERROR_OK :
				strMessage.PrintF( _S(2234, "�̺�Ʈ �������� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_GOODS_ERROR_SOMEREMAIN:
				strMessage.PrintF( _S(2235, "�̺�Ʈ �������� �Ϻ� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_GOODS_ERROR_NOGOODS:
				strMessage.PrintF( _S(2236, "�̺�Ʈ �������� �������� �ʽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_GOODS_ERROR_NOSPACE:
				strMessage.PrintF( _S(2237, "���޹��� ������ �����մϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			}
		}
		break;
	case MSG_EVENT_2PAN4PAN_MONEY_REP:
		{
			ULONG success;
			CTString strMessage;
			(*istr) >> success;

			if(success==1 ){ //1 �°� 
				strMessage.PrintF( _S(2238, "�°��Ӵϸ� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );				

			} 
			else if(success==2 ){ //2 ��Ŀ 
				strMessage.PrintF( _S(2239, "��Ŀ�Ӵϸ� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );				

			} 

			else {				
				strMessage.PrintF( _S(2240, "�̺�Ʈ �������� �������� �ʽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
			}

		}
		break;
	case MSG_EVENT_2PAN4PAN_BOX_CHECK:
		{
			ULONG flag;
			CTString strMessage;
			(*istr) >> flag;
			if(flag>0){
				pUIManager->CloseMessageBoxL( MSGLCMD_EVENT_2PAN4PAN_TWO );
				pUIManager->CreateMessageBoxL( _S( 1875, "�̺�Ʈ ����â" ),UI_QUEST, MSGLCMD_EVENT_2PAN4PAN_TWO);						
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, 
					_S(2241,"2pan4pan �������ڸ� ����� �Ʒ��� 3���� ��ǰ �� �Ѱ����� ���޵˴ϴ�."), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, CTString("\n\n"), -1,0xA3A1A3FF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, _S(2242, "���� ��ǰ" ), -1, 0xFFA41CFF );		
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, _S(2243, "�ν��� 5��" ), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, _S(2244, "������ 5��" ), -1, 0xA3A1A3FF );
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, TRUE, _S(2245, "2pan4pan ���� 10��" ), -1, 0xA3A1A3FF );

				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, FALSE, _S(2246,"2pan4pan �������� ����"),OPEN_TREA);
				pUIManager->AddMessageBoxLString( MSGLCMD_EVENT_2PAN4PAN_TWO, FALSE,_S( 1220, "����Ѵ�." ));

			} else {				
				strMessage.PrintF( _S(2247, "�������ڰ� �������� �ʽ��ϴ�" ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
			}

		}
		break;
	case MSG_EVENT_2PAN4PAN_BOX_REP:
		{
			ULONG errType,count;
			CTString strMessage;
			(*istr) >> errType;
			(*istr) >> count;

			switch(errType)
			{
			case MSG_EVENT_2PAN4PAN_BOX_ERROR_OK :
				strMessage.PrintF( _S(2234, "�̺�Ʈ �������� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_BOX_ERROR_SOMEREMAIN:
				strMessage.PrintF( _S(2235, "�̺�Ʈ �������� �Ϻ� ���� �޾ҽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_BOX_ERROR_NOBOX:
				strMessage.PrintF( _S(2236, "�̺�Ʈ �������� �������� �ʽ��ϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			case MSG_EVENT_2PAN4PAN_BOX_ERROR_NOSPACE:
				strMessage.PrintF( _S(2237, "���޹��� ������ �����մϴ�." ));
				_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );	
				break;
			}

		}
		break;
	case MSG_EVENT_XMAS_2005 :
		LONG errType1;
		(*istr)>>errType1;
		if(errType1==MSG_EVENT_XMAS_2005_ERROR_OK){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(2282,"�����մϴ�. 2005 ũ�������� �̺�Ʈ ����ǰ�� ȹ�� �ϼ̽��ϴ�.") ; // ���� 
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		else if(errType1==MSG_EVENT_XMAS_2005_ERROR_NO_ITEM){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(2283,"������ �ް� ��� �������� �����մϴ�.") ; //���� 
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}
		break;

	case MSG_EVENT_NEWYEAR_2006_CHECK:
		{
			LONG tv_time,hour,min;
			(*istr)>>tv_time;
			hour=tv_time/3600;
			min=(tv_time%3600)/60;


			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage;
			strSysMessage.PrintF(_S(2304,"���� ���� �ð��� %d�ð� %d�� �Դϴ�."),hour,min) ; 
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 2287, "2006 �γ��� �ų� �̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}		
		break;


	case MSG_EVENT_NEWYEAR_2006_GOODS:
		LONG errType2;
		(*istr)>>errType2;
		if(errType2==MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_OK){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(2284,"�����մϴ�. 2006 �ų� �̺�Ʈ ����ǰ�� ȹ�� �ϼ̽��ϴ�.") ;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}
		else if(errType2==MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_TIME){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(2285,"�̺�Ʈ �ð��� ���� �մϴ�.(10�ð� �̻�)") ;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );


		}
		else if(errType2==MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_END){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(2285,"�γ��� ���� �̺�Ʈ ����ǰ�� 2006 �ų� �̺�Ʈ�� ���� �Ǿ�� ���� ������ �� �ֽ��ϴ�.") ;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}
		else if(errType2==MSG_EVENT_NEWYEAR_2006_GOODS_ERROR_ALREADY){
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			CTString strSysMessage = _S(673,"�̺�Ʈ �������� �̹� ���� �Ǿ����ϴ�.") ;
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strSysMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );

		}

		break;

	case MSG_EVENT_SEARCHFRIEND_ADD_CHECK :
	case MSG_EVENT_SEARCHFRIEND_ADDSELECT_CHECK :
		{
			ULONG errType;
			(*istr) >> errType;
			FindFriendErrChk1(errType);
		}
		break;

	case MSG_EVENT_SEARCHFRIEND_ADDSELECT_LIST :
		{
			ULONG listCnt,startIdx,listAll;
			SEL_LIST tv_char;
			LONG tv_tmp;

			(*istr) >> listCnt;
			(*istr) >> startIdx;
			(*istr) >> listAll;

			if( startIdx==0) 
				pUIManager->GetSelectList()->ResetSelectList();

			tv_tmp = startIdx+listCnt;
			for( int i=startIdx; i<tv_tmp; i++){
				(*istr) >> tv_char.m_nIndex;
				(*istr) >> tv_char.m_sName;

				tv_char.m_nState = LS_WAIT ;

				pUIManager->GetSelectList()->GetList()->push_back(tv_char);
			}
			if(tv_tmp>=listAll)
				pUIManager->GetSelectList()->CreateSelectList(SLS_REGIST|SLS_CANCEL|SLS_PREV|SLS_NEXT ,10, _S( 2503, "���� ã�� ���ϴ� ģ��"));
		}		
		break;
	case MSG_EVENT_SEARCHFRIEND_TIME_CHECK :
		{
			CTString strMessage;
			ULONG tv_time;
			(*istr) >> tv_time;
			pUIManager->CloseMessageBox( MSGCMD_NULL );
			strMessage.PrintF(_S( 2504, "���� %d�ð� %d�� ����Ͽ����ϴ�."),tv_time/3600,(tv_time%3600)/60 );
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(   _S( 2433, "ģ�� ã�� �̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSG_EVENT_SEARCHFRIEND_ONETIME_CHECK :
		{
			CTString strMessage;
			ULONG tv_time;
			int tv_sum;
			(*istr) >> tv_time;
			tv_sum = tv_time/3600;
			strMessage.PrintF(_S( 2505, "���� %d�ð� ����Ͽ����ϴ�."),tv_sum);
			_pNetwork->ClientSystemMessage(strMessage);
			if(tv_sum == 30)  
			{
				strMessage.PrintF(_S( 2506, "���� ���𿡰Լ� ����ǰ�� ���� ���� �� �ֽ��ϴ�."));
				_pNetwork->ClientSystemMessage(strMessage);
			}
			if(tv_sum == 60)  
			{
				strMessage.PrintF(_S( 2507, "����ġ �ι� �̺�Ʈ�� ���� �Ǿ����ϴ�."));
				_pNetwork->ClientSystemMessage(strMessage);
			}
		}
		break;
	case MSG_EVENT_SEARCHFRIEND_LIST_GOODS :
		{
			ULONG listCnt,startIdx,listAll;
			SEL_LIST tv_char;
			LONG tv_tmp,listState;

			(*istr) >> listCnt;
			(*istr) >> startIdx;
			(*istr) >> listAll;

			if( startIdx==0) 
				pUIManager->GetSelectList()->ResetSelectList();

			if(listAll <= 0){
				pUIManager->CloseMessageBox( MSGCMD_NULL );
				CTString strSysMessage = _S( 2493, "��ϵ� ģ���� �����ϴ�.") ;
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(   _S( 2433, "ģ�� ã�� �̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString( strSysMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );
				break;
			}
			tv_tmp = startIdx+listCnt;
			for( int i=startIdx; i<tv_tmp; i++){
				(*istr) >> tv_char.m_nIndex;
				(*istr) >> tv_char.m_sName;
				//	(*istr) >> requestTime;
				(*istr) >> listState;
				if(listState < 0) tv_char.m_nState = LS_WAIT;
				else if(listState == 0) tv_char.m_nState = LS_REWARDX;
				else if(listState == 3) tv_char.m_nState = LS_RECEIVED;
				else if(listState > 0 ) tv_char.m_nState = LS_REWARD;

				pUIManager->GetSelectList()->GetList()->push_back(tv_char);
			}
			if(tv_tmp == listAll)
				pUIManager->GetSelectList()->CreateSelectList(SLS_REWARD|SLS_PREV|SLS_NEXT|SLS_CANCEL,10,_S( 2503, "���� ã�� ���ϴ� ģ��"));
		}
		break;
	case MSG_EVENT_SEARCHFRIEND_GOODS_CHECK :
		{
			ULONG errType;
			(*istr) >> errType;
			FindFriendErrChk2(errType);
		}
		break;
	case MSG_EVENT_OXQUIZ:
		{
			ULONG QuizType;
			ULONG QuizNo;
			ULONG Limitsec;
			CTString strQuizMessage;
			UBYTE isAnswer;

			(*istr) >> QuizType;

			if( QuizType == MSG_EVENT_OXQUIZ_INVALID_TIME )
			{
				pUIManager->CloseMessageBox( MSGCMD_NULL );
				CTString strSysMessage = _S(2626, "O.X �̺�Ʈ ���� ���� �ð��� �ƴմϴ�.") ;
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(   _S(2627, "O.X �̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString( strSysMessage );
				pUIManager->CreateMessageBox( MsgBoxInfo );

				pUIManager->SetCSFlagOff(CSF_TELEPORT);
				break;				
			}
			else if( QuizType == MSG_EVENT_OXQUIZ_START )
			{
				CTString strStart = _S(2628, "O.X ��� ���� �մϴ�." );
				_pNetwork->ClientSystemMessage( strStart );
			}
			else if( QuizType == MSG_EVENT_OXQUIZ_QUIZ )
			{
				(*istr) >> QuizNo;
				(*istr) >> Limitsec;
				(*istr) >> strQuizMessage;

				pUIManager->GetOXQuizEvent()->ReceiveQuiz( QuizNo, Limitsec, strQuizMessage );
			}
			else if( QuizType == MSG_EVENT_OXQUIZ_ANSWER )
			{

				(*istr) >> QuizNo;
				(*istr) >> isAnswer;

				CTString tv_str;
				tv_str.PrintF(_S(2629,"%d�� ������ ������"), QuizNo );

				if( isAnswer == 1 )
				{
					tv_str += _S(2630, "O �����ϴ�." );	
				}
				else
				{
					tv_str += _S(2631, "X �����ϴ�." );	
				}

				_pNetwork->ClientSystemMessage( tv_str );
			}
		}
		break;
	case MSG_EVENT_RECOMMEND :
		{
			ULONG subType;
			(*istr) >> subType;

			switch(subType){
			case MSG_EVENT_RECOMMEND_SET :

				break;
			case MSG_EVENT_RECOMMEND_POTION :

				break;
			case MSG_EVENT_RECOMMEND_MOONSTONE :
				ULONG tv_idx;
				CTString tv_str,tv_str2;
				(*istr) >> tv_idx;
				(*istr) >> tv_str;
				tv_str2.PrintF(_S(2632,"%s�Բ��� ��õ���� �̺�Ʈ�� ��÷ �Ǽ̽��ϴ�."),tv_str.str_String);
				PCStartEffectGroup("server_event_using", tv_idx);
				_UIAutoHelp->SetGMNotice ( tv_str2, 0xFFAA33FF );
				break;

			}
		}
		break;
	case MSG_EVENT_PCBANG:	// NetCafe �������� ����, (�±�, �Ϻ�)NetCafe ķ���� �̺�Ʈ
		{
			ULONG ItemIndex;
			(*istr) >> ItemIndex;



			if( ItemIndex != -1 )
			{
				if( ItemIndex == 1394 || ItemIndex == 1395 || ItemIndex == 1396 || ItemIndex == 1397 )
				{// ���� ���ڸ� ���� ����
					Notice* pNotice = GAMEDATAMGR()->GetNotice();

					if (pNotice != NULL)
						pNotice->AddToNoticeList(4002, Notice::NOTICE_EVENT);
				}
				else
				{
					pUIManager->CloseMessageBox( MSGCMD_NULL );
					CTString strSysMessage = _S( 1840, "�������� ���������� ���� �Ǿ����ϴ�." );
					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(   _S( 169, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( strSysMessage );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
			}
			else
			{
				_pNetwork->ClientSystemMessage( _S( 1758, "���� ���ڰ� �����ϴ�." ) );
			}
		}
		break;
	case MSG_EVENT_WORLDCUP :
		{
			ULONG subType,nIdx,errCode;
			(*istr) >> subType;
			(*istr) >> nIdx;
			(*istr) >> errCode;

			WorldCupErrChk( errCode) ;

		}
		break;
	case MSG_EVENT_GOLDENBALL:
		{
			ULONG subType, errType;
			CTString strTeamA, strTeamB, strMessage;
			ULONG ulTeamAScore, ulTeamBScore;
			ULONG ulYear, ulMonth, ulDay, ulHour, ulMinute;
			SYSTEMTIME GoldenTime;

			ZeroMemory( &GoldenTime, sizeof( GoldenTime ) );

			Notice* pNotice = GAMEDATAMGR()->GetNotice();

			CUIMsgBox_Info	MsgBoxInfo;

			(*istr) >>subType;

			switch( subType )
			{
			case MSG_EVENT_GOLDENBALL_VOTE_START:
				{
					(*istr) >> strTeamA;
					(*istr) >> strTeamB;
					(*istr) >> ulYear >> ulMonth >> ulDay >> ulHour >> ulMinute;

					GoldenTime.wYear = static_cast<WORD>(ulYear);
					GoldenTime.wMonth = static_cast<WORD>(ulMonth);
					GoldenTime.wDay = static_cast<WORD>(ulDay);
					GoldenTime.wHour = static_cast<WORD>(ulHour);
					GoldenTime.wMinute = static_cast<WORD>(ulMinute);

					pUIManager->GetQuest()->SetGoldenBallEntry( TRUE );
					pUIManager->GetQuest()->SetStrTeamName( strTeamA, strTeamB, GoldenTime, TRUE );

					if (pNotice != NULL)
						pNotice->AddToNoticeList(2000+100, Notice::NOTICE_EVENT);
				}
				break;
			case MSG_EVENT_GOLDENBALL_VOTE_END:
				{
					(*istr) >> strTeamA;
					(*istr) >> strTeamB;				

					pUIManager->GetQuest()->SetStrTeamName( strTeamA, strTeamB, GoldenTime, FALSE );
					pUIManager->GetQuest()->SetGoldenBallEntry( FALSE );
					_pNetwork->ClientSystemMessage( _S( 2844, "��� �� �̺�Ʈ�� ���� �����մϴ�." ) );
				}
				break;
			case MSG_EVENT_GOLDENBALL_GIFT_START:
				{
					(*istr) >> strTeamA;
					(*istr) >> ulTeamAScore;
					(*istr) >> strTeamB;
					(*istr) >> ulTeamBScore;
					(*istr) >> ulYear >> ulMonth >> ulDay >> ulHour >> ulMinute;

					GoldenTime.wYear = static_cast<WORD>(ulYear);
					GoldenTime.wMonth = static_cast<WORD>(ulMonth);
					GoldenTime.wDay = static_cast<WORD>(ulDay);
					GoldenTime.wHour = static_cast<WORD>(ulHour);
					GoldenTime.wMinute = static_cast<WORD>(ulMinute);

					pUIManager->GetQuest()->SetGoldenBallRequital( TRUE );
					pUIManager->GetQuest()->SetStrTeamName( strTeamA, strTeamB, GoldenTime, TRUE );
					pUIManager->GetQuest()->SetTeamScore( static_cast<int>( ulTeamAScore ), static_cast<int>( ulTeamBScore ) );

					if (pNotice != NULL)
						pNotice->AddToNoticeList(2000+101, Notice::NOTICE_EVENT);

					pUIManager->GetQuest()->SetGoldenBallRequital( TRUE );

				}	
				break;
			case MSG_EVENT_GOLDENBALL_GIFT_END:
				{
					pUIManager->GetQuest()->SetGoldenBallRequital( FALSE );
					_pNetwork->ClientSystemMessage( _S( 2845, "��� �� �̺�Ʈ�� ����ð��� �������ϴ�." ), SYSMSG_NOTIFY );
				}
				break;
			case MSG_EVENT_GOLDENBALL_VOTE:
				{
					(*istr) >> ulTeamAScore;
					(*istr) >> ulTeamBScore;

					pUIManager->GetQuest()->SetTeamScore( static_cast<int>( ulTeamAScore ), static_cast<int>( ulTeamBScore ) );

					(*istr) >> errType;

					switch( errType )
					{
					case MSG_EVENT_GOLDENBALL_ERROR_VOTE_OK:
						{
							strMessage = _S( 2846, "��纼 �̺�Ʈ�� ����Ǿ����ϴ�" );
							_pNetwork->ClientSystemMessage( _S( 2847, "��� �� �̺�Ʈ ������ ���۵Ǹ� ���� �ٽ� ã�ƿ��ż� ������ �����ñ� �ٶ��ϴ�." ), SYSMSG_NOTIFY );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_VOTE_ALREADY:
						{
							strMessage = _S( 2848, "��� �� �̺�Ʈ�� �̹� ���� �ϼ̽��ϴ�." );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_VOTE_NOITEM:
						{
							strMessage = _S( 2849, "�̺�Ʈ ���� ���ؼ��� �����̽�Ʈ �౸�� 10���� �ʿ��մϴ�.\nȮ�� �� �ٽ� �õ��� �ּ���" );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_VOTE_FULLINVEN:
						{
							strMessage = _S( 2850, "�κ��丮�� ���� á���ϴ�." );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_VOTE_TIME:
						{
							strMessage = _S( 2851, "��� �� �̺�Ʈ ���� �ð��� �ƴմϴ�." );
						}
						break;
					}

					MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );		
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
				break;
			case MSG_EVENT_GOLDENBALL_GIFT:
				{
					(*istr) >> errType;

					switch( errType )
					{
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_EXACT:
						{
							_pNetwork->ClientSystemMessage( _S( 2852, "��� �� �̺�Ʈ �¸��� �� ������ ���߾� ������ ȹ�� �ϼ̽��ϴ�." ), SYSMSG_NOTIFY );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_WINNER:
						{
							_pNetwork->ClientSystemMessage( _S( 2853, "��� �� �̺�Ʈ �¸��� �����Ͽ� ������ ȹ���ϼ̽��ϴ�." ), SYSMSG_NOTIFY );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_OK_NONE:
						{
							_pNetwork->ClientSystemMessage( _S( 2854, "��� �� �̺�Ʈ ������ ȹ���ϼ̽��ϴ�." ), SYSMSG_NOTIFY );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_FULLINVEN:
						{
							_pNetwork->ClientSystemMessage( _S( 2855, "�κ��丮�� ���� á���ϴ�." ), SYSMSG_ERROR );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_NOITEM:
						{
							_pNetwork->ClientSystemMessage( _S( 2856, "��� �� �̺�Ʈ ���� ī�尡 �����ϴ�." ), SYSMSG_ERROR );
						}
						break;
					case MSG_EVENT_GOLDENBALL_ERROR_GIFT_TIME:
						{
							_pNetwork->ClientSystemMessage( _S( 2857, "��� �� �̺�Ʈ ���� �Ⱓ�� �ƴմϴ�." ), SYSMSG_ERROR );
						}
						break;
					}
				}
				break;
			}
			break;
		}
		break;
	case MSG_EVENT_RAIN_2006 : 
		{
			ULONG errType;
			(*istr) >> errType;
			CTString tv_str;
			switch(errType)
			{
			case MSG_EVENT_RAIN_2006_ERROR_OK :				// ���� ����
				tv_str=_S( 159, "������ ���������� ���޵Ǿ����ϴ�.");
				break;
			case MSG_EVENT_RAIN_2006_ERROR_NOITEM :			// �����/������ ����
				tv_str=_S(2767, "�𽺹β��� �����Ͽ� ������ ���� �� �����ϴ�. Ȯ�� �� �ٽ� �õ��Ͽ� �ּ���.");
				break;
			case MSG_EVENT_RAIN_2006_ERROR_FULLINVEN :		// �κ��丮 ������
				tv_str=_S( 2768,"�κ��丮�� �������� ������ ���� �� �����ϴ�.");
				break;
			}
			_pNetwork->ClientSystemMessage(tv_str);
		}
		break;
	case MSG_EVENT_TLD_BUDDHIST:
		{
			BYTE ItemType;
			ULONG errType;
			(*istr) >> ItemType;
			(*istr) >> errType;

			switch( errType )
			{
			case MSG_EVENT_TLD_BUDDHIST_ERROR_OK:
				_pNetwork->ClientSystemMessage( _S( 2926, "���������� ����ǰ�� �����Ͽ����ϴ�." ), SYSMSG_NOTIFY );
				break;
			case MSG_EVENT_TLD_BUDDHIST_ERROR_FULLINVEN:
				_pNetwork->ClientSystemMessage( _S( 2768, "�κ��丮�� �������� ������ ���� �� �����ϴ�."), SYSMSG_ERROR );
				break;
			case MSG_EVENT_TLD_BUDDHIST_ERROR_NOITEM:
				_pNetwork->ClientSystemMessage( _S( 2927, "�� ������ �����Ͽ� ������ ���� �� �����ϴ�. Ȯ�� �� �ٽ� �õ��Ͽ� �ּ���." ), SYSMSG_ERROR );
				break;
			}
		}
		break;
	case MSG_EVENT_COLLECT_BUG:
		{
			ULONG subType;
			ULONG ulTemp;
			CTString strMessage;

			CUIMsgBox_Info	MsgBoxInfo;

			(*istr) >> subType;

			switch( subType )
			{
			case MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_OK:
				{
					(*istr) >> ulTemp;
					if( ulTemp == 1 )
					{
						strMessage = _S( 2972, "�����մϴ�! 30����Ʈ�� �߰��� ��� ���� ä�����ڸ� �����ϼ̽��ϴ�" );
					}
					else if( ulTemp == 0 )
					{ 
						strMessage = _S( 2973, "���� ä������ 1���� �����Ͽ����ϴ�." );
					}
				}
				break;
			case MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_DUPLICATE:
				{
					_pNetwork->ClientSystemMessage( _S( 2974, "�̹� ���� ä�����ڸ� ������ �־� �� �̻� ������ �� �����ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_FULLINVEN:
				{
					_pNetwork->ClientSystemMessage( _S( 2855, "�κ��丮�� ���� á���ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_BUY_BOX_REP_ERROR_MONEY:
				{
					_pNetwork->ClientSystemMessage( _S( 266, "�������� �����մϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_GIFT_REP_OK:
				{
					(*istr) >> ulTemp;

					strMessage = _S( 2975, "���� ä�� �̺�Ʈ ������ �Ϸ� �Ǿ����ϴ�." );
					if ( pUIManager->GetInsectCollect()->IsVisible() )
						pUIManager->RearrangeOrder(UI_INSECTCOLLECT, FALSE);
				}
				break;
			case MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_FULLINVEN:
				{
					_pNetwork->ClientSystemMessage( _S( 116, "�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_NOITEM:
				{
					_pNetwork->ClientSystemMessage( _S( 2976, "���� ä�� ���ڸ� ������ ���� �ʽ��ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_GIFT_REP_ERROR_NOTFULL:
				{
					_pNetwork->ClientSystemMessage( _S( 2977, "���� ä�����ڰ� ���� ä������ �ʾ� ���� ���� �� �����ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_PICK_OK:
				{
					(*istr) >> ulTemp;

					strMessage = pUIManager->GetInsectCollect()->GetInsectName( ulTemp );
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_NOTIFY );					
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_PICK_NOITEM:
				{
					_pNetwork->ClientSystemMessage( _S( 2978, "���� ä�� ���ڸ� ������ ���� �ʽ��ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_PICK_FULL:
				{
					_pNetwork->ClientSystemMessage( _S( 2979, "ä�����ڰ� ���� á���ϴ�." ), SYSMSG_ERROR );
					return;
				}
				break;
			case MSG_EVENT_COLLECT_BUG_DROP:
				{
					pUIManager->GetInsectCollect()->DeleteItem();
					return;
				}
			}

			MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;

	case MSG_EVENT_CHUSEOK_2006:
		{
			ULONG subType;
			CTString strMessage;

			CUIMsgBox_Info	MsgBoxInfo;

			(*istr) >> subType;
			switch(subType)
			{
			case MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_OK:
				strMessage.PrintF( _S(3138, "���� ���ۿ� �����Ͽ����ϴ�." ) );	
				break;
			case MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_FAIL:
				strMessage.PrintF( _S(3139, "���� ���ۿ� �����Ͽ����ϴ�." ) );	
				break;
			case MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_NOITEM:
				strMessage.PrintF( _S(3140, "���� ��ᰡ �����մϴ�." ) );
				break;

			case MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_OK:			// ���� ���� ����� ����
				strMessage.PrintF( _S(3141, "�������� ���ۿ� �����Ͽ����ϴ�." ) );	
				break;
			case MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_FAIL:			// ���� ���� ����� ����
				strMessage.PrintF( _S(3142, "�������� ���ۿ� �����Ͽ����ϴ�." ) );	
				break;
			case MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_NOITEM:		// ���� ���� ��� ����
				strMessage.PrintF( _S(3143, "�������� ��ᰡ �����մϴ�." ) );
				break;

			case MSG_EVENT_CHUSEOK_2006_GIFT_OK:							// ���� ���� ��ȯ ����
				strMessage.PrintF( _S( 1884, "�߼� �̺�Ʈ ����ǰ�� ���޵Ǿ����ϴ�. �̺�Ʈ�� ������ �ּż� �����մϴ�." ) );	
				break;
			case MSG_EVENT_CHUSEOK_2006_GIFT_OK_NOITEM:					// ���� ���� ����
				strMessage.PrintF( _S(3144, "���������� ���� ������ ���� �� �����ϴ�." ) );	
				break;

			case MSG_EVENT_CHUSEOK_2006_MAKE_RICECAKE_FULLINVEN:
			case MSG_EVENT_CHUSEOK_2006_MAKE_RAINBOW_CAKE_FULLINVEN:		// �κ��丮 ����
				strMessage.PrintF( _S(265, "�κ��丮 ������ �����մϴ�." ) );
				break;
			case MSG_EVENT_CHUSEOK_2006_GIFT_OK_FULLINVEN:				// �κ��丮 ����
				strMessage.PrintF( _S(116, "�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�." ) );
				break;
			}
			MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSG_EVENT_XMAS_2006:		// 2006 X-Mas event [12/12/2006 Theodoric]
		{
			SLONG nCakeCount;
			ULONG subType;

			CTString strMessage;
			CUIMsgBox_Info	MsgBoxInfo;

			(*istr) >> nCakeCount;
			(*istr) >> subType;	

			switch(subType)
			{
			case MSG_EVENT_XMAS_2006_ERROR_OK:	// ����
				strMessage.PrintF( _S(159, "��ȯ�� ���������� �̷�������ϴ�." ) );
				break;
			case MSG_EVENT_XMAS_2006_ERROR_FULLINVEN:	// �κ� ���� ��
				strMessage.PrintF( _S(265, "�κ��丮 ������ �����մϴ�." ) );
				break;
			case MSG_EVENT_XMAS_2006_ERROR_NOITEM:	// ������ ����
				strMessage.PrintF( _S(2908, "��ȯ�� �������� �����ϴ�." ) );
				break;
			}

			MsgBoxInfo.SetMsgBoxInfo( _S( 191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL, MSGBOX_WIDTH + 20 );		
			MsgBoxInfo.AddString( strMessage );
			pUIManager->CreateMessageBox( MsgBoxInfo );
		}
		break;
	case MSG_EVENT_OPEN_BETA_GIFT:
		{
			CUIMsgBox_Info	MsgBoxInfo;
			CTString strMessage;

			strMessage.PrintF(_S(1840, "�������� ���������� ���� �Ǿ����ϴ�."));
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_EVENT_VALENTINE_2007: // ���귯�� �̺�Ʈ
		{
			pUIManager->GetBingoBox()->ErrorMessage(&(*istr));
		}
		break;

		// wooss 070307 ---------------------------------------------------->>
		// kw : WSS_WHITEDAY_2007 
	case MSG_EVENT_WHITEDAY_2007:
		{
			ULONG subType;
			(*istr) >> subType;
			if( Whiteday2007ErrChk(subType) )
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				CTString tMsg,tStr;

				UBYTE exType;
				(*istr) >> exType;
				switch(exType)
				{
				case 0:
					{
						ULONG iIdx;
						(*istr) >> iIdx;						
						tStr = CTString(_pNetwork->ga_World.wo_aSkillData[iIdx].GetName());
						tMsg.PrintF(_S(3261, "�η������κ��� %s �ֹ��� �޾ҽ��ϴ�."), tStr.str_String );
						MsgBoxInfo.AddString( tMsg );
						pUIManager->CreateMessageBox( MsgBoxInfo );
					}
					break;
				case 1:
					{
						tMsg = _S(3262,"�η������κ��� �ϴû� ������ 1���� �޾ҽ��ϴ�.");
						MsgBoxInfo.AddString( tMsg );
						pUIManager->CreateMessageBox( MsgBoxInfo );					
					}					
					break;
				case 2:
					{
						tMsg =_S(3263,"�η������κ��� ��ȫ�� ������ 1���� �޾ҽ��ϴ�.");
						MsgBoxInfo.AddString( tMsg );
						pUIManager->CreateMessageBox( MsgBoxInfo );					
					}
					break;
				}
			}

			if( subType ==  MSG_EVENT_WHITEDAY_2007_LETTER_REP )
			{
				COLOR tCol;
				CTString tStr;
				(*istr) >> tCol;
				(*istr) >> tStr;
				pUIManager->GetChattingUI()->AddSysMessage( tStr, SYSMSG_USER,tCol );
			}				
		}
		break;
		// [KH_070417] �����ǳ� �̺�Ʈ ���� �߰�
	case MSG_EVENT_TEACH_2007:
		ReceiveEventMaster(istr);
		break;
		// ------------------------------------------------------------------<<
	case MSG_EVENT_CHILDRENSDAY_2007:
		{
			ULONG subType;
			(*istr) >> subType;
			if(subType == MSG_EVENT_CHILDRENSDAY_2007_REP)
			{				
				UBYTE exType;
				(*istr) >> exType;

				CTString tMsg;
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );

				switch(exType)
				{
				case 0:
					{
						ULONG iItemidx;
						(*istr) >> iItemidx;
						CItemData* pID = _pNetwork->GetItemData(iItemidx);
						tMsg.PrintF(_S(3405, "%s �������� ȹ�� �Ͽ����ϴ�."), pID->GetName());
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox( MsgBoxInfo );

					}break;
				case 1:
					{
						tMsg = _S(3406, "�����ϰ� �ִ� ��� ������ ���� ������ �����մϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�");
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox( MsgBoxInfo );

					}break;
				case 2:
					{
						tMsg = _S(3407, "�ѹ� ���� ���� �� �� ���� �� �����ϴ�. Ȯ���ϰ� �ٽ� �õ� �Ͽ� �ֽʽÿ�");
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}break;
				default:
					{
						tMsg.PrintF(_S(1844,"���޵� �������� ���������� ó������ ���Ͽ����ϴ�. �ٽ� �õ��Ͽ� �ֽʽÿ�."));
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}break;

				}

			}
		}break;
		// [KH_070326] ��Ȱ�� �̺�Ʈ ����
	case MSG_EVENT_EGGS_HUNT_2007:
		{
			ULONG subType;
			(*istr) >> subType;
			if( EasterEggs2007ErrChk(subType) )
			{
				pUIManager->CloseMessageBox(MSGCMD_NULL);
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
				CTString tMsg,tStr;

				INDEX exItemType;	// [KH_070329] ������ ���� �ε���
				INDEX exItemNum;	// [KH_070329] ������ ����
				(*istr) >> exItemType;
				(*istr) >> exItemNum;

				if(exItemNum != 1) // [KH_070329] �Ѱ��� �ƴϸ� ���� ǥ��
					tStr.PrintF("%d", exItemNum);
				else // [KH_070329] �ϳ��� �ƴϸ� ǥ�� ����
				{
					tStr = CTString("");
				}

				tMsg.PrintF( _S( 3266, "��Ȱ�� �ް� ����ǰ %s%s�� ȹ���Ͽ����ϴ�."), tStr, _pNetwork->GetItemName( exItemType ) );

				MsgBoxInfo.AddString( tMsg );

				pUIManager->CreateMessageBox( MsgBoxInfo );
			}
		}
		break;

		// ------------------------------------------------------------------<<
		// WSS_GUILDMASTER -------------------------------------------------->>
	case MSG_EVENT_PARENTSDAY_2007:
		{
			UBYTE subType;
			SBYTE errCode;  
			(*istr) >> subType;
			switch(subType)
			{
			case MSG_EVENT_PARENTSDAY_2007_ACCUMULATEPOINT_RANKING_LIST:
				{
					(*istr)>>errCode;
					if(GuildMasterErrChk(errCode))
					{						
						ULONG tCnt;
						ULONG tRank,tPoint;
						CTString gName,strRank,strPoint;
						CUIListBox* tBox = &pUIManager->GetMessageBox(MSGCMD_GUILDMASTER_1)->GetListBox();

						// Init string
						ASSERT(tBox!=NULL);
						tBox->ResetAllStrings();
						tBox->AddString( 0, _S(1714, "����"),0xFFF244FF, FALSE );
						tBox->AddString( 1, _S(3450, "����Ʈ"),0xFFF244FF, FALSE );
						tBox->AddString( 2, _S(3451, "����"),0xFFF244FF, FALSE );	

						(*istr) >> tCnt;
						for(int i=0; i<tCnt;i++)
						{
							(*istr) >> tRank >> tPoint >> gName;
							strRank.PrintF("%d",tRank);
							strPoint.PrintF("%d",tPoint);
							tBox->AddString(0,strRank,0xF2F2F2FF,FALSE);
							tBox->AddString(1,strPoint,0xF2F2F2FF,FALSE);
							tBox->AddString(2,gName,0xF2F2F2FF,FALSE);							
						}									
					}						
				}	
				break;
			case MSG_EVENT_PARENTSDAY_2007_ADD_POINT:			// s->c : errorcode(c) point(n) totalpoint(n)
				{
					(*istr)>>errCode;
					if( GuildMasterErrChk(errCode))
					{
						CTString tMsg;
						CUIMsgBox_Info	MsgBoxInfo;
						ULONG tInc,tPnt;
						(*istr) >> tInc >> tPnt;
						MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
						tMsg.PrintF(_S(3476,"����� ����Ʈ�� %d��ŭ �����Ͽ� %d���� �Ǿ����ϴ�."),tInc,tPnt);
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox( MsgBoxInfo );										
					}
				}
				break;
			case MSG_EVENT_PARENTSDAY_2007_EXCHANGE_TICKET:		// s->c : errorcode(c) changeTicketCount(n)
				{
					(*istr)>>errCode;
					if(GuildMasterErrChk(errCode))
					{
						CTString tMsg;
						CUIMsgBox_Info	MsgBoxInfo;
						ULONG tCnt;
						(*istr) >> tCnt;
						MsgBoxInfo.SetMsgBoxInfo( _S(191, "Ȯ��" ), UMBS_OK, UI_NONE, MSGCMD_NULL );
						tMsg.PrintF(_S(3477,"������ ��ȯ�� %d���� ���� �޾ҽ��ϴ�."),tCnt);
						MsgBoxInfo.AddString(tMsg);
						pUIManager->CreateMessageBox( MsgBoxInfo );										
					}
				}
				break;
			case MSG_EVENT_PARENTSDAY_2007_EXCHANGE_ITEM:		// s->c: errcode(c)					
				(*istr)>>errCode;
				GuildMasterErrChk(errCode);
				break;
			case MSG_EVENT_PARENTSDAY_2007_NOTICE:
				{
					CTString strMessage,tGuild,tItem;
					(*istr)>>tGuild>>tItem;
					strMessage.PrintF(_S(3478,"[%s]����� ��� �����Ͱ� [%s]�����ۿ� ��÷ �Ǿ����ϴ�."),tGuild,tItem);
					_UIAutoHelp->SetGMNotice ( strMessage );
				}
				break;
			}
		}
		break;
		// ------------------------------------------------------------------<<

		// WSS_MINIGAME 070420 ---------------------------------------------->>
	case MSG_EVENT_GOMDORI_2007 :
		{
			UBYTE subType;
			SBYTE wincount; 
			SBYTE usersel;  
			SBYTE npcsel;  
			CUIMsgBox_Info msgInfo;
			CTString strMessage=_S(191,"Ȯ��");
			CUIMinigame* pMinigame=((CUIMinigame*)pUIManager->GetUI(UI_MINIGAME));
			(*istr) >> subType;
			switch(subType)
			{
			case MSG_EVENT_GOMDORI_2007_CHECKITEM:
				// ���ڽ� ��ư�� Ǯ�� �ش�.
				pMinigame->OpenMinigame(MSG_EVENT_GOMDORI_2007);
				break;
			case MSG_EVENT_GOMDORI_2007_START:
				// ���ڽ� ��ư�� Ǯ�� �ش�.
				pMinigame->SetButtonState(BTN_STATE_START_CONTINUE);
				break;
			case MSG_EVENT_GOMDORI_2007_CONTINUE:
				// ���ڽ� ��ư�� Ǯ�� �ش�.
				pMinigame->SetButtonState(BTN_STATE_START_CONTINUE);
				break;

			case MSG_EVENT_GOMDORI_2007_RESULT_WIN:
				// TODO : �̰��� ��� ó��(UIMinigame�� �Լ� ȣ��)
				(*istr)>>wincount>>usersel>>npcsel;
				pMinigame->SetMinigameResult(wincount,usersel,npcsel,0);
				break;
			case MSG_EVENT_GOMDORI_2007_RESULT_LOSE:
				// TODO : ���� ��� ó��(UIMinigame�� �Լ� ȣ��)
				(*istr)>>wincount>>usersel>>npcsel;
				pMinigame->SetMinigameResult(wincount,usersel,npcsel,2);
				break;
			case MSG_EVENT_GOMDORI_2007_RESULT_DRAW:
				// TODO : ����� ��� ó��(UIMinigame�� �Լ� ȣ��)
				(*istr)>>wincount>>usersel>>npcsel;
				pMinigame->SetMinigameResult(wincount,usersel,npcsel,1);
				break;
			case MSG_EVENT_GOMDORI_2007_END:
				{
					UBYTE wincount,prompttype;
					ULONG extra1,extra2;

					(*istr)>>wincount>>prompttype>>extra1>>extra2;
					if(prompttype== 0)
					{
						msgInfo.SetMsgBoxInfo(strMessage,UMBS_OK,UI_NONE,MSGCMD_NULL);
						//	strMessage.PrintF( _s( "���������[%s] %d���� ���� �Ǿ����ϴ�." ), _pNetwork->GetItemName(extra1), extra2);
						strMessage.PrintF( _S(1840, "�������� ���������� ���� �Ǿ����ϴ�" ));
						msgInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(msgInfo);
					}
					else if(prompttype== 1)
					{
						msgInfo.SetMsgBoxInfo(strMessage,UMBS_OK,UI_NONE,MSGCMD_NULL);
						strMessage.PrintF( _S(3479, "ü�� ������ ���޵Ǿ����ϴ�." ));
						msgInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(msgInfo);
					}
					else if(prompttype== 2)
					{
						CTString strName1,strName2;
						strName1.PrintF("%s",_pNetwork->GetItemName(extra1));
						strName2.PrintF("%s",_pNetwork->GetItemName(extra2));

						// ����
						pMinigame->m_extra1 = extra1;
						pMinigame->m_extra2 = extra2;

						strMessage= _S(3480, "���� ���� ����" );
						msgInfo.SetMsgBoxInfo(strMessage,UMBS_SELECTBOX,UI_MINIGAME,MSGCMD_MINIGAME_SELECT_ITEM);
						msgInfo.m_nHeight =200;
						pUIManager->CreateMessageBox(msgInfo);
						pUIManager->GetMessageBox(MSGCMD_MINIGAME_SELECT_ITEM)->addSelectContext(strName1);
						if (_pNetwork->MyCharacterInfo.job != NIGHTSHADOW)
						{
							pUIManager->GetMessageBox(MSGCMD_MINIGAME_SELECT_ITEM)->addSelectContext(strName2);
						}
					}

					// ���� â �ݱ� 
					pMinigame->Close();
				}
				break;
			case MSG_EVENT_GOMDORI_2007_VIEW_STATUS:
				{
					ULONG serverCnt,itemCnt;
					ULONG itemAll=0;
					(*istr)>>serverCnt;
					strMessage= _S(3481, "������ ���� ���� ã�� ��Ȳ");

					msgInfo.SetMsgBoxInfo(strMessage,UMBS_OK,UI_NONE,MSGCMD_NULL,300);

					strMessage=_S(3482, "���ϼ��� ������ ������ ��ü ���� ���� ���� ���� �� ������ �п�ǰ ��Ʈ�� ��̳� õ���� �� ��̵鿡�� �����ϰ� �˴ϴ�." );
					msgInfo.AddString(strMessage);
					CTString strCount;
					for(int i=0;i<serverCnt;i++)
					{
						(*istr)>>itemCnt;
						strCount = UIMGR()->IntegerToCommaString(itemCnt);
						strMessage.PrintF( _S(576, "%s : %s��" ),pUIManager->GetServerSelect()->GetServerName(i+1), strCount);
						msgInfo.AddString(strMessage);

						itemAll+=itemCnt;
					}
					msgInfo.AddString(CTString(" "));
					strMessage.PrintF( _S(3483, "��ü �������� ã�� �ϼ�ǰ �� : %d��" ),itemAll);
					msgInfo.AddString(strMessage);

					pUIManager->CreateMessageBox(msgInfo);
				}
				break;

			case MSG_EVENT_GOMDORI_2007_ERROR_NOITEM:
				{
					if(pUIManager->DoesMessageBoxExist(MSGCMD_NULL)) return;
					msgInfo.SetMsgBoxInfo(strMessage,UMBS_OK,UI_NONE,MSGCMD_NULL);
					strMessage.PrintF( _S(3484, "���, �����̰� ���׿�? �����̰� ������ ������������ �� �� �����. ������ �ϰ� �ʹٸ�, ���������� 1������ 9�������� ��� ��� �ϼ��� �����̸� �����;� �ؿ�." ));
					msgInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(msgInfo);
				}
				break;

			case MSG_EVENT_GOMDORI_2007_ERROR_FULLINVENTORY:
				strMessage=_S(675, "�κ��丮�� ���� ���� ������ ������ �Ұ����մϴ�." );
				pUIManager->GetChattingUI()->AddSysMessage( strMessage, SYSMSG_NORMAL );
				break;
			}
		}
		break;
		// ------------------------------------------------------------------<<
	case MSG_EVENT_FLOWERTREE_2007: // 2007 �ɳ��� �̺�Ʈ
		{
			UBYTE subtype, errortype;
			SLONG SvCount, SvGroup;
			ULONG SvPoint, SvPoint1;

			CUIMsgBox_Info MsgBoxInfo;

			(*istr) >> subtype;

			switch (subtype)
			{
			case MSG_EVENT_FLOWERTREE_2007_POINT:
				{
					(*istr) >> SvPoint;
					(*istr) >> SvGroup;

					pUIManager->GetFlowerTree()->AddServerNameList(SvPoint, SvGroup);
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_POINT_RANK:
				{
					(*istr) >> SvCount; // ������ ����

					SLONG i;

					for (i=0; i<SvCount; i++)
					{
						(*istr) >> SvPoint; // ����Ʈ
						(*istr) >> SvGroup; // ������ ��ȣ

						pUIManager->GetFlowerTree()->AddServerNameList(SvPoint, SvGroup);
					}
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_GROWUP:
				{
					(*istr) >> SvPoint; // ���� ����Ʈ

					CTString strMessage;

					if (SvPoint > 0)
					{
						strMessage.PrintF(_S(3494, "�� ������ ��ȭ�� �����־� �⿩���� %d���� �Ͽ����ϴ�."), SvPoint);
					}
					else
					{
						strMessage.PrintF(_S(3495, "�������� �� ���� ��ȭ���� �����ϴ�."));						
					}

					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_MY_POINT:
				{
					(*istr) >> SvPoint; // ������ �⿩�� ����Ʈ
					(*istr) >> SvPoint1;

					if (pUIManager->DoesMessageBoxExist(MSGCMD_FLOWERTREE_SUPPORT))
						pUIManager->CloseMessageBox(MSGCMD_FLOWERTREE_SUPPORT);

					if (pUIManager->GetFlowerTree()->IsVisible())
						pUIManager->RearrangeOrder(UI_FLOWERTREE, FALSE);

					MsgBoxInfo.SetMsgBoxInfo(_S(169, "�̺�Ʈ"), UMBS_USER_12, UI_FLOWERTREE, MSGCMD_FLOWERTREE_TICKET);
					MsgBoxInfo.SetUserBtnName(_S(3498, "��ȯ�� �ޱ�"), _S(3499, "��ȯ�� Ȯ��"));
					MsgBoxInfo.AddString( _S(3500, "�ɳ��� �⿩����Ʈ"), 0xF3F3F3FF, TEXT_CENTER );
					CTString strPoint, strPoint1;
					strPoint.PrintF(_S(3511, "���� �� �⿩����Ʈ: %d"), SvPoint);
					strPoint1.PrintF(_S(3512, "���� ��ȯ���� ���� ����: %d"), SvPoint1);
					MsgBoxInfo.AddString(CTString(" "));
					MsgBoxInfo.AddString( strPoint, 0x6BD2FFFF, TEXT_CENTER );
					MsgBoxInfo.AddString( strPoint1, 0x6BD2FFFF, TEXT_CENTER );
					pUIManager->CreateMessageBox( MsgBoxInfo );
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_RECV_TICKET:
				{
					(*istr) >> SvCount; // ��ȯ�� ����

					CTString strTicket;					

					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					if (SvCount > 0)
						strTicket.PrintF(_S(3496, "������ ��ȯ�� %d���� ���� �޾ҽ��ϴ�"), SvCount);
					else
						strTicket.PrintF(_S(3497, "���޹��� ��ȯ���� �����ϴ�."));

					MsgBoxInfo.AddString(strTicket);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_OPEN_TICKET:
				{
					(*istr) >> errortype;

					switch (errortype)
					{
					case 0: // ����
						{
							MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
							MsgBoxInfo.AddString(_S(3502, "���� �����ϰ� �ִ� ��ȯ���� �����ϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�"));
							pUIManager->CreateMessageBox(MsgBoxInfo);
						}
						break;
					}
				}
				break;
			case MSG_EVENT_FLOWERTREE_2007_PRICE_MSG:
				{ // ���� �޼���
					CTString CharName, strMessage;
					SLONG nItemIndex;

					(*istr) >> CharName;
					(*istr) >> nItemIndex;

					strMessage.PrintF(_S(3503, "%s���� %s �����ۿ� ��÷�Ǿ����ϴ�."), CharName, _pNetwork->GetItemData(nItemIndex)->GetName());
					_UIAutoHelp->SetGMNotice ( strMessage );
				}
				break;
			}
		}
		break;
		////////////////////////////////////////////////////////////////
		// [070705: Su-won] EVENT_SUMMER_2007						|---------->
	case MSG_EVENT_SUMMER_VACATION_2007:
		{
			LONG subtype;
			(*istr) >> subtype;

			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;

			switch (subtype)
			{
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_MAKE_OK:
				{
					LONG nResult;
					LONG nReward;
					LONG nCount;
					(*istr) >> nResult;
					(*istr) >> nReward;
					(*istr) >> nCount;

					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					CTString strColor;
					if( nResult == 1 )
						strColor = _S(3576, "�׸�");
					else if( nResult<=4)
						strColor = _S(3577, "����");
					else if( nResult<=7)
						strColor = _S(3578, "�ǹ�");
					else if( nResult<=10)
						strColor = _S(3579, "���");

					if( nResult == 1 )
						strMessage.PrintF( _S(3580, "�����̷� %s ���� �����̳׿�! �����մϴ�!"), strColor);
					else if( nResult%3 ==2) 
						strMessage.PrintF( _S(3581, "�����̷� %s �������� �����̳׿�! �����մϴ�!"), strColor);
					else if( nResult%3 ==0) 
						strMessage.PrintF( _S(3582, "�����̷� %s �������� �����̳׿�! �����մϴ�!"), strColor);
					else if( nResult%3 ==1) 
						strMessage.PrintF( _S(3583, "�����̷� %s �巡���� �����̳׿�! �����մϴ�!"), strColor);
					MsgBoxInfo.AddString(strMessage);

					CTString strCount = UIMGR()->IntegerToCommaString(nCount);

					if( nReward == 19 )
						strMessage.PrintF( _S(3584, "�������� %s ������ �帮�ڽ��ϴ�."), strCount );
					else
						strMessage.PrintF( _S(3585, "�������� %s %s���� �帮�ڽ��ϴ�."), _pNetwork->GetItemName(nReward), strCount );

					MsgBoxInfo.AddString(strMessage);

					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_INCHEN_OK:
				{
					LONG nResult;
					(*istr) >> nResult;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF( _S(558, "���տ� �����Ͽ����ϴ�."));
					MsgBoxInfo.AddString(strMessage);
					strMessage.PrintF( _S(3586, "%s 1���� �����Ǿ����ϴ�."), _pNetwork->GetItemName(nResult));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_MAKE_FAIL:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF( _S(3588, "���� ���⿡ ������ ������ �ƴմϴ�."));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_INCHEN_FALIL:
				{
					LONG nResult;
					(*istr) >> nResult;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF( _S(557, "���տ� �����Ͽ����ϴ�."));
					MsgBoxInfo.AddString(strMessage);
					if( nResult != 2370 )
					{
						strMessage.PrintF( _S(3587, "%s 4���� ��������ϴ�."), _pNetwork->GetItemName(nResult));
						MsgBoxInfo.AddString(strMessage);
					}
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOITEM:
				{
					strMessage.PrintF(_S( 1330 ,"�������� �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_FULLINVENTORY:
				{
					strMessage.PrintF(_S( 265 ,"�κ��丮 ������ �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
			case MSG_EVENT_SUMMER_VACATION_2007_ERROR_NOMONEY:
				{
					strMessage.PrintF(_S( 266 ,"�������� �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
			}
		}
		break;
		// [070703: Su-won] EVENT_SUMMER_2007						<----------|
		////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////
		// [070807: Su-won] EVENT_ADULT_OPEN
	case MSG_EVENT_OPEN_ADULT_SERVER:
		{
			LONG subtype;
			(*istr) >> subtype;

			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;

			pUIManager->CloseMessageBox( MSGCMD_NULL );

			switch(subtype)
			{
				//////////////////////////////////////////////
				// ����ī�� �̺�Ʈ
			case MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_OK:
				{
					UBYTE ubBuffType;
					(*istr) >> ubBuffType;

					CTString strBuff;
					switch(ubBuffType)
					{
					case 0:
						strBuff = CTString(_pNetwork->GetSkillData(423).GetName());	//�ٶ��� �������
						break;
					case 1:
						strBuff = CTString(_pNetwork->GetSkillData(424).GetName()); //���� �������
						break;
					case 2:
						strBuff = CTString(_pNetwork->GetSkillData(425).GetName()); //��ø�� �������
						break;
					case 3:
						strBuff = CTString(_pNetwork->GetSkillData(426).GetName()); //������ �������
						break;
					case 4:
						strBuff = CTString(_pNetwork->GetSkillData(427).GetName()); //ü���� �������
						break;
					case 5:
						strBuff = CTString(_pNetwork->GetSkillData(428).GetName()); //�η����� �������
						break;
					}

					strMessage.PrintF( _S(3637, "[���μ��� ���� �̺�Ʈ] �̺�Ʈ ���������κ��� %s �����ֹ��� �޾ҽ��ϴ�."), strBuff);

					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_FAILED:
				{
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_MAGIC_NOITEM:
				{
					strMessage.PrintF(_S( 1330 ,"�������� �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
				// ����ī�� �̺�Ʈ
				//////////////////////////////////////////////


				//////////////////////////////////////////////
				// ���� �̺�Ʈ
			case MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_EXCHANGE_OK:
				{
					LONG lRank, lCount;
					(*istr) >> lRank;
					(*istr) >> lCount;

					if( lRank <=100 )
						strMessage.PrintF( _S(3638, "%d��! �����մϴ�. ��ǰ���� ������ ���� %d���� ���޹����̽��ϴ�."), lRank, lCount);
					else
						strMessage.PrintF( _S(3639, "�����մϴ�. ��ǰ���� ������ ���� %d���� ���޹����̽��ϴ�."), lCount);

					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( strMessage );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_ALREADY:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(3640, "�̹� ���� �޼� ��ǰ�� �����̽��ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);

				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_FAILED:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(3641, "������ ���� �ʾ� ��ǰ�� ���� �� �����ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_CHABGEJOB_ERROR_FULLINVEN:
				{
					strMessage.PrintF(_S( 265 ,"�κ��丮 ������ �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
				// ���� �̺�Ʈ
				//////////////////////////////////////////////

				//////////////////////////////////////////////
				// ���ݼ� �̺�Ʈ
			case MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_OK:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(3642, "�����մϴ�! ������� ���ݼ��� �����Ͽ����ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_NOT_FOUND:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(3643, "���ݼ��� �õ��ϱ� ���� �ʿ��� ��ᰡ �����մϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_FAILED:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(3644, "�̷�����...������� ���ݼ��� �����Ͽ� ����� ��ᰡ ��������ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_OPEN_ADULT_SERVER_UPGRADE_ERROR_FULLINVEN:
				{
					strMessage.PrintF(_S( 265 ,"�κ��丮 ������ �����մϴ�." ));
					_pNetwork->ClientSystemMessage( strMessage, SYSMSG_ERROR );
				}
				break;
				// ���ݼ� �̺�Ʈ
				//////////////////////////////////////////////
			}
		}
		break;
		// '��ħ���� ���!' �̺�Ʈ
	case MSG_EVENT_GIFT_2007:
		{
			BYTE subtype;
			(*istr) >> subtype;

			CTString strMessage;
			CUIMsgBox_Info MsgBoxInfo;

			pUIManager->CloseMessageBox( MSGCMD_NULL );

			switch(subtype)
			{
				//����
			case MSG_CONN_EVENT_GIFT_2007_GIVE:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(2234, "�̺�Ʈ �������� ���޹޾ҽ��ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
				//�̺�Ʈ DB ����(?)
			case MSG_CONN_EVENT_GIFT_2007_CHECK_DBERROR:
				break;
				//�̹� ���� �޾���
			case MSG_CONN_EVENT_GIFT_2007_CHECK_DENY:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
				//DB ����(?)
			case MSG_CONN_EVENT_GIFT_2007_GIVE_DBERROR:
				break;
				// �κ� ����
			case MSG_CONN_EVENT_GIFT_2007_GIVE_FULL:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString( _S(116, "�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�.") );
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			}
		}
		break;
		// [070807: Su-won] EVENT_ADULT_OPEN
		//////////////////////////////////////////////////////////////////////////////////////////////////
	case MSG_EVENT_BJMONO_2007:
		{
			BYTE subtype;

			(*istr) >> subtype;

			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;
			ULONG ulCount;

			switch (subtype)
			{
			case MSG_EVENT_BJMONO_2007_TICKET_REQ:
				{
					(*istr) >> ulCount; // ����� ����

					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF(_s("%d���� ������� �޾ҽ��ϴ�."), ulCount);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_BJMONO_2007_CHANGE_TICKET_REQ:
				{
					pUIManager->CloseMessageBox(MSGCMD_BJMONO_2007_CHANGE_REQ);

					strMessage.PrintF(_s("����� ��ȯ ����"));
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_BJMONO_2007_NO_TICKET:
				{
					_pNetwork->ClientSystemMessage(_s("������ ������� �����ϴ�."), SYSMSG_ERROR);					
				}
				break;
			case MSG_EVENT_BJMONO_2007_DONT_CHANGE_TICKET:
				{
					_pNetwork->ClientSystemMessage( _s("��ȯ ���� ������� �����ϴ�."), SYSMSG_ERROR );
				}
				break;
			case MSG_EVENT_BJMONO_2007_PRICE_FULLINVEN:
				{
					_pNetwork->ClientSystemMessage(_s("�κ��丮�� �������� ������ ���� �� �����ϴ�."), SYSMSG_ERROR);
				}
			}
		}
		break;		
	case MSG_EVENT_SSHOT_2007 : // WSS_TG2007 2007/09/14
		{
			UBYTE subtype;
			(*istr) >> subtype;

			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;			

			switch (subtype)
			{
			case MSG_EVENT_SSHOT_2007_RECIVE:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF(_s("���� 10���� �޾ҽ��ϴ�."));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SSHOT_2007_ALREADY:
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF(_S( 673,"�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�."));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SSHOT_2007_NOSSHOT:					// �������� ����
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF(_s("�����ޱ� �̺�Ʈ�� �ش���� �ʽ��ϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�."));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_SSHOT_2007_FULLINVEN:				// �κ��� ���� ��
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					strMessage.PrintF(_S( 116,"�κ��丮 ������ �����Ͽ� ������ ���� �� �����ϴ�."));
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			}

		}
		break;
	case MSG_EVENT_RICHYEAR : // WSS_TG2007 2007/09/14
		{
			UBYTE subtype;
			(*istr) >> subtype;

			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;			
			MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch (subtype)
			{				
			case MSG_EVENT_RICHYEAR_ERROR_UPGRADE_NOITEM:
				strMessage.PrintF(_S(1799,"��ᰡ �����մϴ�. Ȯ���ϰ� �ٽ� �õ��Ͽ� �ֽʽÿ�."));
				break;
			case MSG_EVENT_RICHYEAR_ERROR_UPGRADE_FAILED:
				strMessage.PrintF(_S(1883,"�۹� ���׷��̵忡 �����Ͽ����ϴ�."));
				break;
			case MSG_EVENT_RICHYEAR_ERROR_NOCROP:
				strMessage.PrintF(_S(1879,"�۹��� �����ϴ�."));
				break;
			case MSG_EVENT_RICHYEAR_ERROR_ALREADY_UPGRADE:
				strMessage.PrintF(_S(2642,"�� �̻� ���׷��̵� �� �� �����ϴ�."));					
				break;
			case MSG_EVENT_RICHYEAR_ERROR_FULLINVEN:
				strMessage.PrintF(_S( 265 ,"�κ��丮 ������ �����մϴ�." ));					
				break;
			case MSG_EVENT_RICHYEAR_UPGRADE_OK:
				strMessage.PrintF(_S(1882,"�۹� ���׷��̵忡 �����Ͽ����ϴ�."));										
				break;
			case MSG_EVENT_RICHYEAR_EXCHAGE_OK:
				strMessage.PrintF(_S(1840,"�������� ���������� ���� �Ǿ����ϴ�"));										
				break;

			}		

			MsgBoxInfo.AddString(strMessage);
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_EVENT_LC_1000DAY: // ��Ʈ ī���� 1000�� �̺�Ʈ
		{
			BYTE subType, noItem;

			(*istr) >> subType;
			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;

			switch (subType)
			{
			case MSG_EVENT_LC_1000DAY_HAT_UPDATE_SUCCESS: // ���� �ɼ� ������Ʈ ����
				{
					_pNetwork->ClientSystemMessage(_S(3833, "���׷��̵带 �����Ͽ����ϴ�."), SYSMSG_ERROR);
				}
				break;
			case MSG_EVENT_LC_1000DAY_HAT_UPDATE_FAIL: // ���� �ɼ� ������Ʈ ����
				{
					(*istr) >> noItem;

					if (noItem == 1)
					{
						_pNetwork->ClientSystemMessage(_S(3834, "���׷��̵��� ������ �������� �����ϴ�." ), SYSMSG_ERROR);
					}
					else
					{
						_pNetwork->ClientSystemMessage(_S(3835, "���׷��̵带 �����Ͽ����ϴ�." ), SYSMSG_ERROR);
						_pNetwork->ClientSystemMessage(_S(3836, "�����ڰ� �ı��Ǿ����ϴ�." ), SYSMSG_ERROR);
					}
				}
				break;
			case MSG_EVENT_LC_1000DAY_FIRECRACKER_DUPLICATION: // ���� �������� �κ��� ����
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(_S(3837, "������ �� ����ϰ� ���� �ٽ� �õ��Ͽ� �ֽʽÿ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_LC_1000DAY_NOITEM: // ������ ����
				{
					MsgBoxInfo.SetMsgBoxInfo(_S(191,"Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(_S(3838, "�̺�Ʈ �������� �����Ͽ� �����ڸ� ���� �� �����ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			case MSG_EVENT_LC_1000DAY_FULLINVEN: // �κ��� ���� ��
				{
					_pNetwork->ClientSystemMessage(_S( 265 ,"�κ��丮 ������ �����մϴ�." ), SYSMSG_ERROR);
				}
				break;
			}
		}
		break;
	case MSG_EVENT_HALLOWEEN_2007:	// �ҷ��� �̺�Ʈ 2007
		{
			BYTE subType, subResult;

			(*istr) >> subType;
			(*istr) >> subResult;
			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch (subType)
			{
			case MSG_EVENT_TAKE_DEVILHEAIR:
				{
					switch (subResult)
					{
					case 0: MsgBoxInfo.AddString(_S(3781, "�Ǹ� ���� �Ӹ��츦 ���� �޾ҽ��ϴ�!")); break;
					case 1: MsgBoxInfo.AddString(_S(3782, "�Ǹ� ���� �Ӹ��츦 ���̻� ���� �� �����ϴ�!")); break;
					}
				}
				break;
			case MSG_EVENT_CHANGE_CANDYBASKET:
				{
					switch (subResult)
					{
					case 0: MsgBoxInfo.AddString(_S(3783, "������ �޾ҽ��ϴ�!")); break;
					case 1: MsgBoxInfo.AddString(_S(3784, "�ٱ��ϰ� ���� ������ ���� ���߽��ϴ�!")); break;
					}
				}
				break;
			case MSG_EVENT_CHANGE_PUMKINHEAD:
				{
					switch (subResult)
					{
					case 0: MsgBoxInfo.AddString(_S(3785, "ȣ�� �Ӹ�Ż�� ��ȯ �޾ҽ��ϴ�!")); break;
					case 1: MsgBoxInfo.AddString(_S(3786, "������ ������ ���ڶ� ��ȯ ���� ���߽��ϴ�!")); break;
					}
				}
				break;
			case MSG_EVENT_CHANGE_WITCHHAT:
				{
					switch (subResult)
					{
					case 0: 
						{
							MsgBoxInfo.AddString(_S(5111, "�ҷ��� ��ũ�� ������ ���� �޾ҽ��ϴ�.!"));
						}
						break;
					case 1: MsgBoxInfo.AddString(_S(3788, "��ǥ�� ���� ��ȯ�� ���� ���߽��ϴ�!")); break;
					}
				}
				break;
			case MSG_EVENT_CHANGE_PUMKIN:
				{
					switch (subResult)
					{
					case 0:
						{
							SLONG slItemIndex;
							(*istr) >> slItemIndex;
							strMessage.PrintF(_S(3789, "ȣ���� �ɰ������� %s��(��) ���Խ��ϴ�!"), _pNetwork->GetItemName(slItemIndex));
							MsgBoxInfo.AddString(strMessage);
						}
						break;
					case 1: MsgBoxInfo.AddString(_S(3790, "�ʿ��� ������ ���� �� ����!")); break;
					}
				}
				break;
			case MSG_EVENT_TASTE_CANDY:
				{
					switch (subResult)
					{
					case 0: MsgBoxInfo.AddString(_S(3791, "�������� ������ ��! ��� ������ �� �� ����!!")); break;
					case 1: MsgBoxInfo.AddString(_S(3792, "��~��! ����! �� ������ ���̱�!!")); break;
					case 2: MsgBoxInfo.AddString(_S(3793, "�׷����� ���� �� �ϱ�!!")); break;
					case 3: MsgBoxInfo.AddString(_S(3794, "��! �ǿܷ� ������ �� �̱�!!")); break;
					case 4: MsgBoxInfo.AddString(_S(3795, "��! õ���� ���̾�! �� ���� �޸� �����...õ..��!!")); break;
					}
				}
				break;
			case MSG_EVENT_FULL_INVEN:
				{
					_pNetwork->ClientSystemMessage(_S(3796, "�κ��丮�� �������� �������� ���� �� �����ϴ�."), SYSMSG_ERROR);
					return;
				}
				break;
			}

			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;

		/////////////////////////////////////////////////////////////////////////
		// [071122: Su-won] NEW_MOONSTONE
	case MSG_EVENT_NEW_MOONSTONE:
		{
			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			unsigned char ucIndex;
			(*istr) >> ucIndex;

			switch ( ucIndex )
			{
			case MSG_EVENT_NEW_MOONSTONE_START_REP:
				{
					LONG lAccumulate;
					(*istr) >> lAccumulate;
					pUIManager->GetGamble()->SetAccumulate( lAccumulate );
					pUIManager->GetGamble()->ShowGamble();
					pUIManager->SetCSFlagOn( CSF_MOONSTONE );
				}
				break;

			case MSG_EVENT_NEW_MOONSTONE_TRY_REP:		// ������ ���� ����
				{
					LONG lRewardItem;
					LONG lAccumulate;
					(*istr) >> lRewardItem;
					(*istr) >> lAccumulate;

					pUIManager->GetGamble()->SetSelectedItem( lRewardItem );
					pUIManager->GetGamble()->Start();
					pUIManager->GetGamble()->SetAccumulate( lAccumulate );
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_RESULT_REP:	// ������ ���� ��� ����.
				{
					LONG	lRewardItem;					
					(*istr) >> lRewardItem;
					pUIManager->GetGamble()->ShowPrizeEffect();
					//pUIManager->GetGamble()->SendAutoClick();
				}
				break;

			case MSG_EVENT_NEW_MOONSTONE_JACK_POT:
				{
					pUIManager->GetGamble()->ShowPrizeEffect();
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_OK:
				{
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_NO_MOONSTONE:
				{
					if (pUIManager->DoesMessageBoxExist(MSGCMD_MOONSTONE_MIX)) {
						pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetColorBox().Reset();
						pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);
					}

					MsgBoxInfo.AddString(_S(1439, "�������� �����ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					pUIManager->GetGamble()->ResetGamble();
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_FULLINVEN:
				{
					if (pUIManager->DoesMessageBoxExist(MSGCMD_MOONSTONE_MIX)) {
						pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetColorBox().Reset();
						pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);
					}

					MsgBoxInfo.AddString(_S(2850, "�κ��丮�� ���� á���ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					pUIManager->GetGamble()->ResetGamble();
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_MIX_SUCCESS:
				{
					pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetColorBox().Start(0, 2);
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_MIX_FAILED:
				{
					pUIManager->GetMessageBox(MSGCMD_MOONSTONE_MIX)->GetColorBox().Start(0, 2);
				}
				break;
			case MSG_EVENT_NEW_MOONSTONE_MIX_MISS:
				{
					if (pUIManager->DoesMessageBoxExist(MSGCMD_MOONSTONE_MIX))
						pUIManager->CloseMessageBox(MSGCMD_MOONSTONE_MIX);

					MsgBoxInfo.AddString(_S(2466, "���ۿ� �������� ���� �����Դϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			}
		}
		break;
		// [071122: Su-won] NEW_MOONSTONE
		/////////////////////////////////////////////////////////////////////////
	case MSG_EVENT_XMAS_2007: // X-MAS 2007 eons 071204
		{
			UBYTE ubSucess;
			UBYTE ubType;
			SLONG slRemain;

			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			(*istr) >> ubType;

			switch (ubType)
			{
			case MSG_EVENT_XMASTREE_ADD_POINT: // ���
				{
					(*istr) >> ubSucess;

					if (ubSucess == 1)
					{
						MsgBoxInfo.AddString(_S(3954, "ũ�������� Ʈ���� ����� �������� �����ϴ�"));
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
				}
				break;
			case MSG_EVENT_XMASTREE_GET_BLESS: // �ູ
				{
					(*istr) >> ubSucess;

					if (ubSucess == 1)
					{
						MsgBoxInfo.AddString(_S(3955, "������ ũ�������� �ູ�� ���� �� �����ϴ�. ��� �� �ٽ� �õ��Ͽ��ֽʽÿ�"));
						pUIManager->CreateMessageBox(MsgBoxInfo);
					}
				}
				break;
			case MSG_EVENT_XMASTREE_DROP_ITEM: // ���� ����
				{
					(*istr) >> slRemain;

					strMessage.PrintF(_S(3956, "%d�� �� ũ�������� Ʈ�������� ũ�������� ������ �������� �˴ϴ�"), slRemain);
					_UIAutoHelp->SetGMNotice(strMessage, 0xFFAA33FF);
				}
				break;
			case MSG_EVENT_XMAS_PUZZLE_CHECKITEM_REP:
				{
					(*istr) >> ubSucess;
					if (ubSucess == 0)
					{
						pUIManager->GetMinigame()->OpenMinigame(MSG_EVENT_XMAS_2007);
					}
					else
					{
						if (pUIManager->DoesMessageBoxExist(MSGCMD_NULL))
							return;
						CUIMsgBox_Info msgInfo;
						CTString strMessage = _S(191, "Ȯ��");
						msgInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
						strMessage.PrintF(_S(5813, "���, ��ŸŬ�ν� ������ ���׿�? ��ŸŬ�ν� ������ ������ ������������ �� �� �����. ������ �ϰ� �ʹٸ�, ������ 1������ 9�������� ��� ��� �ϼ��� ��ŸŬ�ν��� �����;� �ؿ�."));
						msgInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(msgInfo);
					}
				}
				break;
			case MSG_EVENT_XMAS_PUZZLE_START_REP:
				{
					(*istr) >> ubSucess;
					if (ubSucess == 0)
					{
						pUIManager->GetMinigame()->SetButtonState(BTN_STATE_START_CONTINUE);
					}
					else
					{
						if (pUIManager->DoesMessageBoxExist(MSGCMD_NULL))
							return;
						CUIMsgBox_Info msgInfo;
						CTString strMessage = _S(191, "Ȯ��");
						msgInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
						strMessage.PrintF(_S(5813, "���, ��ŸŬ�ν� ������ ���׿�? ��ŸŬ�ν� ������ ������ ������������ �� �� �����. ������ �ϰ� �ʹٸ�, ������ 1������ 9�������� ��� ��� �ϼ��� ��ŸŬ�ν��� �����;� �ؿ�."));
						msgInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(msgInfo);
					}
				}
				break;
			case MSG_EVENT_XMAS_PUZZLE_SELECT_REP:
				{
					UBYTE result, winCount, userSelect, npcSelect;
					(*istr) >> result >> winCount >> userSelect >> npcSelect;
					pUIManager->GetMinigame()->SetMinigameResult(winCount, userSelect, npcSelect, result);
				}
				break;
			case MSG_EVENT_XMAS_PUZZLE_CONTINUE_REP:
				{
					pUIManager->GetMinigame()->SetButtonState(BTN_STATE_START_CONTINUE);
				}
				break;
			case MSG_EVENT_XMAS_PUZZLE_END_REP:
				{
					UBYTE ubWinCount;
					SLONG slItemIndex;
					LONGLONG llItemCount;
					(*istr) >> ubWinCount >> slItemIndex >> llItemCount;
					if (slItemIndex != -1 && llItemCount != -1)
					{
						CUIMsgBox_Info msgInfo;
						CTString strMessage = _S(191, "Ȯ��");
						msgInfo.SetMsgBoxInfo(strMessage, UMBS_OK, UI_NONE, MSGCMD_NULL);
						strMessage.PrintF(_S(1840, "�������� ���������� ���� �Ǿ����ϴ�"));
						msgInfo.AddString(strMessage);
						pUIManager->CreateMessageBox(msgInfo);
					}
					pUIManager->GetMinigame()->Close();
				}
				break;
			}
		}
		break;
		// [071211: Su-won] EVENT_NEWYEAR_2008
	case MSG_EVENT_NEWYEAR_2008:
		{
			INDEX iChar;
			CTString strCharName;

			(*istr) >> iChar;
			(*istr) >> strCharName;

			CTString strMsg;
			strMsg.PrintF(_S(3965, "%s�����κ��� ���غ� ���� �������� �����λ簡 �����Ͽ����ϴ�."), strCharName);
			_pNetwork->ClientSystemMessage( strMsg, SYSMSG_ERROR );

			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OKCANCEL, UI_NONE, MSGCMD_EVENT_NEWYEAR_2008);
			MsgBoxInfo.AddString(_S(3966, "�ظ��� ������ �����Ǿ����ϴ�. �����Ͻðڽ��ϱ�?"));
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_EVENT_SAKURA_2008:
		{
			UBYTE ubType;
			(*istr) >> ubType;

			switch (ubType)
			{
			case MSG_EVENT_SAKURAEVENT_2008_ERROR:
				{
					UBYTE ubError;
					(*istr) >> ubError;

					if( ubError == 0 )
					{

					}
					else if( ubError == 1 )
					{
						CUIMsgBox_Info MsgBoxInfo;
						MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

						MsgBoxInfo.AddString(_S(4114, "��� ������ ���� �ʽ��ϴ�."));
						pUIManager->CreateMessageBox(MsgBoxInfo);

						return;
					}
				}
				break;
			case MSG_EVENT_SAKURAEVENT_2008_ITEMCHANGE:
				{
					CTString strName;
					INDEX iItemIndex;

					(*istr) >> strName;
					(*istr) >> iItemIndex;

					CTString strNotice;
					strNotice.PrintF( _S(4115, "%s���� ���ɼ��� ���ڸ� ���� %s�� ȹ���Ͽ����ϴ�."), strName, _pNetwork->GetItemName(iItemIndex));

					_UIAutoHelp->SetGMNotice( strNotice );

					return;
				}
				break;
			}
		}
		break;
	case MSG_EVENT_NOM:
		{
			UBYTE ubType;
			(*istr) >> ubType;

			switch(ubType)
			{
			case MSG_EVENT_NOM_OK:						// ���� ����
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4150, "���� ��ȭƼ���� ��ƶ�! �̺�Ʈ�� ����Ǿ����ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					return;
				}
				break;
			case MSG_EVENT_NOM_ERROR_ALREADY_APPLY:		// �̹� ���� ��
				break;
			case MSG_EVENT_NOM_ERROR_FULL_INVEN:		// �κ��丮�� ����
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4151, "�κ��丮 ������ �����Ͽ� ������ ���޹��� ���Ͽ����ϴ�. ������ Ȯ���ϰ� ������ �ٽ� �õ��Ͽ� �ֽʽÿ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					return;
				}
				break;
			case MSG_EVENT_NOM_ERROR_ITEM_FAIL:			// ������ ����
				break;
			case MSG_EVENT_NOM_LOTTERY_USE_OK:			// ���� ��� ����
				break;
			case MSG_EVENT_NOM_MOVIE_TICKET_OK:
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4152, "���� ��ȭ Ƽ���� ��ϵǾ����ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					return;
				}
				break;
			}
		}
		break;
	case MSG_EVENT_PHOENIX:
		{
			UBYTE ubType;
			(*istr) >> ubType;
			switch(ubType)
			{
			case MSG_EVENT_PHOENIX_ERROR_ALREADY_APPLY:
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);  // 9423

					MsgBoxInfo.AddString(_S(4235, "�̹� �Ǵн��� ��ϵǾ� �ֽ��ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
					
					return;
				}
				break;
			case MSG_EVENT_PHOENIX_ERROR_REQUIREMENT:
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4236, "�Ǵн��� �� �ڰ��� ���� �ʽ��ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);
					
					return;
				}
				break;
			case MSG_EVENT_PHOENIX_ERROR_FULL_INVENTORY:
				{
					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

					MsgBoxInfo.AddString(_S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�."));
					pUIManager->CreateMessageBox(MsgBoxInfo);

					return;
				}
				break;
			case MSG_EVENT_PHOENIX_OK:
			{
				if (pUIManager->GetQuest()->GetNpcIndex() == 834)
				{
					FLOAT fNPCPosX = pUIManager->GetQuest()->GetNpcPosX();
					FLOAT fNPCPosZ = pUIManager->GetQuest()->GetNpcPosZ();

					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "È®ÀÎ"), UMBS_OKCANCEL, UI_NONE, MSGCMD_EVENT_PHOENIX, -1, fNPCPosX, fNPCPosZ);
					MsgBoxInfo.AddString(_S(4238, "ÇÇ´Ð½º°¡ µÉ ÀÚ°ÝÀÌ ÃæºÐÇÕ´Ï´Ù. °¡ÀÔÇÏ½Ã°Ú½À´Ï±î?"));
					pUIManager->CreateMessageBox(MsgBoxInfo);

				}
				return;
			}
			break;
			}
		}
		break;
	case MSG_EVENT_PHOENIX_SUCCESS:
		{
			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(_S(4239, "�Ǵн��� ��ϵǾ����ϴ�."));
			pUIManager->CreateMessageBox( MsgBoxInfo );

			return;			
		}
		break;

#ifdef DEMIGOD
	case MSG_EVENT_DEMIGOD:
	{
		UBYTE ubType;
		(*istr) >> ubType;
		switch (ubType)
		{
		case MSG_EVENT_DEMIGOD_ERROR_ALREADY_APPLY:
		{
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);  // 9423

			MsgBoxInfo.AddString(_S(9423, "�̹� �Ǵн��� ��ϵǾ� �ֽ��ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);
			
			return;
		}
		break;
		case MSG_EVENT_DEMIGOD_ERROR_REQUIREMENT:
		{
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			MsgBoxInfo.AddString(_S(9421, "�Ǵн��� �� �ڰ��� ���� �ʽ��ϴ�.")); // demi god pwesty
			pUIManager->CreateMessageBox(MsgBoxInfo);
			
			return;
		}
		break;
		case MSG_EVENT_DEMIGOD_ERROR_FULL_INVENTORY:
		{
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			MsgBoxInfo.AddString(_S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);

			return;
		}
		break;
		case MSG_EVENT_DEMIGOD_OK:
		{
			
			if (pUIManager->GetQuest()->GetNpcIndex() == 2050) // demi god pwesty
			{
				FLOAT fNPCPosX = pUIManager->GetQuest()->GetNpcPosX();
				FLOAT fNPCPosZ = pUIManager->GetQuest()->GetNpcPosZ();
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OKCANCEL, UI_NONE, MSGCMD_EVENT_DEMIGOD, -1, fNPCPosX, fNPCPosZ);
				MsgBoxInfo.AddString(_S(9422, "�Ǵн��� �� �ڰ��� ����մϴ�. �����Ͻðڽ��ϱ�?"));
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
			return;
		}
		break;
		}
	}
	break;
	case MSG_EVENT_DEMIGOD_SUCCESS:
	{
		CUIMsgBox_Info	MsgBoxInfo;
		MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
		MsgBoxInfo.AddString(_S(4239, "�Ǵн��� ��ϵǾ����ϴ�."));
		pUIManager->CreateMessageBox(MsgBoxInfo);

		return;
	}
	break;
#endif

	case MSG_EVENT_REQUITAL:
		{
			UBYTE ubType;
			(*istr) >> ubType;

			CUIMsgBox_Info	MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch(ubType)
			{
			case MSG_EVENT_REQUITALM_OK:						// ���� ����
				{
					MsgBoxInfo.AddString(_S(1840,"�������� ���������� ���� �Ǿ����ϴ�"));

				}break;
			case MSG_EVENT_REQUITAL_FAIL:					// ���� ����
			case MSG_EVENT_REQUITAL_FAIL_TIME:				// ���� �ð��� ������
			case MSG_EVENT_REQUITAL_FAIL_TIME_NOPLAY:		// �ش� ��¥�� ������ ���� �ʾƼ� ����
			case MSG_EVENT_REQUITAL_FAIL_CREATE_TIME:		// ������ ������ ������ ��¥�� �ʹ� �̸�
				{
					MsgBoxInfo.AddString(_S(1722, "������ ������ �� �ִ� ������ �ƴմϴ�."));
				}break;
			case MSG_EVENT_REQUITAL_ERROR_ALREADY_APPLY:		// �̹� ���� ��
				{
					MsgBoxInfo.AddString(_S(673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�."));
				}break;
			case MSG_EVENT_REQUITAL_ERROR_FULL_INVEN:		// �κ��丮�� ����				
				{
					MsgBoxInfo.AddString(_S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�."));
				}break;
			}		
			pUIManager->CreateMessageBox( MsgBoxInfo );

			return;
		}
		break;
	case MSG_EVENT_NEW_AFRON_2009:
		{
			UBYTE ubType;
			(*istr) >> ubType;

			if (ubType == MSG_EVENT_GIVE_ITEM_SUCCESS)
			{
				CUIMsgBox_Info	MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(_S(1840,"�������� ���������� ���� �Ǿ����ϴ�"));
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;

		// ($E_WC2010) [100511: selo] 2010 ���ư� ������
	case MSG_EVENT_WORLDCUP_2010:
		{
			UBYTE ubType;
			UBYTE ubError;
			(*istr) >> ubType;

			switch(ubType)
			{
			case MSG_EVENT_WORLDCUP2010_TRADE_REP:				// �౸�� ��ȯ �亯
				{					
					(*istr) >> ubError;					

					switch(ubError)
					{
					case MSG_EVENT_WORLDCUP2010_TRADE_ERROR_SUC:	// �౸�� ��ȯ ����
						{
							INDEX ubTradeType;
							(*istr) >> ubTradeType;

							if( ubTradeType ==  1)
							{
								if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT1) )
									pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->CreateMessageBoxL( _S(4879, "Ȳ�� �౸������ ��ȯ"), UI_SHOP, MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, TRUE, _S(4880, "����� ��Ȯ�Ͽ�. ������ �� �鷯�ֽÿ�."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, FALSE, _S( 191, "Ȯ��" ) );
							}
							else
							{
								if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT1) )
									pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->CreateMessageBoxL( _S(4881, "���� ���� ���ڷ� ��ȯ"), UI_SHOP, MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, TRUE, _S(4882, "�����Ͽ�. �̺�Ʈ �Ⱓ ���ȿ��� �������� ã�� �ֽñ���."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, FALSE, _S( 191, "Ȯ��" ) );
							}
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TRADE_ERROR_BALL:	// �౸�� ���� ���� 
						{
							INDEX nTradeType;
							(*istr) >> nTradeType;

							if( nTradeType ==  1)
							{
								if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT1) )
									pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->CreateMessageBoxL( _S(4879, "Ȳ�� �౸������ ��ȯ"), UI_SHOP, MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, TRUE, _S(4898, "�౸�� ������ �����Ͽ� Ȳ�� �౸������ �ٲ� �帮�� ���� �� ����. �� �� ���ؿ��ÿ�."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, FALSE, _S( 191, "Ȯ��" ) );
							}
							else
							{
								if( pUIManager->DoesMessageBoxLExist(MSGLCMD_EVENT_WORLDCUP_EVENT1) )
									pUIManager->CloseMessageBoxL(MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->CreateMessageBoxL( _S(4881, "���� ���� ���ڷ� ��ȯ"), UI_SHOP, MSGLCMD_EVENT_WORLDCUP_EVENT1);

								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, TRUE, _S(4899, "����~ �� �ڼ� ������� �ƴϿ�. 50��! 50��! ������ ���� �־�� �Ͽ�."),-1,0xa3a1a3ff);
								pUIManager->AddMessageBoxLString(MSGLCMD_EVENT_WORLDCUP_EVENT1, FALSE, _S( 191, "Ȯ��" ) );
							}
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TRADE_ERROR_FAIL:	// �౸�� ��ȯ ����
						{
							// Do Nothing
						}
						break;
					}

				}
				break;

			case MSG_EVENT_WORLDCUP2010_TOTO_REP:				// �¸����� TOTO ��� �亯
				{
					(*istr) >> ubError;
					switch( ubError )
					{
					case MSG_EVENT_WORLDCUP2010_TOTO_ERROR_SUC:
						{
							if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS) )
								pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

							CUIMsgBox_Info	MsgBoxInfo;
							MsgBoxInfo.SetMsgBoxInfo(_S(4921, "�̺�Ʈ ����"), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);
							MsgBoxInfo.AddString(_S(4922, "�̺�Ʈ ���� ����"));
							pUIManager->CreateMessageBox(MsgBoxInfo);
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TOTO_ERROR_FAIL:
						{
							if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS) )
								pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

							CUIMsgBox_Info	MsgBoxInfo;
							MsgBoxInfo.SetMsgBoxInfo(_S(4921, "�̺�Ʈ ����"), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);
							MsgBoxInfo.AddString(_S(4923, "�̺�Ʈ ���� ����"));
							pUIManager->CreateMessageBox(MsgBoxInfo);
						}
						break;
					}
				}
				break;

			case MSG_EVENT_WORLDCUP2010_TOTO_STATUS_REP:		// TOTO ���� ��Ȳ �亯
				{
					(*istr) >> ubError;
					switch( ubError )
					{
					case MSG_EVENT_WORLDCUP2010_TOTO_STATUS_ERROR_SUC:
						{
							INDEX nResultType = 0;
							INDEX nTotoType = 0;
							INDEX nCountryItem1 = 0;
							INDEX nCountryItem2 = 0;

							(*istr) >> nResultType;							
							(*istr) >> nCountryItem1;							

							switch( nResultType )
							{
							case EVENT_WORLDCUP_2010_EVENT2_SEL2:
								{
									if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS) )
										pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

									CTString strDesc;
									CTString strDesc2;
									int nBtnCnt = 1;
									CUIMsgBox_Info	MsgBoxInfo;
									MsgBoxInfo.SetMsgBoxInfo(_S(4911, "�� ���� ��Ȳ"), UMBS_OK | UMBS_BUTTONEX, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);
									strDesc.PrintF(_S(4924, "���� ��� : %s"), _S(4908, "��� ���� ����"));
									strDesc2.PrintF(_S(4925, "��� ���� : %s"), _pNetwork->GetItemName(nCountryItem1));

									MsgBoxInfo.SetBtnType(UBET_ITEM, CItemData::ITEM_ETC, CItemData::ITEM_ETC_EVENT, nBtnCnt);
									MsgBoxInfo.AddString(strDesc);
									MsgBoxInfo.AddString(strDesc2);
									pUIManager->CreateMessageBox(MsgBoxInfo);								

									CUIMessageBox* pMsgBox = pUIManager->GetMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

									if( pMsgBox )
									{
										//pMsgBox->SetBtnEx(0, btn);
										//pMsgBox->GetBtnEx(0).SetEnable(FALSE);
										pMsgBox->GetBtnEx()->setData(UBET_ITEM, nCountryItem1);
									}									
								}
								break;
							default:
								{
									CTString strTitle;
									CTString strDesc;
									int nCommand;

									strTitle = _S(4908, "��� ���� ����");
									strDesc.PrintF(_S(4927, "�̹� ��� ���� ���� ������� %s�� ����ϼ̽��ϴ�. �����Ͻðڽ��ϱ�?"), _pNetwork->GetItemName(nCountryItem1));
									nCommand = MSGCMD_EVENT_WORLDCUP_EVENT2_REREQ;

									if( pUIManager->DoesMessageBoxExist(nCommand) )
										pUIManager->CloseMessageBox(nCommand);

									CUIMsgBox_Info	MsgBoxInfo;
									MsgBoxInfo.SetMsgBoxInfo(strTitle, UMBS_OKCANCEL, UI_QUEST, nCommand);
									MsgBoxInfo.AddString(strDesc);
									pUIManager->CreateMessageBox(MsgBoxInfo);
								}
								break;
							}
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TOTO_STATUS_ERROR_FAIL:
						{
							INDEX nResultType;
							(*istr) >> nResultType;

							switch( nResultType )
							{							
							case EVENT_WORLDCUP_2010_EVENT2_SEL2:		// ���� ��Ȳ
								{
									if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS) )
										pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

									CUIMsgBox_Info MsgBoxInfo;
									MsgBoxInfo.SetMsgBoxInfo(_S(4911, "�� ���� ��Ȳ"), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

									MsgBoxInfo.AddString(_S(4930, "���� �̺�Ʈ ���� ������ �������� �ʽ��ϴ�."));
									pUIManager->CreateMessageBox(MsgBoxInfo);									
								}
								break;
							default:
								{
									pUIManager->GetQuest()->CreateMessageBox_WorldCup2010_Event2(nResultType);
								}
								break;
							}
						}
						break;
					}
				}
				break;

			case MSG_EVENT_WORLDCUP2010_TOTO_GIFT_REP:			// TOTO ��ǰ ��û �亯
				{
					CTString strMessage;

					(*istr) >> ubError;
					switch( ubError )
					{
					case MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_SUC:
						{
							strMessage = _S(2926, "���������� ����ǰ�� �����Ͽ����ϴ�.");
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_INVEN:
						{
							strMessage = _S(265, "�κ��丮 ������ �����մϴ�.");
						}
						break;
					case MSG_EVENT_WORLDCUP2010_TOTO_GIFT_ERROR_FAIL:
						{
							strMessage = _S(1845, "������ ������ ���� �Ͽ����ϴ�.");
						}
						break;
					}

					if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS) )
						pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);

					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(4912, "��÷ ���� �ޱ�" ), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT2_STATUS);					
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;

			case MSG_EVENT_WORLDCUP2010_ATTENDANCE_REP:			// �⼮ �̺�Ʈ �亯
				{
					CTString strMessage;

					(*istr) >> ubError;
					switch( ubError )
					{
					case MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_SUC:		// �⼮ üũ ����
						{							
							strMessage = _S(4943, "���� �����մϴ�. �� ����~!");							
						}
						break;
					case MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_ALREADY:	// �̹� �⼮ ��	
						{
							strMessage = _S(4944, "�̹� �����̳׿�. ������ �� �̻� �帱 �� �����~!");							
						}
						break;
					case MSG_EVENT_WORLDCUP2010_ATTENDANCE_ERROR_FAIL:		// �⼮ üũ ����
						{
							strMessage = _S(4945, "����ī�� �ޱ⿡ ���� �Ͽ����ϴ�.");							
						}
						break;
					}

					if( pUIManager->DoesMessageBoxExist(MSGCMD_EVENT_WORLDCUP_EVENT3) )
						pUIManager->CloseMessageBox(MSGCMD_EVENT_WORLDCUP_EVENT3);

					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(4937, "����ī�� �ޱ�" ), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT3);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;

			case MSG_EVENT_WORLDCUP2010_SUPPORTCARD_REP:		// ���� ī�� ��ȯ �亯
				{
					CTString strMessage;

					(*istr) >> ubError;
					switch( ubError )
					{
					case MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_SUC:		// ���� ī�� ��ȯ ����
						{
							strMessage = _S(2926, "���������� ����ǰ�� �����Ͽ����ϴ�.");
						}
						break;
					case MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_CARD:		// ���� ī�� ���� ����
						{
							strMessage = _S(2912, "������ ������ �����մϴ�.");
						}
						break;
					case MSG_EVENT_WORLDCUP2010_SUPPORTCARD_ERROR_FAIL:		// ���� ī�� ��ȯ ����
						{
							strMessage = _S(1845, "������ ������ ���� �Ͽ����ϴ�.");
						}
						break;
					}

					CUIMsgBox_Info MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(4937, "����ī�� �ޱ�" ), UMBS_OK, UI_QUEST, MSGCMD_EVENT_WORLDCUP_EVENT3);
					MsgBoxInfo.AddString(strMessage);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			}
		}
		break;
	case MSG_EVENT_PROMOTION2:
		{	// ���� ���θ�� �̺�Ʈ
			UBYTE ubType;
			(*istr) >> ubType;

			switch( ubType )
			{
			case MSG_EVENT_PROMOTION2_COUPON_USE_REP:
				{
					RecievePromotionEventMessage( istr );
				}
				break;
			}
		}
		break;

		// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	case MSG_EVENT_ATTENDANCE_2011:
		{
			UBYTE ubType;
			(*istr) >> ubType;

			switch( ubType )
			{
			case MSG_EVENT_ATTENDANCE_2011_NOTICE:
				{
					SLONG attendanceRate;

					(*istr) >> attendanceRate;

					pUIManager->GetNotice()->ShowAttendanceMessage( attendanceRate );
				}
				break;

			case MSG_EVENT_ATTENDANCE_2011_CALC_RATE:
				{
					SLONG attendanceRate, enchantRate, expSpRate;

					(*istr) >> attendanceRate;
					(*istr) >> enchantRate;
					(*istr) >> expSpRate;

					pUIManager->GetNotice()->ShowAttendanceNotice( attendanceRate, enchantRate, expSpRate );
				}
				break;

			case MSG_EVENT_ATTENDANCE_2011_INDIVIDUAL_REWARD_REP:
				{
					UBYTE ubResult;
					CTString strTemp;

					(*istr) >> ubResult;

					switch( ubResult )
					{
					case 0: // ���� ����
						{
							strTemp = _S( 1840, "�������� ���������� ���� �Ǿ����ϴ�." );
						}
						break;
					case 1: // �⼮ ���� ����
						{
							strTemp = _S( 5346, "�⼮ ��� ������ ����� �� ���� ���� �� �ֽ��ϴ�."  );
						}
						break;
					case 2: // �̹� ���޵Ǿ���
						{
							strTemp = _S(673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�.");
						}
						break;
					case 3: // �κ� ��������
						{
							strTemp = _S(4237, "�κ��丮�� ������ ���� �մϴ�. �κ��丮�� ��� �� �ٽ� �õ����ֽñ� �ٶ��ϴ�.");
						}
						break;
					case 4: // ���� ���� ��¥�� �ƴ�
						{
							strTemp = _S(5347, "���� ���� �� �ִ� ������ ���� �ƴմϴ�.");
						}
						break;
					}

					CUIMsgBox_Info	MsgBoxInfo;
					MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);
					MsgBoxInfo.AddString(strTemp);
					pUIManager->CreateMessageBox(MsgBoxInfo);
				}
				break;
			}
		}
		break;

		// [2011/01/18 : Sora] �⼮ �̺�Ʈ
	case MSG_EVENT_ENCHANT_RATE:
		{
			UBYTE ubIsStart;
			SLONG attendanceRate;

			(*istr) >> ubIsStart;
			(*istr) >> attendanceRate;

			pUIManager->GetInventory()->GetEventPopUp()->ClearNoticePopUp();

			if( ubIsStart )
			{
				pUIManager->GetInventory()->GetEventPopUp()->SetPercent( attendanceRate );

				pUIManager->GetInventory()->GetEventPopUp()->SetTitle(_S( 100, "�̺�Ʈ" ));
				pUIManager->GetInventory()->GetEventPopUp()->SetNoticeMessage( _S(5344, "������\n��þƮ ����Ȯ��"), 0xFFFF40FF );
			}
		}
		break;
	case MSG_EVENT_USER_COMEBACK:
		{	// �޸� ���� ���� �̺�Ʈ
			CTString strMessage;

			UBYTE ubResult;
			(*istr) >> ubResult;

			switch ( ubResult )
			{
			case MSG_EVENT_USER_COMEBACK_ERROR_SUC:
				{	// ���� ����
					strMessage = _S( 2234, "�̺�Ʈ �������� ���� �޾ҽ��ϴ�." );
				}
				break;
			case MSG_EVENT_USER_COMEBACK_ERROR_NO_MORE:
				{	// �̹� ���� ����
					strMessage = _S( 673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�." );
				}
				break;
			case MSG_EVENT_USER_COMEBACK_ERROR_NOT_USER:
				{	// ���� ����� �ƴ�
					strMessage = _S( 5357, "�̺�Ʈ ����� �ƴմϴ�." );
				}
				break;
			}

			if ( strMessage.Length() > 0 )
			{
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(100, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	case MSG_EVENT_CHAR_BIRTHDAY:
		{
			CTString strMessage, strMessageAdd;
			UBYTE ubResult;
			(*istr) >> ubResult;

			switch( ubResult )
			{
			case MSG_EVENT_CHAR_BIRTHDAY_GIFT_REP:
				{
					UBYTE ubErrorType;
					(*istr) >> ubErrorType;
					switch( ubErrorType )
					{
					case MSG_EVENT_CHAR_BIRTHDAY_ERROR_SUC:
						{
							strMessage = _S( 2234, "�̺�Ʈ �������� ���� �޾ҽ��ϴ�." );
						}
						break;
					case MSG_EVENT_CHAR_BIRTHDAY_ERROR_FAIL:
						{
							strMessage = _S( 674, "�̺�Ʈ �������� ���� �� �����ϴ�." );
						}
						break;
					}
				}
				break;
			case MSG_EVENT_CHAR_BIRTHDAY_BDAY_REP:
				{
					INDEX iYear;
					UBYTE ubMonth, ubDay;
					(*istr) >> iYear;

					if ( iYear > 0)
					{
						(*istr) >> ubMonth;
						(*istr) >> ubDay;
						strMessage.PrintF( _S( 5356, "ĳ���� �������� %d�� %d�� %d�� �Դϴ�."), iYear, (int)ubMonth, (int)ubDay );
					}
				}
				break;
			}
			if ( strMessage.Length() > 0 )
			{
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(100, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
		// [2011/03/04 : Sora] ����2�� ���θ�� �̺�Ʈ
	case MSG_EVENT_EUR2_PROMOTION:
		{
			CTString strMessage;
			UBYTE ubResult;

			(*istr) >> ubResult;

			switch( ubResult )
			{
			case MSG_EVENT_EUR2_PROMOTION_SUCCESS:
				{
					strMessage = _S( 1840, "�������� ���������� ���� �Ǿ����ϴ�" );
				}
				break;
			case MSG_EVENT_EUR2_PROMOTION_WRONG_KEY:
				{
					strMessage = _S( 2405, "��û�� ���� ��ȣ�� �������� �ʽ��ϴ�." );
				}
				break;
			case MSG_EVENT_EUR2_PROMOTION_ALREADY_USED:
				{
					strMessage = _S( 2406, "�̹� ���޹��� ���� ��ȣ �Դϴ�." );
				}
				break;
			case MSG_EVENT_EUR2_PROMOTION_LACK_INVENTORY:
				{
					strMessage = _S( 675, "�κ��丮 ������ �����ؼ� �̺�Ʈ �������� ���� �� �����ϴ�." );
				}
				break;
			case MSG_EVENT_EUR2_PROMOTION_SYS_ERROR_NOT_USED:
				{
					strMessage = _S(1845, "������ ������ ���� �Ͽ����ϴ�.");
				}
				break;
			case MSG_EVENT_EUR2_PROMOTION_CANT_USE_USER:
				{
					strMessage = _S( 673, "�̺�Ʈ �������� �̹� ���޵Ǿ����ϴ�." );
				}
				break;
			}
			if ( strMessage.Length() > 0 )
			{
				CUIMsgBox_Info MsgBoxInfo;
				MsgBoxInfo.SetMsgBoxInfo(_S(100, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
				MsgBoxInfo.AddString(strMessage);
				pUIManager->CreateMessageBox(MsgBoxInfo);
			}
		}
		break;
	case MSG_EVENT_MUSICAL_ZORRO:
		{
			CUIMsgBox_Info MsgBoxInfo;
			MsgBoxInfo.SetMsgBoxInfo(_S(100, "�̺�Ʈ" ), UMBS_OK, UI_NONE, MSGCMD_NULL);
			MsgBoxInfo.AddString(_S( 5591, "������ ���ΰ����� �����̺�Ʈ�� ���������� �����Ͽ����ϴ�."));
			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_BUFF_NPC_REQ:	// �ҷ��� �̺�Ʈ 2007
		{
			BYTE subType, subResult;

			(*istr) >> subType;
			(*istr) >> subResult;
			CUIMsgBox_Info MsgBoxInfo;
			CTString strMessage;
			MsgBoxInfo.SetMsgBoxInfo(_S(191, "Ȯ��"), UMBS_OK, UI_NONE, MSGCMD_NULL);

			switch (subType)
			{
			case MSG_BUFF_2021_REQ:
				{
					switch (subResult)
					{
					case 0:	MsgBoxInfo.AddString(_S(8505, "Not Enough Buff Tokens")); break;
					case 1: MsgBoxInfo.AddString(_S(8506, "Success")); break;
					}
				}
				break;
				case MSG_BUFF_FRAG_2021_REQ:
				{
					switch (subResult)
					{
					case 0: MsgBoxInfo.AddString(_S(8504, "Not Enough Buff Fragments")); break;
					case 1: MsgBoxInfo.AddString(_S(8506, "Success")); break;
					}
				}
				break;
			case MSG_BUFF_FULL_INVEN:
				{
					_pNetwork->ClientSystemMessage(_S(3796, "�κ��丮�� �������� �������� ���� �� �����ϴ�."), SYSMSG_ERROR);
					return;
				}
				break;
			}

			pUIManager->CreateMessageBox(MsgBoxInfo);
		}
		break;
	case MSG_EVENT_NEW_LIST:
	{
		pUIManager->GetInventory()->m_pEventActiveUI->ReceiveList(istr);
	}
	break;
	case MSG_EVENT_NEW_ACTIVATED:
	{
		pUIManager->GetInventory()->m_pEventActiveUI->ReceiveEventActive(istr);
	}
	break;
	case MSG_EVENT_NEW_DEACTIVATED:
	{
		pUIManager->GetInventory()->m_pEventActiveUI->ReceiveEventDeactive(istr);
	}
	break;
	}
	
}
