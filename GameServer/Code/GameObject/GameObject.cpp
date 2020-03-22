#include "GameObject.h"

GameObject::GameObject()
{
	m_name.clear();
}

GameObject::GameObject(const string& name)
{
	m_name = name;
}

GameObject::~GameObject()
{
	m_name.clear();
}

void GameObject::ClearObjectInfo()
{
	m_name.clear();
}
