#include "Precompiled.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

void StandardEffect::Initialize(const std::filesystem::path& filepath)
{
	mTransformBuffer.Initialize(sizeof(Matrix4));
	mVertexShader.Initialize<Vertex>(filepath);
	mPixelShader.Initialize(filepath);
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

}
void StandardEffect::Terminate() 
{
	mSampler.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mTransformBuffer.Terminate();
}

void StandardEffect::Begin()
{
	ASSERT(mCamera != nullptr, "StandardEffect: no camera set!");
	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mSampler.BindVS(0);
	mSampler.BindPS(0);

}
void StandardEffect::End()
{
	//Nothing RN
}

void StandardEffect::Render(const RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = mCamera->GetViewMatrix();
	const auto& matProj = mCamera->GetProjectionMatrix();

	Matrix4 matFinal = Transpose(matWorld * matView * matProj);
	mTransformBuffer.Update(&matFinal);

	renderObject.meshBuffer.Render();
}

void StandardEffect::SetCamera(const Camera& camera) 
{
	mCamera = &camera;
}

void StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("Standard##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}