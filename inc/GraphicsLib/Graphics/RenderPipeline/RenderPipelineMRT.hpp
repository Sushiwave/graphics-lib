#pragma once
#include <GraphicsLib/Graphics/RenderPipeline/RasterizationBasedRenderPipeline.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTarget/IMultipleRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/GBuffer/GBuffer.hpp>

#include <string>





namespace cg
{
	class RenderPipelineMRT
		: public RasterizationBasedRenderPipeline
	{
	protected:
		const std::shared_ptr<IMultipleRenderTarget> m_multipleRenderTarget;

		GBuffer m_GBuffer;
	public:
		RenderPipelineMRT(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IMultipleRenderTarget> mrt, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept;
		virtual ~RenderPipelineMRT() = default;

		GBuffer getGBuffer() const;
	};
}
