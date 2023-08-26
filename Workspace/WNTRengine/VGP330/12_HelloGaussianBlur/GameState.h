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
	GaussianBlurEffect mGaussianEffect;
	PostProcessingEffect mPostProcessingEffect;
	
	RenderObject mSunRenderObject;
	RenderObject mEarthRenderObject;
	RenderObject mScreenQuad;

	RenderTarget mBaseRenderTarget;
	RenderTarget mBloomRenderTarget;

	float mEarthOffset = 8.0f;
	float mEarthRotation = 0.0f;
	float mEarthRevolution = 0.0f;
};


