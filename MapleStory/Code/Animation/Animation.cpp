#include "Animation.h"

Animation::Animation(const string& name)
{
	m_name = name;
	m_animationList.clear();
	m_animationNum = 0;
	m_delay = 0.f;
	m_flag = IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;
}

Animation::~Animation()
{
}

bool Animation::Initialize()
{
	return true;
}

void Animation::Update(float elapsedTime)
{
	m_delay += elapsedTime;
	if (m_delay < 0.35f)
		return;
	m_delay = 0.f;

	if (m_name == "Idle")
	{
		//m_flag |= IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;

		if (m_flag & IDLE_ANIMATION_TYPE::FOWARD_DIRECTION)
		{
			if (m_animationNum == m_animationList.size() - 1)
			{
				m_flag &= ~IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;
				m_flag |= IDLE_ANIMATION_TYPE::BACK_DIRECTION;
			}

			else
				++m_animationNum;
		}
		else
		{
			if (m_animationNum == 0)
			{
				m_flag &= ~IDLE_ANIMATION_TYPE::BACK_DIRECTION;
				m_flag |= IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;
			}

			else
				--m_animationNum;
		}
	}
}
