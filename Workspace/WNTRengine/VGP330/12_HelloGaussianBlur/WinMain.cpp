#include <Inc/WNTRengine.h>
#include "GameState.h"

using namespace WNTRengine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Gaussian Blur";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return (0);
}