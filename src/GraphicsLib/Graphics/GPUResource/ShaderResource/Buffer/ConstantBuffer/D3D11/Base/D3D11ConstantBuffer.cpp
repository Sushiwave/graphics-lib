#include "D3D11ConstantBuffer.hpp"

namespace cg
{
	namespace d3d11
	{
		ConstantBuffer::ConstantBuffer(unsigned int byteStride, const void* pData)
			: m_buffer(byteStride, pData)
		{
		}
		void ConstantBuffer::set(ShaderStage stage, int unit)
		{
			m_buffer.getCBV()->set(stage, unit, getID());
		}
		void ConstantBuffer::read(void* result)
		{
			m_buffer.read(result);
		}
		BoundedBufferLocationList ConstantBuffer::getBoundedBufferLocationList() const
		{
			return m_buffer.getCBV()->getManagedShaderResourceBufferLocationList();
		}
	}
}

