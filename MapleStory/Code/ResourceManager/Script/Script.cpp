#include "Script.h"
#include "../ResourceManager.h"

Script::Script()
{
	m_lua = nullptr;
}

Script::~Script()
{
	if (m_lua != nullptr)
	{
		lua_close(m_lua);
		m_lua = nullptr;
	}
}

bool Script::Initialize(const string& path)
{
	// 루아 객체 생성
	m_lua = luaL_newstate();
	if (m_lua == nullptr)
		return false;

	luaL_openlibs(m_lua);

	int error = luaL_loadfile(m_lua, path.c_str());
	if (error)
	{
		ErrorDisplay();
		return false;
	}

	error = lua_pcall(m_lua, 0, 0, 0);
	if (error)
	{
		ErrorDisplay();
		return false;
	}

	LoadStaticObjectInfoScript();
	LoadAnimatedObjectInfoScript();

	return true;
}

void Script::ErrorDisplay()
{
	cout << lua_tostring(m_lua, -1);
	lua_pop(m_lua, 1);
}

bool Script::LoadStaticObjectInfoScript()
{
	// 스크립트에 테이블이 몇개있는지
	lua_getglobal(m_lua, "g_staticObjectTableSize");	
	int size = static_cast<int>(lua_tonumber(m_lua, -1));
	lua_pop(m_lua, 1);

	// size 개수만큼 루프를 돔
	for (int i = 0; i < size; ++i)
	{
		lua_register(m_lua, "API_HenesysStaticObjectInfo", API_HenesysStaticObjectInfo);
		lua_getglobal(m_lua, "GetHenesysStaticObjectInfo");
		lua_pushnumber(m_lua, i);

		int error = lua_pcall(m_lua, 1, 0, 0);
		if (error)
		{
			ErrorDisplay();
			return false;
		}
	}

	return true;
}

bool Script::LoadAnimatedObjectInfoScript()
{
	// 스크립트에 테이블이 몇개있는지
	lua_getglobal(m_lua, "g_animatedObjectTableSize");
	int size = static_cast<int>(lua_tonumber(m_lua, -1));
	lua_pop(m_lua, 1);

	// size 개수만큼 루프를 돔
	for (int i = 0; i < size; ++i)
	{
		lua_register(m_lua, "API_HenesysAnimatedObjectInfo", API_HenesysAnimatedObjectInfo);
		lua_getglobal(m_lua, "GetHenesysAnimatedObjectInfo");
		lua_pushnumber(m_lua, i);

		int error = lua_pcall(m_lua, 1, 0, 0);
		if (error)
		{
			ErrorDisplay();
			return false;
		}
	}

	return true;
}

int Script::API_HenesysStaticObjectInfo(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	GET_INSTANCE(ResourceManager)->AddStaticObjectInfo(name, x, y);

	lua_pop(lua, 4);

	return 0;
}

int Script::API_HenesysAnimatedObjectInfo(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -5));
	string animationName = const_cast<char*>(lua_tostring(lua, -4));
	float x = static_cast<float>(lua_tonumber(lua, -3));
	float y = static_cast<float>(lua_tonumber(lua, -2));
	int size = static_cast<int>(lua_tonumber(lua, -1));

	GET_INSTANCE(ResourceManager)->AddAnimatedObjectInfo(name, animationName, x, y, size);

	lua_pop(lua, 6);

	return 0;
}
