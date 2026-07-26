#include "StdH.h"
#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIInventory.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/GameState.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Ska/ModelInstance.h>
#include <Engine/Contents/function/InventoryOptions.h>

CUIInventoryOptions::CUIInventoryOptions()
{
	memset(&m_checkButtons, 0, sizeof(CUICheckButton*) * CheckBoxes::MaxCb);
}

CUIInventoryOptions::~CUIInventoryOptions()
{
	Destroy();
}

void CUIInventoryOptions::initialize()
{
	std::string cbNames[CheckBoxes::MaxCb] = { "cb_invisible_helmet" };
	boost::function<void(CUIBase*)> funcs[CheckBoxes::MaxCb] =
	{
		boost::bind(&CUIInventoryOptions::InvisibleHelmetChange, this, _1)
	};

	for (int32_t i = 0; i < CheckBoxes::MaxCb; i++)
	{
		m_checkButtons[i] = (CUICheckButton*)findUI(cbNames[i].c_str());
		if (m_checkButtons[i]) m_checkButtons[i]->CheckedChangeEvent(funcs[i]);
	}
}

void CUIInventoryOptions::OpenUI()
{
	if (IsVisible())
		return;

	UIMGR()->RearrangeOrder(UI_INVENTORY_OPTIONS, TRUE);
}

void CUIInventoryOptions::CloseUI()
{
	UIMGR()->RearrangeOrder(UI_INVENTORY_OPTIONS, FALSE);
}

WMSG_RESULT CUIInventoryOptions::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (m_bHide || !IsVisible())
		return WMSG_FAIL;

	if (!IsInside(x, y))
		return WMSG_FAIL;

	CUIBase::LButtonDownChild(x, y);
	return WMSG_SUCCESS;
}

void CUIInventoryOptions::InvisibleHelmetChange(CUIBase* base)
{
	BOOL curState = m_checkButtons[CheckBoxes::InvisibleHelmet]->IsChecked();

	CNetworkMessage nmsg((UBYTE)MSG_EXTEND);
	nmsg << (ULONG)MSG_EX_INVENTORY_OPTION
		<< (ULONG)INVENTORY_OPTION_INVENTORY_OPTION
		<< (INDEX)curState;

	_pNetwork->SendToServerNew(nmsg);

	SetInvisibleHelmet(curState);
}

void CUIInventoryOptions::SetInvisibleHelmet(BOOL isInvisible)
{
	m_checkButtons[CheckBoxes::InvisibleHelmet]->SetCheck(isInvisible);
	_pNetwork->m_bInvisibleHelmet = isInvisible;
}

void CUIInventoryOptions::OnInvisibleHelmetChange()
{	
	CModelInstance* pMI = NULL;
	CPlayerEntity* playerEntity = (CPlayerEntity*)CEntity::GetPlayerEntity(0);

	if (_pNetwork->MyCharacterInfo.bPetRide || _pNetwork->MyCharacterInfo.bWildPetRide)
	{
		CModelInstance* pMITemp = playerEntity->GetModelInstance();

		INDEX ctmi = pMITemp->mi_cmiChildren.Count();
		if (ctmi > 0)
			pMI = &pMITemp->mi_cmiChildren[0];
		else
			pMI = playerEntity->GetModelInstance();
	}
	else
	{
		pMI = playerEntity->GetModelInstance();
	}

	if (_pNetwork->m_bInvisibleHelmet)
	{
		playerEntity->DeleteCurrentArmor(WEAR_HELMET);
		playerEntity->WearingDefaultArmor(WEAR_HELMET);

		INDEX iCosIndex = _pNetwork->MyWearCostItem[WEAR_COSTUME_HELMET].Item_Index;
		CItemData* pTakeOffItemData = _pNetwork->GetItemData(iCosIndex);

		if (iCosIndex >= 0)
		{
			_pGameState->TakeOffArmor(pMI, *pTakeOffItemData);
		}
	}
	else
	{
		CItemData* pWearItemData = NULL;

		if (_pNetwork->MyWearCostItem[WEAR_COSTUME_HELMET].Item_Index != -1)
		{
			pWearItemData = _pNetwork->MyWearCostItem[WEAR_COSTUME_HELMET].ItemData;
		}
		else
		{
			pWearItemData = _pNetwork->MyWearItem[WEAR_HELMET].ItemData;
		}

		if (pWearItemData != NULL)
		{
			CTString smcPath = pWearItemData->GetItemSmcFileName();
			if (smcPath != MODEL_TREASURE)
			{
				playerEntity->DeleteCurrentArmor(WEAR_HELMET);
				_pGameState->DeleteDefaultArmor(pMI, WEAR_HELMET, _pNetwork->MyCharacterInfo.job);
				_pGameState->WearingArmor(pMI, *pWearItemData);
			}
		}
	}
}
