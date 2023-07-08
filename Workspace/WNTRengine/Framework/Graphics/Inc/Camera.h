#pragma once

namespace WNTRengine::Graphics
{
	// This camera assumes YAxis as up direction. You
	// cannot look straight up nor straight down.
	class Camera
	{
	public:
		enum class ProjectionMode
		{
			Perspective,
			Orthographic
		};

		void SetMode(ProjectionMode mode);

		void SetPosition(const WNTRmath::Vector3& position);
		void SetDirection(const WNTRmath::Vector3& direction);
		void SetLookAt(const WNTRmath::Vector3& target);

		// Perspective params
		void SetFov(float fov);
		void SetAspectRatio(float ratio);

		// Orthographic params
		void SetSize(float width, float height);

		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		// 3 degrees of freedom for translations
		void Walk(float distance);
		void Strafe(float distance);
		void Rise(float distance);

		// 2 degrees of freedom for rotations
		void Yaw(float radian);
		void Pitch(float radian);

		// 1 degree of freedom for field of view
		void Zoom(float amount);

		const WNTRmath::Vector3& GetPosition() const;
		const WNTRmath::Vector3& GetDirection() const;

		WNTRmath::Matrix4 GetViewMatrix() const;
		WNTRmath::Matrix4 GetProjectionMatrix() const;

		WNTRmath::Matrix4 GetPerspectiveMatrix() const;
		WNTRmath::Matrix4 GetOrthographicMatrix() const;

	private:
		ProjectionMode mProjectionMode = ProjectionMode::Perspective;

		WNTRmath::Vector3 mPosition = WNTRmath::Vector3::Zero;
		WNTRmath::Vector3 mDirection = WNTRmath::Vector3::ZAxis;

		// 0 aspect ratio = use back buffer dimension
		float mFov = 60.0f * WNTRmath::Constants::DegToRad;
		float mAspectRatio = 0.0f;

		// 0 width or height = use back buffer dimension
		float mWidth = 0.0f;
		float mHeight = 0.0f;

		float mNearPlane = 0.01f;
		float mFarPlane = 10000.0f;
	};
}