#include "Input.h"
#include <imm.h>
#pragma comment(lib,"imm32.lib")
#include "../D2DManager/D2DManager.h"

INIT_INSTACNE(Input)

Input::Input()
	: m_IMEMode(IMEMODE::ENGLISH), m_IsActive(false), m_Comb(L""), m_CaretPos(0)
{
	m_TextList.clear();
}

Input::~Input()
{
	m_TextList.clear();

	cout << "Input - 소멸자" << endl;
}

bool Input::Initialize()
{
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
		ProcessMouseMessage(hWnd, message, wParam, lParam);
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
				m_IsActive = !m_IsActive;
				break;

			case VK_ESCAPE:
				::PostQuitMessage(0);
				break;
			}
		}
	}

	if (m_IsActive == true)
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

void Input::ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT mouse{ 0 };
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	ScreenToClient(hWnd, &mouse);
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
	unsigned char key = static_cast<unsigned char>(m_TextList.size());
	wstring text;
	text = static_cast<wchar_t>(wParam);

	m_TextList.emplace_back(TextInfo(key, text));
	
	m_CaretPos = m_TextList.size();
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
			m_Comb = temp;
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

			unsigned char key = static_cast<unsigned char>(m_TextList.size());
			wstring text = temp;
			m_TextList.emplace_back(TextInfo(key, text));

			m_CaretPos = m_TextList.size();
			// 조합중인 글자는 지움
			m_Comb.clear();
		}
	}

	ImmReleaseContext(hWnd, himc);	// IME 핸들 반환!!
}

void Input::DeleteText()
{
	if (m_TextList.size() > 0)
	{
		//for (auto iter = m_TextList.begin(); iter != m_TextList.end(); )
		//{
		//	if ((*iter).m_Key == m_CaretPos - 1)
		//	{
		//		iter = m_TextList.erase(iter);
		//		--m_CaretPos;
		//	}

		//	else
		//		++iter;
		//}
		auto iter = m_TextList.end();
		m_TextList.erase(--iter);
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
	if (wParam == VK_LEFT)
	{
		if (--m_CaretPos < 0)
			m_CaretPos = 0;
	}
	else
	{
		if (++m_CaretPos > m_TextList.size())
			m_CaretPos = m_TextList.size();
	}
}

wstring Input::GetText() const
{
	wstring text = L"";

	for (auto iter = m_TextList.begin(); iter != m_TextList.end(); ++iter)
		text += (*iter).m_Text;

	return text;
}