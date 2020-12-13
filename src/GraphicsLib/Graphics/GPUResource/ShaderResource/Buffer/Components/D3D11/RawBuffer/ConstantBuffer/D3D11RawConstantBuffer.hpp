#pragma once
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Base/D3D11RawBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/IShaderResourceMemoryAccessor.hpp>


namespace cg
{
	namespace d3d11
	{
		class RawConstantBuffer
			: public RawBuffer
		{
		private:
			std::shared_ptr<IShaderResourceMemoryAccessor> m_CBV;
		public:
			RawConstantBuffer() noexcept;
			RawConstantBuffer(unsigned int byteStride, const void* pData = nullptr);
			virtual ~RawConstantBuffer() = default;


			std::shared_ptr<IShaderResourceMemoryAccessor> getCBV() const;
		};
	}
}