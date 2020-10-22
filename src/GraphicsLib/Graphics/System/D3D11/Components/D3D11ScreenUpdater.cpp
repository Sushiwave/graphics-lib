#include "D3D11ScreenUpdater.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/System/System.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>





namespace cg
{
	namespace d3d11
	{
		ScreenUpdater::ScreenUpdater(std::shared_ptr<GraphicsSystemComponents> components, std::shared_ptr<winapi::Window> window)
			: m_window(window),
			  m_swapChain(components->getSwapChain())
		{
		}
		std::shared_ptr<winapi::Window> ScreenUpdater::getWindow() const noexcept
		{
			return m_window;
		}
		cpp::com_ptr<IDXGISwapChain> ScreenUpdater::getSwapChain() const noexcept
		{
			return m_swapChain;
		}
		bool ScreenUpdater::update()
		{
			if (m_window->doEvents() == false) { return false; }
			if (m_window->isClosed()) { return false; }

			if (SUCCEEDED(m_swapChain->Present(0, 0))) { return true; }



			LogEX("A device lost has been detected.");
			bool shouldResetAllGPUResources;
			std::shared_ptr<IScreenUpdater> newScreenUpdater;
			if(Device::recover(&shouldResetAllGPUResources, &newScreenUpdater) == false)
			{
				LogEX("Failed to recover the device.");
				return false;
			}

			LogEX("The device has been successfully recovered.");

			if (newScreenUpdater)
			{
				const auto d3d11NewScreenUpdater = std::dynamic_pointer_cast<d3d11::ScreenUpdater>(newScreenUpdater);
				m_swapChain = d3d11NewScreenUpdater->getSwapChain();
				m_window = d3d11NewScreenUpdater->getWindow();
			}

			if (shouldResetAllGPUResources == false) { return true; }

			return true;
		}
	}
}
