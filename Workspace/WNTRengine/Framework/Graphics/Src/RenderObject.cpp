#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;

void RenderObject::Terminate()
{
	diffuseMapId = 0 ;
	normalMapId  = 0 ;
	bumpMapId    = 0 ;
	specMapId    = 0;
	modelId = 0;
	meshBuffer.Terminate();
}

RenderGroup Graphics::CreateRenderGroup(ModelId modelId)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	RenderGroup renderGroup = CreateRenderGroup(*model);
	for (auto& renderObject : renderGroup)
	{
		renderObject.modelId = modelId;
	}
	return renderGroup;
}

RenderGroup Graphics::CreateRenderGroup(const Model& model) {
	RenderGroup renderGroup;
	renderGroup.reserve(model.meshData.size());

	auto TryLoadTexture = [](const auto& textureName) -> TextureId
	{
		if (textureName.empty())
		{
			return 0;
		}
		return TextureManager::Get()->LoadTexture(textureName, false);
	};


	for (auto& meshData : model.meshData)
	{
		auto& renderObject = renderGroup.emplace_back();
		if (meshData.materialIndex < model.materialData.size())
		{
			auto& materialData = model.materialData[meshData.materialIndex];
			renderObject.material = materialData.material;
			renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
			renderObject.specMapId = TryLoadTexture(materialData.specularMapName);
			renderObject.bumpMapId = TryLoadTexture(materialData.bumpMapName);
			renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
		}

		renderObject.meshBuffer.Initialize(meshData.mesh);
	}
	return renderGroup;
}


void Graphics::CleanupRenderGroup(RenderGroup& renderGroup) {
	for (auto& renderObject : renderGroup)
	{
		renderObject.Terminate();
	}
}
