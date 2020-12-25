#include <GraphicsLib/Graphics/Shape/Box.hpp>





namespace cg
{
	Box::Box()
		: Box(1.0f, 1.0f, 1.0f)
	{
	}

	Box::Box(const cpp::Vector3D<float>& size)
		: Shape(size)
	{
	}

	Box::Box(float width, float height, float depth)
		: Box(cpp::Vector3D<float>(width, height, depth))
	{
	}

	void Box::changeSize(const cpp::Vector3D<float>& size) const noexcept
	{
		notifySizeChanged(size.x, size.y, size.z);
	}

	void Box::changeSize(float width, float height, float depth) const noexcept
	{
		notifySizeChanged(width, height, depth);
	}

	void Box::changeWidth(float width) const noexcept
	{
		notifySizeXChanged(width);
	}

	void Box::changeHeight(float height) const noexcept
	{
		notifySizeYChanged(height);
	}

	void Box::changeDepth(float depth) const noexcept
	{
		notifySizeZChanged(depth);
	}
	float Box::getWidth() const noexcept
	{
		return getSize().x;
	}
	float Box::getHeight() const noexcept
	{
		return getSize().y;
	}
	float Box::getDepth() const noexcept
	{
		return getSize().z;
	}
}
