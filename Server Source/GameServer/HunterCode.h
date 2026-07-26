#ifndef __HUNTER_CODE_H__
#define __HUNTER_CODE_H__
enum HNTERMSG
{
	HNTER_FLAG = 0
};

void SaveHackUser(const char* idname, int charIndex);
void ProcFlagCarrier(CPC* df, CCharacter* of);
bool HasFlagCarrierItem(CPC* pc);


#endif