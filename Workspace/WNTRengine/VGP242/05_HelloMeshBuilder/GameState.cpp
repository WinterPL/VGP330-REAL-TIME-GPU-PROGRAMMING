#include "GameState.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::Input;

void GameState::Initialize() {
    CreateShape();
    mCamera.SetPosition({ 0.0f, 0.0f,-10.0f });
    mCamera.SetLookAt({ 0.0f,-0.7f,0.0f });

    mConstantBuffer.Initialize(sizeof(Matrix4));
    //mMeshBuffer.Initialize(mVertices.data(), sizeof(Vertex), mVertices.size());
    //obj = MeshBuilder::CreateCubePC(1, Colors::Red);
    mMeshBuffer.Initialize(obj);


    //std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";
    std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";

    mVertexBuffer.Initialize(shaderFile, VE_Position | VE_Color);
    mPixelShader.Initialize(shaderFile);
}
void GameState::Terminate() {
    mVertices.clear();
    mPixelShader.Terminate();
    mVertexBuffer.Terminate();
    mMeshBuffer.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;
void GameState::Render() {

    mVertexBuffer.Bind();
    mPixelShader.Bind();

    //Matrix4 matWorld = Matrix4::Identity;
    Matrix4 matWorld = Matrix4::RotationY(gRotationY)* Matrix4::RotationX(gRotationX);
    Matrix4 matView = mCamera.GetViewMatrix();
    Matrix4 matProj = mCamera.GetProjectionMatrix();
    Matrix4 matFinal = Transpose(matWorld * matView * matProj);

    mConstantBuffer.Update(&matFinal);
    mConstantBuffer.BindVS(0);

    mMeshBuffer.Render();
}

void   Obj::CreateShape() {
    {//front
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

}
void Obj::Update(float deltaTime) {
    auto input = InputSystem::Get();


    if (input->IsKeyDown(KeyCode::LEFT)) {
        gRotationY += Constants::HalfPi * deltaTime * 0.5f;
    }
    else if (input->IsKeyDown(KeyCode::RIGHT)) {
        gRotationY -= Constants::HalfPi * deltaTime * 0.5f;
    }

    if (input->IsKeyDown(KeyCode::UP)) {
        gRotationX += Constants::HalfPi * deltaTime * 0.5f;
    }
    else if (input->IsKeyDown(KeyCode::DOWN)) {
        gRotationX -= Constants::HalfPi * deltaTime * 0.5f;
    }

    if (input->IsKeyPressed(KeyCode::ONE)) {
        obj = MeshBuilder::CreateCubePC(1, Colors::Red);
        mMeshBuffer.Terminate();
        mMeshBuffer.Initialize(obj);
    }
    else if (input->IsKeyPressed(KeyCode::TWO)) {
        obj = MeshBuilder::CreateRectPC(1, 2, 3);
        mMeshBuffer.Terminate();
        mMeshBuffer.Initialize(obj);
    }
    else if (input->IsKeyPressed(KeyCode::THREE)) {
        obj = MeshBuilder::CreatePlanePC(3, 3, 2);
        mMeshBuffer.Terminate();
        mMeshBuffer.Initialize(obj);
    }
    else if (input->IsKeyPressed(KeyCode::FOUR)) {
        obj = MeshBuilder::CreateCylinderPC(8, 5);
        mMeshBuffer.Terminate();
        mMeshBuffer.Initialize(obj);
    }
    else if (input->IsKeyPressed(KeyCode::FIVE)) {
        obj = MeshBuilder::CreateSpherePC(30, 30, 1.0f);
        mMeshBuffer.Terminate();
        mMeshBuffer.Initialize(obj);
    }
}

