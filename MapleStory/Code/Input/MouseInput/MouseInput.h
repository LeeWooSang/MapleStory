#pragma once
#include "../Input.h"

class MouseInput : public Input
{
	SINGLE_TONE(MouseInput)

public:
	virtual bool Initialize();
	virtual LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, LPARAM);

	void Pos();

};