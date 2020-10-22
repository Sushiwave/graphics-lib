#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/BoundedBufferLocationList.hpp>





namespace cg
{
	class IShaderResource
		: public virtual IGPUResource
	{
	public:
		[[nodiscard]] virtual BoundedBufferLocationList getBoundedBufferLocationList() const = 0;
	};
}
