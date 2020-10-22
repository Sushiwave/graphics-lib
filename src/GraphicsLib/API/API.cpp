#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/Context.hpp>
#include <Graphics/API/D3D11/D3D11GraphicsAPI.hpp>
#include <Window/API/WINAPI/WINAPIWindowAPI.hpp>




namespace cg
{
	const auto g_graphics =
#ifdef CONTEXT_D3D11
		std::make_shared<d3d11::GraphicsAPI>();
#endif

	const auto g_window =
#ifdef CONTEXT_D3D11
		std::make_shared<winapi::WindowAPI>();
#endif

	API API::shared = API(g_graphics, g_window);





	API::API(std::shared_ptr<IGraphicsAPI> graphics, std::shared_ptr<IWindowAPI> window)
		: m_graphics(graphics),
		  m_window(window)
	{
	}





	std::shared_ptr<IGraphicsAPI> API::graphics() noexcept
	{
		return m_graphics;
	}
	std::shared_ptr<IWindowAPI> API::window() noexcept
	{
		return m_window;
	}
}
