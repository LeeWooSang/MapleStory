#include "LoginUILayer.h"
#include "../../GameObject/UI/LoginUI/LoginUI.h"
#include "../../GameObject/UI/TextUI/TextUI.h"
#include "../../GameObject/UI/NoticeUI/NoticeUI.h"
#include "../../GameObject/UI/ButtonUI/ButtonUI.h"
#include "../../Input/Input.h"
#include "../../Network/Network.h"

LoginUILayer::LoginUILayer()
{
	m_inputKey = -1;
}

LoginUILayer::~LoginUILayer()
{
}

bool LoginUILayer::Initialize()
{
	string name = "LoginInputButton";
	LoginUI* loginButton = new LoginUI(name);
	m_objectMap.emplace(LOGIN_UI_OBJECT_KEY::LOGIN_BUTTON, loginButton);
	if (loginButton->Initialize() == false)
		return false;
	loginButton->SetPosition(VECTOR2D(82.5f, -13.5f));

	name = "LoginIDInput";
	TextUI* idInput = new TextUI(name);
	m_objectMap.emplace(LOGIN_UI_OBJECT_KEY::ID_INPUT, idInput);
	if (idInput->Initialize() == false)
		return false;
	idInput->SetPosition(VECTOR2D(-25.f, -27.f));

	name = "LoginPWInput";
	TextUI* pwInput = new TextUI(name);
	m_objectMap.emplace(LOGIN_UI_OBJECT_KEY::PW_INPUT, pwInput);
	if (pwInput->Initialize() == false)
		return false;
	pwInput->SetPosition(VECTOR2D(-25.f, 0.f));

	name = "LoginQuitButton";
	LoginUI* quitButton = new LoginUI(name);
	m_objectMap.emplace(LOGIN_UI_OBJECT_KEY::QUIT_INPUT, quitButton);
	if (quitButton->Initialize() == false)
		return false;
	quitButton->SetPosition(VECTOR2D(73.f, 55.f));

	return true;
}

void LoginUILayer::Update(float elapsedTime)
{
	int flag = 0;
	for (auto object : m_objectMap)
	{
		flag = object.first;
		if (CheckCollision(object.second, flag) == false)
			continue;

		ProcessCollision(object.second, flag);
	}

	for (auto object : m_objectMap)
		object.second->Update(elapsedTime);
}

void LoginUILayer::Render()
{
	for (auto object : m_objectMap)
		object.second->Render();
}

bool LoginUILayer::CheckCollision(GameObject* object, int & flag)
{
	if (Layer::CheckCollision(object, flag) == false)
		return false;

	return true;
}

void LoginUILayer::ProcessCollision(GameObject* object, int& flag)
{	
	switch (flag)
	{
	case PROCESS_LOGIN_UI_COLLISION_TYPE::LOGIN_BUTTON_COLLISION_AND_CLICK:
		{
			string id = reinterpret_cast<TextUI*>(m_objectMap[LOGIN_UI_OBJECT_KEY::ID_INPUT])->ConvertTextToString();
			string pw = reinterpret_cast<TextUI*>(m_objectMap[LOGIN_UI_OBJECT_KEY::PW_INPUT])->ConvertTextToString();
			GET_INSTANCE(Network)->SendServerLoginPacket(id.c_str(), pw.c_str());
			cout << "로그인 버튼 클릭" << endl;
		}
		break;

	case PROCESS_LOGIN_UI_COLLISION_TYPE::ID_INPUT_COLLISION_AND_CLICK:
		m_inputKey = LOGIN_UI_OBJECT_KEY::ID_INPUT;
		reinterpret_cast<TextUI*>(object)->SetIsActive(true);
		reinterpret_cast<TextUI*>(m_objectMap[LOGIN_UI_OBJECT_KEY::PW_INPUT])->SetIsActive(false);
		break;

	case PROCESS_LOGIN_UI_COLLISION_TYPE::PW_INPUT_COLLISION_AND_CLICK:
		m_inputKey = LOGIN_UI_OBJECT_KEY::PW_INPUT;
		reinterpret_cast<TextUI*>(object)->SetIsActive(true);
		reinterpret_cast<TextUI*>(m_objectMap[LOGIN_UI_OBJECT_KEY::ID_INPUT])->SetIsActive(false);
		break;

	case PROCESS_LOGIN_UI_COLLISION_TYPE::QUIT_INPUT_COLLISION_AND_CLICK:
		::PostQuitMessage(0);
		break;

	default:
		break;
	}
}

void LoginUILayer::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_inputKey == -1)
		return;

	reinterpret_cast<TextUI*>(m_objectMap[m_inputKey])->ProcessKeyboardMessage(hWnd, message, wParam, lParam);
}
