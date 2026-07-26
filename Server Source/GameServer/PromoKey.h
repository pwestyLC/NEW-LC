#ifdef PROMO_KEY_03312023
#ifndef _PROMO_KEY_HEADER_
#define _PROMO_KEY_HEADER_

#include <vector>

typedef struct _Promo_Keys {
	int keyIdx;
	char key;
	int keyUseRemain;
	int keyExpireDate;
} PromoKey;

typedef struct _Promo_Key_Reward {
	int keyIdx;
	int itemIndex[5];
	int itemCount[5];
} PromoKeyReward;

typedef struct _Promo_Key_Use {
	int keyIdx;
	int userId;
	int charId;
	CLCString charName;
	int useTime;
} PromoKeyUse;

//#ifdef PROMO_KEY_03312023

class cPromoKey {
public:
	cPromoKey();
	~cPromoKey();
	bool LoadPromo(); // loading the promo table as well 
	bool LoadReward(); //loading the rewards for the promo
	void AddPromoKeyUseToDB(int keyIdx, int userId, int charId, CLCString charName);
	int GetKeyIndex(char key);
	bool HasCharacterUsedKey(char key, int charIdx);
	bool RedeemPromoCheck(); //checking if they already redeemed the promo
	bool HasValidKey(char key);
	int  GetRewardPromoCount(int keyIdx);
	void SendRewardInventory(CPC* ch, int keyIdx);//first we checked the reward conditons next we'll send accordingly to inventory or statue check reward space
	void SendRewardMail(CPC* ch, int keyIdx);//first we checked the reward conditons next we'll send accordingly to inventory or statue check reward space

private:
	std::vector<PromoKey> promoKeys;
	std::vector<PromoKeyReward> promoKeyRewards;
	std::vector<PromoKeyUse> promoKeyUses;

};
//#endif

#endif
#endif