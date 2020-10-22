#pragma once




namespace cg
{
	enum class RawBufferType
	{
		StructuredBuffer,
		ByteAddressBuffer,
		ConstantBuffer,
		VertexBuffer,
		IndexBuffer,
		Reader,
	};
}