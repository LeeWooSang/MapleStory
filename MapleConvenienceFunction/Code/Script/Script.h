#pragma once
extern "C"
{
#include "include/lua.h"
#include "include/lauxlib.h"
#include "include/lualib.h"
}
#pragma comment(lib, "../Resource/Lua/Lib/lua53.lib")

class Script
{
public:
	Script();
	~Script();

	bool Initialize();
	void ErrorDisplay();
	lua_State* GetLua()	{ return m_lua; }

	static int API_GetCashItem(lua_State*);

private:
	lua_State* m_lua;
};

