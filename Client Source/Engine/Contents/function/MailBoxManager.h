#pragma once

#include <map>
#include <vector>
#include <Engine/LocalDefine.h>
#include <Common/CommonDef.h>
#include <Engine/Entities/OptionData.h>
#include <Common/Packet/ptype_mail_box.h>

class CUILetter;
class CUIMailBox;

#define NPC_INDEX 1374

class MailBoxManager
{
public:
	typedef std::map<MailBoxMessageTypes, std::vector<MailCardInfo*>> mails_map_;

public:
	MailBoxManager();
	~MailBoxManager();

	void Lock() { m_bLock = true; }
	void Unlock() { m_bLock = false; }
	bool IsLock() const { return m_bLock; }
	bool IsMessageOpen();
	CUILetter* GetUILetter() { return m_letterUI; }

	void setMailBoxUI(CUIMailBox* pUI) { m_UI = pUI; }
	void setLetterUI(CUILetter* pLetterUI) { m_letterUI = pLetterUI; }

	MailCardInfo* getMailAt(MailBoxMessageTypes pageType, size_t pos) const;
	mails_map_ getMails() const { return m_mapMails; }
	void clearMails() { m_mapMails.clear(); }
	void clearMails(MailBoxMessageTypes pageType) { m_mapMails[pageType].clear(); }

	void ReceiveMessage(CNetworkMessage* istr);
	void SendListReq(MailBoxMessageTypes pageType, int32_t lastMail = -1);
	void SendDeleteAllMails(MailBoxMessageTypes pageType);
	void SendDeleteMail(MailBoxMessageTypes pageType, int32_t mailPos);
	void SendDeleteMailById(MailBoxMessageTypes pageType, int32_t mailId);
	void SendOpenMail(MailBoxMessageTypes pageType, int32_t mailPos);
	void SendFindUser(CTString nickname);
	void SendCollectMessage(int32_t mailId);
	void SendLetter(SendingMailLetter& letter);

	void showErrorMessage(MailBoxErrors errorType);

public:
	enum eMAIL_NPC_STATE
	{
		MAIL_NPC_STATE_NONE,
		MAIL_NPC_STATE_EXIST,
		MAIL_NPC_STATE_APPEAR,
	};

private:
	int32_t getMailId(MailBoxMessageTypes pageType, int32_t mailPos);
	int32_t getMailPos(MailBoxMessageTypes pageType, int32_t mailId);
	void	deleteMail(MailBoxMessageTypes pageType, int32_t mailId);
	void	deleteAllMails(MailBoxMessageTypes pageType);
	void    ChangeMailNpc(eMAIL_NPC_STATE eNpcState);

private:
	bool m_bLock;
	mails_map_ m_mapMails;
	CUIMailBox* m_UI;
	CUILetter* m_letterUI;
};