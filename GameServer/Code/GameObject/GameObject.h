#pragma once
#include "../Defines.h"

class GameObject
{
public:
	GameObject();
	GameObject(const string&);
	virtual ~GameObject();

	virtual bool Initialize(void* = nullptr) = 0;
	virtual void Update() = 0;

	virtual void ClearObjectInfo();

	const string& GetName()	const { return m_name; }
	void SetName(const string& name) { m_name = name; }

protected:
	string m_name;
};

