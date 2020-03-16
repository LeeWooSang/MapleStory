#pragma once
#include "../Defines.h"
#include "../Macro.h"

class Core
{
	SINGLE_TONE(Core)

public:
	bool Initialize();
	void Update();
	bool MainMenu();

private:
	unordered_map<string, class GameObject*> m_objectList;
};

