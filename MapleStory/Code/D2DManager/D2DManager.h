#pragma once
#include "../Macro.h"
#include "../Defines.h"

constexpr int MAX_FONT_COUNT = 2;
constexpr int MAX_COLOR_COUNT = 8;

struct ImageInfo
{
	ImageInfo()
		: m_FilePath(L""), m_Bitmap(nullptr), m_WidthPixel(0), m_HeightPixel(0), m_TotalFrameX(0), m_TotalFrameY(0), m_FrameXNum(0), m_FrameYNum(0), m_SizeX(0), m_SizeY(0) {}
	ImageInfo(wstring path, int width, int height, int totalX, int totalY, int frameX, int frameY, int sizeX, int sizeY)
		: m_FilePath(path), m_Bitmap(nullptr), m_WidthPixel(width), m_HeightPixel(height), m_TotalFrameX(totalX), m_TotalFrameY(totalY), m_FrameXNum(frameX), m_FrameYNum(frameY), m_SizeX(sizeX), m_SizeY(sizeY) {}

	wstring m_FilePath;
	ID2D1Bitmap* m_Bitmap;

	int m_WidthPixel;
	int m_HeightPixel;

	// �� ���� ��������
	int m_TotalFrameX;
	// �� ���� ��������
	int m_TotalFrameY;

	// ���� ������
	int m_FrameXNum;
	int m_FrameYNum;

	int m_SizeX;
	int m_SizeY;
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

	bool CreateTexture(const string&, ImageInfo);

	void WorldToScreen(D2D1_RECT_F&, int, int, const XMFLOAT2&);
	//void ScreenToWorld();

	void Render(const XMFLOAT2&);
	void Render(const string&, const XMFLOAT2&);
	void Render(const string&, const XMFLOAT2&, int, int );
	void Render(const wstring&, const string&, const string&, D2D1_RECT_F&);

	 ID2D1HwndRenderTarget* GetRenderTarget() const { return m_pRenderTarget; }

	 ImageInfo& GetTexture(string key) { return m_ImageInfoMap[key]; }

	 const unordered_map<string, FontInfo>& GetFontInfoList()	const { return m_FontInfoMap; }
	 const unordered_map<string, ID2D1SolidColorBrush*>& GetFontColorList()	const { return m_FontColorMap; }

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
	unordered_map<string, ImageInfo>						m_ImageInfoMap;
	// ��Ʈ�� ������
	unordered_map<string, FontInfo>						m_FontInfoMap;
	// ��Ʈ ������ ������
	unordered_map<string, ID2D1SolidColorBrush*> m_FontColorMap;
};

