#pragma once
#include "../../Defines.h"

class Texture
{
public:
	Texture();
	~Texture();
	bool Initialize(const wstring&, int, int, int, int, int, int);

	ID2D1Bitmap* GetBitmap() { return m_image; }
	int GetWidth()	const { return m_width; }
	int GetHeight()	const { return m_height; }

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
};

