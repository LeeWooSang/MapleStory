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

private:
	void RegenerateWorldMatrix();
	void Move(VECTOR2D&, bool);


	class Camera* m_camera;

	VECTOR2D m_positionVector;
	VECTOR2D m_rightVector;
	VECTOR2D m_upVector;

	VECTOR2D m_vMaxVelocity;
	float           	m_friction;

	LPVOID m_pPlayerUpdatedContext;
	LPVOID m_pCameraUpdatedContext;
};