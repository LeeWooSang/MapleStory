#include "LoginNoticeLayer.h"
#include "../../GameObject/UI/NoticeUI/NoticeUI.h"
#include "../../GameObject/UI/ButtonUI/ButtonUI.h"
#include "../../../../GameServer/Code/Protocol.h"

LoginNoticeLayer::LoginNoticeLayer()
{
	m_noticeBackground = nullptr;
	m_noticeIDNotCorrect = nullptr;
	m_noticePWNotCorrect = nullptr;
	
	m_yesButton = nullptr;
	m_noButton = nullptr;

	m_isActive = false;
	m_noticeType = 0;
}

LoginNoticeLayer::~LoginNoticeLayer()
{
}

bool LoginNoticeLayer::Initialize()
{
	m_isActive = false;
	m_noticeType = 0;

	string name = "NoticeBackground";
	m_noticeBackground = new NoticeUI(name);
	m_objectMap.emplace(LOGIN_NOTICE_OBJECT_KEY::NOTICE_BACKGROUND, m_noticeBackground);
	if (m_noticeBackground->Initialize() == false)
		return false;
	m_noticeBackground->SetPosition(VECTOR2D(0.f, 0.f));

	name = "NoticeIDNotCorrect";
	m_noticeIDNotCorrect = new NoticeUI(name);
	m_objectMap.emplace(LOGIN_NOTICE_OBJECT_KEY::NOTICE_ID_NOT_CORRECT, m_noticeIDNotCorrect);
	if (m_noticeIDNotCorrect->Initialize() == false)
		return false;
	m_noticeIDNotCorrect->SetPosition(VECTOR2D(0.f, -15.f));

	name = "NoticePWNotCorrect";
	m_noticePWNotCorrect = new NoticeUI(name);
	m_objectMap.emplace(LOGIN_NOTICE_OBJECT_KEY::NOTICE_PW_NOT_CORRECT, m_noticePWNotCorrect);
	if (m_noticePWNotCorrect->Initialize() == false)
		return false;
	m_noticePWNotCorrect->SetPosition(VECTOR2D(0.f, -15.f));

	name = "NoticeYesButton";
	m_yesButton = new ButtonUI(name);
	m_objectMap.emplace(LOGIN_NOTICE_OBJECT_KEY::NOTICE_YES_BUTTON, m_yesButton);
	if (m_yesButton->Initialize() == false)
		return false;
	m_yesButton->SetPosition(VECTOR2D(-40.f, 50.f));

	name = "NoticeNoButton";
	m_noButton = new ButtonUI(name);
	m_objectMap.emplace(LOGIN_NOTICE_OBJECT_KEY::NOTICE_NO_BUTTON, m_noButton);
	if (m_noButton->Initialize() == false)
		return false;
	m_noButton->SetPosition(VECTOR2D(40.f, 50.f));

	return true;
}

void LoginNoticeLayer::Update(float elapsedTime)
{
	if (m_yesButton != nullptr)
	{
		int flag = LOGIN_NOTICE_OBJECT_KEY::NOTICE_YES_BUTTON;
		
		if (CheckCollision(m_yesButton, flag) == true)
			ProcessCollision(m_yesButton, flag);
	}
	//for (auto object : m_objectMap)
	//{
	//	flag = object.first;
	//	if (CheckCollision(object.second, flag) == false)
	//		continue;

	//	ProcessCollision(object.second, flag);
	//}

	for (auto object : m_objectMap)
	{
		object.second->Update(elapsedTime);
	}
}

void LoginNoticeLayer::Render()
{
	if (m_isActive == false)
		return;

	m_noticeBackground->Render();

	if (m_noticeType & NOTICE_TYPE::ID_NOT_CORRECT)
		m_objectMap[LOGIN_NOTICE_OBJECT_KEY::NOTICE_ID_NOT_CORRECT]->Render();

	else if (m_noticeType & NOTICE_TYPE::PW_NOT_CORRECT)
		m_objectMap[LOGIN_NOTICE_OBJECT_KEY::NOTICE_PW_NOT_CORRECT]->Render();

	m_yesButton->Render();
}

bool LoginNoticeLayer::CheckCollision(GameObject* object, int& flag)
{
	if (Layer::CheckCollision(object, flag) == false)
		return false;

	return true;
}

void LoginNoticeLayer::ProcessCollision(GameObject* object, int& flag)
{
	m_isActive = false;

	//switch(flag)
	//{
	//case PROCESS_NOTICE_BUTTON_COLLISION_TYPE::YES_BUTTON_COLLISION_AND_CLICK:
	//case PROCESS_NOTICE_BUTTON_COLLISION_TYPE::NO_BUTTON_COLLISION_AND_CLICK:
	//	m_isActive = false;
	//	break;
	//}
}

void LoginNoticeLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
