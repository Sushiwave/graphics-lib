#pragma once
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/IShader.hpp>

#include <memory>





namespace cg
{
	class ShaderPool
	{
	private:
		using Dict = std::unordered_map<std::string, std::shared_ptr<IShader>>;
		using Pool = std::unordered_map<ShaderStage, Dict>;
	public:
		static ShaderPool shared;
	private:
		Pool m_pool;
	private:
		ShaderPool();
	public:
		virtual ~ShaderPool() = default;
	
		[[nodiscard]] bool exists(ShaderStage stage, const std::string& nameKey) const noexcept;

		[[nodiscard]] std::shared_ptr<IShader> createShaderFromSourceCodeAndPool(ShaderStage stage, const std::string& nameKey, const std::string& sourceCode, const std::string& entryPoint, const std::string& model);
		[[nodiscard]] std::shared_ptr<IShader> createShaderFromFileAndPool(ShaderStage stage, const std::string& nameKey, const std::string& filename, const std::string& entryPoint, const std::string& model);
		void pool(const std::string& nameKey, std::shared_ptr<IShader> shader);
		void update(const std::string& nameKey, std::shared_ptr<IShader> shader);

		void remove(ShaderStage stage, const std::string& nameKey);
		void removeAll(ShaderStage stage);
		void removeAll();

		[[nodiscard]] std::shared_ptr<IShader> get(ShaderStage stage, const std::string& nameKey);
	};
}