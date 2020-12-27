#pragma once
#include <GraphicsLib/Graphics/RenderPipeline/RasterizationBasedRenderPipeline.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>





namespace cg
{
	class RenderPipelineSRT
		: public RasterizationBasedRenderPipeline
	{
	private:
		std::shared_ptr<IRenderTarget> m_renderTarget;
	protected:
		[[nodiscard]] std::shared_ptr<IRenderTarget> accessToRenderTarget() const;
	public:
		RenderPipelineSRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IRenderTarget> renderTarget, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, std::shared_ptr<IRasterizerState> rasterizer, std::shared_ptr<IAlphaBlender> alphaBlender, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept;
		virtual ~RenderPipelineSRT() = default;
	};
}
