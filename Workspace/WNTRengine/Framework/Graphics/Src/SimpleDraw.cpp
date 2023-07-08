#include "Precompiled.h"
#include "SimpleDraw.h"

#include "BlendState.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;
using namespace WNTRengine::WNTRmath::Constants;

namespace {
	class SimpleDrawImpl {
	public:
		void Initialize(uint32_t maxVertexCount);
		void Terminate();

		void AddLine(const Vector3& v0, const Vector3& v1, const Color& color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color);

		void Render(const Camera& camera);
	private:
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		ConstantBuffer mConstantBuffer;
		MeshBuffer mMeshBuffer;

		BlendState mBlendState;
		std::unique_ptr<VertexPC[]> mLineVertices;
		std::unique_ptr<VertexPC[]> mFaceVertices;

		uint32_t mLineVertexCount = 0;
		uint32_t mFaceVertexCount = 0;
		uint32_t mMaxVertexCount = 0;

	};
	void SimpleDrawImpl::Initialize(uint32_t maxVertexCount) {
		std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
		mVertexShader.Initialize<VertexPC>(shaderFile);
		mPixelShader.Initialize(shaderFile);
		mConstantBuffer.Initialize(sizeof(Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
		mBlendState.Initailize(BlendState::Mode::AlphaBlend);

		mLineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mFaceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVertexCount = 0;
		mFaceVertexCount = 0;
		mMaxVertexCount = maxVertexCount;
	}
	void SimpleDrawImpl::Terminate() {
		mBlendState.Terminate();
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mPixelShader.Terminate();
		mVertexShader.Terminate();
	}

	void SimpleDrawImpl::AddLine(const Vector3& v0, const Vector3& v1, const Color& color) {
		if (mLineVertexCount + 2 <= mMaxVertexCount) {
			mLineVertices[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVertices[mLineVertexCount++] = VertexPC{ v1, color };
		}
	}
	void SimpleDrawImpl::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color) {
		if (mFaceVertexCount + 3 <= mMaxVertexCount) {
			mLineVertices[mFaceVertexCount++] = VertexPC{ v0, color };
			mLineVertices[mFaceVertexCount++] = VertexPC{ v1, color };
			mLineVertices[mFaceVertexCount++] = VertexPC{ v2, color };
		}
	}

	void SimpleDrawImpl::Render(const Camera& camera) {
		auto matView = camera.GetViewMatrix();
		auto matProj = camera.GetProjectionMatrix();
		auto transform = Transpose(matView * matProj);
		mConstantBuffer.Update(&transform);
		mConstantBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixelShader.Bind();

		mBlendState.set();

		mMeshBuffer.Update(mLineVertices.get(), mLineVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFaceVertices.get(), mFaceVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		BlendState::ClearState();
		mLineVertexCount = 0;
		mFaceVertexCount = 0;
	}
	std::unique_ptr<SimpleDrawImpl> sInstance;
}



void SimpleDraw::StaticInitialize(uint32_t maxVertexCount) {
	sInstance = std::make_unique<SimpleDrawImpl>();
	sInstance->Initialize(maxVertexCount);
}
void SimpleDraw::StaticTerminate() {
	sInstance->Terminate();
	sInstance.reset();
}

void SimpleDraw::AddLine(const Vector3& v0, const Vector3& v1, const Color& color) {
	sInstance->AddLine(v0, v1, color);
}
void SimpleDraw::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color) {
	sInstance->AddFace(v0, v1,v2, color);
}

void SimpleDraw::AddAABB(const Vector3& min, const Vector3& max, const Color& color) {
	AddAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}
void SimpleDraw::AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color) {
	const Vector3 topRightF = { maxX,maxY,minZ };
	const Vector3 botRightF = { maxX,minY,minZ };
	const Vector3 topLeftF  = { minX,maxY,minZ };
	const Vector3 botLeftF = { minX,minY,minZ };

	const Vector3 topRightB = { maxX,maxY,maxZ };
	const Vector3 botRightB = { maxX,minY,maxZ };
	const Vector3 topLeftB  = { minX,maxY,maxZ };
	const Vector3 botLeftB = { minX,minY,maxZ };

	AddLine(topRightF, botRightF, color);
	AddLine(botRightF, botLeftF, color);
	AddLine(botLeftF, topLeftF, color);
	AddLine(topLeftF, topRightF, color);

	AddLine(topRightB , botRightF, color);
	AddLine(botRightB , botLeftF, color);
	AddLine(botLeftB  , topLeftF, color);
	AddLine(topLeftB  , topRightF, color);

	AddLine(topRightF, botRightB, color);
	AddLine(topLeftF, topLeftB, color);

	AddLine(botRightF, botRightB, color);
	AddLine(botLeftF, botRightB, color);
}

void SimpleDraw::AddFilledAABB(const Vector3& min, const Vector3& max, const Color& color) {
	AddFilledAABB(min.x, min.y, min.z, max.x, max.y, max.z, color);
}
void SimpleDraw::AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& color) {
	const Vector3 topRightF = { maxX,maxY,minZ };
	const Vector3 botRightF = { maxX,minY,minZ };
	const Vector3 topLeftF = { minX,maxY,minZ };
	const Vector3 botLeftF = { minX,minY,minZ };

	const Vector3 topRightB = { maxX,maxY,maxZ };
	const Vector3 botRightB = { maxX,minY,maxZ };
	const Vector3 topLeftB = { minX,maxY,maxZ };
	const Vector3 botLeftB = { minX,minY,maxZ };

	//front
	AddFace(topRightF, botRightF, botLeftF, color);
	AddFace(botLeftF, topLeftF, botRightF, color);
	//back
	AddFace(topRightB,topLeftB,botRightB,color);
	AddFace(botLeftB,topRightB,topLeftB,color);
	//top
	AddFace(topRightB,topRightF,topLeftF,color);
	AddFace(topLeftF, topLeftB, topRightB, color);
	//bot
	AddFace(botRightB,botLeftF,botRightF,color);
	AddFace(botLeftF,botRightB,botLeftB, color);
	//right
	AddFace(topRightB,botRightB,botRightF,color);
	AddFace(botRightF,topRightB,topRightB,color);
	//left
	AddFace(topLeftF,botLeftF,botLeftB,color);
	AddFace(botLeftB,topLeftB,topLeftF,color);

}

void SimpleDraw::AddSphere(int slices, int rings, float radius, const Vector3& pos, const Color& color) {
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;

	float vertRotation = (WNTRmath::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	for (int r = 0; r <= rings; ++r) {
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;

		for (int s = 0; s <= slices; ++s) {
			float slice0 = static_cast<float>(s);
			float rotation0 = slice0 * horzRotation;

			float slice1 = static_cast<float>(s+1);
			float rotation1 = slice1 * horzRotation;

			v0 = {  radius * sin(rotation0) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation0) * sin(phi)
			};
			v1 = {  radius * sin(rotation1) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation1) * sin(phi)
			};
			AddLine(v0+pos, v1+pos, color);

			v0 = {	radius * cos(phi),
					radius * cos(rotation0) * sin(phi),
					radius * sin(rotation0) * sin(phi)
					
			};
			v1 = { 	radius * cos(phi),
					radius * cos(rotation1) * sin(phi),
					radius * sin(rotation1) * sin(phi)
			};
			AddLine(v0+pos, v1+pos, color);
		}
	}

}

void SimpleDraw::AddGroundPlane(float size, const Color& color) {
	const float hs = size * 0.5f;
	for (int i = 0; i <= size; ++i) {
		AddLine({ i - hs, 0.0f, -hs }, { i - hs, 0.0f,hs }, color);
		AddLine({ -hs, 0.0f, i-hs }, { hs, 0.0f,i-hs }, color);
	}
}

void SimpleDraw::AddTransform(const Matrix4& m) {
	const Vector3 side = { m._11,m._12,m._13 };
	const Vector3 up   = { m._21,m._22,m._23 };
	const Vector3 look = { m._31,m._32,m._33 };
	const Vector3 pos  = { m._41,m._42,m._43 };

	AddLine(pos, pos + side, Colors::Red);
	AddLine(pos, pos + up, Colors::Green);
	AddLine(pos, pos + look, Colors::Blue);
}

void SimpleDraw::AddCircle(int slices, float radius, const Color& color) {
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	for (int s = 0; s <= slices; ++s) {
		float slice0 = static_cast<float>(s);
		float rotation0 = slice0 * horzRotation;

		float slice1 = static_cast<float>(s + 1);
		float rotation1 = slice1 * horzRotation;
		v0 = { radius * sin(rotation0),
			   0.0f ,
			   radius * cos(rotation0)

		};
		v1 = { radius * sin(rotation1),
				0.0f ,
				radius * cos(rotation1)
		};
		AddLine(v0, v1, color);
	}
}

void SimpleDraw::Render(const Camera& camera) {
	sInstance->Render(camera);
}