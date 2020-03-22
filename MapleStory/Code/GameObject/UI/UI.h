#pragma once
#include "../GameObject.h"

class UI : public GameObject
{
public:
	UI();
	virtual ~UI();

	virtual bool Initialize() = 0;
	virtual void Update(float) override;
	virtual void Render() override;
	virtual void Release() override;

protected:
};