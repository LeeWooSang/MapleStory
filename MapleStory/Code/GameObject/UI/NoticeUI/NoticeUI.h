#pragma once
#include "../UI.h"

class NoticeUI : public UI
{
public:
	NoticeUI(const string&);
	virtual ~NoticeUI();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	void RenderBase();
	void RenderNotice();

	enum NOTICE_TYPE
	{
		NONE = 0x0000,
		ID_NOT_CORRECT = 0x0001,
		PW_NOT_CORRECT = 0x0002
	};

	void SetNoticeName(NOTICE_TYPE type) { m_noticeType = type; }

private:
	NOTICE_TYPE m_noticeType;

	unordered_map<string, class Collider*> m_noticeList;
};

