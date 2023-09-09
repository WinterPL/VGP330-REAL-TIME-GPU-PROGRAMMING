#include "Precompiled.h"
#include "TerrainEffect.h"	

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

using namespace WNTRengine;
using namespace WNTRengine::WNTRmath;
using namespace WNTRengine::Graphics;

void TerrainEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Terrain.fx";
	mVertexShader.Initialize<Vertex>(shaderFile);
	mPixelShader.Initialize(shaderFile);


	mTransformBuffer.Initialize();
	mLightingBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

}
void TerrainEffect::Terminate()
{
	mSampler.Terminate();
	mSettingBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightingBuffer.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void TerrainEffect::Begin() 
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mLightingBuffer.BindVS(1);
	mLightingBuffer.BindPS(1);

	mMaterialBuffer.BindPS(2);

	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);

	mSampler.BindVS(0);
	mSampler.BindPS(0);
}
void TerrainEffect::End() {
	if (mShadowMap != nullptr)
	{
		Texture::UnbindPS(2);
	}
}

void TerrainEffect::Render(const RenderObject& renderObject)
{
	ASSERT(mCamera != nullptr, "TerrainEffect: no camera specified");
	ASSERT(mDirectionalLight != nullptr, "TerrainEffect: no light specified");

	const auto& matWorld = renderObject.transform.GetMatrix4();
	auto matView = mCamera->GetViewMatrix();
	auto matProj = mCamera->GetProjectionMatrix();

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = mCamera->GetPosition();

	if (mShadowMap != nullptr&& mLightCamera!=nullptr)
	{
		matView = mLightCamera->GetViewMatrix();
		matProj = mLightCamera->GetProjectionMatrix();
		transformData.lwvp = Transpose(matWorld * matView * matProj);
	}
	transformData.viewPosition = mCamera->GetPosition();

	SettingData settingData;
	if (settingData.useShadowMap > 0&&mShadowMap!=nullptr)
	{
		mShadowMap->BindPS(2);
		settingData.useShadowMap = 1;
		settingData.depthBias = mSettingData.depthBias;
	}

	mTransformBuffer.Update(transformData);
	mSettingBuffer.Update(settingData);
	mMaterialBuffer.Update(renderObject.material);
	mLightingBuffer.Update(*mDirectionalLight);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindPS(renderObject.specMapId, 1);

	renderObject.meshBuffer.Render();
}
void TerrainEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("TerrainSEffect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useShadowMap = mSettingData.useShadowMap > 0;
		if (ImGui::Checkbox("UseShadowMap##", &useShadowMap))
		{
			mSettingData.useShadowMap = (useShadowMap) ? 1 : 0;
		}
		ImGui::DragFloat("DepthBias##", &mSettingData.depthBias, 0.0000001f, 0.0f, 1.0f, "%.6f");
	}
}

void TerrainEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}
void TerrainEffect::SetLightCamera(const Camera& camera)
{
	mLightCamera = &camera;
}
void TerrainEffect::SetDirectionalLight(const DirectionalLight& directionalLight) {
	mDirectionalLight = &directionalLight;
}
void TerrainEffect::SetShadowMap(const Texture& shadowMap) 
{
	mShadowMap = &shadowMap;
}