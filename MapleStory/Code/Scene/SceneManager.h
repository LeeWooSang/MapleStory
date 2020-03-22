#pragma once
#include "../Macro.h"
#include "../Defines.h"

class SceneManager
{
	SINGLE_TONE(SceneManager)

	bool Initialize();
	void Update(float);
	void Render();

	class InGameScene* GetInGameScene() const;
private:
	unordered_map<string, class Scene*> m_SceneList;
};