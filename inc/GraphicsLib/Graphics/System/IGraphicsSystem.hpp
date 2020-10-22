#pragma once
#include <GraphicsLib/Graphics/System/Components/IScreenUpdater.hpp>

#include <memory>





namespace cg
{
	class IGraphicsSystem
	{
	public:
		[[nodiscard]] virtual std::shared_ptr<IScreenUpdater> initialize(int MSAASampleCount, bool fullScreen) = 0;
		virtual void finalize() = 0;
	};
}