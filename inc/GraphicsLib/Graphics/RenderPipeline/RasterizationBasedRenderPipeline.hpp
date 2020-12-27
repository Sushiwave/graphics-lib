#pragma once
#include <GraphicsLib/Graphics/RenderPipeline/RenderPipeline.hpp>
#include <GraphicsLib/Graphics/Scene/Scene.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/IRasterizerState.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTesterState/IDepthStencilTesterState.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/IAlphaBlendState.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/PixelShader/IPixelShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/HullShader/IHullShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/DomainShader/IDomainShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/GeometryShader/IGeometryShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/VertexShader/IVertexShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/LightConstantBuffer/LightConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/TransformConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/MaterialConstantBuffer/MaterialConstantBuffer.hpp>

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

		std::shared_ptr<IDepthStencilTesterState> m_depthStencilTester;
		std::shared_ptr<IDepthStencilBuffer> m_depthStencilBuffer;
		
		std::shared_ptr<IRasterizerState>   m_rasterizer;
		std::shared_ptr<IAlphaBlendState> m_alphaBlender;
	protected:
		[[nodiscard]] std::shared_ptr<IDepthStencilBuffer> accessToDepthStencilBuffer() const;
		[[nodiscard]] std::shared_ptr<IRasterizerState> accessToRasterizerState() const;
		[[nodiscard]] std::shared_ptr<IAlphaBlendState> accessToAlphaBlendState() const;
	protected:
		[[nodiscard]] ShaderDict getDictOfShadersSetInPipeline() const;

		void renderDefault(AdditionalSetCall additionalSetCall = []() {}, AdditionalDrawCall additionalDrawCall = []() {});

		void renderDefault(const Scene& scene, bool drawSceneObjects, const AdditionalSetCallScene& additionalSetCall = [](const Scene&){}, const AdditionalDrawCall& additionalDrawCall = [](){});
		void renderDefault(const Scene& scene, const Camera& customCamera, bool drawSceneObjects, const AdditionalSetCallScene& additionalSetCall = [](const Scene&){}, const AdditionalDrawCall& additionalDrawCall = [](){});
	public:
		RasterizationBasedRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTesterState> depthStencilTester, std::shared_ptr<IRasterizerState> rasterizer, std::shared_ptr<IAlphaBlendState> alphaBlender, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept;
		virtual ~RasterizationBasedRenderPipeline() = default;
	};
}
