
#include <GraphicsLib/Graphics/RenderPipeline/RasterizationBasedRenderPipeline.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/RasterizerState.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/AlphaBlendState.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTesterState/DepthStencilTesterState.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/RenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/Shader.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/MainGPUStateRecorder.hpp>





namespace cg
{
	auto releaseUnnecessaryBufferFromPipeline = [](GPUState& newState)
	{
		auto state = GPUStateViewer::view();

		for (auto stage : ShaderStageAll)
		{
			if (newState.shader(stage).isEmpty)
			{
				if (state.shader(stage).isEmpty == false)
				{
					Shader::release(stage);
				}
			}
		}
	};





	void RasterizationBasedRenderPipeline::renderDefault(const Scene& scene, bool drawSceneObjects, const AdditionalSetCallScene& additionalSetCall, const AdditionalDrawCall& additionalDrawCall)
	{
		renderDefault(scene, scene.camera, drawSceneObjects, additionalSetCall, additionalDrawCall);
	}

	void RasterizationBasedRenderPipeline::renderDefault(const Scene& scene, const Camera& customCamera, bool drawSceneObjects, const AdditionalSetCallScene& additionalSetCall, const AdditionalDrawCall& additionalDrawCall)
	{
		using CBLocation = std::tuple<ShaderStage, int>;
		const auto& cbLocation = [&](ShaderResourceType resourceType, const std::string& bufferName)
		{
			std::vector<CBLocation> locations;

			for (const auto pair : m_dictOfShadersSetInPipeline)
			{
				const auto shader = pair.second;
				const auto& locationDict = shader->getResourceLocationDict();
				if (locationDict.at(resourceType).count(bufferName) == 0) { continue; }

				locations.emplace_back(CBLocation(shader->getShaderStage(), locationDict.at(resourceType).at(bufferName)));
			}

			return locations;
		};
		const auto& materialLocations  = cbLocation(ShaderResourceType::ConstantBuffer, "Material");
		const auto& transformLocations = cbLocation(ShaderResourceType::ConstantBuffer, "Transform");
		const auto& lightLocations     = cbLocation(ShaderResourceType::ConstantBuffer, "Light");

		using TextureLocation = std::tuple<std::string, ShaderStage, int>;
		std::vector<TextureLocation> materialTexLocations;
		for (const auto pair : m_dictOfShadersSetInPipeline)
		{
			const auto shader = pair.second;
			const auto texLocationDict = shader->getResourceLocationDict().at(ShaderResourceType::Texture);
			const auto stage = shader->getShaderStage();

			for (auto pair : texLocationDict)
			{
				const auto& texName = pair.first;
				const auto& texLocation = pair.second;
				materialTexLocations.emplace_back(TextureLocation(texName, stage, texLocation));
			}
		}





		static const std::string recordingThreadName = ID().get();
		MainGPUStateRecorder::createNewRecordingThread(recordingThreadName);


		if (m_rasterizerState)         { m_rasterizerState->set();         }
		if (m_alphaBlendState)       { m_alphaBlendState->set();       }
		if (m_depthStencilTesterState) { m_depthStencilTesterState->set(); }
		for (auto pair : m_dictOfShadersSetInPipeline)
		{
			const auto shader = pair.second;
			shader->set();
		}
		if (m_materialConstantBuffer)
		{
			for (const auto& materialLocation : materialLocations)
			{
				m_materialConstantBuffer->set(std::get<0>(materialLocation), std::get<1>(materialLocation));
			}
		}
		if (m_transformConstantBuffer)
		{
			for (const auto& transformLocation : transformLocations)
			{
				m_transformConstantBuffer->set(std::get<0>(transformLocation), std::get<1>(transformLocation));
			}
		}
		if (m_lightConstantBuffer)
		{
			m_lightConstantBuffer->update(scene);
			for (const auto& lightLocation : lightLocations)
			{
				m_lightConstantBuffer->set(std::get<0>(lightLocation), std::get<1>(lightLocation));
			}
		}
		additionalSetCall(scene);


		auto newGPUState = MainGPUStateRecorder::getGPUState(recordingThreadName);
		releaseUnnecessaryBufferFromPipeline(newGPUState);
		MainGPUStateRecorder::removeRecordingThread(recordingThreadName);





		auto gpuStateViewer = GPUStateViewer::view();

		if (drawSceneObjects)
		{
			for (auto targetRenderingGroupName : m_targetRenderingGroupNameList)
			{
				scene.draw(targetRenderingGroupName,
					[&](const std::shared_ptr<DrawableObject> object)
					{
						if (object->geometry.empty()) { return; }
					
						const auto transform = object->transform;
						if (auto shape = object->geometry.shape)
						{
							m_transformConstantBuffer->update(scene, *transform, *shape, customCamera);
						}
						else
						{
							m_transformConstantBuffer->update(scene, *transform, cg::Shape(), customCamera);
						}
					},
					[&](const Geometry::Part& part)
					{
						for (const auto& materialLocation : materialLocations)
						{
							m_materialConstantBuffer->update(std::get<0>(materialLocation), part.material);
						}
						for (const auto& materialTexLocation : materialTexLocations)
						{
							const auto& name = std::get<0>(materialTexLocation);
							const auto type = std::get<1>(materialTexLocation);
							const auto unit = std::get<2>(materialTexLocation);

							if (gpuStateViewer.shader(type).resource(ShaderResourceType::Texture, GPUAccessType::R).unit(unit).isEmpty == false) { continue; }

							auto tex = part.material.getTexture(name);
							if (tex == nullptr) { continue; }

							tex->set(type, unit, GPUAccessType::R);
						}
					});
			}
		}
		else
		{
			m_transformConstantBuffer->update(scene, cg::Transform(), cg::Shape(), scene.camera);
		}

		additionalDrawCall();
	}
	std::shared_ptr<IDepthStencilBuffer> RasterizationBasedRenderPipeline::accessToDepthStencilBuffer() const
	{
		return m_depthStencilBuffer;
	}
	std::shared_ptr<IRasterizerState> RasterizationBasedRenderPipeline::accessToRasterizerState() const
	{
		return m_rasterizerState;
	}
	std::shared_ptr<IAlphaBlendState> RasterizationBasedRenderPipeline::accessToAlphaBlendState() const
	{
		return m_alphaBlendState;
	}
	RasterizationBasedRenderPipeline::ShaderDict RasterizationBasedRenderPipeline::getDictOfShadersSetInPipeline() const
	{
		return m_dictOfShadersSetInPipeline;
	}
	void RasterizationBasedRenderPipeline::renderDefault(AdditionalSetCall additionalSetCall, AdditionalDrawCall additionalDrawCall)
	{
		static const std::string recordingThreadName = ID().get();
		MainGPUStateRecorder::createNewRecordingThread(recordingThreadName);

		if (m_rasterizerState)         { m_rasterizerState->set();         }
		if (m_alphaBlendState)       { m_alphaBlendState->set();       }
		if (m_depthStencilTesterState) { m_depthStencilTesterState->set(); }
		for (auto pair : m_dictOfShadersSetInPipeline)
		{
			const auto shader = pair.second;
			shader->set();
		}

		additionalSetCall();

		auto newGPUState = MainGPUStateRecorder::getGPUState(recordingThreadName);
		releaseUnnecessaryBufferFromPipeline(newGPUState);
		MainGPUStateRecorder::removeRecordingThread(recordingThreadName);

		additionalDrawCall();
	}
	RasterizationBasedRenderPipeline::RasterizationBasedRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<IDepthStencilTesterState> depthStencilTesterState, std::shared_ptr<IRasterizerState> rasterizerState, std::shared_ptr<IAlphaBlendState> alphaBlendState, const ShaderDict& shaders, std::shared_ptr<MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<LightConstantBuffer> lightConstantBuffer) noexcept
		: RenderPipeline(name),
		  m_targetRenderingGroupNameList(targetRenderingGroupNameList),
		  m_dictOfShadersSetInPipeline(shaders),
		  m_materialConstantBuffer(materialConstantBuffer),
		  m_transformConstantBuffer(transformConstantBuffer),
		  m_lightConstantBuffer(lightConstantBuffer),
		  m_depthStencilTesterState(depthStencilTesterState),
		  m_depthStencilBuffer(depthStencilBuffer),
		  m_rasterizerState(rasterizerState),
		  m_alphaBlendState(alphaBlendState)
	{
	}
}
