#ifndef __EVENT_ACTIVE_UI_H__
#define __EVENT_ACTIVE_UI_H__

struct SEventActiveModel;
class CUIList;
class CEventActiveUI : public CUIBase
{
public:
	CEventActiveUI();
	~CEventActiveUI() = default;

	void initialize();
	void Render() override;

	void Close();
	void Open();

	WMSG_RESULT MouseMessage(MSG* pMsg) override;

	void ReceiveList(CNetworkMessage* istr);
	void ReceiveEventActive(CNetworkMessage* istr);
	void ReceiveEventDeactive(CNetworkMessage* istr);

	void RemoveAllEvent();
private:
	void updateEventList();
	void informPopup(const CTString& strTitle);
	std::vector<SEventActiveModel> m_vecEventActiveModel;

	CUIList* m_pEventList;
	CUIButton* m_pBtnClose;
};

struct SEventActiveModel
{
	int m_nIndex;
	CTString m_strName;
	unsigned long m_nDateStart;
	unsigned long m_nDateEnd;
};

#endif
