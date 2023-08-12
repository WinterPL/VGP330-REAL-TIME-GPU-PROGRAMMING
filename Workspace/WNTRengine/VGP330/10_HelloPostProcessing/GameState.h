#pragma once

#include "Inc/WNTRengine.h"
#include "Inc/AppState.h"

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
	PostProcessingEffect mPostProcessingEffect;
	RenderGroup mCharacter;
	RenderObject mGround;
	RenderObject mScreenQuad;
	RenderTarget mRenderTarget;
	RenderTarget mCombineTexture;


};


