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

	void SetIsActive(bool isActive) { m_isActive = isActive; }
	void SetNoticeType(char type) { m_noticeType = type; }

private:
	bool m_isActive;
	char m_noticeType;

	unordered_map<string, class Collider*> m_noticeList;
};

