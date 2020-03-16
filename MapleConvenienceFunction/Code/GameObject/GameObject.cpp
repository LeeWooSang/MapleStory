#include "GameObject.h"

GameObject::GameObject()
	: m_name("")
{
}

GameObject::GameObject(const string & name)
	: m_name(name)
{
}

GameObject::~GameObject()
{
}
