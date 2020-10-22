#pragma once
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>





namespace cg
{
	class Plane
		: public Shape
	{
	public:
		Plane();
		Plane(const cpp::Vector2D<float>& size);
		Plane(float width, float height);
		virtual ~Plane() = default;

		void changeSize(float width, float height) const noexcept;
		void changeSize(const cpp::Vector2D<float>& size) const noexcept;
		void changeWidth(float width) const noexcept;
		void changeHeight(float height) const noexcept;

		cpp::Vector2D<float> getSizeXY() const noexcept;
		float getWidth() const noexcept;
		float getHeight() const noexcept;
	};
}
