#include <GraphicsLib/Graphics/RenderPipeline/RenderPipelineMRT.hpp>





namespace cg
{
	RenderPipelineMRT::RenderPipelineMRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IMultipleRenderTargets> mrt, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept
		: RasterizationBasedRenderPipeline(name, targetRenderingGroupNameList, depthStencilBuffer, materialConstantBuffer, transformConstantBuffer, lightConstantBuffer, depthStencilTester, shaders),
		  m_multipleRenderTargets(mrt)
	{
	}
}
