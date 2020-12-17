#include <CPPLib/ImGui/ImGuiVector3D.hpp>
#include <ThirdParty/ImGui/imgui.h>





namespace ImGui
{
	bool InputVector3D(const char* label, cpp::Vector3D<float>& v)
	{
		bool changed = false;
		cpp::Array3<float> v3 = { v.x, v.y, v.z };
		if (ImGui::InputFloat3(label, v3.data()))
		{
			v = cpp::Vector3D<float>(v3);
			changed = true;
		}
		return changed;
	}
	bool SliderVector3D(const char* label, cpp::Vector3D<float>& v, float min, float max)
	{
		bool changed = false;
		cpp::Array3<float> v3 = { v.x, v.y, v.z };
		if (ImGui::SliderFloat3(label, v3.data(), min, max))
		{
			v = cpp::Vector3D<float>(v3);
			changed = true;
		}
		return changed;
	}
}
