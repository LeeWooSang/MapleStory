#pragma once
#include "../UI.h"

class TextUI : public UI
{
public:
	TextUI(const string&);
	virtual ~TextUI();

	virtual bool Initialize(TextureInfo);
	//virtual bool Initialize(GameObject*);
	virtual void Update(float);
	virtual void Render();
	void TextRender();

private:
	float m_enableTime;
	bool m_isEnable;
};

