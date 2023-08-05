#pragma once

#include "Inc/AppState.h"
#include "Inc/WNTRengine.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	void Update(float deltaTime);
	void DebugUI();

protected:

	Camera mCamera;
	DirectionalLight mDirectionalLight;
	StandardEffect mStandardEffect;
	RenderGroup mCharacter;
	RenderObject mGround;
};


