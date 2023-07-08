#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize() {
    mCamera.SetPosition({ 0.0f, 50.0f,-200.0f });
    mCamera.SetLookAt({ 0.0f,-1.f,0.0f });


    mConstantBuffer.Initialize(sizeof(Matrix4));

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
    mVertexBuffer.Initialize<VertexPX>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    //mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/earth/earth.jpg"); 
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
    mWorldTrans = Matrix4::Identity;

    constexpr uint32_t size = 512;
    mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);

    mSkySphere.Initialize();

    mSun.Initialize();

    mMercury.Initialize(); mMercury.SetPosition({20.f,0.f,0.0f});

    mVenus.Initialize();mVenus.SetPosition({ 30.f,0.f,0.0f });
    
    mEarth.Initialize();mEarth.SetPosition({ 40.f,0.f,0.0f });

    mMars.Initialize();mMars.SetPosition({ 50.f,0.f,0.0f });

    mJupiter.Initialize();mJupiter.SetPosition({ 70.f,0.f,0.0f });

    mSaturn.Initialize();mSaturn.SetPosition({ 90.f,0.f,0.0f });

    mUranus.Initialize();mUranus.SetPosition({ 110.f,0.f,0.0f });

    mNeptune.Initialize();mNeptune.SetPosition({ 125.f,0.f,0.0f });

    mPluto.Initialize();mPluto.SetPosition({ 140.f,0.f,0.0f });
}
void GameState::Terminate() {
    mRenderTarget.Terminate();
    mSampler.Terminate();
    //mDiffuseTexture.Terminate();
    mPixelShader.Terminate();
    mVertexBuffer.Terminate();
    //mMeshBuffer.Terminate();
    mConstantBuffer.Terminate();

    mSkySphere.Terminate();
    mMercury.Terminate();
    mVenus.Terminate();
    mEarth.Terminate();
    mMars.Terminate();
    mJupiter.Terminate();
    mSaturn.Terminate();
    mUranus.Terminate();
    mNeptune.Terminate();
    mPluto.Terminate();
}

void GameState::Render() {

    mVertexBuffer.Bind();
    mPixelShader.Bind();
    //mDiffuseTexture.BindPS(0);
    mSampler.BindPS(0);

    mRenderTarget.BeginRender();
    mCamera.SetAspectRatio(1.0f);
    RenderMesh(mCamera,mConstantBuffer,false);
    mCamera.SetAspectRatio(0.0f);
    mRenderTarget.EndRender();
    RenderMesh(mCamera,mConstantBuffer,true);
}

void GameState::Update(float deltaTime) {
    mSun.Update(deltaTime, mSunREVSPD, mSunRotSPD);
    mMercury.Update(deltaTime, mMercuryREVSPD, mMercuryRotSPD);
    mVenus.Update(deltaTime, mVenusREVSPD, mVenusRotSPD);
    mEarth.Update(deltaTime, mEarthREVSPD, mEarthRotSPD);
    mMars.Update(deltaTime, mMarsREVSPD, mMarsRotSPD);
    mJupiter.Update(deltaTime, mJupiterREVSPD, mJupiterRotSPD);
    mSaturn.Update(deltaTime, mSaturnREVSPD, mSaturnRotSPD);
    mUranus.Update(deltaTime, mUranusREVSPD, mUranusRotSPD);
    mNeptune.Update(deltaTime, mNeptuneREVSPD, mNeptuneRotSPD);
    mPluto.Update(deltaTime, mPlutoREVSPD, mPlutoRotSPD);
}

void GameState::DebugUI() {
    ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("DrawSun",     &mDrawSun);
    if (mDrawSun) {
        ImGui::DragFloat("Sun Rotation", &mSunREVSPD,0.1f, 0.f, 10.f);
    }
    ImGui::Checkbox("DrawMercury", &mDrawMercury);
    if (mDrawMercury) {
        ImGui::Checkbox("DrawMercury Ring", &mDrawMercuryRing);
        ImGui::DragFloat("Mercury Revolve speed", &mMercuryREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Mercury Rotation", &mMercuryRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawVenus", &mDrawVenus);
    if (mDrawVenus) {
        ImGui::Checkbox("DrawVenus Ring", &mDrawVenusRing);
        ImGui::DragFloat("Venus Revolve speed", &mVenusREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Venus Rotation", &mVenusRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawEarth",   &mDrawEarth);
    if (mDrawEarth) {
        ImGui::Checkbox("DrawEarth Ring", &mDrawEarthRing);
        ImGui::DragFloat("Earth Revolve speed", &mEarthREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Earth Rotation", &mEarthRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawMars", &mDrawMars);
    if (mDrawMars) {
        ImGui::Checkbox("DrawMars Ring", &mDrawMarsRing);
        ImGui::DragFloat("Mars Revolve speed", &mMarsREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Mars Rotation", &mMarsRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawJupiter", &mDrawJupiter);
    if (mDrawJupiter) {
        ImGui::Checkbox("DrawJupiter Ring", &mDrawJupiterRing);
        ImGui::DragFloat("Jupiter Revolve speed", &mJupiterREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Jupiter Rotation", &mJupiterRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawSaturn",  &mDrawSaturn);
    if (mDrawSaturn) {
        ImGui::Checkbox("DrawSaturn Ring", &mDrawSaturnRing);
        ImGui::DragFloat("Saturn Revolve speed", &mSaturnREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Saturn Rotation", &mSaturnRotSPD, 0.01f, -10.f, 10.f);
       
    }
    ImGui::Checkbox("DrawUranus",  &mDrawUranus);
    if (mDrawUranus) {
        ImGui::Checkbox("DrawUranus", &mDrawUranusRing);
        ImGui::DragFloat("Uranus Revolve speed", &mUranusREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Uranus Rotation", &mUranusRotSPD, 0.01f, -10.f, 10.f);
       
    }
    ImGui::Checkbox("DrawNeptune Ring", &mDrawNeptune);
    if (mDrawNeptune) {
        ImGui::Checkbox("DrawNeptune", &mDrawNeptuneRing);
        ImGui::DragFloat("Neptune Revolve speed", &mNeptuneREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Neptune Rotation", &mNeptuneRotSPD, 0.01f, -10.f, 10.f);
        
    }
    ImGui::Checkbox("DrawPluto", &mDrawPluto);
    if (mDrawPluto) {
        ImGui::Checkbox("DrawPluto Ring", &mDrawPlutoRing);
        ImGui::DragFloat("Pluto Revolve speed", &mPlutoREVSPD, 0.01f, 0.f, 10.f);
        ImGui::DragFloat("Pluto Rotation", &mPlutoRotSPD, 0.01f, -10.f, 10.f);
        
    }

    ImGui::Image(
        mRenderTarget.GetRawData(),
        { 128,128 },
        { 0, 0 },
        { 1,1 },
        { 1,1,1,1 },
        { 1,1,1,1 });
    SimpleDraw::Render(mCamera);
    ImGui::End();

}

void GameState::RenderMesh(const Camera& camera, ConstantBuffer& constantBuffer,bool useTransform)
{
    mSkySphere.Render(camera,constantBuffer, useTransform);
    if (mDrawSun) { mSun.Render(camera, constantBuffer, useTransform);}
    if (mDrawMercury) {mMercury.Render(camera, constantBuffer, useTransform); if (mDrawMercuryRing) { SimpleDraw::AddCircle(360, 20, Colors::Gray); }}
    if (mDrawVenus){mVenus.Render(camera, constantBuffer, useTransform); if (mDrawVenusRing) { SimpleDraw::AddCircle(360, 30, Colors::Brown); }}
    if (mDrawEarth) { mEarth.Render(camera, constantBuffer, useTransform); if (mDrawEarthRing) { SimpleDraw::AddCircle(360, 40, Colors::Cyan);}}
    if (mDrawMars) { mMars.Render(camera, constantBuffer, useTransform); if (mDrawMarsRing) { SimpleDraw::AddCircle(360, 50, Colors::Red); } }
    if (mDrawJupiter) { mJupiter.Render(camera, constantBuffer, useTransform); if (mDrawJupiterRing) { SimpleDraw::AddCircle(360, 70, Colors::Tan); }}
    if (mDrawSaturn) { mSaturn.Render(camera, constantBuffer, useTransform); if (mDrawSaturnRing) { SimpleDraw::AddCircle(360, 90, Colors::Orange); } }
    if (mDrawUranus) { mUranus.Render(camera, constantBuffer, useTransform);  if (mDrawUranusRing) { SimpleDraw::AddCircle(360, 110, Colors::Green); }}
    if (mDrawNeptune) { mNeptune.Render(camera, constantBuffer, useTransform); if (mDrawNeptuneRing) { SimpleDraw::AddCircle(360, 125, Colors::Blue); }}
    if (mDrawPluto) { mPluto.Render(camera, constantBuffer, useTransform); if (mDrawPlutoRing) { SimpleDraw::AddCircle(360, 140, Colors::DarkGray); } }
}

