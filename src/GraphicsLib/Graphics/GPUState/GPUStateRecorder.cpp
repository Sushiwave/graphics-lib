#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>





namespace cg
{
	const auto emplace = [](GPUState::StateOfBufferBoundedBySeveralResources& state, std::shared_ptr<cg::ITexture2D> texture)
	{
		if (texture) { state.boundedResourceIDList.emplace_back(texture->getID()); }
	};





	const ID GPUStateRecorder::m_mainRecordingThreadName = ID();

	const GPUStateRecorder GPUStateRecorder::main = []()
	{
		auto recorder = GPUStateRecorder();
		recorder.createNewRecordingThread(m_mainRecordingThreadName.get());
		return recorder;
	}();





	void GPUStateRecorder::rasterizerStateSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.rasterizerState;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::rasterizerStateReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.rasterizerState;
			state.isEmpty = true;
			state.id = ID();
		}
	}

	void GPUStateRecorder::depthStencilTesterStateSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilTesterState;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::depthStencilTesterStateReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilTesterState;
			state.isEmpty = true;
			state.id = ID();
		}
	}

	void GPUStateRecorder::blenderSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.blender;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::blenderReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.blender;
			state.isEmpty = true;
			state.id = ID();
		}
	}

	void GPUStateRecorder::multipleRenderTargetsSet(const cg::IMultipleRenderTargets* multipleRenderTargets) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.renderTarget;
			state.isEmpty = false;
			state.id = multipleRenderTargets->getID();
			state.count = multipleRenderTargets->getRenderTargetCount();
			state.boundedResourceIDList.clear();
			const auto renderingResults = multipleRenderTargets->getAllRenderingResults();
			for (auto renderingResult : renderingResults)
			{
				emplace(state, renderingResult);
			}
		}
	}

	void GPUStateRecorder::renderTargetSet(const cg::IRenderTarget* renderTarget) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.renderTarget;
			state.isEmpty = false;
			state.id = renderTarget->getID();
			state.count = 1;
			state.boundedResourceIDList.clear();
			emplace(state, renderTarget->getRenderingResult());
			emplace(state, renderTarget->getRenderingResultMS());
		}
	}

	void GPUStateRecorder::renderTargetReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.renderTarget;
			state.isEmpty = true;
			state.id = ID();
			state.count = 0;
			state.boundedResourceIDList.clear();
		}
	}

	void GPUStateRecorder::depthStencilBufferSet(const cg::IDepthStencilBuffer* depthStencilBuffer) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilBuffer;
			state.isEmpty = false;
			state.id = depthStencilBuffer->getID();
			state.boundedResourceIDList.clear();
			emplace(state, depthStencilBuffer->getDepthBufferTexture());
			emplace(state, depthStencilBuffer->getDepthBufferTextureMS());
			emplace(state, depthStencilBuffer->getStencilBufferTexture());
			emplace(state, depthStencilBuffer->getStencilBufferTextureMS());
		}
	}

	void GPUStateRecorder::depthStencilBufferReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilBuffer;
			state.isEmpty = true;
			state.id = ID();
			state.boundedResourceIDList.clear();
		}
	}

	void GPUStateRecorder::shaderSet(ShaderStage stage, const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.shader(stage);
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::shaderReleased(ShaderStage stage) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.shader(stage);
			state.isEmpty = true;
			state.id = ID();
		}
	}

	void GPUStateRecorder::shaderResourceReleased(ShaderStage stage, ShaderResourceType resourceType, GPUAccessType usage, int unitIndex) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& resourceBufferState = record.second.shader(stage).resource(resourceType, usage);
			resourceBufferState.invalidate(unitIndex);
		}
	}

	void GPUStateRecorder::shaderResourceSet(ShaderStage stage, ShaderResourceType resourceType, GPUAccessType usage, int unitIndex, const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& resourceBufferState = record.second.shader(stage).resource(resourceType, usage);
			resourceBufferState.validate(unitIndex);
			auto& unitState = resourceBufferState.unit(unitIndex);
			unitState.id = id;
			unitState.isEmpty = false;
		}
	}

	void GPUStateRecorder::createNewRecordingThread(const std::string& name) const noexcept
	{
		if (m_records.count(name))
		{
			LogEX("A recording thread named \"%s\" already exists.", name.c_str());
		}
		else
		{
			m_records.emplace(name, GPUState());
		}
	}

	void GPUStateRecorder::removeRecordingThread(const std::string& name) const noexcept
	{
		if (m_records.count(name))
		{
			m_records.erase(name);
		}
		else
		{
			LogEX("A recording thread named \"%s\" does not exist.", name.c_str());
		}
	}

	GPUState GPUStateRecorder::getGPUState(const std::string& name) const
	{
		if (m_records.count(name))
		{
			return m_records[name];
		}
		else
		{
			Assert("A recording thread named \"%s\" does not exist.", name.c_str());
			return GPUState();
		}
	}
}
