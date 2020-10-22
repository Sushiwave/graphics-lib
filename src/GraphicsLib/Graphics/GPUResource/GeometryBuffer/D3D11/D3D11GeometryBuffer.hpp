#pragma once
#include <GraphicsLib/Graphics/GPUResource/VertexBuffer/IVertexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/IndexBuffer/IIndexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/GeometryBuffer/IGeometryBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <memory>





namespace cg
{
	namespace d3d11
	{
		class GeometryBuffer
			: public IGeometryBuffer,
			  public GPUResource
		{
		private:
			std::shared_ptr<IVertexBuffer> m_vertexBuffer;
			std::shared_ptr<IIndexBuffer> m_indexBuffer;
		public:
			GeometryBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer, std::shared_ptr<IIndexBuffer> indexBuffer);
			virtual ~GeometryBuffer() = default;

			void draw(PrimitiveTopology topology, int instanceCount) const override;
		};
	}
}
