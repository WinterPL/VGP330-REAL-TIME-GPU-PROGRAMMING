#pragma once
#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"

namespace WNTRengine::Graphics {
	class RenderObject 
	{
	public:
		void Terminate() 
		{
			meshBuffer.Terminate();
		}
		Transform transform;
		MeshBuffer meshBuffer;
		TextureId diffuseMapId;
	};
}