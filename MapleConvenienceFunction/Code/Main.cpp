#include "Defines.h"
#include "Core/Core.h"

int main()
{
	_wsetlocale(LC_ALL, L"korean");
	// 에러발생시 한글로 출력되도록 명령
	wcout.imbue(locale("korean"));

	if (GET_INSTANCE(Core)->Initialize() == false)
	{
		GET_INSTANCE(Core)->Release();
		return -1;
	}

	GET_INSTANCE(Core)->Update();

	GET_INSTANCE(Core)->Release();
}
