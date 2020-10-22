#pragma once
#include <GraphicsLib/Graphics/Scene/Scene.hpp>

#include <string>





namespace cg
{
	class RenderPipeline
	{
	private:
		std::string m_name;
	public:
		RenderPipeline(const std::string& name) noexcept;
		virtual ~RenderPipeline() = default;

		[[nodiscard]] std::string name() const noexcept;

		virtual void render() = 0;
		virtual void render(const Scene& scene) = 0;
	};
}