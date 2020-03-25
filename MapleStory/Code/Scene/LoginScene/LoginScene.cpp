#include "LoginScene.h"
#include "../../Camera/Camera.h"
#include "../../Input/Input.h"
#include "../../GameObject/Map/Map.h"
#include "../../GameObject/Character/Player/Player.h"

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
	GET_INSTANCE(Camera)->SetExtents(VECTOR2D(float(FRAME_BUFFER_WIDTH), float(FRAME_BUFFER_HEIGHT)));
	GET_INSTANCE(Camera)->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0, 1);

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
	grade->SetPosition(VECTOR2D(600.f, 0.f));

	name = "Logo";
	Map* logo = new Map(name);
	m_objectList.emplace(name, logo);
	if (logo->Initialize(TextureInfo(L"../Resource/Textures/Map/Login/Logo.png", 306, 152, 1, 1, 0, 0)) == false)
		return false;
	logo->SetPosition(VECTOR2D(200.f, 150.f));

	name = "Player";
	m_player = new Player(name);
	if(m_player->Initialize(TextureInfo(L"../Resource/Textures/Character/Player.png", 133, 144, 1, 1, 0, 0)) == false)
		return false;

	return true;
}

void LoginScene::Update(float elapsedTime)
{
	for (auto object : m_objectList)
		object.second->Update(elapsedTime);

	m_player->Update(elapsedTime);

	GET_INSTANCE(Input)->Update(elapsedTime);
}

void LoginScene::Render()
{
	for (auto object : m_objectList)
	{
		if(GET_INSTANCE(Camera)->IsVisible(object.second) == true)
			object.second->Render();
	}

	m_player->Render();

	GET_INSTANCE(Input)->Render();
}
