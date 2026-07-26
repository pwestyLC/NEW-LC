#include "stdhdrs.h"
#include "CashExchangeDB.h"
#include "DBManager.h"
#include "Server.h"
#include "../ShareLib/mysqldb.h"

long long CashExchangeDB::CreateListing(int sellerCharIndex, const std::string& sellerName, 
										long long cashAmount, long long pricePerUnit)
{
	long long totalPrice = cashAmount * pricePerUnit;

	// Build insert query
	std::string query = boost::str(
		boost::format("INSERT INTO t_cash_exchange_listings "
					  "(seller_char_index, seller_name, cash_amount, price_per_unit, total_price, created_at, active) "
					  "VALUES (%d, '%s', %lld, %lld, %lld, NOW(), 1)")
		% sellerCharIndex
		% sellerName
		% cashAmount
		% pricePerUnit
		% totalPrice
	);

	GAMELOG << init("CASHEXCHANGE DB - CreateListing")
			<< "Query: " << query.c_str()
			<< end;

	// Execute query via m_dbauth connection
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - CreateListing") 
				<< "Query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return -1;
	}

	// Get the last inserted ID
	long long listingId = mysql_insert_id(&gserver->m_dbauth);

	GAMELOG << init("CASHEXCHANGE DB - CreateListing SUCCESS")
			<< "Created listing ID: " << listingId
			<< " Seller: " << sellerName.c_str()
			<< end;

	return listingId;
}

std::vector<CashListing> CashExchangeDB::GetActiveListings(int page, int pageSize)
{
	std::vector<CashListing> listings;

	int offset = (page - 1) * pageSize;

	std::string query = boost::str(
		boost::format("SELECT listing_id, seller_char_index, seller_name, cash_amount, "
					  "price_per_unit, total_price, created_at, active "
					  "FROM t_cash_exchange_listings "
					  "WHERE active = 1 "
					  "ORDER BY created_at DESC "
					  "LIMIT %d OFFSET %d")
		% pageSize
		% offset
	);

	GAMELOG << init("CASHEXCHANGE DB - GetActiveListings")
			<< "Fetching page: " << page << " (offset: " << offset << ", limit: " << pageSize << ")"
			<< " Query: " << query.c_str()
			<< end;

	// First, check total count of ALL listings (for debugging)
	std::string countQuery = "SELECT COUNT(*) FROM t_cash_exchange_listings";
	if (!mysql_query(&gserver->m_dbauth, countQuery.c_str()))
	{
		MYSQL_RES* countResult = mysql_store_result(&gserver->m_dbauth);
		if (countResult)
		{
			MYSQL_ROW countRow = mysql_fetch_row(countResult);
			if (countRow)
			{
				GAMELOG << init("CASHEXCHANGE DB - Total Listings Count")
						<< "Total listings in DB: " << countRow[0]
						<< end;
			}
			mysql_free_result(countResult);
		}
	}

	// Check active count
	std::string activeCountQuery = "SELECT COUNT(*) FROM t_cash_exchange_listings WHERE active = 1";
	if (!mysql_query(&gserver->m_dbauth, activeCountQuery.c_str()))
	{
		MYSQL_RES* activeResult = mysql_store_result(&gserver->m_dbauth);
		if (activeResult)
		{
			MYSQL_ROW activeRow = mysql_fetch_row(activeResult);
			if (activeRow)
			{
				GAMELOG << init("CASHEXCHANGE DB - Active Listings Count")
						<< "Active listings (active=1): " << activeRow[0]
						<< end;
			}
			mysql_free_result(activeResult);
		}
	}

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - GetActiveListings") 
				<< "Query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listings;
	}

	MYSQL_RES* result = mysql_store_result(&gserver->m_dbauth);
	if (!result)
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - GetActiveListings") 
				<< "Failed to store result: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listings;
	}

	MYSQL_ROW row;
	int count = 0;
	while ((row = mysql_fetch_row(result)))
	{
		CashListing listing;
		listing.listingId = atoll(row[0]);
		listing.sellerCharIndex = atoi(row[1]);
		listing.sellerName = row[2];
		listing.cashAmount = atoll(row[3]);
		listing.pricePerUnit = atoll(row[4]);
		listing.totalPrice = atoll(row[5]);
		listing.createdAt = (time_t)atoll(row[6]);
		listing.active = atoi(row[7]);
		listings.push_back(listing);

		GAMELOG << init("CASHEXCHANGE DB - Fetched Listing")
				<< "ID: " << listing.listingId
				<< " Seller: " << listing.sellerName.c_str()
				<< " Cash: " << listing.cashAmount
				<< " Active: " << listing.active
				<< end;
		count++;
	}

	mysql_free_result(result);

	GAMELOG << init("CASHEXCHANGE DB - GetActiveListings SUCCESS")
			<< "Retrieved " << count << " listings for page: " << page
			<< end;

	return listings;
}

CashListing CashExchangeDB::GetListing(long long listingId)
{
	CashListing listing = {0};

	std::string query = boost::str(
		boost::format("SELECT listing_id, seller_char_index, seller_name, cash_amount, "
					  "price_per_unit, total_price, created_at, active, "
					  "buyer_char_index, buyer_name "
					  "FROM t_cash_exchange_listings "
					  "WHERE listing_id = %lld")
		% listingId
	);

	GAMELOG << init("CASHEXCHANGE DB - GetListing")
			<< "Query for ID: " << listingId
			<< end;

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - GetListing") 
				<< "Query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listing;
	}

	MYSQL_RES* result = mysql_store_result(&gserver->m_dbauth);
	if (!result)
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - GetListing") 
				<< "Failed to store result: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listing;
	}

	MYSQL_ROW row = mysql_fetch_row(result);
	if (row)
	{
		listing.listingId = atoll(row[0]);
		listing.sellerCharIndex = atoi(row[1]);
		listing.sellerName = row[2];
		listing.cashAmount = atoll(row[3]);
		listing.pricePerUnit = atoll(row[4]);
		listing.totalPrice = atoll(row[5]);
		listing.createdAt = (time_t)atoll(row[6]);
		listing.active = atoi(row[7]);
		listing.buyerCharIndex = row[8] ? atoi(row[8]) : 0;
		listing.buyerName = row[9] ? row[9] : "";

		GAMELOG << init("CASHEXCHANGE DB - GetListing SUCCESS")
				<< "Found listing ID: " << listing.listingId
				<< " Seller: " << listing.sellerName.c_str()
				<< " Active: " << listing.active
				<< end;
	}
	else
	{
		GAMELOG << init("CASHEXCHANGE DB - GetListing NOT FOUND")
				<< "No listing found for ID: " << listingId
				<< end;
	}

	mysql_free_result(result);
	return listing;
}

bool CashExchangeDB::MarkListingBought(long long listingId, int buyerCharIndex, const std::string& buyerName)
{
	std::string query = boost::str(
		boost::format("UPDATE t_cash_exchange_listings "
					  "SET active = 0, bought_at = NOW(), buyer_char_index = %d, buyer_name = '%s' "
					  "WHERE listing_id = %lld")
		% buyerCharIndex
		% buyerName
		% listingId
	);

	GAMELOG << init("CASHEXCHANGE DB - MarkListingBought")
			<< "Marking listing ID: " << listingId << " as bought by: " << buyerName.c_str()
			<< end;

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - MarkListingBought") 
				<< "Query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return false;
	}

	int affectedRows = mysql_affected_rows(&gserver->m_dbauth);
	GAMELOG << init("CASHEXCHANGE DB - MarkListingBought SUCCESS")
			<< "Updated " << affectedRows << " rows for listing ID: " << listingId
			<< end;

	return true;
}

bool CashExchangeDB::ReduceListingCash(long long listingId, long long amountBought, int buyerCharIndex, const std::string& buyerName)
{
	// First get the current cash amount
	CashListing listing = GetListing(listingId);
	if (listing.listingId <= 0)
	{
		GAMELOG << init("CASHEXCHANGE DB - ReduceListingCash ERROR")
				<< "Listing not found: " << listingId
				<< end;
		return false;
	}

	// Calculate remaining cash
	long long remainingCash = listing.cashAmount - amountBought;
	int newActive = (remainingCash > 0) ? 1 : 0;  // Keep active if cash remains, mark bought if depleted

	// Update the listing
	std::string query = boost::str(
		boost::format("UPDATE t_cash_exchange_listings "
					  "SET cash_amount = %lld, active = %d, buyer_char_index = %d, buyer_name = '%s', bought_at = NOW() "
					  "WHERE listing_id = %lld")
		% remainingCash
		% newActive
		% buyerCharIndex
		% buyerName
		% listingId
	);

	GAMELOG << init("CASHEXCHANGE DB - ReduceListingCash")
			<< "Listing ID: " << listingId
			<< " Bought: " << amountBought
			<< " Remaining: " << remainingCash
			<< " NewActive: " << newActive
			<< end;

	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - ReduceListingCash")
				<< "Query failed: " << mysql_error(&gserver->m_dbauth)
				<< end;
		return false;
	}

	int affectedRows = mysql_affected_rows(&gserver->m_dbauth);
	GAMELOG << init("CASHEXCHANGE DB - ReduceListingCash SUCCESS")
			<< "Updated " << affectedRows << " rows for listing ID: " << listingId
			<< " Remaining cash: " << remainingCash
			<< end;

	return true;
}

bool CashExchangeDB::CancelListing(long long listingId)
{
	std::string query = boost::str(
		boost::format("UPDATE t_cash_exchange_listings "
					  "SET active = 0, cancelled_at = NOW() "
					  "WHERE listing_id = %lld")
		% listingId
	);

	GAMELOG << init("CASHEXCHANGE DB - CancelListing")
			<< "Cancelling listing ID: " << listingId
			<< end;

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - CancelListing") 
				<< "Query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return false;
	}

	int affectedRows = mysql_affected_rows(&gserver->m_dbauth);
	GAMELOG << init("CASHEXCHANGE DB - CancelListing SUCCESS")
			<< "Updated " << affectedRows << " rows for listing ID: " << listingId
			<< end;

	return true;
}

bool CashExchangeDB::DeleteListing(long long listingId)
{
	std::string query = boost::str(
		boost::format("DELETE FROM t_cash_exchange_listings WHERE listing_id = %lld")
		% listingId
	);

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR") 
				<< "DeleteListing query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return false;
	}

	return true;
}

std::vector<CashListing> CashExchangeDB::GetSellerListings(int sellerCharIndex)
{
	std::vector<CashListing> listings;

	std::string query = boost::str(
		boost::format("SELECT listing_id, seller_char_index, seller_name, cash_amount, "
					  "price_per_unit, total_price, created_at, active "
					  "FROM t_cash_exchange_listings "
					  "WHERE seller_char_index = %d "
					  "ORDER BY created_at DESC")
		% sellerCharIndex
	);

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR") 
				<< "GetSellerListings query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listings;
	}

	MYSQL_RES* result = mysql_store_result(&gserver->m_dbauth);
	if (!result)
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR") 
				<< "Failed to store result: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return listings;
	}

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		CashListing listing;
		listing.listingId = atoll(row[0]);
		listing.sellerCharIndex = atoi(row[1]);
		listing.sellerName = row[2];
		listing.cashAmount = atoll(row[3]);
		listing.pricePerUnit = atoll(row[4]);
		listing.totalPrice = atoll(row[5]);
		listing.createdAt = (time_t)atoll(row[6]);
		listing.active = atoi(row[7]);
		listings.push_back(listing);
	}

	mysql_free_result(result);
	return listings;
}

int CashExchangeDB::GetActiveListingCount()
{
	std::string query = "SELECT COUNT(*) as cnt FROM t_cash_exchange_listings WHERE active = 1";

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR") 
				<< "GetActiveListingCount query failed: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return 0;
	}

	MYSQL_RES* result = mysql_store_result(&gserver->m_dbauth);
	if (!result)
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR") 
				<< "Failed to store result: " << mysql_error(&gserver->m_dbauth) 
				<< end;
		return 0;
	}

	int count = 0;
	MYSQL_ROW row = mysql_fetch_row(result);
	if (row)
	{
		count = atoi(row[0]);
	}

	mysql_free_result(result);
	return count;
}

void CashExchangeDB::LogPurchase(int buyerCharIndex, const std::string& buyerName,
								  int sellerCharIndex, const std::string& sellerName,
								  long long cashAmount, long long pricePerUnit, long long totalNasPrice,
								  int listingID)
{
	// Log purchase to t_cash_exchange_listings (already done there)
	// Now log to buyer's purchase history

	std::string query = boost::str(
		boost::format(
			"INSERT INTO t_cash_exchange_purchases "
			"(buyer_char_index, buyer_name, seller_char_index, seller_name, cash_amount, price_per_unit, total_nas_price, listing_id, purchased_at) "
			"VALUES (%d, '%s', %d, '%s', %lld, %lld, %lld, %d, NOW())")
		% buyerCharIndex
		% buyerName
		% sellerCharIndex
		% sellerName
		% cashAmount
		% pricePerUnit
		% totalNasPrice
		% listingID
	);

	// Execute query via m_dbauth
	if (mysql_query(&gserver->m_dbauth, query.c_str()))
	{
		GAMELOG << init("CASHEXCHANGE DB ERROR - LogPurchase")
				<< "Failed to log purchase: " << mysql_error(&gserver->m_dbauth)
				<< end;
	}
	else
	{
		GAMELOG << init("CASHEXCHANGE DB - LogPurchase SUCCESS")
				<< "Logged purchase - Buyer: " << buyerName.c_str()
				<< " Seller: " << sellerName.c_str()
				<< " Amount: " << cashAmount
				<< end;
	}
}
