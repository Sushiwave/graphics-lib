#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>

#include <memory>





namespace cg
{
	class ITextureSampler
		: public virtual IShaderResource
	{
	public:
		virtual void set(ShaderStage stage, int unit) = 0;
	};
}