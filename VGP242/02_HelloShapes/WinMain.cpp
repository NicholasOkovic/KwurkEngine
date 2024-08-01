#include <KwurkEngine/Inc/KwurkEngine.h>

#include "ShapeState.h"

using namespace KwurkEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shapes";

	App& myApp = MainApp();
	myApp.AddState<ShapeState>("ShapState");
	myApp.Run(config);

	return(0);
}