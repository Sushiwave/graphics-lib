#include "WINAPIWindowComponents.hpp"





namespace cg
{
	namespace winapi
	{
		WindowComponents::WindowComponents(const HWND& windowHandle)
		{
			m_windowHandle = windowHandle;
		}
		HWND WindowComponents::getWindowHandle() const noexcept
		{
			return m_windowHandle;
		}
	}
}
