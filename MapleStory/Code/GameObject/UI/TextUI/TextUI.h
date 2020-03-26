#pragma once
#include "../UI.h"

class TextUI : public UI
{
public:
	TextUI(const string&);
	virtual ~TextUI();

	virtual bool Initialize(GameObject*);
	virtual void Update(float);
	virtual void Render();

private:
	float m_enableTime;
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

