#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/Shader.hpp>

#include <d3d11.h>
#include <unordered_map>





namespace cg
{
	namespace d3d11
	{
		class Shader
			: public cg::Shader
		{
		private:
			using LocationDict = std::unordered_map<std::string, int>;
		protected:
			cpp::com_ptr<ID3DBlob> m_binary;
		public:
			Shader(const Shader::SetCall& setCall, ShaderStage stage, const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			Shader(const Shader::SetCall& setCall, ShaderStage stage, const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~Shader() = default;

			[[nodiscard]] cpp::com_ptr<ID3DBlob> getBinaryData() const noexcept;
		};
	}
}
