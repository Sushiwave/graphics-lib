#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/D3D11DynamicStructuredBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		DynamicStructuredBuffer::DynamicStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData, bool isByteAddressBuffer)
			: StructuredBuffer(byteStride, elementCount, CPUAccessFlags::W, GPUAccessFlags::R, pData, isByteAddressBuffer)
		{
		}
		void DynamicStructuredBuffer::update(const Constant& constant)
		{
			m_buffer.update(constant.getP().get());
		}
		void DynamicStructuredBuffer::set(ShaderStage stage, int unit)
		{
			m_buffer.getSRV()->set(stage, unit);
		}
		void DynamicStructuredBuffer::copy(std::shared_ptr<IStructuredBuffer> src)
		{
			auto d3d11Src = std::dynamic_pointer_cast<StructuredBuffer>(src);
			m_buffer.copy(d3d11Src->getRawBuffer());
		}
	}
}
