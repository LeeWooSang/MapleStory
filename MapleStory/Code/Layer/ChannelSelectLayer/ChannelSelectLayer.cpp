#include "ChannelSelectLayer.h"
#include "../../GameObject/StaticObject/StaticObject.h"
#include "../../GameObject/UI/ButtonUI/ButtonUI.h"
#include "../../Network/Network.h"

ChannelSelectLayer::ChannelSelectLayer()
{
}

ChannelSelectLayer::~ChannelSelectLayer()
{
}

bool ChannelSelectLayer::Initialize()
{
	string name = "ChannelSelectBackground";
	StaticObject* background = new StaticObject(name);
	m_objectList.emplace_back(background);
	if (background->Initialize() == false)
		return false;
	background->SetPosition(VECTOR2D(0.f, 0.f));

	name = "ChannelWorldLogo";
	StaticObject* channelWorldLogo = new StaticObject(name);
	m_objectList.emplace_back(channelWorldLogo);
	if (channelWorldLogo->Initialize() == false)
		return false;
	channelWorldLogo->SetPosition(VECTOR2D(-105.f, -122.f));

	name = "ChannelSelectButton";
	ButtonUI* channelSelectButton = new ButtonUI(name);
	m_objectMap.emplace(CHANNEL_SELECT_OBJECT_KEY::CHANNEL_SELECT_BUTTON, channelSelectButton);
	if (channelSelectButton->Initialize() == false)
		return false;
	channelSelectButton->SetPosition(VECTOR2D(112.5f, -121.f));

	float x = -142.f;
	float y = -78.5f;

	float widthGap = 71.f;
	float heightGap = 30.f;

	int widthCount = 5;
	int heightCount = 1;

	for (int i = 0; i < widthCount; ++i)
	{
		name = "ChannelButton" + to_string(i +1);
		ButtonUI* channelButton = new ButtonUI(name);
		m_objectMap.emplace(CHANNEL_SELECT_OBJECT_KEY::CHANNEL_BUTTON1 * pow(2, i), channelButton);
		if (channelButton->Initialize() == false)
			return false;
		channelButton->SetPosition(VECTOR2D(x + widthGap * i, y + heightGap * 0));
		channelButton->SetIsDrawBoundingBox(false);
	}

	return true;
}

void ChannelSelectLayer::Update(float elapsedTime)
{
	for (auto object : m_objectList)
		object->Update(elapsedTime);

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

void ChannelSelectLayer::Render()
{
	for (auto object : m_objectList)
		object->Render();

	for (auto object : m_objectMap)
		object.second->Render();
}

bool ChannelSelectLayer::CheckCollision(GameObject* object, int& flag)
{
	if (Layer::CheckCollision(object, flag) == false)
		return false;

	return true;
}

void ChannelSelectLayer::ProcessCollision(GameObject* object, int& flag)
{
	char channel = 0;
	switch (flag)
	{
	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_SELECT_BUTTON_COLLISION_AND_CLICK:
		break;

	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_BUTTON1_COLLISION_AND_CLICK:	channel = 0;	break;
	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_BUTTON2_COLLISION_AND_CLICK:	channel = 1; break;
	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_BUTTON3_COLLISION_AND_CLICK:	channel = 2;	break;
	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_BUTTON4_COLLISION_AND_CLICK:	channel = 3; break;
	case PROCESS_CHANNEL_SELECT_COLLISION_TYPE::CHANNEL_BUTTON5_COLLISION_AND_CLICK:	channel = 4; break;

	default:
		break;
	}

	GET_INSTANCE(Network)->SendChannelLoginPacket(channel);
}

void ChannelSelectLayer::ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM)
{
}
