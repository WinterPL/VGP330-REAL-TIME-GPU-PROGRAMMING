#pragma once
#include "MeshBuffer.h"
#include "Transform.h"
#include "Texture.h"

namespace WNTRengine::Graphics {
	class RenderObject 
	{
	public:
		void Terminate() 
		{

		}
		Transform transform;
		MeshBuffer meshBuffer;
		Texture diffuseTexture;
	};
}