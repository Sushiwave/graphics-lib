#pragma once
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Base/Components/PrimitiveTopology.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IVertexBuffer
		: virtual public IGPUResource
	{
	public:
		[[nodiscard]] virtual int getVertexCount() const = 0;

		virtual void set(PrimitiveTopology topology) = 0;
	};
}