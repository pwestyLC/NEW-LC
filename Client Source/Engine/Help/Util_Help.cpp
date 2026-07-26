#include "StdH.h"
#include "Util_Help.h"

#include <Engine/LocalDefine.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Interface/UIPetInfo.h>
#include <Engine/Entities/InternalClasses.h>
#include <Engine/Network/SessionState.h>
#include <Engine/GameState.h>
#include <Engine/Graphics/Font.h>
#include <Engine/Interface/UITextureManager.h>
#include <Engine/Entities/Items.h>

extern INDEX g_iCountry;

enum
{
	Item_Rare_Grade_Hero_A = 0,
	Item_Rare_Grade_Unique_B,
	Item_Rare_Grade_Rare_C,
	Item_Rare_Grade_Magic_D,
	Item_Rare_Grade_Basic_E,
	
	Item_Rare_Grade_MAX	
};

enum
{
	Item_Grade_Normal_blood = 0,
	Item_Grade_Legend_Origine = 1,
};

#define ONE_MINUTE_SECOND		60
#define ONE_HOUR_SECOND		  3600
#define ONE_DAY_SECOND		 86400
#define FIVE_DAY_SECOND		432000
#define TEN_DAY_SECOND		864000
#define FIFTY_DAY_SECOND   1296000

// �Ϲ� ���â ��Ʈ�� �ε���
const int idx_WearSting[WEAR_TOTAL] = { 
		2544 // ����
	,	4273 // ����
	,	4775 // ����
	,	4274 // ����
	,	4277 // ����
	,	4275 // �尩
	,	4276 // �Ź�
	,	726 // �Ǽ�1
	,	726 // �Ǽ�2
	,	726 // �Ǽ�3
	,	5140 // ��
	,	5916 // ����, ��
	,	726 // newslot - alanssoares
	,	726 // newslot - alanssoares
	,	726 // newslot - alanssoares
	,	726 // newslot - alanssoares
	,	726 // newslot - alanssoares
	,	726 // newslot - alanssoares
};

// �ڽ�Ƭ ���â ��Ʈ�� �ε���
const int idx_WearCostumeSting[WEAR_COSTUME_TOTAL] = { 
		2544 // ����
	,	4273 // ����
	,	4775 // ����
	,	4274 // ����
	,	4277 // ����
	,	4275 // �尩
	,	4276 // �Ź�
	,	5916 // ����, ��
};

UtilHelp::UtilHelp()
{
	
}

UtilHelp::~UtilHelp()
{
	
}

eOPTION_TYPE UtilHelp::GetOptionType( int nOptionType )
{
	eOPTION_TYPE nRet = OPTION_TYPE_ERROR;
	switch(nOptionType)
	{
	case JEWEL_OPTION_PACIVE:
		nRet = OPTION_TYPE_PACIVE;
		break;
		
	case JEWEL_OPTION_ACTIVE_SKILL_ATT:
	case JEWEL_OPTION_ACTIVE_SKILL_DEF:
		nRet = OPTION_TYPE_ACTIVE;
		break;
	}

	return nRet;	
}

eOPTION_STRING_TYPE UtilHelp::GetPaciveOptionType( int nOptionType )
{
	eOPTION_STRING_TYPE		nRet = STRING_TYPE_ERROR;

	switch(nOptionType)
	{
	case OPTION_DOWN_LIMITLEVEL:	//49 �������� ���� �ٿ�
		nRet = STRING_TYPE_NEGATIVE;
		break;
	case OPTION_STEAL_MP:			// 51 ���� ����
	case OPTION_STEAL_HP:			// 52 ������ ����
		// [2012/02/09 : Sora] ITS 6691 ũ��Ƽ�� �� ���鸮 ���ߵ� %ǥ�� �߰�
	case OPTION_ATTACK_CRITICAL:	// 55 ũ��Ƽ�� ���߷� ����
	case OPTION_RECOVER_HP:			// 56 HPȸ���� ���
	case OPTION_RECOVER_MP:			// 57 MPȸ���� ���
	case OPTION_DECREASE_SKILL_MP:	// 59 MP�Ҹ� ����
	case OPTION_RESIST_STONE:		// 60 ���� ���� ����
	case OPTION_RESIST_STURN:		// 61 ���� ���� ����
	case OPTION_RESIST_SILENT:		// 62 ħ�� ���� ����
	case OPTION_BLOCKING:			// 63 ���Ϸ� ����
	case OPTION_MOVESPEED:			// 64 �̵��ӵ� ���
	case OPTION_ATTACK_DEADLY:		// 66 ���鸮 ���߷� ����
	case OPTION_PERSONAL_EXP_UP:	//108 [����] ����ġ ���
	case OPTION_PERSONAL_GOLD_UP:	//109 [����] ȹ�� ���� ���
	case OPTION_PARTY_EXP_UP:		//111 [��Ƽ] ����ġ ���
	case OPTION_PARTY_GOLD_UP:		//112 [��Ƽ] ȹ�� ���� ���
		nRet = STRING_TYPE_PERCENT;
		break;
	case OPTION_FLYSPEED:		// 65 ����ӵ� ���
		nRet = STRING_TYPE_FLOAT_POINT_ONE;
		break;
	case OPTION_PVP_DAMAGE_ABSOLB:	// 100 PVP ������ ����
	case OPTION_DEBUF_DECR_TIME:	// 101 ����� �ð� ����
		nRet = STRING_TYPE_FLOAT_POINT_TWO;
		break;
	case OPTION_APET_TRANS_END:			//���� ���� �ð�
		nRet = STRING_TYPE_TRANS;
		break;
	case OPTION_ATTACK_BLIND:		// 53 ���� ����
	case OPTION_ATTACK_POISON:		// 54 �� ����
	case OPTION_DECREASE_SKILL_DELAY:// 58 ��ų��Ÿ�� ����
		nRet = STRING_TYPE_INTEGER;
		break;
	default:
		nRet = STRING_TYPE_INTEGER;
		break;
	}

	return nRet;
}

COLOR UtilHelp::GetRareItemColor(int iRareIndex, int nFlag, int OptionCount)
{
	bool bRareItem = false;
	int RareGrade = 0;

	if(  nFlag & ITEM_FLAG_RARE )
	{
		bRareItem = true;
		CItemRareOption* pItemRareOption = CItemRareOption::getData(iRareIndex);

		if (pItemRareOption )
			RareGrade = pItemRareOption->GetGrade();
	}		

	if (bRareItem)
	{
		if (OptionCount <= 0) // ��������� �ɼ� �̰���
			return DEF_UI_COLOR_RED;

		if (RareGrade >= 0 && RareGrade < Item_Rare_Grade_MAX)
		{
			const COLOR Color[Item_Rare_Grade_MAX] = {0x1C54CCFF, 0x20A51CFF, 0xE5E230FF, 0xB2FDB7FF, 0x01FDEEFF	};
			return Color[RareGrade];
		}
	}
	else // ���� �������� �ƴ� ���
	{
		if(nFlag & ITEM_FLAG_ORIGIN)
		{
			return 0xCC66FFFF; // ������ �������� ���
		}
		else
		{
			return DEF_UI_COLOR_WHITE; // ��� �������� ���
		}
	}
	
	return DEF_UI_COLOR_WHITE;
}
// COLOR	GetNasColor(SQUAD nNas)
// {
//		TO.DO pUIManager->GetNasColor() �� �ϴ� ��� ���� ����
// }
COLOR UtilHelp::GetReuseTimeColor(int Time)
{
	time_t CurrentTime = time(NULL);
	time_t Endtime	= (time_t)Time;
	time_t ReuseTime = Endtime - CurrentTime;

	if (ReuseTime > 0 && ReuseTime < ONE_DAY_SECOND)
	{
		return 0xFF0000FF;
	}
	else if (ReuseTime >= ONE_DAY_SECOND && ReuseTime < FIVE_DAY_SECOND)
	{
		return 0xFFFF00FF;
	}
	else if (ReuseTime >= FIVE_DAY_SECOND && ReuseTime < TEN_DAY_SECOND)
	{
		return 0xFFCC00FF;
	}
	else if (ReuseTime >= TEN_DAY_SECOND)
	{
		return 0xFFFFFFFF;
	}
	else
	{
		return 0x00000000;
	}
}

CTString UtilHelp::GetCalcStringEllipsis(CTString strText, ULONG ulColumnWidth, CTString strEllipsis)
{
	if (ulColumnWidth == -1)
		return strText;

	if (g_iCountry != RUSSIA)
	{
		CDrawPort* pDrawPort = CUIManager::getSingleton()->GetDrawPort();

		if (pDrawPort == NULL)
			return strText;

		ULONG ulWidth = pDrawPort->GetTextWidth2(strText);
		if (ulWidth <= ulColumnWidth)
			return strText;

		char szTemp[4];
		int len = strText.Length(), pos = 0;
		ulWidth = pDrawPort->GetTextWidth2(strEllipsis);
		for (int i = 0, j = 0; i < len; j = 0)
		{
			if (IsDBCSLeadByte(strText[i]))
				szTemp[j++] = strText[i++];
			szTemp[j++] = strText[i++];
			szTemp[j] = 0;
			ULONG ulTempWidth = pDrawPort->GetTextWidth2(CTString(szTemp));
			if (ulWidth + ulTempWidth > ulColumnWidth)
				break;
			ulWidth += ulTempWidth;
			pos = i;
		}
		strText.DeleteChars(pos, len - pos);
	}
	else
	{
		extern CFontData *_pfdDefaultFont;

		ULONG ulWidth = UTIL_HELP()->GetNoFixedWidth(_pfdDefaultFont, strText.str_String);
		if (ulWidth <= ulColumnWidth)
			return strText;

		char szTemp[4];
		int len = strText.Length(), pos = 0;
		ulWidth = UTIL_HELP()->GetNoFixedWidth(_pfdDefaultFont, strEllipsis.str_String);
		for (int i = 0, j = 0; i < len; j = 0)
		{
			if (IsDBCSLeadByte(strText[i]))
				szTemp[j++] = strText[i++];
			szTemp[j++] = strText[i++];
			szTemp[j] = 0;
			ULONG ulTempWidth = UTIL_HELP()->GetNoFixedWidth(_pfdDefaultFont, szTemp);
			if (ulWidth + ulTempWidth > ulColumnWidth)
				break;
			ulWidth += ulTempWidth;
			pos = i;
		}
		strText.DeleteChars(pos, len - pos);
	}

	return strText + strEllipsis;
}

CTString UtilHelp::GetClassName( eJob eClass )
{
	CTString	retStr = "none";
	switch (eClass)
	{
	case TITAN:
		retStr = _S(43, TITAN);
		break;
	case KNIGHT:
		retStr = _S(44, KNIGHT);
		break;
	case HEALER:
		retStr = _S(45, HEALER);
		break;
	case MAGE:
		retStr = _S(46, MAGE);
		break;
	case ROGUE:
		retStr = _S(47, ROGUE);
		break;
	case SORCERER:
		retStr = _S(48, SORCERER);
		break;
	case NIGHTSHADOW:
		retStr = _S(4410, NIGHTSHADOW);
		break;
#ifdef CHAR_EX_ROGUE
	case EX_ROGUE:
		retStr = _S(5732, EX_ROGUE);
		break;
#endif	// CHAR_EX_ROGUE
#ifdef CHAR_EX_MAGE	
	case EX_MAGE:
		retStr = _S(5820, EX_MAGE);
		break;
#endif	// CHAR_EX_MAGE
	}

	return retStr;	
}

CTString UtilHelp::GetWeaponName( CItemData::ITEMWEAPONTYPE eType )
{
	CTString strRet;

	switch (eType)
	{
	case CItemData::ITEM_WEAPON_KNIFE:
		strRet = _S(1038, "��絵");
		break;
	case CItemData::ITEM_WEAPON_CROSSBOW:
		strRet = _S(1039, "����");
		break;
	case CItemData::ITEM_WEAPON_STAFF:
		strRet = _S(1040, "������");
		break;
	case CItemData::ITEM_WEAPON_BIGSWORD:
		strRet = _S(1041, "���");
		break;
	case CItemData::ITEM_WEAPON_AXE:
		strRet = _S(1042, "����");
		break;
	case CItemData::ITEM_WEAPON_SSTAFF:
		strRet = _S(1043, "��������");
		break;
	case CItemData::ITEM_WEAPON_BOW:
		strRet = _S(1044, "Ȱ");
		break;
	case CItemData::ITEM_WEAPON_DAGGER:
		strRet = _S(1045, "�ܰ�");
		break;
	case CItemData::ITEM_WEAPON_MINING:
		strRet = _S(4270, "ä������");
		break;
	case CItemData::ITEM_WEAPON_GATHERING:
		strRet = _S(4271, "ä������");
		break;
	case CItemData::ITEM_WEAPON_CHARGE:
		strRet = _S(4272, "��������");
		break;
	case CItemData::ITEM_WEAPON_TWOSWORD:
		strRet = _S(1046, "�̵���");
		break;
	case CItemData::ITEM_WEAPON_WAND:
		strRet = _S(1047, "�ϵ�");
		break;
	case CItemData::ITEM_WEAPON_SCYTHE:
		strRet = _S(2306, "���̵�");
		break;
	case CItemData::ITEM_WEAPON_POLEARM:
		strRet = _S(2307, "����");
		break;
	case CItemData::ITEM_WEAPON_SOUL:
		strRet = _S(4614, "ȥ");
		break;
	}

	return strRet;
}

CTString UtilHelp::GetSheildName( CItemData::ITEMSHIELDTYPE eType )
{
	CTString retStr = "none";

	switch (eType)
	{
	case CItemData::ITEM_SHIELD_HEAD:
		retStr = _S(142, "�Ӹ�");
		break;
	case CItemData::ITEM_SHIELD_COAT:
		retStr = _S(4273, "����");
		break;
	case CItemData::ITEM_SHIELD_PANTS:	
		retStr = _S(4274, "����");
		break;
	case CItemData::ITEM_SHIELD_GLOVE:
		retStr = _S(4275, "�尩");
		break;
	case CItemData::ITEM_SHIELD_SHOES:
		retStr = _S(4276, "�Ź�");
		break;
	case CItemData::ITEM_SHIELD_SHIELD:
		retStr = _S(4277, "����");
		break;
	case CItemData::ITEM_SHIELD_BACKWING:
		retStr = _S(5916, "��");
		break;
	}

	return retStr;
}

bool UtilHelp::GetNasStringColor(__int64 nas, CTString& str, COLOR& color )
{
	str.PrintF( "%I64d", nas );

	CUIManager* pUIMgr = CUIManager::getSingleton();
	pUIMgr->InsertCommaToString( str );

	color = pUIMgr->GetNasColor( nas );

	return true;
}

CTString UtilHelp::GetP1PetName( int nDBIdx, int nPlus )
{
	CUIManager* pUIManager = CUIManager::getSingleton();
	SBYTE sbPetTypeGrade = pUIManager->GetPetInfo()->GetPetTypeGrade( nPlus );

	CTString strItemName =_pNetwork->GetItemName( nDBIdx );

	if( sbPetTypeGrade > 0 )
	{
		INDEX iPetType;
		INDEX iPetAge;
		_pNetwork->CheckPetType( sbPetTypeGrade, iPetType, iPetAge );
		strItemName += CTString(" - ") + PetInfo().GetName(iPetType, iPetAge);
	}

	return strItemName;
}

CTString UtilHelp::GetWearPosName(int nWearPos, eWEAR_TYPE eType/*= WEAR_TYPE_NONE*/)
{
	CTString WearPosName = CTString("");
	
	switch (eType)
	{
	case WEAR_TYPE_NONE:
		{
			if ( nWearPos < 0 || nWearPos >= WEAR_TOTAL)
				return WearPosName;

			WearPosName.PrintF( _S( idx_WearSting[nWearPos], "��� ��ġ" ));
		}		
		break;

	case WEAR_TYPE_COSTUME:
		{
			if ( nWearPos < 0 || nWearPos >= WEAR_COSTUME_TOTAL)
				return WearPosName;

			WearPosName.PrintF( _S( idx_WearCostumeSting[nWearPos], "��� ��ġ" ));
		}		
		break;

	default:
		WearPosName.PrintF( _S( 3865, "����" ));
	}	

	return WearPosName;
}

CTString UtilHelp::GetClass2Name( eJob eClass, eJob2 eClass2 )
{
	CTString	retStr = "none";

	switch (eClass)
	{
	case TITAN:
		if (eClass2 == JOB_2ND_HIGHLANDER)
			retStr = _S(1190, "���̷���");
		else if (eClass2 == JOB_2ND_WARMASTER)
			retStr = _S(1191, "��������");
		break;
	case KNIGHT:
		if (eClass2 == JOB_2ND_ROYALKNIGHT)
			retStr = _S(1188, "�ο� ����Ʈ");
		else if (eClass2 == JOB_2ND_TEMPLEKNIGHT)
			retStr = _S(1189, "���� ����Ʈ");
		break;
	case HEALER:
		if (eClass2 == JOB_2ND_ARCHER)
			retStr = _S(1192, "��ó");
		else if (eClass2 == JOB_2ND_CLERIC)
			retStr = _S(1193, "Ŭ����");
		break;
	case MAGE:
		if (eClass2 == JOB_2ND_WIZARD)
			retStr = _S(1194, "���ڵ�");
		else if (eClass2 == JOB_2ND_WITCH)
			retStr = _S(1195, "��ġ");
		break;
	case ROGUE:
		if (eClass2 == JOB_2ND_ASSASSIN)
			retStr = _S(1196, "��ؽ�");
		else if (eClass2 == JOB_2ND_RANGER)
			retStr = _S(1197, "������");
		break;
	case SORCERER:
		if (eClass2 == JOB_2ND_ELEMENTALIST)
			retStr = _S(2324, "������Ż ����Ʈ");
		else if (eClass2 == JOB_2ND_SPECIALIST)
			retStr = _S(2325, "����� ����Ʈ");
		break;
	case NIGHTSHADOW:
			retStr = "";
		break;
#ifdef CHAR_EX_ROGUE
	case EX_ROGUE:
		if (eClass2 == JOB_2ND_EX_ASSASSIN)
			retStr = _S(5734, "EX-��ؽ�");
		else if (eClass2 == JOB_2ND_EX_RANGER)
			retStr = _S(5735, "EX-������");
		break;
#endif	// CHAR_EX_ROGUE
#ifdef CHAR_EX_MAGE	
	case EX_MAGE:
		if (eClass2 == JOB_2ND_EX_WIZARD)
			retStr = _S(5822, "��ũ���ڵ�");
		else if (eClass2 == JOB_2ND_EX_WITCH)
			retStr = _S(5823, "��ũ��ġ");
		break;
#endif	// CHAR_EX_MAGE
	}

	return retStr;	
}

bool UtilHelp::nearMyCharacter( FLOAT3D vPos, float fDistance )
{
	FLOAT	fX = vPos(1) - _pNetwork->MyCharacterInfo.x;
	FLOAT	fZ = vPos(3) - _pNetwork->MyCharacterInfo.z;
	
	if (fX * fX + fZ * fZ <= fDistance)
		return true;

	return false;
}

UIMCType UtilHelp::GetPlayerAttackCursor( INDEX iPcType, BOOL bPcExtension )
{
	UIMCType cursorType = UMCT_ATT_NORMAL;

	if (iPcType == HEALER)	
	{
		if( bPcExtension != FALSE )
			cursorType = UMCT_ATT_MAGIC;
		else
			cursorType = UMCT_ATT_BOW;
	}
	else if (iPcType == MAGE ||	iPcType == SORCERER || iPcType == NIGHTSHADOW
#ifdef CHAR_EX_MAGE
		|| iPcType == EX_MAGE
#endif	//	CHAR_EX_MAGE
		)
	{
		cursorType = UMCT_ATT_MAGIC;
	}
	else if (iPcType == ROGUE 
#ifdef CHAR_EX_ROGUE
		|| iPcType == EX_ROGUE
#endif	//	CHAR_EX_ROGUE
		)
	{
		if( bPcExtension != FALSE )
			cursorType = UMCT_ATT_BOW;
		else
			cursorType = UMCT_ATT_NORMAL;
	}
	else
	{
		cursorType = UMCT_ATT_NORMAL;
	}

	return cursorType;
}

int UtilHelp::GetNationCode()
{
	extern INDEX g_iCountry;
	INDEX tv_idx;
	switch(g_iCountry)
	{
	case KOREA :		tv_idx = 0;		break;	

	case BRAZIL:		tv_idx = 10;	break;
	case MEXICO:		tv_idx = 20;	break;

	case GERMANY:		tv_idx = 13;	break;
	case SPAIN:			tv_idx = 14;	break;
	case FRANCE:		tv_idx = 15;	break;
	case POLAND:		tv_idx = 16;	break;	
	case ITALY:			tv_idx = 19;	break;
	case USA:			tv_idx = 9;		break;

	case RUSSIA:		tv_idx = 17;	break;

	case THAILAND :		tv_idx = 4;		break;
	default:			
		tv_idx = g_iCountry;	// ENGLAND
		break;
	}

	return tv_idx;
}

CTString UtilHelp::GetAttributeString( int nNum )
{
	CTString strAtt;

	switch(nNum)
	{
	case 0:		strAtt = _S( 5852, "��");		break;
	case 1:		strAtt = _S( 5846, "��");		break;
	case 2:		strAtt = _S( 5847, "��");		break;
	case 3:		strAtt = _S( 5849, "����");		break;
	case 4:		strAtt = _S( 5848, "�ٶ�");		break;
	case 5:		strAtt = _S( 5850, "����");		break;
	case 6:		strAtt = _S( 5851, "��");		break;
	default:	strAtt = CTString("");			break;
	}

	return strAtt;
}

int UtilHelp::CheckNoFixedLength( CFontData* pFont, char* strString, int nWidth, bool bPasswd /*= false*/ )
{
	// ��Ʈ ����Ÿ Ȯ��
	if (pFont == NULL)
		return 0;

	PIX pixCharStart = 0, pixCharEnd = 0;
	PIX pixTextCharSpacing = pFont->GetCharSpacing();

	int nStrCount = 0;
	int nStringWidth = 0;
	UBYTE ubcurrChar;

	int i;
	int nStrLength = strlen(strString);

	for (i = 0; i < nStrLength; ++i)
	{
		if (bPasswd == true)
			ubcurrChar = '*'; // �佺�������ϰ�� ������ ����
		else
			ubcurrChar = strString[i];

		// ��Ʈ�� ������ ���
		pixCharStart = pFont->fd_fcdFontCharData[ubcurrChar].fcd_pixStart;
		pixCharEnd   = pFont->fd_fcdFontCharData[ubcurrChar].fcd_pixEnd;

		if (nStringWidth < nWidth)
		{
			nStringWidth += (( pixCharEnd - pixCharStart ) + pixTextCharSpacing);
			nStrCount++;
		}
		else
		{
			break;
		}
	}

	return nStrCount;
}

int UtilHelp::CheckNoFixedLengthUsa(char* strString, int nWidth, bool bPasswd /*= false*/)
{
	PIX pixCharStart = 0, pixCharEnd = 0;
	PIX pixTextCharSpacing = _pUIFontTexMgr->GetFontSpacing();
	int nStrCount = 0;
	int nStringWidth = 0;
	UBYTE ubcurrChar;
	int i;
	int nStrLength = strlen(strString);
	for (i = 0; i < nStrLength; ++i)
	{
		if (bPasswd == true)
			ubcurrChar = '*';
		else
			ubcurrChar = strString[i];
		if (nStringWidth < nWidth)
		{
			nStringWidth += _pUIFontTexMgr->GetFontWidth() + pixTextCharSpacing;
			nStrCount++;
		}
		else
		{
			break;
		}
	}
	return nStrCount;
}
int UtilHelp::GetNoFixedWidth( CFontData* pFont, char* strString )
{
	// ��Ʈ ����Ÿ Ȯ��
	if (pFont == NULL)
		return 0;

	PIX pixCharStart = 0, pixCharEnd = 0;
	PIX pixTextCharSpacing = pFont->GetCharSpacing();

	int nStringWidth = 0;
	UBYTE ubcurrChar;

	int i;
	int nStrLength = strlen(strString);

	for (i = 0; i < nStrLength; ++i)
	{
		ubcurrChar = strString[i];
		// ��Ʈ�� ������ ���
		pixCharStart = pFont->fd_fcdFontCharData[ubcurrChar].fcd_pixStart;
		pixCharEnd   = pFont->fd_fcdFontCharData[ubcurrChar].fcd_pixEnd;

		nStringWidth += (( pixCharEnd - pixCharStart ) + pixTextCharSpacing);
	}

	return nStringWidth;
}

int UtilHelp::GetFontWidth( char* strString, CFontData* pFont /*= NULL*/ )
{
	int ret = 0;	

	std::string str = strString;

	if (g_iCountry != RUSSIA)
	{
		int nFontWidth = _pUIFontTexMgr->GetFontWidth() + _pUIFontTexMgr->GetFontSpacing();

		ret = str.size() * nFontWidth;
	}
	else
	{
		CFontData* pData = pFont;

		if (pData == NULL)
			pData = _pfdDefaultFont;
		// RUSSIA
		ret = GetNoFixedWidth(pData, strString);
	}

	return ret;
}
int UtilHelp::GetNoFixedWidthUsa(char* strString)
{
	PIX pixCharStart = 0, pixCharEnd = 0;
	PIX pixTextCharSpacing = _pUIFontTexMgr->GetFontSpacing();
	int nStringWidth = 0;
	UBYTE ubcurrChar;
	int i;
	int nStrLength = strlen(strString);
	for (i = 0; i < nStrLength; ++i)
	{
		ubcurrChar = strString[i];
		nStringWidth += (GetWithCharUsa(ubcurrChar) + pixTextCharSpacing);
	}
	return nStringWidth;
}
int UtilHelp::GetWithCharUsa(char str)
{
	int pixWidth = 0;
	switch (str)
	{
	case 0x21: // 3
	case 0x27:
	case 0x2C:
	case 0x2E:
	case 0x3A:
	case 0x3B:
	case 0x49:
	case 0x60:
	case 0x69:
	case 0x6A:
	case 0x6C:
		pixWidth = 5;
		break;
	case 0x28: // 4
	case 0x29:
	case 0x4A:
	case 0x5B:
	case 0x5D:
	case 0x66:
	case 0x72:
	case 0x74:
		pixWidth = 4;
		break;
	case 0x22: // 5
	case 0x2A:
	case 0x2D:
	case 0x2F:
	case 0x5F:
	case 0x73:
		pixWidth = 5;
		break;
	case 0x3F: // 6
	case 0x45:
	case 0x46:
	case 0x4C:
	case 0x54:
	case 0x61:
	case 0x63:
	case 0x65:
	case 0x6B:
	case 0x76:
	case 0x78:
	case 0x79:
	case 0x7A:
	case 0x20: // Space
		pixWidth = 6;
		break;
	case 0x23: // 7
	case 0x24:
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x42:
	case 0x4B:
	case 0x50:
	case 0x52:
	case 0x53:
	case 0x58:
	case 0x59:
	case 0x5A:
	case 0x62:
	case 0x64:
	case 0x67:
	case 0x68:
	case 0x6E:
	case 0x70:
	case 0x71:
	case 0x75:
	case 0x6F: // o
		pixWidth = 7;
		break;
	case 0x2B: // 8
	case 0x3C:
	case 0x3D:
	case 0x3E:
	case 0x43:
	case 0x47:
	case 0x55:
	case 0x56:
	case 0x5E:
	case 0x41: // A
		pixWidth = 8;
		break;
	case 0x44: // 9
	case 0x48:
	case 0x4E:
	case 0x4F:
	case 0x51:
	case 0x77:
		pixWidth = 9;
		break;
	case 0x25: // 10
	case 0x26:
		pixWidth = 10;
		break;
	case 0x4D: // 11
	case 0x57:
	case 0x6D:
		pixWidth = 11;
		break;
	case 0x40: // 12
		pixWidth = 12;
		break;
	}
	return pixWidth;
}

COLOR UtilHelp::GetColorContrast(const float fLevel, const COLOR col)
{
	float	fAlphaLevel	= fLevel;
	if(fAlphaLevel < 0.0f)
		fAlphaLevel		= 0.0f;
	else if(fAlphaLevel > 1.0f)
		fAlphaLevel		= 1.0f;

	BYTE	rCol		= ((col & 0xFF000000) >> 24) * fAlphaLevel;
	BYTE	gCol		= ((col & 0x00FF0000) >> 16) * fAlphaLevel;
	BYTE	bCol		= ((col & 0x0000FF00) >> 8) * fAlphaLevel;
	BYTE	aCol		= (col & 0x000000FF);					//(col & 0x000000FF) * fLevel;
	return (rCol << 24) | (gCol << 16) | (bCol << 8) | aCol;
}

COLOR UtilHelp::GetColorAlpha(const float fLevel, const COLOR col)
{
	float	fAlphaLevel	= fLevel;
	if(fAlphaLevel < 0.0f)
		fAlphaLevel		= 0.0f;
	else if(fAlphaLevel > 1.0f)
		fAlphaLevel		= 1.0f;

	return (col & 0xFFFFFF00) | (ULONG)(0xFF * fAlphaLevel);
}
COLOR UtilHelp::GetTargetNameColor( int nIndex )
{
	COLOR colTargetName[] = {
	 0xCE4900FF	,0xD7AA00FF	,0xC5C5C5FF	,0x5B9900FF	,0x008BAAFF // Mob
	,0xE18600FF		// Npc
	,0x06C1FFFF	,0x0066FFFF	,0xFFFFFFFF	,0xABABABFF	,0xFF1E00FF	,0xBB3B00FF // Title, PK
	,0x00FF00FF	,0xF9EF2FFF // ���� �뺴 ī��
#ifdef NEW_CHAO_SYS
	,0x0070C0FF ,0x95B3D7FF	,0xDBE5F1FF	,0xFFCCCCFF	,0xFF6600FF	,0xFF0000FF
	, 0xcc9900FF/*Admin Gold*/, 0x0066ffFF/* Dark Blue*/, 0xFF0000FF/*Red*/,0xcc0099FF,/*Purple*/ 0x33cc33FF,/*green*/
	0x00ffffFF,/*LightBlue*/ 0xff9900FF,/*Orange*/ 0xff66ccFF /*Pink*/
#endif
	};

	return colTargetName[nIndex];
}

void UtilHelp::GetBtnTextureInfo( UIBtnExType eType, int nTexID, int nRow, int nCol, UIRectUV &uv )
{
	float fTexWidth = _pUIBtnTexMgr->GetTexWidth( eType, nTexID );
	float fTexHeight = _pUIBtnTexMgr->GetTexHeight( eType, nTexID );

	int	nUVSX = BTN_SIZE * nCol;
	int	nUVSY = BTN_SIZE * nRow;

	uv.U0 = nUVSX;
	uv.V0 = nUVSY;
	uv.U1 = nUVSX + BTN_SIZE;
	uv.V1 = nUVSY + BTN_SIZE;
}

bool UtilHelp::IsSpecialChar( char* pChars )
{
	std::string		strTmp = pChars;

	if (strTmp.empty() == true)
		return false;

	int i, len = strTmp.size();

	for (i = 0; i < len; ++i)
	{
		if( strTmp[i] == '\t' || strTmp[i] == '\n' ||
			strTmp[i] == '\r' || strTmp[i] == '%' )
			return true;
	}

	return false;
}

CTString UtilHelp::GetOptionPaciveInfo(SBYTE sbOptionType, LONG lOptionLevel, LONG lOriginOptionVar /* = ORIGIN_VAR_DEFAULT*/)
{
	CTString strTemp;

	COptionData*	odItem = COptionData::getData(sbOptionType);

	if (odItem == NULL )
		return CTString("");

	// alanssoares - max option grade-reform
	LONG fMaxOption = 190;

	if (UtilHelp* pHelp = UtilHelp::getSingleton())
	{
		switch (pHelp->GetPaciveOptionType(sbOptionType))
		{
		case STRING_TYPE_INTEGER:
			{
				int option = (odItem->GetValue(lOptionLevel - 1) * lOriginOptionVar) / 100;
				#ifdef ENABLE_MAX_OPTION_ITEM
				int max = (odItem->GetValue(lOptionLevel - 1) * fMaxOption) / 100;
				strTemp.PrintF("%s %d (Max.%d)", odItem->GetName(), option, max, lOriginOptionVar);
				#else
				strTemp.PrintF("%s %d", odItem->GetName(), option, lOriginOptionVar);
				#endif
			}
			break;
		case STRING_TYPE_NEGATIVE:
			{
				int option = odItem->GetValue(lOptionLevel - 1);
				#ifdef ENABLE_MAX_OPTION_ITEM
				int max = odItem->GetValue(lOptionLevel - 1) * fMaxOption / 100;
				strTemp.PrintF("%s -%d (Max.%d)", odItem->GetName(), option, max);
				#else
				strTemp.PrintF("%s -%d", odItem->GetName(), option);
				#endif

			}
			break;
		case STRING_TYPE_PERCENT:
			{
				int option = (odItem->GetValue(lOptionLevel - 1) * lOriginOptionVar) / 100;
				#ifdef ENABLE_MAX_OPTION_ITEM
				int max = (odItem->GetValue(lOptionLevel - 1) * fMaxOption) / 100;
				strTemp.PrintF("%s %d%% (Max.%d%%)", odItem->GetName(), option, max, lOriginOptionVar);
				#else
				strTemp.PrintF("%s %d%%", odItem->GetName(), option, lOriginOptionVar);
				#endif
			}
			break;

		case STRING_TYPE_FLOAT_POINT_ONE:
			{
				float option = ((odItem->GetValue(lOptionLevel - 1)  * lOriginOptionVar) / 100) / 10.0f;
				#ifdef ENABLE_MAX_OPTION_ITEM
				float max = ((odItem->GetValue(lOptionLevel - 1)  * fMaxOption) / 100) / 10.0f;
				strTemp.PrintF("%s %.1f (Max.%1.f)", odItem->GetName(), option, max, lOriginOptionVar );
				#else
				strTemp.PrintF("%s %.1f", odItem->GetName(), option, lOriginOptionVar );
				#endif
			}
			break;
		case STRING_TYPE_FLOAT_POINT_TWO:
			{
				float option = ((odItem->GetValue(lOptionLevel - 1) * lOriginOptionVar) / 100) / 100.0f;
				#ifdef ENABLE_MAX_OPTION_ITEM
				float max = ((odItem->GetValue(lOptionLevel - 1) * fMaxOption) / 100) / 100.0f;
				strTemp.PrintF("%s %.2f (Max.%2.f)", odItem->GetName(), option, max);
				#else
				strTemp.PrintF("%s %.2f", odItem->GetName(), option);
				#endif
			}
			break;
		}
	}

	return strTemp;
}

CTString UtilHelp::GetOptionActiveSkillInfo(CItemData* pItemData)
{
	if (pItemData == NULL)
		return CTString("");

	CTString strTemp;
	LONG		lSkillIndex;
	LONG		lSkillProb;

	lSkillIndex = pItemData->GetSocketOptionIndex();
	lSkillProb = pItemData->GetSocketOptionLevel(); // ���� ��� �ߵ� Ȯ���� ��
	CSkill& SkillItem = _pNetwork->GetSkillData(lSkillIndex);

	strTemp.PrintF("%s : %s %.2f%%", pItemData->GetName(), SkillItem.GetName(), lSkillProb / 100.0f);
	return strTemp;
}

int UtilHelp::GetZoneByNpcIndex(int nNPCIndex)
{
	CNpcHelp::_map::iterator	iter = CNpcHelp::_mapdata.begin();
	CNpcHelp::_map::iterator	eiter = CNpcHelp::_mapdata.end();

	for (;iter != eiter; ++iter)
	{
		CNpcHelp* pNpc = (*iter).second;

		if (pNpc == NULL)
			continue;

		if (pNpc->getNpcIndex() == nNPCIndex)
			return pNpc->zoneNum;
	}

	return -1;
}

int UtilHelp::GetZoneByMobIndex(int nMobIndex)
{
	CMobHelp::_map::iterator	iter1 = CMobHelp::_mapdata.begin();
	CMobHelp::_map::iterator	eiter1 = CMobHelp::_mapdata.end();

	for (;iter1 != eiter1; ++iter1)
	{
		CMobHelp* pMob = (*iter1).second;

		if (pMob == NULL)
			continue;

		if (pMob->getNpcIndex() == nMobIndex)
			return pMob->zoneNum;
	}

	return -1;
}

bool UtilHelp::IsAvailable4Sale( CItems* pItem, UI_TYPE eType )
{
	if (pItem == NULL)
		return false;

	CItemData* pItemData = pItem->ItemData;

	if (pItemData == NULL)
		return false;

	bool bSubJob = false;

#ifdef ADD_SUBJOB
	bSubJob = true;
#endif

	if (pItem->IsFlag(FLAG_ITEM_BELONG))
		return false;

	if (pItemData->GetType() == CItemData::ITEM_ACCESSORY &&
		pItemData->GetSubType() == CItemData::ACCESSORY_RELIC)
		return false;

	if (bSubJob == true && pItemData->IsFlag( ITEM_FLAG_SELLER ))
	{
		if (!UIMGR()->CheckSellerItem(eType, pItemData->GetFlag()))
			return false;
	}
	else
	{
		bool bMonsterMercenaryItem = false; 

		if (pItemData->GetType() == CItemData::ITEM_ETC &&
			pItemData->GetSubType() == CItemData::ITEM_ETC_MONSTER_MERCENARY_CARD)
		{
			bMonsterMercenaryItem = true;
		}

		if (!pItemData->IsFlag(ITEM_FLAG_EXCHANGE)||
			pItem->IsFlag(FLAG_ITEM_LENT) ||
			pItem->IsFlag(FLAG_ITEM_PLATINUMBOOSTER_ADDED) ||
			pItem->Item_Wearing > 0 || 
			( bMonsterMercenaryItem && pItem->Item_Used > 0 ))
			return false;
	}

	return true;
}