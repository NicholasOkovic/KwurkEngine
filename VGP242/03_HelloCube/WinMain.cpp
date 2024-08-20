#include <KwurkEngine/Inc/KwurkEngine.h>

#include "ShapeState.h"

using namespace KwurkEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Cube";

	App& myApp = MainApp();
	myApp.AddState<ShapeState>("ShapeState");
	myApp.Run(config);

	return(0);
}