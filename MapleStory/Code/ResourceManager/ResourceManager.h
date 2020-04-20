#pragma once
#include "../Macro.h"
#include "../Defines.h"

struct ObjectInfo
{
	ObjectInfo(const string& name, float x, float y)
		: m_name(name), m_x(x), m_y(y) {}

	string m_name;
	float m_x;
	float m_y;
};

class ResourceManager
{
	SINGLE_TONE(ResourceManager)

public:
	bool Initialize();
	bool LoadTexture();
	bool LoadScript();

	class Texture* GetTexture(const string&);
	ObjectInfo* GetObjectInfo(const string&);

	void AddObjectInfo(const string& name, float x, float y) { m_objectInfoList.emplace(name, new ObjectInfo(name, x, y)); }

private:
	unordered_map<string, class Texture*> m_textureList;
	unordered_map<string, ObjectInfo*> m_objectInfoList;
};

