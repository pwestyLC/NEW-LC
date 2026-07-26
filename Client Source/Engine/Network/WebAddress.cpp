#include "StdH.h"
#include "WebAddress.h"
#include <Engine/Interface/UIManager.h>


CWebAddress::CWebAddress()
{

}


CWebAddress::~CWebAddress()
{
	m_mapAddressAlias.clear();
}


void CWebAddress::initialize()
{
	regist( "help_list",		_S(117, "") );
	regist( "help_view",		_S(118, "") );

	regist( "notice_list",		_S(119, "") );
	regist( "notice_view",		_S(120, "") );

	regist( "freebbs_list",		_S(121, "") );
	regist( "freebbs_view",		_S(122, "") );
	regist( "freebbs_modify",	_S(123, "") );

	regist( "guildbbs_list",	_S(1008, "") ); // wooss ���ּ� ���� 
	regist( "guildbbs_view",	_S(1009, "") );
	regist( "guildbbs_modify",	_S(1010, "") );
}


bool CWebAddress::regist(const char *alias, const char *address)
{
	MapAddressAlias::value_type temp(alias, address);
	return m_mapAddressAlias.insert(temp).second;
}


const char *CWebAddress::get(const char *alias)
{
	if( m_mapAddressAlias.empty() == true )
		return NULL;

	return m_mapAddressAlias[std::string(alias)].c_str();
}