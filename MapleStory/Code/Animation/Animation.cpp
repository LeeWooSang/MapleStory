#include "Animation.h"

Animation::Animation(const string& name)
{
	m_name = name;
	m_animationList.clear();
	m_animationNum = 0;
	m_delay = 0.f;
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
	if (m_delay < 0.5f)
		return;
	m_delay = 0.f;

	if (m_animationNum == m_animationList.size() - 1)
		m_animationNum = 0;
	else
		++m_animationNum;
}
