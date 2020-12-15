#pragma once
#include <GraphicsLib/Graphics/Transform/Transform.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/Light.hpp>
#include <GraphicsLib/Graphics/Transform/Transformable.hpp>





namespace cg
{
	template <typename ColorConstant_, typename AttenuationConstant_>
	class PositionableLightConstant
		: public LightBaseConstant<ColorConstant_>
	{
	private:
		AttenuationConstant_ m_attenuation;
	public:
		PositionableLightConstant(const Constant sourceConstant)
			: LightBaseConstant<ColorConstant_>(sourceConstant),
			  m_attenuation(sourceConstant.getP())
		{
		}
		virtual ~PositionableLightConstant() = default;

		[[nodiscard]] AttenuationConstant_ getAttenuationConstant() const noexcept
		{
			return m_attenuation;
		}
	};


	class PositionableLight
		: public Light,
		  public Transformable
	{
	private:
		std::shared_ptr<Constant> m_pAttenuation;
	protected:
		template <typename AttenuationConstant_>
		[[nodiscard]] AttenuationConstant_ getAttenuationConstant() const
		{
			return *std::dynamic_pointer_cast<AttenuationConstant_>(m_pAttenuation);
		}
	public:
		template <typename ColorConstant_, typename AttenuationConstant_>
		PositionableLight(const Type& type, const std::string& name, const PositionableLightConstant<ColorConstant_, AttenuationConstant_>& positionableLightConstant, const std::shared_ptr<Constant>& mainConstant)
			: Light(type, name, positionableLightConstant, mainConstant),
			  m_pAttenuation(std::make_shared<AttenuationConstant_>(positionableLightConstant.getAttenuationConstant()))
		{
		}
		virtual ~PositionableLight() = default;
 	};
}
