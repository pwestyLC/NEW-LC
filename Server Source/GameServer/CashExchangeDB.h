#ifndef __CASH_EXCHANGE_DB_H__
#define __CASH_EXCHANGE_DB_H__

#include <string>
#include <vector>

struct CashListing
{
	long long listingId;
	int sellerCharIndex;
	std::string sellerName;
	long long cashAmount;
	long long pricePerUnit;
	long long totalPrice;
	int active;
	time_t createdAt;
	int buyerCharIndex;
	std::string buyerName;
};

class CashExchangeDB
{
public:
	static CashExchangeDB& instance()
	{
		static CashExchangeDB __instance;
		return __instance;
	}

	// Create a new listing in database
	// Returns listing_id on success, -1 on failure
	long long CreateListing(int sellerCharIndex, const std::string& sellerName, 
							long long cashAmount, long long pricePerUnit);

	// Get all active listings with pagination
	// Returns vector of listings for given page
	std::vector<CashListing> GetActiveListings(int page, int pageSize = 20);

	// Get listing by ID
	CashListing GetListing(long long listingId);

	// Mark listing as bought
	bool MarkListingBought(long long listingId, int buyerCharIndex, const std::string& buyerName);

	// Handle partial buy - reduce cash_amount and optionally mark as bought if empty
	bool ReduceListingCash(long long listingId, long long amountBought, int buyerCharIndex, const std::string& buyerName);

	// Cancel listing (seller removes their listing)
	bool CancelListing(long long listingId);

	// Delete listing
	bool DeleteListing(long long listingId);

	// Get listings by seller
	std::vector<CashListing> GetSellerListings(int sellerCharIndex);

	// Get total count of active listings
	int GetActiveListingCount();

	// Log purchase to buyer's purchase history
	void LogPurchase(int buyerCharIndex, const std::string& buyerName,
					 int sellerCharIndex, const std::string& sellerName,
					 long long cashAmount, long long pricePerUnit, long long totalNasPrice,
					 int listingID);

private:
	CashExchangeDB() {}
	~CashExchangeDB() {}
	CashExchangeDB(const CashExchangeDB&);
	CashExchangeDB& operator=(const CashExchangeDB&);
};

#endif // __CASH_EXCHANGE_DB_H__
