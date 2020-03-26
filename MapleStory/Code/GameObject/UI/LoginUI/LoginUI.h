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

	virtual void Input();

private:

};

