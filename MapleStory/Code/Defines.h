#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WM_SOCKET WM_USER + 1

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
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
#include <dwrite_3.h>
#include <wincodec.h>

#pragma comment( lib, "d2d1.lib" )
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dwrite.lib")

// DirectX 12
#include <d3d12.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d12.lib")
using namespace DirectX;

constexpr int FRAME_BUFFER_WIDTH = 1024;
constexpr int FRAME_BUFFER_HEIGHT = 768;

namespace Matrix4x4
{
	inline XMFLOAT4X4 Identity()
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixIdentity());
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 PerspectiveFovLH(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ));
		return(xmf4x4Result);
	}
}

