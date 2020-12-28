#pragma once
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/System/Components/IGraphicsSystemComponents.hpp>





namespace cg
{
	class MainRenderTarget
	{
	public:
		static MainRenderTarget shared;
	private:
		std::shared_ptr<IRenderTarget> m_renderTarget;
	private:
		MainRenderTarget() = default;
	public:
		virtual ~MainRenderTarget() = default;

		void initialize(std::shared_ptr<IGraphicsSystemComponents> components);

		[[nodiscard]] std::shared_ptr<IRenderTarget> get() const noexcept;
	};
}
