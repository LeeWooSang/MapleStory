#include "MouseInput.h"

INIT_INSTACNE(MouseInput)
MouseInput::MouseInput()
{
}

MouseInput::~MouseInput()
{
}


bool MouseInput::Initialize()
{
	return true;
}

LRESULT MouseInput::ProcessWindowMessage(HWND hWnd, UINT nMessageID, LPARAM lParam)
{
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	switch (nMessageID)
	{
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	{
		auto iter = m_shaderMap.find("Select");
		if (iter != m_shaderMap.end())
		{
			XMFLOAT3 position = ScreenPosition(mouseX, mouseY);
			reinterpret_cast<CCharacterSelectUIShader*>(m_ppShaders[CHARACTER_SELECT])->CallbackMouse(nMessageID, position.x, position.y);
		}
		break;
	}
	}

	return 0;
}

void MouseInput::Pos(int mouseX, int mouseY)
{

}
