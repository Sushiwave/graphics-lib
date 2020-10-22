#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IImmutableStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/Base/D3D11StructuredBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class ImmutableStructuredBuffer
			: public StructuredBuffer,
			  public IImmutableStructuredBuffer
		{
		public:
			ImmutableStructuredBuffer(const void* pData, unsigned int byteStride, unsigned int elementCount, bool isByteAddressBuffer = false);
			virtual ~ImmutableStructuredBuffer() = default;

			void set(ShaderStage stage, int unit) override;
		};
	}
}