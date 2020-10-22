#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>

#include <memory>





namespace cg
{
	struct ShapeObserver
	{
		ShapeObserver(const cpp::Vector3D<float> size) noexcept;
		virtual ~ShapeObserver() = default;

		cpp::Vector3D<float> size;
		bool isUpdated = false;
	};
	using ShapeTracker = std::shared_ptr<ShapeObserver>;
}
