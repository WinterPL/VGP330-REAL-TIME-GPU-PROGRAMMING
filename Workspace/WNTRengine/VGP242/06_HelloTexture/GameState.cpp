#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize() {
    mCamera.SetPosition({ 0.0f, 0.0f,-5.0f });
    mCamera.SetLookAt({ 0.0f,-0.7f,0.0f });

    mConstantBuffer.Initialize(sizeof(Matrix4));

    MeshPX SkyB = MeshBuilder::CreateSkyBox(30.0f);
    MeshPX Globe = MeshBuilder::CreateSpherePX(30,30,1.0f);
    mMeshBuffer.Initialize(SkyB);

    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";
    mVertexBuffer.Initialize<VertexPX>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/skybox/skybox_texture.jpg");
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}
void GameState::Terminate() {
    mSampler.Terminate();
    mDiffuseTexture.Terminate();
    mPixelShader.Terminate();
    mVertexBuffer.Terminate();
    mMeshBuffer.Terminate();
    mConstantBuffer.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void GameState::Render() {

    mVertexBuffer.Bind();
    mPixelShader.Bind();
    mDiffuseTexture.BindPS(0);
    mSampler.BindPS(0);

    //Matrix4 matWorld = Matrix4::Identity;
    Matrix4 matWorld = Matrix4::RotationX(gRotationX) * Matrix4::RotationY(gRotationY);
    Matrix4 matView = mCamera.GetViewMatrix();
    Matrix4 matProj = mCamera.GetProjectionMatrix();
    Matrix4 matFinal = Transpose(matWorld * matView * matProj);

    mConstantBuffer.Update(&matFinal);
    mConstantBuffer.BindVS(0);

    mMeshBuffer.Render();
}

void GameState::Update(float deltaTime) {
    auto input = InputSystem::Get();
    if (input->IsKeyDown(KeyCode::LEFT)) {
        gRotationY += Constants::HalfPi * deltaTime * 0.5f;
    }
    if (input->IsKeyDown(KeyCode::RIGHT)) {
        gRotationY -= Constants::HalfPi * deltaTime * 0.5f;
    }

    if (input->IsKeyDown(KeyCode::UP)) {
        gRotationX += Constants::HalfPi * deltaTime * 0.5f;
    }
    if (input->IsKeyDown(KeyCode::DOWN)) {
        gRotationX -= Constants::HalfPi * deltaTime * 0.5f;
    }
}

