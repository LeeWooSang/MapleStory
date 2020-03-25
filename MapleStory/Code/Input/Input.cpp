#include "Input.h"
#include <imm.h>
#pragma comment(lib,"imm32.lib")
#include "../D2DManager/D2DManager.h"
#include "../Network/Network.h"

INIT_INSTACNE(Input)
Input::Input()
{
	m_isActive = false;
	m_IMEMode = IMEMODE::ENGLISH;
	m_comb.clear();
	m_textList.clear();

	m_width = 0.f;
	m_height = 0.f;
	m_gap = 0.f;
	m_startX = 0.f;
	m_startY = 0.f;
	m_endX = 0.f;
	m_endY = 0.f;
}

Input::~Input()
{
	m_textList.clear();
}

bool Input::Initialize()
{
	m_width = 1.5f;
	m_height = 25.f;
	m_gap = 2.f;

	m_startX = 10.f;
	m_startY = 10.f;

	m_endX = m_startX;
	m_endY = m_startY + m_height;

	return true;
}

void Input::Update(float elapsedTime)
{
	m_enableTime += elapsedTime;

	if (m_isEnable == true && m_enableTime > 0.8f)
	{
		m_isEnable = false;
		m_enableTime = 0.f;
	}

	if (m_isEnable == false && m_enableTime > 0.5f)
	{
		m_isEnable = true;
	}
}

void Input::Render()
{
	if (m_isActive == false)
		return;

	D2D_POINT_2F startPos{ m_startX, m_startY };
	D2D_POINT_2F endPos{ m_endX, m_endY };

	wstring text = GetText();
	if (text.size() > 0)
	{
		IDWriteTextLayout* layout = nullptr;
		HRESULT result = GET_INSTANCE(D2DManager)->GetWriteFactory()->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()), 
			GET_INSTANCE(D2DManager)->GetFontInfo("������").m_pFont, 4096.0f, 4096.0f, &layout);

		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawTextLayout(startPos, layout, GET_INSTANCE(D2DManager)->GetFontColor("������"));

		DWRITE_TEXT_METRICS metris;
		layout->GetMetrics(&metris);
		startPos.x += metris.width + m_gap;
		endPos.x = startPos.x;

		layout->Release();
	}

	if (m_isEnable)
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, GET_INSTANCE(D2DManager)->GetFontColor("������"), m_width, 0);
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