#include <Graphics/GPUResource/Shader/D3D11/ComputeShader/D3D11ComputeShader.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		Shader::SetCall ComputeShader::m_createSetCall() const
		{
			return [&]()
			{
				d3d11::Device::getDeviceContext()->CSSetShader(m_computeShader.Get(), nullptr, 0);
			};
		}
		void ComputeShader::m_create()
		{
			auto hr = D3D11CreateFunctions::createComputeShader(Device::getDevice().Get(), m_binary.Get(), m_computeShader.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create ComputeShader.");
			}
		}
		ComputeShader::ComputeShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::cs, sourceCode, sourceCodeLength, entryPoint, model)
		{
			m_create();
		}
		ComputeShader::ComputeShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
			: d3d11::Shader(m_createSetCall(), ShaderStage::cs, filename, entryPoint, model)
		{
			m_create();
		}
		void ComputeShader::dispatch(int x, int y, int z)
		{
			Device::getDeviceContext()->Dispatch(x, y, z);
		}
	}
}