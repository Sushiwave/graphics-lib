#include "D3D11ImmutableConstantBuffer.hpp"





namespace cg
{
	namespace d3d11
	{
		ImmutableConstantBuffer::ImmutableConstantBuffer(const void* pData, unsigned int byteStride)
			: ConstantBuffer(byteStride, pData)
		{
		}
	}
}
