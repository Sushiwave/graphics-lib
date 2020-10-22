#include "D3D11GeometryShader.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>




namespace cg
{
    namespace d3d11
    {
        Shader::SetCall GeometryShader::m_createSetCall() const
        {
            return [&]()
            {
                Device::getDeviceContext()->GSSetShader(m_geometryShader.Get(), nullptr, 0);
            };
        }
        void GeometryShader::m_create()
        {
            auto hr = D3D11CreateFunctions::createGeometryShader(Device::getDevice().Get(), m_binary.Get(), m_geometryShader.ReleaseAndGetAddressOf());
            if(FAILED(hr))
            {
                throw COM_RUNTIME_ERROR(hr, "Failed to create GeometryShader");
            }
        }
        GeometryShader::GeometryShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model)
            : d3d11::Shader(m_createSetCall(), ShaderStage::gs, sourceCode, sourceCodeLength, entryPoint, model)
        {
            m_create();
        }
        GeometryShader::GeometryShader(const std::string& filename, const std::string& entryPoint, const std::string& model)
            : d3d11::Shader(m_createSetCall(), ShaderStage::gs, filename, entryPoint, model)
        {
            m_create();
        }
    }
}

