#pragma once
#include "../GameObject.h"

class Caret : public GameObject
{
public:
	Caret();
	virtual ~Caret();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
	virtual void Release();

private:
	float m_enableTime;
	float m_disableTime;
	bool m_isEnable;
};

