#include "Core.h"
#include <crtdbg.h>
#include "../Framework/Framework.h"
#include "../Input/Input.h"
#include "../Network/Network.h"

INIT_INSTACNE(Core)
bool Core::m_isUpdate = true;
Core::Core()
	: m_hInstance(nullptr), m_hWnd(nullptr), m_ClassName(L"MapleStory")
{
	// 메모리 릭이 있는지 체크를 해준다.
	// 릭이 있으면, 번호를 출력해준다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 출력된 번호를 넣어주면 그 지점으로 바로 이동시켜준다.
	// [ 예시 ]
	// Detected memory leaks!
	//	Dumping objects ->
	// {233} normal block at 0x000001469D91A680, 24 bytes long.
	// 233 이라는 지점에서 릭이 생김	
	//_CrtSetBreakAlloc();
}

Core::~Core()
{
	GET_INSTANCE(Input)->Release();
	GET_INSTANCE(Framework)->Release();

	cout << "Core - 소멸자" << endl;
}

bool Core::Initialize(HINSTANCE hInst)
{
	m_hInstance = hInst;

	if (m_hInstance == nullptr)
		return false;

	MyRegisterClass();

	RECT rc = { 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;

	// 윈도우 생성
	m_hWnd = CreateWindowW(m_ClassName.c_str(), m_ClassName.c_str(), dwStyle, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);
	
	if (m_hWnd == nullptr)
		return false;

	AdjustWindowRect(&rc, dwStyle, false);

	// 윈도우 크기 및 위치 설정
	int posX = 100;
	int posY = 100;
	SetWindowPos(m_hWnd, HWND_TOPMOST, posX, posY, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	if (GET_INSTANCE(Framework)->Initialize(m_hWnd) == false)
		return false;

	if (GET_INSTANCE(Input)->Initialize() == false)
		return false;

	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd);

	return true;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Core::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_ClassName.c_str();
	wcex.hIconSm = ::LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return ::RegisterClassEx(&wcex);
}

int Core::Run()
{
	MSG msg;

	while (m_isUpdate)
	{
		if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
			GET_INSTANCE(Framework)->Run();
	}

	GET_INSTANCE(Core)->Release();

	return (int)msg.wParam;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
		case WM_CREATE:
			break;

		case WM_DESTROY:
			m_isUpdate = false;
			//캐럿 삭제
			::PostQuitMessage(0);
			break;

		case WM_PAINT:

			hdc = ::BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

			// IME 사용
		case WM_IME_COMPOSITION:
			// 한자입력...
		case WM_IME_NOTIFY:			
			// 영문 입력
			// 1byte 문자 (ex : 영어)
		case WM_CHAR:				
			// 키 입력
		case WM_KEYDOWN:
		case WM_KEYUP:
			//Alt키 눌렀을 때, 멈추는 현상을 해결하기위해
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
			GET_INSTANCE(Input)->ProcessWindowMessage(hWnd, message, wParam, lParam);
			break;

			// Network의 Recv처리
		case WM_SOCKET:
			GET_INSTANCE(Network)->ProcessWindowMessage(wParam, lParam);
			break;

		default:
			return(::DefWindowProc(hWnd, message, wParam, lParam));
	}

	return 0;
 }