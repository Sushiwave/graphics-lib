#include "D3D11ImmutableStructuredBuffer.hpp"
namespace cg
{
	namespace d3d11
	{
		ImmutableStructuredBuffer::ImmutableStructuredBuffer(const void* pData, unsigned int byteStride, unsigned int elementCount, bool isByteAddressBuffer)
			: StructuredBuffer(byteStride, elementCount, CPUAccessFlags::none, GPUAccessFlags::R, pData, isByteAddressBuffer)
		{
		}
		void ImmutableStructuredBuffer::set(ShaderStage stage, int unit)
		{
			m_buffer.getSRV()->set(stage, unit);
		}
	}
}
