#pragma once
#include "../GameObject.h"

class Map : public GameObject
{
public:
	Map(const string&);
	virtual ~Map();

	virtual bool Initialize(TextureInfo);
	virtual void Update(float);
	virtual void Render();

};