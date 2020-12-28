#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>
#include <DirectXMath.h>





namespace cg
{
	class Shape
	{
	private:
		mutable cpp::Vector3D<float> m_size;

		mutable DirectX::XMFLOAT4X4 m_matrix;
		mutable bool m_isSizeChanged;
	protected:
		void notifySizeChanged(float x, float y, float z) const;
		void notifySizeXChanged(float x) const;
		void notifySizeYChanged(float y) const;
		void notifySizeZChanged(float z) const;
	public:
		Shape();
		Shape(const cpp::Vector3D<float>& size);
		virtual ~Shape() = default;

		cpp::Vector3D<float> getSize() const;

		[[nodiscard]] DirectX::XMFLOAT4X4 createMatrix() const;
	};
}
