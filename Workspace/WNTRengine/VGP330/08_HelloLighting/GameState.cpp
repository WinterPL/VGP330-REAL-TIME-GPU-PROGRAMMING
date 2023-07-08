#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize() {
    mCamera.SetPosition({ 0.0f, 0.0f,-3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
    mStandardEffect.Initialize(shaderFile);
    mStandardEffect.SetCamera(mCamera);

    Mesh earth = MeshBuilder::CreateSphere(30, 30, 1.0f);
    mRenderObject.meshBuffer.Initialize(earth);
    mRenderObject.diffuseTexture.Initialize(L"../../Asserts/Textures/earth.jpg");
}

void GameState::Terminate() {
    mRenderObject.Terminate();
    mStandardEffect.Terminate();

}

void GameState::Render() {

    mStandardEffect.Begin();
        mStandardEffect.Render(mRenderObject);
    mStandardEffect.End();
}

void GameState::Update(float deltaTime) {
   
}

void GameState::DebugUI() {
    ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        mStandardEffect.DebugUI();
    ImGui::End;

}


