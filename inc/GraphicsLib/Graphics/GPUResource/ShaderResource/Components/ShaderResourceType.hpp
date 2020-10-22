#pragma once
#include <vector>





namespace cg
{
	enum class ShaderResourceType
	{
		Texture,
		TextureSampler,
		ConstantBuffer,
		StructuredBuffer,
	};

	inline const std::vector<ShaderResourceType> ShaderResourceTypeAll = { ShaderResourceType::Texture, ShaderResourceType::TextureSampler, ShaderResourceType::ConstantBuffer, ShaderResourceType::StructuredBuffer };
}