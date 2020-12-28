#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Sphere.hpp>





namespace cg
{
	const auto calcRadius3FromSize3 = [](const cpp::Vector3D<float>& size3)   { return size3*0.5f;   };
	const auto calcSize3FromRadius3 = [](const cpp::Vector3D<float>& radius3) { return radius3*2.0f; };
	const auto calcRadiusFromSize = [](float size)   { return size*0.5f;   };
	const auto calcSizeFromRadius = [](float radius) { return radius*2.0f; };

	Sphere::Sphere()
		: Sphere(0.5f, 0.5f, 0.5f)
	{
	}
	Sphere::Sphere(float radius)
		: Sphere(cpp::Vector3D<float>(radius, radius, radius))
	{
	}
	Sphere::Sphere(const cpp::Vector3D<float>& radius)
		: Shape(calcSize3FromRadius3(radius))
	{
	}
	Sphere::Sphere(float radiusX, float radiusY, float radiusZ)
		: Sphere(cpp::Vector3D<float>(radiusX, radiusY, radiusZ))
	{
	}

	void Sphere::changeRadius(float radius) const noexcept
	{
		changeRadius(radius, radius, radius);
	}

	void Sphere::changeRadius(const cpp::Vector3D<float>& radius) const noexcept
	{
		changeRadius(radius.x, radius.y, radius.z);
	}

	void Sphere::changeRadius(float x, float y, float z) const noexcept
	{
		notifySizeChanged(calcSizeFromRadius(x), calcSizeFromRadius(y), calcSizeFromRadius(z));
	}

	void Sphere::changeRadiusX(float x) const noexcept
	{
		notifySizeXChanged(calcSizeFromRadius(x));
	}

	void Sphere::changeRadiusY(float y) const noexcept
	{
		notifySizeYChanged(calcSizeFromRadius(y));
	}

	void Sphere::changeRadiusZ(float z) const noexcept
	{
		notifySizeZChanged(calcSizeFromRadius(z));
	}
	cpp::Vector3D<float> Sphere::getRadius() const noexcept
	{
		return calcRadius3FromSize3(getSize());
	}
	float Sphere::getRadiusX() const noexcept
	{
		return calcRadiusFromSize(getSize().x);
	}
	float Sphere::getRadiusY() const noexcept
	{
		return calcRadiusFromSize(getSize().y);
	}
	float Sphere::getRadiusZ() const noexcept
	{
		return calcRadiusFromSize(getSize().z);
	}
}
