#include "LoginScene.h"
#include "../../Input/Input.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/UI/LoginUI/LoginUI.h"
#include "../../GameObject/UI/TextUI/TextUI.h"
#include "../../Camera/Camera.h"
#include "../../Network/Network.h"

LoginScene::LoginScene()
{
	m_objectVector.reserve(MAX_OBJECT_TYPE);
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
	m_objectVector.emplace_back(background);
	if (background->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/Background.png", 800, 600, 1, 1, 0, 0)) == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "Frame";
	Map* frame = new Map(name);
	m_objectVector.emplace_back(frame);
	if (frame->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/Frame.png", 800, 600, 1, 1, 0, 0)) == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "GameGrade";
	Map* grade = new Map(name);
	m_objectVector.emplace_back(grade);
	if (grade->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/GameGrade.png", 65, 75, 1, 1, 0, 0)) == false)
		return false;
	grade->SetPosition(VECTOR2D(365.f, -260.f));

	name = "Logo";
	Map* logo = new Map(name);
	m_objectVector.emplace_back(logo);
	if (logo->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/Logo.png", 306, 152, 1, 1, 0, 0)) == false)
		return false;
	logo->SetPosition(VECTOR2D(0.f, -165.f));

	name = "InputBackground";
	LoginUI* inputBackground = new LoginUI(name);
	m_objectVector.emplace_back(inputBackground);
	if (inputBackground->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/InputBackground.png", 244, 158, 1, 1, 0, 0)) == false)
		return false;
	inputBackground->SetPosition(VECTOR2D(0.f, 0.f));
	
	name = "LoginButton";
	LoginUI* loginButton = new LoginUI(name);
	m_objectVector.emplace_back(loginButton);
	if (loginButton->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/LoginButton.png", 50, 50, 1, 1, 0, 0)) == false)
		return false;
	loginButton->SetPosition(VECTOR2D(82.5f, -13.5f));

	name = "IDInput";
	TextUI* idInput = new TextUI(name);
	m_objectVector.emplace_back(idInput);
	if (idInput->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/IDInput1.png", 160, 23, 1, 1, 0, 0)) == false)
		return false;
	idInput->SetPosition(VECTOR2D(-25.f, -27.f));

	name = "PWInput";
	TextUI* pwInput = new TextUI(name);
	m_objectVector.emplace_back(pwInput);
	if (pwInput->Initialize(TextureInfo(L"../Resource/Textures/UI/Login/PWInput.png", 160, 23, 1, 1, 0, 0)) == false)
		return false;
	pwInput->SetPosition(VECTOR2D(-25.f, 0.f));

	//name = "Player";
	//m_player = new Player(name);
	//if(m_player->Initialize(TextureInfo(L"../Resource/Textures/Character/Player.png", 133, 144, 1, 1, 0, 0)) == false)
	//	return false;

	return true;
}

void LoginScene::Update(float elapsedTime)
{
	// 1. �浹�� ������Ʈ�� ã�´�
	int collidedObject = -1;
	int flag = 0;
	for (int i = OBJECT_KEY_TYPE::LOGIN_BUTTON_KEY; i < OBJECT_KEY_TYPE::PW_INPUT_KEY; ++i)
	{
		flag = 0;
		if (CheckCollision(i, flag) == true)
		{
			collidedObject = i;
			break;
		}
	}
	// 2. �浹�� ���� Ŭ���ߴ��� ���ߴ���
	if (collidedObject != -1)
		ProcessCollision(collidedObject, flag);

	for (auto object : m_objectVector)
		object->Update(elapsedTime);

	if (m_player != nullptr)
		m_player->Update(elapsedTime);
}

void LoginScene::Render()
{
	for (auto object : m_objectVector)
	{
		//if(GET_INSTANCE(Camera)->IsVisible(object.second) == true)
			object->Render();
	}

	if(m_player != nullptr)
		m_player->Render();
}

bool LoginScene::CheckCollision(int key, int& flag)
{
	if (m_objectVector[key] == nullptr)
		return false;

	if(key == OBJECT_KEY_TYPE::LOGIN_BUTTON_KEY)
		flag |= OBJECT_TYPE::LOGIN_BUTTON;

	else if (key == OBJECT_KEY_TYPE::ID_INPUT_KEY)
		flag |= OBJECT_TYPE::ID_INPUT;

	else if (key == OBJECT_KEY_TYPE::PW_INPUT_KEY)
		flag |= OBJECT_TYPE::PW_INPUT;

	Matrix3x2F worldView = m_objectVector[key]->GetWorldMatrix() * GET_INSTANCE(Camera)->GetViewMatrix();
	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);

	TextureInfo info = GET_INSTANCE(D2DManager)->GetTexture(m_objectVector[key]->GetName());

	int minX = pos.x - info.m_width * 0.5f;
	int minY = pos.y - info.m_height * 0.5f;
	int maxX = minX + info.m_width;
	int maxY = minY + info.m_height;

	POINT mousePos = GET_INSTANCE(Input)->GetMousePos();

	// �浹 ���� ���
	if (minX > mousePos.x)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
		return false;
	}

	else if (maxX < mousePos.x)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
		return false;
	}

	else if (minY > mousePos.y)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
		return false;
	}

	else if (maxY < mousePos.y)
	{
		flag |= COLLISION_TYPE::NO_COLLISION;
		return false;
	}

	flag |= COLLISION_TYPE::COLLISION;
	return true;
}

void LoginScene::ProcessCollision(int key, int flag)
{
	// ���콺 Ŭ���� ���
	if (GET_INSTANCE(Input)->KeyOnceCheck(KEY_TYPE::MOUSE_LBUTTON) == true)
		flag |= MOUSE_TYPE::CLICK;
	else
		flag |= MOUSE_TYPE::NO_CLICLK;

	switch (flag)
	{
	case PROCESS_OBJECT_COLLISION_TYPE::LOGIN_BUTTON_NO_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::LOGIN_BUTTON_NO_COLLISION_AND_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::LOGIN_BUTTON_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::LOGIN_BUTTON_COLLISION_AND_CLICK:
		cout << "�α��� ��ư Ŭ��" << endl;
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::ID_INPUT_NO_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::ID_INPUT_NO_COLLISION_AND_CLICK:
		GET_INSTANCE(Input)->SetIsActive(false);
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::ID_INPUT_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::ID_INPUT_COLLISION_AND_CLICK:
		GET_INSTANCE(Input)->SetIsActive(true);
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::PW_INPUT_NO_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::PW_INPUT_NO_COLLISION_AND_CLICK:
		GET_INSTANCE(Input)->SetIsActive(false);
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::PW_INPUT_COLLISION_AND_NO_CLICK:
		break;

	case PROCESS_OBJECT_COLLISION_TYPE::PW_INPUT_COLLISION_AND_CLICK:
		GET_INSTANCE(Input)->SetIsActive(true);
		break;

	default:
		break;
	}
}

