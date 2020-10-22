#include <Graphics/GPUResource/AlphaBlender/D3D11/D3D11AlphaBlender.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		AlphaBlender::AlphaBlender(const AlphaBlenderDescriptor& descriptor)
			: cg::AlphaBlender(
			  [&]()
			  {
				  Device::getDeviceContext()->OMSetBlendState(m_blendState.Get(), m_blendFactor, 0xffffffff);
			  })
		{
			auto blendFactorV4 = descriptor.getBlendFactor();

			m_blendFactor[0] = blendFactorV4.x;
			m_blendFactor[1] = blendFactorV4.y;
			m_blendFactor[2] = blendFactorV4.z;
			m_blendFactor[3] = blendFactorV4.w;

			auto hr = D3D11CreateFunctions::createBlendState(Device::getDevice().Get(), descriptor, m_blendState.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create BlendState.");
			}
		}
	}
}
