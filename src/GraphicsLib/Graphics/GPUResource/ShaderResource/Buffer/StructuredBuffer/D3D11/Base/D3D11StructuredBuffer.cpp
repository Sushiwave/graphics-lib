#include "D3D11StructuredBuffer.hpp"
#include <iterator>





namespace cg
{
	namespace d3d11
	{
		StructuredBuffer::StructuredBuffer(unsigned int byteStride, unsigned int elementCount, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, const void* pData, bool isByteAddressBuffer)
			: m_buffer(isByteAddressBuffer ? RawBufferType::ByteAddressBuffer : RawBufferType::StructuredBuffer, elementCount, byteStride, gpuAccessType, cpuAccessType, getID(), pData)
		{
		}
		void StructuredBuffer::read(void* result)
		{
			m_buffer.read(result);
		}
		BoundedBufferLocationList StructuredBuffer::getBoundedBufferLocationList() const
		{
			auto locationList = m_buffer.getSRV()->getManagedShaderResourceBufferLocationList();
			if (m_buffer.getUAV())
			{
				auto UAVLocation = m_buffer.getUAV()->getManagedShaderResourceBufferLocationList();
				std::copy(locationList.begin(), locationList.end(), std::back_inserter(UAVLocation));
			}
			return locationList;
		}
		RawBufferEX StructuredBuffer::getRawBuffer() const
		{
			return m_buffer;
		}
	}
}
