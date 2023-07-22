#pragma once

#include "Colors.h"

namespace WNTRengine::Graphics 
{
	struct DirectionalLight 
	{
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		WNTRmath::Vector3 direction = WNTRmath::Vector3::ZAxis;
		float padding = 0;
	};

}