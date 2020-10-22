#include "D3D11DomainShader.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>




namespace cg
{
    namespace d3d11
    {
        Shader::SetCall DomainShader::m_createSetCall() const
        {
            return [&]()
            {
                Device::getDeviceContext()->DSSetShader(m_domainShader.Get(), nullptr, 0);
            };
        }
        void DomainShader::m_create()
        {
            auto hr = D3D11CreateFunctions::createDomainShader(Device::getDevice().Get(), m_binary.Get(), m_domainShader.ReleaseAndGetAddressOf());
            if(FAILED(hr))
            {
                throw COM_RUNTIME_ERROR(hr, "Failed to create DomainShader.");
            }
        }
        DomainShader::DomainShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
            : d3d11::Shader(m_createSetCall(), ShaderStage::ds, sourceCode, sourceCodeLength, entryPoint, model)
        {
            m_create();
        }
        DomainShader::DomainShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
            : d3d11::Shader(m_createSetCall(), ShaderStage::ds, filename, entryPoint, model)
        {
            m_create();
        }
    }
}
