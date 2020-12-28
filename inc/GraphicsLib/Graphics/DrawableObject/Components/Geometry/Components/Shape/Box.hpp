#pragma once
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Base/Shape.hpp>




namespace cg
{
	class Box
		: public Shape
	{
	public:
		Box();
		Box(const cpp::Vector3D<float>& size);
		Box(float width, float height, float depth);
		virtual ~Box() = default;

		void changeSize(const cpp::Vector3D<float>& size) const noexcept;
		void changeSize(float width, float height, float depth) const noexcept;
		void changeWidth(float width) const noexcept;
		void changeHeight(float height) const noexcept;
		void changeDepth(float depth) const noexcept;

		float getWidth() const noexcept;
		float getHeight() const noexcept;
		float getDepth() const noexcept;
	};
}
