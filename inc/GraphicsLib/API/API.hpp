#pragma once
#include <GraphicsLib/Graphics/API/IGraphicsAPI.hpp>
#include <GraphicsLib/Window/API/IWindowAPI.hpp>





namespace cg
{
	class API
	{
	private:
		std::shared_ptr<IGraphicsAPI> m_graphics;
		std::shared_ptr<IWindowAPI> m_window;
	public:
		static API shared;
	private:
		API(std::shared_ptr<IGraphicsAPI> graphics, std::shared_ptr<IWindowAPI> window);
	public:
		virtual ~API() = default;

		[[nodiscard]] std::shared_ptr<IGraphicsAPI> graphics() noexcept;
		[[nodiscard]] std::shared_ptr<IWindowAPI> window() noexcept;
	};
}