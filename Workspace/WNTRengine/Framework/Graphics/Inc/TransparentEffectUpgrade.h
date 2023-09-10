#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "LightType.h"
#include "Material.h"
#include "BlendState.h"
#include "GaussianBlurEffect.h"

namespace WNTRengine::Graphics
{
	class Camera;
	struct DirectionalLight;
	class RenderObject;
	class Texture;

	class TransparentEffectUpgrade final
	{
	public:
		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);


		void SetCamera(const Camera& camera);
		void SetLightCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetShadowMap(const Texture& shadowMap);

		void DebugUI();
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
			int useDiffuseMap = 0;
			int useNormalMap = 0;
			int useBumpMap = 1;
			int useSpecMap = 0;
			int useCelShading = 0;
			int useShadowMap = 0;
			float bumpWeight = 2.0f;
			float depthBias = 0.000050f;
			float alphaPower = 0.5f;
			float padding[3] = { 0 };
		};
		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightingBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingBuffer = TypedConstantBuffer<SettingData>;
		TransformBuffer mTransformBuffer;
		LightingBuffer mLightingBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingBuffer mSettingBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;

		BlendState mBlendState;
		GaussianBlurEffect mGaussianEffect;

		SettingData mSettingData;
		const Camera* mCamera = nullptr;
		const Camera* mLightCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
		const Texture* mShadowMap = nullptr;
	};
}

