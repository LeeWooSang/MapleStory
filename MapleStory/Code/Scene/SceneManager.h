#pragma once
#include "../Macro.h"
#include "../Defines.h"

class SceneManager
{
	SINGLE_TONE(SceneManager)
		
public:
	bool Initialize();
	void Update(float);
	void Render();

	enum GAME_STATE 
	{ 
		LOGIN_SCENE,
		CHANNEL_SCENE
	};

	void SetGameState(GAME_STATE state) { m_gameState = state; }

	class Scene* GetScene();

private:
	GAME_STATE m_gameState;

	unordered_map<int, class Scene*> m_sceneList;

	class Scene* p;
};

