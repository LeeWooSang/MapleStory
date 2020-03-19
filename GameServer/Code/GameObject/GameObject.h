#pragma once
#include "../../../MapleConvenienceFunction/Code/Defines.h"

class GameObject
{
public:
	GameObject();
	GameObject(const string&);
	virtual ~GameObject();

	virtual bool Initialize(void* = nullptr) = 0;
	virtual void Update() = 0;

	const string& GetName()	const { return m_name; }

protected:
	string m_name;
};

