#include "StaticObject.h"

StaticObject::StaticObject(const string& name)
	: GameObject(name)
{
}

StaticObject::~StaticObject()
{
}

bool StaticObject::Initialize()
{
	return true;
}

void StaticObject::Update(float elapsedTime)
{
}

void StaticObject::Render()
{
}

void StaticObject::RenderBoundingBox()
{
}
