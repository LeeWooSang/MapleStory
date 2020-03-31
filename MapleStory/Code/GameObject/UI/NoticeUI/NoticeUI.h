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

	void SetIsActive(bool isActive) { m_isActive = isActive; }

private:
	bool m_isActive;
};