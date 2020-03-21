#pragma once
#include "../GameObject.h"

class Channel : public GameObject
{
public:
	Channel(const string&);
	virtual ~Channel();

	virtual bool Initialize(void*);
	virtual void Update();

private:
	vector<class Character*> m_channelCharacterList;
};

