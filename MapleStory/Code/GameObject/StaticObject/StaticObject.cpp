#include "StaticObject.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"
#include "../../Camera/Camera.h"

StaticObject::StaticObject(const string& name)
	: GameObject(name)
{
}

StaticObject::~StaticObject()
{
}

bool StaticObject::Initialize()
{
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_name);
	if (tex == nullptr)
		return false;

	int width = tex->GetWidth();
	int height = tex->GetHeight();
	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	m_isDrawBoundingBox = true;

	return true;
}

bool StaticObject::Initialize(const string& textureName)
{
	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	m_textureName = textureName;
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture(m_textureName);
	if (tex == nullptr)
		return false;

	m_textureMap.emplace(m_textureName, tex);

	int width = tex->GetWidth();
	int height = tex->GetHeight();
	m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	m_isDrawBoundingBox = true;

	return true;
}

void StaticObject::Update(float elapsedTime)
{
}

void StaticObject::Render()
{
	auto iter = m_textureMap.find(m_textureName);
	if (iter != m_textureMap.end())
	{
		Matrix3x2F transform = m_worldMatrix;
		transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
		GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

		D2D1_RECT_F rect;
		m_collider->GetAABB(&rect);
		GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap((*iter).second->GetBitmap(), rect);
	}
	
	RenderBoundingBox();
}

void StaticObject::RenderBoundingBox()
{
	if (m_isDrawBoundingBox == true && m_collider != nullptr)
	{
		switch (m_collider->GetType())
		{
		case COLLIDER_AABB:
		{
			D2D1_RECT_F boundRect;
			AABBCollider* aabbCollider = reinterpret_cast<AABBCollider*>(m_collider);
			//				pAABBCollider->GetBounds(&d2drcBounds);
			aabbCollider->GetTransformedBounds(&m_worldMatrix, &boundRect);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		case COLLIDER_OOBB:
		{
			D2D1_RECT_F boundRect;
			OOBBCollider* oobbCollider = reinterpret_cast<OOBBCollider*>(m_collider);
			oobbCollider->GetBounds(&boundRect);
			oobbCollider->GetTransformedBounds(&m_worldMatrix);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		case COLLIDER_CIRCLE:
		{
			CircleCollider* circleCollider = reinterpret_cast<CircleCollider*>(m_collider);
			//				CIRCLE ccCircle = pCircleCollider->GetTransformedBounds(&m_d2dmtxWorld);
			//				D2D1_ELLIPSE d2dEllipse = Ellipse(ccCircle.m_vCenter, ccCircle.m_fRadius, ccCircle.m_fRadius);
			D2D1_ELLIPSE ellipse;
			circleCollider->GetBounds(&ellipse);
			//				pd2dRenderTarget->SetTransform((pCamera) ? pCamera->m_d2dmtxView : Matrix3x2F::Identity());
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawEllipse(ellipse, GET_INSTANCE(D2DManager)->GetFontColor("說除儀"));
			break;
		}
		}
	}
}