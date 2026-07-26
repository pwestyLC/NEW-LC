#ifndef _CJEWELDATA_H_
#define _CJEWELDATA_H_

#include <map>

class CJewelData
{
public:
	CJewelData();
	virtual ~CJewelData();
	friend class CJewelDataList;

private:
	int m_jewelGrade;
	GoldType_t m_normalComposeMoney;
	GoldType_t m_chaosComposeMoney;
	int m_normalComposeProb;
	int m_chaosComposeProb;
	int m_composeNormalToChaosProb;
	int m_normal_plus2_prob;
	int m_normal_plus3_prob;
	int m_chaos_plus2_prob;
	int m_chaos_plus3_prob;
	int m_normal_minus1_prob;
	int m_normal_minus2_prob;
	int m_normal_minus3_prob;
	int m_chaos_minus1_prob;
	int m_chaos_minus2_prob;
	int m_chaos_minus3_prob;
	int m_eventComposeProb;					//���� �ռ� �̺�Ʈ Ȯ�� ��
	int m_eventChaosCreateProb;				//ī���� ���� ���� �̺�Ʈ Ȯ�� ��
	int m_eventUpgradeProb;					//���� ��޻�� �̺�Ʈ Ȯ�� ��
	int m_eventCombineProb;					//���� ���� �̺�Ʈ Ȯ�� ��
	int m_eventCollectProb;					//���� ���� ���н� �̺�Ʈ ȸ�� Ȯ�� ���� ��

public:
	void setEventComposeProb( int composeProb )
	{
		m_eventComposeProb = composeProb;
	}
	void setEventChaosCreateProb( int createProb )
	{
		m_eventChaosCreateProb = createProb;
	}
	void setEventUpgradePorb( int upgradeProb )
	{
		m_eventUpgradeProb = upgradeProb;
	}
	void setEventCombineProb( int combineProb )
	{
		m_eventCombineProb = combineProb;
	}
	void setEventCollectProb( int collectPorb )
	{
		m_eventCollectProb = collectPorb;
	}

	int getJewelGrade()
	{
		return m_jewelGrade;
	}
	int getNormalComposeMoney()
	{
		return m_normalComposeMoney;
	}
	int getChaosComposeMoney()
	{
		return m_chaosComposeMoney;
	}
	int getNormalComposeProb()
	{
		return m_normalComposeProb;
	}
	int getChaosComposeProb()
	{
		return m_chaosComposeProb;
	}
	int getComposeNormalToChaosProb()
	{
		return m_composeNormalToChaosProb;
	}
	int getNormalPlus2Prob()
	{
		return m_normal_plus2_prob;
	}
	int getNormalPlus3Prob()
	{
		return m_normal_plus3_prob;
	}
	int getChaosPlus2Prob()
	{
		return m_chaos_plus2_prob;
	}
	int getChaosPlus3Prob()
	{
		return m_chaos_plus3_prob;
	}
	int getNormalMinus1Prob()
	{
		return m_normal_minus1_prob;
	}
	int getNormalMinus2Prob()
	{
		return m_normal_minus2_prob;
	}
	int getNormalMinus3Prob()
	{
		return m_normal_minus3_prob;
	}
	int getChaosMinus1Prob()
	{
		return m_chaos_minus1_prob;
	}
	int getChaosMinus2Prob()
	{
		return m_chaos_minus2_prob;
	}
	int getChaosMinus3Prob()
	{
		return m_chaos_minus3_prob;
	}
	int getEventComposeProb()
	{
		return m_eventComposeProb;
	}
	int getEventCreateChaosProb()
	{
		return m_eventChaosCreateProb;
	}
	int getEventUpgradeProb()
	{
		return m_eventUpgradeProb;
	}
	int getEventCombineProb()
	{
		return m_eventCombineProb;
	}
	int getEventCollectProb()
	{
		return m_eventCollectProb;
	}
};

class CJewelDataList
{
public:
	typedef std::map<int, CJewelData*> map_t;

	map_t m_jewelDataList;			//���� ������ ����Ʈ (key : ���� ���)
	CJewelData* m_jewelData;		//���� ������
	//int m_nCount;
	int **m_gradedJewel;			//��޺� ���� ����
	int **m_gradedChaosJewel;		//��޺� ī���� ���� ����
	int m_nJewelItemKindCount;		//���� ���� ����
	int m_nJewelItemKindCount_Chaos; //ī���� ���� ���� ����
	int m_JewelPocketItem[JEWEL_POCKET_MAX_LEVEL];
	int m_ChaosJewelPocketItem[JEWEL_POCKET_MAX_LEVEL];

	int m_composeProb;
	int m_chaosCreateProb;
	int m_upgradeProb;
	int m_combineProb;
	int m_collectProb;

public:
	CJewelDataList();
	virtual ~CJewelDataList();

	bool Load();
	bool LoadProb();
	CJewelData* FindGrade(int grade);
	int FindJewelPocketIndex(int grade);
	int FindChaosJewelPocketIndex(int grade);

	int getRandomJewel(int grade, int rand);
	int getRandomChaosJewel(int grade, int rand);
};
#endif //_CJEWELDATA_H_
