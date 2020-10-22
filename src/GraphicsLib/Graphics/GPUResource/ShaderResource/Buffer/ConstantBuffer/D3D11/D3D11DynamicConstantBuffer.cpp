#include <Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/D3D11/D3D11DynamicConstantBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		DynamicConstantBuffer::DynamicConstantBuffer(unsigned int byteStride, const void* pData)
			: ConstantBuffer(byteStride, pData)
		{
		}
		void DynamicConstantBuffer::update(const Constant& constant)
		{
			m_buffer.update(constant.getP().get());
		}
		void DynamicConstantBuffer::copy(std::shared_ptr<IConstantBuffer> src)
		{
			auto d3d11Src = std::dynamic_pointer_cast<DynamicConstantBuffer>(src);

			m_buffer.copy(d3d11Src->m_buffer);
		}
	}
}
