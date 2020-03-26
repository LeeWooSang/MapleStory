#include "LoginUI.h"
#include "../../../Input/Input.h"
#include "../../../Camera/Camera.h"

LoginUI::LoginUI(const string& name)
	: UI(name)
{
	m_enableTime = 0.f;
	m_isEnable = false;

	m_width = 0.f;
	m_height = 0.f;
	m_gap = 0.f;
	m_startX = 0.f;
	m_startY = 0.f;
	m_endX = 0.f;
	m_endY = 0.f;
}

LoginUI::~LoginUI()
{
}

bool LoginUI::Initialize(TextureInfo info)
{
	if (GameObject::Initialize(info) == false)
		return false;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	m_width = 1.5f;
	m_height = 25.f;
	m_gap = 2.f;

	m_startX = m_worldMatrix._31;
	m_startY = m_worldMatrix._32;

	m_endX = m_startX;
	m_endY = m_startY + m_height;

	return true;
}

void LoginUI::Update(float elapsedTime)
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

void LoginUI::Render()
{
	GameObject::Render();

	TextRender();
}

void LoginUI::TextRender()
{
	if (GET_INSTANCE(Input)->GetIsActive() == false)
		return;

	//Matrix3x2F transform = m_worldMatrix;
	//transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	//GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D_POINT_2F startPos;
	startPos.x = m_worldMatrix._31;
	startPos.y = m_worldMatrix._32;

	D2D_POINT_2F endPos;
	endPos.x = startPos.x;
	endPos.y = startPos.y + m_height;

	wstring text = GET_INSTANCE(Input)->GetText();
	if (text.size() > 0)
	{
		IDWriteTextLayout* layout = nullptr;
		HRESULT result = GET_INSTANCE(D2DManager)->GetWriteFactory()->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.length()),
			GET_INSTANCE(D2DManager)->GetFontInfo("메이플").m_pFont, 4096.0f, 4096.0f, &layout);

		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawTextLayout(startPos, layout, GET_INSTANCE(D2DManager)->GetFontColor("검은색"));

		DWRITE_TEXT_METRICS metris;
		layout->GetMetrics(&metris);
		startPos.x += metris.width + m_gap;
		endPos.x = startPos.x;

		layout->Release();
	}

	//if (m_isEnable)
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawLine(startPos, endPos, GET_INSTANCE(D2DManager)->GetFontColor("검은색"), m_width, 0);
}

void LoginUI::Input()
{

}
