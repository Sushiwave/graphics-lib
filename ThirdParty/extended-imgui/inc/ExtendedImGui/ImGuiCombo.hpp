#pragma once
#include <vector>
#include <string>





namespace ImGui
{
	bool Combo(const char* label, const std::vector<std::string>& itemList, std::string& previewItem, int& previewItemIndex);
}
