#pragma once
#include "../Scene.h"

class LoginScene : public Scene
{
public:
	LoginScene();
	virtual ~LoginScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

private:
	class Player* m_player;
};

