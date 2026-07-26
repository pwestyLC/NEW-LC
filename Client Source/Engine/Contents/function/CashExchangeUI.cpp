#include "stdH.h"
#include <Engine/Interface/UIInternalClasses.h>
#include "CashExchangeUI.h"
#include <Engine/Interface/UIManager.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Contents/Base/UIMsgBoxNumeric_only.h>
#include "CashExchangeCmd.h"
#include <Engine/Interface/UICashShopEX.h>
#include <Common/Packet/ptype_cash_exchange.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Contents/Base/UIMsgBoxMgr.h>
#include <Engine/Network/MessageDefine.h>

// Debug logging helper - file will be created automatically if it doesn't exist
#define CASH_DEBUG_LOG(fmt, ...) \
	do { \
		FILE* pDebugLog = fopen("D:\\\\cash_exchange_debug.log", "a"); \
		if (pDebugLog) { \
			fprintf(pDebugLog, fmt, __VA_ARGS__); \
			fflush(pDebugLog); \
			fclose(pDebugLog); \
		} \
	} while(0)

CCashExchangeUI::CCashExchangeUI()
	: m_pListingList(NULL),
	  m_nSelectedListingIndex(-1),
	  m_pBtnListCash(NULL),
	  m_nDialogState(CASH_DIALOG_NONE),
	  m_llCashAmount(0),
	  m_llPricePerUnit(0),
	  m_llTotalValue(0),
	  m_nBuyListingIndex(-1)
{
	setInherit(false);
}

CCashExchangeUI::~CCashExchangeUI()
{
	ClearListings();
}

void CCashExchangeUI::initialize()
{
#ifndef WORLD_EDITOR
	CUIBase* pBase = NULL;

	// Find the listing list (matches itemproduct.xml pattern)
	m_pListingList = (CUIList*)findUI("listing_list");

	// Find close button
	if (pBase = findUI("btn_close"))
	{
		pBase->SetCommandFUp(boost::bind(&CCashExchangeUI::CloseUI, this));
	}

	// NEW: Find "List Cash" button
	if (m_pBtnListCash = (CUIButton*)findUI("btn_list_cash"))
	{
		m_pBtnListCash->SetCommandFUp(boost::bind(&CCashExchangeUI::OnListCashClick, this));
	}

	// Find refresh button
	if (pBase = findUI("btn_refresh"))
	{
		pBase->SetCommandFUp(boost::bind(&CCashExchangeUI::SendRequestListingsMessage, this));
	}

	// NOTE: Buy buttons are now per-row (btn_select in each list item)
	// They are bound dynamically in AddListing() for each row
#endif // WORLD_EDITOR
}

void CCashExchangeUI::OpenUI()
{
	if (GetHide() == TRUE || IsVisible() == FALSE)
	{
		Hide(FALSE);
		UIMGR()->RearrangeOrder(UI_CASHEXCHANGE, TRUE);

		// Request listings from server
		SendRequestListingsMessage();

		// Try to process any pending messages immediately
		ProcessPendingMessages();
	}
}

void CCashExchangeUI::CloseUI()
{
	Hide(TRUE);
	UIMGR()->RearrangeOrder(UI_CASHEXCHANGE, FALSE);
}

void CCashExchangeUI::AddListing(const CashListing& listing)
{
	CASH_DEBUG_LOG("[CashExchangeUI] AddListing called for listing ID=%d\n", listing.listingID);

	if (m_pListingList == NULL)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] ERROR - m_pListingList is NULL!\n");
		return;
	}

	// First, check for any pending messages that haven't been processed yet
	ProcessPendingMessages();

	CUIBase* pTmp = m_pListingList->GetListItemTemplate();
	if (pTmp == NULL)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] ERROR - GetListItemTemplate returned NULL!\n");
		return;
	}

	// Clone the template
	CUIBase* pItem = pTmp->Clone();
	m_pListingList->AddListItem(pItem);

	// Get the newly added item
	pItem = m_pListingList->GetListItem(m_pListingList->getListItemCount() - 1);
	if (pItem == NULL)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] ERROR - GetListItem returned NULL!\n");
		return;
	}

	CASH_DEBUG_LOG("[CashExchangeUI] List item created, updating fields\n");

	// Update seller name text
	CUIText* pText = (CUIText*)pItem->findUI("txt_seller");
	if (pText != NULL)
	{
		pText->SetText((CTString&)listing.sellerName);
	}

	// Update cash amount text
	pText = (CUIText*)pItem->findUI("txt_amount");
	if (pText != NULL)
	{
		CTString str;
		str.PrintF("%I64d", listing.cashAmount);
		pText->SetText(str);
	}

	// Update price per unit text
	pText = (CUIText*)pItem->findUI("txt_price");
	if (pText != NULL)
	{
		CTString str;
		str.PrintF("%I64d/ea", listing.pricePerUnit);
		pText->SetText(str);
	}

	// Update total price text
	pText = (CUIText*)pItem->findUI("txt_total");
	if (pText != NULL)
	{
		CTString str;
		str.PrintF("%I64d NAS", listing.totalPrice);
		pText->SetText(str);
	}

	// NEW: Bind the Buy button in this row to purchase this specific listing
	int listingIndex = (int)m_listings.size();
	int currentPlayerCharIndex = GetCurrentPlayerCharIndex();
	BOOL bIsOwner = (listing.sellerCharIndex == currentPlayerCharIndex);

	CUIButton* pBuyBtn = (CUIButton*)pItem->findUI("btn_select");
	CUIButton* pCancelBtn = (CUIButton*)pItem->findUI("btn_cancel");

	if (bIsOwner)
	{
		// Player is the seller - show cancel button, hide buy button
		if (pBuyBtn != NULL)
		{
			pBuyBtn->Hide(TRUE);
		}
		if (pCancelBtn != NULL)
		{
			pCancelBtn->Hide(FALSE);
			pCancelBtn->SetCommandFUp(boost::bind(&CCashExchangeUI::CancelListingAtIndex, this, listingIndex));
			CASH_DEBUG_LOG("[CashExchangeUI] Binding cancel button for listing %d (seller)\n", listing.listingID);
		}
	}
	else
	{
		// Player is not the seller - show buy button, hide cancel button
		if (pCancelBtn != NULL)
		{
			pCancelBtn->Hide(TRUE);
		}
		if (pBuyBtn != NULL)
		{
			pBuyBtn->Hide(FALSE);
			pBuyBtn->SetCommandFUp(boost::bind(&CCashExchangeUI::BuyListingAtIndex, this, listingIndex));
			CASH_DEBUG_LOG("[CashExchangeUI] Binding buy button for listing %d (buyer)\n", listing.listingID);
		}
	}

	m_pListingList->UpdateList();

	// Store the listing data
	m_listings.push_back(listing);
}

void CCashExchangeUI::ClearListings()
{
	if (m_pListingList != NULL)
	{
		m_pListingList->DeleteAllListItem();
	}
	m_listings.clear();
	m_nSelectedListingIndex = -1;
}

void CCashExchangeUI::SelectListing(int index)
{
	if (index < 0 || index >= (int)m_listings.size())
		return;

	m_nSelectedListingIndex = index;
	UpdateSelectedListingDisplay();

	// Note: CUIList doesn't have SetSelectIdx, selection is handled by the list internally
}

void CCashExchangeUI::UpdateSelectedListingDisplay()
{
	// With the itemproduct-style list, selection is handled by the list itself
	// The selected item will be visually highlighted by the UI framework
	// No additional update needed
}

void CCashExchangeUI::BuyCurrentListing()
{
	if (m_nSelectedListingIndex < 0 || m_nSelectedListingIndex >= (int)m_listings.size())
		return;

	const CashListing& listing = m_listings[m_nSelectedListingIndex];

	if (_pNetwork == NULL)
	{
		CloseUI();
		return;
	}

	// Build and send buy request to server using struct-based serialization
	CNetworkMessage nmMsg;
	RequestClient::doCashExchangeBuyListing* packet = 
		reinterpret_cast<RequestClient::doCashExchangeBuyListing*>(nmMsg.nm_pubMessage);
	packet->type = MSG_CASHEXCHANGE;
	packet->subType = MSG_CASHEXCHANGE_BUY_LISTING;
	packet->listingID = listing.listingID;
	packet->cashAmount = listing.cashAmount;
	nmMsg.setSize(sizeof(*packet));

	_pNetwork->SendToServerNew(nmMsg);

	// Close the UI after sending
	CloseUI();
}

void CCashExchangeUI::BuyListingAtIndex(int listingIndex)
{
	if (listingIndex < 0 || listingIndex >= (int)m_listings.size())
		return;

	const CashListing& listing = m_listings[listingIndex];

	// Store the listing index for later use
	m_nBuyListingIndex = listingIndex;

	// Show input dialog to ask how much to buy
	// Create a command to handle the input
	CmdCashExchangeNumericInput* pCmd = new CmdCashExchangeNumericInput;
	pCmd->setData(this, 3000);  // Command code 3000 for buy amount

	CUIManager* pUIManager = CUIManager::getSingleton();
	if (pUIManager == NULL)
		return;

	CUIMsgBoxNumericOnly* pNumBox = pUIManager->GetMsgBoxNumOnly();
	if (pNumBox == NULL)
		return;

	// Build the message
	CTString strTitle;
	strTitle.PrintF("Buy from %s", (const char*)listing.sellerName);

	CTString strMsg;
	strMsg.PrintF("Available: %I64d cash\nPrice: %I64d NAS each\nTotal cost for all: %I64d NAS\n\nHow much do you want to buy?", 
		listing.cashAmount, listing.pricePerUnit, listing.totalPrice);

	// Show dialog with range 1 to listing.cashAmount
	pNumBox->SetInfo(pCmd, strTitle, strMsg, 1, (SQUAD)listing.cashAmount);
	pNumBox->InitData((SQUAD)listing.cashAmount);  // Default to full amount

	CASH_DEBUG_LOG("[CashExchangeUI] Buy partial amount dialog opened for listing ID=%d\n", listing.listingID);
}

void CCashExchangeUI::CancelListingAtIndex(int listingIndex)
{
	if (listingIndex < 0 || listingIndex >= (int)m_listings.size())
		return;

	const CashListing& listing = m_listings[listingIndex];

	if (_pNetwork == NULL)
		return;

	// Build and send cancel request to server
	CNetworkMessage nmMsg;
	RequestClient::doCashExchangeCancelListing* packet = 
		reinterpret_cast<RequestClient::doCashExchangeCancelListing*>(nmMsg.nm_pubMessage);
	packet->type = MSG_CASHEXCHANGE;
	packet->subType = MSG_CASHEXCHANGE_CANCEL_LISTING;
	packet->listingID = listing.listingID;
	nmMsg.setSize(sizeof(*packet));

	_pNetwork->SendToServerNew(nmMsg);

	CASH_DEBUG_LOG("[CashExchangeUI] Cancel request sent for listing ID=%d\n", listing.listingID);
}

void CCashExchangeUI::ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	SetPos((pixMaxI + pixMinI - GetWidth()) / 2, (pixMaxJ + pixMinJ - GetHeight()) / 2);
}

void CCashExchangeUI::AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ)
{
	if (m_nPosX < pixMinI || m_nPosX + GetWidth() > pixMaxI ||
		m_nPosY < pixMinJ || m_nPosY + GetHeight() > pixMaxJ)
		ResetPosition(pixMinI, pixMinJ, pixMaxI, pixMaxJ);
}

// ========== NEW: Cash Listing Creation Methods ==========

void CCashExchangeUI::OnListCashClick()
{
	// Initialize dialog state
	m_nDialogState = CASH_DIALOG_AMOUNT;
	m_llCashAmount = 0;
	m_llPricePerUnit = 0;
	m_llTotalValue = 0;

	// Show first dialog: Cash amount input
	ShowCashAmountDialog();
}

void CCashExchangeUI::ShowCashAmountDialog()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	if (pUIManager == NULL)
		return;

	// Get player's current cash balance
	// Note: The first time this is called, the cash value might not be synced from server yet.
	// In that case, it will show an outdated value. The actual value will sync within 2-5 minutes
	// when the server sends the cash balance update. This is normal game behavior.
	LONGLONG llBalance = GetPlayerCashBalance();

	// If balance is 0 or very large (uninitialized), show a message to wait
	if (llBalance <= 0)
	{
		pUIManager->CreateMessageBoxL(CTString("Warning"), UI_CASHEXCHANGE, -1);
		pUIManager->AddMessageBoxLString(-1, TRUE, CTString("Your cash balance is loading from server.\nPlease wait a moment and try again."), -1, 0xFFFFFFFF);
		pUIManager->AddMessageBoxLString(-1, FALSE, CTString("OK"), -1);
		return;
	}

	// Create message for dialog with cash amount
	CTString strCashBalance;
	strCashBalance.PrintF("%I64d", llBalance);

	CTString strMessage;
	strMessage.PrintF("Your current cash: %s\n\nHow much cash to list?", (const char*)strCashBalance);

	// Create command for the numeric input dialog
	CmdCashExchangeNumericInput* pCmd = new CmdCashExchangeNumericInput;
	pCmd->setData(this, CE_MSGCMD_CASH_AMOUNT);

	// Show numeric input dialog using the UIManager's message box
	// SetInfo(Command* pCmdOk, CTString title, CTString desc, int nMin, SQUAD llMax, Command* pCmdCancel = NULL)
	CUIMsgBoxNumericOnly* pNumBox = pUIManager->GetMsgBoxNumOnly();
	if (pNumBox != NULL)
	{
		pNumBox->SetInfo(pCmd, "List Cash", strMessage, 1, llBalance);
	}
}

void CCashExchangeUI::OnCashAmountInputConfirm(const CTString& strInput)
{
	// Parse input
	LONGLONG llAmount = _atoi64((const char*)strInput);

	// Validate
	if (!ValidateCashAmount(llAmount))
	{
		// Show error and retry
		// MSGMGR()->ShowMsgBoxOK("Cash amount must be greater than 0 and not exceed your balance");
		// ShowCashAmountDialog();
		return;
	}

	// Store amount and move to next step
	m_llCashAmount = llAmount;
	m_nDialogState = CASH_DIALOG_PRICE;

	// Show price per unit dialog
	ShowPricePerUnitDialog();
}

void CCashExchangeUI::ShowPricePerUnitDialog()
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	if (pUIManager == NULL)
		return;

	CTString strMessage;
	strMessage.PrintF("Listing amount: %I64d cash\n\nPrice per unit (NAS)?", m_llCashAmount);

	// Create command for the numeric input dialog
	CmdCashExchangeNumericInput* pCmd = new CmdCashExchangeNumericInput;
	pCmd->setData(this, CE_MSGCMD_CASH_PRICE);

	// Show numeric input dialog
	CUIMsgBoxNumericOnly* pNumBox = pUIManager->GetMsgBoxNumOnly();
	if (pNumBox != NULL)
	{
		pNumBox->SetInfo(pCmd, "List Cash - Price", strMessage, 1, LLONG_MAX / 2);
	}
}

void CCashExchangeUI::OnPricePerUnitInputConfirm(const CTString& strInput)
{
	// Parse input
	LONGLONG llPrice = _atoi64((const char*)strInput);

	// Validate price
	if (!ValidatePricePerUnit(llPrice))
	{
		// Show error and retry
		// MSGMGR()->ShowMsgBoxOK("Price must be greater than 0");
		// ShowPricePerUnitDialog();
		return;
	}

	// Check for overflow
	if (!ValidateOverflow(m_llCashAmount, llPrice))
	{
		// Show error and retry
		// MSGMGR()->ShowMsgBoxOK("Total price is too high");
		// ShowPricePerUnitDialog();
		return;
	}

	// Store price and calculate total
	m_llPricePerUnit = llPrice;
	m_llTotalValue = m_llCashAmount * m_llPricePerUnit;
	m_nDialogState = CASH_DIALOG_CONFIRM;

	// Show confirmation preview and immediately send on confirmation
	ShowConfirmationPreview();
}

void CCashExchangeUI::ShowConfirmationPreview()
{
	CTString strTitle = "Confirm Listing";
	CTString strAmountStr;
	strAmountStr.PrintF("%I64d", m_llCashAmount);
	CTString strPriceStr;
	strPriceStr.PrintF("%I64d", m_llPricePerUnit);
	CTString strTotalStr;
	strTotalStr.PrintF("%I64d", m_llTotalValue);

	CTString strMessage;
	strMessage.PrintF(
		"Amount: %s cash\n"
		"Price: %s NAS/unit\n"
		"Total: %s NAS\n\n"
		"Do you want to create this listing?",
		(const char*)strAmountStr, (const char*)strPriceStr, (const char*)strTotalStr
	);

	// Use YES/NO message box for confirmation
	MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
		strTitle,
		strMessage,
		eMSG_YESNO,
		true,
		boost::bind(&CCashExchangeUI::OnConfirmListingClick, this),  // OK/YES callback
		NULL,  // NO callback - just close
		NULL   // Close callback
	);
}



void CCashExchangeUI::OnConfirmListingClick()
{
	if (m_nDialogState != CASH_DIALOG_CONFIRM)
		return;

	// Send message to server
	m_nDialogState = CASH_DIALOG_LOADING;
	SendCreateListingMessage();

	// Show loading message
	// MSGMGR()->ShowMsgBoxOK("Creating listing...");
}

void CCashExchangeUI::SendCreateListingMessage()
{
	// Validate inputs before sending
	if (!ValidateCashAmount(m_llCashAmount))
	{
		HandleCreateListingResult(0, 2); // Error code 2: invalid cash amount
		return;
	}

	if (!ValidatePricePerUnit(m_llPricePerUnit))
	{
		HandleCreateListingResult(0, 3); // Error code 3: invalid price
		return;
	}

	if (!ValidateOverflow(m_llCashAmount, m_llPricePerUnit))
	{
		HandleCreateListingResult(0, 4); // Error code 4: overflow
		return;
	}

	// Get player character index
	// TODO: Replace with actual character index retrieval:
	// int nCharIndex = MY_INFO().GetCharIndex();
	int nCharIndex = 0;

	if (_pNetwork == NULL)
		return;

	// Build and send network message using struct-based serialization
	CNetworkMessage nmMsg;
	RequestClient::doCashExchangeCreateListing* packet = 
		reinterpret_cast<RequestClient::doCashExchangeCreateListing*>(nmMsg.nm_pubMessage);
	packet->type = MSG_CASHEXCHANGE;
	packet->subType = MSG_CASHEXCHANGE_CREATE_LISTING;
	packet->charIndex = nCharIndex;
	packet->cashAmount = m_llCashAmount;
	packet->pricePerUnit = m_llPricePerUnit;
	nmMsg.setSize(sizeof(*packet));

	_pNetwork->SendToServerNew(nmMsg);

	// Clear the dialog after sending
	ClearCashListingDialog();
}

void CCashExchangeUI::SendRequestListingsMessage()
{
	if (_pNetwork == NULL)
		return;

	// Build and send network message using struct-based serialization
	CNetworkMessage nmMsg;
	RequestClient::doCashExchangeListRequest* packet = 
		reinterpret_cast<RequestClient::doCashExchangeListRequest*>(nmMsg.nm_pubMessage);
	packet->type = MSG_CASHEXCHANGE;
	packet->subType = MSG_CASHEXCHANGE_LIST_REQUEST;
	packet->page = 1;  // Page 1 is the first page (server calculates offset as (page-1)*pageSize)
	nmMsg.setSize(sizeof(*packet));

	_pNetwork->SendToServerNew(nmMsg);

	CASH_DEBUG_LOG("[CashExchangeUI] SendRequestListingsMessage - request sent to server\n");
	// Do NOT poll here - let the main game loop handle receiving messages
	// Polling on the main thread causes massive lag
}

void CCashExchangeUI::HandleCreateListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance)
{
	if (nSuccess)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] Create listing succeeded! New balance: %I64d\n", newCashBalance);

		// Show success message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			"Listing created successfully!",
			eMSG_OK
		);

		ClearCashListingDialog();

		// Close and reopen the UI to refresh with updated data
		// This ensures we show the new listing immediately
		CloseUI();

		// Schedule a reopen after a short delay to let messages settle
		Sleep(100);
		OpenUI();
	}
	else
	{
		// Handle errors
		CTString strError;

		switch (nErrorCode)
		{
		case 1:
			strError = "Insufficient cash to create listing";
			break;
		case 2:
			strError = "Cash amount must be greater than 0";
			break;
		case 3:
			strError = "Price per unit must be greater than 0";
			break;
		case 4:
			strError = "Total price too high";
			break;
		default:
			strError = "Failed to create listing";
			break;
		}

		CASH_DEBUG_LOG("[CashExchangeUI] Create listing failed: %s (error code %d)\n", (const char*)strError, nErrorCode);

		// Show error message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			strError,
			eMSG_OK
		);

		ClearCashListingDialog();
	}
}

void CCashExchangeUI::HandleBuyListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance)
{
	if (nSuccess)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] Buy listing succeeded! New balance: %I64d\n", newCashBalance);

		// Show success message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			"Listing purchased successfully!",
			eMSG_OK
		);

		// Close and reopen the UI to refresh with updated data
		// This ensures the bought listing is removed or reduced immediately
		CloseUI();

		// Schedule a reopen after a short delay to let messages settle
		Sleep(100);
		OpenUI();
	}
	else
	{
		// Handle errors
		CTString strError;

		switch (nErrorCode)
		{
		case 1:
			strError = "Insufficient cash to buy this listing";
			break;
		case 2:
			strError = "Listing not found or already sold";
			break;
		case 3:
			strError = "Listing is no longer available";
			break;
		case 8:
			strError = "Insufficient NAS to complete this purchase";
			break;
		default:
			strError = "Failed to buy listing";
			break;
		}

		CASH_DEBUG_LOG("[CashExchangeUI] Buy listing failed: %s (error code %d)\n", (const char*)strError, nErrorCode);

		// Show error message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			strError,
			eMSG_OK
		);
	}
}

void CCashExchangeUI::HandleCancelListingResult(int nSuccess, int nErrorCode, LONGLONG newCashBalance)
{
	if (nSuccess)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] Cancel listing succeeded! New balance: %I64d\n", newCashBalance);

		// Show success message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			"Listing cancelled successfully!",
			eMSG_OK
		);

		// Close and reopen the UI to refresh with updated data
		// This ensures the cancelled listing is removed immediately
		CloseUI();

		// Schedule a reopen after a short delay to let messages settle
		Sleep(100);
		OpenUI();
	}
	else
	{
		// Handle errors
		CTString strError;

		switch (nErrorCode)
		{
		case 2:
			strError = "Listing not found";
			break;
		case 3:
			strError = "Listing is no longer available";
			break;
		case 4:
			strError = "You are not the seller of this listing";
			break;
		default:
			strError = "Failed to cancel listing";
			break;
		}

		CASH_DEBUG_LOG("[CashExchangeUI] Cancel listing failed: %s (error code %d)\n", (const char*)strError, nErrorCode);

		// Show error message
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			strError,
			eMSG_OK
		);
	}
}

void CCashExchangeUI::MsgBoxCommand(int nCommandCode, BOOL bOK, CTString& strInput)
{
	if (!bOK)
	{
		// User cancelled
		ClearCashListingDialog();
		return;
	}

	switch (nCommandCode)
	{
	case CE_MSGCMD_CASH_AMOUNT:
		OnCashAmountInputConfirm(strInput);
		break;

	case CE_MSGCMD_CASH_PRICE:
		OnPricePerUnitInputConfirm(strInput);
		break;

	case CE_MSGCMD_CONFIRM:
		OnConfirmListingClick();
		break;

	case 3000:  // Buy partial amount
		OnBuyAmountConfirm(strInput);
		break;

	default:
		break;
	}
}

void CCashExchangeUI::OnBuyAmountConfirm(const CTString& strInput)
{
	// The input from numeric box is just a string representation of the number
	// Try to parse it
	LONGLONG llBuyAmount = 0;

	// CTString can be cast to const char pointer
	if (!strInput.IsEmpty())
	{
		llBuyAmount = _atoi64((const char*)strInput);
	}

	// Validate
	if (m_nBuyListingIndex < 0 || m_nBuyListingIndex >= (int)m_listings.size())
	{
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			"Listing is no longer available",
			eMSG_OK
		);
		m_nBuyListingIndex = -1;
		return;
	}

	const CashListing& listing = m_listings[m_nBuyListingIndex];

	if (llBuyAmount <= 0 || llBuyAmount > listing.cashAmount)
	{
		CTString strError;
		strError.PrintF("Invalid amount. Max available: %I64d", listing.cashAmount);
		MsgBoxMgr::getSingleton()->CreateMsgBoxNEW(
			"Cash Exchange",
			strError,
			eMSG_OK
		);
		return;
	}

	if (_pNetwork == NULL)
	{
		m_nBuyListingIndex = -1;
		return;
	}

	// Build and send buy request to server with the specified amount
	CNetworkMessage nmMsg;
	RequestClient::doCashExchangeBuyListing* packet = 
		reinterpret_cast<RequestClient::doCashExchangeBuyListing*>(nmMsg.nm_pubMessage);
	packet->type = MSG_CASHEXCHANGE;
	packet->subType = MSG_CASHEXCHANGE_BUY_LISTING;
	packet->listingID = listing.listingID;
	packet->cashAmount = llBuyAmount;  // Send the user-specified amount
	nmMsg.setSize(sizeof(*packet));

	_pNetwork->SendToServerNew(nmMsg);

	CASH_DEBUG_LOG("[CashExchangeUI] Buy request sent for listing ID=%d, amount=%I64d (of %I64d available)\n", 
		listing.listingID, llBuyAmount, listing.cashAmount);

	m_nBuyListingIndex = -1;
}

// ========== Helper Methods ==========

void CCashExchangeUI::ClearCashListingDialog()
{
	m_nDialogState = CASH_DIALOG_NONE;
	m_llCashAmount = 0;
	m_llPricePerUnit = 0;
	m_llTotalValue = 0;
}

BOOL CCashExchangeUI::ValidateCashAmount(LONGLONG llAmount)
{
	// Check if amount is positive
	if (llAmount <= 0)
		return FALSE;

	// Check if player has enough cash
	if (llAmount > GetPlayerCashBalance())
		return FALSE;

	return TRUE;
}

BOOL CCashExchangeUI::ValidatePricePerUnit(LONGLONG llPrice)
{
	// Check if price is positive
	if (llPrice <= 0)
		return FALSE;

	return TRUE;
}

BOOL CCashExchangeUI::ValidateOverflow(LONGLONG llAmount, LONGLONG llPrice)
{
	// Check for overflow: amount * price should not exceed LONGLONG max
	if (llAmount > LLONG_MAX / llPrice)
		return FALSE;

	return TRUE;
}

LONGLONG CCashExchangeUI::GetPlayerCashBalance() const
{
	// Get player's current cash balance from bg_user.cash (premium currency in database)
	// 
	// The premium cash comes from UpdateClient::money packet which contains:
	// - nas: Regular NAS currency (in-game gold)
	// - bonus: Premium cash (from bg_user.cash in database)
	//
	// This is accessed via the CashShop UI which stores it in m_hasCash:
	// The cash shop sets this via SetMyCash(SQUAD myCash) when it receives
	// the MSG_EX_CASHITEM_BALANCE_REP message from the server.
	//
	// For the cash exchange feature, we retrieve the same cash value that
	// the cash shop displays to the player.

	CUIManager* pUIManager = CUIManager::getSingleton();
	if (pUIManager == NULL)
		return 0;

	CUICashShopEX* pCashShop = pUIManager->GetCashShopEX();
	if (pCashShop == NULL)
		return 0;

	// GetMyCash() returns the player's current premium cash balance
	// This value is updated whenever the server sends a money update packet
	return (LONGLONG)pCashShop->GetMyCash();
}

void CCashExchangeUI::HandleListingResponse(CNetworkMessage& msg)
{
	// Parse listing response from server
	// Format: type(1) subType(1) count(4) [listingID(4) sellerCharIndex(4) sellerNameLen(2) sellerName(n) cashAmount(8) pricePerUnit(8) totalPrice(8)]...

	CASH_DEBUG_LOG("[CashExchangeUI] HandleListingResponse called\n");
	CASH_DEBUG_LOG("[CashExchangeUI] Message size = %d bytes\n", msg.nm_slSize);

	ClearListings();

	// Get the message buffer and pointer
	unsigned char* pBuf = (unsigned char*)msg.nm_pubMessage;
	int nPos = 0;

	// Validate minimum message size (type + subType + count)
	if (msg.nm_slSize < 6)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] ERROR - Message too small: %d bytes\n", msg.nm_slSize);
		return;
	}

	// Skip type and subType (already consumed by dispatcher)
	nPos += 2;

	// Read count as int (4 bytes) to match struct definition
	int nCount = *(int*)(pBuf + nPos);
	nPos += sizeof(int);

	CASH_DEBUG_LOG("[CashExchangeUI] Listing count = %d\n", nCount);

	// Validate count to prevent excessive iteration
	if (nCount < 0 || nCount > 1000)
	{
		CASH_DEBUG_LOG("[CashExchangeUI] ERROR - Invalid listing count: %d\n", nCount);
		return;
	}

	for (int i = 0; i < nCount; i++)
	{
		// Validate we have enough data for minimum listing fields
		// (ID + SellerIdx + NameLen = 4 + 4 + 2 = 10 bytes minimum)
		if (nPos + 10 > msg.nm_slSize)
		{
			CASH_DEBUG_LOG("[CashExchangeUI] ERROR - Buffer overrun detected at listing %d\n", i);
			break;
		}

		CashListing listing;

		// Read listing ID (int)
		listing.listingID = *(int*)(pBuf + nPos);
		nPos += sizeof(int);

		// Read seller character index (int)
		listing.sellerCharIndex = *(int*)(pBuf + nPos);
		nPos += sizeof(int);

		// Read seller name (string with length prefix)
		unsigned short nameLen = *(unsigned short*)(pBuf + nPos);
		nPos += sizeof(unsigned short);

		// Validate we have enough data for the name
		if (nPos + nameLen > msg.nm_slSize)
		{
			CASH_DEBUG_LOG("[CashExchangeUI] ERROR - Buffer overrun when reading name at listing %d, nameLen=%d\n", i, nameLen);
			break;
		}

		// Validate name length to prevent buffer overrun
		if (nameLen == 0 || nameLen > 255)
		{
			CASH_DEBUG_LOG("[CashExchangeUI] ERROR - Invalid name length: %d\n", nameLen);
			continue;  // Skip this listing
		}

		char szSellerName[256];
		memcpy(szSellerName, pBuf + nPos, nameLen);
		szSellerName[nameLen] = '\0';
		listing.sellerName = szSellerName;
		nPos += nameLen;

		// Read amounts
		listing.cashAmount = *(__int64*)(pBuf + nPos);
		nPos += sizeof(__int64);
		listing.pricePerUnit = *(__int64*)(pBuf + nPos);
		nPos += sizeof(__int64);
		listing.totalPrice = *(__int64*)(pBuf + nPos);
		nPos += sizeof(__int64);

		CASH_DEBUG_LOG("[CashExchangeUI] Parsed listing %d: ID=%d, SellerIdx=%d, Seller=%s, Cash=%lld, Price=%lld\n", i, listing.listingID, listing.sellerCharIndex, (const char*)listing.sellerName, listing.cashAmount, listing.pricePerUnit);

		// Add to UI
		AddListing(listing);
	}
}

// Static handler for incoming MSG_CASHEXCHANGE messages
void CCashExchangeUI::ProcessCashExchangeMessage(CNetworkMessage& msg)
{
	// Get the UI instance
	CCashExchangeUI* pUI = (CCashExchangeUI*)UIMGR()->GetUI(UI_CASHEXCHANGE);
	if (pUI == NULL)
		return;

	// Read the message header to determine what type of response this is
	unsigned char* pBuf = (unsigned char*)msg.nm_pubMessage;
	unsigned char type = pBuf[0];
	unsigned char subType = pBuf[1];

	CASH_DEBUG_LOG("[CashExchangeUI] ProcessCashExchangeMessage - subType=%d, msgSize=%d\n", subType, msg.nm_slSize);

	// Route to appropriate handler based on subType
	switch (subType)
	{
	case 1:  // MSG_CASHEXCHANGE_CREATE_LISTING_RESULT
	{
		// Parse the result packet with newCashBalance
		if (msg.nm_slSize >= sizeof(UpdateClient::doCashExchangeCreateListingResult))
		{
			UpdateClient::doCashExchangeCreateListingResult* pResult = 
				(UpdateClient::doCashExchangeCreateListingResult*)pBuf;
			pUI->HandleCreateListingResult(pResult->success, pResult->errorCode, pResult->newCashBalance);
		}
		else
		{
			// Fallback for older packet format
			pUI->HandleCreateListingResult(pBuf[2], pBuf[3], 0);
		}
		break;
	}

	case 2:  // MSG_CASHEXCHANGE_BUY_LISTING_RESULT
	{
		// Parse the result packet with newCashBalance
		if (msg.nm_slSize >= sizeof(UpdateClient::doCashExchangeBuyListingResult))
		{
			UpdateClient::doCashExchangeBuyListingResult* pResult = 
				(UpdateClient::doCashExchangeBuyListingResult*)pBuf;
			pUI->HandleBuyListingResult(pResult->success, pResult->errorCode, pResult->newCashBalance);
		}
		else
		{
			// Fallback for older packet format
			pUI->HandleBuyListingResult(pBuf[2], pBuf[3], 0);
		}
		break;
	}

	case 4:  // MSG_CASHEXCHANGE_CANCEL_LISTING_RESULT
	{
		// Parse the result packet with newCashBalance
		if (msg.nm_slSize >= sizeof(UpdateClient::doCashExchangeCancelListingResult))
		{
			UpdateClient::doCashExchangeCancelListingResult* pResult = 
				(UpdateClient::doCashExchangeCancelListingResult*)pBuf;
			pUI->HandleCancelListingResult(pResult->success, pResult->errorCode, pResult->newCashBalance);
		}
		else
		{
			// Fallback for older packet format
			pUI->HandleCancelListingResult(pBuf[2], pBuf[3], 0);
		}
		break;
	}

	case 3:  // MSG_CASHEXCHANGE_LIST_RESPONSE
		pUI->HandleListingResponse(msg);
		break;

	default:
		break;
	}
}

// Process any pending cash exchange messages from the network
void CCashExchangeUI::ProcessPendingMessages()
{
	if (_pNetwork == NULL)
		return;

	// Try to receive multiple pending cash exchange messages
	// This polling mechanism handles messages that may have arrived
	// from the server while the UI was processing
	CNetworkMessage nmMsg;

	// Keep receiving until no more messages are available
	// This ensures we don't miss any cash exchange responses
	while (_pNetwork->ReceiveFromServerNew(nmMsg))
	{
		// Check if we got any data
		unsigned char* pBuf = (unsigned char*)nmMsg.nm_pubMessage;
		if (pBuf != NULL && nmMsg.nm_slSize > 0)
		{
			unsigned char ubType = pBuf[0];

			// If it's a cash exchange message, process it
			if (ubType == MSG_CASHEXCHANGE)
			{
				ProcessCashExchangeMessage(nmMsg);
			}
			else
			{
				// Not a cash exchange message
				// In a fully integrated system, this would be routed to the main dispatcher
				// For now, we just skip non-cash-exchange messages
			}
		}
		else
		{
			// No more messages available
			break;
		}
	}
}

int CCashExchangeUI::GetCurrentPlayerCharIndex() const
{
	// Get the local player's character index from the network connection
	// This index is used to determine if the current player is the seller of a listing

	if (_pNetwork != NULL)
	{
		return _pNetwork->MyCharacterInfo.index;
	}

	// Fallback if network is not available
	CASH_DEBUG_LOG("[CashExchangeUI] GetCurrentPlayerCharIndex() - network unavailable, returning 0\n");
	return 0;
}
