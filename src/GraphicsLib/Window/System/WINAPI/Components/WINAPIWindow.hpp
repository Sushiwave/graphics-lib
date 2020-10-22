#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>

#include <string>
#include <Windows.h>





namespace cg
{
	namespace winapi
	{
		class Window
		{
		private:
			HWND m_hWnd;
		private:
			static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		public:
			Window() = default;
			Window(int width, int height, bool fullScreen, const std::string& title, const std::string& iconFilenameICO);
			Window(const HWND& hWnd);

			virtual ~Window() = default;

			bool doEvents();

			[[nodiscard]] bool isClosed() noexcept;
			[[nodiscard]] HWND getHandle() noexcept;

			void close();
		};
	}
}
