#include <Graphics/GPUResource/VertexBuffer/D3D11/D3D11VertexBuffer.hpp>
#include <Graphics/GPUResource/Shader/D3D11/VertexShader/D3D11VertexShader.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>

#include <d3d11.h>





namespace cg
{
	constexpr int ENUM_MIN_CONTROLPOINT = static_cast<int>(D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST);
	constexpr int ENUM_MAX_CONTROLPOINT = static_cast<int>(D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST);





	namespace d3d11
	{
		int VertexBuffer::getVertexCount() const noexcept
		{
			return m_vertexCount;
		}

		void VertexBuffer::set(PrimitiveTopology topology)
		{
			UINT offset = 0;
			auto deviceContext = Device::getDeviceContext();
			deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &m_byteStride, &offset);
			deviceContext->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(topology));
		}

		VertexBuffer::VertexBuffer() noexcept
			: m_vertexCount(0),
			  m_byteStride(0)
		{
		}
		VertexBuffer::VertexBuffer(const void* vertices, unsigned int vertexCount, unsigned int byteStride)
			: m_vertexCount(vertexCount),
			  m_byteStride(byteStride)
		{
			Assert(0 < vertexCount, "vertexCount must be greater than 0.");
			auto hr = D3D11CreateFunctions::createBuffer(Device::getDevice().Get(), vertices, vertexCount * byteStride, byteStride, CPUAccessType::none, GPUAccessType::R, false, RawBufferType::VertexBuffer, m_vertexBuffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create VertexBuffer.");
			}
		}
	}
}
