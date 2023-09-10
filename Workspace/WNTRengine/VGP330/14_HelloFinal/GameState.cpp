#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 5.0f,-5.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

    mDirectionalLight.direction = WNTRmath::Normalize({ 1.0f,-1.0f,1.0f });
    mDirectionalLight.ambient = { 0.4f,0.4f,0.4f,1.0f };
    mDirectionalLight.diffuse = { 0.7f,0.7f,0.7f,1.0f };
    mDirectionalLight.specular = { 0.9f,0.9f,0.9f,1.0f };

    std::filesystem::path shaderFile = L"../../Assets/Shaders/TransparentObject.fx";
    mTransparentEffect.Initialize(shaderFile);
    mTransparentEffect.SetCamera(mCamera);
    mTransparentEffect.SetDirectionalLight(mDirectionalLight);
    mTransparentEffect.SetBlurIterations(10);
    mTransparentEffect.SetBlurSaturation(1.0f);
    mTransparentEffect.SetAlphaPower(0.5f);

    mPostProcessingEffect.Initialize(L"../../Assets/Shaders/PostProcess.fx");
    mPostProcessingEffect.SetTexture(&mBaseRenderTarget);
    mPostProcessingEffect.SetTexture(&mTransparentEffect.GetVerticalBlurTexture(),1);

    auto gs = GraphicsSystem::Get();
    const auto screenWidth = gs->GetBackBufferWidth();
    const auto screenHeight = gs->GetBackBufferHeight();
    mBaseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
    mBloomRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
   
    MeshPX screenQuad = MeshBuilder::CreateScreenQuad();
    mScreenQuad.meshBuffer.Initialize(screenQuad);

    mBlendState.Initailize(BlendState::Mode::Transparent);

    auto tm = TextureManager::Get();
    mSunRenderObject.diffuseMapId = tm->LoadTexture(L"planets/sun.jpg");
    mSunRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(1024, 512, 5.0f));
    mSunRenderObject.material.emissive = Colors::White;
    mSunRenderObject.material.power = 1.0f;

    mEarthRenderObject.diffuseMapId = tm->LoadTexture("planets/earth/earth.jpg");
    mEarthRenderObject.normalMapId = tm->LoadTexture("planets/earth/earth_normal.jpg");
    mEarthRenderObject.bumpMapId = tm->LoadTexture("planets/earth/earth_bump.jpg");
    mEarthRenderObject.specMapId = tm->LoadTexture("planets/earth/earth_spec.jpg");
    mEarthRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(1024, 512, 1.0f));
    mEarthRenderObject.material.ambient = { 0.5f,0.5f,0.5f,1.0f };
    mEarthRenderObject.material.diffuse = { 0.8f,0.8f,0.8f,1.0f };
    mEarthRenderObject.material.specular = { 0.5f,0.5f,0.5f,1.0f };
    mEarthRenderObject.material.power = 10.0f;

    mEarthRenderObject.transform.position = { 0.0f,0.0f,-8.0f };
}

void GameState::Terminate()
{
    mEarthRenderObject.Terminate();
    mSunRenderObject.Terminate();
    mScreenQuad.Terminate();
    mBloomRenderTarget.Terminate();
    mBaseRenderTarget.Terminate();

    mPostProcessingEffect.Terminate();
     mTransparentEffect.Terminate();
    mBlendState.Terminate();
}

void GameState::Render()
{
    mBlendState.set();
    mBaseRenderTarget.BeginRender();
        mTransparentEffect.Begin();
            mTransparentEffect.Render(mSunRenderObject);
            mTransparentEffect.Render(mEarthRenderObject);
        mTransparentEffect.End();
        SimpleDraw::AddGroundPlane(20.0f, Colors::White);
         SimpleDraw::Render(mCamera);
    mBaseRenderTarget.EndRender();

   

    //mBloomRenderTarget.BeginRender();
    // Material dummyMaterial;
    // dummyMaterial.power = 1.0f;
    // std::swap(mEarthRenderObject.material, dummyMaterial);
    //    mStandardEffect.Begin();
    //    mStandardEffect.Render(mSunRenderObject);
    //    mStandardEffect.Render(mEarthRenderObject);
    //    mStandardEffect.End();
    // std::swap(mEarthRenderObject.material, dummyMaterial);
    //mBloomRenderTarget.EndRender();

  
    mPostProcessingEffect.Begin();
        mPostProcessingEffect.Render(mScreenQuad);
    mPostProcessingEffect.End();

    BlendState::ClearState();
   
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

    WNTRmath::Vector3 earthposition = { 0.0f,0.0f,-mEarthOffset };
    mEarthRenderObject.transform.position = TransformCoord(earthposition, Matrix4::RotationY(mEarthRevolution));
    mEarthRenderObject.transform.rotation.y = mEarthRotation;

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
        ImGui::Text("Earth");
        ImGui::DragFloat("Offset", &mEarthOffset, 0.01f);
        ImGui::DragFloat("Rotation", &mEarthRotation, 0.01f);
        ImGui::DragFloat("Revolution", &mEarthRevolution, 0.01f);

        //mStandardEffect.DebugUI();
        mPostProcessingEffect.DebugUI();
        mTransparentEffect.DebugUI();
        
    ImGui::End();

}


