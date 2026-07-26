#ifndef __PTYPE_CASH_EXCHANGE_H__
#define __PTYPE_CASH_EXCHANGE_H__

#include "ptype_base.h"

#pragma pack(push, 1)

namespace RequestClient
{
	struct doCashExchangeCreateListing : public pTypeBase
	{
		int charIndex;
		__int64 cashAmount;
		__int64 pricePerUnit;
	};

	struct doCashExchangeListRequest : public pTypeBase
	{
		int page;
	};

	struct doCashExchangeBuyListing : public pTypeBase
	{
		int listingID;
		__int64 cashAmount;
	};

	struct doCashExchangeCancelListing : public pTypeBase
	{
		int listingID;
	};
}

namespace UpdateClient
{
	struct doCashExchangeCreateListingResult : public pTypeBase
	{
		unsigned char success;				// 1 = success, 0 = fail
		unsigned char errorCode;			// error code if failed
		__int64 newCashBalance;				// updated cash balance after transaction
	};

	struct doCashExchangeBuyListingResult : public pTypeBase
	{
		unsigned char success;				// 1 = success, 0 = fail
		unsigned char errorCode;			// error code if failed
		__int64 newCashBalance;				// updated cash balance after transaction
	};

	struct doCashExchangeCancelListingResult : public pTypeBase
	{
		unsigned char success;				// 1 = success, 0 = fail
		unsigned char errorCode;			// error code if failed
		__int64 newCashBalance;				// updated cash balance after transaction
	};

	struct doCashExchangeListResponse : public pTypeBase
	{
		int listingCount;
		// followed by: listingCount * listing_data structures
	};
}

#pragma pack(pop)

#endif // __PTYPE_CASH_EXCHANGE_H__
