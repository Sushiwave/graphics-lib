#include <GraphicsLib/Graphics/GPUResource/MaterialConstantBuffer/MaterialConstantBuffer.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>




namespace cg
{
	MaterialConstantBuffer::MaterialConstantBuffer(const BufferDict& bufferForEachShaderStage)
	{
		for (auto pair : bufferForEachShaderStage)
		{
			const auto buffer = pair.second;
			const auto type = pair.first;
			const auto id = buffer->getID().get();
			if (buffer == nullptr) { continue; }
			if (m_bufferDict.count(id) == 0)
			{
				m_bufferDict.emplace(id, buffer);
			}
			m_bufferForEachShaderStage.emplace(type, buffer);
		}
	}

	void MaterialConstantBuffer::update(ShaderStage stage, const Material& material)
	{
		if (m_bufferForEachShaderStage.count(stage) == 0) 
		{
			LogEX("The material buffer does not hold a buffer corresponding to a given shader stage.");
			return; 
		}
		m_bufferForEachShaderStage[stage]->update(stage, material);
	}
	void MaterialConstantBuffer::set(ShaderStage stage, int unit)
	{
		if (m_bufferForEachShaderStage.count(stage) == 0) 
		{
			LogEX("The material buffer does not hold a buffer corresponding to a given shader stage.");
			return;
		}
		m_bufferForEachShaderStage[stage]->set(stage, unit);
	}

	MaterialConstantBuffer::ElementBuffer::ElementBuffer(unsigned int byteStride)
	{
		m_constantBuffer = API::shared.graphics()->createDynamicConstantBuffer(byteStride);
	}

	void MaterialConstantBuffer::ElementBuffer::update(ShaderStage stage, const Material& material)
	{
		m_constantBuffer->update(material.getConstant(stage));
	}
	void MaterialConstantBuffer::ElementBuffer::set(ShaderStage stage, int unit)
	{
		m_constantBuffer->set(stage, unit);
	}
	BoundedBufferLocationList MaterialConstantBuffer::ElementBuffer::getBoundedBufferLocationList() const
	{
		return m_constantBuffer->getBoundedBufferLocationList();
	}
}
