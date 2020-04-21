#include "D2DManager.h"

INIT_INSTACNE(D2DManager)
D2DManager::D2DManager()
	: m_pFactory(nullptr), m_pRenderTarget(nullptr), m_pWriteFactory(nullptr), m_pFontCollection(nullptr), m_pWICImagingFactory(nullptr)
{
}

D2DManager::~D2DManager()
{
	// 폰트 컬러를 모두 지움
	for (auto iter = m_FontColorMap.begin(); iter != m_FontColorMap.end(); )
	{
		(*iter).second->Release();
		iter = m_FontColorMap.erase(iter);
	}
	m_FontColorMap.clear();

	for (auto iter = m_FontInfoMap.begin(); iter != m_FontInfoMap.end(); )
	{
		(*iter).second.m_pFont->Release();
		(*iter).second.m_pTextLayout->Release();
		iter = m_FontInfoMap.erase(iter);
	}
	m_FontInfoMap.clear();

	if (m_pFontCollection)
		m_pFontCollection->Release();
	if (m_pWICImagingFactory)
		m_pWICImagingFactory->Release();
	if (m_pWriteFactory)
		m_pWriteFactory->Release();
	if (m_pRenderTarget)
		m_pRenderTarget->Release();
	if (m_pFactory)
		m_pFactory->Release();

	cout << "D2DManager - 소멸자" << endl;
}

bool D2DManager::Initialize(HWND hWnd)
{
	// D2DManager Factory 생성
	HRESULT result = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	if (result != S_OK)
		return false;

	// 콤객체 초기화
	result = CoInitialize(nullptr);
	if (result != S_OK)
		return false;

	// 렌더타겟 생성
	D2D1_SIZE_U size = D2D1::SizeU(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
	D2D1_RENDER_TARGET_PROPERTIES d2dRTProps = D2D1::RenderTargetProperties();
	D2D1_HWND_RENDER_TARGET_PROPERTIES d2dHwndRTProps = D2D1::HwndRenderTargetProperties(hWnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY);
	result = m_pFactory->CreateHwndRenderTarget(d2dRTProps, d2dHwndRTProps, &m_pRenderTarget);
	if (result != S_OK)
		return false;


	// 이미지를 위한 Factory 생성
	result = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(IWICImagingFactory), (void**)&m_pWICImagingFactory);
	if (result != S_OK)
		return false;

	// 텍스트를 위한 Factory 생성
	result = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5), (IUnknown**)&m_pWriteFactory);
	//result = ::DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory4), (IUnknown**)&m_pWriteFactory);
	if (result != S_OK)
		return false;

	CreateGameFont();
	CreateGameFontColor();

	return true;
}

void D2DManager::CreateGameFont()
{
	// 폰트 경로
	wstring fontPath[] = { L"../Resource/Fonts/a피오피동글.ttf", L"../Resource/Fonts/메이플스토리.ttf" };

	// 폰트를 직접 설치할때 사용
	//AddFontResourceEx(fontPath[0].c_str(), FR_PRIVATE, 0);
	//AddFontResourceEx(fontPath[1].c_str(), FR_PRIVATE, 0);

	// 폰트를 설치하지 않고, 메모리에 올려서 사용할 경우
	// 빌더 생성
	IDWriteFontSetBuilder1* pFontSetBuilder;
	HRESULT result = m_pWriteFactory->CreateFontSetBuilder(&pFontSetBuilder);

	IDWriteFontFile* pFontFile[MAX_FONT_COUNT];
	IDWriteFontSet* pFontSet[MAX_FONT_COUNT];

	wstring FontName[MAX_FONT_COUNT];
	unsigned int max_length = 64;

	for (int i = 0; i < MAX_FONT_COUNT; ++i)
	{
		// 해당하는 경로에서 폰트 파일을 로드한다.
		result = m_pWriteFactory->CreateFontFileReference(fontPath[i].c_str(), nullptr, &pFontFile[i]);
		// 빌더에 폰트 추가
		result = pFontSetBuilder->AddFontFile(pFontFile[i]);
		result = pFontSetBuilder->CreateFontSet(&pFontSet[i]);
		// 폰트 Collection에 폰트 추가 => 폰트 Collection에서 내가 사용할 폰트가 저장되어 있음
		result = m_pWriteFactory->CreateFontCollectionFromFontSet(pFontSet[i], &m_pFontCollection);

		// 폰트 이름을 얻어오는 방법
		IDWriteFontFamily* pFontFamily;
		IDWriteLocalizedStrings* pLocalizedFontName;

		result = m_pFontCollection->GetFontFamily(i, &pFontFamily);
		result = pFontFamily->GetFamilyNames(&pLocalizedFontName);
		// 저장되어있는 폰트의 이름을 얻어옴
		result = pLocalizedFontName->GetString(0, const_cast<wchar_t*>(FontName[i].c_str()), max_length);

		pFontFamily->Release();
		pLocalizedFontName->Release();
	}

	pFontSetBuilder->Release();

	for (int i = 0; i < MAX_FONT_COUNT; ++i)
	{
		pFontFile[i]->Release();
		pFontSet[i]->Release();
	}

	float fontSize = 25.f;

	// 폰트 객체
	IDWriteTextFormat* pFont[MAX_FONT_COUNT];
	// 폰트 형식
	IDWriteTextLayout*	pTextLayout[MAX_FONT_COUNT];
	wstring wstr = L"TextLayout Initialize";

	for (int i = 0; i < MAX_FONT_COUNT; ++i)
	{
		// 폰트 객체 생성	
		result = m_pWriteFactory->CreateTextFormat(FontName[i].c_str(), m_pFontCollection, DWRITE_FONT_WEIGHT_DEMI_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-US", &pFont[i]);

		if (i == 0)
		{
			// 폰트를 중앙에 정렬시키기
			result = pFont[i]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			result = pFont[i]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			result = m_pWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<UINT32>(wstr.length()), pFont[i], 1024.0f, 1024.0f, &pTextLayout[i]);

			m_FontInfoMap.emplace("피오피동글", FontInfo(pFont[i], pTextLayout[i], fontSize));
		}
		else
		{
			result = pFont[i]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			result = pFont[i]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
			result = m_pWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<UINT32>(wstr.length()), pFont[i], 4096.0f, 4096.0f, &pTextLayout[i]);

			m_FontInfoMap.emplace("메이플", FontInfo(pFont[i], pTextLayout[i], fontSize));
		}
	}
}

void D2DManager::CreateGameFontColor()
{
	ID2D1SolidColorBrush* pColor[MAX_COLOR_COUNT];

	int index = 0;
	HRESULT result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DeepPink, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("분홍색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Brown, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("갈색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("흰색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("검은색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SkyBlue, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("하늘색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LavenderBlush, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("연분홍색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("빨간색", pColor[index++]);

	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange, 1.0f), &pColor[index]);
	m_FontColorMap.emplace("주황색", pColor[index++]);
}

void D2DManager::Render(const wstring& text, const string& font, const string& color, D2D1_RECT_F& pos)
{
	m_pRenderTarget->DrawTextW(text.c_str(), static_cast<UINT32>(text.length()), m_FontInfoMap[font].m_pFont, &pos, m_FontColorMap[color]);
}