#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IDefaultStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/Base/D3D11StructuredBuffer.hpp>




namespace cg
{
	namespace d3d11
	{
		class DefaultStructuredBuffer
			: public StructuredBuffer,
			  public IDefaultStructuredBuffer
		{
		public:
			DefaultStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr, bool isByteAddressBuffer = false);
			virtual ~DefaultStructuredBuffer() = default;

			void update(const Constant& constant) override;
			void set(ShaderStage stage, int unit, GPUAccessType usage) override;
			void copy(std::shared_ptr<IStructuredBuffer> src);
		};
	}
}
