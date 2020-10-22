#include <GraphicsLib/Graphics/RenderPipeline/RenderPipelineSRT.hpp>





namespace cg
{
	RenderPipelineSRT::RenderPipelineSRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IRenderTarget> renderTarget, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept
		: RasterizationBasedRenderPipeline(name, targetRenderingGroupNameList, depthStencilBuffer, materialConstantBuffer, transformConstantBuffer, lightConstantBuffer, depthStencilTester, shaders),
		  m_renderTarget(renderTarget)
	{
	}
}
