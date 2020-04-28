#include "WorldSelectBaseLayer.h"
#include "../../GameObject/StaticObject/StaticObject.h"

WorldSelectBaseLayer::WorldSelectBaseLayer()
{
}

WorldSelectBaseLayer::~WorldSelectBaseLayer()
{
}

bool WorldSelectBaseLayer::Initialize()
{
	string name = "WorldSelectBackground";
	StaticObject* background = new StaticObject(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "WorldSelectFrame";
	StaticObject* worldSelectFrame = new StaticObject(name);
	m_objectList.emplace_back(worldSelectFrame);
	if (worldSelectFrame->Initialize() == false)
		return false;
	worldSelectFrame->SetPosition(VECTOR2D(310.f, -5.f));

	name = "Frame";
	StaticObject* frame = new StaticObject(name);
	m_objectList.emplace_back(frame);
	if (frame->Initialize() == false)
		return false;
	frame->SetPosition(VECTOR2D(0.f, 0.f));

	name = "WorldSelectLogo";
	StaticObject* worldSelectlogo = new StaticObject(name);
	m_objectList.emplace_back(worldSelectlogo);
	if (worldSelectlogo->Initialize() == false)
		return false;
	worldSelectlogo->SetPosition(VECTOR2D(-300.f, -279.f));

	name = "ChannelSelectBackground";
	return true;
}

void WorldSelectBaseLayer::Update(float elapsedTime)
{
	for (auto object : m_objectList)
		object->Update(elapsedTime);
}

void WorldSelectBaseLayer::Render()
{
	for (auto object : m_objectList)
		object->Render();
}

bool WorldSelectBaseLayer::CheckCollision(GameObject*, int&)
{
	return false;
}

void WorldSelectBaseLayer::ProcessCollision(GameObject*, int&)
{
}

void WorldSelectBaseLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
