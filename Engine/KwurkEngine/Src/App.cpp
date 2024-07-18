#include "Precompiled.h"
#include "App.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Core;

void App::Run()
{
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		L"Hellowindow",
		1280,
		720
	);

	(void)TimeUtil::GetTime();

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
			Quit();
		}
	}
	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}
