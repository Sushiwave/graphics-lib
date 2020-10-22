#pragma once
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Base/D3D11RawBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/IShaderResourceMemoryAccessor.hpp>





namespace cg
{
	namespace d3d11
	{
		class RawBufferEX
			: public RawBuffer
		{
		private:
			std::shared_ptr<IShaderResourceMemoryAccessor> m_SRV;
			std::shared_ptr<IShaderResourceMemoryAccessor> m_UAV;
		public:
			RawBufferEX(const RawBufferType bufferType, unsigned int elementCount, unsigned int byteStride, GPUAccessFlags gpuAccessFlags, CPUAccessFlags cpuAccessFlags, const ID& memoryAccessorID, const void* pData = nullptr);
			virtual ~RawBufferEX() = default;

			[[nodiscard]] std::shared_ptr<IShaderResourceMemoryAccessor> getSRV() const noexcept;
			[[nodiscard]] std::shared_ptr<IShaderResourceMemoryAccessor> getUAV() const noexcept;
		};
	}
}