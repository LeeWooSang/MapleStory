#include "LoginBaseLayer.h"
#include "../../GameObject/StaticObject/StaticObject.h"
#include "../../GameObject/UI/LoginUI/LoginUI.h"

LoginBaseLayer::LoginBaseLayer()
{
}

LoginBaseLayer::~LoginBaseLayer()
{
}

bool LoginBaseLayer::Initialize()
{	
	string name = "LoginBackground";
	StaticObject* background = new StaticObject(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "Frame";
	StaticObject* frame = new StaticObject(name);
	m_objectList.emplace_back(frame);
	if (frame->Initialize() == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "LoginGameGrade";
	StaticObject* grade = new StaticObject(name);
	m_objectList.emplace_back(grade);
	if (grade->Initialize() == false)
		return false;
	grade->SetPosition(VECTOR2D(365.f, -260.f));

	name = "LoginLogo";
	StaticObject* logo = new StaticObject(name);
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
