#include "AnimatedObject.h"
#include "../../Animation/Animation.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"
#include "../../Camera/Camera.h"

AnimatedObject::AnimatedObject(const string& name)
	: GameObject(name)
{
	m_hierarchyList.clear();
	m_hierarchyMap.clear();
	m_animation.clear();
	m_animationMap.clear();

	m_textureMap.clear();
}

AnimatedObject::~AnimatedObject()
{
	SAFE_DELETE_LIST(m_hierarchyList);
	//SAFE_DELETE_MAP(m_hierarchyMap);
	SAFE_DELETE_MAP(m_animationMap);

	m_textureMap.clear();
}

bool AnimatedObject::Initialize()
{
	m_worldMatrix._11 = 1.f;
	m_worldMatrix._12 = 0.f;

	m_worldMatrix._21 = 0.f;
	m_worldMatrix._22 = -1.f;

	return true;
}

void AnimatedObject::Update(float elapsedTime)
{
	// ���� �ִϸ��̼ǿ� �ش��ϴ� ������ �� ������Ʈ���� ã�´�.
	auto iter = m_animationMap.find(m_animation);
	if (iter != m_animationMap.end())
	{
		(*iter).second->Update(elapsedTime);
		RegenerateColliderAABB();
	}

	for (auto object : m_hierarchyList)
		object->Update(elapsedTime);
}

void AnimatedObject::Render()
{
	auto iter = m_animationMap.find(m_animation);
	if (iter != m_animationMap.end())
	{
		//// ���� ����� �ִϸ��̼� �̸��� ���� �ؽ��ĸ� ������
		//Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
		//if (tex == nullptr)
		//	return;

		//Matrix3x2F transform = m_worldMatrix;

		//// ������ ������� ��
		//transform._11 *= m_direction;
		//transform._31 += tex->GetOriginX() * m_direction;
		//transform._32 += tex->GetOriginY();

		//transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
		//GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

		//D2D1_RECT_F rect;
		//m_collider->GetAABB(&rect);
		//GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);

		//AnimatedObject::RenderBoundingBox();

		auto iter0 = m_textureMap.find((*iter).second->GetAnimation());
		if (iter0 != m_textureMap.end())
		{
			Matrix3x2F transform = m_worldMatrix;

			// ������ ������� ��
			transform._11 *= m_direction;
			transform._31 += (*iter0).second->GetOffsetX() * m_direction;
			transform._32 += (*iter0).second->GetOffsetY();

			transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
			GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

			D2D1_RECT_F rect;
			m_collider->GetAABB(&rect);
			GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap((*iter0).second->GetBitmap(), rect);

			AnimatedObject::RenderBoundingBox();
		}
	}

	for (auto object : m_hierarchyList)
		object->Render();
}

void AnimatedObject::RenderBoundingBox()
{
	if (m_isDrawBoundingBox == true && m_collider != nullptr)
	{
		auto iter = m_animationMap.find(m_animation);
		if (iter == m_animationMap.end())
			return;

		switch (m_collider->GetType())
		{
		case COLLIDER_AABB:
			{
				D2D1_RECT_F boundRect;
				AABBCollider* aabbCollider = reinterpret_cast<AABBCollider*>(m_collider);
				//				pAABBCollider->GetBounds(&d2drcBounds);

					// ���� ����� �ִϸ��̼� �̸��� ���� �ؽ��ĸ� ������
				Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
				if (tex == nullptr)
					return;

				int width = tex->GetWidth();
				int height = tex->GetHeight();

				Matrix3x2F transform = m_worldMatrix;

				transform._11 *= m_direction;
				transform._31 += tex->GetOffsetX();
				transform._32 += tex->GetOffsetY();

				aabbCollider->GetTransformedBounds(&transform, &boundRect);
				GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
				GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("������"));
				break;
			}
		case COLLIDER_OOBB:
			{
				D2D1_RECT_F boundRect;
				OOBBCollider* oobbCollider = reinterpret_cast<OOBBCollider*>(m_collider);
				oobbCollider->GetBounds(&boundRect);
				oobbCollider->GetTransformedBounds(&m_worldMatrix);
				GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(GET_INSTANCE(Camera)->GetViewMatrix());
				GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawRectangle(boundRect, GET_INSTANCE(D2DManager)->GetFontColor("������"));
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
				GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawEllipse(ellipse, GET_INSTANCE(D2DManager)->GetFontColor("������"));
				break;
			}
		}
	}
}

void AnimatedObject::SetDirection(char dir)
{
	m_direction = dir;

	for (auto& object : m_hierarchyList)
		object->SetDirection(dir);
}

void AnimatedObject::SetRightVector(VECTOR2D right)
{
	m_worldMatrix._11 = right.x;
	m_worldMatrix._12 = right.y;

	for (auto& object : m_hierarchyList)
		object->SetRightVector(right);
}

void AnimatedObject::SetUpVector(VECTOR2D up)
{
	m_worldMatrix._21 = up.x;
	m_worldMatrix._22 = up.y;

	for (auto& object : m_hierarchyList)
		object->SetUpVector(up);
}

void AnimatedObject::SetPosition(VECTOR2D position)
{
	m_worldMatrix._31 = position.x;
	m_worldMatrix._32 = position.y;

	for (auto& object : m_hierarchyList)
		object->SetPosition(position);
}

float AnimatedObject::GetObjectBottomPos()
{
	auto iter0 = m_animationMap.find(m_animation);
	if (iter0 == m_animationMap.end())
		return 0.f;

	auto iter1 = m_textureMap.find((*iter0).second->GetAnimation());
	if (iter1 == m_textureMap.end())
		return 0.f;

	// ������Ʈ�� y��ǥ + �̹��� ������ ���� + offsetY
	float y = GetPositionVector().y + (*iter1).second->GetHeight() * 0.5f + (*iter1).second->GetOffsetY();

	return y;
}

void AnimatedObject::RegenerateColliderAABB()
{
	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;

	// ���� ����� �ִϸ��̼� �̸��� ���� �ؽ��ĸ� ������
	Texture* tex = GET_INSTANCE(ResourceManager)->GetTexture((*iter).second->GetAnimation());
	if (tex == nullptr)
		return;

	int width = tex->GetWidth();
	int height = tex->GetHeight();

	if (m_collider == nullptr)
		m_collider = new AABBCollider(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));
	else
		reinterpret_cast<AABBCollider*>(m_collider)->SetAABB(AABB(-width * 0.5f, -height * 0.5f, width * 0.5f, height * 0.5f));

	Matrix3x2F transform = m_worldMatrix;
	transform._31 += tex->GetOffsetX();
	transform._32 += tex->GetOffsetY();

	m_collider->Update(&transform);

	m_isDrawBoundingBox = true;
}

AnimatedObject* AnimatedObject::InitHierarchy(const string& name)
{
	AnimatedObject* obj = new AnimatedObject(name);
	m_hierarchyList.emplace_back(obj);

	if (obj->Initialize() == false)
		return nullptr;

	return obj;
}

AnimatedObject* AnimatedObject::FindObject(const string & name)
{
	for (auto object : m_hierarchyList)
		if (object->m_name == name)
			return object;

	return nullptr;
}

void AnimatedObject::InitAnimation(int size, const string& animationName, const string& textureName)
{	
	// �ִϸ��̼ǿ� �ʿ��� �ؽ��� ������ �˾ƾ���.
	Animation* ani = new Animation(animationName);
	
	// �ִϸ��̼� �ؽ��� �̸� : �ִϸ��̼� �̸� + ������Ʈ �̸� + a
	for (int i = 0; i < size; ++i)
	{
		string s = textureName + to_string(i);
		ani->AddAnimation(s);
		m_textureMap.emplace(s, GET_INSTANCE(ResourceManager)->GetTexture(s));
	}

	AddAnimationMap(animationName, ani);
}

void AnimatedObject::InitAnimation(int size, const string& animationName, const string& textureName, AnimatedObject* obj)
{
	// �ִϸ��̼ǿ� �ʿ��� �ؽ��� ������ �˾ƾ���.
	Animation* ani = new Animation(animationName);
	for (int i = 0; i < size; ++i)
	{
		string s = textureName + to_string(i);
		ani->AddAnimation(s);
		obj->m_textureMap.emplace(s, GET_INSTANCE(ResourceManager)->GetTexture(s));
	}

	obj->AddAnimationMap(animationName, ani);
}

void AnimatedObject::SetAnimation(const string& animationName)
{
	m_animation = animationName;

	for (auto& object : m_hierarchyList)
		object->m_animation = animationName;
}
