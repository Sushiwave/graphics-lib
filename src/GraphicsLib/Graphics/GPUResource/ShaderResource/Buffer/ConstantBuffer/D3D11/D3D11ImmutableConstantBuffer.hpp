#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/IImmutableConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/D3D11/Base/D3D11ConstantBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class ImmutableConstantBuffer
			: public ConstantBuffer,
			  public IImmutableConstantBuffer
		{
		public:
			ImmutableConstantBuffer(const void* pData, unsigned int byteStride);
			virtual ~ImmutableConstantBuffer() = default;
		};
	}
}