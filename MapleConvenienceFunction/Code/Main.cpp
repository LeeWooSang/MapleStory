#include "Defines.h"
#include "Core/Core.h"

int main()
{
	if (GET_INSTANCE(Core)->Initialize() == false)
	{
		GET_INSTANCE(Core)->Release();
		return -1;
	}

	GET_INSTANCE(Core)->Update();

	GET_INSTANCE(Core)->Release();
}
