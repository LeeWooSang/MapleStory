#include "Script.h"
#include "../Defines.h"
#include "../Resource/Resource.h"

Script::Script()
{
	m_lua = nullptr;
}

Script::~Script()
{
	if(m_lua != nullptr)
		lua_close(m_lua);
}

bool Script::Initialize()
{
	// 风酒 按眉 积己
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);

	int error = luaL_loadfile(m_lua, "../Resource/Lua/Script/ItemInfo.lua");
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

	lua_getglobal(m_lua, "g_TableSize");
	int size = static_cast<int>(lua_tonumber(m_lua, -1));
	lua_pop(m_lua, 1);

	for (int i = 0; i < size; ++i)
	{
		lua_register(m_lua, "API_GetCashItem", API_GetCashItem);
		lua_getglobal(m_lua, "GetCashItem");
		lua_pushnumber(m_lua, i);

		error = lua_pcall(m_lua, 1, 0, 0);
		if (error)
		{
			ErrorDisplay();
			return false;
		}
	}

	return true;
}

void Script::ErrorDisplay()
{
	cout << lua_tostring(m_lua, -1);
	lua_pop(m_lua, 1);
}

int Script::API_GetCashItem(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -3));
	int price = static_cast<int>(lua_tonumber(lua, -2));
	int size = static_cast<int>(lua_tonumber(lua, -1));
	lua_pop(lua, 4);

	GET_INSTANCE(Resource)->AddItemInfo(name, price, size);

	return 0;
}
