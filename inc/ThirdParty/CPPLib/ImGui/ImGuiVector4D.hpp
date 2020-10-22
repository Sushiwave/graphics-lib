#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>





namespace ImGui
{
	bool InputVector4D(const char* label, cpp::Vector4D<float>& v);
	bool SliderVector4D(const char* label, cpp::Vector4D<float>& v, float min, float max);
}
