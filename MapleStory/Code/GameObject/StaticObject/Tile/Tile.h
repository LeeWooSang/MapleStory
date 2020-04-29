#pragma once
#include "../StaticObject.h"

class Tile : public StaticObject
{
public:
	Tile(const string&);
	virtual ~Tile();

	virtual bool Initialize(const string&);

	virtual void Update(float);
	virtual void Render();

	void SetTopPos();
	bool CheckCollision(class AnimatedObject*);

private:
	VECTOR2D m_topStartPos;
	VECTOR2D m_topEndPos;
};