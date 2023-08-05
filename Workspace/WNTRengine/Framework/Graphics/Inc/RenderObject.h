#pragma once
#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Material.h"
#include "ModelManager.h"

namespace WNTRengine::Graphics {

	struct Model;

	class RenderObject 
	{
	public:
		void Terminate();
		Transform transform;
		Material material;
		
		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId bumpMapId;
		TextureId specMapId;

		ModelId modelId = 0;

		MeshBuffer meshBuffer;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(ModelId modelId);
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (auto& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}

}