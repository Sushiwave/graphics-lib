#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IIndexBuffer
		: virtual public IGPUResource
	{
	public:
		[[nodiscard]] virtual int getIndexCount() const = 0;

		virtual void set() = 0;
	};
}