#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>





namespace cg
{
	class ShaderResource
		: public GPUResource,
		  public virtual IShaderResource
	{
	public:
		ShaderResource() = default;
		virtual ~ShaderResource() = default;


		[[nodiscard]] virtual BoundedBufferLocationList getBoundedBufferLocationList() const = 0;
	};
}