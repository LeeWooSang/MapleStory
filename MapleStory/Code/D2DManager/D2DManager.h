#pragma once
#include "../Macro.h"
#include "../Defines.h"

constexpr int MAX_FONT_COUNT = 2;
constexpr int MAX_COLOR_COUNT = 8;

struct TextureInfo
{
	TextureInfo()
		: m_path(L""), m_image(nullptr), m_width(0), m_height(0), m_totalFrameX(0), m_totalFrameY(0), m_frameX(0), m_frameY(0) {}
	TextureInfo(const wstring& path, int width, int height, int totalX, int totalY, int frameX, int frameY)
		: m_path(path), m_image(nullptr), m_width(width), m_height(height), m_totalFrameX(totalX), m_totalFrameY(totalY), m_frameX(frameX), m_frameY(frameY) {}

	wstring m_path;
	ID2D1Bitmap* m_image;

	int m_width;
	int m_height;

	// �� ���� ��������
	int m_totalFrameX;
	// �� ���� ��������
	int m_totalFrameY;

	// ���� ������
	int m_frameX;
	int m_frameY;
};

struct FontInfo
{
	FontInfo()
		: m_pFont(nullptr), m_pTextLayout(nullptr), m_FontSize(0.f) {}
	FontInfo(IDWriteTextFormat* pFont, IDWriteTextLayout* layout, float size)
		: m_pFont(pFont), m_pTextLayout(layout), m_FontSize(size) {}

	// ��Ʈ ��ü
	IDWriteTextFormat*			m_pFont{ nullptr };
	// ��Ʈ ����
	IDWriteTextLayout*			m_pTextLayout{ nullptr };

	float m_FontSize;
};

class D2DManager
{
	SINGLE_TONE(D2DManager)

	bool Initialize(HWND);

	bool CreateTexture(const string&, TextureInfo&);

	void Render(const wstring&, const string&, const string&, D2D1_RECT_F&);

	IDWriteFactory5* GetWriteFactory()	const { return m_pWriteFactory; }
	 ID2D1HwndRenderTarget* GetRenderTarget() const { return m_pRenderTarget; }

	 const unordered_map<string, FontInfo>& GetFontInfoList()	const { return m_FontInfoMap; }
	 ID2D1SolidColorBrush* GetFontColor(const string& key)	 { return m_FontColorMap[key]; }

	 const TextureInfo& GetTexture(string key) { return m_ImageInfoMap[key]; }
	 FontInfo& GetFontInfo(const string& font) { return m_FontInfoMap[font]; }

private:
	void CreateGameFont();
	void CreateGameFontColor();

	ID2D1Factory3*						m_pFactory;
	// ����Ÿ��
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	// D2DManager�� �ؽ�Ʈ�� �׸��� ���� ���丮
	IDWriteFactory5*					m_pWriteFactory;
	IDWriteFontCollection1*		m_pFontCollection;
	// D2DManager�� �̹����� �׸��� ���� ���丮
	IWICImagingFactory*			m_pWICImagingFactory;

	// �̹����� ������
	unordered_map<string, TextureInfo>						m_ImageInfoMap;
	// ��Ʈ�� ������
	unordered_map<string, FontInfo>						m_FontInfoMap;
	// ��Ʈ ������ ������
	unordered_map<string, ID2D1SolidColorBrush*> m_FontColorMap;

	float prev = 0.f;
};

