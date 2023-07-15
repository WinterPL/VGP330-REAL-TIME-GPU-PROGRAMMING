#pragma once

#include "Colors.h"

namespace WNTRengine::Graphics 
{
	struct DirectionalLight 
	{
		WNTRmath::Vector3 direction = WNTRmath::Vector3::ZAxis;
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		float padding = 0;
	};

}