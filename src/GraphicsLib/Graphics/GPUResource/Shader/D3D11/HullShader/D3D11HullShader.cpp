#include "D3D11HullShader.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		Shader::SetCall HullShader::m_createSetCall() const
		{
			return [&]()
			{
				Device::getDeviceContext()->HSSetShader(m_hullShader.Get(), nullptr, 0);
			};
		}
		void HullShader::m_create()
		{
			auto hr = D3D11CreateFunctions::createHullShader(Device::getDevice().Get(), m_binary.Get(), m_hullShader.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create HullShader.");
			}
		}
		HullShader::HullShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::hs, sourceCode, sourceCodeLength, entryPoint, model)
		{
			m_create();
		}
		HullShader::HullShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::hs, filename, entryPoint, model)
		{
			m_create();
		}
	}
}