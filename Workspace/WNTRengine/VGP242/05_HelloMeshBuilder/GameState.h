#pragma once
#include "Inc/AppState.h"
#include "Inc/WNTRengine.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	//void DebugUI() {}
protected:
	virtual void CreateShape() = 0;

protected:

	struct Vertex {
		Vector3 position;
		Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	MeshBuffer mMeshBuffer;
	VertexShader mVertexBuffer;
	ID3D11InputLayout* mInputLayout = nullptr;
	PixelShader mPixelShader;
	ConstantBuffer mConstantBuffer;
	Camera mCamera;
	MeshPC obj = MeshBuilder::CreateCubePC(1, Colors::Red);
};

class Obj :public GameState
{
public:
	void CreateShape();
	void Update(float deltaTime);
};


