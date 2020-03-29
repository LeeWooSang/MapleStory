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

	// 총 가로 몇프레임
	int m_totalFrameX;
	// 총 세로 몇프레임
	int m_totalFrameY;

	// 현재 프레임
	int m_frameX;
	int m_frameY;
};

