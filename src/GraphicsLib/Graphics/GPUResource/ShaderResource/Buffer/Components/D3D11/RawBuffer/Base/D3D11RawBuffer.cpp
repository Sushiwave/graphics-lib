#include "D3D11RawBuffer.hpp"

#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/BufferReader/D3D11RawBufferReader.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		RawBuffer::RawBuffer() noexcept
		{
		}
		RawBuffer::RawBuffer(const RawBufferType bufferType, unsigned int elementCount, unsigned int byteStride, GPUAccessType gpuAccessType, CPUAccessType cpuAccessType, const void* pData)
			: m_bufferType(bufferType),
			  m_byteWidth(elementCount*byteStride),
			  m_byteStride(byteStride),
			  m_elementCount(elementCount),
			  m_cpuAccessType(cpuAccessType),
			  m_gpuAccessType(gpuAccessType)
		{
			auto pDevice = Device::getDevice().Get();
			auto hr = D3D11CreateFunctions::createBuffer(
				pDevice,
				pData,
				m_byteWidth,
				byteStride,
				cpuAccessType,
				gpuAccessType,
				gpuAccessType == GPUAccessType::RW,
				m_bufferType,
				m_buffer.ReleaseAndGetAddressOf()
			);
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create a buffer.");
			}
		}
		void RawBuffer::copy(const RawBuffer src)
		{
			Assert(m_id != src.m_id,
				"The source and destination resources must be different resources.");
			Assert((m_gpuAccessType == GPUAccessType::R && m_cpuAccessType == CPUAccessType::none) == false,
				"Immutable resources are not allowed to perform copy operations.");
			Assert(m_byteStride == src.m_byteStride && m_elementCount == src.m_elementCount,
				"The source and destination resources must have same size.");
			
			Device::getDeviceContext()->CopyResource(m_buffer.Get(), src.m_buffer.Get());
		}
		void RawBuffer::update(const void* pData)
		{
			if ((static_cast<int>(m_cpuAccessType) & static_cast<int>(CPUAccessType::W)) == 0) { return; }

			if (m_gpuAccessType == GPUAccessType::RW)
			{
				Device::getDeviceContext()->UpdateSubresource(m_buffer.Get(), 0, nullptr, pData, 0, 0);
			}
			else
			{
				D3D11_MAPPED_SUBRESOURCE mappedResource;
				auto deviceContext = Device::getDeviceContext();
				deviceContext->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				CopyMemory(mappedResource.pData, pData, m_byteWidth);
				deviceContext->Unmap(m_buffer.Get(), 0);
			}
		}
		void RawBuffer::read(void* result)
		{
			RawBufferReader(m_elementCount, m_byteStride).read(m_buffer.Get(), result);
		}
		unsigned int RawBuffer::getByteWidth() const
		{
			return m_byteWidth;
		}
		unsigned int RawBuffer::getByteStride() const
		{
			return m_byteStride;
		}
		unsigned int RawBuffer::getElementCount() const
		{
			return m_elementCount;
		}
	}
}