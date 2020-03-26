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
	virtual bool Collision(const string&);

private:
	class Player* m_player;
	class TextUI* m_text;
};

