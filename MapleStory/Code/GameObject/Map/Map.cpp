#include "Map.h"
#include "../../D2DManager/D2DManager.h"
#include "../../Camera/Camera.h"

Map::Map()
	: GameObject()
{
}

Map::~Map()
{
	cout << "Map - ¼Ò¸êÀÚ" << endl;
}

bool Map::Initialize()
{
	if (GET_INSTANCE(D2DManager)->CreateTexture("Map", ImageInfo(L"../Resource/Textures/Map/Login.png", 795, 560, 1, 1, 0, 0, 1200, 800)) == false)
		return false;


	return true;
}

void Map::Update(float elapsedTime)
{
}

void Map::Render()
{
	//GET_INSTANCE(D2DManager)->Render("Player", GET_INSTANCE(Camera)->GetWorldPosition(), static_cast<int>(m_Frame), 0);
	GET_INSTANCE(D2DManager)->Render("Map", GET_INSTANCE(Camera)->GetWorldPosition());
}

void Map::Release()
{
}
