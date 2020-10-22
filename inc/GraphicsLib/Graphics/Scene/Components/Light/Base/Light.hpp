#pragma once
#include <GraphicsLib/Graphics/DrawableObject/Components/Transform/Transform.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/Components/Constant.hpp>





namespace cg
{
	template <typename ColorConstant_>
	class LightBaseConstant
	{
	private:
		ColorConstant_ m_color;
	public:
		LightBaseConstant(const Constant sourceConstant)
			: m_color(sourceConstant.getP())
		{
		}
		virtual ~LightBaseConstant() = default;

		[[nodiscard]] ColorConstant_ getColorConstant() const noexcept
		{
			return m_color;
		}
	};

	class Light
	{
	public:
		using Type = std::string;
	private:
		Type m_type;
		std::string m_name;

		std::shared_ptr<Constant> m_pColor;
		std::shared_ptr<Constant> m_mainConstant;
	protected:
			template <typename ColorConstant_>
			[[nodiscard]] ColorConstant_ getColorConstant() const
			{
				return *std::dynamic_pointer_cast<ColorConstant_>(m_pColor);
			}
	public:
		template <typename ColorConstant_>
		Light(const Type& type, const std::string& name, const LightBaseConstant<ColorConstant_>& lightBaseConstant, const std::shared_ptr<Constant>& mainConstant)
			: m_type(type),
			  m_name(name),
			  m_pColor(std::make_shared<ColorConstant_>(lightBaseConstant.getColorConstant())),
			  m_mainConstant(mainConstant)
		{
		}
		virtual ~Light() = default;

		[[nodiscard]] Type getType() const noexcept;
		[[nodiscard]] std::string getName() const noexcept;
		[[nodiscard]] Constant getConstant() const noexcept;
		template <typename T>
		[[nodiscard]] std::shared_ptr<T> getConstantP() const noexcept
		{
			return std::dynamic_pointer_cast<T>(m_mainConstant);
		}
	};
}