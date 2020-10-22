#include "WINAPIWindowSystem.hpp"
#include <Window/Components/WINAPI/WindowHandle/WINAPIWindowHandle.hpp>
#include <GraphicsLib/Context.hpp>





namespace cg
{
	namespace winapi
	{
		void WindowSystem::initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& title, const std::string& iconFilenameICO)
		{
			if (m_window && (m_window->isClosed() == false)) { return; }

			m_windowInfo = WindowInfo(windowWidth, windowHeight, fullScreen, title);

			m_window = std::make_shared<winapi::Window>(windowWidth, windowHeight, fullScreen, title, iconFilenameICO);

			winapi::WindowHandle::initialize(winapi::WindowComponents(m_window->getHandle()));
		}
		void WindowSystem::finalize()
		{
			m_window->close();
		}
		WindowInfo WindowSystem::getWindowInfo() const noexcept
		{
			return m_windowInfo;
		}
	}
}
