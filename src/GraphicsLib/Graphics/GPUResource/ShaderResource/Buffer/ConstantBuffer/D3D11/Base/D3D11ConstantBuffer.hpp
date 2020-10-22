#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/ConstantBuffer/D3D11RawConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/Base/IConstantBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class ConstantBuffer
			: public ShaderResource,
			  public virtual IConstantBuffer
		{
		protected:
			RawConstantBuffer m_buffer;
		public:
			ConstantBuffer(unsigned int byteStride, const void* pData = nullptr);
			virtual ~ConstantBuffer() = default;

			void set(ShaderStage stage, int unit) override;
			void read(void* result) override;

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;
		};
	}
}