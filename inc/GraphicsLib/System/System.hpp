#pragma once
#include <GraphicsLib/Graphics/System/IGraphicsSystem.hpp>
#include <GraphicsLib/Window/System/IWindowSystem.hpp>





namespace cg
{
	class System
	{
	private:
		static std::shared_ptr<IGraphicsSystem> m_graphicsLibrary;
		static std::shared_ptr<IWindowSystem> m_windowManager;
	private:
		System() = default;
	public:
		virtual ~System() = default;

		[[nodiscard]] static std::shared_ptr<IScreenUpdater> initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& windowTitle, const std::string& iconFilenameICO);
		[[nodiscard]] static std::shared_ptr<IScreenUpdater> initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& windowTitle);
		[[nodiscard]] static std::shared_ptr<IScreenUpdater> initialize(int windowWidth, int windowHeight, bool fullScreen, int MSAASampleCount, const std::string& windowTitle);
		[[nodiscard]] static std::shared_ptr<IScreenUpdater> initialize(int windowWidth, int windowHeight, bool fullScreen, int MSAASampleCount, const std::string& windowTitle, const std::string& iconFilenameICO);

		static void finalize();

		static WindowInfo getWindowInfo();
	};
}
