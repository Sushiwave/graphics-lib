#include <GraphicsLib/Graphics/GPUState/GPUState.hpp>





namespace cg
{
	GPUState::ShaderBufferState::ShaderBufferState() noexcept
	{
		for (auto resourceType : ShaderResourceTypeAll)
		{
			std::unordered_map<GPUAccessFlags, ShaderResourceBufferState> dict;
			dict.emplace(GPUAccessFlags::R, ShaderResourceBufferState());
			dict.emplace(GPUAccessFlags::RW, ShaderResourceBufferState());
			m_resource.emplace(resourceType, dict);
		}
	}

	GPUState::ShaderBufferState::ShaderResourceBufferState& GPUState::ShaderBufferState::resource(ShaderResourceType type, GPUAccessFlags usage)
	{
		return m_resource[type][usage];
	}

	GPUState::GPUState() noexcept
	{
		for (auto stage : ShaderStageAll)
		{
			m_shader.emplace(stage, ShaderBufferState());
		}
	}

	GPUState::ShaderBufferState& GPUState::shader(ShaderStage stage)
	{
		return m_shader[stage];
	}

	void GPUState::ShaderBufferState::ShaderResourceBufferState::validate(int unitIndex)
	{
		if (isValidated(unitIndex) == false)
		{
			m_unit.emplace(unitIndex, State());
			m_validatedUnitIndexList.emplace_back(unitIndex);
		}
	}

	void GPUState::ShaderBufferState::ShaderResourceBufferState::invalidate(int unitIndex)
	{
		if (isValidated(unitIndex))
		{
			m_unit.erase(unitIndex);
			m_validatedUnitIndexList.erase(std::find(m_validatedUnitIndexList.begin(), m_validatedUnitIndexList.end(), unitIndex));
		}
	}

	bool GPUState::ShaderBufferState::ShaderResourceBufferState::isValidated(int index) const noexcept
	{
		return m_unit.count(index) == 1;
	}

	std::vector<int> GPUState::ShaderBufferState::ShaderResourceBufferState::validatedUnitIndexList() const noexcept
	{
		return m_validatedUnitIndexList;
	}

	GPUState::State& GPUState::ShaderBufferState::ShaderResourceBufferState::unit(int index)
	{
		return m_unit[index];
	}
}
