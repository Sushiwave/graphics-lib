#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/System/Components/IGraphicsSystemComponents.hpp>
#include <Graphics/System/D3D11/D3D11GraphicsSystem.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class GraphicsSystemComponents
			: public IGraphicsSystemComponents
		{
		private:
			friend class d3d11::GraphicsSystem;

			cpp::com_ptr<ID3D11Device> m_device;
			cpp::com_ptr<ID3D11DeviceContext> m_deviceContext;
			cpp::com_ptr<IDXGISwapChain> m_swapChain;
			cpp::com_ptr<ID3D11Texture2D> m_backBuffer;

			GraphicsSystemComponents(HWND hWnd, bool fullScreen, int MSAASampleCount);
		public:
			virtual ~GraphicsSystemComponents() = default;

			[[nodiscard]] cpp::com_ptr<ID3D11Device> getDevice() const noexcept;
			[[nodiscard]] cpp::com_ptr<ID3D11DeviceContext> getDeviceContext() const noexcept;
			[[nodiscard]] cpp::com_ptr<IDXGISwapChain> getSwapChain() const noexcept;
			[[nodiscard]] cpp::com_ptr<ID3D11Texture2D> getBackBuffer() const noexcept;
		};
	}
}
