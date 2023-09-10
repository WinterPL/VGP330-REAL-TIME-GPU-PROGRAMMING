#pragma once
#pragma once


#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "RenderTarget.h"
#include "VertexShader.h"
#include "BlendState.h"
#include "LightType.h"
#include "Material.h"

namespace WNTRengine::Graphics
{
	class Camera;
	struct DirectionalLight;
	class RenderObject;
	class Texture;

	class Transparent
	{
	public:
		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void DebugUI();

		void SetSourceTexture(const Texture& texture) { mSourceTexture = &texture; }

		const Texture& GetHorizontalBlurTexture()const { return mHorizontalBlurRenderTarget; }
		const Texture& GetVerticalBlurTexture()const { return mVerticalBlurRenderTarget; }
		const Texture& GetResultTexture()const { return mVerticalBlurRenderTarget; }

		void SetCamera(const Camera& camera);
		void SetLightCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetShadowMap(const Texture& shadowMap);
		void SetBlurIterations(int iterations) { mBlurIterations = iterations; }
		void SetBlurSaturation(float saturation) { mBlurSaturation = saturation; }
		void SetAlphaPower(float alphaPower) { mAlphaPower = alphaPower; }


	private:
		struct TransformData
		{
			WNTRmath::Matrix4 world;
			WNTRmath::Matrix4 wvp;
			WNTRmath::Matrix4 lwvp;
			WNTRmath::Vector3 viewPosition;
			float padding = 0;
		};


		struct SettingData
		{
			int useDiffuseMap = 1;
			int useNormalMap = 0;
			int useBumpMap = 0;
			int useSpecMap = 0;
			int useCelShading = 0;
			int useShadowMap = 0;
			float bumpWeight = 1.0f;
			float depthBias = 0.000050f;

			float screenWidth = 0;
			float screenHeight = 0;
			float multiplier = 0;
			float alphaPower = 0;
		};
		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightingBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingBuffer = TypedConstantBuffer<SettingData>;
		TransformBuffer mTransformBuffer;
		LightingBuffer mLightingBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingBuffer mSettingBuffer;

		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader	mVerticalBlurPixelShader;

		Sampler mSampler;

		BlendState mBlendState;

		SettingData mSettingData;
		const Texture* mSourceTexture = nullptr;
		const Camera* mCamera = nullptr;
		const Camera* mLightCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
		const Texture* mShadowMap = nullptr;

		int mBlurIterations = 1;
		float mBlurSaturation = 1.0f;
		float mAlphaPower = 0.5f;
	};
}

