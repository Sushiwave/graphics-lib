#pragma once
#include <vector>
#include <list>
#include <string>





namespace ImGui
{
	class SearchBar
	{
	private:
		std::string m_inputText;

		int m_selectedItem;

		bool m_selected;
		bool m_preFrameAnnotated;
		bool m_preFrameInputDetected;
		bool m_preFrameInputTextActivatedButEmpty;

		bool m_forciblyPulldown;
		int m_frameCounter;
	public:
		SearchBar();
		virtual ~SearchBar() = default;

		void draw(const char* label, const char* annotationMessage, const std::vector<const char*>& itemList, int max_height_in_items, int& selectedItem);
		void draw(const char* label, const char* annotationMessage, const std::vector<std::string>& itemList, int max_height_in_items, int& selectedItem);

		void reset();
	};
}
