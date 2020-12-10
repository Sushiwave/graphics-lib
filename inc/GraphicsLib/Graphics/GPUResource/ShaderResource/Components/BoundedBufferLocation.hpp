#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessType.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>





namespace cg
{
	struct BoundedBufferLocation
	{
		BoundedBufferLocation(ShaderStage stage, int unit, GPUAccessType usage) noexcept;

		ShaderStage stage;
		int unit;
		GPUAccessType usage;
	};
}