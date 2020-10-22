#include <GraphicsLib/System/System.hpp>
#include <Graphics/System/D3D11/D3D11GraphicsSystem.hpp>
#include <Window/System/WINAPI/WINAPIWindowSystem.hpp>
#include <GraphicsLib/API/API.hpp>





namespace cg
{
	std::shared_ptr<IGraphicsSystem> System::m_graphicsLibrary =
#ifdef CONTEXT_D3D11
		std::make_shared<d3d11::GraphicsSystem>();
#endif

	std::shared_ptr<IWindowSystem> System::m_windowManager =
#ifdef CONTEXT_D3D11
		std::make_shared<winapi::WindowSystem>();
#endif





	std::shared_ptr<IScreenUpdater> System::initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& windowTitle)
	{
		return initialize(windowWidth, windowHeight, fullScreen, 1, windowTitle);
	}

	std::shared_ptr<IScreenUpdater> System::initialize(int windowWidth, int windowHeight, bool fullScreen, int MSAASampleCount, const std::string& windowTitle)
	{
		return initialize(windowWidth, windowHeight, fullScreen, MSAASampleCount, windowTitle, "");
	}

	std::shared_ptr<IScreenUpdater> System::initialize(int windowWidth, int windowHeight, bool fullScreen, const std::string& windowTitle, const std::string& iconFilenameICO)
	{
		return initialize(windowWidth, windowHeight, fullScreen, 1, windowTitle, iconFilenameICO);
	}

	std::shared_ptr<IScreenUpdater> System::initialize(int windowWidth, int windowHeight, bool fullScreen, int MSAASampleCount, const std::string& windowTitle, const std::string& iconFilenameICO)
	{
		m_windowManager->initialize(windowWidth, windowHeight, fullScreen, windowTitle, iconFilenameICO);
		const auto& screenUpdater = m_graphicsLibrary->initialize(MSAASampleCount, fullScreen);

		return screenUpdater;
	}

	void System::finalize()
	{
		m_graphicsLibrary->finalize();
		m_windowManager->finalize();
	}

	WindowInfo System::getWindowInfo()
	{
		return m_windowManager->getWindowInfo();
	}
}
