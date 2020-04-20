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
	
	 void SetDirection(char dir);

	Collider* GetCollider()	 { return m_collider; }
	void SetCollider(Collider* collider) { m_collider = collider; }

	VECTOR2D GetRightVector() const;
	void SetRightVector(VECTOR2D);

	VECTOR2D GetUpVector()	const;
	void SetUpVector(VECTOR2D);

	VECTOR2D GetPositionVector()	const;
	void SetPosition(VECTOR2D);

	VECTOR2D GetVelocity()	const { return m_velocity; }
	void SetVelocity(VECTOR2D velocity) { m_velocity = velocity; };

	VECTOR2D GetSize(Matrix3x2F* pd2dmtxTransform = nullptr);

	void SetIsDrawBoundingBox(bool value) { m_isDrawBoundingBox = value; }

	void SetCollisionObject(GameObject* object) { m_collisionObject = object; }

	list<GameObject*>& GetHierarchyList() { return m_hierarchyList; }
	GameObject* FindObject(const string& name);
	//virtual void InitHierarchyMap() = 0;

protected:
	string m_name;
	Matrix3x2F m_worldMatrix;
	char m_direction;

	class Collider* m_collider;

	float m_angle;

	VECTOR2D m_velocity;
	VECTOR2D m_maxVelocity;

	VECTOR2D m_gravity;

	bool m_isDrawBoundingBox;

	unordered_map<string, GameObject*> m_hierarchyMap;
	list<GameObject*> m_hierarchyList;

	GameObject* m_collisionObject;
};
