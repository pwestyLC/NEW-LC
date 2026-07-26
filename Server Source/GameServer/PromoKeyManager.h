#ifndef PROMO_KEY_SYSTEM
#define PROMO_KEY_SYSTEM

struct SPromoKeyModel;

class CPromoKeyManager
{
public:
	CPromoKeyManager();
	~CPromoKeyManager();

	bool Load();

	void UsePromoKey(CPC* pc, const CLCString& key);

private:
	bool AddPromoKeyToUser(CPC* pc, SPromoKeyModel promo);
	SPromoKeyModel GetPromoKeyModel(CPC* pc, const std::string& key) const;

	std::vector<SPromoKeyModel> m_promoKeyList;
};

struct SPromoKeyModel
{
	int index;
	std::string key;
	int rewardIndex;
	int rewardCount;
	int dateEnd;
};

#endif

