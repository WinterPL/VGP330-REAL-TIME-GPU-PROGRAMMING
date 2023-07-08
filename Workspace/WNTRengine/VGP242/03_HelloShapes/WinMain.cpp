#include <../Engine/Inc/WNTRengine.h>
#include "GameState.h"

using namespace WNTRengine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shapes";

	App& myApp = MainApp();
	myApp.AddState<TrianglesState>("Triangle");
	myApp.AddState<SquareState>("Square");
	myApp.AddState<HeartState>("Heart");
	myApp.AddState<SpearState>("Spear");
	myApp.AddState<FishState>("Fish");
	myApp.Run(config);

	return (0);
}