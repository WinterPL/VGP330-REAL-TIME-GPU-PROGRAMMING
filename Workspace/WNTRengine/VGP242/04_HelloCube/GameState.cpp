#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize() {
	CreateShape();
    mCamera.SetPosition({ 0.0f, 1.0f,-5.0f });
    mCamera.SetLookAt({ 0.0f,0.0f,0.0f });

    mConstantBuffer.Initialize(sizeof(Matrix4));
	//mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
    MeshPC cube = MeshBuilder::CreateCubePC(1, Colors::Red);
    mMeshBuffer.Initialize(cube);

	//std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";
    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
    
    mVertexBuffer.Initialize(shaderFile, VE_Position|VE_Color);
    mPixelShader.Initialize(shaderFile);
}
void GameState::Terminate() {
	mVertices.clear();
	mPixelShader.Terminate();
	mVertexBuffer.Terminate();
	mMeshBuffer.Terminate();
}
float gRotationY = 0.0f;
void GameState::Render() {
	
    mVertexBuffer.Bind();
	mPixelShader.Bind();

    //Matrix4 matWorld = Matrix4::Identity;
    Matrix4 matWorld = Matrix4::RotationY(gRotationY);
    Matrix4 matView = mCamera.GetViewMatrix();
    Matrix4 matProj = mCamera.GetProjectionMatrix();
    Matrix4 matFinal = Transpose(matWorld * matView * matProj);

    mConstantBuffer.Update(&matFinal);
    mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void   cube::CreateShape() {
    //front
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.0f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.0f), Colors::Red });
    //back
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.0f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    //right
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    //left
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Red });
    //top
    mVertices.push_back({ Vector3(-0.5f, 0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    //buttom
    mVertices.push_back({ Vector3(-0.5f, -0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, -0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Red });
    
    mVertices.push_back({ Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
    mVertices.push_back({ Vector3(-0.5f, -0.5f, 0.5f), Colors::Red });
}
void cube::Update(float deltaTime) {
    auto input = InputSystem::Get();


    if (input->IsKeyDown(KeyCode::LEFT)) {
        gRotationY += Constants::HalfPi * deltaTime * 0.5f;
    }
    else if (input->IsKeyDown(KeyCode::RIGHT)) {
        gRotationY -= Constants::HalfPi * deltaTime * 0.5f;
    }
}

