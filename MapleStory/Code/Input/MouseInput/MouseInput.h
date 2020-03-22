#pragma once
#include "../Input.h"

class MouseInput : public Input
{
	virtual bool Initialize() override;
	virtual LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM) override;
};