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
		m_notifySizeChanged(size.x, size.y, size.z);
	}

	void Box::changeSize(float width, float height, float depth) const noexcept
	{
		m_notifySizeChanged(width, height, depth);
	}

	void Box::changeWidth(float width) const noexcept
	{
		m_notifySizeXChanged(width);
	}

	void Box::changeHeight(float height) const noexcept
	{
		m_notifySizeYChanged(height);
	}

	void Box::changeDepth(float depth) const noexcept
	{
		m_notifySizeZChanged(depth);
	}
	float Box::getWidth() const noexcept
	{
		return m_getSizeX();
	}
	float Box::getHeight() const noexcept
	{
		return m_getSizeY();
	}
	float Box::getDepth() const noexcept
	{
		return m_getSizeZ();
	}
}
