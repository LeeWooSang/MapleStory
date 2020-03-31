#pragma once
#include "../UI.h"

class ButtonUI : public UI
{
public:
	ButtonUI(const string&);
	virtual ~ButtonUI();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();
};

