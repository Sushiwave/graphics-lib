#include <Graphics/GPUResource/DepthStencilTester/D3D11/D3D11DepthStencilTester.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		DepthStencilTester::DepthStencilTester(ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled)
			: cg::DepthStencilTester(
				[&]()
				{
					Device::getDeviceContext()->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
				},
				depthFunction,
				stencilFunction,
				isDepthTestEnabled,
				isStencilTestEnabled,
			    isDepthBufferWritingOperationEnabled)
		{
			auto hr = D3D11CreateFunctions::createDepthStencilState(Device::getDevice().Get(), depthFunction, stencilFunction, isDepthTestEnabled, isStencilTestEnabled, isDepthBufferWritingOperationEnabled, m_depthStencilState.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create DepthStencilState.");
			}
		}
	}
}