#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IAlphaBlendState
		: public virtual IGPUResource
	{
	public:
		virtual void set() = 0;
	};
}