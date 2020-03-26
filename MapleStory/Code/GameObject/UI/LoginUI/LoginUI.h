#pragma once
#include "../UI.h"

class LoginUI : public UI
{
public:
	LoginUI(const string&);
	virtual ~LoginUI();

	virtual bool Initialize(TextureInfo);
	virtual void Update(float);
	virtual void Render();
	void TextRender();

	virtual void Input();

	void SetIsTextRender(bool isTextRender) { m_isTextRender = isTextRender; }

private:
	bool m_isTextRender;
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

