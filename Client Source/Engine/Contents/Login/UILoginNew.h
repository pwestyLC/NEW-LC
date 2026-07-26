#ifndef __CUILOGIN_NEW_H__
#define __CUILOGIN_NEW_H__

class CUIComboBox;
class CUISpriteAni;
class CUICheckButton;
class CUIImage;
class CUIButton;

class ENGINE_API CUILoginNew : public CUIWindow
{
public:
	CUILoginNew(void);
	virtual ~CUILoginNew(void);

	void	PressLoginBtn();
	void	PressCloseBtn();
	void	PressCheckSave();
	void	PressChangeLang(std::string lang);
	BOOL	TryToLogin();		// �α��� �õ�
	
	void	OpenUI();
	void	CloseUI();

	void	initialize();
	void	SetLogin();
	void	Reset();
	void	ResetBtn();

	void	Lock(BOOL bLock);

	void	ReadPreviousId();
	void	WritePreviousId();

	void	SetPWFocus() 
	{ 
		if (m_pEbPw != NULL)
			m_pEbPw->SetFocus(TRUE);
	}

	void	SetFocus( BOOL bVisible );
	BOOL	IsEditBoxFocused();
	void	KillFocusEditBox();
	void	OnTabKeyProc();

	void	OnRender(CDrawPort* pDraw);
	void	OnUpdate( float fDeltaTime, ULONG ElapsedTime );
	
	void setVersion(const char* strVer);
	const char* getVersion()		{ return m_strVersion.c_str(); }
	
#ifdef DEV_LOGIN
	void	ReadTextDevPreviousIdPw(); // Login.txt �� ����� ���̵� �н����� ������
#endif // DEV_LOGIN

	WMSG_RESULT OnKeyMessage(MSG* pMsg);
private:
	void	sendIP();
	void	updateLogo();
	void	updateLogoHal(float fDelta);
	void	updateLogoXmas(float fDelta);

	void	updateLogoAlpha(CUIImage* pUpdateImage, float fAlphaLv);
	float	calcLogoAlphaLv(int iType, float fCurAlphaLv, bool bUp, float fDeltaTime);

	CUISpriteAni*	m_pLogoFrame;
	CUIButton*		m_pBtnLogin;
#ifdef MULTI_LANGUAGE
	CUIButton*		m_pBtnLangES;
	CUIButton*		m_pBtnLangDT;
#endif
	CUIButton*		m_pBtnLangEN;
	CUIButton*		m_pBtnLangPT;
	//CUIButton*		m_pBtnLangDT;
#ifdef LANGUAGE_FR_DETH04072021
	CUIButton*      m_pBtnLangFR;
#endif
	CUIButton*		m_pBtnClose;
	CUICheckButton*	m_pBtnSave;
	CUIComboBox*	m_pCbSelServer;
	CUIEditBox*		m_pEbId;
	CUIEditBox*		m_pEbPw;
	CUIImage*		m_pImgLogo;	// �⺻ ��ī �ΰ�
	CUIImage*		m_pImgLogoHal; // �ҷ��� �̺�Ʈ�� �ΰ�
	CUIImage*		m_pImgHalEye; // �ҷ��� �̺�Ʈ �ΰ��� �� �̹���
	CUIImage*		m_pImgLogoXmas;
	CUIImage*		m_pImgXmasEffect1;
	CUIImage*		m_pImgXmasEffect2;
	std::string		m_strVersion;
	int				m_nLogoType;
};
#endif	//	__CUILOGIN_NEW_H__