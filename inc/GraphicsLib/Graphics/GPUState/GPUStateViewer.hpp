#pragma once
#include <GraphicsLib/Graphics/GPUState/GPUState.hpp>





namespace cg
{
	class GPUStateViewer
	{
	public:
		[[nodiscard]] static GPUState view() noexcept;
	};
}
