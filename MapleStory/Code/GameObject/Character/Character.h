#pragma once
#include "../GameObject.h"

class Character : public GameObject
{
public:
	Character(const string&);
	virtual ~Character();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
	virtual void RenderBoundingBox();

	virtual bool InitHierarchyMap();
	virtual void InitAnimation();

	void RegenerateColliderAABB();
	void SetAnimation(const string&);
	void AddAnimation(const string& animationName, class Animation* ani) { m_animationMap.emplace(string(animationName), ani); }

protected:
	string m_animation;
	unordered_map<string, class Animation*> m_animationMap;
};

