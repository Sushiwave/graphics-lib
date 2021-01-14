#include <GraphicsLib/Graphics/ShaderPool/ShaderPool.hpp>
#include <GraphicsLib/API/API.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>





namespace cg
{
	ShaderPool ShaderPool::shared;





	ShaderPool::ShaderPool()
	{
		for (auto stage : ShaderStageAll)
		{
			m_pool.emplace(stage, ShaderPool::Dict());
		}
	}

	bool ShaderPool::exists(ShaderStage stage, const std::string& name) const noexcept
	{
		return m_pool.at(stage).count(name) == 1;
	}
	std::shared_ptr<IShader> ShaderPool::createShaderFromSourceCodeAndPool(ShaderStage stage, const std::string& name, const std::string& sourceCode, const std::string& entryPoint, const std::string& model)
	{
		if (exists(stage, name)) { return get(stage, name); }
		auto shader = API::shared.graphics()->createShaderFromSourceCode(stage, sourceCode, entryPoint, model);
		m_pool[stage].emplace(name, shader);
		return shader;
	}
	std::shared_ptr<IShader> ShaderPool::createShaderFromFileAndPool(ShaderStage stage, const std::string& name, const std::string& filename, const std::string& entryPoint, const std::string& model)
	{
		if (exists(stage, name)) { return get(stage, name); }
		auto shader = API::shared.graphics()->createShaderFromFile(stage, filename, entryPoint, model);
		m_pool[stage].emplace(name, shader);
		return shader;
	}
	void ShaderPool::pool(const std::string& name, std::shared_ptr<IShader> shader)
	{
		auto stage = shader->getShaderStage();
		if (exists(stage, name)) 
		{
			LogEX("A shader named \"%s\" already exist.", name.c_str());
			return; 
		}

		m_pool[stage].emplace(name, shader);
	}
	void ShaderPool::update(const std::string& name, std::shared_ptr<IShader> shader)
	{
		auto stage = shader->getShaderStage();
		if (exists(stage, name) == false) 
		{
			LogEX("A shader named \"%s\" does not exist.", name.c_str());
			return; 
		}

		m_pool[stage].at(name) = shader;
	}
	void ShaderPool::remove(ShaderStage stage, const std::string& name)
	{
		if (exists(stage, name) == false) 
		{
			LogEX("A shader named \"%s\" does not exist.", name.c_str());
			return;
		}

		m_pool[stage].erase(name);
	}
	void ShaderPool::removeAll(ShaderStage stage)
	{
		m_pool[stage].clear();
	}
	void ShaderPool::removeAll()
	{
		m_pool.clear();
	}

	std::shared_ptr<IShader> ShaderPool::get(ShaderStage stage, const std::string& name)
	{
		if (exists(stage, name) == false) 
		{
			LogEX("A shader named \"%s\" does not exist.", name.c_str());
			return nullptr;
		}
		return m_pool[stage].at(name);
	}
}
