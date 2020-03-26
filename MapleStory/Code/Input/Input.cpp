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
	case WM_IME_NOTIFY:			// 한자입력...
	case WM_CHAR:				// 1byte 문자 (ex : 영어)
	case WM_KEYDOWN:
	case WM_KEYUP:
		//Alt키 눌렀을 때, 멈추는 현상을 해결하기위해
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
		case WM_CHAR:				// 1byte 문자 (ex : 영어)
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

	// 한글 조합중이라면,
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

	// 한글이 완성됬다면,
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
			// 조합중인 글자는 지움
			m_comb.clear();
		}
	}

	ImmReleaseContext(hWnd, himc);	// IME 핸들 반환!!
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

	// 상태를 바꿉니다. 
	if (korean)
		temp |= IME_CMODE_NATIVE;      // 한글 
	else
		temp |= IME_CMODE_ALPHANUMERIC;  // 영문

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
	m_flag = false; // 초기화하고 시작하여 버튼이 하나라도 눌려있으면 True처리.

	for(auto& key : m_keyStateList)
	{
		// 버튼이 정의되어있지 않으면(버튼 설정이 안된 상태)
		if (key.m_keyType == KEY_TYPE::NONE) 
			continue; 

		// 지금 확인하는 버튼이 눌린 상태면
		if (KEY_DOWN(key.m_keyType)) 
		{
			// 버튼이 눌리지 않은 상태였던 경우 즉, 지금 막 버튼이 눌린 상태인 경우
			if (key.m_pushing == false) 
				key.m_pushed = true; // 지금 버튼이 눌렸다고 알림

			// 버튼을 계속 누르고 있을 때,
			else 
				key.m_pushed = false; // 버튼이 지금 눌린 것은 아니라고 알림

			// 버튼이 눌린 상태
			// 어떤 버튼이든 현재 눌린 상태이므로 True 입력
			key.m_pushing = true; 
			m_flag = true; 
		}

		// 키가 눌리지 않을 때 처리
		else
		{
			// 키를 눌렀다가 땔 때,
			if (key.m_pushing == true)
				key.m_pop = true; // 지금 버튼을 뗐다고 알림.

			// 키를 누르지도 않았을 떄,
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
