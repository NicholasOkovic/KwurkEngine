#include "Precompiled.h"
#include "Window.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Core;

LRESULT CALLBACK WindowMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::Initialize(HINSTANCE instance, const std::wstring& appName, uint32_t width, uint32_t height)
{
	mInstance = instance;
	mAppName = appName;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowMessageHandler;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = mAppName.c_str();
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	mScreenRect = { 0,0 (LONG)width, (LONG)height };
	AdjustWindowRect(&mScreenRect, WS_OVERLAPPEDWINDOW, FALSE);

	mWindow = CreateWindow(
		mAppName.c_str(),
		mAppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		);
	ShowWindow(mWindow, SW_SHOWNORMAL);
		mActive = (mWindow != nullptr);
}

void Window::Terminte()
{
	DestroyWindow(mWindow);
	UnregisteredClass(mAppName.c_str(), mInstance);
	mWindow = nullptr;
	mInstance = nullptr;
}

void Window::ProcessMessage()
{
	MSG msg{};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			float time TimeUtil::GetTime()
		}
}

HWND Window::GetWINdowHandle() const
{
	return mWindow();
}

bool Window::IsActive() const
{
	return mActive;
}
