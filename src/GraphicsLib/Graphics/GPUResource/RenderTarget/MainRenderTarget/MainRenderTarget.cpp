#include <GraphicsLib/Graphics/GPUResource/RenderTarget/MainRenderTarget/MainRenderTarget.hpp>
#include <Graphics/GPUResource/RenderTarget/D3D11/D3D11RenderTarget.hpp>
#include <Graphics/System/D3D11/Components/D3D11GraphicsSystemComponents.hpp>





namespace cg
{
	MainRenderTarget MainRenderTarget::shared;





	void MainRenderTarget::initialize(std::shared_ptr<IGraphicsSystemComponents> components)
	{
		const auto& graphicsLibraryComponents
#ifdef CONTEXT_D3D11
			= std::static_pointer_cast<d3d11::GraphicsSystemComponents>(components);
#endif

		m_renderTarget
#ifdef CONTEXT_D3D11
			= std::make_shared<d3d11::RenderTarget>(graphicsLibraryComponents->getBackBuffer(), 0);
#endif
	}
	std::shared_ptr<IRenderTarget> MainRenderTarget::get() const noexcept
	{
		return m_renderTarget;
	}
}