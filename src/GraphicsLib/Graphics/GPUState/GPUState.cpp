#include <GraphicsLib/Graphics/GPUState/GPUState.hpp>





namespace cg
{
	GPUState::ShaderBufferState::ShaderBufferState() noexcept
	{
		for (auto resourceType : ShaderResourceTypeAll)
		{
			std::unordered_map<GPUAccessType, ShaderResourceBufferState> dict;
			dict.emplace(GPUAccessType::R, ShaderResourceBufferState());
			dict.emplace(GPUAccessType::RW, ShaderResourceBufferState());
			m_resource.emplace(resourceType, dict);
		}
	}

	GPUState::ShaderBufferState::ShaderResourceBufferState& GPUState::ShaderBufferState::resource(ShaderResourceType type, GPUAccessType usage)
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
			m_unitStateDict.emplace(unitIndex, UnitState());
			m_validatedUnitIndexList.emplace_back(unitIndex);
		}
	}

	void GPUState::ShaderBufferState::ShaderResourceBufferState::invalidate(int unitIndex)
	{
		if (isValidated(unitIndex))
		{
			m_unitStateDict.erase(unitIndex);
			m_validatedUnitIndexList.erase(std::find(m_validatedUnitIndexList.begin(), m_validatedUnitIndexList.end(), unitIndex));
		}
	}

	bool GPUState::ShaderBufferState::ShaderResourceBufferState::isValidated(int index) const noexcept
	{
		return m_unitStateDict.count(index) == 1;
	}

	std::vector<int> GPUState::ShaderBufferState::ShaderResourceBufferState::validatedUnitIndexList() const noexcept
	{
		return m_validatedUnitIndexList;
	}

	GPUState::ShaderBufferState::ShaderResourceBufferState::UnitState& GPUState::ShaderBufferState::ShaderResourceBufferState::unit(int index)
	{
		return m_unitStateDict[index];
	}
}
