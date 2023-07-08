#pragma once

#include "Inc/AppState.h"
#include "Inc/WNTRengine.h"

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	void Update(float deltaTime);
	void DebugUI();

protected:

	WNTRengine::Graphics::Camera mCamera;
	WNTRengine::Graphics::StandardEffect mStandardEffect;
	WNTRengine::Graphics::RenderObject mRenderObject;
};


