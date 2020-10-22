#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IDynamicStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/Base/D3D11StructuredBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class DynamicStructuredBuffer
			: public StructuredBuffer,
			  public IDynamicStructuredBuffer
		{
		public:
			DynamicStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr, bool isByteAddressBuffer = false);
			virtual ~DynamicStructuredBuffer() = default;

			void update(const Constant& constant) override;
			void set(ShaderStage stage, int unit) override;
			void copy(std::shared_ptr<IStructuredBuffer> src);
		};
	}
}