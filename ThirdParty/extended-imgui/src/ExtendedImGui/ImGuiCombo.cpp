#include <ExtendedImGui/ImGuiCombo.hpp>
#include <ExtendedImGui/ImGui/imgui.h>





namespace ImGui
{
    bool Combo(const char* label, const std::vector<std::string>& itemList, std::string& previewItem, int& previewItemIndex)
    {
        bool changed = false;

        const int listSize = static_cast<int>(itemList.size());

        if (ImGui::BeginCombo(label, previewItem.c_str()))
        {
            for (int i = 0; i < listSize; ++i)
            {
                auto& item = itemList[i];

                bool selected = (item == previewItem);
                if (ImGui::Selectable(item.c_str(), selected))
                {
                    previewItem = item;
                    previewItemIndex = i;
                    changed = true;
                    break;
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        else
        {
            for (int i = 0; i < listSize; ++i)
            {
                if (itemList[i] == previewItem)
                {
                    previewItemIndex = i;
                    break;
                }
            }
        }

        return changed;
    }
}
