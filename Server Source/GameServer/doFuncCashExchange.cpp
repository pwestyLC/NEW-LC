#include "stdhdrs.h"
#include "Log.h"
#include "Character.h"
#include "Server.h"
#include "doFunc.h"
#include "../ShareLib/MessageType.h"
#include "../ShareLib/packetType/ptype_cash_exchange.h"
#include "../ShareLib/Config.h"
#include "CashExchangeDB.h"
#include "DBManager.h"
#include "MailBoxManager.h"
#include <boost/format.hpp>

void do_CashExchangeCreateListing(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || !ch->m_desc)
	{
		GAMELOG << init("CASHEXCHANGE CREATE - INVALID CHARACTER") << end;
		return;
	}

	// Parse request
	RequestClient::doCashExchangeCreateListing* req = (RequestClient::doCashExchangeCreateListing*)msg->m_buf;

	long long cashAmount = req->cashAmount;
	long long pricePerUnit = req->pricePerUnit;

	GAMELOG << init("CASHEXCHANGE CREATE REQUEST", ch)
			<< "CashAmount: " << cashAmount
			<< " PricePerUnit: " << pricePerUnit
			<< end;

	// VALIDATION
	if (cashAmount <= 0 || pricePerUnit <= 0)
	{
		GAMELOG << init("CASHEXCHANGE CREATE FAILED - INVALID AMOUNT", ch) << end;
		return;
	}

	// Check seller's current cash
	char szQuery[2048];
	sprintf_s(szQuery, sizeof(szQuery), "SELECT cash FROM bg_user WHERE user_code = %d", ch->m_desc->m_index);

	LONGLONG sellerCurrentCash = 0;
	if (mysql_query(&gserver->m_dbauth, szQuery) == 0)
	{
		MYSQL_RES* result = mysql_store_result(&gserver->m_dbauth);
		MYSQL_ROW row = result ? mysql_fetch_row(result) : NULL;
		if (row && row[0])
		{
			sellerCurrentCash = _atoi64(row[0]);
		}
		if (result)
			mysql_free_result(result);
	}

	if (sellerCurrentCash < cashAmount)
	{
		GAMELOG << init("CASHEXCHANGE CREATE FAILED - NOT ENOUGH CASH", ch)
				<< "CharIndex: " << ch->m_index
				<< " CurrentCash: " << sellerCurrentCash
				<< " RequestedAmount: " << cashAmount
				<< end;
		return;
	}

	// Deduct cash from seller
	long long newCash = sellerCurrentCash - cashAmount;
	sprintf_s(szQuery, sizeof(szQuery), "UPDATE bg_user SET cash = %lld WHERE user_code = %d",
		newCash, ch->m_desc->m_index);

	GAMELOG << init("CASHEXCHANGE CREATE - DEDUCT CASH QUERY", ch)
			<< "Query: " << szQuery
			<< end;

	if (mysql_query(&gserver->m_dbauth, szQuery))
	{
		GAMELOG << init("CASHEXCHANGE CREATE FAILED - DEDUCT ERROR", ch)
				<< "Error: " << mysql_error(&gserver->m_dbauth)
				<< end;
		return;
	}

	// Create listing in database
	std::string sellerName((const char*)ch->m_name);
	long long listingId = CashExchangeDB::instance().CreateListing(ch->m_index, sellerName, cashAmount, pricePerUnit);

	if (listingId <= 0)
	{
		// Restore cash on database error
		sprintf_s(szQuery, sizeof(szQuery), "UPDATE bg_user SET cash = %lld WHERE user_code = %d",
			sellerCurrentCash, ch->m_desc->m_index);
		mysql_query(&gserver->m_dbauth, szQuery);

		GAMELOG << init("CASHEXCHANGE CREATE FAILED - DB ERROR", ch) << end;
		return;
	}

	GAMELOG << init("CASHEXCHANGE CREATE SUCCESS", ch)
			<< "ListingID: " << listingId
			<< " NewCashBalance: " << newCash
			<< end;
}

void do_CashExchangeBuyListing(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || !ch->m_desc)
	{
		GAMELOG << init("CASHEXCHANGE BUY - INVALID CHARACTER") << end;
		return;
	}

	RequestClient::doCashExchangeBuyListing* req = (RequestClient::doCashExchangeBuyListing*)msg->m_buf;
	long long listingID = req->listingID;
	long long buyAmount = req->cashAmount;  // Amount buyer wants to buy

	GAMELOG << init("CASHEXCHANGE BUY REQUEST", ch)
			<< "ListingID: " << listingID
			<< " BuyAmount: " << buyAmount
			<< end;

	// Get listing details
	CashListing listing = CashExchangeDB::instance().GetListing(listingID);

	if (listing.listingId <= 0 || listing.active == 0)
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - LISTING NOT FOUND", ch)
				<< "ListingID: " << listingID
				<< end;
		return;
	}

	// Check if buyer is the seller (prevent self-buying)
	if (listing.sellerCharIndex == ch->m_index)
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - SELF BUY", ch)
				<< "Seller: " << listing.sellerCharIndex
				<< " Buyer: " << ch->m_index
				<< end;
		return;
	}

	// Validate buy amount
	if (buyAmount <= 0 || buyAmount > listing.cashAmount)
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - INVALID AMOUNT", ch)
				<< "RequestedAmount: " << buyAmount
				<< " ListingAmount: " << listing.cashAmount
				<< end;
		return;
	}

	// Calculate total NAS price for this purchase
	long long totalNasPrice = buyAmount * listing.pricePerUnit;

	GAMELOG << init("CASHEXCHANGE BUY DEBUG IDENTIFIERS", ch)
			<< "ch->m_index=" << ch->m_index
			<< " ch->m_desc->m_index=" << ch->m_desc->m_index
			<< " ch->m_name=" << (const char*)ch->m_name
			<< " ch->m_inventory.getMoney()=" << ch->m_inventory.getMoney()
			<< end;

	// Get buyer's current NAS from t_characters
	char szQuery[2048];
	sprintf_s(szQuery, sizeof(szQuery), "SELECT a_nas FROM t_characters WHERE a_index = %d", ch->m_index);

	LONGLONG buyerNas = 0;
	if (mysql_query(&gserver->m_dbchar, szQuery) == 0)
	{
		MYSQL_RES* result = mysql_store_result(&gserver->m_dbchar);
		if (result)
		{
			MYSQL_ROW row = mysql_fetch_row(result);
			if (row && row[0])
			{
				buyerNas = _atoi64(row[0]);
			}
			mysql_free_result(result);
		}
	}
	else
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - NAS QUERY ERROR", ch)
				<< "Query failed: " << mysql_error(&gserver->m_dbchar)
				<< end;
		return;
	}

	// Check if buyer has enough NAS
	if (buyerNas < totalNasPrice)
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - NOT ENOUGH NAS", ch)
				<< "BuyerNas: " << buyerNas
				<< " RequiredNas: " << totalNasPrice
				<< end;
		return;
	}

	GAMELOG << init("CASHEXCHANGE BUY PROCESSING")
			<< "All validations passed, processing transaction"
			<< " ListingID: " << listingID
			<< " BuyAmount: " << buyAmount
			<< " TotalPrice: " << totalNasPrice
			<< end;

	// Step 1: Add cash to buyer's account in bg_user
	sprintf_s(szQuery, sizeof(szQuery), "UPDATE bg_user SET cash = (cash + %lld) WHERE user_code = %d",
		buyAmount, ch->m_desc->m_index);

	if (mysql_query(&gserver->m_dbauth, szQuery))
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - ADD CASH ERROR", ch)
				<< "Failed to add cash to buyer"
				<< " ListingID: " << listingID
				<< " Amount: " << buyAmount
				<< end;
		return;
	}

	GAMELOG << init("CASHEXCHANGE BUY - CASH ADDED SUCCESS", ch)
			<< "Added cash to buyer account"
			<< " Amount: " << buyAmount
			<< " UserCode: " << ch->m_desc->m_index
			<< end;

	// Step 2: Deduct NAS from buyer's LIVE inventory and mail NAS to seller
	// The buyer pays NAS (from their current inventory), seller receives NAS via mail
	// Mail system works for both online and offline sellers

	// Deduct NAS from buyer's live inventory (this updates the player immediately)
	ch->m_inventory.decreaseMoney(totalNasPrice);

	GAMELOG << init("CASHEXCHANGE BUY - NAS DEDUCTED FROM BUYER INVENTORY", ch)
			<< "Deducted NAS from buyer's live inventory"
			<< " Amount: " << totalNasPrice
			<< " BuyerCharIndex: " << ch->m_index
			<< end;

	// Mail the NAS to the seller (works whether they're online or offline)
	// Try to get the seller if they're online
	CPC* sellerCh = PCManager::instance()->getPlayerByCharIndex(listing.sellerCharIndex);

	BOOL bMailSent = FALSE;
	if (sellerCh != NULL && sellerCh->m_desc != NULL)
	{
		// Seller is online - send mail via the global MailBoxManager instance
		SendingSystemMailInfo mailInfo;
		mailInfo.Receiver = sellerCh;
		mailInfo.Subject = "Cash Exchange Sale";
		mailInfo.Message = boost::str(boost::format("You sold %lld cash for %lld NAS to player %s") 
			% buyAmount % totalNasPrice % std::string((const char*)ch->m_name));
		mailInfo.Nas = totalNasPrice;
		mailInfo.ItemCount = 0;

		// Use the global singleton instance, not a local one
		gserver->m_mailBoxManager.SendSystemMail(mailInfo);
		bMailSent = TRUE;

		GAMELOG << init("CASHEXCHANGE BUY - NAS MAILED TO SELLER (ONLINE)", ch)
				<< "Mailed NAS to online seller via MailBoxManager"
				<< " Amount: " << totalNasPrice
				<< " SellerCharIndex: " << listing.sellerCharIndex
				<< " SellerName: " << listing.sellerName.c_str()
				<< end;
	}
	else
	{
		// Seller is offline - we need to insert mail into database
		// For now, we'll store the NAS directly in database and they'll get it on next login
		// TODO: Implement mail database insertion for offline players
		sprintf_s(szQuery, sizeof(szQuery), "UPDATE t_characters SET a_nas = (a_nas + %lld) WHERE a_index = %d",
			totalNasPrice, listing.sellerCharIndex);

		if (mysql_query(&gserver->m_dbchar, szQuery))
		{
			GAMELOG << init("CASHEXCHANGE BUY FAILED - ADD NAS TO SELLER ERROR", ch)
					<< "Failed to add NAS to offline seller"
					<< " ListingID: " << listingID
					<< " NasAmount: " << totalNasPrice
					<< " SellerCharIndex: " << listing.sellerCharIndex
					<< " Error: " << mysql_error(&gserver->m_dbchar)
					<< end;
			return;
		}

		GAMELOG << init("CASHEXCHANGE BUY - NAS STORED FOR OFFLINE SELLER", ch)
				<< "Stored NAS in database for offline seller"
				<< " Amount: " << totalNasPrice
				<< " SellerCharIndex: " << listing.sellerCharIndex
				<< " SellerName: " << listing.sellerName.c_str()
				<< end;
	}

	// Step 3: Update listing to reflect partial buy or mark as complete
	if (!CashExchangeDB::instance().ReduceListingCash(listingID, buyAmount, ch->m_index, std::string((const char*)ch->m_name)))
	{
		GAMELOG << init("CASHEXCHANGE BUY FAILED - UPDATE LISTING ERROR", ch)
				<< "Failed to reduce listing cash"
				<< " ListingID: " << listingID
				<< end;
		return;
	}

	// Step 4: Log the purchase to buyer's history
	CashExchangeDB::instance().LogPurchase(
		ch->m_index,
		std::string((const char*)ch->m_name),
		listing.sellerCharIndex,
		listing.sellerName,
		buyAmount,
		listing.pricePerUnit,
		totalNasPrice,
		listingID
	);

	GAMELOG << init("CASHEXCHANGE BUY SUCCESS", ch)
			<< "Transaction complete!"
			<< " ListingID: " << listingID
			<< " Seller: " << listing.sellerName.c_str()
			<< " Buyer: " << std::string((const char*)ch->m_name).c_str()
			<< " CashAmount: " << buyAmount
			<< " NasPrice: " << totalNasPrice
			<< end;
}

void do_CashExchangeCancelListing(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || !ch->m_desc)
	{
		GAMELOG << init("CASHEXCHANGE CANCEL - INVALID CHARACTER") << end;
		return;
	}

	RequestClient::doCashExchangeCancelListing* req = (RequestClient::doCashExchangeCancelListing*)msg->m_buf;
	long long listingID = req->listingID;

	GAMELOG << init("CASHEXCHANGE CANCEL REQUEST", ch)
			<< "ListingID: " << listingID
			<< end;

	// Get listing details
	CashListing listing = CashExchangeDB::instance().GetListing(listingID);

	if (listing.listingId <= 0)
	{
		GAMELOG << init("CASHEXCHANGE CANCEL FAILED - NOT FOUND", ch)
				<< "ListingID: " << listingID
				<< end;
		return;
	}

	// Check if requester is the seller
	if (listing.sellerCharIndex != ch->m_index)
	{
		GAMELOG << init("CASHEXCHANGE CANCEL FAILED - NOT SELLER", ch)
				<< "ListingID: " << listingID
				<< " SellerCharIndex: " << listing.sellerCharIndex
				<< " RequesterCharIndex: " << ch->m_index
				<< end;
		return;
	}

	// Cancel the listing (mark as inactive)
	if (!CashExchangeDB::instance().CancelListing(listingID))
	{
		GAMELOG << init("CASHEXCHANGE CANCEL FAILED - DB ERROR", ch)
				<< "ListingID: " << listingID
				<< end;
		return;
	}

	// Refund the cash to the seller
	char szQuery[2048];
	sprintf_s(szQuery, sizeof(szQuery), "UPDATE bg_user SET cash = (cash + %lld) WHERE user_code = %d",
		listing.cashAmount, ch->m_desc->m_index);

	if (mysql_query(&gserver->m_dbauth, szQuery))
	{
		GAMELOG << init("CASHEXCHANGE CANCEL FAILED - REFUND ERROR", ch)
				<< "ListingID: " << listingID
				<< " Error: " << mysql_error(&gserver->m_dbauth)
				<< end;
		return;
	}

	GAMELOG << init("CASHEXCHANGE CANCEL SUCCESS", ch)
			<< "Listing cancelled"
			<< " ListingID: " << listingID
			<< " RefundedAmount: " << listing.cashAmount
			<< end;
}

void do_CashExchangeListRequest(CPC* ch, CNetMsg::SP& msg)
{
	if (!ch || !ch->m_desc)
	{
		GAMELOG << init("CASHEXCHANGE LIST - INVALID CHARACTER") << end;
		return;
	}

	RequestClient::doCashExchangeListRequest* req = (RequestClient::doCashExchangeListRequest*)msg->m_buf;
	int page = req->page;

	if (page < 1)
		page = 1;

	GAMELOG << init("CASHEXCHANGE LIST REQUEST", ch)
			<< "Page: " << page
			<< end;

	// Get active listings from database for this page
	std::vector<CashListing> listings = CashExchangeDB::instance().GetActiveListings(page, 20);

	GAMELOG << init("CASHEXCHANGE LIST QUERY", ch)
			<< "Retrieved " << listings.size() << " active listings for page " << page
			<< end;

	// Build response packet with listing data
	unsigned char* pBuf;
	CNetMsg::SP rmsg(new CNetMsg);
	pBuf = rmsg->m_buf;
	int nPos = 0;

	// Write message header
	pBuf[nPos++] = MSG_CASHEXCHANGE;
	pBuf[nPos++] = MSG_CASHEXCHANGE_LIST_RESPONSE;

	// Write listing count
	*(int*)(pBuf + nPos) = (int)listings.size();
	nPos += sizeof(int);

	// Write each listing
	for (const CashListing& listing : listings)
	{
		*(int*)(pBuf + nPos) = listing.listingId;
		nPos += sizeof(int);

		*(int*)(pBuf + nPos) = listing.sellerCharIndex;
		nPos += sizeof(int);

		// Seller name (string with length prefix)
		unsigned short nameLen = (unsigned short)listing.sellerName.length();
		*(unsigned short*)(pBuf + nPos) = nameLen;
		nPos += sizeof(unsigned short);

		memcpy(pBuf + nPos, listing.sellerName.c_str(), nameLen);
		nPos += nameLen;

		*(long long*)(pBuf + nPos) = listing.cashAmount;
		nPos += sizeof(long long);

		*(long long*)(pBuf + nPos) = listing.pricePerUnit;
		nPos += sizeof(long long);

		*(long long*)(pBuf + nPos) = listing.totalPrice;
		nPos += sizeof(long long);

		*(long long*)(pBuf + nPos) = (long long)listing.createdAt;
		nPos += sizeof(long long);

		GAMELOG << init("CASHEXCHANGE LIST - SERIALIZED LISTING")
				<< "ID: " << listing.listingId
				<< " Seller: " << listing.sellerName.c_str()
				<< " Cash: " << listing.cashAmount
				<< " Price/Unit: " << listing.pricePerUnit
				<< end;
	}

	rmsg->setSize(nPos);

	GAMELOG << init("CASHEXCHANGE LIST RESPONSE SEND", ch)
			<< "Sending " << listings.size() << " listings"
			<< end;

	SEND_Q(rmsg, ch->m_desc);
}

void do_CashExchange(CPC* ch, CNetMsg::SP& msg)
{
	if (!msg || msg->m_size < 2)
	{
		GAMELOG << init("CASHEXCHANGE - INVALID MESSAGE") << end;
		return;
	}

	unsigned char subType = msg->m_buf[1];

	switch (subType)
	{
	case MSG_CASHEXCHANGE_CREATE_LISTING:
		do_CashExchangeCreateListing(ch, msg);
		break;
	case MSG_CASHEXCHANGE_BUY_LISTING:
		do_CashExchangeBuyListing(ch, msg);
		break;
	case MSG_CASHEXCHANGE_CANCEL_LISTING:
		do_CashExchangeCancelListing(ch, msg);
		break;
	case MSG_CASHEXCHANGE_LIST_REQUEST:
		do_CashExchangeListRequest(ch, msg);
		break;
	default:
		GAMELOG << init("CASHEXCHANGE - UNKNOWN SUBTYPE") << "SubType: " << (int)subType << end;
		break;
	}
}
