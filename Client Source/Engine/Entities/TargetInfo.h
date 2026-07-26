#ifndef INCL_TARGETINFOM_H
#define INCL_TARGETINFOM_H
#ifdef PRAGMA_ONCE
#pragma once
#endif

//#include <Engine/Entities/Entity.h>
#include <Engine/Math/Vector.h>
#include <Engine/Base/CTString.h>

typedef enum _tagTargetType
{
	CHARACTER,
	MOB,
	ITEM,
	NPC,
	PRODUCTION,
	P1PET,	
	SUMMON,
	WILDPET,
} TARGET_TYPE;


struct stTargetBase
{
	BOOL	bIsActive;
	SBYTE	TargetType;
	char	TargetName[50];
	__int64	fMaxHealth;
	__int64	fHealth;
	int		iLevel;
	CEntity	*pen_pEntity;
	int		PkMode;
	int		PkState;
	int     PkTitle;
	int		Legit;
	int		dbIdx;

	void Init()
	{
		fMaxHealth = 0;
		fHealth = 0;
		bIsActive = FALSE;
		iLevel = 0;
		TargetName[0] = NULL;
		pen_pEntity = NULL;
		PkMode = 0;
		PkState = 0;
		PkTitle = 0;
		dbIdx = 0;		
	}
};

class  CTargetInfom : public stTargetBase
{
public:
	BOOL	bPkHideState;
	int		nSyndicateType;		// ���� Ÿ��
	int		nSyndicateGrade;	// ���� ����

public:
	CTargetInfom(void);
	~CTargetInfom(void);

	ENGINE_API void	Init();
};

class  CTargetInfomReal : public stTargetBase
{
public:
	INDEX		colorName;
	INDEX		iReborn;
	SQUAD		llCount;
	LONG		lGuildIndex;	// ��� �ε���
	CTString	strGuildName;	// ����
	SBYTE		sbGuildRank;		// WSS_GUILDMASTER 070517
	UBYTE		ubGuildNameColor;	//[071123: Su-won] DRATAN_SIEGE_DUNGEON
	INDEX		iNickIndex;			// ȣĪ �ε���
	
public:
	CTargetInfomReal(void);
	~CTargetInfomReal(void);

	ENGINE_API void	Init();
};

#endif