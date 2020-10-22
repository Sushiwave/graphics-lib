#pragma once
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Components/RawBufferType.hpp>

#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/ID/ID.hpp>




namespace cg
{
	namespace d3d11
	{
		class RawBuffer
		{
		private:
			ID m_id;

			unsigned int m_byteWidth;
			unsigned int m_byteStride;
			unsigned int m_elementCount;

			CPUAccessFlags m_cpuAccessFlags;
			GPUAccessFlags m_gpuAccessFlags;
		protected:
			cpp::com_ptr<ID3D11Buffer> m_buffer;
			RawBufferType m_bufferType;
		public:
			RawBuffer() noexcept;
			RawBuffer(const RawBufferType bufferType, unsigned int elementCount, unsigned int byteStride, GPUAccessFlags gpuAccessFalgs, CPUAccessFlags cpuAccessFlags, const void* pData = nullptr);
			virtual ~RawBuffer() = default;

			

			void copy(const RawBuffer src);
			void update(const void* pData);
			void read(void* result);



			unsigned int getByteWidth() const;
			unsigned int getByteStride() const;
			unsigned int getElementCount() const;
		};
	}
}
