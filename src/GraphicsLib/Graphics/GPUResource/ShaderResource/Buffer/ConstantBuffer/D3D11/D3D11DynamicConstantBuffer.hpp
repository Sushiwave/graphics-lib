#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/IDynamicConstantBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/D3D11/Base/D3D11ConstantBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class DynamicConstantBuffer
			: public ConstantBuffer,
			  public IDynamicConstantBuffer
		{
		public:
			DynamicConstantBuffer(unsigned int byteStride, const void* pData = nullptr);
			virtual ~DynamicConstantBuffer() = default;



			void update(const Constant& constant) override;
			void copy(std::shared_ptr<IConstantBuffer> src);
		};
	}
}