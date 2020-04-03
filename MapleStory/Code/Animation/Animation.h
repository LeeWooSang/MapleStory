#pragma once
#include "../Defines.h"

class Animation
{
public:
	Animation(const string&);
	~Animation();

	bool Initialize();
	void Update(float);

	// ���� �ִϸ��̼� ��ȣ�� �ش��ϴ� �ִϸ��̼� �̸��� ����
	const string& Animation::GetAnimation()	const { return m_animationList[m_animationNum]; }
	void AddAnimation(const string& ani) { m_animationList.emplace_back(string(ani)); }

private:
	string m_name;
	// ���ۿ� �ش��ϴ� �̸���

	vector<string> m_animationList;
	int m_animationNum;
	float m_delay;
};

