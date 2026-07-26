#pragma once

typedef enum _tagPCInventoryOption
{
	INVENTORY_OPTION_INVENTORY_OPTION = 0,
	INVENTORY_OPTION_MAX
} PC_INVENTORY_OPTION;

class CUICheckButton;

class CUIInventoryOptions : public CUIWindow
{
public:
	CUIInventoryOptions();
	~CUIInventoryOptions();

	void initialize();
	void OpenUI();
	void CloseUI();

	void InvisibleHelmetChange(CUIBase* base);
	void OnInvisibleHelmetChange();
	void SetInvisibleHelmet(BOOL isInvisible);

protected:
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);

private:
	enum CheckBoxes
	{
		InvisibleHelmet,
		MaxCb
	};

private:
	CUICheckButton* m_checkButtons[CheckBoxes::MaxCb];
};