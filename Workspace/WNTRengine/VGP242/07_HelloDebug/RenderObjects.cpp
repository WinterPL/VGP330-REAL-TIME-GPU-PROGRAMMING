#include "RenderObjects.h"

void SkySphere::Initialize()
{
    MeshPX Skysphere = MeshBuilder::CreateSkyBoxSphere(500, 500, 500.f);
    mMeshBuffer.Initialize(Skysphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/skysphere/space.jpg");

    mTransform = Matrix4::Identity;
}
void SkySphere::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void SkySphere::Render(const Camera& camera, ConstantBuffer& constantBuffer,bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = mTransform;
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);
}
void SkySphere::Update(float deltaTime, float speed, float RotSpeed)
{
}

void Sun::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(25, 25, 10.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/sun.jpg");

    mTransform = Matrix4::Identity;
}
void Sun::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Sun::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity)* Matrix4::RotationY(gRotationY) ;
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Sun::Update(float deltaTime,float speed, float RotSpeed)
{
    gRotationY += Constants::HalfPi * deltaTime * speed;
}


void Mercury::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(25, 25, 2.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mercury.jpg");

    mTransform = Matrix4::Identity;
}
void Mercury::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Mercury::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Mercury::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}


void Venus::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/venus.jpg");

    mTransform = Matrix4::Identity;
}
void Venus::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Venus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Venus::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}


void Earth::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/earth/earth.jpg");

    mTransform = Matrix4::Identity;
}
void Earth::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Earth::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
	mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Earth::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}


void Mars::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(20, 20, 2.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/mars.jpg");

    mTransform = Matrix4::Identity;
}
void Mars::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Mars::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Mars::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}

void Jupiter::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(50, 50, 6.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/jupiter.jpg");

    mTransform = Matrix4::Identity;
}
void Jupiter::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Jupiter::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Jupiter::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}

void Saturn::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(40, 40, 5.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/saturn.jpg");

    mTransform = Matrix4::Identity;
}
void Saturn::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Saturn::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Saturn::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}

void Uranus::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(35, 35, 4.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/uranus.jpg");

    mTransform = Matrix4::Identity;
}
void Uranus::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Uranus::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Uranus::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}

void Neptune::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(30, 30, 3.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/neptune.jpg");

    mTransform = Matrix4::Identity;
}
void Neptune::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Neptune::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Neptune::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}

void Pluto::Initialize()
{
    MeshPX sphere = MeshBuilder::CreateSpherePX(20, 20, 1.0f);
    mMeshBuffer.Initialize(sphere);

    mDiffuseTexture.Initialize(L"../../Assets/Textures/planets/pluto.jpg");

    mTransform = Matrix4::Identity;
}
void Pluto::Terminate()
{
    mDiffuseTexture.Terminate();
    mMeshBuffer.Terminate();
}
void Pluto::Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)
{
    mDiffuseTexture.BindPS(0);

    Matrix4 matWorld = ((useTransform) ? mTransform : Matrix4::Identity) * Matrix4::RotationY(gRevY);
    Matrix4 matView = camera.GetViewMatrix();
    Matrix4 matProj = camera.GetProjectionMatrix();
    Matrix4 matFinal = matWorld * matView * matProj;
    Matrix4 wvp = Transpose(matFinal) * Matrix4::RotationY(-gRotationY);

    constantBuffer.Update(&wvp);
    constantBuffer.BindVS(0);

    mMeshBuffer.Render();
    Texture::UnbindPS(0);

}
void Pluto::Update(float deltaTime, float speed, float RotSpeed)
{
    gRevY += Constants::HalfPi * deltaTime * speed;
    gRotationY += Constants::HalfPi * deltaTime * RotSpeed;
}