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

	bool Initialize(const string&);
	void ErrorDisplay();

	bool LoadStaticObjectInfoScript();
	bool LoadAnimatedObjectInfoScript();
	bool LoadCharacterObjectInfoScript();

	// API ÇÔ¼öµé
public:
	static int API_HenesysStaticObjectInfo(lua_State*);
	static int API_HenesysAnimatedObjectInfo(lua_State*);
	static int API_CharacterObjectInfo(lua_State*);

private:
	lua_State* m_lua;
};

