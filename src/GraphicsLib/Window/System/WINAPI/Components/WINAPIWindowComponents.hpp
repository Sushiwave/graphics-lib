#pragma once
#include <Window/System/WINAPI/WINAPIWindowSystem.hpp>





namespace cg
{
	namespace winapi
	{
		class WindowComponents
		{
		private:
			friend class winapi::WindowSystem;
		private:
			HWND m_windowHandle;
		private:
			WindowComponents(const HWND& windowHandle);
		public:
			virtual ~WindowComponents() = default;

			[[nodiscard]] HWND getWindowHandle() const noexcept;
		};
	}
}
