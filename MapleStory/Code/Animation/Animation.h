#pragma once
#include "../Defines.h"

class Animation
{
public:
	Animation(const string&);
	~Animation();

	bool Initialize();
	void Update(float);

	// 현재 애니메이션 번호에 해당하는 애니메이션 이름을 리턴
	const string& Animation::GetAnimation()	const { return m_animationList[m_animationNum]; }
	void AddAnimation(const string& ani) { m_animationList.emplace_back(string(ani)); }

private:
	string m_name;
	// 동작에 해당하는 이름들

	vector<string> m_animationList;
	int m_animationNum;
	float m_delay;
};

