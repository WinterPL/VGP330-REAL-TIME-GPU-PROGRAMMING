#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace WNTRengine::Graphics
{
	class Camera;
	class RenderObject;
	class Texture;

	class StandardEffect final
	{
	public:
		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);

		void DebugUI();

	private:
		ConstantBuffer mTransformBuffer;
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;

		const Camera* mCamera = nullptr;
	};
}