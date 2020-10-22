#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/ShaderResourceType.hpp>

#include <unordered_map>





namespace cg
{
	using ShaderResourceLocationDict = std::unordered_map<ShaderResourceType, std::unordered_map<std::string, int>>;
}
