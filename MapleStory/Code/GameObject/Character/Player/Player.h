#pragma once
#include "../Character.h"

class Player : public Character
{
public:
	Player(const string&);
	virtual ~Player();

	virtual bool Initialize(TextureInfo);
	virtual void Update(float);
	virtual void Render();

private:
	void RegenerateWorldMatrix();
	void Move(float);
	void Move(char direction, float distance, bool velocity = false);
	void Move(VECTOR2D&, bool);

	VECTOR2D m_positionVector;
	VECTOR2D m_rightVector;
	VECTOR2D m_upVector;

	float           	m_friction;

	LPVOID m_pPlayerUpdatedContext;
	LPVOID m_pCameraUpdatedContext;
};

enum DIRECTION
{
	RIGHT = 0x0001,
	LEFT = 0x0002,
	UP = 0x0004,
	DOWN = 0x0008
};