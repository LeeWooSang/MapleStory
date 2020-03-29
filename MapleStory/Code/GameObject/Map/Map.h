#pragma once
#include "../GameObject.h"

class Map : public GameObject
{
public:
	Map(const string&);
	virtual ~Map();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

};