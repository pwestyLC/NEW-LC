#pragma once

#include <Common/Packet/ptype_mail_box.h>

struct MailLetter;
class CUIText;
class CUIButton;
class CUIImage;
class CUIIcon;
class CUIEditBox;
class CUIImageArray;
class CUIMultiEditBox;
class MailBoxManager;

enum LetterTypes
{
	LetterSended,
	LetterReceived,
	LetterWrite
};

class CUILetter : public CUIWindow
{
public:
	CUILetter();
	~CUILetter();

	void	initialize();
	void	ResetPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);
	void	AdjustPosition(PIX pixMinI, PIX pixMinJ, PIX pixMaxI, PIX pixMaxJ);

	void	OpenUI(LetterTypes letterType);
	void	CloseUI();
	void	UpdateUI();

	void	setData(MailLetter* letter);
	void	deleteMail();
	void	findUserRequest();
	void	collectAttachment();
	void	sendMail();
	void	updateFindUser(bool isFind);

	void	targetUserChanged();
	void	CountItemCallback(int iconPos);

	void	collected();

	BOOL	IsEditBoxFocused();

	int32_t getOpenMailId() { 
		if (!m_curLetter) return -1;
		return m_curLetter->getIndex();
	}

public:
	enum Texts
	{
		TargetUserType,
		Sender,
		Date,
		SubjectType,
		Subject,
		MaxText
	};

	enum Buttons
	{
		Close,
		Close2,
		FindUser,
		Send,
		Collect,
		Delete,
		MaxBtn
	};

	enum EditBoxes
	{
		SenderName,
		SubjectText,
		Gold,
		MaxEditBox
	};

	enum Areas
	{
		ReceiveArea,
		WriteLetterArea,
		MaxArea
	};

	enum Images
	{
		NotFoundUser,
		FoundUser,
		MaxImage
	};

protected:
	WMSG_RESULT OnLButtonDown(UINT16 x, UINT16 y);
	WMSG_RESULT OnLButtonUp(UINT16 x, UINT16 y);
	WMSG_RESULT OnMouseMove(UINT16 x, UINT16 y, MSG* pMsg);
	WMSG_RESULT OnKeyMessage(MSG* pMsg);

private:
	void PrepareOpen(LetterTypes letterTypes);
	void PrepareClose();

	MailBoxMessageTypes getMessageType();

	bool canPutItem(CItems* item, int32_t iconPos);

private:
	bool			isMove;
	int				nX,
					nY;
	CUIBase*		m_moveArea;
	CUIImageArray*	m_jobArray;
	CUIBase*		m_UIBlocks[Areas::MaxArea];
	CUIText*		m_labels[Texts::MaxText];
	CUIButton*		m_buttons[Buttons::MaxBtn];
	CUIImage*		m_images[Images::MaxImage];
	CUIEditBox*		m_editBoxes[EditBoxes::MaxEditBox];
	CUIIcon*		m_icons[LETTER_MAX_ITEMS];
	CUIMultiEditBox* m_messageBox;

	LetterTypes		m_windowType;
	MailBoxManager*	m_mailManager;

	MailLetter*		m_curLetter;

	bool			m_selectedUser;
};