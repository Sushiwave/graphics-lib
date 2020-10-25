#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/Light.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	template <typename ColorConstant_>
	class DirectionalLightConstant
		: public LightBaseConstant<ColorConstant_>
	{
	public:
		DirectionalLightConstant(const Constant constant)
			: LightBaseConstant<ColorConstant_>(constant)
		{
		}
		virtual ~DirectionalLightConstant() = default;
	};

	class DirectionalLight
		: public Light
	{
	public:
		Camera perspective;
	public:
		template <typename ColorConstant_>
		DirectionalLight(const Type& type, const std::string& name, const DirectionalLightConstant<ColorConstant_>& directionalLightConstant, const std::shared_ptr<Constant>& mainConstant)
			: Light(type, name, directionalLightConstant, mainConstant)
		{
		}
		virtual ~DirectionalLight() = default;
	};
}