#ifndef __JUMPING_SYSTEM_H__
#define __JUMPING_SYSTEM_H__

class CJumpingSystem
{
public:
	CJumpingSystem(CPC* _ch, int _itemIndex);
	~CJumpingSystem(void);

	// ������ �� �ִ���, �������� ���޹��� �� �ִ��� ���� �˻�
	bool check(void);

	// ����
	bool jump(void);
	bool UnwearItems();
	
	bool learnSkill();
	
private:
	// ĳ���� �ʱ�ȭ
	bool initCharacter(void);

	// ���� �ʱ�ȭ
	bool initJob(void);

	// ��ų �ʱ�ȭ
	bool initSkill(void);

	// ���� �ʱ�ȭ
	bool initStat(void);

	// ���� ����
	bool giveReward(void);

private:
	CPC* m_pc;					// ���� ĳ����
	const int m_itemIndex;		// ���ο� ����� ������ �ε���
	int m_jumpingLevel;			// ���� ����
	int m_rewardIndex;			// ���� ���̺� �ε���
};


#endif
