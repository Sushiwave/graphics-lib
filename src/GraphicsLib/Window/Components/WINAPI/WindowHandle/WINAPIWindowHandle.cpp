#include <Window/Components/WINAPI/WindowHandle/WINAPIWindowHandle.hpp>





namespace cg
{
	namespace winapi
	{
		HWND WindowHandle::m_windowHandle;

		void WindowHandle::initialize(WindowComponents components)
		{
			m_windowHandle = components.getWindowHandle();
		}
		HWND WindowHandle::get() noexcept
		{
			return m_windowHandle;
		}
	}
}
