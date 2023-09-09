#pragma once
#pragma once


#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "RenderTarget.h"
#include "VertexShader.h"
#include "BlendState.h"

namespace WNTRengine::Graphics
{
	class RenderObject;
	class Transparent
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
		void SetAlphaPower(float alphaPower) { mAlphaPower = alphaPower; }

	private:

		struct SettingData
		{
			float screenWidth;
			float screenHeight;
			float multiplier;
			float alphaPower;
		};

		using SettingBuffer = TypedConstantBuffer<SettingData>;
		SettingBuffer mSettingBuffer;

		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;
		RenderTarget TransparentRenderTarget;

		VertexShader mVertexShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader	mVerticalBlurPixelShader;

		Sampler mSampler;

		BlendState mBlendState;

		const Texture* mSourceTexture = nullptr;

		int mBlurIterations = 1;
		float mBlurSaturation = 1.0f;
		float mAlphaPower = 0.5f;
	};


}

