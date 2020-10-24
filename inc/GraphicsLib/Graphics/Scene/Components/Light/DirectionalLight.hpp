#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/Light.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	template <typename ColorConstant_, typename DirectionConstant_>
	class DirectionalLightConstant
		: public LightBaseConstant<ColorConstant_>
	{
	private:
		DirectionConstant_ m_direction;
	public:
		DirectionalLightConstant(const Constant constant)
			: LightBaseConstant<ColorConstant_>(constant),
			  m_direction(constant.getP())
		{
		}
		virtual ~DirectionalLightConstant() = default;

		[[nodiscard]] DirectionConstant_ getDirectionConstant() const noexcept
		{
			return m_direction;
		}
	};

	class DirectionalLight
		: public Light
	{
	private:
		std::shared_ptr<Constant> m_pDirectionConstant;
	protected:
		template <typename DirectionConstant_>
		[[nodiscard]] DirectionConstant_ getDirectionConstant() const
		{
			return *std::dynamic_pointer_cast<DirectionConstant_>(m_pDirectionConstant);
		}
	public:
		Camera camera;
	public:
		template <typename ColorConstant_, typename DirectionConstant_>
		DirectionalLight(const Type& type, const std::string& name, const DirectionalLightConstant<ColorConstant_, DirectionConstant_>& directionalLightConstant, const std::shared_ptr<Constant>& mainConstant)
			: Light(type, name, directionalLightConstant, mainConstant),
			  m_pDirectionConstant(std::make_shared<DirectionConstant_>(directionalLightConstant.getDirectionConstant()))
		{
		}
		virtual ~DirectionalLight() = default;
	};
}