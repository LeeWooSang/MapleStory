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
	virtual void Update(float) = 0;
	virtual void Render();
	virtual void RenderBoundingBox();

	const string& GetName()	const { return m_name; }

	 Matrix3x2F& GetWorldMatrix() { return m_worldMatrix; }
	
	 virtual void SetDirection(char dir) { m_direction = dir; }

	Collider* GetCollider()	 { return m_collider; }
	void SetCollider(Collider* collider) { m_collider = collider; }

	virtual VECTOR2D GetRightVector() const;
	virtual void SetRightVector(VECTOR2D);

	virtual VECTOR2D GetUpVector()	const;
	virtual void SetUpVector(VECTOR2D);

	virtual VECTOR2D GetPositionVector()	const;
	virtual void SetPosition(VECTOR2D);

	VECTOR2D GetVelocity()	const { return m_velocity; }
	void SetVelocity(VECTOR2D velocity) { m_velocity = velocity; };

	VECTOR2D GetSize(Matrix3x2F* pd2dmtxTransform = nullptr);

	void SetIsDrawBoundingBox(bool value) { m_isDrawBoundingBox = value; }

	void SetCollisionObject(GameObject* object) { m_collisionObject = object; }

protected:
	string m_name;
	unordered_map<string, class Texture*> m_textureMap;

	Matrix3x2F m_worldMatrix;
	char m_direction;

	class Collider* m_collider;

	float m_angle;

	VECTOR2D m_velocity;
	VECTOR2D m_maxVelocity;

	VECTOR2D m_gravity;

	bool m_isDrawBoundingBox;

	GameObject* m_collisionObject;
};
