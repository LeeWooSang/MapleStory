#pragma once
#include "../Macro.h"
#include "../Defines.h"

struct StaticObjectInfo
{
	StaticObjectInfo(const string& objectName, const string& textureName, float x, float y)
		: m_objectName(objectName), m_textureName(textureName), m_x(x), m_y(y) {}

	string m_objectName;
	string m_textureName;
	float m_x;
	float m_y;
};

struct AnimatedObjectInfo
{
	AnimatedObjectInfo(const string& objectName, const string& animationName, const string& textureName, float x, float y, int size)
		: m_objectName(objectName), m_animationName(animationName), m_textureName(textureName), m_x(x), m_y(y), m_size(size) {}

	string m_objectName;
	string m_animationName;
	string m_textureName;

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
	unordered_multimap<string, StaticObjectInfo*>& GetStaticObjectInfoList() { return m_staticObjectInfoList; }
	unordered_multimap<string, AnimatedObjectInfo*>& GetCharacterObjectInfoList() { return m_characterObjectInfoList; }

	void AddStaticObjectInfo(const string& objectName, const string& textureName, float x, float y) { m_staticObjectInfoList.emplace(objectName, new StaticObjectInfo(objectName, textureName, x, y)); }
	void AddAnimatedObjectInfo(const string& objectName, const string& animationName, const string& textureName, float x, float y, int size) { m_animatedObjectInfoList.emplace(objectName, new AnimatedObjectInfo(objectName, animationName, textureName, x, y, size)); }
	void AddCharacterObjectInfo(const string& objectName, const string& animationName, const string& textureName, float x, float y, int size) { m_characterObjectInfoList.emplace(objectName, new AnimatedObjectInfo(objectName, animationName, textureName, x, y, size)); }

private:
	unordered_map<string, class Texture*> m_textureList;

	unordered_multimap<string, StaticObjectInfo*> m_staticObjectInfoList;
	unordered_map<string, AnimatedObjectInfo*> m_animatedObjectInfoList;
	unordered_multimap<string, AnimatedObjectInfo*> m_characterObjectInfoList;
};

