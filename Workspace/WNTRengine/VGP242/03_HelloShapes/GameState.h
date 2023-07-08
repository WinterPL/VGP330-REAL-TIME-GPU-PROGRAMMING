#pragma once

#include "Inc/WNTRengine.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;


class GameState : public AppState
{
public:
	void Initialize();
	void Terminate();
	void Render();
	void DebugUI() {}

	virtual void CreateShape() = 0;

protected:

	struct Vertex {
		Vector3 position;
		Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};

class TrianglesState :public GameState
{
public: 
	void CreateShape();
	void Update(float deltaTime);
};

class SquareState :public GameState {
public:
	void CreateShape();
	void Update(float deltaTime);
};

class HeartState :public GameState {
public:
	void CreateShape();
	void Update(float deltaTime);
};

class SpearState :public GameState {
public:
	void CreateShape();
	void Update(float deltaTime);
};

class FishState :public GameState {
public:
	void CreateShape();
	void Update(float deltaTime);
};
