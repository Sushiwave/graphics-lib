#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/Base/IStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Base/D3D11RawBufferEX.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>





namespace cg
{
	namespace d3d11
	{
		class StructuredBuffer
			: public ShaderResource,
			  public virtual IStructuredBuffer
		{
		protected:
			RawBufferEX m_buffer;
		public:
			StructuredBuffer(unsigned int byteStride, unsigned int elementCount, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, const void* pData = nullptr, bool isByteAddressBuffer = false);
			virtual ~StructuredBuffer() = default;

			void read(void* result) override;

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;

			[[nodiscard]] RawBufferEX getRawBuffer() const;
		};
	}
}
