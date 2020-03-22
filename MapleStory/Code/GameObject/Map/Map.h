#pragma once
#include "../GameObject.h"

class Map : public GameObject
{
public:
	Map();
	virtual ~Map();

	virtual bool Initialize() override;
	virtual void Update(float) override;
	virtual void Render() override;
	virtual void Release() override;
};