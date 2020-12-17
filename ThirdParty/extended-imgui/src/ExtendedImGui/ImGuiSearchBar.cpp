#include <ExtendedImGui/ImGuiSearchBar.hpp>
#include <ExtendedImGui/ImGui/imgui.h>

#include <string.h>
#include <algorithm>





namespace ImGui
{
	SearchBar::SearchBar()
	{
		reset();
	}

	void SearchBar::draw(const char* label, const char* annotationMessage, const std::vector<const char*>& itemList, int max_height_in_items, int& selectedItem)
	{		
#define IMGUI_SEARCH_BAR_TEXT_BUFF_SIZE 256
		char textBuff[IMGUI_SEARCH_BAR_TEXT_BUFF_SIZE] = {};

		const bool inputTextEmpty = m_inputText.empty();
		const bool shouldAnnotate = inputTextEmpty && (m_preFrameInputDetected == false);
		const bool shouldInitializeText = inputTextEmpty && m_preFrameInputDetected && m_preFrameAnnotated;
		


		if (shouldAnnotate)
		{
			strcpy_s(textBuff, annotationMessage);
		}
		else
		{
			if(inputTextEmpty == false)
			{
				strcpy_s(textBuff, m_inputText.c_str());
			}
		}



		bool flags[2] = { false, shouldInitializeText };

		if (shouldAnnotate)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 100)));
		}
		ImGui::InputText(label, textBuff, IMGUI_SEARCH_BAR_TEXT_BUFF_SIZE, ImGuiInputTextFlags_CallbackAlways, [](ImGuiTextEditCallbackData* data)->int
		{
			auto flags = static_cast<bool*>(data->UserData);
			
			auto& inputDetected = flags[0];
			auto shouldInitializeText = flags[1];

			if (shouldInitializeText)
			{
				memset(data->Buf, 0, 256);
				data->BufTextLen = 0;
				data->CursorPos = 0;
				data->BufDirty = true;
			}

			inputDetected = true;

			return 0;
		}, 
		flags);
		if (shouldAnnotate)
		{
			ImGui::PopStyleColor();
		}
		else
		{
			m_inputText = textBuff;
		}



		const auto inputDetected = flags[0];
		const auto shouldPulldown = inputTextEmpty && inputDetected;
		const auto textBuffEmpty = std::strcmp(textBuff, "") == 0;
		

		
		if (inputDetected)
		{
			m_selected = false;
			m_selectedItem = -1;
		}
		


		if (m_forciblyPulldown)
		{
			constexpr float frameCountScale = 2.0;
			const float waitUntilImGuiBackgroundProcessEnded = ImGui::GetIO().Framerate*frameCountScale;
			if (waitUntilImGuiBackgroundProcessEnded <= m_frameCounter)
			{
				m_forciblyPulldown = false;
			}
			m_frameCounter += 1;
		}
		else
		{
			if (shouldPulldown)
			{
				m_forciblyPulldown = true;
				m_frameCounter = 0;
			}
		}
		


		std::string textSmallLetters = textBuff;
		std::transform(textSmallLetters.begin(), textSmallLetters.end(), textSmallLetters.begin(), std::toupper);

		using CandidateWithIndex = std::pair<const char*, int>;
		std::vector<CandidateWithIndex> candidateWithIndexList;
		int itemListSize = static_cast<int>(itemList.size());

		for (int i = 0; i < itemListSize; ++i)
		{
			const auto item = itemList[i];
			auto itemSmallLetters = std::string(item);
			std::transform(itemSmallLetters.begin(), itemSmallLetters.end(), itemSmallLetters.begin(), std::toupper);
			const auto containKeyword = (std::strstr(itemSmallLetters.c_str(), textSmallLetters.c_str()) != nullptr) && (textBuffEmpty == false);
			if (containKeyword || shouldPulldown || m_forciblyPulldown)
			{
				candidateWithIndexList.emplace_back(std::make_pair(item, i));
			}
		}



		std::vector<const char*> candidateList;
		for (auto& indexValue : candidateWithIndexList)
		{
			candidateList.emplace_back(indexValue.first);
		}



		if (candidateList.empty() == false)
		{
			if (m_selected == false)
			{
				auto candidateIndex = -1;
				ImGui::ListBox("", &candidateIndex, candidateList.data(), static_cast<int>(candidateList.size()), (std::min)(static_cast<int>(candidateList.size()), max_height_in_items));
				if (candidateIndex != -1)
				{
					auto item = candidateWithIndexList.at(candidateIndex);
					m_selectedItem = item.second;
					m_inputText = item.first;
					m_forciblyPulldown = false;
					m_selected = true;
				}
			}

		}
		else
		{
			m_selectedItem = -1;
		}



		if (m_selected == false)
		{
			m_selectedItem = -1;
		}
		m_preFrameInputDetected = inputDetected;
		m_preFrameAnnotated = shouldAnnotate;
		selectedItem = m_selectedItem;
	}

	void SearchBar::draw(const char* label, const char* annotationMessage, const std::vector<std::string>& itemList, int max_height_in_items, int& selectedItem)
	{
		std::vector<const char*> itemListConstChar;
		for (auto& item : itemList)
		{
			itemListConstChar.emplace_back(item.c_str());
		}
		draw(label, annotationMessage, itemListConstChar, max_height_in_items, selectedItem);
	}

	void SearchBar::reset()
	{
		m_inputText = "";

		m_selectedItem = -1;

		m_selected                           = false;
		m_preFrameAnnotated                  = false;
		m_preFrameInputDetected              = false;
		m_preFrameInputTextActivatedButEmpty = false;
	
		m_forciblyPulldown = false;
		m_frameCounter = 0;
	}
}
