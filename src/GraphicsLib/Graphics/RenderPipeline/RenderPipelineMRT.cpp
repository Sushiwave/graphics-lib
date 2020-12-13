#include <GraphicsLib/Graphics/RenderPipeline/RenderPipelineMRT.hpp>





namespace cg
{
	std::shared_ptr<IMultipleRenderTargets> RenderPipelineMRT::accessToMultipleRenderTargets() const
	{
		return m_multipleRenderTargets;
	}
	RenderPipelineMRT::RenderPipelineMRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IMultipleRenderTargets> mrt, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, std::shared_ptr<IRasterizer> rasterizer, std::shared_ptr<IAlphaBlender> alphaBlender, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept
		: RasterizationBasedRenderPipeline(name, targetRenderingGroupNameList, depthStencilBuffer, depthStencilTester, rasterizer, alphaBlender, shaders, materialConstantBuffer, transformConstantBuffer, lightConstantBuffer),
		  m_multipleRenderTargets(mrt)
	{
	}
}
