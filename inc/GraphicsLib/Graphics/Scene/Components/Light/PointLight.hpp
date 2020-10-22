#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/PositionableLight.hpp>





namespace cg
{
	template <typename ColorConstant_, typename AttenuationConstant_>
	class PointLightConstant
		: public PositionableLightConstant<ColorConstant_, AttenuationConstant_>
	{
	public:
		PointLightConstant(const Constant constant)
			: PositionableLightConstant<ColorConstant_, AttenuationConstant_>(constant)
		{
		}
		virtual ~PointLightConstant() = default;
	};

	class PointLight
		: public PositionableLight
	{
	public:
		template <typename ColorConstant_, typename AttenuationConstant_>
		PointLight(const Type& type, const std::string& name, const PointLightConstant<ColorConstant_, AttenuationConstant_>& pointLightConstant, const std::shared_ptr<Constant>& mainConstant)
			: PositionableLight(type, name, pointLightConstant, mainConstant)
		{
		}
		virtual ~PointLight() = default;
	};
}