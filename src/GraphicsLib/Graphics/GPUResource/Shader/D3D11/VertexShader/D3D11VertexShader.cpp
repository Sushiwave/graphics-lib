#include <Graphics/GPUResource/Shader/D3D11/VertexShader/D3D11VertexShader.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/ShaderCodeParser/D3D11/D3D11ShaderCodeParser.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>




namespace cg
{
	namespace d3d11
	{
		Shader::SetCall VertexShader::m_createSetCall() const
		{
			return [=]()
			{
				auto deviceContext = Device::getDeviceContext();
				deviceContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
				deviceContext->IASetInputLayout(m_inputLayout.Get());
			};
		}
		void VertexShader::m_parse()
		{
			d3d11::ShaderCodeParser(m_binary).createInputLayoutFromVertexShaderSignature(m_inputLayout.ReleaseAndGetAddressOf());
		}
		void VertexShader::m_create()
		{
			auto hr = D3D11CreateFunctions::createVertexShader(Device::getDevice().Get(), m_binary.Get(), m_vertexShader.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create VertexShader.");
			}
		}

		VertexShader::VertexShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::vs, sourceCode, sourceCodeLength, entryPoint, model)
		{
			m_create();
			m_parse();
		}
		VertexShader::VertexShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::vs, filename, entryPoint, model)
		{
			m_create();
			m_parse();
		}
	}
}
