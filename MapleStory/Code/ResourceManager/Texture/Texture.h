#pragma once
#include "../../Defines.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool Initialize(const wstring&, int, int, int, int, int, int, float originX = 0.f, float originY = 0.f);

	ID2D1Bitmap* GetBitmap() { return m_image; }
	int GetWidth()	const { return m_width; }
	int GetHeight()	const { return m_height; }

	float GetOriginX()	const { return m_originX; }
	float GetOriginY()	const { return m_originY; }

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

	float m_originX;
	float m_originY;
};

