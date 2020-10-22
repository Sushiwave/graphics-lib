#include <Graphics/GPUResource/Shader/D3D11/PixelShader/D3D11PixelShader.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		Shader::SetCall PixelShader::m_createSetCall() const
		{
			return [&]()
			{
				Device::getDeviceContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);
			};
		}
		void PixelShader::m_create()
		{
			auto hr = D3D11CreateFunctions::createPixelShader(Device::getDevice().Get(), m_binary.Get(), m_pixelShader.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create PixelShader.");
			}
		}
		PixelShader::PixelShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::ps, sourceCode, sourceCodeLength, entryPoint, model)
		{
			m_create();
		}
		PixelShader::PixelShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::ps, filename, entryPoint, model)
		{
			m_create();
		}
	}
}
