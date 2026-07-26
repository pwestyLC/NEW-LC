#include "StdH.h"
#include <functional>
#include <boost/foreach.hpp>
#include "DonationTierUIMini.h"
#include "DonationTierManager.h"

#include <Engine/DesignClasses/Singleton/SingletonBase.h>
#include <Engine/Interface/UIInternalClasses.h>
#include "DonationTierUI.h"

CUIDonationTierMini::CUIDonationTierMini()
	: m_levelProgress(nullptr)
	, m_isFocus(false)
	, m_isTooltipForcedShow(false)
{
	memset(&m_labels, 0, sizeof(CUIText*) * LabelMax);
}

CUIDonationTierMini::~CUIDonationTierMini()
{
	Destroy();
}

void CUIDonationTierMini::initialize()
{
	m_levelProgress = (CUIProgressBar*)findUI("pb_progress");

	std::string labels[LabelMax] = { "text_exp", "text_cur_lvl", "text_next_lvl" };
	for (int i = 0; i < LabelMax; i++)
	{
		m_labels[i] = (CUIText*)findUI(labels[i].c_str());
	}

	DonationTierManager::getSingleton()->RegisterCallback(
		std::bind(&CUIDonationTierMini::LoadDataFinishedNotify, this)
	);
}

void CUIDonationTierMini::ToggleUI()
{
	if (IsVisible())
	{
		UIMGR()->RearrangeOrder(UI_DONATION_TIER_MINI, FALSE);
	}
	else
	{
		HideLables(true);
		DonationTierManager::getSingleton()->LoadInfo();
		UIMGR()->GetDonationTier()->SetPos(GetPosX(), GetPosY() + 28);
		UIMGR()->RearrangeOrder(UI_DONATION_TIER_MINI, TRUE);
	}
}

void CUIDonationTierMini::HideLables(bool bHide)
{
	BOOST_FOREACH(CUIText* label, m_labels)
	{
		if (label) label->Hide(bHide);
	}
}

void CUIDonationTierMini::LoadDataFinishedNotify()
{
	if (!DonationTierManager::getSingleton()->isEventActive())
	{
		ShowSingleMessage(CTString("Event not started!"));
		HideLables(false);
		return;
	}

	const MyDonationTierInfo& myInfo = DonationTierManager::getSingleton()->getMyTierInfo();

	TierInfo tierInfo;
	if (DonationTierManager::getSingleton()->TryGetTierInfo(tierInfo, myInfo.Level))
	{

		m_levelProgress->SetProgressRange(0, tierInfo.LevelUpPoints);
		m_levelProgress->SetProgressPos(myInfo.Points);

		CTString str;
		str.PrintF("%d/%d (%d%%)", myInfo.Points, tierInfo.LevelUpPoints,
			(int)(myInfo.Points * 100 / tierInfo.LevelUpPoints));
		m_labels[LabelExp]->SetText(str);

		str.PrintF("Lvl %d.", myInfo.Level);
		m_labels[LabelCurLevel]->SetText(str);

		int nextLevel = myInfo.Level + 1;
		TierInfo nextLevelInfo;

		m_labels[LabelNextLevel]->SetVisible(false);
		str.PrintF("Lvl %d.", nextLevel);
		m_labels[LabelNextLevel]->SetText(str);
		m_labels[LabelNextLevel]->SetVisible(true);
	}
	else
	{
		ShowSingleMessage(CTString("You have max level!"));
	}

	HideLables(false);		
}

void CUIDonationTierMini::ShowSingleMessage(CTString message)
{
	m_labels[LabelCurLevel]->SetText(CTString(""));
	m_labels[LabelNextLevel]->SetText(CTString(""));
	m_labels[LabelExp]->SetText(message);

	m_levelProgress->SetProgressRange(0, 1);
	m_levelProgress->SetProgressPos(0);
}

WMSG_RESULT CUIDonationTierMini::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

	if (!IsInside(x, y))
		return WMSG_FAIL;

	CUIBase::OnLButtonDown(x, y);
	return WMSG_SUCCESS;
}

WMSG_RESULT CUIDonationTierMini::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

	if (!IsInside(x, y))
		return WMSG_FAIL;

	m_isTooltipForcedShow = !m_isTooltipForcedShow;
	CUIBase::OnLButtonUp(x, y);
	return WMSG_SUCCESS;
}

WMSG_RESULT	CUIDonationTierMini::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (!IsInside(x, y))
	{
		m_isFocus = false;
		return WMSG_FAIL;
	}

	m_isFocus = true;
	CUIBase::OnMouseMove(x, y, pMsg);
	return WMSG_SUCCESS;
}

void CUIDonationTierMini::OnUpdate(float fDeltaTime, ULONG ElapsedTime)
{
	if (m_isFocus || m_isTooltipForcedShow && !UIMGR()->GetDonationTier()->IsVisible())
		UIMGR()->GetDonationTier()->OpenUI();
	else if(UIMGR()->GetDonationTier()->IsVisible())
		UIMGR()->GetDonationTier()->CloseUI();
}
