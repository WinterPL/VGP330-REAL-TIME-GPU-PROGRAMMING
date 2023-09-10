#include "Precompiled.h"
#include "TransparentEffect.h"


#include "Camera.h";
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "TextureManager.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

void Transparent::Initialize(const std::filesystem::path& filepath)
{
	mTransformBuffer.Initialize();
	mLightingBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();
	mVertexShader.Initialize<Vertex>(filepath);
	mPixelShader.Initialize(filepath);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mHorizontalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mVerticalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	//std::filesystem::path shaderFile = "../../Assets/Shaders/Transparent.fx";
	mHorizontalBlurPixelShader.Initialize(filepath, "HorizontalBlurPS");
	mVerticalBlurPixelShader.Initialize(filepath, "VerticalBlurPS");

	mBlendState.Initailize(BlendState::Mode::Transparent);

	mSettingBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void Transparent::Terminate()
{
	mPixelShader.Terminate();
	mMaterialBuffer.Terminate();
	mVertexShader.Terminate();
	mTransformBuffer.Terminate();
	mSampler.Terminate();
	mSettingBuffer.Terminate();
	mHorizontalBlurPixelShader.Terminate();
	mVerticalBlurPixelShader.Terminate();
	mHorizontalBlurRenderTarget.Terminate();
	mVerticalBlurRenderTarget.Terminate();
	mBlendState.Terminate();
}

void Transparent::Begin()
{

	ASSERT(mCamera != nullptr, "StandardEffect: no camera set!");
	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mLightingBuffer.BindVS(1);
	mLightingBuffer.BindPS(1);

	mMaterialBuffer.BindPS(2);

	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();

	SettingData data;
	data.screenWidth = screenWidth;
	data.screenHeight = screenHeight;
	data.multiplier = mBlurSaturation;
	data.alphaPower = mAlphaPower;
	mSettingBuffer.Update(data);
	mSettingBuffer.BindPS(0);

	mSampler.BindVS(0);
	mSampler.BindPS(0);
}
void Transparent::End()
{
	if (mShadowMap != nullptr)
	{
		Texture::UnbindPS(4);
	}
	auto gs = GraphicsSystem::Get();
	gs->ResetRenderTarget();
	gs->ResetViewport();
}

void Transparent::Render(const RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = mCamera->GetViewMatrix();
	const auto& matProj = mCamera->GetProjectionMatrix();

	SettingData settingData;
	settingData.useDiffuseMap = mSettingData.useDiffuseMap > 0 && renderObject.diffuseMapId != 0;
	settingData.useNormalMap = mSettingData.useNormalMap > 0 && renderObject.normalMapId != 0;
	settingData.useDiffuseMap = mSettingData.useDiffuseMap > 0 && renderObject.diffuseMapId != 0;
	settingData.useBumpMap = mSettingData.useBumpMap > 0 && renderObject.bumpMapId != 0;
	settingData.useSpecMap = mSettingData.useSpecMap > 0 && renderObject.specMapId != 0;
	settingData.useCelShading = mSettingData.useCelShading;
	settingData.useShadowMap = mSettingData.useShadowMap > 0 && mShadowMap != nullptr;
	settingData.bumpWeight = mSettingData.bumpWeight;
	settingData.depthBias = mSettingData.depthBias;
	mSettingBuffer.Update(mSettingData);

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = mCamera->GetPosition();
	if (settingData.useShadowMap)
	{
		const auto& matLightView = mLightCamera->GetViewMatrix();
		const auto& matLightProj = mLightCamera->GetProjectionMatrix();
		transformData.lwvp = Transpose(matWorld * matLightView * matLightProj);

		mShadowMap->BindPS(4);
	}
	mTransformBuffer.Update(transformData);

	mLightingBuffer.Update(*mDirectionalLight);

	mMaterialBuffer.Update(renderObject.material);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindPS(renderObject.normalMapId, 1);
	tm->BindVS(renderObject.bumpMapId, 2);
	tm->BindPS(renderObject.specMapId, 3);

	renderObject.meshBuffer.Render();

	auto gs = GraphicsSystem::Get();
	mHorizontalBlurRenderTarget.BeginRender();
	mSourceTexture->BindPS(0);
	mHorizontalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(5);
	mHorizontalBlurRenderTarget.EndRender();

	for (uint32_t i = 1; i < mBlurIterations; ++i)
	{
		mVerticalBlurRenderTarget.BeginRender();
		mHorizontalBlurRenderTarget.BindPS(0);
		mVerticalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(5);
		mVerticalBlurRenderTarget.EndRender();

		mHorizontalBlurRenderTarget.BeginRender();
		mVerticalBlurRenderTarget.BindPS(5);
		mHorizontalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(5);
		mHorizontalBlurRenderTarget.EndRender();
	}
	mVerticalBlurRenderTarget.BeginRender();
	mHorizontalBlurRenderTarget.BindPS(5);
	mVerticalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(5);
	mVerticalBlurRenderTarget.EndRender();
}

void Transparent::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void Transparent::SetLightCamera(const Camera& camera)
{
	mLightCamera = &camera;
}

void Transparent::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}
void Transparent::SetShadowMap(const Texture& shadowMap) {
	mShadowMap = &shadowMap;
}

void Transparent::DebugUI()
{
	if (ImGui::CollapsingHeader("TransparentEffect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = mSettingData.useDiffuseMap > 0;
		if (ImGui::Checkbox("UseDiffuseMap##", &useDiffuseMap))
		{
			mSettingData.useDiffuseMap = (useDiffuseMap) ? 1 : 0;
		}
		bool useNormalMap = mSettingData.useNormalMap > 0;
		if (ImGui::Checkbox("UseNormalMap##", &useNormalMap))
		{
			mSettingData.useNormalMap = (useNormalMap) ? 1 : 0;
		}
		bool useBumpMap = mSettingData.useBumpMap > 0;
		if (ImGui::Checkbox("UseBumpMap##", &useBumpMap))
		{
			mSettingData.useBumpMap = (useBumpMap) ? 1 : 0;
		}
		if (useBumpMap == true) {
		ImGui::DragFloat("BumpWeight##", &mSettingData.bumpWeight, 0.1f, 0.0f, 2.0f);
		}
		bool useSpecMap = mSettingData.useSpecMap > 0;
		if (ImGui::Checkbox("UseSpecMap##", &useSpecMap))
		{
			mSettingData.useSpecMap = (useSpecMap) ? 1 : 0;
		}
		bool useCelShading = mSettingData.useCelShading > 0;
		if (ImGui::Checkbox("UseCelShading##", &useCelShading))
		{
			mSettingData.useCelShading = (useCelShading) ? 1 : 0;
		}
		bool useShadowMap = mSettingData.useShadowMap > 0;
		if (ImGui::Checkbox("UseShadowMap##", &useShadowMap))
		{
			mSettingData.useShadowMap = (useShadowMap) ? 1 : 0;
		}
		ImGui::DragFloat("DepthBias##", &mSettingData.depthBias, 0.0000001f, 0.0f, 1.0f, "%.6f");
		ImGui::DragInt("BlurIterations##", &mBlurIterations, 1, 1, 100);
		ImGui::DragFloat("BlurSaturation##", &mBlurSaturation, 0.001f, 1.0f, 10.0f);
		ImGui::DragFloat("Transparency##", &mSettingData.alphaPower, 0.001f, 0.01f, 1.0f);
		ImGui::Text("Horizontal");
		ImGui::Image(mHorizontalBlurRenderTarget.GetRawData(), { 144,144 });
		ImGui::Text("Vertical");
		ImGui::Image(mVerticalBlurRenderTarget.GetRawData(), { 144,144 });
	}
}

