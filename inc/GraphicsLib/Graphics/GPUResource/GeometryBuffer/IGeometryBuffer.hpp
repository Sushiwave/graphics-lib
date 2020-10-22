#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>
#include <GraphicsLib/Graphics/Shape/Base/Components/PrimitiveTopology.hpp>





namespace cg
{
	class IGeometryBuffer
		: virtual public IGPUResource
	{
	public:
		virtual void draw(PrimitiveTopology topology, int instanceCount) const = 0;
	};
}
