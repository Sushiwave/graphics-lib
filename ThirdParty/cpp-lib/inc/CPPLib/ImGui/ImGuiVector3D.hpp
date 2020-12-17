#pragma once
#include <CPPLib/Math/Vector/Vector3D.hpp>





namespace ImGui
{
	bool InputVector3D(const char* label, cpp::Vector3D<float>& v);
	bool SliderVector3D(const char* label, cpp::Vector3D<float>& v, float min, float max);
}
