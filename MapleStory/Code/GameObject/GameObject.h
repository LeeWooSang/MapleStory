#pragma once
#include "../Defines.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual bool Initialize() = 0;
	virtual void Update(float) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	const XMFLOAT2& GetWorldPosition()	const { return m_WorldPosition; }
	void SetWorldPosition(const XMFLOAT2& pos) { m_WorldPosition = pos; }

	int GetID()		const { return m_ID; }
	void SetID(int id) { m_ID = id; }

protected:
	XMFLOAT2 m_WorldPosition;
	float m_Speed;
	int m_ID;
};
