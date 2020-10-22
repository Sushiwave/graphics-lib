#pragma once
#include <GraphicsLib/Context.hpp>

#include <vector>
#include <string>


namespace cg
{
	enum class ShaderStage
	{
#ifdef CONTEXT_D3D11
		vs,
		hs,
		ds,
		gs,
		ps,
		cs
#endif
	};

	inline const std::vector<ShaderStage> ShaderStageAll =
#ifdef CONTEXT_D3D11
	{ ShaderStage::vs, ShaderStage::hs, ShaderStage::ds, ShaderStage::gs, ShaderStage::ps, ShaderStage::cs };
#endif

	inline const std::vector<std::string> ShaderStageNameAll =
#ifdef CONTEXT_D3D11
	{ "Vertex Shader", "Hull Shader", "Domain Shader", "Geometry Shader", "Pixel Shader", "Compute Shader" };
#endif
}