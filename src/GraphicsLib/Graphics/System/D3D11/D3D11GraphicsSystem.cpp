#include "D3D11GraphicsSystem.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/System/D3D11/Components/D3D11ScreenUpdater.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/MainRenderTarget/MainRenderTarget.hpp>
#include <Graphics/System/D3D11/Components/D3D11GraphicsSystemComponents.hpp>
#include <Window/Components/WINAPI/WindowHandle/WINAPIWindowHandle.hpp>
#include <Window/System/WINAPI/Components/WINAPIWindowComponents.hpp>





namespace cg
{
	namespace d3d11
	{
		std::shared_ptr<IScreenUpdater> d3d11::GraphicsSystem::initialize(int MSAASampleCount, bool fullScreen)
		{
			const auto& windowHandle = winapi::WindowHandle::get();
			auto d3d11Components = d3d11::GraphicsSystemComponents(windowHandle, fullScreen, MSAASampleCount);
			auto components = std::make_shared<d3d11::GraphicsSystemComponents>(d3d11Components);

			Device::initialize(components);
			MainRenderTarget::shared.initialize(components);

			const auto copiedWindow = std::make_shared<winapi::Window>(windowHandle);
			const auto screenUpdater = std::make_shared<d3d11::ScreenUpdater>(components, copiedWindow);

			return screenUpdater;
		}
		void GraphicsSystem::finalize()
		{
			auto deviceContext = Device::getDeviceContext();
			if (deviceContext.Get())
			{
				deviceContext->ClearState();
			}
		}
	}
}
