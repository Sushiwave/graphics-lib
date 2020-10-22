#pragma once
#include <Window/System/WINAPI/Components/WINAPIWindow.hpp>
#include <GraphicsLib/Window/System/IWindowSystem.hpp>

#include <memory>





namespace cg
{
	namespace winapi
	{
		class WindowSystem
			: public IWindowSystem
		{
		private:
			std::shared_ptr<winapi::Window> m_window = nullptr;
			WindowInfo m_windowInfo;
		public:
			void initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& title, const std::string& iconFilenameICO) override;
			void finalize() override;

			[[nodiscard]] WindowInfo getWindowInfo() const noexcept override;
		};
	}
}
