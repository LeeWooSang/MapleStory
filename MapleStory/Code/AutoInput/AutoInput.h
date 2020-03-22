#pragma once
#include "../Macro.h"
#include "../Defines.h"

class AutoInput
{
	SINGLE_TONE(AutoInput)

	bool Initialize();

	LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM);
	LRESULT ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessMouseMessage(HWND, UINT, WPARAM, LPARAM);

private:
};