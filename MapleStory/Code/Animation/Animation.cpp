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
	if (m_delay < 0.2f)
		return;
	m_delay = 0.f;

	//m_flag |= IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;

	if (m_animationList.size() == 1)
		return;

	if (m_name == "Idle")
	{
		if (m_flag & IDLE_ANIMATION_TYPE::FOWARD_DIRECTION)
		{
			if (m_animationNum == m_animationList.size() - 1)
			{
				m_flag &= ~IDLE_ANIMATION_TYPE::FOWARD_DIRECTION;
				m_flag |= IDLE_ANIMATION_TYPE::BACK_DIRECTION;

				if (m_animationList.size() > 1)
					--m_animationNum;
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

				if (m_animationList.size() > 1)
					++m_animationNum;
			}

			else
				--m_animationNum;
		}
	}

	else if (m_name == "Walk")
	{
		if (m_animationNum == m_animationList.size() - 1)
		{
			m_animationNum = 0;
		}
		else
			++m_animationNum;

	}
}
