#ifndef __GUILD_H__
#define __GUILD_H__

#define GUILD_MAX_OFFICER			2
#define GUILD_MAX_MEMBER			200
#define GUILD_MAX_GUILD_LEVEL		50

#define GUILD_REG_DELAY				2

#define GUILD_LEVEL1_MAX_MEMBER		10
#define GUILD_LEVEL1_NEED_LEVEL		10
#define GUILD_LEVEL1_NEED_SP		10
#define GUILD_LEVEL1_NEED_MONEY		10000

#define GUILD_LEVEL2_MAX_MEMBER		15
#define GUILD_LEVEL2_NEED_LEVEL		15
#define GUILD_LEVEL2_NEED_SP		30
#define GUILD_LEVEL2_NEED_MONEY		50000

#define GUILD_LEVEL3_MAX_MEMBER		20
#define GUILD_LEVEL3_NEED_LEVEL		20
#define GUILD_LEVEL3_NEED_SP		60
#define GUILD_LEVEL3_NEED_MONEY		250000

#define GUILD_LEVEL4_MAX_MEMBER		25
#define GUILD_LEVEL4_NEED_LEVEL		25
#define GUILD_LEVEL4_NEED_SP		120
#define GUILD_LEVEL4_NEED_MONEY		500000

#define GUILD_LEVEL5_MAX_MEMBER		30
#define GUILD_LEVEL5_NEED_LEVEL		30
#define GUILD_LEVEL5_NEED_SP		240
#define GUILD_LEVEL5_NEED_MONEY		1000000

#define GUILD_LEVEL6_MAX_MEMBER		30
#define GUILD_LEVEL6_NEED_LEVEL		30
#define GUILD_LEVEL6_NEED_SP		500
#define GUILD_LEVEL6_NEED_MONEY		2000000

#define GUILD_LEVEL7_NEED_LEVEL		30
#define GUILD_LEVEL7_NEED_SP		550
#define GUILD_LEVEL7_NEED_GP		18000
#define GUILD_LEVEL7_NEED_MONEY		2500000

#define GUILD_EXTEND_BASE_LEVEL			7			// ���� Ȯ�� �� ��ȭ�Ǵ� ������ �⺻��
#define GUILD_POSITION_NAME		12
#define GUILD_NOTICE_TITLE_MAX	64
#define GUILD_NOTICE_TEXT_MAX	1024

#define GUILD_INCLINE_GENERAL		0		// �Ϲ� ���
#define GUILD_INCLINE_CHAO			1		// ī�� ���
#define GUILD_INCLINE_HUNTER		2		// ���� ���

#define GUILD_BATTLE_MIN_MEMBER		10

#define GUILD_BATTLE_MIN_PRIZE		100000

#if defined(LC_GAMIGO)
#define GUILD_BATTLE_MAX_PRIZE		10000000
#else
#define GUILD_BATTLE_MAX_PRIZE		1000000
#endif

#define GUILD_BATTLE_MIN_TIME		6000		// �ּ� 10��
#define GUILD_BATTLE_MAX_TIME		180000		// �ִ� 300��

#define GUILD_BATTLE_WAIT_TIME		600		// 1��

#define GUILD_BATTLE_STATE_PEACE		-1		// ��ȭ ����
#define GUILD_BATTLE_STATE_START_WAIT	0		// ����� ��û ��
#define	GUILD_BATTLE_STATE_WAIT			1		// ����� ���
#define	GUILD_BATTLE_STATE_ING			2		// ����� ����
#define GUILD_BATTLE_STATE_STOP_WAIT	3		// ����� �ߴ� ��û ��
#define	GUILD_BATTLE_STATE_PRIZE		4		// ����� �� ��� ��� ���

#define MANAGE_NEED_LEVEL				5

#define MAX_GUILD_CREATE			30 //new24052022

// ??? ?n??
typedef struct __tagGuildSignal
{
	MSG_GUILD_POSITION_TYPE		flag;
	int							senderIndex;
	float						x;
	float						z;
} GUILD_SIGNAL;

#include "GuildKick.h"

class CGuild;

class CGuildMember
{
	friend class CGuild;

	int				m_charindex;
	CLCString		m_name;
	//CLCString		m_nick;
	int				m_pos;
	CGuild*			m_guild;
	int				m_listindex;
	char			m_online;

	CPC*			m_pc;

	int				m_contributeExp_min;
	int				m_contributeExp_max;
	int				m_contributeFame_min;
	int				m_contributeFame_max;

	int				m_contributeExp;	// ����ġ���� ��� ����Ʈ�� �⿩�� %
	int				m_contributeFame;	// ����ġ���� ��� ����Ʈ�� �⿩�� %
	LONGLONG				m_cumulatePoint;	// RomeoST ADjust
	CLCString		m_positionName;
	int				m_channel;			// ���� ������ ä��
	int				m_zoneindex;			// ���� ������ ��ġ

	CGuildMember();

public:
	~CGuildMember();

	int charindex()
	{
		return m_charindex;
	}
	void charindex(int index)
	{
		m_charindex = index;
	}

	const char* GetName()
	{
		//member nick�κ� ���� : bw 060403
		//if(strcmp((const char*) m_nick, "") != 0)
		//	return (const char*)m_nick;
		return (const char*) m_name;
	}
//	const char* nick() { return (const char*)m_nick; }
	void name(const char* str)
	{
		if (str) m_name = str;
		else m_name = "";
	}
//	void nick(const char* str) { if (str) m_nick = str; else m_nick = ""; }

	MSG_GUILD_POSITION_TYPE pos()
	{
		return (MSG_GUILD_POSITION_TYPE)m_pos;
	}
	void pos(int p)
	{
		m_pos = p;
	}

	CGuild* guild()
	{
		return m_guild;
	}
	void guild(CGuild* g)
	{
		m_guild = g;
	}

	int listindex()
	{
		return m_listindex;
	}

	char online()
	{
		return m_online;
	}
	void online(char val)
	{
		m_online = val;
	}

	char GetGuildMark();

	void contributeExp( int contribute )
	{
		m_contributeExp = contribute;
	}
	void contributeFame( int contribute )
	{
		m_contributeFame = contribute;
	}
	void cumulatePoint(LONGLONG point )
	{
		m_cumulatePoint = point;
	}
	void AddCumulatePoint(LONGLONG point )
	{
		m_cumulatePoint += point;
	}
	//void positionName( const char* str ) { if( str ) m_positionName = str; else m_positionName = ""; }
	void positionName( CLCString& str )
	{
		m_positionName = "";
		if( str.Length() > 0 )
			m_positionName = str;
	}

	void channel( int channel )
	{
		m_channel = channel;
	}
	void zoneindex( int zoneNum )
	{
		m_zoneindex = zoneNum;
	}

	int	GetcontributeExp( )
	{
		return m_contributeExp;
	}
	int GetcontributeFame()
	{
		return m_contributeFame;
	}
	LONGLONG GetcumulatePoint()
	{
		return m_cumulatePoint;
	}
	const char* GetPositionName( )
	{
		return m_positionName;
	}

	int	GetChannel()
	{
		return m_channel;
	}
	int GetZoneNum()
	{
		return m_zoneindex;
	}

	void SetContributeExp_min(int value)
	{
		m_contributeExp_min = value;
	}
	void SetContributeExp_max(int value)
	{
		m_contributeExp_max = value;
	}
	int GetcontributeExp_min()
	{
		return m_contributeExp_min;
	}
	int GetcontributeExp_max()
	{
		return m_contributeExp_max;
	}

	void SetContributeFame_min(int value)
	{
		m_contributeFame_min = value;
	}
	void SetContributeFame_max(int value)
	{
		m_contributeFame_max = value;
	}
	int GetcontributeFame_min()
	{
		return m_contributeFame_min;
	}
	int GetcontributeFame_max()
	{
		return m_contributeFame_max;
	}

	void SetPC(CPC* pc)
	{
		if (guild() == NULL)
		{
			m_pc = NULL;
			if (pc)
				pc->m_guildInfo = NULL;
			return ;
		}
		if (m_pc && pc == NULL)
			m_pc->m_guildInfo = NULL;
		m_pc = pc;
		if (pc)
			pc->m_guildInfo = this;
	}
	CPC* GetPC()
	{
		return m_pc;
	}

private:
	void listindex(int idx)
	{
		m_listindex = idx;
	}
};

class CGuild
{
	int				m_index;
	CLCString		m_name;
	int				m_level;
	CGuildMember*	m_boss;
	CGuildMember*	m_officer[GUILD_MAX_OFFICER];

	int				m_membercount;

	CGuild*			m_next;
	CGuild*			m_prev;

	// ����� -------------------
	int				m_battleIndex;
	int				m_battlePrize_nas;
	int				m_battleZone;
	int				m_battleTime;
	int				m_killCount;
	char			m_battleState;
	int				m_battlePulse;
	// ---------------------------

	GUILD_SIGNAL	m_guildSignal;

	int				m_landcount;
	int				m_land[256];					// ������
	LONGLONG		m_GuildPoint;			// ��ü ��� ����Ʈ
	char			m_incline;				// ��� ���� -> ī������ �������� ����
	int				m_maxmember;
	int				m_GuildPointRanking;		// ��� ����Ʈ ��ŷ
	// ��� ��ũ ���� �߰�;
	// ��� ��ų
	////////////
	// ��ų ����
public:
	int				m_create_date;			//��� ������
	CGuildMember*	m_member[GUILD_MAX_MEMBER];
	CSkillList	m_passiveSkillList;			// ��� ��ų ����Ʈ
	CSkillList	m_activeSkillList;
	CSkillList	m_etcSkillList;
	CSkill* FindSkill(int index);
	void clearReadySkill();

	bool m_bRebirthPos;	// ��Ȱ ������ �Ծ����� üũ �ϴ� �κ�

public:
	CGuild(int guildindex, const char* name, int level, int battleIndex = -1, int battlePrize = 0, int battleTime = 0, int batttleZone = -1, int battleKillCount = 0, int battleState = -1);
	~CGuild();

	CPC* GetNearMember(CCharacter* pPC, int nListIndex);

	void landcount( int landcount )
	{
		m_landcount = landcount;
	}
	void land( int count, int* land )
	{
		if( count != 0 )
		{
			for( int i = 0; i < count; i++ )
				m_land[i] = land[i];
		}
	}
	void guildPoint(LONGLONG guildPoint )
	{
		m_GuildPoint = guildPoint;
	}
	void incline( char incline )
	{
		m_incline = incline;
	}
	void AddGuildPoint(LONGLONG GuildPoint );

	int GetLandCount( )
	{
		return m_landcount;
	}
	int* GetLand()
	{
		return m_land;
	}
	LONGLONG GetGuildPoint()
	{
		return m_GuildPoint;
	}
	char GetIncline()
	{
		return m_incline;
	}
	void guildPointRanking( int nRanking )
	{
		m_GuildPointRanking = nRanking;
	}
	int	GetGuildPointRanking( )
	{
		return m_GuildPointRanking;
	}

	bool IsRebrithPos( )
	{
		return m_bRebirthPos;
	}
	void SetRerithPos( bool bUse )
	{
		m_bRebirthPos = bUse;
	}

	int index()
	{
		return m_index;
	}

	void	changeName(const char* name)
	{
		m_name = name;
	}

	const char* name()
	{
		return (const char*)m_name;
	}

	int level()
	{
		return m_level;
	}
	void level(int n)
	{
		m_level = n;
	}

	void LevelUp()
	{
		if (m_level < GUILD_MAX_GUILD_LEVEL) m_level++;
	}

	CGuildMember* boss()
	{
		return m_boss;
	}

	CGuildMember* officer(int idx)
	{
		return (idx < 0 || idx >= GUILD_MAX_OFFICER) ? NULL : m_officer[idx];
	}

	CGuild* nextguild()
	{
		return m_next;
	}
	void nextguild(CGuild* g)
	{
		m_next = g;
	}

	CGuild* prevguild()
	{
		return m_prev;
	}
	void prevguild(CGuild* g)
	{
		m_prev = g;
	}

	int membercount()
	{
		return m_membercount;
	}

	CGuildMember* member(int idx)
	{
		return (idx < 0 || idx >= GUILD_MAX_MEMBER) ? NULL : m_member[idx];
	}

	// ����� �߰�

	int battleIndex()
	{
		return m_battleIndex;
	}

	int battlePrizeNas()
	{
		return m_battlePrize_nas;
	}

	int battleZone()
	{
		return m_battleZone;
	}

	void BattleSet (int index, int nas, int zone_index)
	{
		m_battleIndex = index;
		m_battlePrize_nas = nas;
		m_battleZone = zone_index;
	}

	int battlePulse()
	{
		return m_battlePulse;
	}
	void BattlePulse(int p)
	{
		m_battlePulse = p;
	}

	int battleTime()
	{
		return m_battleTime;
	}
	void BattleTime(int t)
	{
		m_battleTime = t;
	}

	int killCount()
	{
		return m_killCount;
	}
	void KillCount(int c)
	{
		m_killCount = c;
	}

	char battleState()
	{
		return m_battleState;
	}
	void BattleState(char s)
	{
		m_battleState = s;
	}
	//---------------------------


	GUILD_SIGNAL* guildSignal()
	{
		return &m_guildSignal;
	}
	void guildSignal(MSG_GUILD_POSITION_TYPE flag, int senderIndex, float x, float z)
	{
		m_guildSignal.flag = flag;
		m_guildSignal.senderIndex = senderIndex;
		m_guildSignal.x = x;
		m_guildSignal.z = z;
	}

	int maxmember();
	void setMaxmember( int maxmember )
	{
		m_maxmember = maxmember;
	};

	////////////////////
	// Function name	: addmember
	// Description	    : ��� �߰�,
	// Return type		: int
	//                  : ����: �߰��� ����� ����Ʈ �ε���, ����: -1
	int addmember(int charindex, const char* name);

	void removemember(CGuildMember* delmember);

	////////////////////
	// Function name	: changeboss
	// Description	    : ����� ����
	// Return type		: CGuildMember*
	//                  : ���� ���� ����� ��� ������
	CGuildMember* changeboss(int newbosslistindex);

	void appoint(int listindex);

	void fire(int listindex);

	////////////////////
	// Function name	: findmember
	// Description	    : ������ ã�´�.
	CGuildMember* findmember(int charindex);

	CGuildMember* findmember(const char* charname);

	// bCell�� true�̸� ���� ������ ���� ��� dis, appear �޼����� ������.
	void SendToAll(CNetMsg::SP& msg, bool bCell = false);
	void SendToAllInSameZone(CNetMsg::SP& msg, int zoneindex);
	void SendToAllStatusMsg();

#ifdef GMTOOL
	bool m_bGmtarget;
#endif // GMTOOL

#ifdef EXTREME_CUBE
	int	m_cubeUniqueIdx;
#endif // EXTREME_CUBE

#ifdef LC_GAMIGO
	int BossChangeNeedPCLevel();
#endif // LC_GAMIGO

	int				m_nCountRushCaptain;
	int				m_nCountSupportCaptain;
	int				m_nCountReconCaptain;
	int				m_nCountTotalGradeEx;

	void InitGradeExPosCount();
	bool CheckGradeExPosCount( int pos, int charIndex = 0 );
	void ChangeGradeExPosCount( int oldpos, int pos);
	void DelGradeExPosCount(int pos);
	void AddGradeExPosCount( int pos );
	int  GetGradeExPosNeedGuilPoint( int pos );

#ifdef DEV_GUILD_MARK
private:
	char m_GuildMark_row;
	char m_GuildMark_col;
	char m_Background_row;
	char m_Background_col;
	// ��帶ũ �ð��� ���� ���� �ð����� ����Ǿ� ������ ���ӿ��� ����Ҷ��� ���ӽð��� Ŭ���̾�Ʈ�� �����ش�.
	int m_GuildMarkExpire;
public:
	void SetGuildMark(char gm_row, char gm_col, char bg_row, char bg_col, int markTime);
	char GetGuildMarkRow();
	char GetGuildMarkCol();
	char GetBackgroundRow();
	char GetBackgroundCol();
	int GetMarkTime();
	int GetMarkTimeConvertGameTime();
#endif // GUILD_MARK

private:
	CGuildKick m_guildKick;

	int getStandardTimeForKick(void);
	int getBossDateStamp(void);
	int getLastChansgeBossTime(void);
public:
	CGuildKick* getGuildKick(void);

	bool isPossibleKickMaster(void);		// ���� �߹��� ��������?
	bool isPastLastChangeBoss(void);		// ���� ������ ����� �� 7���� ��������?
	int getNewBossByKick(void);				// �߹����� ���� ���ο� ���� ���ϱ�

	bool m_isUseTheStashAndSkill;

	int m_battle_win_count;
	int m_battle_lose_count;
	int m_battle_total_count;

	int m_guild_contribute_all_exp_min;
	int m_guild_contribute_all_exp_max;

	int m_guild_contribute_all_fame_min;
	int m_guild_contribute_all_fame_max;
};

class CGuildList
{
	CGuild*			m_head;
	int				m_count;

public:
	CGuildList();
	~CGuildList();

	////////////////////
	// Function name	: create
	// Description	    : ��带 ���� -> ����� boss�߰� -> boss ���� -> 1��¥�� ������ ���� ��� ����
	static CGuild* create(int guildindex, const char* guildname, int charindex, const char* bossname, int create_date, int battle_win_count, int battle_lose_count, int battle_total_count);
	static CGuild* create(int guildindex, const char* guildname, int guildlevel, int battleIndex, int battlePrize, int battleTime, int batttleZone, int battleKillCount, int battleState, int create_date, int battle_win_count, int battle_lose_count, int battle_total_count);

	void add(CGuild* guild);
	void Remove(CGuild* guild);

	CGuild* findguild(int guildindex);

	CGuild* findguild(const char* guildname);

	////////////////////
	// Function name	: findmember
	// Description	    : Ư�� ĳ���Ͱ� �Ҽӵ� ��带 ã�´�
	CGuildMember* findmember(int charindex);

	void Reset();

	int GetCount() { return m_count; } //new24052022

	CGuild* head()
	{
		return m_head;
	}
};

// ���� ��� ����Ʈ
class CHostilityGuildList
{
	CGuild*		m_head;
	int			m_count;

public:
	CHostilityGuildList();
	~CHostilityGuildList();

	void AddGuild( CGuild* guild );
	void RemoveGuild( CGuild* guild );

	CGuild* FindGuild( int guildindx );

	////////////////////
	// Function name	: findmember
	// Description	    : Ư�� ĳ���Ͱ� �Ҽӵ� ��带 ã�´�
	CGuildMember* findmember(int charindex);

	void Reset();

	CGuild* head()
	{
		return m_head;
	}
};

// ���� ��� ����Ʈ
class CAllyGuildList
{
	CGuild*		m_head;
	int			m_count;

public:
	CAllyGuildList();
	~CAllyGuildList();

	void AddGuild( CGuild* guild );
	void RemoveGuild( CGuild* guild );

	CGuild* FindGuild( int guildindx );

	////////////////////
	// Function name	: findmember
	// Description	    : Ư�� ĳ���Ͱ� �Ҽӵ� ��带 ã�´�
	CGuildMember* findmember(int charindex);

	void Reset();

	CGuild* head()
	{
		return m_head;
	}
};

#endif
