#include <CPPLib/ImGui/ImGuiVector2D.hpp>
#include <ThirdParty/ImGui/imgui.h>





namespace ImGui
{
	bool InputVector2D(const char* label, cpp::Vector2D<float>& v)
	{
		bool changed = false;
		cpp::Array2<float> v2 = { v.x, v.y };
		if (ImGui::InputFloat2(label, v2.data()))
		{
			v = cpp::Vector2D<float>(v2);
			changed = true;
		}
		return changed;
	}
	bool SliderVector2D(const char* label, cpp::Vector2D<float>& v, float min, float max)
	{
		bool changed = false;
		cpp::Array2<float> v2 = { v.x, v.y };
		if (ImGui::SliderFloat2(label, v2.data(), min, max))
		{
			v = cpp::Vector2D<float>(v2);
			changed = true;
		}
		return changed;
	}
}
