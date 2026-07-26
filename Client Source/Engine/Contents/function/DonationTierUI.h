#pragma once

class CUIImage;
class CUIBase;
class CUIText;
class CUIImage;
class CUIButton;
class DonationTierManager;

class DonationTierTooltip
{
public:
	DonationTierTooltip(DonationTierManager* manager);
	~DonationTierTooltip();

	void initialize(CUIWindow* window);

	void Show(int level);
	void Hide();

private:
	CUIBase* m_tooltipBase;
	CUIList* m_giftsList;
	CUIWindow* m_mainWindow;
	DonationTierManager* m_manager;
};

class CUIDonationTier : public CUIWindow
{
public:
	CUIDonationTier();
	~CUIDonationTier();

	void OpenUI();
	void CloseUI();
	void initialize();

	void LoadDataFinishedNotify();
	void OnLevelBtnEntry(int level, bool isOn);

protected:
	void OnUpdate(float fDeltaTime, ULONG ElapsedTime);
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT	OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);

protected:
	struct LevelUI
	{
		CUIButton* m_levelButton;
		CUIBase* m_levelMarker;

		LevelUI()
		{
			m_levelButton = nullptr;
			m_levelMarker = nullptr;
		}
	};

	enum Labels
	{
		EndTime,
		CurrentLevel,
		MaxLevel,
		LevelUpPoints,
		MaxPoints,
		MaxLabel
	};

	enum LevelMarkerTypes
	{
		Top,
		Bottom,
		MaxMarkerType
	};

private:
	void DeleteOldData();

private:
	CUIImage* m_progressImage;
	CUIImage* m_bgProgressImage;
	CUIText* m_labels[MaxLabel];

	CUIButton* m_levelBtnProto;
	CUIBase* m_levelUIPrototypes[MaxMarkerType];


	std::vector<LevelUI> m_levelUIVec;
	DonationTierTooltip m_tooptipHelper;
	DonationTierManager* m_manager;
};