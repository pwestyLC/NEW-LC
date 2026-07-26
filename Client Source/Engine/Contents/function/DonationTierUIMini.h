#pragma once

class CUIText;
class CUIProgressBar;

#include <Engine/Interface/UIWindow.h>

class CUIDonationTierMini : public CUIWindow
{
public:
	CUIDonationTierMini();
	~CUIDonationTierMini();

	void initialize();
	void ToggleUI();

	void LoadDataFinishedNotify();

protected:
	void HideLables(bool bHide);

	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);

	void ShowSingleMessage(CTString message);

	void OnUpdate(float fDeltaTime, ULONG ElapsedTime);

private:
	enum
	{
		LabelExp,
		LabelCurLevel,
		LabelNextLevel,
		LabelMax
	};

private:
	CUIText* m_labels[LabelMax];
	CUIProgressBar* m_levelProgress;
	bool m_isFocus;
	bool m_isTooltipForcedShow;
};