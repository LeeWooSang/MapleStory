#pragma once
#include "../GameObject.h"

class Caret : public GameObject
{
public:
	Caret();
	virtual ~Caret();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
	virtual void Release();

	void SetEndX(float x) { m_endX = x; }
	void SetEndY(float y) { m_endY = y; }

private:
	float m_enableTime;
	float m_disableTime;
	bool m_isEnable;

	// ����
	float m_width;
	// ����
	float m_height;
	//�� ����
	float m_gap;

	float m_startX;
	float m_startY;

	float m_endX;
	float m_endY;
};

