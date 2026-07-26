#include "StdH.h"
#include <Engine/GameStageManager/StageMgr.h>
#include "StageLogin.h"
#include <Engine/Interface/UIManager.h>
#include <Engine/Contents/Login/UILoginNew.h>
#include <Engine/GameState.h> //RomeoST

void CStageLogin::Init()
{
	_pGameState->BackToLogin(); // RomeoST
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->SetUIGameState();
	pUIManager->GetLogin()->OpenUI();
}

void CStageLogin::Release()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->GetLogin()->CloseUI();
}
