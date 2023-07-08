#include <../Engine/Inc/WNTRengine.h>
#include "GameState.h"

using namespace WNTRengine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Cube";

	App& myApp = MainApp();
	myApp.AddState<cube>("cube");
	myApp.Run(config);

	return (0);
}