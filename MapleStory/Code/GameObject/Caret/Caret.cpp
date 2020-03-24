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
	D2D_POINT_2F startPos;
	startPos.x = 10;
	startPos.y = 10;

	D2D_POINT_2F endPos;
	endPos.x = 10;
	endPos.y = 100;
	auto iter = GET_INSTANCE(D2DManager)->GetFontColorList().find("검은색");

	FontInfo info = GET_INSTANCE(D2DManager)->GetFontInfo("메이플");
	// 보이는 시간
	if (m_isEnable == true)
	{
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, (*iter).second, 2.0f, 0);

	}


	//HRESULT result = info.m_pTextLayout->HitTestPoint(endPos.x, endPos.y, &isTrailingHit, &isInside, &metrics);
	//if (result == S_OK)
	//{
	//	if (isTrailingHit)
	//	{
	//		cout << "충돌" << endl;
	//	}
	//}
	DWRITE_HIT_TEST_METRICS metrics = { 0 };
	BOOL isInside = false, isTrailingHit = false;

	UINT32 textPos = 0;

	DWRITE_TEXT_METRICS textMetrics;
	info.m_pTextLayout->GetMetrics(&textMetrics);

	

	info.m_pTextLayout->HitTestTextPosition(metrics.textPosition, isTrailingHit, &endPos.x, &endPos.y, &metrics);

	D2D_RECT_F texPos;
	texPos.left = metrics.left;
	texPos.top = metrics.top;
	
	GET_INSTANCE(D2DManager)->Render(GET_INSTANCE(Input)->GetText(), "메이플", "검은색", texPos);
}

void Caret::Release()
{
}
