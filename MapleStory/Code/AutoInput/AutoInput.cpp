#include "AutoInput.h"

INIT_INSTACNE(AutoInput)

AutoInput::AutoInput()
{
}

AutoInput::~AutoInput()
{
	cout << "AutoInput - �Ҹ���" << endl;
}

bool AutoInput::Initialize()
{
	return true;
}

LRESULT AutoInput::ProcessWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
		//AltŰ ������ ��, ���ߴ� ������ �ذ��ϱ�����
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		ProcessKeyboardMessage(hWnd, message, wParam, lParam);
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		ProcessMouseMessage(hWnd, message, wParam, lParam);
		break;

	default:
		return(::DefWindowProc(hWnd, message, wParam, lParam));
	}

	return 0;
}

LRESULT AutoInput::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_CONTROL:
					cout << "Control Ű ����" << endl;
					break;

				default:
					break;
			}
		}
		break;
	}

	return 0;
}

void AutoInput::ProcessMouseMessage(HWND, UINT, WPARAM, LPARAM)
{
}
