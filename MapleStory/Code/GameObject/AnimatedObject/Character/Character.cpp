#include "Character.h"
#include "../../../Camera/Camera.h"
#include "../../../ResourceManager/ResourceManager.h"
#include "../../../ResourceManager/Texture/Texture.h"

Character::Character(const string& name)
	: AnimatedObject(name)
{
}

Character::~Character()
{
}

bool Character::Initialize()
{
	return true;
}

void Character::Update(float elapsedTime)
{
	AnimatedObject::Update(elapsedTime);
}

void Character::Render()
{
	AnimatedObject::Render();
}