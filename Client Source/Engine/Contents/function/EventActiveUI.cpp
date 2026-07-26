#include "StdH.h"

#include <Engine/Interface/UIInternalClasses.h>
#include <Engine/Contents/function/EventActiveUI.h>

#include "Interface/UIAutoHelp.h"
#include "Interface/UIOption.h"

CEventActiveUI::CEventActiveUI()
{
}

void CEventActiveUI::initialize()
{
	m_pEventList = static_cast<CUIList*>(findUI("eventList"));
	m_pBtnClose = static_cast<CUIButton*>(findUI("btn_close"));
	m_pBtnClose->SetCommandFUp(std::bind(&CEventActiveUI::Close, this));
}

void CEventActiveUI::Render()
{
	std::vector<int> toRemoveIndices;

	int oldSize = m_vecEventActiveModel.size();
	for (int nCount = 0; nCount < m_vecEventActiveModel.size(); ++nCount)
	{
		auto& it = m_vecEventActiveModel[nCount];

		if (it.m_nDateStart == 0 || it.m_nDateEnd == 0)
			continue;

		ULONG currentTime = (ULONG)time(NULL) - _pNetwork->slServerTimeGap;

		if (it.m_nDateEnd > currentTime)
		{
			auto item = m_pEventList->GetListItem(nCount);
			if (item)
			{
				auto txt = dynamic_cast<CUIText*>(item->findUI("txt_time_to_end"));
				if (txt)
				{
					CTString tmp;
					time_t tmt = it.m_nDateEnd - currentTime;

					if (tmt >= 3600 * 24)
						tmp.PrintF("%d days", (tmt / 3600) / 24);
					else
						tmp.PrintF("%02d:%02d:%02d", tmt / 3600, (tmt % 3600) / 60, tmt % 60);

					COLOR color;
					if (it.m_nDateEnd - currentTime < 60)
						color = DEF_UI_COLOR_RED;
					else
						color = DEF_UI_COLOR_WHITE;

					txt->SetText(tmp);
					txt->setFontColor(color);
				}
			}
		}
		else if (it.m_nDateEnd < currentTime)
		{
			toRemoveIndices.push_back(it.m_nIndex);
		}
	}

	// Remove items after iterating through the vector
	for (int i = toRemoveIndices.size() - 1; i >= 0; --i)
	{
		auto removeEvent = std::find_if(m_vecEventActiveModel.begin(), m_vecEventActiveModel.end(), [&](const SEventActiveModel& it)
			{
				return it.m_nIndex == toRemoveIndices[i];
			});
		if (removeEvent != m_vecEventActiveModel.end())
			m_vecEventActiveModel.erase(removeEvent);
	}

	if (oldSize != m_vecEventActiveModel.size())
		updateEventList();

	m_pEventList->UpdateList();
}

void CEventActiveUI::Close()
{
	if (IsVisible() == FALSE || GetHide() == TRUE)
		return;

	Hide(TRUE);
	SetVisible(FALSE);

	extern INDEX g_iHideEvent;
	g_iHideEvent = 1;
	//UIMGR()->GetOption()->UpdateEventControl();
}

void CEventActiveUI::Open()
{
	if (IsVisible() == TRUE || GetHide() == FALSE)
		return;

	Hide(FALSE);
	SetVisible(TRUE);
}

WMSG_RESULT CEventActiveUI::MouseMessage(MSG* pMsg)
{
	static int	nOldX, nOldY;
	int	nX = LOWORD(pMsg->lParam);
	int	nY = HIWORD(pMsg->lParam);

	if (m_pEventList->IsInside(nX, nY))
	{
		return m_pEventList->MouseMessage(pMsg);
	}

	return CUIBase::MouseMessage(pMsg);
}


void CEventActiveUI::ReceiveList(CNetworkMessage* istr)
{
	m_vecEventActiveModel.clear();
	int count;
	(*istr) >> count;
	for (int i = 0; i < count; ++i)
	{
		SEventActiveModel model;
		(*istr) >> model.m_nIndex;
		(*istr) >> model.m_strName;
		(*istr) >> model.m_nDateStart;
		(*istr) >> model.m_nDateEnd;

		m_vecEventActiveModel.push_back(model);
	}

	if (count > 0)
	{
		updateEventList();
	}
}

void CEventActiveUI::ReceiveEventActive(CNetworkMessage* istr)
{
	SEventActiveModel model;
	(*istr) >> model.m_nIndex;
	(*istr) >> model.m_strName;
	(*istr) >> model.m_nDateStart;
	(*istr) >> model.m_nDateEnd;

	auto it = std::find_if(m_vecEventActiveModel.begin(), m_vecEventActiveModel.end(), [&](const SEventActiveModel& it)
		{
			return it.m_nIndex == model.m_nIndex;
		});
	if (it == m_vecEventActiveModel.end())
	{
		CTString strTitle;
		strTitle.PrintF("Event %s has started.", model.m_strName.str_String);
		informPopup(strTitle);
		m_vecEventActiveModel.push_back(model);
	}
	else
		*it = model;

	updateEventList();
}

void CEventActiveUI::ReceiveEventDeactive(CNetworkMessage* istr)
{
	int index;
	(*istr) >> index;

	auto it = std::find_if(m_vecEventActiveModel.begin(), m_vecEventActiveModel.end(), [&](const SEventActiveModel& it)
		{
			return it.m_nIndex == index;
		});

	if (it != m_vecEventActiveModel.end())
	{
		CTString strTitle;
		strTitle.PrintF("Event %s has ended.", it->m_strName.str_String);
		informPopup(strTitle);
		m_vecEventActiveModel.erase(it);
	}

	updateEventList();
}

void CEventActiveUI::RemoveAllEvent()
{
	m_vecEventActiveModel.clear();
	updateEventList();
}

void CEventActiveUI::informPopup(const CTString& strTitle)
{
	_UIAutoHelp->SetGMNotice(strTitle);
}

void CEventActiveUI::updateEventList()
{
	CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

	m_pEventList->DeleteAllListItem();

	CTString tmp;
	for (auto& it : m_vecEventActiveModel)
	{
		const auto listItemTemplate = m_pEventList->GetListItemTemplate();
		const auto item = listItemTemplate->Clone();

		auto txt = dynamic_cast<CUIText*>(item->findUI("txt_name"));
		txt->SetText(it.m_strName, "...");
		if (pDrawPort != NULL)
		{
			const ULONG ulWidth = pDrawPort->GetTextWidth2(it.m_strName);
			if (ulWidth > txt->GetWidth())
			{
				//item->setTooltip(it.m_strName);
				item->addTooltip(it.m_strName, DEF_UI_COLOR_WHITE);
			}
		}

		txt = dynamic_cast<CUIText*>(item->findUI("txt_time_to_end"));
		if (it.m_nDateStart == 0 || it.m_nDateEnd == 0)
		{
			txt->SetText(_s("unlimited"));
			txt->setAlignH(eALIGN_H_CENTER);
		}
		else
		{
			time_t tmt = it.m_nDateEnd - (ULONG)time(NULL) - _pNetwork->slServerTimeGap;
			if (tmt >= 3600 * 24)
				tmp.PrintF("%d days", (tmt / 3600) / 24);
			else
				tmp.PrintF("%02d:%02d:%02d", tmt / 3600, (tmt % 3600) / 60, tmt % 60);
			txt->SetText(tmp);
			txt->setAlignH(eALIGN_H_LEFT);
		}
		m_pEventList->AddListItem(item);
	}

	m_pEventList->UpdateList();
	m_pEventList->UpdateScroll(m_vecEventActiveModel.size());
}
