#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 0.0f,-3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

    mDirectionalLight.direction = WNTRmath::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.4f,0.4f,0.4f,1.0f };
    mDirectionalLight.diffuse = { 0.7f,0.7f,0.7f,1.0f };
    mDirectionalLight.specular = { 0.9f,0.9f,0.9f,1.0f };

    std::filesystem::path shaderFile = L"../../Assets/Shaders/Standard.fx";
    mStandardEffect.Initialize(shaderFile);
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);

    auto tm = TextureManager::Get();
    Mesh earth = MeshBuilder::CreateSphere(60, 60, 1.0f);
    mRenderObject.meshBuffer.Initialize(earth);
    mRenderObject.diffuseMapId = tm->LoadTexture("planets/earth/earth.jpg");
    mRenderObject.normalMapId  = tm->LoadTexture("planets/earth/earth_normal.jpg");
    mRenderObject.bumpMapId    = tm->LoadTexture("planets/earth/earth_bump.jpg");
    mRenderObject.specMapId    = tm->LoadTexture("planets/earth/earth_spec.jpg");

    const uint32_t size = 512;
    mRenderTarget.Initialize(size, size,Texture::Format::RGBA_U8);
}

void GameState::Terminate()
{
    mRenderTarget.Terminate();
    mRenderObject.Terminate();
    mStandardEffect.Terminate();
}

void GameState::Render()
{

    mCamera.SetAspectRatio(1.0f);
        mRenderTarget.BeginRender();
            mStandardEffect.Begin();
            mStandardEffect.Render(mRenderObject);
        mRenderTarget.EndRender();
    mCamera.SetAspectRatio(.0f);

    mStandardEffect.Begin();
        mStandardEffect.Render(mRenderObject);
    mStandardEffect.End();
}

void GameState::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 0.1f);
    const float turnSpeed = 0.1f * deltaTime;
    if (input->IsKeyDown(KeyCode::W)) {
        mCamera.Walk(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::S)) {
        mCamera.Walk(-moveSpeed);
    }

    if (input->IsKeyDown(KeyCode::D)) {
        mCamera.Strafe(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::A)) {
        mCamera.Strafe(-moveSpeed);
    }

    if (input->IsKeyDown(KeyCode::E)) {
        mCamera.Rise(moveSpeed);
    }
    else if (input->IsKeyDown(KeyCode::Q)) {
        mCamera.Rise(-moveSpeed);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON)) {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
    }

}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Draw", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        if (ImGui::CollapsingHeader("Lighting##", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (ImGui::DragFloat3("Directional##Light", &mDirectionalLight.direction.x, 0.01f, -0.01f, 1.0f)){
                mDirectionalLight.direction = WNTRmath::Normalize(mDirectionalLight.direction);
            }
            ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
            ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
            ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
        }
        if (ImGui::CollapsingHeader("Material##", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::ColorEdit4("Ambient##Material", &mRenderObject.material.ambient.r);
            ImGui::ColorEdit4("Diffuse##Material", &mRenderObject.material.diffuse.r);
            ImGui::ColorEdit4("Specular##Material", &mRenderObject.material.specular.r);
            ImGui::ColorEdit4("Emissive##Material", &mRenderObject.material.emissive.r);
            ImGui::DragFloat("Power##Materail", &mRenderObject.material.materialPower,0.01f,1.0f);
        }
        ImGui::Text("Render Target");
        ImGui::Image(
            mRenderTarget.GetRawData(),
            {128, 128},
            { 0,0 },
            { 1,1 },
            { 1,1,1,1 },
            { 1,1,1,1 }
        );


        mStandardEffect.DebugUI();
    ImGui::End();

}


