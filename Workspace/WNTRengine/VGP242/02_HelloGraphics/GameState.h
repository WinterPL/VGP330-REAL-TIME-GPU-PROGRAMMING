#pragma once

#include "Inc/AppState.h"
#include "../Framework/Graphics/Inc/GraphicsSystem.h"
#include "Input/Inc/InputSystem.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate() {}
	void Update(float deltaTime);
	void Render() {}
	void DebugUI() {}
};
