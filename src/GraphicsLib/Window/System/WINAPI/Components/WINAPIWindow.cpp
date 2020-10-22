#include <Window/System/WINAPI/Components/WINAPIWindow.hpp>
#include <GraphicsLib/System/System.hpp>
#include <GraphicsLib/ImGui/imgui_impl_graphicslib.hpp>




namespace cg
{
	namespace winapi
	{
		Window::Window(int width, int height, bool fullScreen, const std::string& title, const std::string& iconFilenameICO)
		{
			std::string windowClassName = "DirectX11";
			const DWORD style = fullScreen ? WS_VISIBLE | WS_POPUP : WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);
			const DWORD exstyle = 0;
			const HINSTANCE instance = GetModuleHandle(nullptr);

			WNDCLASSEX wc;
			ZeroMemory(&wc, sizeof(WNDCLASSEX));
			wc.cbSize = sizeof(wc);
			wc.hInstance = instance;
			wc.lpszClassName = windowClassName.c_str();
			wc.lpfnWndProc = MsgProc;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			wc.hIcon = static_cast<HICON>(LoadImage(nullptr, iconFilenameICO.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED));
			wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			if (!RegisterClassEx(&wc)) { return; }

			RECT rect = { 0, 0, width, height };
			AdjustWindowRectEx(&rect, style, FALSE, exstyle);

			m_hWnd = CreateWindowEx(
				exstyle, windowClassName.c_str(), title.c_str(), style,
				CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
				nullptr, nullptr, instance, nullptr
			);

			if (!m_hWnd) { return; }

			ShowWindow(m_hWnd, SW_SHOW);

			if (System::getWindowInfo().fullScreen())
			{
				ShowCursor(FALSE);
			}
		}

		Window::Window(const HWND& hWnd)
		{
			m_hWnd = hWnd;
		}

		bool Window::doEvents()
		{
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
			while (msg.message != WM_QUIT)
			{
				if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					return true;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return false;
		}

		bool Window::isClosed() noexcept
		{
			if (IsWindow(m_hWnd)) { return false; }
			return true;
		}

		void Window::close()
		{
			DestroyWindow(m_hWnd);
		}

		HWND Window::getHandle() noexcept
		{
			return m_hWnd;
		}

		LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) { return true; }

			switch (msg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_PAINT:
				ValidateRect(hWnd, nullptr);
				return 0;
			}
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
}
