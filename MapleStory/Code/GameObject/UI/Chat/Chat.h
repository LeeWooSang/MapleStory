#pragma once
#include "../UI.h"

class Chat : public UI
{
public:
	Chat();
	virtual ~Chat();

	virtual bool Initialize() override;
	virtual void Update(float) override;
	virtual void Render() override;
	virtual void Release() override;

};