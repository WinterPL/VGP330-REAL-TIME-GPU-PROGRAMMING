#include "Precompiled.h"
#include "WNTRengine.h"


WNTRengine::App& WNTRengine::MainApp() {
	static App sApp;
	return sApp;
}
