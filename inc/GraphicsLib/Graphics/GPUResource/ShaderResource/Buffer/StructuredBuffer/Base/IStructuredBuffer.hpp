#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>





namespace cg
{
	class IStructuredBuffer
		: public virtual IShaderResource
	{
		virtual void read(void* result) = 0;
	};
}