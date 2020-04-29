#pragma once
#include "../GameObject.h"

class AnimatedObject : public GameObject
{
public:
	AnimatedObject(const string&);
	virtual ~AnimatedObject();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
	virtual void RenderBoundingBox();

	virtual void SetDirection(char);
	virtual void SetRightVector(VECTOR2D);
	virtual void SetUpVector(VECTOR2D);
	virtual void SetPosition(VECTOR2D);
	
	virtual float GetObjectBottomPos();

	AnimatedObject* InitHierarchy(const string&);
	AnimatedObject* FindObject(const string&);

	void InitAnimation(int, const string&, const string&);
	void InitAnimation(int, const string&, const string&, AnimatedObject*);

	void SetAnimation(const string&);

protected:
	void RegenerateColliderAABB();
	void AddAnimationMap(const string& animationName, class Animation* ani) { m_animationMap.emplace(string(animationName), ani); }

	list<AnimatedObject*> m_hierarchyList;
	unordered_map<string, AnimatedObject*> m_hierarchyMap;
	string m_animation;
	unordered_map<string, class Animation*> m_animationMap;
};

