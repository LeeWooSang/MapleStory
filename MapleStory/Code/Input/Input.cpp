#include "Input.h"
#include <imm.h>
#pragma comment(lib,"imm32.lib")
#include "../D2DManager/D2DManager.h"
#include "../Network/Network.h"
#include "../Scene/SceneManager.h"
#include "../Scene/LoginScene/LoginScene.h"

INIT_INSTACNE(Input)
Input::Input()
{
	m_isActive = false;
	m_IMEMode = IMEMODE::ENGLISH;
	m_comb.clear();
	m_textList.clear();

	m_mousePos.x = 0;
	m_mousePos.y = 0;
}

Input::~Input()
{
	m_textList.clear();
}

bool Input::Initialize()
{
	m_keyStateList[KEY_TYPE::NONE].m_keyType = KEY_TYPE::NONE;
	m_keyStateList[KEY_TYPE::KEYBOARD_LEFT].m_keyType = VK_LEFT;
	m_keyStateList[KEY_TYPE::KEYBOARD_RIGHT].m_keyType = VK_RIGHT;
	m_keyStateList[KEY_TYPE::KEYBOARD_UP].m_keyType = VK_UP;
	m_keyStateList[KEY_TYPE::KEYBOARD_DOWN].m_keyType = VK_DOWN;
	m_keyStateList[KEY_TYPE::MOUSE_LBUTTON].m_keyType = VK_LBUTTON;
	m_keyStateList[KEY_TYPE::MOUSE_RBUTTON].m_keyType = VK_RBUTTON;

	return true;
}

LRESULT Input::ProcessWindowMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_IME_COMPOSITION:
	case WM_IME_NOTIFY:			// �����Է�...
	case WM_CHAR:				// 1byte ���� (ex : ����)
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
		ProcessMouseMessage(hWnd, message, lParam);
		break;

	default:
		return(::DefWindowProc(hWnd, message, wParam, lParam));
	}

	return 0;
}

LRESULT Input::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RETURN:
				m_isActive = !m_isActive;
				break;

			case VK_ESCAPE:
				::PostQuitMessage(0);
				break;
			}
		}
	}

	if (m_isActive == true)
	{
		switch (message)
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
			switch (wParam)
			{
			case VK_BACK:
				DeleteText();
				break;

			case VK_HANGEUL:
				m_IMEMode = !m_IMEMode;
				ChangeIMEMode(hWnd, m_IMEMode);
				break;

			case VK_LEFT:
			case VK_RIGHT:
				ControlCaret(wParam);
				break;
			}
			break;
		}

		switch (message)
		{
		case WM_CHAR:				// 1byte ���� (ex : ����)
			ProcessEnglish(hWnd, wParam);
			break;

		case WM_IME_COMPOSITION:
			ProcessKorean(hWnd, lParam);
			break;

		case WM_IME_NOTIFY:
			break;
		}
	}
	
	return 0;
}

void Input::ProcessMouseMessage(HWND hWnd, UINT message, LPARAM lParam)
{
	m_mousePos.x = LOWORD(lParam);
	m_mousePos.y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:

		//cout << "X : " << x << ", Y : " << y << endl;
		//cout << "mX : " << mouse.x << ", mY : " << mouse.y << endl;
		break;

	default:
		break;
	}
}

void Input::ProcessEnglish(HWND hWnd, WPARAM wParam)
{
	unsigned char key = static_cast<unsigned char>(m_textList.size());

	wstring text = L"";
	text = static_cast<wchar_t>(wParam);
	if (text == L"\r")
	{
		WStringToString();
		return;
	}

	m_textList.emplace_back(TextInfo(key, text));
}

void Input::ProcessKorean(HWND hWnd, LPARAM lParam)
{
	HIMC himc = ImmGetContext(hWnd);
	int len = 0;
	wchar_t temp[10] = { 0, };

	// �ѱ� �������̶��,
	if (lParam & GCS_COMPSTR)
	{
		len = ImmGetCompositionStringW(himc, GCS_COMPSTR, nullptr, 0);
		if (len > 0)
		{
			ImmGetCompositionStringW(himc, GCS_COMPSTR, temp, len);
			temp[len] = 0;
			m_comb = temp;
		}
	}

	// �ѱ��� �ϼ���ٸ�,
	else if (lParam & GCS_RESULTSTR)
	{
		len = ImmGetCompositionStringW(himc, GCS_RESULTSTR, nullptr, 0);
		if (len > 0)
		{
			ImmGetCompositionStringW(himc, GCS_RESULTSTR, temp, len);
			temp[len] = 0;

			unsigned char key = static_cast<unsigned char>(m_textList.size());
			wstring text = temp;
			m_textList.emplace_back(TextInfo(key, text));
			// �������� ���ڴ� ����
			m_comb.clear();
		}
	}

	ImmReleaseContext(hWnd, himc);	// IME �ڵ� ��ȯ!!
}

void Input::DeleteText()
{
	if (m_textList.size() > 0)
	{
		//for (auto iter = m_textList.begin(); iter != m_textList.end(); )
		//{
		//	if ((*iter).m_Key == m_CaretPos - 1)
		//	{
		//		iter = m_textList.erase(iter);
		//		--m_CaretPos;
		//	}

		//	else
		//		++iter;
		//}
		auto iter = m_textList.end();
		m_textList.erase(--iter);
	}
}

void Input::ChangeIMEMode(HWND hWnd, bool korean)
{
	HIMC himc = ImmGetContext(hWnd);
	DWORD sentence;
	DWORD temp;

	ImmGetConversionStatus(himc, &m_IMEMode, &sentence);

	temp = m_IMEMode & ~IME_CMODE_LANGUAGE;

	// ���¸� �ٲߴϴ�. 
	if (korean)
		temp |= IME_CMODE_NATIVE;      // �ѱ� 
	else
		temp |= IME_CMODE_ALPHANUMERIC;  // ����

	m_IMEMode = temp;

	ImmSetConversionStatus(himc, m_IMEMode, sentence);
	ImmReleaseContext(hWnd, himc);
}

void Input::ControlCaret(WPARAM wParam)
{
}

wstring Input::GetText() const
{
	wstring text = L"";

	for (auto iter = m_textList.begin(); iter != m_textList.end(); ++iter)
		text += (*iter).m_Text;

	return text;
}

void Input::WStringToString()
{
	string s = "";
	for (auto data : m_textList)
	{
		char temp[10] = { 0, };
		wcstombs(temp, const_cast<wchar_t*>(data.m_Text.c_str()), data.m_Text.length());
		s += temp;
	}
	GET_INSTANCE(Network)->SetServerIP(s);
	GET_INSTANCE(Network)->Connect();
}

void Input::ProcessKeyEvent()
{
	m_flag = false; // �ʱ�ȭ�ϰ� �����Ͽ� ��ư�� �ϳ��� ���������� Trueó��.

	for(auto& key : m_keyStateList)
	{
		// ��ư�� ���ǵǾ����� ������(��ư ������ �ȵ� ����)
		if (key.m_keyType == KEY_TYPE::NONE) 
			continue; 

		// ���� Ȯ���ϴ� ��ư�� ���� ���¸�
		if (KEY_DOWN(key.m_keyType)) 
		{
			// ��ư�� ������ ���� ���¿��� ��� ��, ���� �� ��ư�� ���� ������ ���
			if (key.m_pushing == false) 
				key.m_pushed = true; // ���� ��ư�� ���ȴٰ� �˸�

			// ��ư�� ��� ������ ���� ��,
			else 
				key.m_pushed = false; // ��ư�� ���� ���� ���� �ƴ϶�� �˸�

			// ��ư�� ���� ����
			// � ��ư�̵� ���� ���� �����̹Ƿ� True �Է�
			key.m_pushing = true; 
			m_flag = true; 
		}

		// Ű�� ������ ���� �� ó��
		else
		{
			// Ű�� �����ٰ� �� ��,
			if (key.m_pushing == true)
				key.m_pop = true; // ���� ��ư�� �ôٰ� �˸�.

			// Ű�� �������� �ʾ��� ��,
			else
				key.m_pop = false;

			key.m_pushing = false;
			key.m_pushed = false;
		}
	}
}

bool Input::KeyOnceCheck(KEY_TYPE key)
{
	ProcessKeyEvent();

	if (m_keyStateList[key].m_pop == true)
		return true;

	return false;
}
