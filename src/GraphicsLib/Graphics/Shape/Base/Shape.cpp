#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>

#include <DirectXMath.h>





namespace cg
{
	void Shape::m_notifySizeChanged(float x, float y, float z) const
	{
		m_size.x = x;
		m_size.y = y;
		m_size.z = z;
		notify();
	}
	void Shape::m_notifySizeXChanged(float x) const
	{
		m_size.x = x;
		notify();
	}
	void Shape::m_notifySizeYChanged(float y) const
	{
		m_size.y = y;	
		notify();
	}
	void Shape::m_notifySizeZChanged(float z) const
	{
		m_size.z = z;
		notify();
	}
	float Shape::m_getSizeX() const noexcept
	{
		return m_size.x;
	}
	float Shape::m_getSizeY() const noexcept
	{
		return m_size.y;
	}
	float Shape::m_getSizeZ() const noexcept
	{
		return m_size.z;
	}
	Shape::Shape(const cpp::Vector3D<float>& size)
	{
		m_size = size;
		notify();
	}

	cpp::Vector3D<float> Shape::getSize() const
	{
		return m_size;
	}
}
