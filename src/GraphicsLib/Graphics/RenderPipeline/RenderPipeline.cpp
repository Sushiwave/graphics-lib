#include <GraphicsLib/Graphics/RenderPipeline/RenderPipeline.hpp>





namespace cg
{
	RenderPipeline::RenderPipeline(const std::string& name) noexcept
		: m_name(name)
	{
	}
	std::string RenderPipeline::name() const noexcept
	{
		return m_name;
	}
}
