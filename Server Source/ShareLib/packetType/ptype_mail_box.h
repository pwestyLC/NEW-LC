#pragma once

#include "ptype_base.h"
#include "ptype_express_system.h"

#define LETTER_MAX_ITEMS   (5)
#define MAX_SUBJECT_LENGTH (50)
#define MAX_MESSAGE_LENGTH (255)

enum
{
	MSG_SUB_MAILBOX_LIST,
	MSG_SUB_MAILBOX_LIST_FINISH,
	MSG_SUB_MAILBOX_DELETE,
	MSG_SUB_MAILBOX_DELETE_ALL,
	MSG_SUB_MAILBOX_FIND_USER,
	MSG_SUB_MAILBOX_OPEN_LETTER,
	MSG_SUB_MAILBOX_LETTER_COLLECT,
	MSG_SUB_MAILBOX_LETTER_COLLECT_ROLLBACK,
	MSG_SUB_MAILBOX_SEND_LETTER,
	MSG_SUB_MAILBOX_UPDATE_STATUS,
	MSG_SUB_MAILBOX_ERROR
};

enum MailBoxMessageTypes
{
	Received,
	Sent,
	SystemMails
};

enum MailBoxErrors
{
	Ok,
	AlreadyUsed,
	InvalidNickFormat,
	InvalidPageType,
	ServiceNotWork,
	IncorrectItem,
	CantSendYourself,
	FullInventory,
	DbError,
	LetterNotFound,
	MailBoxLocked,
	NotFoundUser,
	SubjectInvalidLenght,
	UnknownError
};

enum MailSenderTypes
{
	User,
	System
};

#pragma pack(push, 1)
struct MailCardInfo
{
	int				index;
	MailSenderTypes senderType;
	int				targetIndex;
	char			targetUser[EXPRESS_SENDER_NAME];
	char			subject[MAX_SUBJECT_LENGTH];
	char			message[MAX_MESSAGE_LENGTH];
	LONGLONG		recvTime;
	bool			haveAttachment;
	bool			isRead;

	int32_t getIndex() const { return index; }
};

struct MailLetter : MailCardInfo
{
	int			senderJob;
	bool		isMeLetter;
	LONGLONG	nas;
	int			itemsCount;
	ExpressSystemItemInfo list[0];
};

struct SendingMailLetter
{
	MailSenderTypes senderType;
	char			targetUser[EXPRESS_SENDER_NAME];
	char			subject[MAX_SUBJECT_LENGTH];
	char			message[MAX_MESSAGE_LENGTH];
	LONGLONG		nas;
	int				itemCount;
	struct
	{
		unsigned short tab;
		unsigned short invenIndex;
		int virtualIndex;
		int count;
	} list[0];
};

class MailSelector
{
public:
	MailSelector(int mailId) : m_mailId(mailId) { }

	bool operator ()(MailCardInfo* mailCard) const
	{
		return mailCard->getIndex() == m_mailId;
	}

private:
	int m_mailId;
};

namespace RequestClient
{
	struct MailBoxDeleteAll : public pTypeBase
	{
		MailBoxMessageTypes pageType;
	};

	struct MailBoxList : public pTypeBase
	{
		int lastMailId;
		MailBoxMessageTypes pageType;
	};

	struct MailBoxDeleteMail : public pTypeBase
	{
		int mailId;
		MailBoxMessageTypes pageType;
	};

	struct MailBoxOpenLetter : public pTypeBase
	{
		int mailId;
		MailBoxMessageTypes pageType;
	};

	struct MailBoxDeleteAllMails : public pTypeBase
	{
		MailBoxMessageTypes pageType;
	};

	struct MailBoxFindUser : public pTypeBase
	{
		char nickname[EXPRESS_SENDER_NAME];
	};

	struct MailBoxCollectLetter : public pTypeBase
	{
		int mailId;
	};

	struct MailBoxSendLetter : public pTypeBase
	{
		SendingMailLetter letter;
	};

#ifndef _CLIENT_
	struct MailBoxListGS : public MailBoxList
	{
		int	userIndex;
		int charIndex;
	};

	struct MailBoxDeleteMailGS : public MailBoxDeleteMail
	{
		int	userIndex;
		int charIndex;
	};

	struct MailBoxDeleteAllMailsGS : public MailBoxDeleteAllMails
	{
		int	userIndex;
		int charIndex;
	};

	struct MailBoxOpenLetterGS : public MailBoxOpenLetter
	{
		int	userIndex;
		int charIndex;
	};

	struct MailBoxCollectLetterGS : public MailBoxCollectLetter
	{
		int charIndex;
	};

	struct MailBoxSendGS : public pTypeBase
	{
		int				charIndex;
		MailSenderTypes senderType;
		int				targetCharIndex;
		char			subject[MAX_SUBJECT_LENGTH];
		char			message[MAX_MESSAGE_LENGTH];
		LONGLONG		nas;
		int				itemCount;
		ExpressSystemItemInfo list[0];
	};

	struct MailBoxCheckLettersGS : public pTypeBase
	{
		int charIndex;
	};
#endif

#ifndef _CLIENT_
	inline void makeMailBoxUpdateMessage(CNetMsg::SP& msg, int charIndex)
	{
		MailBoxCheckLettersGS* packet = reinterpret_cast<MailBoxCheckLettersGS*>(msg->m_buf);
		packet->type = MSG_MAIL_BOX;
		packet->subType = MSG_SUB_MAILBOX_UPDATE_STATUS;
		packet->charIndex = charIndex;
		msg->setSize(sizeof(*packet));
	}
#endif
};

namespace ResponseClient
{
	struct MailBoxDeleteAll : public pTypeBase
	{
		MailBoxMessageTypes pageType;
		MailBoxErrors errorCode;
	};

	struct MailBoxDeleteMail : public pTypeBase
	{
		int mailId;
		MailBoxMessageTypes pageType;
	};

	struct MailBoxList : public pTypeBase
	{
		int listCount;
		struct
		{
			int index;
			MailSenderTypes senderType;
			MailBoxMessageTypes pageType;
			int	 targetIndex;
			char targetUser[EXPRESS_SENDER_NAME];
			char subject[MAX_SUBJECT_LENGTH];
			LONGLONG recvTime;
			bool haveAttachment;
			bool isRead;
		} list[0];
	};

	struct MailBoxFindUser : public pTypeBase
	{
		bool isFind;
	};

	struct MailBoxOpenLetter : public pTypeBase
	{
		MailLetter letter;
	};

	struct MailBoxError : public pTypeBase
	{
		MailBoxErrors errorCode;
	};

	struct MailBoxCollectLetter : public pTypeBase
	{
		int mailId;
	};

#ifndef _CLIENT_
	struct MailBoxListGS : public pTypeBase
	{
		int error;
		int charIndex;
		int listCount;
		struct
		{
			int index;
			MailSenderTypes senderType;
			MailBoxMessageTypes pageType;
			int	 targetIndex;
			char targetUser[EXPRESS_SENDER_NAME];
			char subject[MAX_SUBJECT_LENGTH];
			LONGLONG recvTime;
			bool haveAttachment;
			bool isRead;
		} list[0];
	};

	struct MailBoxDeleteMailGS : public MailBoxDeleteMail
	{
		int error;
		int charIndex;
	};

	struct MailBoxErrorGS : public MailBoxError
	{
		int charIndex;
	};

	struct MailBoxDeleteAllMailsGS : public MailBoxDeleteAll
	{
		int error;
		int charIndex;
	};

	struct MailBoxOpenLetterGS : public pTypeBase
	{
		int error;
		int charIndex;
		MailLetter letter;
	};

	struct MailBoxCollectLetterGS : public MailBoxCollectLetter
	{
		int				error;
		int				charIndex;
		LONGLONG		nas;
		unsigned short	itemsCount;
		ExpressSystemItemInfo list[0];
	};

	struct MailBoxSendGS : public pTypeBase
	{
		int	error;
		int charIndex;
	};

	struct MailBoxCheckLettersGS : public pTypeBase
	{
		int charIndex;
		int	newMailsCount;
	};
#endif

#ifndef _CLIENT_
	inline void makeMailBoxErrorMessage(CNetMsg::SP& msg, int errorCode)
	{
		MailBoxError* packet = reinterpret_cast<MailBoxError*>(msg->m_buf);
		packet->type = MSG_MAIL_BOX;
		packet->subType = MSG_SUB_MAILBOX_ERROR;
		packet->errorCode = (MailBoxErrors)errorCode;

		msg->setSize(sizeof(MailBoxError));
	}

	inline void makeMailBoxFindUserResult(CNetMsg::SP& msg, bool isFind)
	{
		MailBoxFindUser* packet = reinterpret_cast<MailBoxFindUser*>(msg->m_buf);
		packet->type = MSG_MAIL_BOX;
		packet->subType = MSG_SUB_MAILBOX_FIND_USER;
		packet->isFind = isFind;

		msg->setSize(sizeof(MailBoxFindUser));
	}
#endif
};

namespace UpdateClient
{
	struct MailBoxUpdateStatus : public pTypeBase
	{
		int gotNewMails;
	};

#ifndef _CLIENT_
#endif
};
#pragma pack(pop)
