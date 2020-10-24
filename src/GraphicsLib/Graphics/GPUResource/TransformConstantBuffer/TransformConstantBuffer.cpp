#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/TransformConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/MaterialConstantBuffer/MaterialConstantBuffer.hpp>





namespace cg
{
	TransformConstantBuffer::TransformConstantBuffer(const BufferDict& bufferForEachShaderStage)
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

	void TransformConstantBuffer::update(const Scene& scene, const Transform& transform, const Camera& camera) const
	{
		for (auto transformBuffer : m_bufferDict)
		{
			transformBuffer.second->update(scene, transform, camera);
		}
	}

	void TransformConstantBuffer::set(ShaderStage stage, int unit) const
	{
		if (m_bufferForEachShaderStage.count(stage) == 0)
		{
			LogEX("The transform buffer does not hold a buffer corresponding to a given shader stage.");
			return; 
		}
		m_bufferForEachShaderStage.at(stage)->set(stage, unit);
	}


	TransformConstantBuffer::ElementBuffer::ElementBuffer()
	{
	}

	TransformConstantBuffer::ElementBuffer::~ElementBuffer()
	{
	}

	void TransformConstantBuffer::ElementBuffer::update(const Scene& scene, const Transform& transform, const Camera& camera)
	{
		m_update(scene, transform, camera);
	}
	void TransformConstantBuffer::ElementBuffer::set(ShaderStage stage, int unit)
	{
		m_constantBuffer->set(stage, unit);
	}
	BoundedBufferLocationList TransformConstantBuffer::ElementBuffer::getBoundedBufferLocationList() const
	{
		return m_constantBuffer->getBoundedBufferLocationList();
	}
}

