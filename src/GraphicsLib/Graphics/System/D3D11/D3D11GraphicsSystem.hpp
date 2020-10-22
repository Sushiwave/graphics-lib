#pragma once
#include <GraphicsLib/Graphics/System/IGraphicsSystem.hpp>





namespace cg
{
	namespace d3d11
	{
		class GraphicsSystem
			: public IGraphicsSystem
		{
		public:
			virtual ~GraphicsSystem() = default;

			[[nodiscard]] std::shared_ptr<IScreenUpdater> initialize(int MSAASampleCount, bool fullScreen) override;
			void finalize() override;
		};
	}
}
