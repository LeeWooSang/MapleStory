#pragma once
#include "../Macro.h"
#include "../Defines.h"

class Core
{
	SINGLE_TONE(Core)

	bool Initialize(HINSTANCE);
	int Run();

	const HWND& GetHwnd() const { return m_hWnd; }

private:
	ATOM MyRegisterClass();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	HINSTANCE		m_hInstance;
	HWND				m_hWnd;
	wstring				m_ClassName;

	static bool		m_isUpdate;
};
