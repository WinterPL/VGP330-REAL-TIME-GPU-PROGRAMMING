#pragma once
#include "Inc/AppState.h"
#include "Inc/WNTRengine.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	void Update(float deltaTime);

protected:

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexBuffer;
	PixelShader mPixelShader;
	
	Texture mDiffuseTexture;
	Sampler mSampler;
};


