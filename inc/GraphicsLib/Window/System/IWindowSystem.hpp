#pragma once
#include <GraphicsLib/Window/System/Components/WindowInfo.hpp>




namespace cg
{
	class IWindowSystem
	{
	public:
		virtual void initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& title, const std::string& iconFilenameICO) = 0;
		virtual void finalize() = 0;

		virtual WindowInfo getWindowInfo() const = 0;
	};
}