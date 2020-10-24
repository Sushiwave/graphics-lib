#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Light/Base/PositionableLight.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	template <typename ColorConstant_, typename AttenuationConstant_, typename ShapeConstant_>
	class SpotLightConstant
		: public PositionableLightConstant<ColorConstant_, AttenuationConstant_>
	{
	private:
		ShapeConstant_ m_shape;
	public:
		SpotLightConstant(const Constant constant)
			: PositionableLightConstant<ColorConstant_, AttenuationConstant_>(constant),
			  m_shape(constant.getP())
		{
		}
		virtual ~SpotLightConstant() = default;

		[[nodiscard]] ShapeConstant_ getShapeConstant() const noexcept
		{
			return m_shape;
		}
	};

	class SpotLight
		: public PositionableLight
	{
	private:
		std::shared_ptr<Constant> m_pShape;
	protected:
		template <typename ShapeConstant_>
		[[nodiscard]] ShapeConstant_ getShapeConstant() const
		{
			return *std::dynamic_pointer_cast<ShapeConstant_>(m_pShape);
		}
	public:
		Camera camera;
	public:
		template <typename ColorConstant_, typename AttenuationConstant_, typename ShapeConstant_>
		SpotLight(const Type& type, const std::string& name, const SpotLightConstant<ColorConstant_, AttenuationConstant_, ShapeConstant_>& spotLightConstant, const std::shared_ptr<Constant>& mainConstant)
			: PositionableLight(type, name, spotLightConstant, mainConstant),
			  m_pShape(std::make_shared<ShapeConstant_>(spotLightConstant.getShapeConstant()))
		{
		}
		virtual ~SpotLight() = default;
	};
}