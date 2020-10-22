#include <GraphicsLib/Graphics/GPUResource/LightConstantBuffer/LightConstantBuffer.hpp>





namespace cg
{
	void LightConstantBuffer::ElementBuffer::update(const Scene& scene)
	{
		m_update(scene);
	}

	void LightConstantBuffer::ElementBuffer::set(ShaderStage stage, int unit)
	{
		m_constantBuffer->set(stage, unit);
	}

	BoundedBufferLocationList LightConstantBuffer::ElementBuffer::getBoundedBufferLocationList() const
	{
		return m_constantBuffer->getBoundedBufferLocationList();
	}
	LightConstantBuffer::LightConstantBuffer(const BufferDict& bufferForEachShaderStage)
	{
		for (auto pair : bufferForEachShaderStage)
		{
			const auto buffer = pair.second;
			const auto type = pair.first;
			const auto id = buffer->getID().get();
			if (buffer == nullptr) { return; }
			if (m_bufferDict.count(id) == 0)
			{
				m_bufferDict.emplace(id, buffer);
			}
			m_bufferForEachShaderStage.emplace(type, buffer);
		};
	}
	void LightConstantBuffer::update(const Scene& scene)
	{
		for (auto lightBuffer : m_bufferDict)
		{
			lightBuffer.second->update(scene);
		}
	}
	void LightConstantBuffer::set(ShaderStage stage, int unit)
	{
		if (m_bufferForEachShaderStage.count(stage) == 0)
		{
			LogEX("The light buffer does not hold a buffer corresponding to a given shader stage.");
			return;
		}
		m_bufferForEachShaderStage.at(stage)->set(stage, unit);
	}
}
