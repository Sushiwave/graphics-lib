#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>





namespace cg
{
	struct BoundedBufferLocation
	{
		BoundedBufferLocation(ShaderStage stage, int unit, GPUAccessFlags usage) noexcept;

		ShaderStage stage;
		int unit;
		GPUAccessFlags usage;
	};
}