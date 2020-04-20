#include "Script.h"

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

bool Script::LoadLuaScript(const string& path)
{
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

	// ��ũ��Ʈ�� ���̺��� ��ִ���
	lua_getglobal(m_lua, "g_tableSize");	
	int size = static_cast<int>(lua_tonumber(m_lua, -1));
	lua_pop(m_lua, 1);

	// size ������ŭ ������ ��
	for (int i = 0; i < size; ++i)
	{
		lua_register(m_lua, "API_HenesysObjectInfo", API_HenesysObjectInfo);
		lua_getglobal(m_lua, "GetHenesysObjectInfo");
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


int Script::API_HenesysObjectInfo(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -3));
	float x = static_cast<float>(lua_tonumber(lua, -2));
	float y = static_cast<float>(lua_tonumber(lua, -1));

	cout << name << ", " << x << ", " << y << endl;

	lua_pop(lua, 3);

	return 0;
}

int Script::API_GetArcaneSymbolInfo(lua_State* lua)
{
	string name = const_cast<char*>(lua_tostring(lua, -2));
	int requestLevel = static_cast<int>(lua_tonumber(lua, -1));
	lua_pop(lua, 3);

	//GET_INSTANCE(Resource)->AddNormalItemInfo(name, requestLevel);

	return 0;
}
