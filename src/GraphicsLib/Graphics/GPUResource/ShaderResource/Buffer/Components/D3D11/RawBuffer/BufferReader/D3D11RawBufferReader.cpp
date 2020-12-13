#include "D3D11RawBufferReader.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		RawBufferReader::RawBufferReader(unsigned int byteStride, unsigned int elementCount)
			: RawBuffer(RawBufferType::Reader, elementCount, byteStride, GPUAccessType::none, CPUAccessType::RW, nullptr)
		{
		}
		void RawBufferReader::read(ID3D11Buffer* pBuffer, void* result)
		{
			auto deviceContext = Device::getDeviceContext();

			deviceContext->CopyResource(m_buffer.Get(), pBuffer);

			D3D11_MAPPED_SUBRESOURCE mappedResource;
			auto hr = deviceContext->Map(m_buffer.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to read the buffer.");
			}

			memcpy(result, mappedResource.pData, getByteWidth());

			deviceContext->Unmap(m_buffer.Get(), 0);
		}
	}
}
