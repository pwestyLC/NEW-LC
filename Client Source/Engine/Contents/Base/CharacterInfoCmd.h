#ifndef		_CHARACTER_INFO_COMMAND_H_
#define		_CHARACTER_INFO_COMMAND_H_

class Command;

//--------------------------------------------------------------
// UI �ݱ�
class CmdCharInfoClose : public Command
{
public:
	CmdCharInfoClose() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->CloseUI();
	}
private:
	CUICharacterInfo* pUI_;
};

//--------------------------------------------------------------
// Main �� ����
class CmdCharInfoChangeTab : public Command
{
public:
	CmdCharInfoChangeTab() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->ChangeTab();
	}
private:
	CUICharacterInfo* pUI_;
};

//--------------------------------------------------------------
// StatPoint ���
class CmdCharInfoStatpoint : public Command
{
public:
	CmdCharInfoStatpoint() : pUI_(NULL), ubStatType_(0) {}
	void setData(CUICharacterInfo* pUI, UBYTE ubStatType)	
	{ 
		pUI_ = pUI; 
		ubStatType_ = ubStatType;
	}
	void execute() {
		if (pUI_)
			pUI_->SendUseStatPoint(ubStatType_);
	}
private:
	CUICharacterInfo* pUI_;
	UBYTE ubStatType_;
};

class CmdCharInfoStatpointReset : public Command
{
public:
	CmdCharInfoStatpointReset() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	
	{ 
		pUI_ = pUI; 
	}
	void execute() {
		if (pUI_)
			pUI_->SendResetStatPoint();
	}
private:
	CUICharacterInfo* pUI_;
};
//--------------------------------------------------------------
// ��ų �� ����
class CmdCharSkillChangeTab : public Command
{
public:
	CmdCharSkillChangeTab() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->ChangeTabSkill();
	}
private:
	CUICharacterInfo* pUI_;
};

//--------------------------------------------------------------
// �׼� �� ����
class CmdCharActionChangeTab : public Command
{
public:
	CmdCharActionChangeTab() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->ChangeTabAction();
	}
private:
	CUICharacterInfo* pUI_;
};

//--------------------------------------------------------------
// Ŀ�´�Ƽ �� ����
class CmdCharCommunityChangeTab : public Command
{
public:
	CmdCharCommunityChangeTab() : pUI_(NULL) {}
	void setData(CUICharacterInfo* pUI)	{ pUI_ = pUI; }
	void execute() {
		if (pUI_)
			pUI_->ChangeTabCommunity();
	}
private:
	CUICharacterInfo* pUI_;
};

//--------------------------------------------------------------
// ��ų ���
class CmdCharSkillFire : public Command
{
public:
	CmdCharSkillFire() : m_slSkillIndex(-1) {}
	void setData(SLONG idx) { m_slSkillIndex = idx; }
	void execute() {
		if( m_slSkillIndex > 0 )
			CUIManager::getSingleton()->GetCharacterInfo()->UseSkill(m_slSkillIndex);
	}
private:
	SLONG m_slSkillIndex;
};

//--------------------------------------------------------------
// �׼� ���
class CmdCharActionFire : public Command
{
public:
	CmdCharActionFire() : m_slActionIndex(-1) {}
	void setData(SLONG idx) { m_slActionIndex = idx; }
	void execute() {
		if( m_slActionIndex > 0 )
		{
			CUITooltipMgr::getSingleton()->clearTooltip();
			CUIManager::getSingleton()->GetCharacterInfo()->UseAction(m_slActionIndex);
		}
	}
private:
	SLONG m_slActionIndex;
};

//--------------------------------------------------------------
// Syndi ����
class CmdCharMySyndiCateInfo : public Command
{
public:
	CmdCharMySyndiCateInfo(){}
	void execute()
	{
		CUIManager::getSingleton()->GetMySyndiInfo()->OpenUI();
	}
};

//--------------------------------------------------------------
// ToolTip Ŭ����
class CmdCharTooltipClear : public Command
{
public:
	void execute()
	{
		CUITooltipMgr::getSingleton()->clearTooltip();
	}
};

//--------------------------------------------------------------
// ����Ʈ �̹���
class CmdCharSelectImg : public Command
{
public:
	CmdCharSelectImg() : m_pWnd(NULL), m_pIcon(NULL)	{}
	void setData(CUICharacterInfo* pWnd, CUIIcon* pIcon)
	{
		m_pWnd = pWnd;
		m_pIcon = pIcon;
	}
	void execute()
	{
		if (m_pWnd != NULL && m_pIcon != NULL)
			m_pWnd->UpdateSelectImage(m_pIcon);
	}
private:
	CUICharacterInfo* m_pWnd;
	CUIIcon* m_pIcon;
};

#endif		// _CHARACTER_INFO_COMMAND_H_