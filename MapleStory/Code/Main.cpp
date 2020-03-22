#include "Core/Core.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	if (GET_INSTANCE(Core)->Initialize(hInstance) == false)
	{
		GET_INSTANCE(Core)->Release();
		return 0;
	}

	GET_INSTANCE(Core)->Run();
}