#include "Character.h"
#include "../../Animation/Animation.h"
#include "../../Camera/Camera.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../ResourceManager/Texture/Texture.h"

Character::Character(const string& name)
	: GameObject(name)
{
	m_animation.clear();
}

Character::~Character()
{
	SAFE_DELETE_MAP(m_animationMap);
}

bool Character::Initialize()
{
	return true;
}

void Character::Update(float elapsedTime)
{
	m_animation = "Idle";

	for (auto object : m_hierarchyList)
		object->Update(elapsedTime);

	// 현재 애니메이션에 해당하는 정보를 각 오브젝트마다 찾는다.
	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;
	(*iter).second->Update(elapsedTime);
}

void Character::Render()
{
	for (auto object : m_hierarchyList)
		object->Render();

	auto iter = m_animationMap.find(m_animation);
	if (iter == m_animationMap.end())
		return;

	// 현재 재생할 애니메이션 이름을 얻어와 텍스쳐를 가져옴
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
	transform = transform * GET_INSTANCE(Camera)->GetViewMatrix();
	GET_INSTANCE(D2DManager)->GetRenderTarget()->SetTransform(transform);

	D2D1_RECT_F rect;
	m_collider->GetAABB(&rect);
	GET_INSTANCE(D2DManager)->GetRenderTarget()->DrawBitmap(tex->GetBitmap(), rect);
	RenderBoundingBox();
}

bool Character::InitHierarchyMap()
{
	return true;
}

void Character::InitAnimation()
{
	string animationName = "Idle";

	string objectName;

	{
		objectName = "Body";
		Character* body = new Character(objectName);
		//m_hierarchyMap.emplace(objectName, body);
		m_hierarchyList.emplace_back(body);
		body->SetUpVector(VECTOR2D(0.f, -1.f));
		body->SetPosition(VECTOR2D(0.f, 30.f));

		Animation* IdleBodyAni = new Animation(animationName);
		IdleBodyAni->AddAnimation("IdleBody0");
		IdleBodyAni->AddAnimation("IdleBody1");
		IdleBodyAni->AddAnimation("IdleBody2");
		body->m_animationMap.emplace(animationName, IdleBodyAni);
	}

	{
		objectName = "Arm";
		Character* arm = new Character(objectName);
		//m_hierarchyMap.emplace(objectName, arm);
		m_hierarchyList.emplace_back(arm);
		arm->SetUpVector(VECTOR2D(0.f, -1.f));
		arm->SetPosition(VECTOR2D(10.f, 25.f));

		Animation* IdleArmAni = new Animation(animationName);
		IdleArmAni->AddAnimation("IdleArm0");
		IdleArmAni->AddAnimation("IdleArm1");
		IdleArmAni->AddAnimation("IdleArm2");
		arm->m_animationMap.emplace(animationName, IdleArmAni);
	}

	{
		objectName = "Head";
		Character* head = new Character(objectName);
		head->SetUpVector(VECTOR2D(0.f, -1.f));
		head->SetPosition(VECTOR2D(2.5f, 0.f));
		//m_hierarchyMap.emplace(objectName, head);
		m_hierarchyList.emplace_back(head);

		Animation* frontHeadAni = new Animation(animationName);
		frontHeadAni->AddAnimation("FrontHead");
		head->m_animationMap.emplace(animationName, frontHeadAni);
	}
}
