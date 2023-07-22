#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "LightType.h"
#include "Material.h"

namespace WNTRengine::Graphics 
{
	class Camera;
	class DirectionalLight;
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
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();

	private:
		struct TransformData 
		{
			WNTRmath::Matrix4 world;
			WNTRmath::Matrix4 wvp;
			WNTRmath::Vector3 viewPosition;
			float padding = 0;
		};

		struct SettingData
		{
			int useDiffuseMap = 1;
			int useNormalMap  = 0;
			int useBumpMap    = 0;
			int useSpecMap    = 0;
			int useCelShading = 0;
			float bumpWeight  = 1.0f;
			float padding[2]  = { 0.0f };
		};


		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightingBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingBuffer = TypedConstantBuffer<SettingData>;
		TransformBuffer mTransformBuffer;
		LightingBuffer mLightingBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingBuffer mSettingBuffer;

		//ConstantBuffer mTransformBuffer;
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;

		SettingData mSettingData;
		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
	};
}