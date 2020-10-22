#include <ThirdParty/CPPLib/ImGui/ImGuiVector4D.hpp>
#include <ThirdParty/ExtendedImGui/ImGui/imgui.h>





namespace ImGui
{
	bool InputVector4D(const char* label, cpp::Vector4D<float>& v)
	{
		bool changed = false;
		cpp::Array4<float> v4 = { v.x, v.y, v.z, v.w };
		if (ImGui::InputFloat3(label, v4.data()))
		{
			v = cpp::Vector4D<float>(v4);
			changed = true;
		}
		return changed;
	}
	bool SliderVector4D(const char* label, cpp::Vector4D<float>& v, float min, float max)
	{
		bool changed = false;
		cpp::Array4<float> v4 = { v.x, v.y, v.z, v.w };
		if (ImGui::SliderFloat4(label, v4.data(), min, max))
		{
			v = cpp::Vector4D<float>(v4);
			changed = true;
		}
		return changed;
	}
}