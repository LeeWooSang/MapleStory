#include "Caret.h"
#include "../../D2DManager/D2DManager.h"
#include "../../Input/Input.h"

Caret::Caret()
{
	m_enableTime = 0.f;
	m_disableTime = 0.f;
	m_isEnable = false;
}

Caret::~Caret()
{
}

bool Caret::Initialize()
{
	m_width = 1.5f;
	m_height = 25.f;
	m_gap = 2.f;

	m_startX = 10.f;
	m_startY = 10.f;

	m_endX = m_startX;
	m_endY = m_startY + m_height;

	return true;
}

void Caret::Update(float elapsedTime)
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
}

void Caret::Render()
{
	if (GET_INSTANCE(Input)->GetIsActive() == false)
		return;

	D2D_POINT_2F startPos { m_startX, m_startY };
	D2D_POINT_2F endPos{ m_endX, m_endY };

	wstring text = GET_INSTANCE(Input)->GetText();
	if (text.size() > 0)
	{
		IDWriteTextLayout* layout = nullptr;
		HRESULT result = GET_INSTANCE(D2DManager)->GetWriteFactory()->CreateTextLayout
		(
			text.c_str(), 
			text.length(), 
			GET_INSTANCE(D2DManager)->GetFontInfo("메이플").m_pFont, 
			4096.0f, 
			4096.0f, 
			&layout
		);

		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawTextLayout(startPos, layout, GET_INSTANCE(D2DManager)->GetFontColor("검은색"));

		DWRITE_TEXT_METRICS metris;
		layout->GetMetrics(&metris);
		startPos.x += metris.width + m_gap;
		endPos.x = startPos.x;

		layout->Release();
	}

	if (m_isEnable)
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, GET_INSTANCE(D2DManager)->GetFontColor("검은색"), m_width, 0);
}

void Caret::Release()
{
}
