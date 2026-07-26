#include "CheckPassword.h"

#ifndef _WIN64
#include <algorithm>
#include <crypt.h>
#include <cstring>
#include "md5.h"
bool CCheckPassword::checkPass(const std::string& pass, const std::string& dbpass)
{

	int crypttype = kPlainText;
	if (dbpass.size() == 60)	crypttype = kBcryptedText;
	else if (dbpass.size() == 32)	crypttype = kMD5Text;

	switch (crypttype)
	{
	case kPlainText:
	{
		return (pass.compare(dbpass) == 0 ? true : false);
	}
	break;

	case kMD5Text:
	{
		char tmpPass[1024];
		char tmpResult[256];
		md5_buffer(pass.c_str(), pass.size(), tmpPass);
		md5_sig_to_string(tmpPass, tmpResult, sizeof(tmpResult));
		std::string md5String(tmpResult);
		std::transform(md5String.begin(), md5String.end(), md5String.begin(),
			[](unsigned char c) { return std::toupper(c); });
		std::string dbpassUpper(dbpass);
		std::transform(dbpassUpper.begin(), dbpassUpper.end(), dbpassUpper.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return (md5String.compare(dbpassUpper) == 0 ? true : false);
	}
	break;

	case kBcryptedText:
	{

		char* out = crypt(pass.c_str(), dbpass.c_str());
		if (!out) return false;
		return std::strcmp(out, dbpass.c_str()) == 0;
	}
	break;

	default:
		return false;
		break;
	}
	return false;
}

#else

bool CCheckPassword::checkPass(const std::string& pass, const std::string& dbpass)
{
	return true;
}

#endif