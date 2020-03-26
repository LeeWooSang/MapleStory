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

