#ifndef __CASHEXCHANGE_UI_H__
#define __CASHEXCHANGE_UI_H__

// Cash listing dialog state machine
#define CASH_DIALOG_NONE			0
#define CASH_DIALOG_AMOUNT			1
#define CASH_DIALOG_PRICE			2
#define CASH_DIALOG_CONFIRM			3
#define CASH_DIALOG_LOADING			4

// Message codes for cash listing creation (matching PersonalshopUI patterns)
#define CE_MSGCMD_CASH_AMOUNT		2000		// Cash amount input
#define CE_MSGCMD_CASH_PRICE		2001		// Price per unit input
#define CE_MSGCMD_CONFIRM			2002		// Confirmation dialog

// Cash listing data structure
struct CashListing
{
	int listingID;
	int sellerCharIndex;			// Character index of the seller
	CTString sellerName;
	LONGLONG cashAmount;
	LONGLONG pricePerUnit;  // in NAS
	LONGLONG totalPrice;    // pricePerUnit * cashAmount
};

class CCashExchangeUI : public CUIWindow
{
public:
	CCashExchangeUI();
	~CCashExchangeUI();

	void initialize();
	void OpenUI();
	void CloseUI();

	void AddListing(const CashListing& listing);
	void ClearListings();
	void SelectListing(int index);
	void BuyCurrentListing();
	void BuyListingAtIndex(int listingIndex);
	void CancelListingAtIndex(int listingIndex);

	void ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);

	// NEW: Cash listing creation flow
	void OnListCashClick();
	void ShowCashAmountDialog();
	void ShowPricePerUnitDialog();
	void ShowConfirmationPreview();
	void OnCashAmountInputConfirm(const CTString& strInput);
	void OnPricePerUnitInputConfirm(const CTString& strInput);
	void OnConfirmListingClick();
	void OnBuyAmountConfirm(const CTString& strInput);  // NEW: Handle partial buy amount
	void SendCreateListingMessage();
	void SendRequestListingsMessage();
	void HandleCreateListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance = 0);
	void HandleBuyListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance = 0);
	void HandleCancelListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance = 0);
	void HandleListingResponse(CNetworkMessage& msg);

	// NEW: Message handler
	void MsgBoxCommand(int nCommandCode, BOOL bOK, CTString& strInput);

	// Static handler for incoming network messages
	static void ProcessCashExchangeMessage(CNetworkMessage& msg);

	// Check and process any pending cash exchange messages from server
	void ProcessPendingMessages();

private:
	void UpdateSelectedListingDisplay();
	void ClearCashListingDialog();
	BOOL ValidateCashAmount(LONGLONG llAmount);
	BOOL ValidatePricePerUnit(LONGLONG llPrice);
	BOOL ValidateOverflow(LONGLONG llAmount, LONGLONG llPrice);
	LONGLONG GetPlayerCashBalance() const;
	int GetCurrentPlayerCharIndex() const;  // Get the current player's character index

	CUIList* m_pListingList;
	CUIButton* m_pBtnListCash;		// "List Cash" button
	// NOTE: Buy buttons are now per-row in the list items (btn_select)

	int m_nSelectedListingIndex;
	std::vector<CashListing> m_listings;

	// NEW: Dialog state machine
	int m_nDialogState;
	LONGLONG m_llCashAmount;
	LONGLONG m_llPricePerUnit;
	LONGLONG m_llTotalValue;
	int m_nBuyListingIndex;  // Track which listing is being partially bought
};

#endif // __CASHEXCHANGE_UI_H__
