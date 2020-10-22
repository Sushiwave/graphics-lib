#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	Camera::Camera()
		: m_transform(std::make_shared<Transform>())
	{
	}
	void Camera::tweakTransform(const std::function<void(Transform&)>& operation) const
	{
		operation(*m_transform);
	}
	Transform& Camera::getTransformRef() const noexcept
	{
		return *m_transform;
	}
}
