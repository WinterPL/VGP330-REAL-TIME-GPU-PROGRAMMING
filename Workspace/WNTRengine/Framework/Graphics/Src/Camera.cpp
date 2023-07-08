#include "Precompiled.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	mProjectionMode = mode;
}

void Camera::SetPosition(const WNTRmath::Vector3& position)
{
	mPosition = position;
}

void Camera::SetDirection(const WNTRmath::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = WNTRmath::Normalize(direction);
	if (WNTRmath::Abs(WNTRmath::Dot(dir, WNTRmath::Vector3::YAxis)) < 0.995f)
		mDirection = dir;
}

void Camera::SetLookAt(const WNTRmath::Vector3& target)
{
	SetDirection(target - mPosition);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * WNTRmath::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f * WNTRmath::Constants::DegToRad;
	mFov = WNTRmath::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	mAspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
	const WNTRmath::Vector3 right = WNTRmath::Normalize(Cross(WNTRmath::Vector3::YAxis, mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	mPosition += WNTRmath::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	WNTRmath::Matrix4 matRotate = WNTRmath::Matrix4::RotationY(radian);
	mDirection = WNTRmath::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float radian)
{
	const WNTRmath::Vector3 right = WNTRmath::Normalize(Cross(WNTRmath::Vector3::YAxis, mDirection));
	const WNTRmath::Matrix4 matRot = WNTRmath::Matrix4::RotationAxis(right, radian);
	const WNTRmath::Vector3 newLook = WNTRmath::TransformNormal(mDirection, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * WNTRmath::Constants::DegToRad;
	constexpr float maxZoom = 10.0f * WNTRmath::Constants::DegToRad;
	mFov = WNTRmath::Clamp(mFov - amount, maxZoom, minZoom);
}

const WNTRmath::Vector3& Camera::GetPosition() const
{
	return mPosition;
}

const WNTRmath::Vector3& Camera::GetDirection() const
{
	return mDirection;
}

WNTRmath::Matrix4 Camera::GetViewMatrix() const
{
	const WNTRmath::Vector3 l = mDirection;
	const WNTRmath::Vector3 r = WNTRmath::Normalize(WNTRmath::Cross(WNTRmath::Vector3::YAxis, l));
	const WNTRmath::Vector3 u = WNTRmath::Normalize(WNTRmath::Cross(l, r));
	const float x = -WNTRmath::Dot(r, mPosition);
	const float y = -WNTRmath::Dot(u, mPosition);
	const float z = -WNTRmath::Dot(l, mPosition);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

WNTRmath::Matrix4 Camera::GetProjectionMatrix() const
{
	return (mProjectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

WNTRmath::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
	const float h = 1.0f / tan(mFov * 0.5f);
	const float w = h / a;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float q = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, q,       1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

WNTRmath::Matrix4 Camera::GetOrthographicMatrix() const
{
	const float w = (mWidth == 0.0f) ? GraphicsSystem::Get()->GetBackBufferWidth() : mWidth;
	const float h = (mHeight == 0.0f) ? GraphicsSystem::Get()->GetBackBufferHeight() : mHeight;
	const float f = mFarPlane;
	const float n = mNearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}