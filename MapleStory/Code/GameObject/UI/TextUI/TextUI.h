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

	// 굵기
	float m_width;
	// 높이
	float m_height;
	//글 간격
	float m_gap;

	float m_startX;
	float m_startY;
	float m_endX;
	float m_endY;
};

