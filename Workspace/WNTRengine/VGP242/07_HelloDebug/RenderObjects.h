#pragma once
#include <../Engine/Inc/WNTRengine.h>

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

class RenderObjects
{
public:
	virtual void Initialize() {}
	virtual void Terminate() {}
	virtual void Render(const Camera& camera, ConstantBuffer& constantBuffer,bool useTransform) {}
	virtual void Update(float deltaTime,float speed, float RotSpeed) {}
	void SetPosition(const Vector3& pos) { mTransform._41 = pos.x; mTransform._42 = pos.y; mTransform._43 = pos.z;}

protected:
	MeshBuffer mMeshBuffer;
	Texture mDiffuseTexture;
	Matrix4 mTransform;

	float gRotationY = 0.0f;
	float gRevY = 0.0f;

};

class SkySphere :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer,bool useTransform)override;
	void Update(float deltaTime,float speed, float RotSpeed) override;
};


class Sun :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};


class Mercury :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Venus :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Earth :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Mars :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Jupiter :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Saturn :public RenderObjects
{
public:
	void Initialize();
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform);
	void Update(float deltaTime, float speed, float RotSpeed);
};

class Uranus :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Neptune :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};

class Pluto :public RenderObjects
{
public:
	void Initialize()override;
	void Terminate();
	void Render(const Camera& camera, ConstantBuffer& constantBuffer, bool useTransform)override;
	void Update(float deltaTime, float speed, float RotSpeed) override;
};