#include "LoginBaseLayer.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/UI/LoginUI/LoginUI.h"

LoginBaseLayer::LoginBaseLayer()
{
}

LoginBaseLayer::~LoginBaseLayer()
{
}

bool LoginBaseLayer::Initialize()
{	
	string name = "";

	name = "LoginBackground";
	Map* background = new Map(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "LoginFrame";
	Map* frame = new Map(name);
	m_objectList.emplace_back(frame);
	if (frame->Initialize() == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "LoginGameGrade";
	Map* grade = new Map(name);
	m_objectList.emplace_back(grade);
	if (grade->Initialize() == false)
		return false;
	grade->SetPosition(VECTOR2D(365.f, -260.f));

	name = "LoginLogo";
	Map* logo = new Map(name);
	m_objectList.emplace_back(logo);
	if (logo->Initialize() == false)
		return false;
	logo->SetPosition(VECTOR2D(0.f, -165.f));

	name = "LoginInputBackground";
	LoginUI* inputBackground = new LoginUI(name);
	m_objectList.emplace_back(inputBackground);
	if (inputBackground->Initialize() == false)
		return false;
	inputBackground->SetPosition(VECTOR2D(0.f, 0.f));

	return true;
}

void LoginBaseLayer::Update(float elapsedTime)
{
	for (auto object : m_objectList)
	{
		object->Update(elapsedTime);
	}
}

void LoginBaseLayer::Render()
{
	for (auto object : m_objectList)
	{
		//if(GET_INSTANCE(Camera)->IsVisible(object.second) == true)
		object->Render();
	}

}

bool LoginBaseLayer::CheckCollision(GameObject*, int&)
{
	return false;
}

void LoginBaseLayer::ProcessCollision(GameObject *, int&)
{
}

void LoginBaseLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
