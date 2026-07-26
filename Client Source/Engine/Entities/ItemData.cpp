
#include "stdh.h"

#include <Engine/Templates/StaticArray.cpp>
#include <Engine/Entities/ItemData.h>
#include <Engine/Network/CNetwork.h>
#include <Engine/Interface/UIManager.h>
#include <Engine/Secure/FileSecure.h>	// [2012/07/18 : Sora]  ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Úµï¿½ ï¿½ß°ï¿½


#define LOAD_ITEMARMOR_EFFECT

// [2010/10/20 : Sora] 
#define  MERCENARY_CARD_HOLDER_MAX 4
const int mercenary_card_holder[MERCENARY_CARD_HOLDER_MAX] = {6251, 6256, 6257, 6258};

/*
 *  Constructor.
 */
CItemData::CItemData(void)
:Item_MeshCnt(0), Item_TexCnt(0), Item_Tex2Cnt(0)
{
	//memset(&Item_Data, 0, sizeof(_ItemStat));
	ZeroMemory(&fileBm,255);
	ZeroMemory(&fileTex,255);
	ZeroMemory(&fileTexNormal,255);
	ZeroMemory(&fileBm2,255);
	ZeroMemory(&fileTex2,255);
	ZeroMemory(&fileTex2Normal,255);
	ZeroMemory(&fileBm3,255);
	ZeroMemory(&fileTex3,255);
	ZeroMemory(&fileTex3Normal,255);
	bCreateSet = FALSE;

	StartTime = 0.0;
}

/*
 *  Destructor.
 */
CItemData::~CItemData(void) 
{
	
}

CItemData& CItemData::operator=(const CItemData& data)
{
	name = data.name;
	descr = data.descr;
	return *this;
}

//-----------------------------------------------------------------------------
// Purpose: ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Í¸ï¿½ ï¿½ï¿½ï¿½Ï·Îºï¿½ï¿½ï¿½ ï¿½Ð¾ï¿½ï¿½ï¿½Ô´Ï´ï¿½.
// Input  : &apItemData - ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½è¿­.
//			FileName - ï¿½ï¿½ï¿½Ï¸ï¿½.
// Output : 	static int
//-----------------------------------------------------------------------------
int CItemData::LoadJewelItemDataFromFile(CStaticArray<JewelComosInfo> &apJewelData, const char* FileName)
{
	FILE *fp		= NULL;

	if ((fp = fopen(FileName, "rb")) == NULL) 
	{
		CTString msg; msg.PrintF("File is not Exist: %s", FileName); MessageBox(NULL, msg, "error!", MB_OK);
		return -1;
	}

	int iLastGradeIndex;
	int iLength			= -1;
	int iReadBytes		= 0;

//	fflush(fp);
	iReadBytes = fread(&iLastGradeIndex, sizeof(int), 1, fp);				// JewelComposï¿½ï¿½ï¿½ï¿½Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½Ìºï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
	apJewelData.New(iLastGradeIndex); 
	ASSERT(apJewelData.Count() >= iLastGradeIndex && "Invalid Array Count");
	ASSERT(iLastGradeIndex > 0 && "Invalid Item Data");
	//////////////////////////////////////////////////////////////////////////	
	// MACRO DEFINITION
	//////////////////////////////////////////////////////////////////////////	
#define LOADINT(d)			iReadBytes = fread(&d, sizeof(int), 1, fp);
#define LOADSHORT(d)		iReadBytes = fread(&d, sizeof(short), 1, fp);
#define LOADCHAR(d)			iReadBytes = fread(&d, sizeof(char), 1, fp);
#define LOADFLOAT(d)		iReadBytes = fread(&d, sizeof(float), 1, fp);
#define LOADSTR(d)			{ int iLen; LOADINT(iLen); iReadBytes = fread(&d, iLen, 1, fp); }
	//////////////////////////////////////////////////////////////////////////	
	
	for(int i = 0; i < iLastGradeIndex; ++i)
	{
		int iIndex = -1;
		LOADINT(iIndex);

		if(iReadBytes <= 0)		break;										// EOF
		ASSERT(iIndex != -1	&& "Invalid Item Index");

		JewelComosInfo& ID		= apJewelData[iIndex - 1];
		ID.index = iIndex;
		LOADINT(ID.nor_comp_nas);
		LOADINT(ID.ca_comp_nas);
		LOADINT(ID.ca_jew_create);
		LOADINT(ID.nor_comp_val);
		LOADINT(ID.ca_comp_val);
		LOADINT(ID.nor_up_2);
		LOADINT(ID.nor_up_3);
		LOADINT(ID.ca_up_2);
		LOADINT(ID.ca_up_3);
		LOADINT(ID.nor_down_1);
		LOADINT(ID.nor_down_2);
		LOADINT(ID.nor_down_3);
		LOADINT(ID.ca_down_1);
		LOADINT(ID.ca_down_2);
		LOADINT(ID.ca_down_3);
	}
	fclose(fp);
//////////////////////////////////////////////////////////////////////////	
#undef LOADINT
#undef LOADCHAR
#undef LOADFLOAT
#undef LOADSTR
	return iLastGradeIndex;
}

bool CItemData::loadItemEx(const char* FileName)
{	
	FILE*	fp = NULL;

	fp = fopen(FileName, "rb");

	if (fp == NULL)
		return false;

	fread(&_nSize, sizeof(int), 1, fp);

	if (_nSize <= 0)
	{
		fclose(fp);
		return false;
	}

	stItem* pdata = new stItem[_nSize];
	fread(pdata, sizeof(stItem) * _nSize, 1, fp);
	fclose(fp);

	for (int i = 0; i < _nSize; i++)
	{
		CItemData* ptmp = new CItemData;
		memcpy(ptmp, &pdata[i], sizeof(stItem));

		if (_mapdata.insert(std::make_pair(ptmp->getindex(), ptmp)).second == false)
		{
			delete ptmp;
			ptmp = NULL;
			continue;
		}

		_vecdata.push_back(ptmp);

		if(ptmp->type == ITEM_ETC && ( ptmp->subType == ITEM_ETC_JEWEL || ptmp->subType == ITEM_ETC_CHAOSJEWEL ) && ptmp->num3 > 0)
		{
			_vecJewelInfo vecJewelInfo;
			JewelInfo jewelinfo;
			jewelinfo.Jewel_idx = ptmp->getindex();
			jewelinfo.Jewel_composGrade = ptmp->num3;
			vecJewelInfo.push_back(jewelinfo);

			std::map<int, _vecJewelInfo>::iterator	iterJewelGradeInfo = _pNetwork->wo_mapJewelGradeInfo.find(ptmp->num0);
			std::map<int, _vecJewelInfo>::iterator	iterJewelGradeInfoEnd = _pNetwork->wo_mapJewelGradeInfo.end();

			if (iterJewelGradeInfo != iterJewelGradeInfoEnd)
			{
				iterJewelGradeInfo->second.push_back(jewelinfo);
			}
			else
			{
				_pNetwork->wo_mapJewelGradeInfo.insert(std::make_pair( ptmp->num0, vecJewelInfo));
			}

			if (ptmp->subType == ITEM_ETC_CHAOSJEWEL)
			{
				std::map<int, _vecJewelInfo>::iterator	iterChaosJewelGradeInfo = _pNetwork->wo_mapChaosJewelGradeInfo.find(ptmp->num0);
				std::map<int, _vecJewelInfo>::iterator	iterChaosJewelGradeInfoEnd = _pNetwork->wo_mapChaosJewelGradeInfo.end();

				if (iterChaosJewelGradeInfo != iterChaosJewelGradeInfoEnd)
				{
					iterChaosJewelGradeInfo->second.push_back(jewelinfo);
				}
				else
				{
					_pNetwork->wo_mapChaosJewelGradeInfo.insert(std::make_pair( ptmp->num0, vecJewelInfo));
				}
			}
		}
	}

	m_dummy = new CItemData; // ï¿½ï¿½ï¿½Ìµï¿½ï¿½ï¿½Å¸ ï¿½ï¿½ï¿½ï¿½
	memset(m_dummy, 0, sizeof(stItem));

	if (pdata != NULL)
	{
		delete[] pdata;
		pdata = NULL;
	}

	return true;
}


bool CFortuneData::loadFortuneEx( const char* FileName )
{
	FILE*	fp = NULL;

	fp = fopen(FileName, "rb");

	if (fp == NULL)
		return false;

	fread(&_nSize, sizeof(int), 1, fp);

	if (_nSize <= 0)
	{
		fclose(fp);
		return false;
	}

	stFortune* pdata = new stFortune[_nSize];
	fread(pdata, sizeof(stFortune) * _nSize, 1, fp);
	fclose(fp);

	for (int i = 0; i < _nSize; i++)
	{
		CFortuneData* ptmp = new CFortuneData;
		memcpy(ptmp, &pdata[i], sizeof(stFortune));
		
		if (_mapdata.insert(std::make_pair(i, ptmp)).second == false)
		{
			delete ptmp;
			ptmp = NULL;
		}
	}

	m_dummy = new CFortuneData; // ï¿½ï¿½ï¿½Ìµï¿½ï¿½ï¿½Å¸ ï¿½ï¿½ï¿½ï¿½
	memset(m_dummy, 0, sizeof(stFortune));

	if (pdata != NULL)
	{
		delete[] pdata;
		pdata = NULL;
	}

	return true;
}

//[sora] ï¿½Ì¹ï¿½ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ index Ç¥ï¿½ï¿½
void CItemData::SetNoTranslate()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->IsNotTranslated( TRANS_NAME, transFlag ) )
		SetName( CTString(0, "[%d] : item name", index) );

	if( pUIManager->IsNotTranslated( TRANS_DESC, transFlag ) )
		SetDesc( CTString(0, "[%d] : item desc", index) );
}

void CItemData::ClearNoTranslate()
{
	CUIManager* pUIManager = CUIManager::getSingleton();

	if( pUIManager->IsNotTranslated( TRANS_NAME, transFlag ) )
		SetName("");

	if( pUIManager->IsNotTranslated( TRANS_DESC, transFlag ) )
		SetDesc("");
}



static float fN = pow( 1.06, 12 );
int nLordItmeIndex[CItemData::LORD_ITEM_TOTAL] = { 861, 862, 863, 864, 865, 866, 867, 868, 869, 870, 1070,1071};

int	CItemData::GetPhysicalAttack()
{	
	if( !IsFlag( ITEM_FLAG_LORD ) && !IsFlag(ITEM_FLAG_PHOENIX) ) return num0;
	//And OR? not sure yet need test
	int nLordLevel = _pNetwork->MyCharacterInfo.level;
	if(!IsFlag( PLATINUM_MAX_PLUS )) nLordLevel = nLordLevel > 15 ? 15 : nLordLevel;
	
	
	float fAttack = 0.0f;

	float	fIncrease = 0.0f;
	int		nBaseAttack = 0;
	bool 	isPhoenixWep = false;

	switch( index )
	{
	case 861:	// ï¿½ï¿½ï¿½
		fIncrease = 3.0f;
		nBaseAttack = 20;
		isPhoenixWep = false;
		break;
	case 862:	// ï¿½ï¿½ï¿½ï¿½
		fIncrease = 3.3f;
		nBaseAttack = 23;
		isPhoenixWep = false;
		break;
	case 863:	// ï¿½Ñ¼Õ°ï¿½  
		fIncrease = 2.4f;
		nBaseAttack = 16;
		isPhoenixWep = false;
		break;
	case 864:	// ï¿½Ìµï¿½ï¿½ï¿½
		fIncrease = 2.8f;
		nBaseAttack = 19;
		isPhoenixWep = false;
		break;
	case 865:	// È°
		fIncrease = 2.5f;
		nBaseAttack = 14;
		isPhoenixWep = false;
		break;
	case 869:	// ï¿½Ü°ï¿½
		fIncrease = 2.9f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 970:	// ï¿½ï¿½ï¿½ï¿½
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	//Phoenix Weapons
	case 12109: //sword
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12110: //dual sword
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12111: //giant sword
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12112: //axe
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12113://bow
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12117://dagger
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	case 12118://crossbow
		fIncrease = 2.5f;
		nBaseAttack = 10;
		isPhoenixWep = true;
		break;
	}
	
	if (isPhoenixWep)
	fAttack = ( nBaseAttack + ( nLordLevel - 1 ) * fIncrease ) * fN;
	else 
	fAttack = ( nBaseAttack + ( nLordLevel - 1 ) * fIncrease ) * fN;

	return fAttack;	
}

int	CItemData::GetMagicAttack()
{
	if( !IsFlag( ITEM_FLAG_LORD ) && !IsFlag(ITEM_FLAG_PHOENIX) ) return num1;
	//And OR? not sure yet need test

	int nLordLevel = _pNetwork->MyCharacterInfo.level;

	if(!IsFlag( PLATINUM_MAX_PLUS )) nLordLevel = nLordLevel > 15 ? 15 : nLordLevel;
	
	float fAttack = 0;

	float	fIncrease = 0.0f;
	int		nBaseAttack = 0;
	bool 	isPhoenixWep = false;
	switch( index )
	{
	case 866:	// ï¿½Ïµï¿½(ï¿½ï¿½ï¿½ï¿½)
		fIncrease = 1.9f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 867:	// ï¿½Ïµï¿½(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
		fIncrease = 3.5f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 868:	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		fIncrease = 3.0f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 1070:  // ï¿½ï¿½ï¿½Ìµï¿½
		fIncrease = 2.9f;
		nBaseAttack = 20;
		isPhoenixWep = false;
		break;
	case 1071:  // ï¿½ï¿½ï¿½ï¿½
		fIncrease = 2.5f;
		nBaseAttack = 18;
		isPhoenixWep = false;
		break;
	//Phoenix Weapons
	case 12114:	//wand
		fIncrease = 1.9f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 12115:	// staff
		fIncrease = 3.5f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 12116:	// wand m
		fIncrease = 3.0f;
		nBaseAttack = 10;
		isPhoenixWep = false;
		break;
	case 12119:  // scythe
		fIncrease = 2.9f;
		nBaseAttack = 20;
		isPhoenixWep = false;
		break;
	case 12120:  // fallarm
		fIncrease = 2.5f;
		nBaseAttack = 18;
		isPhoenixWep = false;
		break;
	}
	
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ì¿¡ï¿½ï¿½ ï¿½ï¿½ï¿½Ö¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ê·ï¿½ ï¿½ï¿½ï¿½Ý·ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
	if (isPhoenixWep)
	fAttack = ( nBaseAttack + ( nLordLevel - 1 ) * fIncrease ) *fN;
	//267 if user is level 40 and is sorcerer 
	//1055 if user is level 174 (needs tested to confirm)
	else 
	fAttack = ( nBaseAttack + ( nLordLevel - 1 ) * fIncrease ) *fN;

	return fAttack;	
	
}

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´ï¿½ï¿½ï¿½ ï¿½Ç´ï¿½
bool CItemData::IsLordItem( int nIndex )
{
	for( int i = 0; i < CItemData::LORD_ITEM_TOTAL; i++ )
	{
		if( nLordItmeIndex[i] == nIndex )
		{
			return true;
		}
	}
	return false;
}

// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´ï¿½ï¿½ï¿½ ï¿½Ç´ï¿½
bool CItemData::IsUniqueItem( int nIndex )
{
	if(nIndex == 887) return true;
	if(nIndex == 1280) return true;
	if(nIndex >= 907 && nIndex <= 947) return true;
	//dethunter12 unique item index. pheonix
	return false;
}

bool CItemData::IsPremiumPheonixItem( int nIndex )
{
	if(nIndex >= 12121 && nIndex <= 12151) return true;
	//dethunter12 unique item index. pheonix
	return false;
}

bool CItemData::IsMercenaryCardHolder()
{
	for( int i=0; i<MERCENARY_CARD_HOLDER_MAX; ++i )
	{
		if( mercenary_card_holder[i] == index )
			return true;
	}

	return false;
}

CItemRareOption::CItemRareOption()
{
}

CItemRareOption::~CItemRareOption()
{
	
}

//-----------------------------------------------------------------------------
// Purpose: ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½É¼ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï·Îºï¿½ï¿½ï¿½ ï¿½Ð¾ï¿½ï¿½ï¿½Ô´Ï´ï¿½.
//-----------------------------------------------------------------------------
bool CItemRareOption::loadEx(const char* FileName)
{
	FILE*	fp = NULL;

	fp = fopen(FileName, "rb");

	if (fp == NULL)
		return false;

	fread(&_nSize, sizeof(int), 1, fp);

	if (_nSize <= 0)
	{
		fclose(fp);
		return false;
	}

	stRareOption* pdata = new stRareOption[_nSize];
	fread(pdata, sizeof(stRareOption) * _nSize, 1, fp);
	fclose(fp);

	for (int i = 0; i < _nSize; i++)
	{
		CItemRareOption* ptmp = new CItemRareOption;
		memcpy(ptmp, &pdata[i], sizeof(stRareOption));
		if (_mapdata.insert(std::make_pair(ptmp->getindex(), ptmp)).second == false)
		{
			delete ptmp;
			ptmp = NULL;
		}
	}

	m_dummy = new CItemRareOption; // ï¿½ï¿½ï¿½Ìµï¿½ï¿½ï¿½Å¸ ï¿½ï¿½ï¿½ï¿½
	memset(m_dummy, 0, sizeof(stRareOption));

	if (pdata != NULL)
	{
		delete[] pdata;
		pdata = NULL;
	}

	return true;
}

//SET_ITEM_ADD				//[ttos_2009_5_22]: ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
CSetItemData::CSetItemData()
{
}

CSetItemData::~CSetItemData()
{
}

bool CSetItemData::loadSetItemEx(const char* FileName)
{
	FILE*	fp = NULL;

	fp = fopen(FileName, "rb");

	if (fp == NULL)
		return false;

	fread(&_nSize, sizeof(int), 1, fp);

	if (_nSize <= 0)
	{
		fclose(fp);
		return false;
	}

	stSetItem* pdata = new stSetItem[_nSize];
	fread(pdata, sizeof(stSetItem) * _nSize, 1, fp);
	fclose(fp);

	for (int i = 0; i < _nSize; i++)
	{
		CSetItemData* ptmp = new CSetItemData;
		memcpy(ptmp, &pdata[i], sizeof(stSetItem));
		if (_mapdata.insert(std::make_pair(ptmp->getindex(), ptmp)).second == false)
		{
			delete ptmp;
			ptmp = NULL;
		}
	}

	m_dummy = new CSetItemData; // ï¿½ï¿½ï¿½Ìµï¿½ï¿½ï¿½Å¸ ï¿½ï¿½ï¿½ï¿½
	memset(m_dummy, 0, sizeof(stSetItem));

	if (pdata != NULL)
	{
		delete[] pdata;
		pdata = NULL;
	}

	return true;
}

CMakeItemData::CMakeItemData()
{
	//ZeroMemory(this, 0);
	memset(this, 0 , sizeof(CMakeItemData));
	for (int i = 0; i < MAX_STUFF_ITEM; i++)
	{
		this->m_StuffItem[i].nStuff_Index = -1;
		this->m_StuffItem[i].nStuff_Count = 0;
	}

}

CMakeItemData::~CMakeItemData()
{
}

int CMakeItemData::LoadMakeItemFromFile(CStaticArray<CMakeItemData> &apMakeItem, const char* FileName)
{
	FILE *fp		= NULL;
	if ((fp = fopen(FileName, "rb")) == NULL) 
	{
		CTString msg; msg.PrintF("File is not Exist: %s", FileName); MessageBox(NULL, msg, "error!", MB_OK);
		return -1;
	}

	int iCount;
	int iReadBytes		= 0;
	
	iReadBytes = fread(&iCount, sizeof(int), 1, fp);				// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	apMakeItem.New(iCount);
	ASSERT(apMakeItem.Count() >= iCount && "Invalid Array Count");
	ASSERT(iCount > 0 && "Invalid SetItem Data");
	//////////////////////////////////////////////////////////////////////////	
	// MACRO DEFINITION
	//////////////////////////////////////////////////////////////////////////	
#define LOADINT(d)			iReadBytes = fread(&d, sizeof(int), 1, fp);
#define LOADSHORT(d)		iReadBytes = fread(&d, sizeof(short), 1, fp);
#define LOADCHAR(d)			iReadBytes = fread(&d, sizeof(char), 1, fp);
#define LOADFLOAT(d)		iReadBytes = fread(&d, sizeof(float), 1, fp);
#define LOADQUAD(d)			iReadBytes = fread(&d, sizeof(UQUAD), 1, fp);
#define LOADSTR(d)			{ int iLen; LOADINT(iLen); iReadBytes = fread(&d, iLen, 1, fp); }
	//////////////////////////////////////////////////////////////////////////	

	for(int i = 0; i < iCount; ++i)
	{
		CMakeItemData& temMakeData = apMakeItem[i];
		
		LOADINT(temMakeData.m_nFactory_Index);
		if(iReadBytes <= 0)		break;
		LOADSTR(temMakeData.m_strFactory_Name);
		LOADINT(temMakeData.m_nFactory_Type);
		LOADINT(temMakeData.m_nFactory_Subtype);
		LOADINT(temMakeData.m_nItemIndex);
		
		// [090904: selo] 팩토리 이름을 아이템 이름으로 설정한다.
		//				  기획에서 확장성을 두어 Factory_Name을 두었기에 
		//				  차후 변경될 가능성이 있다.
		CItemData* pItemData = _pNetwork->GetItemData(temMakeData.m_nItemIndex);

		if (pItemData == NULL || pItemData->GetItemIndex() < 0)
			continue;

		strcpy(temMakeData.m_strFactory_Name, pItemData->GetName()); 

		LOADQUAD(temMakeData.m_nMakeExp);
		LOADQUAD(temMakeData.m_nNeedExp);
		LOADQUAD(temMakeData.m_nNeedNas);
				
		for (int cont = 0; cont < MAX_STUFF_ITEM; ++cont)
		{
			LOADINT(temMakeData.m_StuffItem[cont].nStuff_Index);
			LOADINT(temMakeData.m_StuffItem[cont].nStuff_Count);
		}
		
	}
	fclose(fp);
	//////////////////////////////////////////////////////////////////////////	
#undef LOADINT
#undef LOADCHAR
#undef LOADFLOAT
#undef LOADSTR
	return iCount;

}
