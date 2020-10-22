#include <GraphicsLib/Graphics/Scene/Components/Light/Base/Light.hpp>





namespace cg
{
	Light::Type Light::getType() const noexcept
	{
		return m_type;
	}
	std::string Light::getName() const noexcept
	{
		return m_name;
	}
	Constant Light::getConstant() const noexcept
	{
		return *m_mainConstant;
	}
}
