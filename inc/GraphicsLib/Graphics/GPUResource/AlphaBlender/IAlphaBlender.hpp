#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IAlphaBlender
		: public virtual IGPUResource
	{
	public:
		virtual void set() = 0;
	};
}