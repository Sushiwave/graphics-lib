#pragma once
#include <GraphicsLib/Graphics/RenderPipeline/RasterizationBasedRenderPipeline.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/IMultipleRenderTargets.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>

#include <string>





namespace cg
{
	class RenderPipelineMRT
		: public RasterizationBasedRenderPipeline
	{
	private:
		std::shared_ptr<IMultipleRenderTargets> m_multipleRenderTargets;
	protected:
		[[nodiscard]] std::shared_ptr<IMultipleRenderTargets> accessToMultipleRenderTargets() const;
	public:
		RenderPipelineMRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IMultipleRenderTargets> mrt, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTesterState> depthStencilTesterState, std::shared_ptr<IRasterizerState> rasterizerState, std::shared_ptr<IAlphaBlendState> alphaBlendState, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept;
		virtual ~RenderPipelineMRT() = default;
	};
}
