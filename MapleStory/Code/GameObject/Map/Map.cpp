#include "Map.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"
#include "../../ResourceManager/Script/Script.h"

Map::Map(const string& name)
	: GameObject(name)
{
}

Map::~Map()
{
}

bool Map::Initialize()
{
	if (GameObject::Initialize() == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;
	return true;
}

void Map::Update(float elapsedTime)
{
}

void Map::Render()
{	
	GameObject::Render();
}

void Map::InitWrap()
{
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	tex->InitWrap();
}

int Map::API_HenesysObjectInfo(lua_State * lua)
{
	 m_name = const_cast<char*>(lua_tostring(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	cout << name << ", " << x << ", " << y << endl;

	lua_pop(lua, 3);

	return 0;
}
