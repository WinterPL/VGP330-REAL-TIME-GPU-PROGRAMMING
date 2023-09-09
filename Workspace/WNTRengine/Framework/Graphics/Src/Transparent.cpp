#include "Precompiled.h"
#include "Transparent.h"


#include "Camera.h";
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;


void Transparent::Initialize()
{
	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mHorizontalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mVerticalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	std::filesystem::path shaderFile = "../../Assets/Shaders/Transparent.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mHorizontalBlurPixelShader.Initialize(shaderFile, "HorizontalBlurPS");
	mVerticalBlurPixelShader.Initialize(shaderFile, "VerticalBlurPS");

	mBlendState.Initailize(BlendState::Mode::Transparent);

	mSettingBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void Transparent::Terminate()
{
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
	mVertexShader.Bind();

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

	mSampler.BindPS(0);

}
void Transparent::End()
{
	auto gs = GraphicsSystem::Get();
	gs->ResetRenderTarget();
	gs->ResetViewport();
}

void Transparent::Render(const RenderObject& renderObject)
{

	auto gs = GraphicsSystem::Get();
	mHorizontalBlurRenderTarget.BeginRender();
	mSourceTexture->BindPS(0);
	mHorizontalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(0);
	mHorizontalBlurRenderTarget.EndRender();

	for (uint32_t i = 1; i < mBlurIterations; ++i)
	{
		mVerticalBlurRenderTarget.BeginRender();
		mHorizontalBlurRenderTarget.BindPS(0);
		mVerticalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(0);
		mVerticalBlurRenderTarget.EndRender();

		mHorizontalBlurRenderTarget.BeginRender();
		mVerticalBlurRenderTarget.BindPS(0);
		mHorizontalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(0);
		mHorizontalBlurRenderTarget.EndRender();
	}
	mVerticalBlurRenderTarget.BeginRender();
	mHorizontalBlurRenderTarget.BindPS(0);
	mVerticalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(0);
	mVerticalBlurRenderTarget.EndRender();
	mBlendState.set();

	BlendState::ClearState();
}

void Transparent::DebugUI()
{
	if (ImGui::CollapsingHeader("GaussianBlurEffect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragInt("BlurIterations##", &mBlurIterations, 1, 1, 100);
		ImGui::DragFloat("BlurSaturation##", &mBlurSaturation, 0.001f, 1.0f, 10.0f);
		ImGui::DragFloat("Transparency##", &mAlphaPower, 0.001f, 0.01f, 1.0f);
		ImGui::Text("Horizontal");
		ImGui::Image(mHorizontalBlurRenderTarget.GetRawData(), { 144,144 });
		ImGui::Text("Vertical");
		ImGui::Image(mVerticalBlurRenderTarget.GetRawData(), { 144,144 });
	}
}

