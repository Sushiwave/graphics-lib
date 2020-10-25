#include <GraphicsLib/Graphics/Scene/Components/Camera/Components/Projection/Projection.hpp>
#include <GraphicsLib/System/System.hpp>





namespace cg
{
	Projection::Projection()
		: m_matrix([](){ DirectX::XMFLOAT4X4 identity; DirectX::XMStoreFloat4x4(&identity, DirectX::XMMatrixIdentity()); return identity; }())
	{
	}



	Projection Projection::operator=(const Projection& other)
	{
		this->m_matrix = other.m_matrix;
		return *this;
	}

	void Projection::changeType(ProjectionType type)
	{
		m_type = type;
	}

	ProjectionType Projection::getType() const noexcept
	{
		return m_type;
	}

	void Projection::changeLowerLeft(float x, float y)
	{
		m_lowerLeft.x = x;
		m_lowerLeft.y = y;
		m_isUpdated = true;
	}

	void Projection::changeUpperRight(float x, float y)
	{
		m_upperRight.x = x;
		m_upperRight.y = y;
		m_isUpdated = true;
	}

	void Projection::changeLowerLeft(const cpp::Vector2D<float>& lowerLeft)
	{
		changeLowerLeft(lowerLeft.x, lowerLeft.y);
	}

	void Projection::changeUpperRight(const cpp::Vector2D<float>& upperRight)
	{
		changeUpperRight(upperRight.x, upperRight.y);
	}

	void Projection::changeFov(float fov)
	{
		m_fov = (fov <= 0) ? m_fov : fov;
		m_isUpdated = true;
	}

	void Projection::changeAspect(float aspect)
	{
		m_aspect = (aspect <= 0) ? m_aspect : aspect;
		m_isUpdated = true;
	}

	void Projection::changeNearZ(float z)
	{
		m_nearZ = (z <= 0 || m_farZ <= z) ? m_nearZ : z;
		m_isUpdated = true;
	}

	void Projection::changeFarZ(float z)
	{
		m_farZ = (z <= 0 || z <= m_nearZ) ? m_farZ : z;
		m_isUpdated = true;
	}

	void Projection::tweakLowerLeft(const std::function<void(cpp::Vector2D<float>&)>& operation)
	{
		operation(m_lowerLeft);
		m_isUpdated = true;
	}

	void Projection::tweakUpperRight(const std::function<void(cpp::Vector2D<float>&)>& operation)
	{
		operation(m_upperRight);
		m_isUpdated = true;
	}

	void Projection::tweakFov(const std::function<void(float&)>& operation)
	{
		operation(m_fov);
		changeFov(m_fov);
	}

	void Projection::tweakAspect(const std::function<void(float&)>& operation)
	{
		operation(m_aspect);
		changeAspect(m_aspect);
	}

	void Projection::changeViewWidth(float width)
	{
		m_viewSize.x = width;
		m_isUpdated = true;
	}

	void Projection::tweakViewWidth(const std::function<void(float&)>& operation)
	{
		operation(m_viewSize.x);
		changeViewWidth(m_viewSize.x);
	}

	void Projection::changeViewHeight(float height)
	{
		m_viewSize.y = height;
		m_isUpdated = true;
	}

	void Projection::tweakViewHeight(const std::function<void(float&)>& operation)
	{
		operation(m_viewSize.y);
		changeViewWidth(m_viewSize.y);
	}

	void Projection::changeViewSize(float width, float height)
	{
		m_viewSize.x = width;
		m_viewSize.y = height;
		m_isUpdated = true;
	}

	void Projection::changeViewSize(const cpp::Vector2D<float>& size)
	{
		changeViewSize(size.x, size.y);
	}

	void Projection::tweakViewSize(const std::function<void(cpp::Vector2D<float>&)>& operation)
	{
		operation(m_viewSize);
		changeViewSize(m_viewSize);
	}

	void Projection::tweakNearZ(const std::function<void(float&)>& operation)
	{
		float nearZ = m_nearZ;
		operation(nearZ);
		changeNearZ(nearZ);
	}

	void Projection::tweakFarZ(const std::function<void(float&)>& operation)
	{
		float farZ = m_farZ;
		operation(farZ);
		changeFarZ(farZ);
	}

	cpp::Vector2D<float> Projection::getLowerLeft() const noexcept
	{
		return m_lowerLeft;
	}

	cpp::Vector2D<float> Projection::getUpperRight() const noexcept
	{
		return m_upperRight;
	}

	cpp::Vector2D<float> Projection::getViewSize() const noexcept
	{
		return m_viewSize;
	}

	float Projection::getNearZ() const noexcept
	{
		return m_nearZ;
	}

	float Projection::getFarZ() const noexcept
	{
		return m_farZ;
	}

	float Projection::getAspect() const noexcept
	{
		return m_aspect;
	}

	float Projection::getFov() const noexcept
	{
		return m_fov;
	}

	DirectX::XMFLOAT4X4 Projection::createMatrix() const
	{
		if (m_isUpdated)
		{
			switch (m_type)
			{
			case ProjectionType::perspective:
				DirectX::XMStoreFloat4x4(&m_matrix, DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ));
				break;
			case ProjectionType::orthographic2D:
				{
					const auto size = m_upperRight-m_lowerLeft;
					DirectX::XMStoreFloat4x4(&m_matrix, DirectX::XMMatrixSet(2.0f/size.x,  0.0f,        0.0f, -2.0f*m_lowerLeft.x/size.x-1.0f,
			                                                                 0.0f,        -2.0f/size.y, 0.0f,  2.0f*m_upperRight.y/size.y-1.0f,
			                                                                 0.0f,         0.0f,        0.0f,  0.0f,                           
			                                                                 0.0f,         0.0f,        0.0f,  1.0f));
				}
				break;
			case ProjectionType::orthographic3D:
				DirectX::XMStoreFloat4x4(&m_matrix, DirectX::XMMatrixOrthographicLH(m_viewSize.x, m_viewSize.y, m_nearZ, m_farZ));
				break;
			}
		}
		return m_matrix;
	}
}
