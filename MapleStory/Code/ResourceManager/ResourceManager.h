#pragma once
#include "../Macro.h"
#include "../Defines.h"

struct StaticObjectInfo
{
	StaticObjectInfo(const string& name, float x, float y)
		: m_name(name), m_x(x), m_y(y) {}

	string m_name;
	float m_x;
	float m_y;
};

struct AnimatedObjectInfo
{
	AnimatedObjectInfo(const string& name, const string& animationName, float x, float y, int size)
		: m_name(name), m_animationName(animationName), m_x(x), m_y(y), m_size(size) {}

	string m_name;
	string m_animationName;

	float m_x;
	float m_y;
	int m_size;
};

class ResourceManager
{
	SINGLE_TONE(ResourceManager)

public:
	bool Initialize();
	bool LoadTexture();
	bool LoadScript();

	class Texture* GetTexture(const string&);
	StaticObjectInfo* GetStaticObjectInfo(const string&);
	AnimatedObjectInfo* GetAnimatedObjectInfo(const string&);

	void AddStaticObjectInfo(const string& name, float x, float y) { m_staticObjectInfoList.emplace(name, new StaticObjectInfo(name, x, y)); }
	void AddAnimatedObjectInfo(const string& name, const string& animationName, float x, float y, int size) { m_animatedObjectInfoList.emplace(name, new AnimatedObjectInfo(name, animationName, x, y, size)); }

private:
	unordered_map<string, class Texture*> m_textureList;
	unordered_map<string, StaticObjectInfo*> m_staticObjectInfoList;
	unordered_map<string, AnimatedObjectInfo*> m_animatedObjectInfoList;
};

