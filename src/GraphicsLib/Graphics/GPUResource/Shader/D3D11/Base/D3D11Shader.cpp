#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>
#include <Graphics/ShaderCompiler/HLSL/D3D11/D3D11ShaderCompiler.hpp>





namespace cg
{
	namespace d3d11
	{
		Shader::Shader(const Shader::SetCall& setCall, ShaderStage stage, const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
			: cg::Shader(setCall, stage),
			  m_binary(d3d::ShaderCompiler::compile(sourceCode.c_str(), sourceCodeLength, entryPoint.c_str(), model.c_str()))
		{
		}
		Shader::Shader(const Shader::SetCall& setCall, ShaderStage stage, const std::string& filename, const std::string& entryPoint, const std::string& model)
			: cg::Shader(setCall, stage),
			  m_binary(d3d::ShaderCompiler::compileFromFile(filename.c_str(), entryPoint.c_str(), model.c_str()))
		{
		}
		cpp::com_ptr<ID3DBlob> Shader::getBinaryData() const noexcept
		{
			return m_binary;
		}
	}
}
