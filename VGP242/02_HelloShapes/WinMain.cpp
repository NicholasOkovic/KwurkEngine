#include <KwurkEngine/Inc/KwurkEngine.h>

#include "ShapeState.h"

using namespace KwurkEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shapes";
	//config.winWidth = 800;
	//config.winHeight = 800;


	App& myApp = MainApp();

	myApp.AddState<TriangleShapeState>("TriangleShapeState");
	myApp.AddState<SquareShapeState>("SquareShapeState");
	myApp.Run(config);

	return(0);
}