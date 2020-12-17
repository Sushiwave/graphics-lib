#pragma once
#include <CPPLib/Math/Vector/Vector2D.hpp>





namespace ImGui
{
	bool InputVector2D(const char* label, cpp::Vector2D<float>& v);
	bool SliderVector2D(const char* label, cpp::Vector2D<float>& v, float min, float max);
}
