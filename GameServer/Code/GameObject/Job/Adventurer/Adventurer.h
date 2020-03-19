#pragma once
#include "../Job.h"

class Adventurer : public Job
{
public:
	Adventurer(const string&);
	virtual ~Adventurer();

	virtual bool Initialize(void*);
	virtual void Update();
};

