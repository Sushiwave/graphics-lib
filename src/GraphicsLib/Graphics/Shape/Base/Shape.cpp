#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>

#include <DirectXMath.h>





namespace cg
{
	void Shape::notifySizeChanged(float x, float y, float z) const
	{
		m_isSizeChanged = true;
		m_size.x = x;
		m_size.y = y;
		m_size.z = z;
	}
	void Shape::notifySizeXChanged(float x) const
	{
		notifySizeChanged(x, m_size.y, m_size.z);
	}
	void Shape::notifySizeYChanged(float y) const
	{
		notifySizeChanged(m_size.x, y, m_size.z);
	}
	void Shape::notifySizeZChanged(float z) const
	{
		notifySizeChanged(m_size.x, m_size.y, z);
	}
	Shape::Shape()
		: Shape(cpp::Vector3D<float>(1.0, 1.0, 1.0))
	{
	}
	Shape::Shape(const cpp::Vector3D<float>& size)
	{
		notifySizeChanged(size.x, size.y, size.z);
	}

	cpp::Vector3D<float> Shape::getSize() const
	{
		return m_size;
	}
	DirectX::XMFLOAT4X4 Shape::createMatrix() const
	{
		if (m_isSizeChanged)
		{
			DirectX::XMStoreFloat4x4(&m_matrix, DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z));
			m_isSizeChanged = false;
		}
		return m_matrix;
	}
}
