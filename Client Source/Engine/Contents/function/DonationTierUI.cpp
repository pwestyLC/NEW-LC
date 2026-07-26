#include "StdH.h"

#include <sstream>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Contents/function/DonationTierManager.h>
#include "DonationTierUI.h"

#define NAS_ITEM (19)

#pragma region DonationTierTooltip
DonationTierTooltip::DonationTierTooltip(DonationTierManager* manager)
	: m_manager(manager)
	, m_mainWindow(nullptr)
{

}

DonationTierTooltip::~DonationTierTooltip()
{

}

void DonationTierTooltip::initialize(CUIWindow* window)
{
	m_tooltipBase = window->findUI("base_tooltip");
	m_giftsList = (CUIList*)window->findUI("list_gifts");

	window->deleteChild(m_tooltipBase, false);
	m_mainWindow = window;
}

void DonationTierTooltip::Show(int level)
{
	TierInfo tierInfo;
	if (!m_manager->TryGetTierInfo(tierInfo, level))
		return;

	size_t giftCount = tierInfo.Gifts.size();
	
	CUIImage* image;
	
	const int baseBorderHeight = 38;
	const int baseBlockHeight = 44;
	const int listItemHeight = 36;
	if (giftCount > 0)
	{
		int height = baseBorderHeight + listItemHeight * giftCount;
		image = (CUIImage*)m_tooltipBase->findUI("border_left");
		if (image != nullptr)
		{
			image->SetHeight(height);
		}

		image = (CUIImage*)m_tooltipBase->findUI("border_right");
		if (image != nullptr)
		{
			image->SetHeight(height);
		}

		image = (CUIImage*)m_tooltipBase->findUI("img_content");
		if (image != nullptr)
		{
			image->SetHeight(height);
		}

		m_giftsList->SetHeight(listItemHeight * giftCount);
		m_giftsList->DeleteAllListItem();
		m_tooltipBase->SetHeight(baseBlockHeight + listItemHeight * giftCount);

		BOOST_FOREACH(DonationTierGift & gift, tierInfo.Gifts)
		{
			CUIListItem* item = (CUIListItem*)m_giftsList->GetListItemTemplate()->Clone();
			m_giftsList->AddListItem(item);

			CUIIcon* itemIcon;
			CUIText* itemName;
			CItemData* itemData = CItemData::getData(gift.ItemIndex);
			if (itemData != nullptr) 
			{
				itemIcon = (CUIIcon*)item->findUI("icon_item");
				if (itemIcon != nullptr)
				{
					itemIcon->setData(UIBtnExType::UBET_ITEM, gift.ItemIndex);
					if (gift.ItemIndex != NAS_ITEM)
					{
						itemIcon->setCount(gift.ItemCount);
					}
				}

				itemName = (CUIText*)item->findUI("txt_item_name");
				if (itemName != nullptr)
				{
					if (gift.ItemIndex != NAS_ITEM)
					{
						itemName->SetText(CTString(itemData->GetName()));
					}
					else
					{
						CTString str;
						str.PrintF("%I64d", gift.ItemCount);
						CUIManager::getSingleton()->InsertCommaToString(str);
						itemName->SetText(str);
					}
				}
			}
		}

		m_giftsList->UpdateList();
		m_tooltipBase->Hide(FALSE);
	}
	
	std::string btnName = boost::str(boost::format("btn_level_%1%") % level).c_str();
	CUIBase* btn = m_mainWindow->findUI(btnName.c_str());
	m_tooltipBase->SetPos(btn->GetPosX() + (btn->GetWidth() / 2) - (m_tooltipBase->GetWidth() / 2),
		btn->GetPosY() + btn->GetHeight() + 5);

	m_mainWindow->addChild(m_tooltipBase);
}

void DonationTierTooltip::Hide()
{
	m_tooltipBase->Hide(TRUE);
	m_mainWindow->deleteChild(m_tooltipBase, false);
}
#pragma endregion

CUIDonationTier::CUIDonationTier()
	: m_manager(DonationTierManager::getSingleton())
	, m_tooptipHelper(DonationTierManager::getSingleton())
	, m_progressImage(nullptr)
	, m_levelBtnProto(nullptr)
	, m_bgProgressImage(nullptr)
{
	memset(m_labels, 0, sizeof(CUIText*) * MaxLabel);
	memset(m_levelUIPrototypes, 0, sizeof(CUIBase*) * MaxMarkerType);
}

CUIDonationTier::~CUIDonationTier()
{
	Destroy();
}

void CUIDonationTier::initialize()
{
	std::string labelNames[MaxLabel] =
	{
		"txt_finish_time", "txt_cur_level", "txt_max_level",
		"txt_next_level_points", "txt_max_level_points"
	};

	for (int i = 0; i < MaxLabel; i++)
	{
		m_labels[i] = (CUIText*)findUI(labelNames[i].c_str());
	}

	std::string markerNames[MaxMarkerType] = { "lvl_top_info", "lvl_bottom_info" };
	for (int i = 0; i < MaxMarkerType; i++)
	{
		m_levelUIPrototypes[i] = findUI(markerNames[i].c_str());
	}

	m_progressImage = (CUIImage*)findUI("progress_green");
	m_bgProgressImage = (CUIImage*)findUI("progress_white");
	m_levelBtnProto = (CUIButton*)findUI("btn_tier_proto");

	m_tooptipHelper.initialize(this);
	m_manager->RegisterCallback(boost::bind(&CUIDonationTier::LoadDataFinishedNotify, this));
}

void CUIDonationTier::OpenUI()
{
	if (IsVisible() || !m_manager->isEventActive())
		return;

	UIMGR()->RearrangeOrder(UI_DONATION_TIER, TRUE);
}

void CUIDonationTier::CloseUI()
{
	UIMGR()->RearrangeOrder(UI_DONATION_TIER, FALSE);
}

void CUIDonationTier::DeleteOldData()
{
	BOOST_FOREACH(LevelUI& level, m_levelUIVec)
	{
		if (level.m_levelButton)
		{
			deleteChild(level.m_levelButton);
		}

		if (level.m_levelMarker)
		{
			deleteChild(level.m_levelMarker);
		}
	}

	m_levelUIVec.clear();
}

void CUIDonationTier::LoadDataFinishedNotify()
{
	if (!m_manager->isEventActive())
	{
		CloseUI();
		return;
	}

	DeleteOldData();

	auto tiersVec = m_manager->getTiersInfoVec();
	auto userInfo = m_manager->getMyTierInfo();

	TierInfo curTierInfo;
	m_manager->TryGetTierInfo(curTierInfo, userInfo.Level);

	int maxPoints = m_manager->getMaxPoints();
	int userGlobalPoints = m_manager->getUserGlobalPoints();

	int progressWidth = m_bgProgressImage->GetWidth();

	int pointsSum = 0;
	BOOST_FOREACH(TierInfo tierInfo, tiersVec)
	{
		pointsSum += tierInfo.LevelUpPoints;

		int posX = m_bgProgressImage->GetPosX() +
			(pointsSum * 100 / maxPoints) / 100.0f * m_bgProgressImage->GetWidth() -
			m_levelBtnProto->GetWidth() / 2;

		CUIButton* btn = (CUIButton*)m_levelBtnProto->Clone();
		btn->Hide(FALSE);
		btn->SetPosX(posX);
		btn->setID(boost::str(boost::format("btn_level_%1%") % tierInfo.Level).c_str());
		addChild(btn);

		btn->SetCommandFEnter(boost::bind(&CUIDonationTier::OnLevelBtnEntry, this, tierInfo.Level, true));
		btn->SetCommandFLeave(boost::bind(&CUIDonationTier::OnLevelBtnEntry, this, tierInfo.Level, false));

		CUIBase* levelMarker = m_levelUIPrototypes[tierInfo.Level % 2]->Clone();
		levelMarker->Hide(FALSE);
		levelMarker->SetPosX(posX - levelMarker->GetWidth() + m_levelBtnProto->GetWidth() / 2);

		CUIText* levelLabel = (CUIText*)levelMarker->findUI("str_level");
		if (levelLabel)
		{
			std::string text = boost::str(boost::format("Level %1%") % (tierInfo.Level + 1));
			levelLabel->SetText(CTString(text.c_str()));
		}
		
		addChild(levelMarker);

		LevelUI level;
		level.m_levelButton = btn;
		level.m_levelMarker = levelMarker;
		m_levelUIVec.push_back(level);

		m_progressImage->SetWidth((userGlobalPoints * 100 / maxPoints) / 100.0f * m_bgProgressImage->GetWidth());
		
		CTString str;
		str.PrintF("%d", userInfo.Level);
		m_labels[CurrentLevel]->SetText(str);

		str.PrintF("%d", tiersVec.at(tiersVec.size() - 1).Level + 1);
		m_labels[MaxLevel]->SetText(str);

		int remainPoints = curTierInfo.LevelUpPoints - userInfo.Points;
		remainPoints = remainPoints < 0 ? 0 : remainPoints;

		int remainPointsToFinish = maxPoints - userGlobalPoints;

		if (userInfo.Level == tiersVec.at(tiersVec.size() - 1).Level + 1) {
			remainPoints = 0;
			remainPointsToFinish = 0;
		}

		str.PrintF("%d", remainPoints);
		CUIManager::getSingleton()->InsertCommaToString(str);
		m_labels[LevelUpPoints]->SetText(str);

		str.PrintF("%d", remainPointsToFinish);
		CUIManager::getSingleton()->InsertCommaToString(str);
		m_labels[MaxPoints]->SetText(str);
	}
}

void CUIDonationTier::OnLevelBtnEntry(int level, bool isOn)
{
	if (isOn)
	{
		m_tooptipHelper.Show(level);
	}
	else
	{
		m_tooptipHelper.Hide();
	}
}

void CUIDonationTier::OnUpdate(float fDeltaTime, ULONG ElapsedTime)
{
	time_t finishEventTime = m_manager->getMyTierInfo().FinishTime;
	time_t curTime = _pTimer->GetHighPrecisionTimer().GetSeconds();
	time_t remainTime = finishEventTime - curTime;

	std::stringstream ss;
	ss << "Remain time: ";
	if (remainTime > 24 * 60 * 60)
	{
		int days = remainTime / 24 / 60 / 60;
		remainTime = remainTime % (24 * 60 * 60);
		ss << days << " d. ";
	}

	if (remainTime > 60 * 60)
	{
		int hours = remainTime / 60 / 60;
		remainTime = remainTime % (60 * 60);
		ss << hours << " h. ";
	}

	if (remainTime > 60)
	{
		int minutes = remainTime / 60;
		remainTime = remainTime % 60;
		ss << minutes << " m. ";
	}

	ss << remainTime << " s. ";
	std::string timeStr = ss.str();
	m_labels[EndTime]->SetText(CTString(timeStr.c_str()));
}

WMSG_RESULT CUIDonationTier::OnLButtonDown(UINT16 x, UINT16 y)
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

	if (!IsInside(x, y))
		return WMSG_FAIL;

	CUIBase::OnLButtonDown(x, y);
	CUIBase::LButtonDownChild(x, y);
	return WMSG_SUCCESS;
}

WMSG_RESULT CUIDonationTier::OnLButtonUp(UINT16 x, UINT16 y)
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

	if (!IsInside(x, y))
		return WMSG_FAIL;

	CUIBase::OnLButtonUp(x, y);
	CUIBase::LButtonUpChild(x, y);
	return WMSG_SUCCESS;
}

WMSG_RESULT	CUIDonationTier::OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg)
{
	if (!IsVisible())
	{
		return WMSG_FAIL;
	}

	if (!IsInside(x, y))
		return WMSG_FAIL;

	CUIBase::OnMouseMove(x, y, pMsg);
	CUIBase::MouseMoveChild(x, y, pMsg);
	return WMSG_SUCCESS;
}
