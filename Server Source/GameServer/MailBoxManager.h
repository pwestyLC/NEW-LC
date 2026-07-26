#pragma once

#include "../ShareLib/packetType/ptype_mail_box.h"

struct SendingSystemMailInfo  //pwesty fixed
{
    CPC* Receiver = nullptr;
    std::string Subject;
    std::string Message;
    LONGLONG Nas = 0;
    CItem* Items[LETTER_MAX_ITEMS] = {};
    int ItemCount = 0;
};


class MailBoxManager
{
public:
	MailBoxManager() { }
	~MailBoxManager() { }

	void SendSystemMail(const SendingSystemMailInfo& mailInfo);

private:
};

