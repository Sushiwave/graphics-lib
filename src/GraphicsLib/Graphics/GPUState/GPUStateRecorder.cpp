#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>





namespace cg
{
	const ID GPUStateRecorder::m_mainRecordingThreadName = ID();

	const GPUStateRecorder GPUStateRecorder::main = []()
	{
		auto recorder = GPUStateRecorder();
		recorder.createNewRecordingThread(m_mainRecordingThreadName.get());
		return recorder;
	}();





	void GPUStateRecorder::rasterizerSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.rasterizer;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::rasterizerReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.rasterizer;
			state.isEmpty = true;
			state.id = ID();
		}
	}

	void GPUStateRecorder::depthStencilTesterSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilTester;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::depthStencilTesterReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilTester;
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

	void GPUStateRecorder::renderTargetSet(const ID& id, int count) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.renderTarget;
			state.isEmpty = false;
			state.id = id;
			state.count = count;
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
		}
	}

	void GPUStateRecorder::depthStencilBufferSet(const ID& id) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilBuffer;
			state.isEmpty = false;
			state.id = id;
		}
	}

	void GPUStateRecorder::depthStencilBufferReleased() const noexcept
	{
		for (auto& record : m_records)
		{
			auto& state = record.second.depthStencilBuffer;
			state.isEmpty = true;
			state.id = ID();
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

	void GPUStateRecorder::shaderResourceReleased(ShaderStage stage, ShaderResourceType resourceType, GPUAccessFlags usage, int unitIndex) const noexcept
	{
		for (auto& record : m_records)
		{
			auto& resourceBufferState = record.second.shader(stage).resource(resourceType, usage);
			resourceBufferState.invalidate(unitIndex);
		}
	}

	void GPUStateRecorder::shaderResourceSet(ShaderStage stage, ShaderResourceType resourceType, GPUAccessFlags usage, int unitIndex, const ID& id) const noexcept
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
