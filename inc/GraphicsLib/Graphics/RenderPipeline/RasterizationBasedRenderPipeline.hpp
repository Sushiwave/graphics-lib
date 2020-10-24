#pragma once
#include <GraphicsLib/Graphics/RenderPipeline/RenderPipeline.hpp>
#include <GraphicsLib/Graphics/Scene/Scene.hpp>
#include <GraphicsLib/Graphics/GPUResource/Rasterizer/IRasterizer.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/IDepthStencilTester.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/IAlphaBlender.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/PixelShader/IPixelShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/HullShader/IHullShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/DomainShader/IDomainShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/GeometryShader/IGeometryShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/VertexShader/IVertexShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/LightConstantBuffer/LightConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/TransformConstantBuffer.hpp>

#include <memory>
#include <list>




namespace cg
{
	class RasterizationBasedRenderPipeline
		: public RenderPipeline
	{
	public:
		using AdditionalSetCall = std::function<void()>;
		using AdditionalSetCallScene = std::function<void(const Scene&)>;
		using AdditionalDrawCall = std::function<void()>;
		using ShaderDict = std::unordered_map<ShaderStage, std::shared_ptr<IShader>>;
		using TargetRenderingGroupNameList = std::list<std::string>;
	private:
		ShaderDict m_dictOfShadersSetInPipeline;
		TargetRenderingGroupNameList m_targetRenderingGroupNameList;

		std::shared_ptr<MaterialConstantBuffer>  m_materialConstantBuffer;
		std::shared_ptr<TransformConstantBuffer> m_transformConstantBuffer;
		std::shared_ptr<LightConstantBuffer>     m_lightConstantBuffer;

		std::shared_ptr<IDepthStencilTester> m_depthStencilTester;
	protected:
		std::shared_ptr<IDepthStencilBuffer> m_depthStencilBuffer;

		std::shared_ptr<IRasterizer>         m_rasterizer;
		std::shared_ptr<IAlphaBlender>       m_alphaBlender;
	protected:
		[[nodiscard]] ShaderDict getDictOfShadersSetInPipeline() const;

		void renderDefault();
		void renderDefault(AdditionalSetCall additionalSetCall, AdditionalDrawCall additionalDrawCall);

		void renderDefault(const Scene& scene);
		void renderDefault(const Scene& scene, const Camera& customCamera);
		void renderDefault(const Scene& scene, AdditionalSetCallScene additionalSetCall, AdditionalDrawCall additionalDrawCall);
		void renderDefault(const Scene& scene, const Camera& customCamera, AdditionalSetCallScene additionalSetCall, AdditionalDrawCall additionalDrawCall);
	public:
		RasterizationBasedRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroup, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer, std::shared_ptr<IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept;
		virtual ~RasterizationBasedRenderPipeline() = default;
	};
}
