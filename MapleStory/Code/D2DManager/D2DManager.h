#pragma once
#include "../Macro.h"
#include "../Defines.h"

constexpr int MAX_FONT_COUNT = 2;
constexpr int MAX_COLOR_COUNT = 8;

struct FontInfo
{
	FontInfo()
		: m_pFont(nullptr), m_pTextLayout(nullptr), m_FontSize(0.f) {}
	FontInfo(IDWriteTextFormat* pFont, IDWriteTextLayout* layout, float size)
		: m_pFont(pFont), m_pTextLayout(layout), m_FontSize(size) {}

	// 폰트 객체
	IDWriteTextFormat*			m_pFont{ nullptr };
	// 폰트 형식
	IDWriteTextLayout*			m_pTextLayout{ nullptr };

	float m_FontSize;
};

class D2DManager
{
	SINGLE_TONE(D2DManager)

	bool Initialize(HWND);


	void Render(const wstring&, const string&, const string&, D2D1_RECT_F&);

	IWICImagingFactory* GetWICImagingFactory() { return m_pWICImagingFactory; }

	IDWriteFactory5* GetWriteFactory()	const { return m_pWriteFactory; }
	 ID2D1HwndRenderTarget* GetRenderTarget() const { return m_pRenderTarget; }

	 const unordered_map<string, FontInfo>& GetFontInfoList()	const { return m_FontInfoMap; }
	 ID2D1SolidColorBrush* GetFontColor(const string& key)	 { return m_FontColorMap[key]; }

	 FontInfo& GetFontInfo(const string& font) { return m_FontInfoMap[font]; }

private:
	void CreateGameFont();
	void CreateGameFontColor();

	ID2D1Factory3*						m_pFactory;
	// 렌더타겟
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	// D2DManager로 텍스트를 그리기 위한 팩토리
	IDWriteFactory5*					m_pWriteFactory;
	IDWriteFontCollection1*		m_pFontCollection;
	// D2DManager로 이미지를 그리기 위한 팩토리
	IWICImagingFactory*			m_pWICImagingFactory;

	// 폰트를 저장함
	unordered_map<string, FontInfo>						m_FontInfoMap;
	// 폰트 색상을 저장함
	unordered_map<string, ID2D1SolidColorBrush*> m_FontColorMap;

	float prev = 0.f;
};

