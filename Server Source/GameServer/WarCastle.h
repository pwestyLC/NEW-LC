#ifndef __WAR_CASTLE_H__
#define __WAR_CASTLE_H__

#define WAR_CASTLE_SUBNUMBER_DRATAN WAR_CASTLE_SUBNUMBER_MERAC

#define CHECK_SUBSERVER(castle)		if (!castle->CheckSubServer()) return

// ���� ����
#define WCSF_NORMAL			0		// �Ϲ�
#define WCSF_WAR_FIELD		1		// ����
#define WCSF_WAR_CASTLE		2		// ����

// ���� ���� ����
#define WCJF_NONE			0		// ������
#define WCJF_OWNER			1		// ���� ���
#define WCJF_DEFENSE_GUILD	2		// ���� ���
#define WCJF_DEFENSE_CHAR	3		// ������ �뺴
#define WCJF_ATTACK_GUILD	4		// ���� ���
#define WCJF_ATTACK_CHAR	5		// ������ �뺴

#define IS_DEFENSE_TEAM(joinflag)		( (joinflag == WCJF_OWNER || joinflag == WCJF_DEFENSE_GUILD || joinflag == WCJF_DEFENSE_CHAR) ? true : false )
#define IS_ATTACK_TEAM(joinflag)		( (joinflag == WCJF_ATTACK_GUILD || joinflag == WCJF_ATTACK_CHAR) ? true : false )

// �������� ������ ����ĥ �� �����Ǵ� ����Ʈ
#define WCFP_CASTLE_GUARD	5		// ��ȣ�� ������ �����Ǵ� ����Ʈ
#define WCFP_PLAYER			1		// �÷��̾� ������ �����Ǵ� ����Ʈ

// ���� �ʵ� ���� �ð� : �ʴ���
#define WCT_FIELD			(15 * 60)		// �ʵ��� ���� �ð� : ��
#define WCT_WAR				(60 * 60)		// �ʵ��� ���� ��ü ���� �ð� : ��

#define	APPLY_GUILD_GRADE_SKILL_TIME 10	// ��� ���� ���� ���� �ð� (��)

// ���� ���� ��� ����
#define WCGF_ATTACK_LEVEL	5
#define WCGF_DEFENSE_LEVEL	4
#define WCGF_CHAR_LEVEL		15
#define WCGF_ITEM			759
#define WCGF_MEMBERCOUNT	3
#define WCGF_MONEY			100000

// ���� ��û�� Ŭ����
class CWarCastleJoin
{
	friend class CWarCastle;

	int					m_index;
	char				m_bAttack;
	int					m_point;
	CWarCastleJoin*		m_prev;
	CWarCastleJoin*		m_next;

//	CWarCastleJoin(int index, char bAttack) { m_index = index; m_bAttack = bAttack; m_prev = m_next = NULL; m_point = 0; }

	void IncreasePoint(int val)
	{
		m_point += val;
	}

public:
	CWarCastleJoin(int index, char bAttack)
	{
		m_index = index;
		m_bAttack = bAttack;
		m_prev = m_next = NULL;
		m_point = 0;
	}

	int GetIndex()
	{
		return m_index;
	}
	char IsAttack()
	{
		return m_bAttack;
	}
	int GetPoint()
	{
		return m_point;
	}
	CWarCastleJoin* GetNext()
	{
		return m_next;
	}
	void SetPoint(int p)
	{
		m_point = p;
	}
	void SetPrev(CWarCastleJoin * n)
	{
		m_prev = n;
	}
	void SetNext(CWarCastleJoin * n)
	{
		m_next = n;
	}
};

// ���� Ŭ����
class CWarCastle
{
	// 
	friend void ProcHelperWarNoticeStart(CNetMsg::SP& msg);
	friend void ProcHelperWarNoticeStartAttackCastle(CNetMsg::SP& msg);
	friend void ProcHelperWarNoticeEnd(CNetMsg::SP& msg);

protected:
	int					m_state;							// ���� ����
	CNPC*				m_castleNPC;						// ���� ��û NPC
	CNPC*				m_lordSymbol;						// ����
	bool				m_bRegenShop;						// ���� ���� ����
	int					m_lastWarTime;						// ������ ���� �ð�
	int					m_nextWarTime;						// ���� ���� �ð�

	int					m_ownerGuildIndex;					// ���� ��� �ε���
	CLCString			m_ownerGuildName;					// ���� ��� �̸�
	int					m_ownerCharIndex;					// ���� ĳ���� �ε���
	CLCString			m_ownerCharName;					// ���� ĳ���� �̸�
	bool				m_bNoticeWarTime;					// ���� �ð��� �˷������ ����
	int					m_noticeRemain;						// ���� ���۱��� ���� �ð� �˸� �޽��� �÷���
	int					m_defensePoint;						// ������ ����Ʈ
	int					m_gateState;						// ���� ����
	bool				m_bGiveLordWeapon;					// ���� Į ���޿���
	bool				m_bMoveToRegen;						// 10���� ���� �̵� ����
	bool				m_bWarCastleReady;					// ������ ���� 1���� �غ����

	int					m_countAttackGuild;					// ���� ��� ��
	CWarCastleJoin*		m_defenseGuildList;					// ���� ��� ����Ʈ
	CWarCastleJoin*		m_attackGuildList;					// ���� ��� ����Ʈ
	CWarCastleJoin*		m_defenseCharList;					// ������ �뺴 ����Ʈ
	CWarCastleJoin*		m_attackCharList;					// ������ �뺴 ����Ʈ

	CWarCastleJoin*		m_top3guild[3];						// �ʵ� ���� �ֻ��� 3�� ���
	int*				m_posRegenPoint;					// �ش� ���� ������ �Ҵ�� ���� ��� �ε���
	int					m_nRegenPoint;						// posRegenPoint�� ����

	char				m_nSendInterval;					// �޼��� ������ ī��Ʈ : Hertbeat �� 1 �ʾ� ī��Ʈ

	int					m_oldOwnerCharIndex;				// ���� �����ϸ� �ٷ� ���� ������ �ε��� �����Ѵ�.

	int					m_guildGradeSkillTime;

public:

	CWarCastle();
	virtual ~CWarCastle();

	////////////////////
	// ���� ����
	// �ش� �� ���� ������ ����
	void SetNoticeWarTime(bool value)
	{
		m_bNoticeWarTime = value;
	}
	void SetNoticeRemain(int value)
	{
		m_noticeRemain = value;
	}

	virtual bool CheckSubServer();

	// ��� ���� Ŭ�������� �������̵� �� ��쿡�� �ݵ�� ȣ�� �ʿ���
	virtual bool LoadCastleData();

	// ���� ��ȯ
	int GetState()
	{
		return m_state;
	}

	// 공성 상태 변경
	void CheckWarCastle(bool forced_end_merac);

	// �ش� ������ ���� ��Ҹ� ��ȯ
	// ch�� NULL �ϼ� ����
	virtual int GetRegenPoint(int joinflag, CPC* ch) = 0;

	// �ش� �� ��ȣ�� ��ȯ
	virtual int GetZoneIndex() = 0;

	// ���� ���� ����
	int GetGateState(int mask = 0xffffffff)
	{
		return m_gateState & mask;
	}

	// ��ȣ�� ����� ���� ���� ����
	virtual void UpdateGateState(CNPC* npc) = 0;

	// ���� ��ȯ
	CNPC* GetLordSymbol()
	{
		return m_lordSymbol;
	}

	// �����ִ� ������ �ִ��� �˻�
	virtual bool IsOpenGate() = 0;

	// ���� HP ����
	int DecreaseLordSymbolHP();

	// ���������ȿ� �ִ��� �˻�
	bool IsInRegenPoint(CCharacter* ch, bool bAttack);

	// ������ �����ϴ� �簢�� ��ǥ ���ϱ�
	virtual void GetInnerCastleRect(char* nYlayer, int* nX0x2, int* nZ0x2, int* nX1x2, int* nZ1x2) = 0;

	// ���ȿ� �ִ��� �˻�
	bool IsInInnerCastle(CCharacter* pChar);

	// ���� ���� �������� �˻�
	virtual bool IsDefenseWarpPoint(int pos) = 0;

	// ��ȣž ��ü��
	virtual int GetGateNPCCount() = 0;

	// ��ȣž NPC ��ȯ
	virtual CNPC* GetGateNPC(int idx) = 0;

	// ���� ���� ����
	bool IsRegenShop()
	{
		return m_bRegenShop;
	}

	////////////////////
	// ���� �ð� ����

	// ���� ���� �ð� ����
	virtual void SetNextWarTime(int nextWarTime) = 0;
	virtual bool SetNextWarTime(int wday, int hour) = 0;

	// ���� ���� �ð� ���
	void GetNextWarTime(struct tm* nextWarTime, bool bHumanable);
	int GetNextWarTime()
	{
		return m_nextWarTime;
	}

	// ����/���� �뺴/��� ��û ���� �ð� �˻�
	virtual bool IsJoinTime() = 0;

	// ���� ���� ��û ���� �ð� ���ϱ�
	virtual void GetJoinTime(struct tm* joinTime, bool bHumanable) = 0;

	// ����� ������� ���� �ð� ���ϱ�
	int GetRemainWarTime();

	////////////////////
	// ���� ���� ����

	// ���� ���� ���ϱ�
	int GetOwnerGuildIndex()
	{
		return m_ownerGuildIndex;
	}
	const char* GetOwnerGuildName()
	{
		return (const char*)m_ownerGuildName;
	}
	int GetOwnerCharIndex()
	{
		return m_ownerCharIndex;
	}
	const char* GetOwnerCharName()
	{
		return (const char*)m_ownerCharName;
	}

	bool UpdateNextWarTime();
	
	// ���� �뺴 �߰�
	bool AddDefenseChar(int index);

	// ���� ��� �߰�
	bool AddDefenseGuild(int index);

	// ���� �뺴 �߰�
	bool AddAttackChar(int index);

	// ���� ��� �߰�
	bool AddAttackGuild(int index);

	// ���� �뺴 ����
	void RemoveDefenseChar(int index);

	// ���� ��� ����
	void RemoveDefenseGuild(int index);

	// ���� �뺴 ����
	void RemoveAttackChar(int index);

	// ���� ��� ����
	void RemoveAttackGuild(int index);

	// ���� ������� �˻�
	bool IsAttackGuild(int index);

	// ���� �뺴���� �˻�
	bool IsAttackChar(int index);

	// ���� ������� �˻�
	bool IsDefenseGuild(int index);

	// ���� �뺴���� �˻�
	bool IsDefenseChar(int index);

	// ������ ��� ��
	int GetCountAttackGuild()
	{
		return m_countAttackGuild;
	}

	// �ֻ��� ������� ���� ���
	void GetTop3AttackGuild(int guildindex[3], char guildname[3][MAX_GUILD_NAME_LENGTH + 1], int guildpoint[3]);

	// Top3 ����� �ϳ����� �˻�
	bool IsTop3Guild(int guildindex);

	bool IsWarCastleReady()
	{
		return m_bWarCastleReady;
	}

	////////////////////
	// ����Ʈ ����

	// �� ������ ���
	// guildindex�� 0�̸� ������, �׿ܴ� ���� ���
	int GetTeamPoint(int guildindex);

	// �� ���� ����
	// guildindex�� 0�̸� ������, �׿ܴ� ���� ���
	// ���� ���� ��ȯ
	int IncreaseTeamPoint(int guildindex, int val);

	// Ư�� ��� ����Ʈ ���ϱ�
	// ���������� ų����Ʈ
	// ���������� ���� ����Ʈ
	// ��� ������ ���ų�, ������ ���� ����Ʈ ��û�� �߸��� ��û������ -1
	int GetGuildPoint(int guildindex);

	///////////////////
	// ���� ������ ����

	// ���� ������ ����
	virtual bool GiveLordItem(CPC* pc) = 0;

	// ���� ������ ȸ��
	virtual bool TakeLordItem(CPC* pc) = 0;

	// ���� ������ �ε��� ���ϱ�
	virtual int GetLordItemIndex(char job1, char job2) = 0;

	// ���� ���� �� ���� �������� ���� ���� ���� ���Ƴ���
	void GetOutNonDefense();

	void SendCastleState( int zoneindex );	// ����Ʈ ���� ����

	void GuildGradeSkillAll( bool bApply);
	void ApplyGuildGradeSkillAll( )
	{
		GuildGradeSkillAll( true );
	}
	void CureGuildGradeSkillAll( )
	{
		GuildGradeSkillAll( false );
	}

#ifdef WARCASTLE_STATE_CHANNEL_CYNC
	void SetStateChannelCync( int state )
	{
		SetState( state);
	}
#endif

protected:

	////////////////////
	// ���� ���� ����

	// ���� ���� �˸�
	void CheckWarCastleNotice();

	// ���� ����
	void CheckWarCastleStartWar();

	// ���� ����
	void CheckWarCastleStartWarCastle();

	// ���� �� ó��
	void CheckWarCastleEnd(bool forced_end_merac);

	// ���� ���� ����
	void SetState(int state)
	{
		m_state = state;
	}

	////////////////////
	// ���� ���� ����

	// ������ �̷�� ���� Area�� �����´�
	CArea* GetArea();

	// ���� �������� ���� ����
	void MoveToRegenPoint();

	// ���� ��ġ �ʱ�ȭ
	virtual void InitRegenPosition() = 0;

	////////////////////
	// MPC ����

	// ���� NPC�� ���� ��Ų��
	void RegenCastleNPC();

	// ������ ����
	void RegenGuardNPC();

	// ��ȣž ����
	void RegenCastleTower();

	// ���� ����
	void RegenLordSymbol();

	// ��������Ʈ ����
	void RegenWarpNPC();

	// ���� ����/����
	void RegenShop();

	// ���� NPC�� �����Ѵ�
	void RemoveCastleNPC();

	// ��ȣ���� �����Ѵ�
	void RemoveGuardNPC();

	// ��ȣž ����
	void RemoveCastleTower();

	// ���� ����
	void RemoveLordSymbol();

	// ��������Ʈ ����
	void RemoveWarpNPC();

	// ��ȣž�� ��������� ����
	virtual void SetGateNPC(CNPC* npc) = 0;

	// �������� �ʱ�ȭ
	virtual void InitGateNPC() = 0;

	// m_state�� ���� ���� NPC�� �����ϰų� ���ش�
	void CheckWarCastleNPC();

	////////////////////
	// ������ ����

	// �ʵ� ���� �ֻ��� 3�� ��� ���ϱ�
	void GetTop3AttackGuild();

	// ���� ���� ã��
	CWarCastleJoin* FindAttackGuild(int index);
	CWarCastleJoin* FindAttackChar(int index);
	CWarCastleJoin* FindDefenseGuild(int index);
	CWarCastleJoin* FindDefenseChar(int index);

	// ������ ���� �ʱ�ȭ
	void ResetJoinFlag();

	// ���� ����Ʈ �ʱ�ȭ
	void RemoveAllJoinList();

	// �� ������ ���� �ʱ�ȭ
	void ResetOwner();

public:

	// ���� ������ �˻�, WCJF_XXX ��ȯ
	int CheckJoin(CPC* ch);

	// �� ������ ����
	void SetOwner(CGuild* guild);

	////////////////////
	// static �Լ���

	// �ش� ���� ���� ������ ��ȯ
	static CWarCastle* GetCastleObject(int zoneindex);

	// ����� ���� ���������� �˻�
	static void CheckJoinAll(CPC* ch);

	// ���� �� ��ȯ
	// ȣ���� ������ delete [] �� �ؾ���
	// ���� ���� ������ NULL ��ȯ
	// ���� ���� ������ count�� �� ���� ����
	static int* GetOwnCastle(int guildindex, int* count);

	// ��� ������ �ش� ������ ���� ������ �ݿ�
	static void DeleteGuild(int guildindex);

	// �ش� PC�� ���� ������ ����� �� �ִ��� ����
	static bool CanLordChat(CPC* pc);

	// ���� ���꼭���� �������� �ε��� ���, ������ -1
	static int GetCurSubServerCastleZoneIndex();
	void SetOldOwnerChar(int ownerIndex)
	{
		m_oldOwnerCharIndex = ownerIndex;
	}
	int  GetOldOwnerChar()
	{
		return m_oldOwnerCharIndex;
	}

	virtual int GetWarTime() = 0;

	int		GetGuildGradeSkillTime()
	{
		return m_guildGradeSkillTime;
	}
	void	SetGuildGradeSkillTime(int currenttime)
	{
		m_guildGradeSkillTime = currenttime;
	}

	void endWarCastleMerac()
	{
		CheckWarCastleEnd(true);
	}

	void EndWarRegenPoint();
};

// �޶�ũ ���� Ŭ����
class CMeracCastle : public CWarCastle
{
	enum { COUNT_MERAC_GATE_NPC = 6 };

	CNPC*		m_gateNPC[COUNT_MERAC_GATE_NPC];		// ���� ��Ű�� ��ȣ��

public:
	CMeracCastle();
#ifdef WARCASTLE_SUBNUMBER_MEMBER_VALUE
	int					m_subNumber;						// �������� �ϴ� ä�� �ѹ�
#endif // WARCASTLE_SUBNUMBER_MEMBER_VALUE

// virtual function ����
protected:
	void SetGateNPC(CNPC* npc);
	void InitGateNPC();
	void InitRegenPosition();

public:
	int GetZoneIndex()
	{
		return ZONE_MERAC;
	}
	void SetNextWarTime(int nextWarTime);
	bool SetNextWarTime(int wday, int hour);
	bool IsJoinTime();
	void GetJoinTime(struct tm* nextJoinTime, bool bHumanable);
	int GetRegenPoint(int joinflag, CPC* ch);
	void UpdateGateState(CNPC* npc);
	bool IsOpenGate();
	bool GiveLordItem(CPC* pc);
	bool TakeLordItem(CPC* pc);
	int GetLordItemIndex(char job1, char job2);
	bool IsDefenseWarpPoint(int pos);
	int GetGateNPCCount()
	{
		return (GetGateNPC(0) == NULL) ? 0 : COUNT_MERAC_GATE_NPC;
	}
	CNPC* GetGateNPC(int idx)
	{
		return (idx < 0 || idx >= COUNT_MERAC_GATE_NPC) ? NULL : m_gateNPC[idx];
	}
	void GetInnerCastleRect(char* nYlayer, int* nX0x2, int* nZ0x2, int* nX1x2, int* nZ1x2);
// --- virtual function ����
	int GetWarTime()
	{
		return WCT_WAR;
	}
};

void CheckWarCastle();
bool LoadCastleData();
bool IsValidGuildCommandWithWarCastle(CPC* ch, unsigned char subtype);

extern CMeracCastle meracCastle;

#endif // __WAR_CASTLE_H__
//
