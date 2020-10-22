#include <GraphicsLib/Graphics/Scene/Components/Light/Base/PositionableLight.hpp>





namespace cg
{
	void PositionableLight::tweakTransform(const std::function<void(Transform&)>& operation) const
	{
		operation(*m_transform);
	}
	Transform& PositionableLight::getTransformRef() const noexcept
	{
		return *m_transform;
	}
}
