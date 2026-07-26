#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>

#include <Engine/GameDataManager/GameDataManager.h>
#include <Common/Packet/ptype_reserved_gm_command.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Help/Util_Help.h>
#include "Reza.h"
//#include "ReZaBot.h" 
#include <Engine/Entities/InternalClasses.h>//player entity stuff

#include <Engine/Contents/function/PremiumChar.h>

#include <Engine/Interface/UIInternalClasses.h>

/*
#include <Engine/Interface/UIButton.h>
#include <Engine/Interface/UICheckButton.h>
#include <Engine/Interface/UIComboBox.h>
#include <Engine/Interface/UISlideBar.h>
#include <Engine/Interface/UICheckButton.h>
*/
//#include <Engine/Graphics/Adapter.h>

#include <Engine/Info/MyInfo.h> // stats stuff etarget
#include <Engine/Interface/UIAutoHelp.h> // search item
#include <Engine/Object/ActorMgr.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Contents/Base/UICharacterInfoNew.h>

//skills
#include <Engine/Entities/Skill.h>
#ifdef REZABOT
ReZaBotUI::ReZaBotUI(void)
	:
		m_pDrag(NULL)
	,	m_nOriX(0), m_nOriY(0)
{
	
	setInherit(false);		// â �ȿ� ���� MsgProc â���� ��ȭ. �ٸ��� ��� ����
	
}

ReZaBotUI::~ReZaBotUI()
{
	EndBOT();
	if(RezabotTimerThread){
		delete RezabotTimerThread;
	}
	Destroy();
}

void ReZaBotUI::initialize()
{
	//botlogic
	
	
	//FORM DRAG
	m_pDrag = (CUIText*)findUI("text_drag");
	//UI TAB
	Tab_Win = (CUITab*)findUI("Tab_Win");
	Window_BG = (CUIImageSplit*) findUI("WindowBG");
	Controls = (CUIBase*) findUI("Controls");
	//BUTTONS
	int i;
	std::string strBtnId[eBTN_MAX] = { "btn_close","btn_mini", "btn_botstart", "btnMoveTest"};

	for (i = 0; i < eBTN_MAX; ++i)
		m_pBtn[i] = (CUIButton*)findUI(strBtnId[i].c_str());

	if( m_pBtn[eBTN_CLOSE] != NULL)
	{
		m_pBtn[eBTN_CLOSE]->SetCommandFUp(boost::bind(&ReZaBotUI::CloseReZaBotUI, this));
	}
	if( m_pBtn[eBTN_MINI] != NULL)
	{
		m_pBtn[eBTN_MINI]->SetCommandFUp(boost::bind(&ReZaBotUI::Mini, this));
	}
	if( m_pBtn[eBTN_START] != NULL)
	{
		m_pBtn[eBTN_START]->SetCommandFUp(boost::bind(&ReZaBotUI::StartBot, this));
	}
	if(m_pBtn[eBTN_MOVETEST]!= NULL ) {
		m_pBtn[eBTN_MOVETEST]->SetCommandFUp(boost::bind(&ReZaBotUI::MoveTest,this)); 

	}
	//EDITS 
	

	std::string strEditId[eEDIT_MAX] = {
		"ed_maxdist","ed_hptrigskill1",
		"ed_hptrigskill2", "ed_mptrigskill1","ed_mptrigskill2","ed_hptrigbuff1",
		"ed_hptrigbuff2","ed_mptrigbuff1",
		"ed_mptrigbuff2","ed_hptrigitem1","ed_hptrigitem2","ed_mptrigitem1",
		"ed_mptrigitem2"
	};
	for (i = 0; i < eEDIT_MAX; ++i)
	{
		m_pEdit[i] = (CUIEditBox*)findUI(strEditId[i].c_str());
		m_pEdit[i]->SetString("0");
	}

	//ICONS
	std::string strIconId[eICON_MAX] = {
		"icon_skill1", "icon_skill2","icon_skill3","icon_skill4",
		"icon_skill5", "icon_skill6","icon_skill7","icon_skill8",
		"icon_hptrigskill1","icon_hptrigskill2",
		"icon_mptrigskill1" , "icon_mptrigskill2",
		"icon_buff1","icon_buff2","icon_buff3","icon_buff4",
		"icon_buff5","icon_buff6","icon_buff7","icon_buff8",
		"icon_hptrigbuff1","icon_hptrigbuff2","icon_mptrigbuff1","icon_mptrigbuff2",
		"icon_hptrigitem1","icon_hptrigitem2","icon_mptrigitem1","icon_mptrigitem2",
		"icon_petfeed1","icon_petfeed2",
		"icon_timeritem1","icon_timeritem2","icon_timeritem3","icon_timeritem4","icon_botticket"
	};
	
	for (i = 0; i < eICON_MAX; ++i)
	{
		m_pIcon[i] = (CUIIcon*)findUI(strIconId[i].c_str());
		_resetIcon(i);
	}
		
	//Check boxes
	std::string strChkId[eCHK_MAX] = {
		"chk_atk","chk_def",
		"chk_wanpos","chk_retpos","chk_skill","chk_buff","chk_item",
		"chk_ig1","chk_ig2", "chk_ig3","chk_ig4",
		"chk_pickup", "chk_p1pickup", "chk_selltoshop"
	
	};

	for (i = 0; i < eCHK_MAX; i++)
		m_pChk[i] = (CUICheckButton*)findUI(strChkId[i].c_str());
	
	for(i = 0 ; i  < 2  ; i++ )//Mode checks
	{
		m_pChk[eCHK_ATK+i]->SetCommandF(boost::bind(&ReZaBotUI::Mode, this,i));
	}
	for(i = 0 ; i  < 2  ; i++ )//Positioning checks
	{
		m_pChk[eCHK_WANDER+i]->SetCommandF(boost::bind(&ReZaBotUI::Positioning, this,i));
	}
	for(i = 0 ; i  < 4  ; i++ )//ignition checks
	{
		m_pChk[eCHK_IG1+i]->SetCommandF(boost::bind(&ReZaBotUI::Ignition, this,i+1));
	}
	
	//preset check
	if(m_pChk[eCHK_RETURN])
		m_pChk[eCHK_RETURN]->SetCheck(FALSE);
	
	if(m_pChk[eCHK_WANDER])
		m_pChk[eCHK_WANDER]->SetCheck(TRUE);
	
	if(m_pChk[eCHK_ATK])
		m_pChk[eCHK_ATK]->SetCheck(TRUE);
	
	for(int i = 0 ; i < 4 ;  i++) {
		if(m_pChk[eCHK_IG1+i])
			m_pChk[eCHK_IG1+i]->SetCheck(FALSE);
	}
	//if(m_pChk[eCHK_IG4])
			//m_pChk[eCHK_IG4]->SetCheck(TRUE);

	if(m_pChk[eCHK_SKILL])
			m_pChk[eCHK_SKILL]->SetCheck(FALSE);
	
	if(m_pChk[eCHK_BUFF])
			m_pChk[eCHK_BUFF]->SetCheck(FALSE);
	
	if(m_pChk[eCHK_ITEM])
			m_pChk[eCHK_ITEM]->SetCheck(FALSE);
	
	if(m_pChk[eCHK_PICKUP])
		m_pChk[eCHK_PICKUP]->SetCheck(FALSE);
	
	if(m_pChk[eCHK_P1PICKUP])
		m_pChk[eCHK_P1PICKUP]->SetCheck(FALSE);

	//list 

	m_pList = (CUIList*) findUI("list_outtext");
	m_plistScroll = (CUIScrollBar*)findUI("list_scroll");
	m_pListItem = (CUIBase*)(m_pList->findUI("list_item_001")->Clone()); 

	if(m_plistScroll)
	{
		m_plistScroll->SetScrollPos(0);
		m_pList->setScroll(m_plistScroll);
	}
	m_pList->DeleteAllListItem();
	m_plistScroll->setVertical(true);

	if (m_plistScroll != NULL)//settings the uitool failed to save fml
	{
		m_pList->SetItemShowNum(4);
		m_plistScroll->setThumbUnit(4);
		m_plistScroll->SetItemsPerPage(4);
	}
	
	//get list item template

	
	//Text Boxes
	std::string strTextId = "text_nas";
	m_pTextNas = (CUIText* ) findUI(strTextId.c_str());
	m_pTextNas->SetText(CTString("0"));

	strTextId = "lblCoord";
	m_pTextCoord = (CUIText* ) findUI(strTextId.c_str());

	
	strTextId = "lblDist";
	m_pTextDist = (CUIText* ) findUI(strTextId.c_str());
	

	Reset();

	m_pIcon[eICON_BOTTICKET]->clearIconData();
	m_pIcon[eICON_BOTTICKET]->setTooltip(_S(9335,"Select a Bot Ticket to enable the system."));
	

	CTextureData* m_ptdPopupTexture = _pTextureStock->Obtain_t( CTString( "Data\\Interface\\NamePopup.tex" ) );
	FLOAT	fTexWidth = m_ptdPopupTexture->GetPixWidth();
	FLOAT	fTexHeight = m_ptdPopupTexture->GetPixHeight();

	//render rect for bot icon.
	m_rcREZABOT.SetRect(0, 0 ,DREZABOTW,DREZABOTH); 
	m_rtREZABOT.SetUV(DREZABOTX
									,DREZABOTY
									,DREZABOTX +DREZABOTW
									,DREZABOTY +DREZABOTH
									,fTexWidth
									,fTexHeight
									);

}
void ReZaBotUI::OpenReZaBotUI(int ticketid,int ticketvindex)
{
	if(IsVisible() == TRUE )
		return;
	
	//Reset();
	Hide(TRUE);
	SetVisible(FALSE);
	//m_pIcon[eICON_BOTTICKET]->clearIconData();
	//m_pIcon[eICON_BOTTICKET]->setTooltip(_S(9335,"Select a Bot Ticket to enable the system.").str_String);

	m_pIcon[eICON_BOTTICKET]->setData(UBET_ITEM,ticketid,ticketvindex);
	CNetworkMessage ProcRezaBOT((UBYTE)MSG_REZA);
	ProcRezaBOT << (DWORD)REZA_REZABOT;
	ProcRezaBOT << (DWORD)REZABOT_OPEN;
	
	_pNetwork->SendToServerNew(ProcRezaBOT);
	

}
void ReZaBotUI::OpenReZaBotUI()
{
	//m_pIcon[eICON_BOTTICKET]->clearIconData();
	//m_pIcon[eICON_BOTTICKET]->setTooltip("Select a Bot Ticket to enable the system.");
	//Reset();
	Hide(TRUE);
	SetVisible(FALSE);
	CNetworkMessage ProcRezaBOT((UBYTE)MSG_REZA);
	ProcRezaBOT << (DWORD)REZA_REZABOT;
	ProcRezaBOT << (DWORD)REZABOT_OPEN;

	_pNetwork->SendToServerNew(ProcRezaBOT);
}

void ReZaBotUI::CloseReZaBotUI()
{
	Clear();
	Hide(TRUE);
	SetVisible(FALSE);
	CUIManager::getSingleton()->RearrangeOrder(UI_REZABOT, FALSE);
}

void ReZaBotUI::Mini(){
	int curstate = Tab_Win->GetHide();
	switch(curstate){
	case 0:
		{
			Tab_Win->Hide(TRUE);

			SetSize(GetWidth(),75);
			Window_BG->SetSize(Window_BG->GetWidth(),75,false);
			Window_BG->UpdateSplit();
			Controls->updatePosition();
		}

		break;
	case 1:
		{
			Tab_Win->Hide(FALSE);
			SetSize(GetWidth(),390);
			Window_BG->SetSize(Window_BG->GetWidth(),390,false);
			Window_BG->UpdateSplit();
			Controls->updatePosition();
		}
		break;
	}
	
}

float ReZaBotUI::distcalc(FLOAT3D p1, FLOAT3D p2) {

	float x1,y1,z1; 
	float x2,y2,z2;

	x1 = p1.vector[0];
	x2 = p2.vector[0]; 
	
	y1 = p1.vector[1];
	y2 = p2.vector[1];

	z1 = p1.vector[2];
	z2 = p2.vector[2];


    float d = sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) +  
                pow(z2 - z1, 2) * 1.0); 
  

    return d; 

}

void ReZaBotUI::MoveTest() {

	CEntity			*penPlEntity;
	CPlayerEntity	*penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity( 0 );
	penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);
	
	//ObjInfo* pInfo = ObjInfo::getSingleton();

	CTString strTarget;// = pInfo->GetTargetName(eTARGET);

		//if(pInfo->IsTargetActive(eTARGET) && (pInfo->GetTargetType(eTARGET) == MOB))
		//{
	FLOAT3D vDelta = StartPos;//FLOAT3D(1111,163,952);
	strTarget.PrintF("pos[%0.0f,%0.0f,%0.0f]" ,vDelta.vector[0],vDelta.vector[1], vDelta.vector[2]);
		//	AddText("Move", strTarget.str_String);
			//penPlayerEntity->CommandAttack();
			penPlayerEntity->moveto(vDelta);//pInfo->GetTargetEntity(eTARGET)->en_plPlacement.pl_PositionVector);
		//}
	
}

void ReZaBotUI::StartBot()
{

	CNetworkMessage ProcRezaBOT((UBYTE)MSG_REZA);
	ProcRezaBOT << (DWORD)REZA_REZABOT;
	ProcRezaBOT << (DWORD)REZABOT_START;
	if( !m_pIcon[eICON_BOTTICKET]->IsEmpty()){
		ProcRezaBOT << (DWORD)m_pIcon[eICON_BOTTICKET]->getItems()->ItemData->index;
		ProcRezaBOT << (DWORD)m_pIcon[eICON_BOTTICKET]->getItems()->Item_UniIndex;
	}
	else
	{
		ProcRezaBOT << (DWORD) -1 ; 
		ProcRezaBOT << (DWORD) -1 ; 
	}

	_pNetwork->SendToServerNew(ProcRezaBOT);

}

void ReZaBotUI::EndBOT(){
		
		//bBotison=false;
		TerminateThread(RezabotTimerThread,0); 
		//CloseHandle(RezabotTimerThread) ;
		//RezabotTimerThread->Terminate(0);

		m_pBtn[eBTN_START]->SetText(_S(9321,"Start Bot"));
		/*if(RezabotTimerThread)
		{
			delete RezabotTimerThread;
		}
		*/
}
void ReZaBotUI::Mode(int id)
{	
	if(id == 0) 
	{
		AddText(_S(9309,"Mode").str_String,_S(9313,"Attack").str_String);
	}
	if(id == 1){
		AddText(_S(9309,"Mode").str_String,_S(9314,"Defend").str_String);
	}
	m_pChk[eCHK_ATK]->SetCheck(id==0? true: false);
	m_pChk[eCHK_DEF]->SetCheck(id==1? true: false);	
	//todo set logic variables
}
void ReZaBotUI::Positioning(int id)
{	
	if(id == 0) 
	{
		AddText(_S(9334,"Position").str_String,_S(9316,"Wander").str_String);
	}
	if(id == 1){
		AddText(_S(9334,"Position").str_String,_S(9317,"Return").str_String);
	}
	m_pChk[eCHK_WANDER]->SetCheck(id==0? true: false);
	m_pChk[eCHK_RETURN]->SetCheck(id==1? true: false);	
	//todo set logic variables

}
void ReZaBotUI::Ignition(int lvl){
	
	//handle the level selected
	switch(lvl)//todo set logic variables
	{
	case 1:
		AddText(_S(9320,"Ignition").str_String,"1");
	break;
	case 2:
		AddText(_S(9320,"Ignition").str_String,"2");
	break;
	case 3:
		AddText(_S(9320,"Ignition").str_String,"3");
	break;
	case 4:
		AddText(_S(9320,"Ignition").str_String,"4");
	break;
	}
	//fix checkboxes to only allow one selected.
	int level =lvl-1;
	for(int i =0 ; i < 4 ; i ++ ) {
		if(i == level)
		{
			/*bool wtf =m_pChk[eCHK_IG1+i]->IsChecked() == TRUE? true:false;
			m_pChk[eCHK_IG1+i]->SetCheck(!wtf);*/
		}
		else
		{
			m_pChk[eCHK_IG1+i]->SetCheck(false);
		}
	} 
	
}
#define IGNI1_BUF				1062
#define IGNI2_BUF				1063
#define IGNI3_BUF				1064
#define IGNI4_BUF				1065
void ReZaBotUI::UpdateEP(int lvl)
{	
	if (m_pChk != NULL) {
		if (m_pChk[0] == NULL)
			return;
	}

	int useig = 0;
	if(m_pChk[eCHK_IG1]->IsChecked())
		useig = 1;
	if(m_pChk[eCHK_IG2]->IsChecked())
		useig = 2;
	if(m_pChk[eCHK_IG3]->IsChecked())
		useig = 3;
	if(m_pChk[eCHK_IG4]->IsChecked())
		useig = 4;
	if(useig !=0)
	{
		if(
		!_pUIBuff->IsSkillBuff(IGNI1_BUF)&&
		!_pUIBuff->IsSkillBuff(IGNI2_BUF)&&
		!_pUIBuff->IsSkillBuff(IGNI3_BUF)&&
		!_pUIBuff->IsSkillBuff(IGNI4_BUF)
		){

		if (lvl>=useig){
		
			_pNetwork->SendEnergySkillMessage();

		}
		}
	}

	
}

void ReZaBotUI::Reset()
{
	bBotison=false;
	
	b_pickup = false;
	b_petpick = false;
	b_useitem = false;
	b_usebuff = false;

	lastcount = 0;//count of items in world
	pickupc = 0;//pickup attempts
	failcount = 0;

	skillCount = 0;

	itemCount = 0; 
	nas_earned = 0;

	lasttarget = NULL;
	WasSkilling = false ;
	aftersocial = false;

	StartPos = FLOAT3D(0,0,0);

	m_ilastThought = 0;
	RezabotTimerThread = NULL;


	distmax = 0;

	
}

void ReZaBotUI::Clear()
{
	
}


//listbox output text handle
void ReZaBotUI::AddText(char* SystemName , char* text){
	
		extern HWND _hwndMain;
		if(IsIconic(_hwndMain))
		{
			return;
		}

	if(checkparentshidden(m_pList))
		return;

	CUIBase* TempItem; 
	TempItem =(CUIBase*) m_pListItem->Clone();
	
	CTString TempString("");
	TempString.PrintF("%s->%s" ,SystemName,text);
		
	CUIText* TempTextBox = (CUIText*)TempItem->findUI("TEXT");
	TempTextBox->SetText(TempString);

	m_pList->AddListItem(TempItem);
	
	OutTextUpdate();
}
void ReZaBotUI::OutTextUpdate()
{
	/*
	int nMaxItem = m_pList->getListItemCount();AN
	
	m_pList->UpdateScroll(nMaxItem);
	m_plistScroll->SetScrollPos(nMaxItem - m_pList->GetItemShowNum());
	m_pList->UpdateList();
	*/
	if (m_pList->GetScroll() != NULL)
	{
		int nCurScrollPos = m_pList->GetScroll()->GetScrollPos();
		int nShowCount = m_pList->GetItemShowNum();
		int	nOldItemCount = m_pList->getListItemCount()-1;
		if(nOldItemCount >= MAX_BOTHISTORY)
		{
			m_pList->deleteListItem(0);
		}


		if (nOldItemCount - nShowCount == nCurScrollPos ||
			(nCurScrollPos == 0 && (nOldItemCount - nShowCount < 0)))
			nCurScrollPos = m_pList->getListItemCount() - m_pList->GetItemShowNum();

		m_pList->UpdateScroll(m_pList->getListItemCount());
 		m_pList->GetScroll()->SetScrollCurPos(nCurScrollPos);
 	}

	m_pList->UpdateList();
}


//open bot
void ReZaBotUI::tacobuttplug()
{
	if(IsVisible() == TRUE )
		return;
	OutTextUpdate();
	SetPos( m_rcOriginPos.Left, m_rcOriginPos.Top );
	SetVisible(TRUE);
	Hide(FALSE);
	CUIManager::getSingleton()->RearrangeOrder(UI_REZABOT, TRUE);
	
}


#pragma region Network handles

void ReZaBotUI::do_ReZaBotUI(CNetworkMessage* istr){
		int type = 0 ;
		(*istr) >> type ;

		switch (type)
		{
		case REZABOT_OPEN:
				tacobuttplug();
			break;
		case REZABOT_START:
				anotherbuttplug();
			break;
		case REZABOT_STOP:
				EndBOT();
			break;
	
		case REZABOT_CHECK:
			{
				EndBOT();
				m_pIcon[eICON_BOTTICKET]->clearIconData();
				m_pIcon[eICON_BOTTICKET]->setTooltip("Select a Bot Ticket to enable the system.");
			}


		default :
			//log and kick 
			break; 

		}
	}


#pragma endregion


#define PETHP 197
#define PETSTA 154
bool ReZaBotUI::IsItemMatched( CItems* pItem ,int slot){ 

	if(slot > eICON_SKILLS_END )
	{
		
		switch(slot){
		

		case eICON_PETFEED1:
		case eICON_PETFEED2:
			if (pItem->ItemData->index == PETSTA || pItem->ItemData->index == PETHP)
			{
				return true;
			}
			else
			{
				return false;
			}
		break;

		}
	return true;
	}

	return false;
}

bool ReZaBotUI::CheckItem( CItems* pItem ,int slot)
{
	
	if (pItem == NULL)
		return false;

	CItemData* pItemData = pItem->ItemData;

	if (pItemData == NULL)
		return false;

	if(!IsItemMatched(pItem,slot)) {
		return false;
	}

	return true;
}

bool ReZaBotUI::CheckSkillIcon(CSkill* Skill ,bool Buff )
{
	
	return true;
}

//start bot
void ReZaBotUI::anotherbuttplug(){
		

	CEntity			*penPlEntity;
	penPlEntity = CEntity::GetPlayerEntity( 0 );

	StartPos =  penPlEntity->en_plPlacement.pl_PositionVector;
	
	CTString strTarget;// = pInfo->GetTargetName(eTARGET);
	strTarget.PrintF("[%0.0f,%0.0f]" ,StartPos.vector[0], StartPos.vector[2]);
	m_pTextCoord->SetText(strTarget);
	strTarget.PrintF("[0]m %s" , _S(9332,"From Start Point").str_String);
	m_pTextDist->SetText(strTarget);

	distmax = atoi(m_pEdit[eEDIT_MAXDIST]->GetString());

	if(_pNetwork->MyCharacterInfo.char_botting == 1)
	//if(bBotison == true)
	{
		//_pNetwork->MyCharacterInfo.char_botting = 1;
		//RezabotTimerThread = new cThreadWrapper(&ReZaBotUI::HandleTimer);
		//RezabotTimerThread->Start(NULL);
		RezabotTimerThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HandleTimer, NULL, NULL, NULL); //Create Thread to handle this client. The index in the socket array for this thread is the value (i).
		
		//bBotison= true;
		m_pBtn[eBTN_START]->SetText(_S(9333,"Stop Bot"));

	}
	else
	{
		
		//_pNetwork->MyCharacterInfo.char_botting = 0;
		TerminateThread(RezabotTimerThread,0); 
		CloseHandle(RezabotTimerThread);
		Reset();

		m_pBtn[eBTN_START]->SetText(_S(9321,"Start Bot"));
	}
}


bool ReZaBotUI::IdleCheck()
{		
	CEntity			*penPlEntity;
	CPlayerEntity	*penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity( 0 );
	penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);

	if(penPlayerEntity->IsAttacking())
	{
		//AddText("Player","Attacking");
	}
	else if( penPlayerEntity->IsSkilling())
	{
		//AddText("Player","Skilling");
	}
	else if ( penPlayerEntity->IsMoving()){
		//AddText("Player", "Moving");
	}
	
	else if (penPlayerEntity->IsSocialActing())
	{
		//AddText("Player", "Social");
		aftersocial = true;
	}
	else if(((CPlayerEntity*)CEntity::GetPlayerEntity(0))->IsIdle()) 
	{
		/*
			virtual BOOL IsIdle	if( IsSitting() || IsSkilling() || IsMoving() || IsAlreadyDie() )
		*/
		//AddText("Player","Idle");
		return true;
	}
	return false;
	
}

ReZaBotUI::BotAction ReZaBotUI::Think()
{
	

	//###### VARIABLES
	CUIManager* pUIManager = CUIManager::getSingleton();
	//my player
	CEntity			*penPlEntity;
	CPlayerEntity	*penPlayerEntity;
	penPlEntity = CEntity::GetPlayerEntity( 0 );
	penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);

	CTString strTarget("");
	strTarget.PrintF("[%0.0f]m %s",distcalc(penPlayerEntity->en_plPlacement.pl_PositionVector,StartPos),_S(9332,"From Start Point").str_String);
	m_pTextDist->SetText(strTarget);

	int myx = _pNetwork->MyCharacterInfo.x;
	int myz =_pNetwork->MyCharacterInfo.z;

	//target
	ObjInfo* pInfo = ObjInfo::getSingleton();

	int petStaDiff = pInfo->GetMyPetInfo()->fMaxHungry - pInfo->GetMyPetInfo()->fHungry;
	int petHpDiff = pInfo->GetMyPetInfo()->fMaxHealth - pInfo->GetMyPetInfo()->fHealth;

	 if(penPlayerEntity->IsMoving()){
			
			int dist = distcalc(penPlayerEntity->en_plPlacement.pl_PositionVector,StartPos);
			if(dist < 3 ) 
			{
				penPlayerEntity->StopMove();
				return ACT_MAX;
			}
	 }
	//###### LOGIC
	if(aftersocial)
	{
		if (!penPlayerEntity->IsSocialActing()){
			aftersocial = false;
			return ACT_MAX;
			/*
			penPlayerEntity->StopMove();
			penPlayerEntity->ClearMove();
			penPlayerEntity->ClearActionApplied();
			penPlayerEntity->ClearNextPosition();
			penPlayerEntity->SetTargetMe();
			*/
		}
	}
	if(penPlayerEntity->IsSkilling())
	{
		WasSkilling= true;
		return ACT_MAX;
	}
	
	if(WasSkilling)
	{
		WasSkilling = false;
		if(b_usebuff)
		{
			if(m_pChk[eCHK_BUFF]->IsChecked())
			{
				if(UseBuffs())
				{
					return ACT_MAX;
				}
			}
		}
		if(lasttarget!= NULL) 
		{	
			if(m_pChk[eCHK_ATK]->IsChecked())
			{
				penPlayerEntity->SetTarget(lasttarget);
				lasttarget = NULL;
			}
			b_usebuff= false;
		}
	
	}
	if(lasttarget != NULL)
	{
		if(pInfo->IsTargetActive(eTARGET) && (pInfo->GetTargetType(eTARGET) == MOB))
		{
			lasttarget = NULL;
		}
	}
	if(skillCount == 1)
	{
		b_useitem=true;
	}

	if(m_pChk[eCHK_ITEM]->IsChecked() && b_useitem )
	{
		itemCount++;
		if(itemCount >4) 
		{
			itemCount = 0;
				
			b_useitem= false;
		}
			
		UseItems();
	}
	if(penPlayerEntity->IsAttacking())
	{
		lastselected= NULL;
		if(m_pChk[eCHK_BUFF]->IsChecked())
		{
			
			int imhp= _pNetwork->MyCharacterInfo.hp;
			int imhpmax= _pNetwork->MyCharacterInfo.maxHP;
			int immp= _pNetwork->MyCharacterInfo.mp;
			int immpmax =_pNetwork->MyCharacterInfo.maxMP;
			float fHPRatio = ((float)((float)imhp /(float) imhpmax)) * 100.0f; 
			float fMPRatio = ((float)((float)immp /(float) immpmax)) * 100.0f; 
			//
			
			bool trig = false;
			for(int i = eICON_HPBUFF1 ; i <= eICON_MPBUFF2 ; i ++) 
			{
				int hptrig = 0;
				int mptrig = 0;
				switch(i)
				{
					case eICON_HPBUFF1:
						hptrig = atoi(m_pEdit[eEDIT_HPBUFF1]->GetString());
						break;
					case eICON_HPBUFF2:
						hptrig = atoi(m_pEdit[eEDIT_HPBUFF2]->GetString());
						break;
					case eICON_MPBUFF1:
						mptrig = atoi(m_pEdit[eEDIT_MPBUFF1]->GetString());
						break;
					case eICON_MPBUFF2:
						mptrig = atoi(m_pEdit[eEDIT_MPBUFF2]->GetString());
						break;
					default:
						continue;
				}
				
				if ( hptrig==0 && mptrig==0)
					continue;

				if(fHPRatio < hptrig )
				{
					trig = true;
					break;
				}
				if(fMPRatio < mptrig )
				{	
					trig= true;
					break;
				}

			}	
			//
			int skill1 = m_pIcon[eICON_BUFF1]->getIndex();
			int skill2 = m_pIcon[eICON_BUFF2]->getIndex();
			int skill3 = m_pIcon[eICON_BUFF3]->getIndex();
			int skill4 = m_pIcon[eICON_BUFF4]->getIndex();
			int skill5 = m_pIcon[eICON_BUFF5]->getIndex();
			int skill6 = m_pIcon[eICON_BUFF6]->getIndex();
			int skill7 = m_pIcon[eICON_BUFF7]->getIndex();
			int skill8 = m_pIcon[eICON_BUFF8]->getIndex();

			if(
				(skill1 !=-1 && !_pUIBuff->IsSkillBuff(skill1)) ||
				(skill2 !=-1 && !_pUIBuff->IsSkillBuff(skill2)) ||
				(skill3 !=-1 && !_pUIBuff->IsSkillBuff(skill3)) ||
				(skill4 !=-1 && !_pUIBuff->IsSkillBuff(skill4)) ||
				(skill4 !=-1 && !_pUIBuff->IsSkillBuff(skill5)) ||
				(skill4 !=-1 && !_pUIBuff->IsSkillBuff(skill6)) ||
				(skill4 !=-1 && !_pUIBuff->IsSkillBuff(skill7)) ||
				(skill4 !=-1 && !_pUIBuff->IsSkillBuff(skill8)) ||
				(trig == true)
				)
			{
					b_usebuff= true;
					lasttarget =pInfo->GetTargetEntity(eTARGET);
					
					return ACT_BUFF;
			}


			
		}
		if(m_pChk[eCHK_SKILL]->IsChecked() )// && ! b_useitem)
		{
			UseSkills();	
		}
			
		if(!m_pChk[eCHK_SKILL]->IsChecked())
		b_useitem= true;
	}
	
	if(IdleCheck())
	{
		if(m_pChk[eCHK_P1PICKUP]->IsChecked() && b_petpick){
			b_petpick = false;
			return ACT_P1PICK;
		}
		else{
		b_petpick = true;
		}
		if(m_pChk[eCHK_PICKUP]->IsChecked() && b_pickup  ) // replace with check items on ground
		{
				
			int curcount = ACTORMGR()->GetObjectCount(eOBJ_ITEM);
			if(pickupc == 0)
			{
				failcount=0;
			}
				
			if(lastcount == curcount)
				failcount++;

			if (failcount > 0)
			{
				if ( curcount < lastcount)
				failcount = 0 ; 
			}

			lastcount = curcount;
			pickupc++;
				
			if (pickupc >= 3)
			{
				pickupc = 0;
				lastcount=0;
				b_pickup = false;

			} 

			return ACT_PICKUP;
		}
		if(m_pChk[eCHK_RETURN]->IsChecked()){

			int dist = distcalc(penPlayerEntity->en_plPlacement.pl_PositionVector,StartPos);
			if(dist >  distmax + 2 ) 
			{
				penPlayerEntity->moveto(StartPos);
				return ACT_MAX;
			}
		}
		if(!pInfo->IsTargetActive(eTARGET) || (pInfo->GetTargetType(eTARGET) != MOB /*||pInfo->GetTargetType(eTARGET) != CHARACTER*/)  )
		{
			b_useitem=true;
			
			if(m_pChk[eCHK_DEF]->IsChecked())
			{
				if(m_pChk[eCHK_BUFF]->IsChecked())
				{
					b_usebuff= true;
					penPlayerEntity->SetTargetMe();
					return ACT_BUFF;
				}
			}

			if(m_pChk[eCHK_ATK]->IsChecked())
			{
			
				return ACT_SEARCH;
			}
		}

		if(pInfo->IsTargetActive(eTARGET))
		{
			
			if(m_pChk[eCHK_DEF]->IsChecked())
			{
				if ( pInfo->GetTargetType(eTARGET) == CHARACTER)
				{
					if(pInfo->GetTargetEntity(eTARGET)->IsPlayer())
					{
						return ACT_BUFF;
					}
				}
			}
			
			if(m_pChk[eCHK_ATK]->IsChecked())
			{
				if(lastselected == pInfo->GetTargetEntity(eTARGET))
				{
					samecheck ++;
				}
				else
				{
					samecheck = 0;
				}

				if ( pInfo->GetTargetType(eTARGET) == MOB)
				{
					if(samecheck < 4) {

					lastselected = pInfo->GetTargetEntity(eTARGET);
					b_pickup = true;
#ifdef BOT_USE_SKILL_ONLY
					return ACT_SKILL;
#else
					return ACT_ATK;
#endif

					}
					else
					{
						pInfo->TargetClear();
						lastselected = NULL;
						return ACT_SEARCH;
					}
				}
			}
			
		}

		
	}
	
	return ACT_MAX;
	

}

void ReZaBotUI::DoAction(BotAction Action)
{
CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
ObjInfo* pInfo = ObjInfo::getSingleton();


	switch (Action)
	{
		case ACT_ITEM:
			{
				UseItems();
			}
		break;
		case ACT_ATK:
			{
				CTString strTarget = pInfo->GetTargetName(eTARGET);
				AddText(_S(9313,"Attack").str_String, strTarget.str_String);
				penPlayerEntity->CommandAttack();
			}
			break;
		case ACT_SKILL:
			{
				UseSkills();
			}
		break;
		case ACT_BUFF:
			{
				UseBuffs();

			}
		break;
		case ACT_PICKUP:
			
			{
				
				PickUpItems();
				
			}
		break;
		case ACT_P1PICK:
			UseSocialAction(40);
			break;
		case ACT_SEARCH:
			{
			
				SearchEnemy();
				if( pInfo->IsTargetActive(eTARGET) && pInfo->GetTargetType(eTARGET) == MOB )
				{
					CTString strTarget = pInfo->GetTargetName(eTARGET);
					AddText(_S(9331,"Search").str_String, strTarget.str_String);
				}
			}
		break;
		case ACT_MAX:
			//AddText("Action","Waiting");
		return;
			
			break;

	}
	
}

static INT64 g_InputTabTime = 0;
bool ReZaBotUI::SearchEnemy(){

	if (g_InputTabTime > 0)
		{
			INT64 DeltaTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds() - g_InputTabTime;
			
			if (DeltaTime < 500)
			{
				return false;
			}
		}
		
		g_InputTabTime = _pTimer->GetHighPrecisionTimer().GetMilliseconds();
		CEntity			*penPlEntity;
		CPlayerEntity	*penPlayerEntity;
		penPlEntity = CEntity::GetPlayerEntity( 0 );
		penPlayerEntity = static_cast<CPlayerEntity *>(penPlEntity);
		penPlayerEntity->EnemyTargetSelected_InputTab();
		return true;
}
void ReZaBotUI::UseSocialAction(int index) {
	CUIManager* pUIMgr = UIMGR();
	pUIMgr->GetCharacterInfo()->UseAction(index);
}
void ReZaBotUI::PickUpItems(){
	CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
	
	penPlayerEntity->BOTSearchItem(0+failcount);
	

}
void ReZaBotUI::UseBuff(int SkillIdx)
{
	CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
	penPlayerEntity->SetTargetMe();
	CSkill	&Skill1 = _pNetwork->GetSkillData(SkillIdx);

	if (Skill1.GetIndex() == SkillIdx)
	{
		CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
		penPlayerEntity->UseSkill(SkillIdx);
	}
}
bool ReZaBotUI::UseBuffs()
{
	int SkillIdx =0 ;
	int imhp= _pNetwork->MyCharacterInfo.hp;
	int imhpmax= _pNetwork->MyCharacterInfo.maxHP;
	int immp= _pNetwork->MyCharacterInfo.mp;
	int immpmax =_pNetwork->MyCharacterInfo.maxMP;
	float fHPRatio = ((float)((float)imhp /(float) imhpmax)) * 100.0f; 
	float fMPRatio = ((float)((float)immp /(float) immpmax)) * 100.0f; 
	//hp triggers
	for(int i = eICON_HPBUFF1 ; i <= eICON_MPBUFF2 ; i ++) 
	{
		int hptrig = 0;
		int mptrig = 0;
		int iconidx = 0;
		switch(i)
		{
			case eICON_HPBUFF1:
				SkillIdx = m_pIcon[eICON_HPBUFF1]->getIndex();
				hptrig = atoi(m_pEdit[eEDIT_HPBUFF1]->GetString());
				iconidx = i;
				break;
			case eICON_HPBUFF2:
				SkillIdx = m_pIcon[eICON_HPBUFF2]->getIndex();
				hptrig = atoi(m_pEdit[eEDIT_HPBUFF2]->GetString());
				iconidx = i;
				break;
			case eICON_MPBUFF1:
				SkillIdx = m_pIcon[eICON_MPBUFF1]->getIndex();
				mptrig = atoi(m_pEdit[eEDIT_MPBUFF1]->GetString());
				iconidx = i;
				break;
			case eICON_MPBUFF2:
				SkillIdx = m_pIcon[eICON_MPBUFF2]->getIndex();
				mptrig = atoi(m_pEdit[eEDIT_MPBUFF2]->GetString());
				iconidx = i;
				break;
			default:
				continue;
		}
		if(_pUIBuff->IsSkillBuff(m_pIcon[i]->getIndex())){
			continue;
		}

		if ( hptrig==0 && mptrig==0)
			continue;
		if(SkillIdx == -1)
			continue;
		if(iconidx == 0)
			continue;

		if(fHPRatio < hptrig )
		{
			UseBuff(SkillIdx);
			return true;
		}
		if(fMPRatio < mptrig )
		{	
			UseBuff(SkillIdx); 
			return true;
		}

	}
	SkillIdx = 0;
	//go thru the skills and see which are set and not on our character yet
	for(int i = eICON_BUFF1; i <= eICON_BUFF8 ; i++)
	{
		if(m_pIcon[i]->getIndex() != 0 )
		{	
			if(!_pUIBuff->IsSkillBuff(m_pIcon[i]->getIndex()))
			{
				SkillIdx = m_pIcon[i]->getIndex();
				break;
			}	
		}
	}
	if(SkillIdx !=0)
	{
		UseBuff(SkillIdx);
		return true;
	}
	
	return false;


	/*
		
		case 1:
			SkillIdx = m_pIcon[eICON_SKILL1]->getIndex();
		break;
		case 2:
			SkillIdx = m_pIcon[eICON_SKILL2]->getIndex();
		break;
		case 3:
			SkillIdx = m_pIcon[eICON_SKILL3]->getIndex();
		break;
		case 4:
			 SkillIdx = m_pIcon[eICON_SKILL4]->getIndex();
		break;
		default:
			skillCount=1;
			SkillIdx = m_pIcon[eICON_SKILL1]->getIndex();
		break;

	}
	if(SkillIdx != 0 )
	{
		UseSkill(SkillIdx);
		skillCount++;
		if( skillCount > 4)
		{
			skillCount = 1;
		}
	}*/
}
void ReZaBotUI::UseSkill(int SkillIdx){
	CSkill	&Skill1 = _pNetwork->GetSkillData(SkillIdx);

	if (Skill1.GetIndex() == SkillIdx)
	{
		CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
		penPlayerEntity->UseSkill(SkillIdx);
	}
}
void ReZaBotUI::UseSkills(){
	int SkillIdx =0 ;
	
	
	int imhp= _pNetwork->MyCharacterInfo.hp;
	int imhpmax= _pNetwork->MyCharacterInfo.maxHP;
	int immp= _pNetwork->MyCharacterInfo.mp;
	int immpmax =_pNetwork->MyCharacterInfo.maxMP;
	float fHPRatio = ((float)((float)imhp /(float) imhpmax)) * 100.0f; 
	float fMPRatio = ((float)((float)immp /(float) immpmax)) * 100.0f; 
	//hp triggers
	for(int i = eICON_HPSKILL1 ; i <= eICON_MPSKILL2 ; i ++) 
	{
		int hptrig = 0;
		int mptrig = 0;
		int iconidx = 0;
		switch(i)
		{
			case eICON_HPSKILL1:
				SkillIdx = m_pIcon[eICON_HPSKILL1]->getIndex();
				hptrig = atoi(m_pEdit[eEDIT_HPSKILL1]->GetString());
				iconidx = i;
				break;
			case eICON_HPSKILL2:
				SkillIdx = m_pIcon[eICON_HPSKILL2]->getIndex();
				hptrig = atoi(m_pEdit[eEDIT_HPSKILL2]->GetString());
				iconidx = i;
				break;
			case eICON_MPSKILL1:
				SkillIdx = m_pIcon[eICON_MPSKILL1]->getIndex();
				mptrig = atoi(m_pEdit[eEDIT_MPSKILL1]->GetString());
				iconidx = i;
				break;
			case eICON_MPSKILL2:
				SkillIdx = m_pIcon[eICON_MPSKILL2]->getIndex();
				mptrig = atoi(m_pEdit[eEDIT_MPITEM2]->GetString());
				iconidx = i;
				break;
			default:
				continue;
		}
		
		if ( hptrig==0 && mptrig==0)
			continue;
		if(SkillIdx == -1)
			continue;
		if(iconidx == 0)
			continue;

		if(fHPRatio < hptrig )
		{
			UseSkill(SkillIdx);
			return;
		}
		if(fMPRatio < mptrig )
		{	
			UseSkill(SkillIdx); 
			return;
		}

	}		
	
	
	switch(skillCount)
	{
		
		case 1:
			SkillIdx = m_pIcon[eICON_SKILL1]->getIndex();
		break;
		case 2:
			SkillIdx = m_pIcon[eICON_SKILL2]->getIndex();
		break;
		case 3:
			SkillIdx = m_pIcon[eICON_SKILL3]->getIndex();
		break;
		case 4:
			 SkillIdx = m_pIcon[eICON_SKILL4]->getIndex();
		break;
		case 5:
			SkillIdx = m_pIcon[eICON_SKILL5]->getIndex();
		break;
		case 6:
			SkillIdx = m_pIcon[eICON_SKILL6]->getIndex();
		break;
		case 7:
			SkillIdx = m_pIcon[eICON_SKILL7]->getIndex();
		break;
		case 8:
			 SkillIdx = m_pIcon[eICON_SKILL8]->getIndex();
		break;
		default:
			skillCount=1;
			SkillIdx = m_pIcon[eICON_SKILL1]->getIndex();
		break;

	}
	if(SkillIdx != 0 )
	{
		UseSkill(SkillIdx);
		skillCount++;
		if( skillCount > 8)
		{
			skillCount = 1;
		}
	}


}
void ReZaBotUI::UseItem(CItems* pItems, int index)
{
	CItemData* item = pItems->ItemData;
	
	if(item == NULL)
		return;
	if(pItems->Item_Sum <= 0) 
	{
		return; 
	}
	SQUAD llTerm = _pTimer->GetHighPrecisionTimer().GetMilliseconds() - MY_INFO()->GetUseItem(index);
	if( llTerm > 500 )
	{
		MY_INFO()->SetUseItem(index, _pTimer->GetHighPrecisionTimer().GetMilliseconds());
	}
	else 
	{ 
		return; 
	}
	int	nTab = pItems->Item_Tab;
	int	nIdx = pItems->InvenIndex;

	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->GetInventory()->SetUseItemSlotInfo(nTab, nIdx);
	pUIManager->GetInventory()->SendUseSlotItem(nTab, nIdx);

}

bool ReZaBotUI::UseItems(){

	CUIManager* pUIManager = CUIManager::getSingleton();
	if( pUIManager->IsCSFlagOn( CSF_WAREHOUSE ) )
			return false;	
	//setup
	CPlayerEntity	*penPlayerEntity = ((CPlayerEntity*)CEntity::GetPlayerEntity(0));
	ObjInfo* pInfo = ObjInfo::getSingleton();
	
	//pet check
	CPetTargetInfom* pPetInfo = pInfo->GetMyPetInfo();
	bool peton = false;
	if (pPetInfo->pen_pEntity != NULL)
	{
		peton = true;
	}
	//pet trigger
	int petStaDiff = pInfo->GetMyPetInfo()->fMaxHungry - pInfo->GetMyPetInfo()->fHungry;
	int petHpDiff = pInfo->GetMyPetInfo()->fMaxHealth - pInfo->GetMyPetInfo()->fHealth;



	int nItemIdxHP1 = m_pIcon[eICON_HPITEM1]->getIndex();
	int nItemIdxHP2 = m_pIcon[eICON_HPITEM2]->getIndex();
	CItems* pItemsHP1 = m_pIcon[eICON_HPITEM1]->getItems();
	CItems* pItemsHP2 = m_pIcon[eICON_HPITEM2]->getItems();


	int nItemIdxMP1 = m_pIcon[eICON_MPITEM1]->getIndex();
	int nItemIdxMP2 = m_pIcon[eICON_MPITEM2]->getIndex();
	CItems* pItemsMP1 = m_pIcon[eICON_MPITEM1]->getItems();
	CItems* pItemsMP2 = m_pIcon[eICON_MPITEM2]->getItems();


	//pet feeder
	int nItemIdxPF1 = m_pIcon[eICON_PETFEED1]->getIndex();
	int nItemIdxPF2 = m_pIcon[eICON_PETFEED2]->getIndex();
	CItems* pItemsPF1 = m_pIcon[eICON_PETFEED1]->getItems();
	CItems* pItemsPF2 = m_pIcon[eICON_PETFEED2]->getItems();
	
	if(peton)
	{
	
		if(petHpDiff > 10)
		{
			if(nItemIdxPF1 == PETHP)
			{
				AddText(_S(9312,"Item").str_String,_S(9330, "Pet Health").str_String);
			
				UseItem(pItemsPF1,nItemIdxPF1);
				m_pIcon[eICON_PETFEED1]->setCount(pItemsPF1->Item_Sum-1);
				if(pItemsPF1->Item_Sum-1 <=0 ) 
					_resetIcon(eICON_PETFEED1);
				//return true;
			}
			else if(nItemIdxPF2 == PETHP)
			{
				AddText(_S(9312,"Item").str_String,_S(9330, "Pet Health").str_String);
			
				UseItem(pItemsPF2,nItemIdxPF2);
				m_pIcon[eICON_PETFEED2]->setCount(pItemsPF2->Item_Sum-1);
				if(pItemsPF2->Item_Sum-1 <=0 ) 
					_resetIcon(eICON_PETFEED2);
				//	return true;
			}

		}
		if(petStaDiff > 10) 
		{
			
			if(nItemIdxPF1 == PETSTA)
			{
				AddText(_S(9312,"Item").str_String,_S(9329,"Pet Stamina").str_String);
				UseItem(pItemsPF1,nItemIdxPF1);//return true;
				m_pIcon[eICON_PETFEED1]->setCount(pItemsPF1->Item_Sum-1);
				if(pItemsPF1->Item_Sum-1 <=0 ) 
					_resetIcon(eICON_PETFEED1);
			}
			else if(nItemIdxPF2 == PETSTA)
			{
				AddText(_S(9312,"Item").str_String,_S(9329,"Pet Stamina").str_String);
				UseItem(pItemsPF2,nItemIdxPF2);//return true;
				m_pIcon[eICON_PETFEED2]->setCount(pItemsPF2->Item_Sum-1);
				if(pItemsPF2->Item_Sum-1 <=0 ) 
					_resetIcon(eICON_PETFEED2);
			}
			
		}
	}

	int imhp= _pNetwork->MyCharacterInfo.hp;
	int imhpmax= _pNetwork->MyCharacterInfo.maxHP;
	int immp= _pNetwork->MyCharacterInfo.mp;
	int immpmax =_pNetwork->MyCharacterInfo.maxMP;
	float fHPRatio = ((float)((float)imhp /(float) imhpmax)) * 100.0f; 
	float fMPRatio = ((float)((float)immp /(float) immpmax)) * 100.0f; 
	//hp triggers
	for(int i = 0 ; i < eEDIT_MAX ; i ++) 
	{
		int hptrig =0;
		int mptrig =0;
		CItems* tmpitem= NULL;
		int iconidx = 0;
		switch(i)
		{
			case eEDIT_MPITEM1:
				mptrig = atoi(m_pEdit[eEDIT_MPITEM1]->GetString());
				tmpitem = pItemsMP1;
				iconidx = eICON_MPITEM1;
				break;
			case eEDIT_MPITEM2:
				mptrig = atoi(m_pEdit[eEDIT_MPITEM2]->GetString());
				tmpitem = pItemsMP2;
				iconidx = eEDIT_MPITEM2;
				break;
			case eEDIT_HPITEM1:
				hptrig = atoi(m_pEdit[eEDIT_HPITEM1]->GetString());
				tmpitem = pItemsHP1;
				iconidx = eEDIT_HPITEM1;
				break;
			case eEDIT_HPITEM2:
				hptrig = atoi(m_pEdit[eEDIT_HPITEM2]->GetString());
				tmpitem = pItemsHP2;
				iconidx = eEDIT_HPITEM2;

				break;
			default:
				continue;
		}
		
		
		if ( hptrig==0 && mptrig==0)
			continue;
		if(tmpitem == NULL)
			continue;
		if (tmpitem->Item_Index == -1)
		{
			_resetIcon(iconidx);
			continue;
		}

		if(fHPRatio < hptrig )
		{
			UseItem(tmpitem,tmpitem->ItemData->getindex());
			m_pIcon[iconidx]->setCount(tmpitem->Item_Sum-1);	
		}
		if(fMPRatio < mptrig )
		{	
			UseItem(tmpitem,tmpitem->ItemData->getindex());
			m_pIcon[iconidx]->setCount(tmpitem->Item_Sum-1);	 
		}

		if(tmpitem->Item_Sum-1 <=0)	
			_resetIcon(iconidx);
	}		
		
	//timer items
	
	
	
	for(int i = eICON_TIMERITEM1; i <= eICON_TIMERITEM4 ; i++)
	{
		int nItemTimer1 ;
		CItems* pItemsTI1;
		int SkillIdx = 0;
		if(m_pIcon[i]->getIndex() != 0 )
		{
			nItemTimer1 = m_pIcon[i]->getIndex();
			pItemsTI1 = m_pIcon[i]->getItems();
			if(!pItemsTI1)
				continue;
			if(nItemTimer1 != pItemsTI1->ItemData->index)
			{
				continue;
			}
			if(!_pUIBuff->IsSkillBuff(pItemsTI1->ItemData->GetNum0()))
			{
				SkillIdx = pItemsTI1->ItemData->GetNum0();
			}
			if(SkillIdx !=0)
			{
				bool reseticon = false;
				if(pItemsTI1->Item_Sum-1 <= 0 ) 
					reseticon = true; 
					 
				UseItem(pItemsTI1,nItemTimer1);

				m_pIcon[i]->setCount(pItemsTI1->Item_Sum-1);
				
				if(reseticon)
					_resetIcon(i);
				return true;
			}	
		}
	}
	
	

	return false;
		
}

UINT WINAPI ReZaBotUI::HandleTimer(void *parameter)
{
	CUIManager* pUIMgr = UIMGR();
	int timenow = time(NULL);
	int lastthot = pUIMgr->GetReZaBotUI()->m_ilastThought;
	//pUIMgr->GetReZaBotUI()->bBotison = true;

	int timetocheck = 0;

	while (_pNetwork->MyCharacterInfo.char_botting == 1)
	{
		if(timenow > lastthot  + 1)
		{
			pUIMgr->GetReZaBotUI()->DoAction(pUIMgr->GetReZaBotUI()->Think());
		}
		if(timetocheck == 0 || timetocheck + 5 < time(NULL))
		{
			timetocheck = time(NULL);
			pUIMgr->GetReZaBotUI()->CheckTime();


		}
		Sleep(300);//500
	}
	return 0;

}

void ReZaBotUI::CheckTime(){

	CNetworkMessage ProcRezaBOT((UBYTE)MSG_REZA);
	ProcRezaBOT << (DWORD)REZA_REZABOT;
	ProcRezaBOT << (DWORD)REZABOT_CHECK;
	if( !m_pIcon[eICON_BOTTICKET]->IsEmpty()){
		ProcRezaBOT << (DWORD)m_pIcon[eICON_BOTTICKET]->getItems()->ItemData->index;
		ProcRezaBOT << (DWORD)m_pIcon[eICON_BOTTICKET]->getItems()->Item_UniIndex;
	}
	else
	{
		ProcRezaBOT << (DWORD) -1 ; 
		ProcRezaBOT << (DWORD) -1 ; 
	}

	_pNetwork->SendToServerNew(ProcRezaBOT);

}


void ReZaBotUI::UpdateMoney(int64_t val){
	CUIManager* pUIManager = CUIManager::getSingleton();
	CTString strResult("");

	nas_earned += val;

	strResult.PrintF( "%I64d", nas_earned );
	pUIManager->InsertCommaToString( strResult );

	m_pTextNas->SetText(strResult);
}

//WINDOWS FUN STUFF
void ReZaBotUI::Render(){
	CUIWindow::Render();

}

void ReZaBotUI::OnRender(CDrawPort* pDraw){
	
	CUIWindow::OnRender(pDraw);

}

void ReZaBotUI::ResetPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	SetPos( ( pixMaxI + pixMinI - GetWidth() ) / 2, ( pixMaxJ + pixMinJ - GetHeight() ) / 2 );
	m_rcOriginPos.SetRect(m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}
void ReZaBotUI::AdjustPosition( PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ )
{
	if( m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ )
		ResetPosition( pixMinI, pixMinJ, pixMaxI, pixMaxJ );
}

BOOL ReZaBotUI::checkparentshidden(CUIBase* checkhidden)
{
	CTString lol(checkhidden->getID());
	
	if(lol.Matches("ReBotSys"))
	{
		return checkhidden->GetHide();
	}
	else
	{
		if(checkhidden->GetHide())
		{
			return checkhidden->GetHide();
		}
		else
		{
			return checkparentshidden(checkhidden->getParent());
		}
	}
	return FALSE;
}

WMSG_RESULT ReZaBotUI::HandleIconDrag(UINT16 x ,UINT16 y)
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	CUIIcon* pDrag = pUIManager->GetDragIcon();

	if (pDrag && pDrag->IsEmpty() == false)
	{
		
		UIBtnExType temp =	pDrag->getBtnType();

		switch(temp)
		{
			case UBET_ITEM:
			{
				CItems* pItemDrag = pDrag->getItems();

				if (pItemDrag == NULL)
				{
					pUIManager->ResetHoldBtn();
					return WMSG_FAIL;
				}

				for(int i = 0 ; i < eICON_MAX ; i ++ )
				{
					if (m_pIcon[i] && m_pIcon[i]->IsInside(x, y))
					{
						//check page active
						if(checkparentshidden((CUIBase*)m_pIcon[i]))
						{
							continue;
						}
						if (CheckItem(pItemDrag, i) == true)
						{
							m_pIcon[i]->copyItem(pDrag);
							m_pIcon[i]->setCount(pItemDrag->Item_Sum);
							//_resetIcon(i);
						}
						break;
					}
				}
			}
			break;
			case UBET_ACTION:
				//donothing 
				break;
			case UBET_SKILL: 
				{
					int dragidx = pDrag->getIndex();
					CSkill	&rSelSkill = _pNetwork->GetSkillData(pDrag->getIndex());

					if (rSelSkill.GetIndex() != dragidx)
					{
						pUIManager->ResetHoldBtn();
						return WMSG_FAIL;
					}
				

					for(int i = 0 ; i <= eICON_SKILLS_END ; i ++ )
					{
						if (m_pIcon[i] && m_pIcon[i]->IsInside(x, y))
						{
							//check page active
							if(checkparentshidden((CUIBase*)m_pIcon[i]))
							{
								continue;
							}
							//if (CheckItem(pItemDrag, i) == true)
							if( i <= eICON_SKILLS_END)
							{
								m_pIcon[i]->setSkill(dragidx);
								//_resetIcon(i);
						
							}
							break;
						}
					}
				}
				break;

		}
		
	}
	return WMSG_FAIL;
}

WMSG_RESULT ReZaBotUI::OnLButtonDBLClick(UINT16 x, UINT16 y )
{
	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	for (int i = 0; i <= eICON_MAX; ++i)
	{
		if (m_pIcon[i] && m_pIcon[i]->IsInside(x, y))
		{
			if(checkparentshidden((CUIBase*)m_pIcon[i]))
			{
				continue;
			}
			_resetIcon(i);
			break;
		}
	}

	return CUIWindow::OnLButtonDBLClick(x, y);
}

WMSG_RESULT ReZaBotUI::OnLButtonDown( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	if( m_pDrag && m_pDrag->IsInside(x, y))
	{
		m_bDrag = true;
		m_nOriX = x;
		m_nOriY = y;
	}


	CUIManager::getSingleton()->RearrangeOrder(UI_REZABOT, TRUE);
	
	/*m_slRGB[0]->IsInside(x,y)
	for(int i = 0
		){

	}
	*/

	return CUIBase::OnLButtonDown(x, y);
}

WMSG_RESULT ReZaBotUI::OnLButtonUp( UINT16 x, UINT16 y )
{
	if (m_bHide)
		return WMSG_FAIL;

	m_bDrag = false;

	if (IsInside(x, y) == FALSE)
		return WMSG_FAIL;

	CUIManager* pUIManager = CUIManager::getSingleton();
	
	HandleIconDrag(x,y);
	
	pUIManager->ResetHoldBtn();
	return CUIBase::OnLButtonUp(x, y);
}

WMSG_RESULT ReZaBotUI::OnMouseMove( UINT16 x, UINT16 y, MSG* pMsg )
{
	if (m_bHide)
		return WMSG_FAIL;

	bool clearicontooltip=false;
	for(int i = 0 ; i < eICON_MAX; i++)
	{
		if(m_pIcon[i]->IsInside(x,y))
		{
			clearicontooltip=true;
			break;
		}
		
	}
	if(!clearicontooltip)
	{
		CUITooltipMgr::getSingleton()->clearTooltip();
	}

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

	return CUIBase::OnMouseMove(x, y, pMsg);
}
//edit box focus bs
BOOL ReZaBotUI::IsEditBoxFocused()
{
	for (int i = 0 ; i < eEDIT_MAX; i++ ) 
	{
		if ( m_pEdit[eEDIT_MAXDIST+i]!= NULL)
		{
			if(m_pEdit[eEDIT_MAXDIST+i]->IsFocused())
			{
					return true;
			}
		}
	}
	return FALSE;
	//return m_roomName->IsFocused();
}

void ReZaBotUI::KillFocusEditBox()
{

	for (int i = 0 ; i < eEDIT_MAX; i++ ) 
	{
		if ( m_pEdit[eEDIT_MAXDIST+i]!= NULL)
		{
				if(m_pEdit[eEDIT_MAXDIST+i]->IsFocused())
				{
					m_pEdit[eEDIT_MAXDIST+i]->SetFocus(FALSE);
				}
		}
	}

	//if (m_roomName == NULL)
		return;

	//m_roomName->SetFocus( FALSE );
}


void ReZaBotUI::_resetIcon( int nSlotIdx )
{
	if (nSlotIdx < 0 || nSlotIdx >= eICON_MAX)
		return;

	CTString textEmptyGuide;

	switch(nSlotIdx)
	{
		case eICON_SKILL1:
		case eICON_SKILL2:
		case eICON_SKILL3:
		case eICON_SKILL4:
				textEmptyGuide.PrintF(_S(9299,"Skills to use when botting."));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_HPSKILL1:
		case eICON_HPSKILL2:
				textEmptyGuide.PrintF(_S(9300,"Skills to use when Hp triggers"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_MPSKILL1:
		case eICON_MPSKILL2:
				textEmptyGuide.PrintF(_S(9301,"Skills to use when Mp triggers"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_BUFF1:
		case eICON_BUFF2:
		case eICON_BUFF3:
		case eICON_BUFF4:
				textEmptyGuide.PrintF(_S(9302,"Buffs to use when botting"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_HPBUFF1:
		case eICON_HPBUFF2:
				textEmptyGuide.PrintF(_S(9303,"Buffs to use when Hp triggers"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_MPBUFF1:
		case eICON_MPBUFF2:
				textEmptyGuide.PrintF(_S(9304,"Buffs to use when Mp triggers"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_HPITEM1:
		case eICON_HPITEM2:
				textEmptyGuide.PrintF(_S(9305,"Items to use when Hp triggers"));//_S(9282, "Booster XP/SP used each kill."));
		
			break;
		case eICON_MPITEM1:
		case eICON_MPITEM2:
				textEmptyGuide.PrintF(_S(9306,"Items to use when Mp triggers"));//_S(9282, "Booster XP/SP used each kill."));
			break;
		case eICON_PETFEED1:
		case eICON_PETFEED2:
				textEmptyGuide.PrintF(_S(9307,"Items to use when Pet triggers below 90% on hp or stamina."));//_S(9282, "Booster XP/SP used each kill."));
			break;
		case eICON_TIMERITEM1:
		case eICON_TIMERITEM2:
		case eICON_TIMERITEM3:
		case eICON_TIMERITEM4:
				textEmptyGuide.PrintF(_S(9308,"Items to use when your item has a lasting effect you would like to keep active when it expires."));//_S(9282, "Booster XP/SP used each kill."));
			break;
		default:
			textEmptyGuide.PrintF( CTString(""));
			break;
	}

	if (m_pIcon[nSlotIdx] != NULL)
	{
		m_pIcon[nSlotIdx]->clearIconData();
		m_pIcon[nSlotIdx]->setTooltip(textEmptyGuide.str_String);
	}
}


void ReZaBotUI::RenderBotHead(FLOAT3D vPopupPos,FLOAT fPopupZ, CEntity* pTarget, int isPC)
{
	int DelayTimeSec = 10;
	int x = vPopupPos(1);
	int y = vPopupPos(2);
	enum etag{
		eMe = 0,
		eChar,
		eMob
	};

	CUIManager* pUIManager = CUIManager::getSingleton();

	switch(isPC)
	{

		case eMe:
		{
			if(_pNetwork->MyCharacterInfo.char_botting)
			{
				// Me->GetCharacterTarget()->cha_killChain;
				DrawBotting(x,y,fPopupZ,_pNetwork->MyCharacterInfo.char_botting,1);
			}
		}								 
		break;	

		case eChar:
		{
			CCharacterTarget* cChar = pTarget->GetCharacterTarget();

			DrawBotting(x,y,fPopupZ,pTarget->GetCharacterTarget()->cha_botting,1);
			
		}
		break;

		case eMob:
		{

		}
		break;


		default:return;break;
	}

	//pTarget->GetCharacterTarget();

}

void ReZaBotUI::DrawBotting( int nX, int nY,int nZ, char botting, FLOAT fRatio )
{
	if(botting == 1){

		//bot picture
		m_rcREZABOT.SetRect(0,0,DREZABOTW,DREZABOTH);
		UIRectUV rtREZABOT	=	m_rtREZABOT;
		UIRect	rcREZABOT	=	m_rcREZABOT;
		int offsety = -129;
		float fWidth = rcREZABOT.GetWidth();
		float fHieght = rcREZABOT.GetHeight();

		fWidth *= fRatio;
		fHieght *= fRatio;
		
		int scaledratio = 4;

		nX -= ( (fWidth/scaledratio) / 2 );
		COLOR colColor = 0xFFFFFFff;
		
		CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();
		
		pDrawPort->AddTexture( nX, nY+offsety, nX + (fWidth/scaledratio) ,nY+offsety + (fHieght/scaledratio),
								rtREZABOT.U0, rtREZABOT.V0, rtREZABOT.U1, rtREZABOT.V1,
								colColor, nZ);
	}
	else 
		return ; 
}
#endif
