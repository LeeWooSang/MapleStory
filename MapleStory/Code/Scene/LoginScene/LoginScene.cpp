#include "LoginScene.h"
#include "../../Input/Input.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/UI/LoginUI/LoginUI.h"
#include "../../GameObject/UI/TextUI/TextUI.h"
#include "../../Camera/Camera.h"

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
	if (m_player)
		delete m_player;
}

bool LoginScene::Initialize()
{
	string name = "";

	name = "Background";
	Map* background = new Map(name);
	m_objectList.emplace(name, background);
	if (background->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/Background.png", 800, 600, 1, 1, 0, 0)) == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "Frame";
	Map* frame = new Map(name);
	m_objectList.emplace(name, frame);
	if (frame->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/Frame.png", 800, 600, 1, 1, 0, 0)) == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "GameGrade";
	Map* grade = new Map(name);
	m_objectList.emplace(name, grade);
	if (grade->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/GameGrade.png", 65, 75, 1, 1, 0, 0)) == false)
		return false;
	grade->SetPosition(VECTOR2D(365.f, -260.f));

	name = "Logo";
	Map* logo = new Map(name);
	m_objectList.emplace(name, logo);
	if (logo->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/Logo.png", 306, 152, 1, 1, 0, 0)) == false)
		return false;
	logo->SetPosition(VECTOR2D(0.f, -165.f));

	//name = "InputBackground";
	//LoginUI* inputBackground = new LoginUI(name);
	//m_objectList.emplace(name, inputBackground);
	//if (inputBackground->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/InputBackground.png", 244, 158, 1, 1, 0, 0)) == false)
	//	return false;
	//inputBackground->SetPosition(VECTOR2D(0.f, 0.f));
	
	name = "IDInput";
	LoginUI* idInput = new LoginUI(name);
	m_objectList.emplace(name, idInput);
	if (idInput->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/IDInput1.png", 160, 23, 1, 1, 0, 0)) == false)
		return false;
	idInput->SetPosition(VECTOR2D(-25.f, -27.f));

	//name = "PWInput";
	//LoginUI* pwInput = new LoginUI(name);
	//m_objectList.emplace(name, pwInput);
	//if (pwInput->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/PWInput.png", 160, 23, 1, 1, 0, 0)) == false)
	//	return false;
	//pwInput->SetPosition(VECTOR2D(-25.f, 0.f));

	//name = "Player";
	//m_player = new Player(name);
	//if(m_player->Initialize(TextureInfo(L"../Resource/Textures/Character/Player.png", 133, 144, 1, 1, 0, 0)) == false)
	//	return false;

	return true;
}

void LoginScene::Update(float elapsedTime)
{
	bool result = Collision("IDInput");
	if(result == true)
	{
		if (GET_INSTANCE(Input)->KeyOnceCheck(KEY_TYPE::MOUSE_LBUTTON) == true)
			GET_INSTANCE(Input)->SetIsActive(true);
	}

	else 
	{
		if (GET_INSTANCE(Input)->KeyOnceCheck(KEY_TYPE::MOUSE_LBUTTON) == true)
			GET_INSTANCE(Input)->SetIsActive(false);
	}

	for (auto object : m_objectList)
		object.second->Update(elapsedTime);

	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void LoginScene::Render()
{
	for (auto object : m_objectList)
	{
		//if(GET_INSTANCE(Camera)->IsVisible(object.second) == true)
			object.second->Render();
	}

	if(m_player != nullptr)
		m_player->Render();
}

bool LoginScene::Collision(const string& key)
{
	auto iter = m_objectList.find(key);
	if (iter == m_objectList.end())
		return false;

	Matrix3x2F worldView = (*iter).second->GetWorldMatrix() * GET_INSTANCE(Camera)->GetViewMatrix();
	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);

	TextureInfo info = GET_INSTANCE(D2DManager)->GetTexture(key);

	int minX = pos.x - info.m_width * 0.5f;
	int minY = pos.y - info.m_height * 0.5f;
	int maxX = minX + info.m_width;
	int maxY = minY + info.m_height;

	POINT mousePos = GET_INSTANCE(Input)->GetMousePos();
	if (minX > mousePos.x)
		return false;
	else if (maxX < mousePos.x)
		return false;
	else if (minY > mousePos.y)
		return false;
	else if (maxY < mousePos.y)
		return false;

	return true;
}

