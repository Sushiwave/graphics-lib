#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/D3D11DefaultStructuredBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		DefaultStructuredBuffer::DefaultStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData, bool isByteAddressBuffer)
			: StructuredBuffer(byteStride, elementCount, CPUAccessFlags::W, GPUAccessFlags::RW, pData, isByteAddressBuffer)
		{
		}

		void DefaultStructuredBuffer::update(const Constant& constant)
		{
			m_buffer.update(constant.getP().get());
		}

		void DefaultStructuredBuffer::set(ShaderStage stage, int unit, GPUAccessFlags usage)
		{
			std::shared_ptr<IShaderResourceMemoryAccessor> accessor;
			switch (usage)
			{
			case GPUAccessFlags::R:
				accessor = m_buffer.getSRV();
				break;
			case GPUAccessFlags::RW:
				accessor = m_buffer.getUAV();
				break;
			default:
				Assert(false, "The given GPUAccessFlags is not supported.");
				return;
			}

			accessor->set(stage, unit);
		}
		void DefaultStructuredBuffer::copy(std::shared_ptr<IStructuredBuffer> src)
		{
			auto d3d11Src = std::dynamic_pointer_cast<StructuredBuffer>(src);
			m_buffer.copy(d3d11Src->getRawBuffer());
		}
	}
}
