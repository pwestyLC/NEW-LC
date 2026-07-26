
#ifndef		_UTIL_HELP_H_
#define		_UTIL_HELP_H_

#include <Engine/DesignClasses/Singleton/SingletonBase.h>
#include <Engine/GlobalDefinition.h>
#include <Engine/Entities/ItemData.h>
#include <Engine/Entities/OptionData.h>
#include <Engine/Interface/UIDefine.h>
#include <Engine/Interface/UICommon.h>

enum eOPTION_TYPE
{
	OPTION_TYPE_ERROR = -1,
	OPTION_TYPE_PACIVE = 0,
	OPTION_TYPE_ACTIVE = 1,
};

enum eOPTION_STRING_TYPE
{
	STRING_TYPE_ERROR = -1,
	STRING_TYPE_INTEGER = 0,	// ����
	STRING_TYPE_NEGATIVE = 1,	// ����
	STRING_TYPE_PERCENT = 2,	// %
	STRING_TYPE_FLOAT_POINT_ONE = 3,	// 0.1f  
	STRING_TYPE_FLOAT_POINT_TWO = 4,	// 0.01f
	STRING_TYPE_TRANS = 5,		// ���� ����
};

enum eREUSE_TIME_TYPE
{
	REUSE_SEC,
	REUSE_MIN,
	REUSE_HOUR,
	REUSE_DAY,
};

enum eWEAR_TYPE
{
	WEAR_TYPE_NONE = 0, // �Ϲ� ��� 
	WEAR_TYPE_COSTUME,	// �ڽ�Ƭ ���
};

enum UIMCType;
enum UI_TYPE;
class CItems;

class UtilHelp : public CSingletonBase< UtilHelp >
{
public:
	UtilHelp();
	~UtilHelp();

	eOPTION_TYPE GetOptionType(int nOptionType);
	eOPTION_STRING_TYPE GetPaciveOptionType(int nOptionType);

	//string color

	// Express System //
	COLOR	GetRareItemColor(int iRareIndex, int nFlag, int OptionCount);
//	COLOR	GetNasColor(SQUAD nNas);
	COLOR	GetReuseTimeColor(int Time);
	CTString GetCalcStringEllipsis( CTString strText, ULONG ulColumnWidth, CTString strEllipsis );
	bool	GetNasStringColor(__int64 nas, CTString& str, COLOR& color);
	CTString GetClassName(eJob eClass);
	CTString GetClass2Name(eJob eClass, eJob2 eClass2 );
	CTString GetWeaponName(CItemData::ITEMWEAPONTYPE eType);
	CTString GetSheildName(CItemData::ITEMSHIELDTYPE eType);
	CTString GetWearPosName(int nWearPos, eWEAR_TYPE eType = WEAR_TYPE_NONE);

	CTString GetP1PetName( int nDBIdx, int nPlus );

	bool nearMyCharacter(FLOAT3D vPos, float fDistance);
	ENGINE_API UIMCType GetPlayerAttackCursor(INDEX iPcType, BOOL bPcExtension);

	int		GetNationCode();
	CTString GetAttributeString(int nNum);
	// ���� ��Ʈ - nWidth�� ��� ������ ���ڱ��� ���
	int CheckNoFixedLength(CFontData* pFont, char* strString, int nWidth, bool bPasswd = false);
	int CheckNoFixedLengthUsa(char* strString, int nWidth, bool bPasswd = false);
	int	GetNoFixedWidth(CFontData* pFont, char* strString);
	int	GetNoFixedWidthUsa(char* strString);
	int GetWithCharUsa(char str);

	int GetFontWidth(char* strString, CFontData* pFont = NULL);

	COLOR GetColorContrast(const float fLevel, const COLOR col);		// fLevel : 0.0 ~ 1.0
	COLOR GetColorAlpha(const float fLevel, const COLOR col);			// fLevel : 0.0 ~ 1.0

	COLOR GetTargetNameColor(int nIndex);

	void GetBtnTextureInfo( UIBtnExType eType, int nTexID, int nRow, int nCol, UIRectUV &uv);
	bool IsSpecialChar(char* pChars);

	CTString GetOptionPaciveInfo(SBYTE sbOptionType, LONG lOptionLevel, LONG lOriginOptionVar = ORIGIN_VAR_DEFAULT);
	CTString GetOptionActiveSkillInfo(CItemData* pItemData);

	int GetZoneByNpcIndex(int nNPCIndex);
	int GetZoneByMobIndex(int nMobIndex);

	bool	IsAvailable4Sale(CItems* pItem, UI_TYPE eType);
};

#define		UTIL_HELP()					UtilHelp::getSingleton()

#endif		// _UTIL_HELP_H_