#pragma once

#include "MeshTypes.h"

namespace WNTRengine::Graphics 
{
	class Terrain final
	{
	public:
		void Initialize(const std::filesystem::path& fileName, float heightScale);
		float GetHeight(const WNTRmath::Vector3& position)const;

		Mesh mesh;
		uint32_t mRows;
		uint32_t mColumns;
	};
}