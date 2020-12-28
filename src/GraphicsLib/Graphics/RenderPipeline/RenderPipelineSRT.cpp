#include <GraphicsLib/Graphics/RenderPipeline/RenderPipelineSRT.hpp>





namespace cg
{
	std::shared_ptr<IRenderTarget> RenderPipelineSRT::accessToRenderTarget() const
	{
		return m_renderTarget;
	}
	RenderPipelineSRT::RenderPipelineSRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IRenderTarget> renderTarget, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTesterState> depthStencilTesterState, std::shared_ptr<IRasterizerState> rasterizerState, std::shared_ptr<IAlphaBlendState> alphaBlendState, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept
		: RasterizationBasedRenderPipeline(name, targetRenderingGroupNameList, depthStencilBuffer, depthStencilTesterState, rasterizerState, alphaBlendState, shaders, materialConstantBuffer, transformConstantBuffer, lightConstantBuffer),
		  m_renderTarget(renderTarget)
	{
	}
}
