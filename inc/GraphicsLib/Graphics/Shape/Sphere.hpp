#pragma once
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>





namespace cg
{
	class Sphere
		: public Shape
	{
	public:
		Sphere();
		Sphere(float radius);
		Sphere(const cpp::Vector3D<float>& radius);
		Sphere(float radiusX, float radiusY, float radiusZ);
		virtual ~Sphere() = default;

		void changeRadius(float radius) const noexcept;
		void changeRadius(const cpp::Vector3D<float>& radius) const noexcept;
		void changeRadius(float x, float y, float z) const noexcept;
		void changeRadiusX(float x) const noexcept;
		void changeRadiusY(float y) const noexcept;
		void changeRadiusZ(float z) const noexcept;

		[[nodiscard]] cpp::Vector3D<float> getRadius() const noexcept;
		[[nodiscard]] float getRadiusX() const noexcept;
		[[nodiscard]] float getRadiusY() const noexcept;
		[[nodiscard]] float getRadiusZ() const noexcept;
	};
}
