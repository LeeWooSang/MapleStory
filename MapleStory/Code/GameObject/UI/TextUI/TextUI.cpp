#include "TextUI.h"
#include "../../../Input/Input.h"
#include "../../../Camera/Camera.h"

TextUI::TextUI(const string& name)
	: UI(name)
{
	m_enableTime = 0.f;
	m_isEnable = false;
}

TextUI::~TextUI()
{
}

bool TextUI::Initialize(TextureInfo info)
{
	GameObject::Initialize(info);

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

//bool TextUI::Initialize(GameObject* target)
//{
//	Matrix3x2F worldView = target->GetWorldMatrix() * GET_INSTANCE(Camera)->GetViewMatrix();
//	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);
//
//	TextureInfo info = GET_INSTANCE(D2DManager)->GetTexture(target->GetName());
//	int minX = pos.x - info.m_width * 0.5f;
//	int minY = pos.y - info.m_height * 0.5f;
//	int maxX = minX + info.m_width;
//	int maxY = minY + info.m_height;
//
//	m_width = 1.5f;
//	m_height = info.m_height;
//	m_gap = 2.f;
//
//	m_startX = minX;
//	m_startY = minY;
//
//	m_worldMatrix._21 = 0.f;
//	m_worldMatrix._22 = -1.f;
//	m_worldMatrix._31 = 0.f;
//	m_worldMatrix._32 = 0.f;
//
//	m_endX = m_startX;
//	m_endY = m_startY + m_height;
//
//	return true;
//}

void TextUI::Update(float elapsedTime)
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

void TextUI::Render()
{
	GameObject::Render();

	TextRender();
}

void TextUI::TextRender()
{
	if (GET_INSTANCE(Input)->GetIsActive() == false)
		return;

	Matrix3x2F worldView = m_worldMatrix * GET_INSTANCE(Camera)->GetViewMatrix();
	VECTOR2D pos = VECTOR2D(worldView._31, worldView._32);
	TextureInfo info = GET_INSTANCE(D2DManager)->GetTexture(m_name);

	int minX = pos.x - info.m_width * 0.5f;
	int minY = pos.y - info.m_height * 0.5f;
	int maxX = minX + info.m_width;
	int maxY = minY + info.m_height;

	float width = 1.5f;
	float gap = 2.f;

	D2D_POINT_2F startPos;
	startPos.x = static_cast<float>(minX);
	startPos.y = static_cast<float>(minY);

	D2D_POINT_2F endPos;
	endPos.x = startPos.x;
	endPos.y = startPos.y + info.m_height;

	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(Matrix3x2F::Identity());
	wstring text = GET_INSTANCE(Input)->GetText();
	if (text.size() > 0)
	{
		IDWriteTextLayout* layout = nullptr;
		HRESULT result = GET_INSTANCE(D2DManager)->GetWriteFactory()->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()),
			GET_INSTANCE(D2DManager)->GetFontInfo("메이플").m_pFont, 4096.0f, 4096.0f, &layout);

		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawTextLayout(startPos, layout, GET_INSTANCE(D2DManager)->GetFontColor("검은색"));

		DWRITE_TEXT_METRICS metris;
		layout->GetMetrics(&metris);
		startPos.x += metris.width + gap;
		endPos.x = startPos.x;

		layout->Release();
	}

	if (m_isEnable)
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, GET_INSTANCE(D2DManager)->GetFontColor("검은색"), width, 0);
}
