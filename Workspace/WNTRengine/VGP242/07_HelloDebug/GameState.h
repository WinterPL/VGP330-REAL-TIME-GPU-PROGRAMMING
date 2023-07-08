#pragma once
#include "Inc/AppState.h"
#include "Inc/WNTRengine.h"
#include "RenderObjects.h"

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
	void DebugUI();
	void RenderMesh(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform);

protected:

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexBuffer;
	PixelShader mPixelShader;
	RenderTarget mRenderTarget;

	Texture mDiffuseTexture;
	Sampler mSampler;
	Matrix4 mWorldTrans;

	SkySphere mSkySphere;
	Sun       mSun;
	Mercury   mMercury;
	Venus     mVenus;
	Earth     mEarth;
	Mars      mMars;
	Jupiter   mJupiter;
	Saturn    mSaturn;
	Uranus    mUranus;
	Neptune   mNeptune;
	Pluto     mPluto;

	bool mDrawSun = true;
	bool mDrawMercury = true;
	bool mDrawVenus = true;
	bool mDrawEarth = true;
	bool mDrawMars = true;
	bool mDrawJupiter = true;
	bool mDrawSaturn = true;
	bool mDrawUranus = true;
	bool mDrawNeptune = true;
	bool mDrawPluto = true;


	bool mDrawMercuryRing = true;
	bool mDrawVenusRing   = true;
	bool mDrawEarthRing = true;
	bool mDrawMarsRing = true;
	bool mDrawJupiterRing = true;
	bool mDrawSaturnRing = true;
	bool mDrawUranusRing = true;
	bool mDrawNeptuneRing = true;
	bool mDrawPlutoRing = true;


	float mSunRotSPD     = 0.5f;
	float mMercuryRotSPD = 0.5f;
	float mVenusRotSPD   = 0.5f;
	float mEarthRotSPD   = 0.5f;
	float mMarsRotSPD    = 0.5f;
	float mJupiterRotSPD = 0.5f;
	float mSaturnRotSPD  = 0.5f;
	float mUranusRotSPD  = 0.5f;
	float mNeptuneRotSPD = 0.5f;
	float mPlutoRotSPD   = 0.5f;

	float mSunREVSPD = 0.1f;
	float mMercuryREVSPD = 0.8f;
	float mVenusREVSPD = 0.7f;
	float mEarthREVSPD = 0.75f;
	float mMarsREVSPD = 0.8f;
	float mJupiterREVSPD = 0.4f;
	float mSaturnREVSPD = 0.5f;
	float mUranusREVSPD = 0.6f;
	float mNeptuneREVSPD = 0.74f;
	float mPlutoREVSPD = 0.9f;
};


