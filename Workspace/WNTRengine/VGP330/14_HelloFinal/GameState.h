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
	Transparent mTransparentEffect;
	PostProcessingEffect mPostProcessingEffect;
	
	RenderObject mSunRenderObject;
	RenderObject mEarthRenderObject;
	RenderObject mScreenQuad;

	RenderTarget mBaseRenderTarget;
	RenderTarget mBloomRenderTarget;

	BlendState mBlendState;

	float mEarthOffset = 8.0f;
	float mEarthRotation = 0.0f;
	float mEarthRevolution = 0.0f;
	float mAlphaPower = 1.0f;
};


