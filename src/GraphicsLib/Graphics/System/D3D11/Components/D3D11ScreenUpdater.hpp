#pragma once
#include <Window/System/WINAPI/Components/WINAPIWindow.hpp>
#include <Graphics/System/D3D11/Components/D3D11GraphicsSystemComponents.hpp>
#include <GraphicsLib/Graphics/System/Components/IGraphicsSystemComponents.hpp>





namespace cg
{
	namespace d3d11
	{
		class ScreenUpdater
			: public IScreenUpdater
		{
		private:
			std::shared_ptr<winapi::Window> m_window;
			cpp::com_ptr<IDXGISwapChain> m_swapChain;
		public:
			ScreenUpdater(std::shared_ptr<d3d11::GraphicsSystemComponents> components, std::shared_ptr<winapi::Window> window);
			virtual ~ScreenUpdater() = default;

			[[nodiscard]] std::shared_ptr<winapi::Window> getWindow() const noexcept;
			[[nodiscard]] cpp::com_ptr<IDXGISwapChain> getSwapChain() const noexcept;

			[[nodiscard]] bool update() override;
		};
	}
}
