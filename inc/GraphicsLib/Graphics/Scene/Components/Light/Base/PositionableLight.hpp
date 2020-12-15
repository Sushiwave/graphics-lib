#pragma once
#include <GraphicsLib/Graphics/Transform/Transform.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/Light.hpp>





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
		: public Light
	{
	private:
		std::shared_ptr<Transform> m_transform;
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
			  m_pAttenuation(std::make_shared<AttenuationConstant_>(positionableLightConstant.getAttenuationConstant())),
			  m_transform(std::make_shared<Transform>())
		{
		}
		virtual ~PositionableLight() = default;

		void tweakTransform(const std::function<void(Transform&)>& operation) const;
		[[nodiscard]] Transform& getTransformRef() const noexcept;
 	};
}
