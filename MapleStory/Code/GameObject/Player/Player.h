#pragma once
#include "../GameObject.h"

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual bool Initialize() override;
	virtual void Update(float) override;
	virtual void Render() override;
	virtual void Release() override;

	void ProcessAnimation(char, float);

private:
	enum ANIMATION
	{
		IDLE = 0x0000,
		ACTION = 0x0001,
		RAGINGBLOW = 0x0002
	};

	enum ANIMATION_FRAME
	{
		IDLE_FRAME = 0,
		ACTION_FRAME = 9,
		RAGINGBLOW_FRAME = 13
	};

	char m_PrevAnimation;
	string m_AnimationName;
	float m_Frame;
	float m_ActionFrame;

	unordered_map<ANIMATION, ANIMATION_FRAME> m_AnimationMap;
};