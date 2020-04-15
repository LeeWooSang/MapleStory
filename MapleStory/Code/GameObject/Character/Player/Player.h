#pragma once
#include "../Character.h"

class Player : public Character
{
public:
	Player(const string&);
	virtual ~Player();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	void SetCollision(bool value) { m_collision = value; }

private:
	virtual void InitAnimation();

	void RegenerateWorldMatrix();
	void Move(float);
	void Move(char direction, float distance, bool velocity = false);
	void Move(VECTOR2D&, bool);

	void ProcessInput();

	VECTOR2D m_positionVector;
	VECTOR2D m_rightVector;
	VECTOR2D m_upVector;

	float           	m_friction;

	LPVOID m_pPlayerUpdatedContext;
	LPVOID m_pCameraUpdatedContext;

	bool m_collision;
};
