#include <Graphics/GPUResource/Rasterizer/D3D11/D3D11Rasterizer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		Rasterizer::Rasterizer(CullMode cullMode, bool isWireFrameMode, bool multisampleEnable, bool antialiassedLineEnable, bool frontCounterClockwise, bool depthClipEnable, bool scissorEnable)
			: cg::Rasterizer(
			  [&]()
			  {
				  Device::getDeviceContext()->RSSetState(m_state.Get());
			  })
		{
			auto hr = D3D11CreateFunctions::createRasterizerState(Device::getDevice().Get(), cullMode, isWireFrameMode, multisampleEnable, antialiassedLineEnable, frontCounterClockwise, depthClipEnable, scissorEnable, m_state.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create RasterizerState.");
			}
		}
	}
}
