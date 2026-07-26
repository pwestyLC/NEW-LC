#include "StdH.h"
#include <Engine/GameStageManager/StageMgr.h>
#include "StageSelServer.h"
#include <Engine/Interface/UIManager.h>
#include <Engine/Contents/Login/UIServerSelect.h>
#include <Engine/GameState.h> //RomeoST

void CStageSelServer::Init()
{
	_pGameState->BackToLogin(); // RomeoST
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->SetUIGameState();
	pUIManager->GetServerSelect()->OpenUI();
}

void CStageSelServer::Release()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	pUIManager->GetServerSelect()->CloseUI();
}
