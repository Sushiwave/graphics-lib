#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Plane.hpp>





namespace cg
{
	Plane::Plane()
		: Plane(1.0f, 1.0f)
	{
	}
	Plane::Plane(const cpp::Vector2D<float>& size)
		: Shape(cpp::Vector3D<float>(size, 1.0))
	{
	}
	Plane::Plane(float width, float height)
		: Plane(cpp::Vector2D<float>(width, height))
	{
	}

	void Plane::changeSize(float width, float height) const noexcept
	{
		notifySizeChanged(width, height, 1.0f);
	}

	void Plane::changeSize(const cpp::Vector2D<float>& size) const noexcept
	{
		changeSize(size.x, size.y);
	}

	void Plane::changeWidth(float width) const noexcept
	{
		notifySizeXChanged(width);
	}

	void Plane::changeHeight(float height) const noexcept
	{
		notifySizeYChanged(height);
	}
	cpp::Vector2D<float> Plane::getSizeXY() const noexcept
	{
		const auto size = getSize();
		return cpp::Vector2D<float>(size.x, size.y);
	}
	float Plane::getWidth() const noexcept
	{
		return getSize().x;
	}
	float Plane::getHeight() const noexcept
	{
		return getSize().y;
	}
}
