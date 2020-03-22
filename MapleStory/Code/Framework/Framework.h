#pragma once
#include "../Macro.h"
#include "../Defines.h"

class Framework
{
	SINGLE_TONE(Framework)

	bool Initialize(HWND);
	void Run();

private:
	void Update(float);
	void Render();
};
