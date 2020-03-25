#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WM_SOCKET WM_USER + 1

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>
#include <math.h>

#include "Default/Resource.h"

// Direct2D
#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <d2d1_3.h>
#include <d2d1helper.h>
#include <dwrite_3.h>
#include <wincodec.h>

#include <Mmsystem.h>

using namespace D2D1;

#pragma comment(lib, "winmm.lib")
#pragma comment( lib, "d2d1.lib" )
#pragma comment(lib, "dwrite.lib")

constexpr int FRAME_BUFFER_WIDTH = 800;
constexpr int FRAME_BUFFER_HEIGHT = 600;

#define PI		3.14159265358979323846f
#define DEGREE_TO_RADIAN(d)	((d) * PI / 180.0f)
#define RADIAN_TO_DEGREE(r)	((r) * 180.0f / PI)