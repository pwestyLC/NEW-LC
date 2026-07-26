#ifndef __BATTLE_H__
#define __BATTLE_H__

bool IsPK(CPC* of, CCharacter* df);
bool IsAvailableAttack(CCharacter* of, CCharacter* df);
void ProcAfterHit(CCharacter* of, CCharacter* df);
void ProcDead(CNPC* df, CCharacter* of);
void ProcDead(CPC* df, CCharacter* of);
void ProcDead(CPet* df, CCharacter* of);
void ProcDead(CElemental* df, CCharacter* of);
void ProcDead(CAPet* df, CCharacter* of);
void ProcDropItemAfterBattle(CNPC* df, CPC* opc, CPC* tpc, int level);
int ProcAttack(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE damageType, CSkill* skill, int magicindex, int damage = 0);

// ���� ����� ó���κ�
void ProcFollowNPC(CNPC* npc);
bool CheckBothPvPArea(CCharacter* ch, CCharacter* tch);
bool CheckInNearCellExt(CCharacter* ch, CCharacter* tch);
char GetHitType(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type);
#if defined (ENABLE_ROGUE_SKILL125_BRZ)
char SelectHitType(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type, char flag, const CMagicProto* magic, const CMagicLevelProto* magiclevel, bool nothelp, int skillLevel = 0);
#else
char SelectHitType(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type, char flag, const CMagicProto* magic, const CMagicLevelProto* magiclevel, bool nothelp);
#endif // ENABLE_ROGUE_SKILL125_BRZ
int GetDamage(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type, char flag, const CMagicProto* magic, const CMagicLevelProto* magiclevel, bool& isCharge);
CPC* FindPreferencePC(CNPC* npc, int* level, LONGLONG* pnTotalDamage);
// ����ġ �й� : 051228 : BS ���� �ۼ�
bool DivisionExpSP(CNPC* npc, CPC* pPreferencePC, LONGLONG nTotalDamage);
void DivisionPartyMoney(CPC* pc, CNPC* npc, LONGLONG count);
bool GetItemRandomParty(CPC* pc, CItem* item);

bool GetItemRaidOpenBox(CPC* pc, CItem* item);

void DivisionExpedMoney(CPC* pc, CNPC* npc, LONGLONG count);
bool GetItemRandomExped(CPC* pc, CItem* item);
bool GetItemGiveToBoss(CPC* pc, CItem* item);

CCharacter* CheckAttackPulse(CNPC* npc);
// tch�� attackchar���� ch�� �ش� �ϴ� �� ����
CAttackChar* AddAttackList(CCharacter* ch, CCharacter* tch, int hate);
void DelAttackList(CCharacter* ch);
void DelTargetFromAttackList(CCharacter* ch, CCharacter* tch);
void FindFamilyInNear(CCharacter* of, CNPC* npc);
bool GetSkillPrototypes(const CSkillProto* proto, int level, int magicindex, const CSkillLevelProto** levelproto, const CMagicProto** magic, const CMagicLevelProto** magiclevel);
void ApplyHateByDamage(CCharacter* of, CCharacter* df, char hittype, int damage);
// tch�� attackchar���� ch�� �ش� �ϴ� �� ����
CAttackChar* ApplyHate(CCharacter* of, CCharacter* df, int hate, bool bApplyFamily);
void ApplyDamage(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE damageType, const CSkillProto* proto, const CMagicProto* magic, int damage, char flag, bool isCharge);
void CalcPKPoint(CPC* of, CPC* df, bool bDeadPet);

// ������� ����Ʈ ���� �߰�
void AddRaList(CPC* of, CPC* df);

// ������� ����Ʈ�� �ִ°� Ȯ��
bool IsRaList(CPC* of, CPC* df);

// 060318 : bs : ���濡�� of�� df�� �����Ͽ����� �˻�
bool IsFirstAttackInAttackList(CPC* of, CPC* df);

// ���� ����Ʈ ����ϴ� �Լ�
void CalcWarPoint(CCharacter* of, CCharacter* df);
void DropWarCastleTokenDeadPC(CCharacter* df);
void DropWarCastleToken(CNPC* npc, CPC* pc, CPC* tpc, int level);
void DropPvPTokenDeadPC(CCharacter* of, CCharacter* df);

bool DropPetItem(CPet* pet);

// base ������� n1�� n2�� AI �켱���� ��
// n1�� ������ -1, n2�� ������ 1, ������ 0
int AIComp(CNPC* base, CNPC* n1, CNPC* n2);

char GetHitType_Adult(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type);
char SelectHitType_Adult(CCharacter* of, CCharacter* df, MSG_DAMAGE_TYPE type, char flag, const CMagicProto* magic, const CMagicLevelProto* magiclevel, bool nothelp);

//pvp ī�� ���Ƽ ����
int CalcNewDamage(CCharacter* of, CCharacter* df, int damage);
void CalcNewHitProb(CCharacter* of, CCharacter* df, float& hit, float& avoid);
int CalcNewHitProb(CCharacter* of, CCharacter* df, int hit, int avoid);

bool checkPvPProtect(CPC* pc, CCharacter* tpc);
#endif // __BATTLE_H__
//
