#ifndef __RANKINGSYSTEM_H__
#define __RANKINGSYSTEM_H__

#include "mysql.h"

class CRankingData
{
public:
	// ĳ���� ����
	int m_index;		// char index
	CLCString m_name;	// char name
	int m_level;		// char level
	int m_job;			// char job

	// ��ŷ ����
	int m_rank;			// ���� ��ŷ
	int m_rank_pre;		// ���� ��ŷ

	// �޼���
	int m_value;				// ���� �޼���
	int m_value_pre;			// ���� �޼���
	CLCString m_achieve_date;	// �޼� ��¥
};

class CRankingSystemEX
{
	class CRankerData
	{
		// ��Ŀ ��� ���� �� ���Ǵ� ������
	public:
		CRankerData()
			: m_char_index(0), m_rank(0), m_rank_pre(0), m_value(0), m_value_pre(0), m_level(0), m_job(0)
		{
		}
		~CRankerData() {};

		CRankerData& operator=(const CRankerData& other)
		{
			this->m_char_index = other.m_char_index;
			this->m_rank = other.m_rank;
			this->m_rank_pre = other.m_rank_pre;
			this->m_value = other.m_value;
			this->m_value_pre = other.m_value_pre;
			this->m_level = other.m_level;
			this->m_job = other.m_job;
			this->m_name = other.m_name;
			this->m_date = other.m_date;

			return *this;
		}
		CLCString m_name, m_date;
		int m_char_index;
		int m_rank;
		int m_rank_pre;
		int m_value;
		int m_value_pre;
		int m_level;
		int m_job;
	};
private:
	std::string		m_refreshDate;			/* ��ŷ ���� �ð� */
	bool m_lock;
	bool m_reward;	// �����ٰ� �ִ���? ( true : ������ ����Ұ� ����, false : ������ ����Ұ� ���� )

public:
	CRankingSystemEX();
	~CRankingSystemEX();

	MYSQL m_dbrank;
	bool TestConnectDB();
	bool ConnectDB();

	// ���� ����
	void StartRefresh(void);					// ��ŷ ���� ����
	bool RankingEX_Refresh(void);				// ����
	// ���� ����
	void RankingEX_GiveReward(int endTime);		// ���� ����
	// �ð� ����
	void CheckRankingRefreshTime(void);			// ��ŷ ���� �ð� Ȯ��
	// �� ����
	bool IsLock(void)
	{
		return m_lock;	   // ��ŷ �ý��� ��
	}
	void SetLock(bool b)
	{
		m_lock = b;		   // ��ŷ �ý��� ��
	}
	// ���� ���� ����
	bool IsExistReward(void)
	{
		return m_reward;	   // ���� ���� ( true : ������ ����Ұ� ����, false : ������ ����Ұ� ���� )
	}
	void SetExistReward(bool b)
	{
		m_reward = b;		   // ���� ���� ( true : ������ ����Ұ� ����, false : ������ ����Ұ� ���� )
	}
	// ����Ʈ ����
	void RankingEX_TOP50List(CNetMsg::SP& msg, CDescriptor* dest, int type, int subtype);	// Top50 ��Ŀ ����Ʈ ���
	void RankingEX_SearchList(CNetMsg::SP& msg, CDescriptor* dest, int type, int subtype);	// Search ��Ŀ ����Ʈ ��� (��Ŀ�� �˻��ϸ� �ش� ��Ŀ �Ʒ�,�� 5���� �� 11���� ����Ʈ�� �����ش�)
private:
	// Refresh ����
	bool RankingEX_BackUp(void);				// ���
	bool RankingEX_ClearRankingTable(void);		// ��ŷ ���̺� �ʱ�ȭ
	bool RankingEX_ClearCharTable(void);		// ĳ���� ���̺� ��ŷ ���� �ʵ� �ʱ�ȭ
	bool RankingEX_RefreshData(void);			// t_characters -> t_ranking_data
	bool RankingEX_RefreshRankByLevel(void);	// ��ŷ ����
	bool RankingEX_RefreshDate(void);			// ���� ��¥ ���
	std::string GetRefreshTime(void);				// ���� �ð� Ȯ��

	// ���� ����
	void RankingEX_GiveRewardByType(int type, int subtype, int endTime);	// ��Ŀ Ÿ�Կ� ���� ���� �����ϱ�
	int RankingEX_GetRewardTitle(int type, int subtype);					// ���� ������(ȣĪ) �ε��� ���

	void RankingEX_GiveRewardReborn(int endTime);
	void RankingEX_GiveRewardSummon(int endTime);
	void RankingEX_GiveRewardPvP(int endTime);

	void RankingEX_GiveTitle(int endTime, int title_index, CLCString sql);

	int RankingEX_ExistTitle(int title_index, int currentCharIndex);

	// ��Ÿ
	std::string GetPreviousRefreshDate(void);						// ���� ��ŷ ���� ��¥ ���
	int GetRankerCount(int type, int subtype);						// ��Ŀ�� �� �� ���
	int GetRankingByName(int type, int subtype, CLCString name);	// ĳ���� �̸����� ��ŷ ���
};

#endif // __RANKINGSYSTEM_H__
//
