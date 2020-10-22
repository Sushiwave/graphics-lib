#include <Graphics/GPUResource/IndexBuffer/D3D11/D3D11IndexBuffer.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		IndexBuffer::IndexBuffer(const void* indices, unsigned int indexCount, unsigned int byteStride)
			: m_indexCount(indexCount),
			  m_isByteStride32bit(byteStride == 4 ? true : false)
		{
			Assert(0 < indexCount, "indexCount must be greater than 0.");

			auto hr = D3D11CreateFunctions::createBuffer(Device::getDevice().Get(), indices, indexCount * byteStride, byteStride, CPUAccessFlags::none, GPUAccessFlags::R, false, RawBufferType::IndexBuffer, m_indexBuffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create IndexBuffer.");
			}
		}

		int IndexBuffer::getIndexCount() const noexcept
		{
			return m_indexCount;
		}

		void IndexBuffer::set()
		{
			Device::getDeviceContext()->IASetIndexBuffer(m_indexBuffer.Get(), m_isByteStride32bit ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT, 0);
		}
	}
}
