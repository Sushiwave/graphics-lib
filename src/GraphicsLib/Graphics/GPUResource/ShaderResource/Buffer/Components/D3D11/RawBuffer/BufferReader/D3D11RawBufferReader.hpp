#pragma once
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Base/D3D11RawBuffer.hpp>





namespace cg
{
	namespace d3d11
	{
		class RawBufferReader
			: public RawBuffer
		{
		public:
			RawBufferReader() = default;
			RawBufferReader(unsigned int byteWidth, unsigned int byteStride);
			virtual ~RawBufferReader() = default;

			void read(ID3D11Buffer* src, void* result);
		};
	}
}
