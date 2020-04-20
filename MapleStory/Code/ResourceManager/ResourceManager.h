#pragma once
#include "../Macro.h"
#include "../Defines.h"

class ResourceManager
{
	SINGLE_TONE(ResourceManager)

public:
	bool Initialize();
	bool LoadTexture();
	bool LoadScript();

	class Texture* GetTexture(const string&);
	class Script* GetScript(const string&);

private:
	unordered_map<string, class Texture*> m_textureList;
	unordered_map<string, class Script*> m_scriptList;
};

