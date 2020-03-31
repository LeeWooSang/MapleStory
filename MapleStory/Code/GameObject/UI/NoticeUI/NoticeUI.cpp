#include "NoticeUI.h"
#include "../../../../../GameServer/Code/Protocol.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../../ResourceManager/Texture/Texture.h"
#include "../../../Camera/Camera.h"

NoticeUI::NoticeUI(const string& name)
	: UI(name)
{
	m_isActive = false;
	m_noticeType = NOTICE_TYPE::CORRECT;
}

NoticeUI::~NoticeUI()
{
	SAFE_DELETE_MAP(m_noticeList);
}

bool NoticeUI::Initialize()
{
	//GameObject::Initialize(info);

	Texture* tex1 = GET_INSTANCE(ResourceManager)->GetTexture("NoticeBackground");
	if (tex1 == nullptr)
		return false;
	int width = tex1->GetWidth();
	int height = tex1->GetHeight();
	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	m_isDrawBoundingBox = true;
	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	m_noticeType = NOTICE_TYPE::CORRECT;

	Texture* tex2 = GET_INSTANCE(ResourceManager)->GetTexture("NoticeIDNotCorrect");
	if (tex2 == nullptr)
		return false;
	width = tex2->GetWidth();
	height = tex2->GetHeight();
	AABBCollider* noticeIDNot = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));
	m_noticeList.emplace("NoticeIDNotCorrect", noticeIDNot);

	Texture* tex3 = GET_INSTANCE(ResourceManager)->GetTexture("NoticePWNotCorrect");
	if (tex3 == nullptr)
		return false;
	width = tex3->GetWidth();
	height = tex3->GetHeight();
	AABBCollider* noticePWNot = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));
	m_noticeList.emplace("NoticePWNotCorrect", noticePWNot);

	return true;
}

void NoticeUI::Update(float elapsedTime)
{
}

void NoticeUI::Render()
{
	if (m_isActive == true)
	{
		RenderBase();
		RenderNotice();
	}
}

void NoticeUI::RenderBase()
{
	GameObject::Render();
}

void NoticeUI::RenderNotice()
{
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(Matrix3x2F::Identity());
	D2D1_RECT_F rect;

	if (m_noticeType & NOTICE_TYPE::ID_NOT_CORRECT)
	{
		Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture("NoticeIDNotCorrect");
		if (tex == nullptr)
			return;

		Matrix3x2F transform = m_worldMatrix;
		transform._31 = 0.f;
		transform._32 = -15.f;
		transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
		GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

		auto iter = m_noticeList.find("NoticeIDNotCorrect");
		(*iter).second->GetAABB(&rect);
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);
	}

	else if (m_noticeType & NOTICE_TYPE::PW_NOT_CORRECT)
	{
		Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture("NoticePWNotCorrect");
		if (tex == nullptr)
			return;

		Matrix3x2F transform = m_worldMatrix;
		transform._31 = 0.f;
		transform._32 = -15.f;

		transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
		GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

		auto iter = m_noticeList.find("NoticePWNotCorrect");
		(*iter).second->GetAABB(&rect);
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);
	}
}
