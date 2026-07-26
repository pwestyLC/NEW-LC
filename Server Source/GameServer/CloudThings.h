#pragma once
#ifndef __CLOUDTHINGS__
#define __CLOUDTHINGS__
#include "../ShareLib/Config.h"
#include "CloudThings.h"

#ifdef BATTLE_PASS_SYSTEM
void ResetBattlePass();
#endif
#ifdef PRESTIGE_SYSTEM
void ResetPrestige();
#endif
#ifdef CLOUD_EXPEDITION_PARTY_DUNGEONS	
void UpdatePartyDungeonInfo(CPC* pChar);
#endif
#endif