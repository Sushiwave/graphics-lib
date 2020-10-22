#include <Graphics/System/D3D11/Components/D3D11GraphicsSystemComponents.hpp>
#include <GraphicsLib/System/System.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>

#include <DirectXMath.h>





namespace cg
{
	namespace d3d11
	{
		GraphicsSystemComponents::GraphicsSystemComponents(HWND hWnd, bool fullScreen, int MSAASampleCount)
		{
			auto windowWidth = System::getWindowInfo().getWidth();
			auto windowHeight = System::getWindowInfo().getHeight();

			D3D_FEATURE_LEVEL pFeatureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
			UINT featureLevelsNum = sizeof(pFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);
			D3D_FEATURE_LEVEL featureLevelsSupported;

#ifdef _DEBUG
			UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
			UINT createDeviceFlags = 0;
#endif

			D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE };
			int driverTypesNum = static_cast<int>(sizeof(driverTypes) / sizeof(D3D_DRIVER_TYPE));
			for (int i = 0; i < driverTypesNum; ++i)
			{
				auto hr = D3D11CreateDevice(nullptr,
					driverTypes[i],
					nullptr,
					createDeviceFlags,
					pFeatureLevels,
					featureLevelsNum,
					D3D11_SDK_VERSION,
					m_device.ReleaseAndGetAddressOf(),
					&featureLevelsSupported,
					m_deviceContext.ReleaseAndGetAddressOf());

				if (SUCCEEDED(hr)) { break; }
			}

			auto format = DXGI_FORMAT_R8G8B8A8_UNORM;

			DXGI_SAMPLE_DESC sampleDesc;

			if (SUCCEEDED(m_device->CheckMultisampleQualityLevels(format, MSAASampleCount, &sampleDesc.Quality)))
			{
				if (0 < sampleDesc.Quality)
				{
					sampleDesc.Count = MSAASampleCount;
					sampleDesc.Quality -= 1;
				}
			}
			else
			{
				LogEX("The specified MSAASampleCount = %d is not supported on this device. Force the sampleCount to be 1.", MSAASampleCount);
				sampleDesc.Count = 1;
				sampleDesc.Quality = 0;
			}

			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = windowWidth;
			sd.BufferDesc.Height = windowHeight;
			sd.BufferDesc.Format = format;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
			sd.OutputWindow = hWnd;
			sd.SampleDesc = sampleDesc;
			sd.Windowed = true;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			cpp::com_ptr<IDXGIDevice1> DXGI;
			auto hr = m_device->QueryInterface(__uuidof(IDXGIDevice1), (void**)DXGI.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to get QueryInterface.");
			}
			cpp::com_ptr<IDXGIAdapter> adapter;
			hr = DXGI->GetAdapter(adapter.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to get DXGIAdapter.");
			}
			cpp::com_ptr<IDXGIFactory> DXGIFactory;
			hr = adapter->GetParent(__uuidof(IDXGIFactory), (void**)DXGIFactory.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to get DXGIFactory.");
			}
			hr = DXGIFactory->CreateSwapChain(m_device.Get(), &sd, m_swapChain.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create SwapChain.");
			}

			m_swapChain->GetBuffer
			(
				0,
				__uuidof(ID3D11Texture2D),
				reinterpret_cast<LPVOID*>(m_backBuffer.ReleaseAndGetAddressOf())
			);

			m_swapChain->SetFullscreenState(fullScreen, nullptr);

			D3D11_VIEWPORT viewport[1];
			viewport[0].TopLeftX = 0.0f;
			viewport[0].TopLeftY = 0.0f;
			viewport[0].Width = static_cast<float>(windowWidth);
			viewport[0].Height = static_cast<float>(windowHeight);
			viewport[0].MinDepth = 0.0f;
			viewport[0].MaxDepth = 1.0f;
			m_deviceContext->RSSetViewports(1, viewport);
		}

		cpp::com_ptr<ID3D11Device> GraphicsSystemComponents::getDevice() const noexcept
		{
			return m_device;
		}

		cpp::com_ptr<ID3D11DeviceContext> GraphicsSystemComponents::getDeviceContext() const noexcept
		{
			return m_deviceContext;
		}

		cpp::com_ptr<IDXGISwapChain> GraphicsSystemComponents::getSwapChain() const noexcept
		{
			return m_swapChain;
		}
		cpp::com_ptr<ID3D11Texture2D> GraphicsSystemComponents::getBackBuffer() const noexcept
		{
			return m_backBuffer;
		}
	}
}
