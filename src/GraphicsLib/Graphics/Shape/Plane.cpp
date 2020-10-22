#include <GraphicsLib/Graphics/Shape/Plane.hpp>





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
		m_notifySizeChanged(width, height, 1.0f);
	}

	void Plane::changeSize(const cpp::Vector2D<float>& size) const noexcept
	{
		changeSize(size.x, size.y);
	}

	void Plane::changeWidth(float width) const noexcept
	{
		m_notifySizeXChanged(width);
	}

	void Plane::changeHeight(float height) const noexcept
	{
		m_notifySizeYChanged(height);
	}
	cpp::Vector2D<float> Plane::getSizeXY() const noexcept
	{
		return cpp::Vector2D<float>(m_getSizeX(), m_getSizeY());
	}
	float Plane::getWidth() const noexcept
	{
		return m_getSizeX();
	}
	float Plane::getHeight() const noexcept
	{
		return m_getSizeY();
	}
}
