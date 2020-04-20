#pragma once
#include "../../Defines.h"

extern "C"
{
#include "Lua/include/lua.h"
#include "Lua/include/lauxlib.h"
#include "Lua/include/lualib.h"
}
#pragma comment(lib, "../Code/ResourceManager/Script/Lua/lib/lua53.lib")

class Script
{
public:
	Script();
	~Script();

	bool Initialize();
	void ErrorDisplay();

	bool LoadLuaScript(const string&);
	
	lua_State* GetLua() { return m_lua; }

	static int API_HenesysObjectInfo(lua_State*);
	static int API_GetArcaneSymbolInfo(lua_State*);

private:
	lua_State* m_lua;
};

