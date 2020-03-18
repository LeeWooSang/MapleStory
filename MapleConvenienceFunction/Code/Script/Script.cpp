#include "Script.h"
#include "../Defines.h"
#include "../Resource/Resource.h"

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

bool Script::Initialize()
{
	// ��� ��ü ����
	m_lua = luaL_newstate();
	if (m_lua == nullptr)
		return false;

	luaL_openlibs(m_lua);

	return true;
}

void Script::ErrorDisplay()
{
	cout << lua_tostring(m_lua, -1);
	lua_pop(m_lua, 1);
}

bool Script::LoadICashtemInfoScript()
{
	int error = luaL_loadfile(m_lua, "../Resource/Script/CashItemInfo.lua");
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

bool Script::LoadJobInfoScript()
{
	int error = luaL_loadfile(m_lua, "../Resource/Script/JobInfo.lua");
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
		lua_register(m_lua, "API_GetJobInfo", API_GetJobInfo);
		lua_getglobal(m_lua, "GetJobInfo");
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

int Script::API_GetCashItem(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -3));
	int price = static_cast<int>(lua_tonumber(lua, -2));
	int size = static_cast<int>(lua_tonumber(lua, -1));
	lua_pop(lua, 4);

	GET_INSTANCE(Resource)->AddItemInfo(name, price, size);

	return 0;
}

int Script::API_GetJobInfo(lua_State* lua)
{
	string occupationalCluster = const_cast<char*>(lua_tostring(lua, -4));
	string jobName = const_cast<char*>(lua_tostring(lua, -3));
	int mainStat = static_cast<int>(lua_tonumber(lua, -2));
	int effect = static_cast<int>(lua_tonumber(lua, -1));
	lua_pop(lua, 5);

	GET_INSTANCE(Resource)->AddJobInfo(occupationalCluster, jobName, mainStat, effect);

	return 0;
}
