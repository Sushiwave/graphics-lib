#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/GPUResource/IndexBuffer/IIndexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

struct ID3D11Buffer;





namespace cg
{
	namespace d3d11
	{
		class IndexBuffer
			: public IIndexBuffer,
			  public GPUResource
		{
		private:
			cpp::com_ptr<ID3D11Buffer> m_indexBuffer;
			int m_indexCount;
			bool m_isByteStride32bit;
		public:
			IndexBuffer() = default;
			IndexBuffer(const void* indices, unsigned int indexCount, unsigned int byteStride);
			virtual ~IndexBuffer() = default;

			[[nodiscard]] int getIndexCount() const noexcept override;

			void set() override;
		};
	}
}