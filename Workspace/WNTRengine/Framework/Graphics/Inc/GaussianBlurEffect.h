#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "RenderTarget.h"
#include "VertexShader.h"

namespace WNTRengine::Graphics
{
	class RenderObject;

	class GaussianBlurEffect
	{
		public:
			void Initialize();
			void Terminate();

			void Begin();
			void End();

			void Render(const RenderObject& renderObject);

			void DebugUI();

			void SetSourceTexture(const Texture& texture) { mSourceTexture = &texture; }
	
			const Texture& GetHorizontalBlurTexture()const { return mHorizontalBlurRenderTarget; }
			const Texture& GetVerticalBlurTexture()const { return mVerticalBlurRenderTarget; }
			const Texture& GetResultTexture()const { return mVerticalBlurRenderTarget; }
			
			void SetBlurIterations(int iterations) { mBlurIterations = iterations; }
			void SetBlurSaturation(float saturation) { mBlurSaturation = saturation; }
	
	private:

		struct SettingData
		{
			float screenWidth;
			float screenHeight;
			float multiplier;
			float padding;

		};

		using SettingBuffer = TypedConstantBuffer<SettingData>;
		SettingBuffer mSettingBuffer;
		
		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;

		VertexShader mVertexShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader	mVerticalBlurPixelShader;

		Sampler mSampler;

		const Texture* mSourceTexture = nullptr;

		int mBlurIterations = 2;
		float mBlurSaturation = 5.0f;
	};				


}

