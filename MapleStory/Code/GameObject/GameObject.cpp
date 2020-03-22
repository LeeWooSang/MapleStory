#include "GameObject.h"

GameObject::GameObject()
	: m_Speed(0.f), m_ID(0)
{
	m_WorldPosition.x = 0.f;
	m_WorldPosition.y = 0.f;
}

GameObject::~GameObject()
{
	cout << "GameObject - ¼Ò¸êÀÚ" << endl;
}