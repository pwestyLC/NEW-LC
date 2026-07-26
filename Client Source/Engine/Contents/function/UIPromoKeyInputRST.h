#ifndef __PROMO_KEY_RST_UI_H__
#define __PROMO_KEY_RST_UI_H__

class CUIPromoKeyInputRST : public CUIWindow
{
public:
	CUIPromoKeyInputRST();
	~CUIPromoKeyInputRST();

	void initialize() override;

	void openUI();
	void closeUI();

	void ToggleVisible();

	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg) override;
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y) override;
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y) override;

	WMSG_RESULT OnCharMessage(MSG* pMsg) override;
	WMSG_RESULT	OnIMEMessage(MSG* pMsg) override;

	BOOL IsEditBoxFocused() override;
	void KillFocusEditBox() override;

	void OnSendPromoKey();

private:
	bool CheckPromoKey();

	enum
	{
		eBTN_CLOSE,
		eBTN_APPLY,
		eBTN_MAX
	};

	bool m_bDrag;
	int m_nOldX{};
	int m_nOldY{};


	CUIBase* m_Drag;
	CUIEditBox* m_pEditBoxKey;
	CUIButton* m_btn[eBTN_MAX];
};

#endif
