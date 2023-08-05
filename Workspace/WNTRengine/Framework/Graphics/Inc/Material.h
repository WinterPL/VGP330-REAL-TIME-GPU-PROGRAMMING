#pragma once

#include "Colors.h"

namespace WNTRengine::Graphics
{
	struct Material
	{
		Color ambient =  Colors::White;
		Color diffuse =  Colors::White;
		Color specular = Colors::White;
		Color emissive = Colors::Black;
		float power = 1.0f;
		float padding[3] = { 0.0f };
	};

}