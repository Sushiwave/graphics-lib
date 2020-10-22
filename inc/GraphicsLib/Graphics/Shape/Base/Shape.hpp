#pragma once
#include <ThirdParty/CPPLib/DesignPattern/Observer/Subject.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>





namespace cg
{
	class Shape
		: public cpp::Subject
	{
	private:
		mutable cpp::Vector3D<float> m_size;
	protected:
		void m_notifySizeChanged(float x, float y, float z) const;
		void m_notifySizeXChanged(float x) const;
		void m_notifySizeYChanged(float y) const;
		void m_notifySizeZChanged(float z) const;

		float m_getSizeX() const noexcept;
		float m_getSizeY() const noexcept;
		float m_getSizeZ() const noexcept;
	public:
		Shape(const cpp::Vector3D<float>& size);
		virtual ~Shape() = default;

		cpp::Vector3D<float> getSize() const;
	};
}
