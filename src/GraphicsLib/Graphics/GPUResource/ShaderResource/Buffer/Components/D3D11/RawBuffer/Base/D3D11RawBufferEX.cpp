#include "D3D11RawBufferEX.hpp"
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
    namespace d3d11
    {
		RawBufferEX::RawBufferEX(const RawBufferType bufferType, unsigned int elementCount, unsigned int byteStride, GPUAccessType gpuAccessType, CPUAccessType cpuAccessType, const void* pData)
			: RawBuffer(bufferType, elementCount, byteStride, gpuAccessType, cpuAccessType, pData)
		{
			ShaderResourceType resourceType;
			if (bufferType == RawBufferType::ByteAddressBuffer ||
				bufferType == RawBufferType::StructuredBuffer)
			{
				resourceType = ShaderResourceType::StructuredBuffer;
			}
			else if (bufferType == RawBufferType::ConstantBuffer)
			{
				resourceType = ShaderResourceType::ConstantBuffer;
			}
			else
			{
				Assert(false, "The given RawBufferType is not supported.");
			}

			cpp::com_ptr<ID3D11ShaderResourceView> cpD3DSRV;
			auto hr = D3D11CreateFunctions::createBufferSRV(Device::getDevice().Get(), m_buffer.Get(), m_bufferType, cpD3DSRV.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create ShaderResourceView.");
			}

			m_SRV = std::make_shared<ShaderResourceView>(resourceType, cpD3DSRV);

			if (gpuAccessType == GPUAccessType::RW)
			{
				cpp::com_ptr<ID3D11UnorderedAccessView> cpD3DUAV;
				hr = D3D11CreateFunctions::createBufferUAV(Device::getDevice().Get(), m_buffer.Get(), m_bufferType, cpD3DUAV.ReleaseAndGetAddressOf());
				if(FAILED(hr))
				{
					throw COM_RUNTIME_ERROR(hr, "Failed to create UnorderedAccessView.");
				}

				m_UAV = std::make_shared<UnorderedAccessView>(resourceType, cpD3DUAV);
			}
		}
        std::shared_ptr<IShaderResourceMemoryAccessor> RawBufferEX::getSRV() const noexcept
        {
            return m_SRV;
        }
		std::shared_ptr<IShaderResourceMemoryAccessor> RawBufferEX::getUAV() const noexcept
		{
			return m_UAV;
		}
    }
}
