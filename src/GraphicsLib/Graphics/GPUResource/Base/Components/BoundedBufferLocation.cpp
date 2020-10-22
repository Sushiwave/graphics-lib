#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/BoundedBufferLocation.hpp>





namespace cg
{
	BoundedBufferLocation::BoundedBufferLocation(ShaderStage stage, int unit, GPUAccessFlags usage) noexcept
		: stage(stage),
		  unit(unit),
		  usage(usage)
	{
	}
}
