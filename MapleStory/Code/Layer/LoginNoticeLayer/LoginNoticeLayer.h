#pragma once
#include "../Layer.h"

class LoginNoticeLayer : public Layer
{
public:
	LoginNoticeLayer();
	virtual ~LoginNoticeLayer();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual bool CheckCollision(class GameObject*, int&);
	virtual void ProcessCollision(class GameObject*, int&);
	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

	void SetNoticeType(char noticeType) { m_isActive = true, m_noticeType = noticeType; }

private:
	class NoticeUI* m_noticeBackground;
	class NoticeUI* m_noticeIDNotCorrect;
	class NoticeUI* m_noticePWNotCorrect;

	class ButtonUI* m_yesButton;
	class ButtonUI* m_noButton;

	bool m_isActive;
	char m_noticeType;
};

enum NOTICE_OBJECT_KEY
{
	NOTICE_BACKGROUND = 0x0010,
	NOTICE_ID_NOT_CORRECT = 0x0020,
	NOTICE_PW_NOT_CORRECT = 0x0040,

	NOTICE_YES_BUTTON = 0x0080,
	NOTICE_NO_BUTTON = 0x0100,
};

enum PROCESS_NOTICE_BUTTON_COLLISION_TYPE
{
	YES_BUTTON_COLLISION_AND_CLICK = 0x008A,
	NO_BUTTON_COLLISION_AND_CLICK = 0x010A,
};