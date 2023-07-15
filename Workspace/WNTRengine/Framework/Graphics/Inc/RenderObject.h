#pragma once
#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Material.h"

namespace WNTRengine::Graphics {
	class RenderObject 
	{
	public:
		void Terminate() 
		{
			meshBuffer.Terminate();
		}
		Transform transform;
		Material material;
		
		TextureId diffuseMapId;
		TextureId normalMapId;

		MeshBuffer meshBuffer;
	};
}