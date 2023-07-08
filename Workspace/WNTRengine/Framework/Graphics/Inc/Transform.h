#pragma once
#include  "Common.h"

namespace WNTRengine::Graphics 
{
	struct Transform 
	{
		WNTRmath::Vector3 position = WNTRmath::Vector3::Zero;
		WNTRmath::Quaternion rotation = WNTRmath::Quaternion::Identity;
		WNTRmath::Vector3 scale = WNTRmath::Vector3::One;

		WNTRmath::Matrix4 GetMatrix4() const
		{
			return{
				WNTRmath::Matrix4::Scaling(scale) *
				WNTRmath::Matrix4::MatrixRotationQuaternion(rotation) *
				WNTRmath::Matrix4::Translation(position)
			};
		}
	};

}