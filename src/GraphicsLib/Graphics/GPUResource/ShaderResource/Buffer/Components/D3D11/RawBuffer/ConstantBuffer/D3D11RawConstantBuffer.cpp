#include "D3D11RawConstantBuffer.hpp"
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ConstantBufferView.hpp>





namespace cg
{
	namespace d3d11
	{
		RawConstantBuffer::RawConstantBuffer() noexcept
		{
		}
		RawConstantBuffer::RawConstantBuffer(unsigned int byteStride, const ID& memoryAccessorID, const void* pData)
			: RawBuffer(RawBufferType::ConstantBuffer, 1, byteStride, GPUAccessFlags::R, CPUAccessFlags::W, pData)
		{
			m_CBV = std::make_shared<ConstantBufferView>(memoryAccessorID, m_buffer);
		}
		std::shared_ptr<IShaderResourceMemoryAccessor> RawConstantBuffer::getCBV() const
		{
			return m_CBV;
		}
	}
}
