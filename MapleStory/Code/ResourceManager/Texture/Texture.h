#pragma once
#include "../../Defines.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool Initialize(const wstring&, int, int, int, int, int, int, float offsetX = 0.f, float offsetY = 0.f);

	bool InitWrap();

	ID2D1Bitmap* GetBitmap() { return m_image; }
	int GetWidth()	const { return m_width; }
	int GetHeight()	const { return m_height; }

	float GetOffsetX()	const { return m_offsetX; }
	float GetOffsetY()	const { return m_offsetY; }

	ID2D1BitmapBrush* GetWrapBrush() { return m_bitmapBrush[0]; }

private:
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

	float m_offsetX;
	float m_offsetY;

	ID2D1BitmapBrush* m_bitmapBrush[3];
};

