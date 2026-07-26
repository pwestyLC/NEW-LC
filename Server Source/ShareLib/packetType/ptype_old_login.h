#ifndef __PTYPE_LOGIN_H__
#define __PTYPE_LOGIN_H__

#include "ptype_base.h"

// Ŭ���̾�Ʈ�� �����ϰ� �����
// ���尡 ������(?) ��¥�� �������� ���ڸ� ����� ��
//#define VERSION_FOR_CLIENT			(20201019)
#define VERSION_FOR_CLIENT			(20210126) // classic

#pragma pack(push, 1)
//////////////////////////////////////////////////////////////////////////
namespace RequestClient
{
	struct LoginFromClient : public pTypeBase
	{
		unsigned char		mode;
		unsigned char		nation;
		int					version;
		char				id[MAX_ID_NAME_LENGTH + 1];
		char				pw[MAX_PWD_LENGTH + 1];
		char				mac[18];
		char				hwid[MAX_GUID_LENGTH + 1];
	};
}
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)

#endif
