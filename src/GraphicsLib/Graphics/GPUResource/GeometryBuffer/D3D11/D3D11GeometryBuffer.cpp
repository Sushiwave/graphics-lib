#include <Graphics/GPUResource/GeometryBuffer/D3D11/D3D11GeometryBuffer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>





namespace cg
{
	namespace d3d11
	{
		GeometryBuffer::GeometryBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer, std::shared_ptr<IIndexBuffer> indexBuffer)
			: m_vertexBuffer(vertexBuffer),
			  m_indexBuffer(indexBuffer)
		{
		}

		void GeometryBuffer::draw(PrimitiveTopology topology, int instanceCount) const
		{
			m_vertexBuffer->set(topology);

			if (m_indexBuffer)
			{
				m_indexBuffer->set();

				if (0 < instanceCount)
				{
					Device::getDeviceContext()->DrawIndexedInstanced(m_indexBuffer->getIndexCount(), instanceCount, 0, 0, 0);
				}
				else
				{
					Device::getDeviceContext()->DrawIndexed(m_indexBuffer->getIndexCount(), 0, 0);
				}
			}
			else
			{
				if (0 < instanceCount)
				{
					Device::getDeviceContext()->DrawInstanced(m_vertexBuffer->getVertexCount(), instanceCount, 0, 0);
				}
				else
				{
					Device::getDeviceContext()->Draw(m_vertexBuffer->getVertexCount(), 0);
				}
			}
		}
	}
}
