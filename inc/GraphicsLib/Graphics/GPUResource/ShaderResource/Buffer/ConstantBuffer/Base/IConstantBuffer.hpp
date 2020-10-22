#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>





namespace cg
{
	class IConstantBuffer
		: public virtual IShaderResource
	{
	public:
		virtual void set(ShaderStage stage, int unit) = 0;
		virtual void read(void* result) = 0;
	};
}
