#ifndef __QUEST_SYSTEM__
#define __QUEST_SYSTEM__

#include <string>
#include <vector>
#include <map>
#include <Engine/Base/Types.h>
#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIDefine.h>

#include <Engine/Help/LoadLod.h>
#include <common/header/def_quest.h>

#define QUEST_FLAG_NOT_LEVEL	0		// ���� �Ұ��� : ����
#define QUEST_FLAG_NOT_JOB		1		// ���� �Ұ��� : ����
#define QUEST_FLAG_NOT_ITEM		2		// ���� �Ұ��� : ������
#define QUEST_FLAG_CAN			3		// ���� ����
#define QUEST_FLAG_ING			4		// ���� ��
#define QUEST_FLAG_COMPLETE		5		// ����Ʈ �Ϸ�.
#define QUEST_FLAG_NOT_EXP		6		//���� �Ұ��� : ����ġ ����.
#define QUEST_FLAG_NOT_PREQUEST	7		//���� �Ұ��� : ���� ����Ʈ �̿Ϸ�.

//�������� ������ Define
#define		MAX_MAX_NEED_ITEM			5		// �ʿ������ �ִ� 5
#define		QUEST_MAX_CONDITION			3		// �������� �ִ� 3
#define		QUEST_MAX_PRIZE				5		// ���� �ִ� 5
#define		QUEST_MAX_OPTION_PRIZE		7		// �ɼ� ���� �ִ� 7 [090728: selo]
#define		QUEST_MAX_CONDITION_DATA	4		// �������� �ϳ��� �ΰ� ����Ÿ 4
#define		MAX_PC_QUEST				10		// ĳ���� ��Ƽ ����Ʈ 10

// ����Ʈ �з� [090603: selo]
#define		QCATEGORY_NORMAL			0		// �Ϲ�
#define		QCATEGORY_SCENARIO			1		// �ó�����
#define		QCATEGORY_SUPPLEMENT		2		// ����
//#define		QCATEGORY_NIGHTSHADOW		3		// ����Ʈ ������
#define		QCATEGORY_END				QCATEGORY_SUPPLEMENT + 1

// ����Ʈ �Ը� [090603: selo]
#define		QSCALE_SINGLE				0		// �Ϲ�
#define		QSCALE_PARTY				1		// ��Ƽ
#define		QSCALE_EXPEDITION			2		// ������

// ������ Ÿ��(Type1)
#define		QTYPE_KIND_REPEAT					0  // �ݺ��� ����Ʈ
#define		QTYPE_KIND_COLLECTION				1  // ������ ����Ʈ
#define		QTYPE_KIND_DELIVERY					2  // ������ ����Ʈ
#define		QTYPE_KIND_DEFEAT					3  // ���� ����Ʈ(�̱۴���1)
#define		QTYPE_KIND_SAVE						4  // ���� ����Ʈ(�̱۴���2)
#define		QTYPE_KIND_MINING_EXPERIENCE		5  // ä�� ü�� ����Ʈ
#define		QTYPE_KIND_GATHERING_EXPERIENCE		6  // ä�� ü�� ����Ʈ
#define		QTYPE_KIND_CHARGE_EXPERIENCE		7  // ���� ü�� ����Ʈ
#define		QTYPE_KIND_PROCESS_EXPERIENCE		8  // ���� ü�� ����Ʈ
#define		QTYPE_KIND_MAKE_EXPERIENCE			9  // ���� ü�� ����Ʈ
#define		QTYPE_KIND_TUTORIAL					10 // Ʃ�丮�� ����Ʈ
#define		QTYPE_KIND_SEARCH					11 // Ž�� ����Ʈ

// ���ະ Ÿ��(Type2)
#define		QTYPE_REPEAT_ONCE			0		// 1ȸ�� ����Ʈ
#define		QTYPE_REPEAT_UNLIMITED		1		// ���� ����Ʈ
#define		QTYPE_REPEAT_DAY			2		// ���� ����Ʈ
#define		QTYPE_REPEAT_WEEK			3 //dethunter12 repeat quest weekly

// ���� Ÿ��
#define		QSTART_NPC					0		// NPC�� ���� ����
#define		QSTART_LEVEL				1		// ���� ���� ���� ����
#define		QSTART_ITEM					2		// �������� ���� ����
#define		QSTART_AREA					3		// Ư�������� �����Ͽ� ����

// ����Ʈ ���� ����
#define		QCONDITION_NPC				0		// NPC
#define		QCONDITION_ITEM				1		// ������
#define		QCONDITION_ITEM_NORMAL		2		// ������(�Ϲ�)
#define		QCONDITION_PC				3		// PC (ĳ���� PK)
#define		QCONDITION_AREA				4		// ���� ����
#define		QCONDITION_ITEMUSE			5		// ������ ���

// ����Ʈ ���� ����
#define		QPRIZE_ITEM					0		// ������ (������)
#define		QPRIZE_MONEY				1		// ������ (������)
#define		QPRIZE_EXP					2		// ����ġ
#define		QPRIZE_SP					3		// ��ų����Ʈ
#define		QPRIZE_SKILL				4		// ��ų
#define		QPRIZE_SSKILL				5		// Ư����ų
#define		QPRIZE_RVR_POINT			7		// ���� ����Ʈ.
#define		QPRIZE_EXP_RATE				8

#define		QUEST_MAX_NPC				50		// npc �ϳ��� �ִ� ����Ʈ ���� �� 50
#define		QUEST_MAX_PC_COMPLETE		100		// pc�� �Ϸ��� 1ȸ�� ����Ʈ �ִ� ��

// Line count of description
#define	QUEST_TITLE_DESC				4
#define	QUEST_STATUS_DESC				QUEST_MAX_CONDITION * 2
#define	QUEST_PRIZE_DESC				QUEST_MAX_PRIZE + 1
#define QUEST_OPTION_PRIZE_DESC			QUEST_MAX_OPTION_PRIZE + 1	// [090728: selo] �ɼ� ���� ������ ���� �Ǿ��� (5�� -> 7��)
#define	QUEST_NEED_DESC					MAX_MAX_NEED_ITEM + 1

// [100119: selo] ������ �ɼ� ó���� ���� ����ü
struct stOptionPrizeTemp
{
	INDEX	m_iOptionPrizeType[QUEST_MAX_OPTION_PRIZE];
	INDEX	m_iOptionPrizeIndex[QUEST_MAX_OPTION_PRIZE];
	INDEX	m_iOptionPrizeData[QUEST_MAX_OPTION_PRIZE];
	INDEX	m_iOptionPrizePlus[QUEST_MAX_OPTION_PRIZE];
};

// quest ���� ������, DB���� ���� Data�� ���Ͽ��� �о����. ���� �������.
class CQuestStaticData : public stQuest, public LodLoader<CQuestStaticData>
{
protected:
	INDEX	m_iCategory;		// ����Ʈ �з� [090603: selo]
	int		transFlag;	//[sora] �̹��� ��Ʈ�� index ǥ��

	std::string	m_szName;
	std::string	m_szDesc;
	std::string	m_szDesc2;
	std::string	m_szDesc3;

public:
	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslate();
	void ClearNoTranslate();
	INDEX GetIndex()	{ return index; }

	void SetCategory(INDEX iCategory) { m_iCategory = iCategory; }
	void SetTitle(const char* str)	{ m_szName = str; }
	void SetDesc1(const char* str)	{ m_szDesc = str; }
	void SetDesc2(const char* str)	{ m_szDesc2 = str; }
	void SetDesc3(const char* str)	{ m_szDesc3 = str; }

	INDEX GetCategory() { return m_iCategory; }
	const char* GetTitle()	{ return m_szName.c_str(); }
	const char* GetDesc1()	{ return m_szDesc.c_str(); }
	const char* GetDesc2()	{ return m_szDesc2.c_str(); }
	const char* GetDesc3()	{ return m_szDesc3.c_str(); }

	static bool loadEx(const char* fileName);
};

// quest ���� ������, ������ �����ִ� Data�� ���Ͽ��� ���� Data�� «���ؼ� ����� ����Ÿ
// ���� ������� ����� Data�� ���� �÷��� ���� ĳ������ Data��. String ������.
class ENGINE_API CQuestDynamicData
{
private:
	CQuestStaticData* m_pStaticData;
public:
	CQuestDynamicData(CQuestStaticData* data);
	~CQuestDynamicData();

	// from quest static data
	INDEX GetQuestIndex()	{ return m_iQuestIndex; }
	const char *GetName()	{ return m_pStaticData->GetTitle(); }
	INDEX GetQuestCategory() { return m_pStaticData->GetCategory();	}   const		// ����Ʈ �з� [090603: selo]
	INDEX GetQuestPartyScale() { return m_pStaticData->partyscale; }	const		// ����Ʈ �Ը� [090603: selo]
	INDEX GetQuestType1()	{ return m_pStaticData->type1;		}	const		// Type1
	INDEX GetQuestType2()	{ return m_pStaticData->type2;		}	const		// Type2

	INDEX GetStartType()	{ return m_pStaticData->startType;	}	const
	INDEX GetStartData()	{ return m_pStaticData->startData;	}	const
	//INDEX GetGiveNPCIndex()	{ return m_rStaticData.m_iGiveNPCIndex; }	const
	INDEX GetPrizeNPCIndex(){ return m_pStaticData->prizeNPC; }	const
	INDEX GetPreQuestIndex(){ return m_pStaticData->preQuestNo; }	const
	INDEX GetStartNPCZoneIndex(){ return m_pStaticData->startNpcZoneNo; }	const
	INDEX GetPrizeNPCZoneIndex(){ return m_pStaticData->prizeNpcZoneNo; }	const

	INDEX GetNeedMinLevel()	{ return m_pStaticData->needMinLevel;	}	const
	INDEX GetNeedMaxLevel()	{ return m_pStaticData->needMaxLevel;	}	const
	INDEX GetNeedJob()		{ return m_pStaticData->needJob;	}	const
	INDEX GetNeedItemIndex(INDEX i)		{ ASSERT(i < MAX_MAX_NEED_ITEM); return m_pStaticData->needItemIndex[i]; }
	INDEX GetNeedItemCount(INDEX i)		{ ASSERT(i < MAX_MAX_NEED_ITEM); return m_pStaticData->needItemCount[i]; }

	INDEX GetConditionType(INDEX i)		{ ASSERT(i < QUEST_MAX_CONDITION); return m_pStaticData->conditionType[i]; }
	INDEX GetConditionIndex(INDEX i)	{ ASSERT(i < QUEST_MAX_CONDITION); return m_pStaticData->conditionIndex[i]; }
	INDEX GetConditionNum(INDEX i)		{ ASSERT(i < QUEST_MAX_CONDITION); return m_pStaticData->conditionNum[i]; }
	INDEX GetConditionData(INDEX i, INDEX j)		
	{ ASSERT(i < QUEST_MAX_CONDITION); ASSERT(j < QUEST_MAX_CONDITION_DATA); return m_pStaticData->conditionData[i][j]; }

	INDEX		GetSyndicateType()	{ return m_pStaticData->rvr_type;	}
	INDEX		GetSyndicateGrade()	{ return m_pStaticData->rvr_grade;	}
	
	//INDEX GetPrizeType(INDEX i)			{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iPrizeType[i]; }
	//INDEX GetPrizeIndex(INDEX i)		{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iPrizeIndex[i]; }
	//INDEX GetPrizeData(INDEX i)			{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iPrizeData[i]; }
	//INDEX IsOptionPrizeExist()			{ return m_rStaticData.m_bOptionPrize;	}
	//INDEX GetOptionPrizeType(INDEX i)	{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iOptionPrizeType[i]; }
	//INDEX GetOptionPrizeIndex(INDEX i)	{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iOptionPrizeIndex[i]; }
	//INDEX GetOptionPrizeData(INDEX i)	{ ASSERT(i < QUEST_MAX_PRIZE); return m_rStaticData.m_iOptionPrizeData[i]; }
	INDEX IsPrizeExist()				{ return m_bPrize;	}
	INDEX GetPrizeType(INDEX i)			{ ASSERT(i < QUEST_MAX_PRIZE); return m_iPrizeType[i]; }
	INDEX GetPrizeIndex(INDEX i)		{ ASSERT(i < QUEST_MAX_PRIZE); return m_iPrizeIndex[i]; }
	__int64 GetPrizeData(INDEX i)			{ ASSERT(i < QUEST_MAX_PRIZE); return m_iPrizeData[i]; }

	INDEX IsOptionPrizeExist()			{ return m_bOptionPrize;	}
	INDEX GetOptionPrizeType(INDEX i)	{ ASSERT(i < QUEST_MAX_OPTION_PRIZE); return m_iOptionPrizeType[i]; }
	INDEX GetOptionPrizeIndex(INDEX i)	{ ASSERT(i < QUEST_MAX_OPTION_PRIZE); return m_iOptionPrizeIndex[i]; }
	INDEX GetOptionPrizeData(INDEX i)	{ ASSERT(i < QUEST_MAX_OPTION_PRIZE); return m_iOptionPrizeData[i]; }
	INDEX GetOptionPrizePlus(INDEX i)	{ ASSERT(i < QUEST_MAX_OPTION_PRIZE); return m_iOptionPrizePlus[i]; }

	const char *GetDesc()	{ return m_pStaticData->GetDesc1(); }
	const char *GetDesc2()	{ return m_pStaticData->GetDesc2(); }
	const char *GetDesc3()	{ return m_pStaticData->GetDesc3(); }		

	// myself
	void SetCurrentConditionValueStatus(INDEX current[QUEST_MAX_CONDITION]);
	INDEX GetCurrentConditionValueStatus(INDEX i)	{ ASSERT(i < QUEST_MAX_CONDITION); return m_iCurrentConditionValueStatus[i]; }

	void MakeQuestComplete()			{ m_bQuestComplete = TRUE; }
	void MakeQuestUncomplete()			{ m_bQuestComplete = FALSE; }
	BOOL IsQuestComplete()				{ return m_bQuestComplete; }

	//INDEX GetConditionValue(INDEX i)	{ ASSERT(i < QUEST_MAX_CONDITION); return m_iConditionValue[i]; }
	//INDEX GetPrizeValue(INDEX i)		{ ASSERT(i < QUEST_MAX_PRIZE); return m_iPrizeValue[i]; }

	CTString	&GetIntroDesc() { return m_strIntroDesc; }
	COLOR		GetColorIntroDesc() { return m_colIntroDesc; }

	INDEX		GetCountTitleDesc() { return m_ctTitleDesc; }
	CTString	&GetTitleDesc( INDEX iIndex ) { return m_strTitleDesc[iIndex]; }
	COLOR		GetColorTitleDesc( INDEX iIndex ) { return m_colTitleDesc[iIndex]; }

	INDEX		GetCountStatusDesc() { return m_ctStatusDesc; }
	CTString	&GetStatusDesc( INDEX iIndex ) { return m_strStatusDesc[iIndex]; }
	COLOR		GetColorStatusDesc( INDEX iIndex ) { return m_colStatusDesc[iIndex]; }

	INDEX		GetCountPrizeDesc() { return m_ctPrizeDesc; }
	CTString	&GetPrizeDesc( INDEX iIndex ) { return m_strPrizeDesc[iIndex]; }
	COLOR		GetColorPrizeDesc( INDEX iIndex ) { return m_colPrizeDesc[iIndex]; }

	INDEX		GetCountOptionPrizeDesc() { return m_ctOptionPrizeDesc; }
	CTString	&GetOptionPrizeDesc( INDEX iIndex ) { return m_strOptionPrizeDesc[iIndex]; }
	COLOR		GetColorOptionPrizeDesc( INDEX iIndex ) { return m_colOptionPrizeDesc[iIndex]; }

	INDEX		GetCountNeedDesc() { return m_ctNeedDesc; }
	CTString	&GetNeedDesc( INDEX iIndex ) { return m_strNeedDesc[iIndex]; }
	COLOR		GetColorNeedDesc( INDEX iIndex ) { return m_colNeedDesc[iIndex]; }

	friend class CQuestSystem;
	
protected:
	CQuestDynamicData(const CQuestDynamicData &other);
	CQuestDynamicData &operator = (CQuestDynamicData &other);

	void	MakeQuestFirstDesc();
	void	MakeQuestTitleDesc();
	void	MakeQuestStatusDesc();
	void	MakeQuestPrizeDesc();
	void	MakeQuestOptionPrizeDesc();
	void	MakeQuestNeedDesc();

	INDEX	FindItemForPrize(INDEX type, INDEX index);

	INDEX		m_iQuestIndex;
	BOOL		m_bQuestComplete;

	BOOL		m_bPrize;
	INDEX		m_iPrizeType[QUEST_MAX_PRIZE];
	INDEX		m_iPrizeIndex[QUEST_MAX_PRIZE];
	__int64		m_iPrizeData[QUEST_MAX_PRIZE];
	
	INDEX		m_bOptionPrize;
	INDEX		m_iOptionPrizeType[QUEST_MAX_OPTION_PRIZE];
	INDEX		m_iOptionPrizeIndex[QUEST_MAX_OPTION_PRIZE];
	INDEX		m_iOptionPrizeData[QUEST_MAX_OPTION_PRIZE];
	INDEX		m_iOptionPrizePlus[QUEST_MAX_OPTION_PRIZE];

	// [090728: selo] �ɼ� ���� ī��Ʈ
	INDEX		m_iOptionPrizeCount;

	INDEX		m_iCurrentConditionValueStatus[QUEST_MAX_CONDITION];
	CTString	m_strIntroDesc;
	COLOR		m_colIntroDesc;
	INDEX		m_ctTitleDesc;
	CTString	m_strTitleDesc[QUEST_TITLE_DESC];
	COLOR		m_colTitleDesc[QUEST_TITLE_DESC];
	INDEX		m_ctStatusDesc;
	CTString	m_strStatusDesc[QUEST_STATUS_DESC];
	COLOR		m_colStatusDesc[QUEST_STATUS_DESC];
	INDEX		m_ctPrizeDesc;
	CTString	m_strPrizeDesc[QUEST_PRIZE_DESC];
	COLOR		m_colPrizeDesc[QUEST_PRIZE_DESC];
	INDEX		m_ctOptionPrizeDesc;
	CTString	m_strOptionPrizeDesc[QUEST_OPTION_PRIZE_DESC];
	COLOR		m_colOptionPrizeDesc[QUEST_OPTION_PRIZE_DESC];
	INDEX		m_ctNeedDesc;
	CTString	m_strNeedDesc[QUEST_NEED_DESC];
	COLOR		m_colNeedDesc[QUEST_PRIZE_DESC];
};

// Quest���� �������� ������ ����Ѵ�. �̱��� ����.
class ENGINE_API CQuestSystem
{
public:
	enum eNpcQuestType
	{
		NQT_NONE,
		NQT_HAVE_QUEST,
		NQT_CAN_PRIZE,
		NQT_COUNT,
	};
	enum eQuestAllowType
	{
		QAT_ALLOW,
		QAT_ALREADY_DONE,
		QAT_GIVEUP,
		QAT_DOING,//���� ������.
	};
public:
	static CQuestSystem &Instance()	{ return m_instance; }
	bool Load();

	CQuestDynamicData *GetDynamicDataByVectorIndex(INDEX idx)
	{
		if(idx >= m_vectorCurrentUserQuest.size()) return NULL;
		else return m_vectorCurrentUserQuest[idx];
	}
	CQuestDynamicData *GetDynamicDataByQuestIndex(INDEX idxQuest);
	INDEX GetVectorIndexByGiveNPCIndex( INDEX idxNPC );
	INDEX GetVectorIndexByPrizeNPCIndex( INDEX idxNPC );

	CQuestDynamicData *Create(INDEX idxQuest);
	INDEX AddCurrentRequest();
	void DeleteCurrentRequest();
	BOOL Remove(INDEX idxQuest);

	CQuestDynamicData *GetCurrentRequest() const { return m_pCurrentRequest; }

	void	ClearAllDynamicData();
	void	ClearAllAllowList();

	~CQuestSystem();
	
	CQuestStaticData* GetStaticData(INDEX idxQuest)
	{
		return CQuestStaticData::getData(idxQuest);
	}

	void SetQuestAllow(INDEX iQuestIndex, eQuestAllowType qat)
	{
		if(iQuestIndex==-1) return;
		if((qat == QAT_ALREADY_DONE || qat == QAT_GIVEUP)
		&& CQuestStaticData::getData(iQuestIndex)->type2 == QTYPE_REPEAT_UNLIMITED)
		{
			m_vectorQuestAllowList[iQuestIndex] = QAT_ALLOW;
			return;
		}
		m_vectorQuestAllowList[iQuestIndex] = qat;
	}
	eQuestAllowType GetQuestAllow(INDEX iQuestIndex)
	{
		ASSERT(iQuestIndex != -1);
		return m_vectorQuestAllowList[iQuestIndex];
	}
	const char *GetQuestName(int iQuestIndex)
	{
		return CQuestStaticData::getData(iQuestIndex)->GetTitle();
	}
	const int GetQuestMinLevel(int iQuestIndex)
	{
		return CQuestStaticData::getData(iQuestIndex)->needMinLevel;
	}
	const int GetQuestMaxLevel(int iQuestIndex)
	{
		return CQuestStaticData::getData(iQuestIndex)->needMaxLevel;
	}

	INDEX SearchContactQuestIndex(INDEX iQuestIndex); // ����Ʈ �ε����� ���� �Ǵ� ����Ʈ �˻� ���� ���� ����Ǵ� npc Index
	BOOL CanIDoQuest(INDEX iQuestIndex);
	CTString MakeInfoForCondition(int iQuestIndex, int iConditionType, int iConditionIndex, int iCurrentCnt, int iConditionCnt);
	eNpcQuestType TestNPCForQuest(INDEX iNPCIndex);

	//[sora] �̹��� ��Ʈ�� index ǥ��
	void SetNoTranslate( std::vector<INDEX> transList );
	void ClearNoTranslate( std::vector<INDEX> transList );
	
protected:
	CQuestSystem();

	static CQuestSystem m_instance;
	CQuestDynamicData *m_pCurrentRequest;
	std::vector<CQuestDynamicData*> m_vectorCurrentUserQuest;
	std::vector<eQuestAllowType>	m_vectorQuestAllowList;
	typedef std::multimap<INDEX, INDEX> mmap;
	mmap m_mmapNPCToQuest;
	mmap m_mmapPreQuestToCurQuest;
};

#endif //__QUEST_SYSTEM__