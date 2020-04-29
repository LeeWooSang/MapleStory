#include "Texture.h"
#include "../../D2DManager/D2DManager.h"

Texture::Texture()
{
	m_image = nullptr;
	m_width = 0;
	m_height = 0;
	m_totalFrameX = 0;
	m_totalFrameY = 0;
	m_frameX = 0;
	m_frameY = 0;
	m_offsetX = 0.f;
	m_offsetY = 0.f;

	for(int i = 0; i < 3; ++i)
		m_bitmapBrush[i] = nullptr;
}

Texture::~Texture()
{
	if (m_image != nullptr)
		m_image->Release();

	if(m_bitmapBrush[0] != nullptr)
		m_bitmapBrush[0]->Release();
}

bool Texture::Initialize(const wstring& path, int width, int height, int totalX, int totalY, int frameX, int frameY, float offsetX, float offsetY)
{
	m_width = width;
	m_height = height;
	m_totalFrameX = totalX;
	m_totalFrameY = totalY;
	m_frameX = frameX;
	m_frameY = frameY;
	m_offsetX = offsetX;
	m_offsetY = offsetY;

	IWICBitmapDecoder* pBitmapDecoder;
	HRESULT result = GET_INSTANCE(D2DManager)->GetWICImagingFactory()->CreateDecoderFromFilename(path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pBitmapDecoder);
	if (result != S_OK)
		return false;

	IWICBitmapFrameDecode* pFrameDecode;
	result = pBitmapDecoder->GetFrame(0, &pFrameDecode);
	if (result != S_OK)
		return false;

	IWICBitmapSource* wicSource = pFrameDecode;

	IWICBitmapFlipRotator* flipRotator = nullptr;
	result = GET_INSTANCE(D2DManager)->GetWICImagingFactory()->CreateBitmapFlipRotator(&flipRotator);
	if (result != S_OK)
		return false;

	//result = flipRotator->Initialize(wicSource, WICBitmapTransformFlipHorizontal);
	result = flipRotator->Initialize(wicSource, WICBitmapTransformFlipVertical);
	if (result != S_OK)
		return false;
	wicSource = flipRotator;

	IWICFormatConverter* pFormatConverter;
	result = GET_INSTANCE(D2DManager)->GetWICImagingFactory()->CreateFormatConverter(&pFormatConverter);
	if (result != S_OK)
		return false;
	//result = pFormatConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	result = pFormatConverter->Initialize(wicSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeMedianCut);
	if (result != S_OK)
		return false;

	result = GET_INSTANCE(D2DManager)->GetRenderTarget()->CreateBitmapFromWicBitmap(pFormatConverter, &m_image);
	if (result != S_OK)
		return false;

	if (pBitmapDecoder)
		pBitmapDecoder->Release();

	if (pFrameDecode)
		pFrameDecode->Release();

	if (pFormatConverter)
		pFormatConverter->Release();

	if (flipRotator)
		flipRotator->Release();

	return true;
}

bool Texture::InitWrap()
{
	HRESULT result = GET_INSTANCE(D2DManager)->GetRenderTarget()->CreateBitmapBrush(m_image, &m_bitmapBrush[0]);
	if (result != S_OK)
		return false;
	m_bitmapBrush[0]->SetExtendModeX(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
	m_bitmapBrush[0]->SetExtendModeY(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
	//m_bitmapBrush[0]->SetExtendModeY(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_FORCE_DWORD);

	Matrix3x2F matrix = Matrix3x2F::Identity();
	m_bitmapBrush[0]->SetTransform(matrix);

	return true;
}
