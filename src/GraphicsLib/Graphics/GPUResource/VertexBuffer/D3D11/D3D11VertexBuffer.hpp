#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Base/Components/PrimitiveTopology.hpp>
#include <GraphicsLib/Graphics/GPUResource/VertexBuffer/IVertexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>


struct ID3D11Buffer;





namespace cg
{
	namespace d3d11
	{
		class VertexBuffer
			: public IVertexBuffer,
			  public GPUResource
		{
		private:
			cpp::com_ptr<ID3D11Buffer> m_vertexBuffer;
			int m_vertexCount;
			UINT m_byteStride;
		public:
			VertexBuffer() noexcept;
			VertexBuffer(const void* vertices, unsigned int vertexCount, unsigned int byteStride);
			virtual ~VertexBuffer() = default;

			[[nodiscard]] int getVertexCount() const noexcept override;

			void set(PrimitiveTopology topology) override;
		};
	}
}
