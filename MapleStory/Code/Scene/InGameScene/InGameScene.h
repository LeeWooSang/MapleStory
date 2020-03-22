#pragma once
#include "../Scene.h"

class InGameScene : public Scene
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual bool Initialize() override;
	virtual void Update(float) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	class Player* m_Player;
};