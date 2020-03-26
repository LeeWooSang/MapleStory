#pragma once
#include "../Defines.h"
#include "../D2DManager/D2DManager.h"
#include "../Collision/Collision.h"

class GameObject
{
public:
	GameObject(const string&);
	virtual ~GameObject();

	virtual bool Initialize();
	virtual bool Initialize(TextureInfo);
	virtual void Update(float) = 0;
	virtual void Render();
	void RenderBoundingBox();

	 Matrix3x2F& GetWorldMatrix() { return m_worldMatrix; }
	
	Collider* GetCollider()	 { return m_collider; }
	void SetCollider(Collider* collider) { m_collider = collider; }

	VECTOR2D GetRightVector() const;
	void SetRightVector(VECTOR2D);

	VECTOR2D GetUpVector()	const;
	void SetUpVector(VECTOR2D);

	VECTOR2D GetPositionVector()	const;
	void SetPosition(VECTOR2D);

	VECTOR2D GetSize(Matrix3x2F* pd2dmtxTransform = nullptr);

	void SetIsDrawBoundingBox(bool value) { m_isDrawBoundingBox = value; }

protected:
	string m_name;
	Matrix3x2F m_worldMatrix;
	class Collider* m_collider;

	float m_angle;

	VECTOR2D m_velocity;
	VECTOR2D m_maxVelocity;

	VECTOR2D m_gravity;

	bool m_isDrawBoundingBox;
};
