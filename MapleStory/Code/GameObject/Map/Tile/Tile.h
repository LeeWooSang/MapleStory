#pragma once
#include "../Map.h"

class Tile : public Map
{
public:
	Tile(const string&);
	virtual ~Tile();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	void GetTopPos();
	bool CheckCollision(GameObject*);

private:
	VECTOR2D m_topStartPos;
	VECTOR2D m_topEndPos;
};