#pragma once
#include <Window/System/WINAPI/Components/WINAPIWindowComponents.hpp>





namespace cg
{
	namespace winapi
	{
		class WindowHandle
		{
		private:
			static HWND m_windowHandle;
		private:
			WindowHandle() = default;
		public:
			static void initialize(WindowComponents components);

			[[nodiscard]] static HWND get() noexcept;
		};
	}
}
