#include "D3D11RawConstantBuffer.hpp"
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ConstantBufferView.hpp>





namespace cg
{
	namespace d3d11
	{
		RawConstantBuffer::RawConstantBuffer() noexcept
		{
		}
		RawConstantBuffer::RawConstantBuffer(unsigned int byteStride, const void* pData)
			: RawBuffer(RawBufferType::ConstantBuffer, 1, byteStride, GPUAccessType::R, CPUAccessType::W, pData)
		{
			m_CBV = std::make_shared<ConstantBufferView>(m_buffer);
		}
		std::shared_ptr<IShaderResourceMemoryAccessor> RawConstantBuffer::getCBV() const
		{
			return m_CBV;
		}
	}
}
