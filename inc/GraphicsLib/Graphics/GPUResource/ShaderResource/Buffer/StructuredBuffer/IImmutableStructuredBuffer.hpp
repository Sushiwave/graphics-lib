#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/Base/IStructuredBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>





namespace cg
{
	class IImmutableStructuredBuffer
		: public virtual IStructuredBuffer
	{
		virtual void set(ShaderStage stage, int unit) = 0;
	};
}
