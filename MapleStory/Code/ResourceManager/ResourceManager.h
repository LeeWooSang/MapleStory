#pragma once
#include "../Macro.h"
#include "../Defines.h"

class ResourceManager
{
	SINGLE_TONE(ResourceManager)

public:
	bool Initialize();
	bool LoadTexture();
	class Texture* GetTexture(const string&);

private:
	unordered_map<string, class Texture*> m_textureList;
};

