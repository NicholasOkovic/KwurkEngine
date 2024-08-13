#include <KwurkEngine/Inc/KwurkEngine.h>

#include "ShapeState.h"

using namespace KwurkEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Cube";
	//config.winWidth = 800;
	//config.winHeight = 800;


	App& myApp = MainApp();

	myApp.AddState<ShapeState>("ShapeState");
	myApp.Run(config);

	return(0);
}