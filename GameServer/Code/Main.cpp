#include "Core/Core.h"

int main()
{
	if (GET_INSTANCE(Core)->Initialize() == false)
	{
		GET_INSTANCE(Core)->Release();
		return -1;
	}

	while (GET_INSTANCE(Core)->Run());
	GET_INSTANCE(Core)->Release();
}
