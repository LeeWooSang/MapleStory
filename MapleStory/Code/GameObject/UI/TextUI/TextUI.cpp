#include "TextUI.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../../ResourceManager/Texture/Texture.h"
#include "../../../Camera/Camera.h"

TextUI::TextUI(const string& name)
	: UI(name)
{
	m_isActive = false;
	m_enableTime = 0.f;
	m_isEnable = false;

	m_textList.clear();
	m_IMEMode = IMEMODE::ENGLISH;
	m_comb.clear();

	m_flag = 0x0000;
}

TextUI::~TextUI()
{
	m_isActive = false;
	m_enableTime = 0.f;
	m_isEnable = false;

	m_textList.clear();
	m_IMEMode = IMEMODE::ENGLISH;
}

bool TextUI::Initialize()
{
	GameObject::Initialize();

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

void TextUI::Update(float elapsedTime)
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

	if (m_isActive == true)
		m_flag |= CHECK_TYPE::IS_ACTIVE;
	else
		m_flag &= ~CHECK_TYPE::IS_ACTIVE;

	if (GetText().size() <= 0)
		m_flag |= CHECK_TYPE::IS_EMPTY;
	else
		m_flag &= ~CHECK_TYPE::IS_EMPTY;
}

void TextUI::Render()
{
	Matrix3x2F worldView = m_worldMatrix * GET_INSTANCE(Camera)->GetViewMatrix();
	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);

	int minX = pos.x - tex->GetWidth() * 0.5f;
	int minY = pos.y - tex->GetHeight() * 0.5f;

	float width = 1.5f;
	float gap = 2.f;

	D2D_POINT_2F startPos;
	startPos.x = static_cast<float>(minX);
	startPos.y = static_cast<float>(minY);

	D2D_POINT_2F endPos;
	endPos.x = startPos.x;
	endPos.y = startPos.y + tex->GetHeight();

	if (m_flag & CHECK_TYPE::IS_EMPTY)
	{
		GameObject::Render();
	}
	else
	{
		GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(Matrix3x2F::Identity());

		wstring text = GetText();

		IDWriteTextLayout* layout = nullptr;
		HRESULT result = GET_INSTANCE(D2DManager)->GetWriteFactory()->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()),
			GET_INSTANCE(D2DManager)->GetFontInfo("메이플").m_pFont, 4096.0f, 4096.0f, &layout);

		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawTextLayout(startPos, layout, GET_INSTANCE(D2DManager)->GetFontColor("검은색"));

		DWRITE_TEXT_METRICS metris;
		layout->GetMetrics(&metris);
		startPos.x += metris.width + gap;
		endPos.x = startPos.x;

		layout->Release();
	}

	if (m_flag & CHECK_TYPE::IS_ACTIVE && m_isEnable == true)
	{
		GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(Matrix3x2F::Identity());
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, GET_INSTANCE(D2DManager)->GetFontColor("검은색"), width, 0);
	}
}

void TextUI::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_isActive == false)
		return;

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

void TextUI::ProcessEnglish(HWND hWnd, WPARAM wParam)
{
	unsigned char key = static_cast<unsigned char>(m_textList.size());

	wstring text = L"";
	text = static_cast<wchar_t>(wParam);
	if (text == L"\r")
	{
		//WStringToString();
		return;
	}

	m_textList.emplace_back(TextInfo(key, text));
}

void TextUI::ProcessKorean(HWND hWnd, LPARAM lParam)
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

void TextUI::DeleteText()
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

void TextUI::ChangeIMEMode(HWND hWnd, bool korean)
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

string TextUI::ConvertTextToString()
{
	string s = "";
	for (auto data : m_textList)
	{
		char temp[10] = { 0, };
		wcstombs(temp, const_cast<wchar_t*>(data.m_Text.c_str()), data.m_Text.length());
		s += temp;
	}

	return s;
}

wstring TextUI::GetText() const
{
	wstring text = L"";

	for (auto iter = m_textList.begin(); iter != m_textList.end(); ++iter)
		text += (*iter).m_Text;

	return text;
}