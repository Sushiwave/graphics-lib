#include "D3D11ShaderReflection.hpp"

#include <d3dcompiler.h>





namespace cg
{
	namespace d3d11
	{
		ShaderReflection::ShaderReflection(ID3DBlob* binary)
			: m_shaderDesc()
		{
			if (SUCCEEDED(D3DReflect(binary->GetBufferPointer(), binary->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)m_shaderReflection.ReleaseAndGetAddressOf())))
			{
				m_shaderReflection->GetDesc(&m_shaderDesc);
				m_parameterDescs.resize(m_shaderDesc.InputParameters);
				m_inputBindingDescs.resize(m_shaderDesc.BoundResources);
				m_constantBufferDescs.resize(m_shaderDesc.ConstantBuffers);
				for (UINT i = 0; i < m_shaderDesc.InputParameters; ++i)
				{
					m_shaderReflection->GetInputParameterDesc(i, &m_parameterDescs[i]);
				}
				for (UINT i = 0; i < m_shaderDesc.BoundResources; ++i)
				{
					m_shaderReflection->GetResourceBindingDesc(i, &m_inputBindingDescs[i]);
				}
				for (UINT i = 0; i < m_shaderDesc.ConstantBuffers; ++i)
				{
					m_shaderReflection->GetConstantBufferByIndex(i)->GetDesc(&m_constantBufferDescs[i]);
				}
			}
		}
		D3D11_SHADER_DESC ShaderReflection::getShaderDesc() const
		{
			return m_shaderDesc;
		}
		D3D11_SIGNATURE_PARAMETER_DESC ShaderReflection::getParameterDesc(int index) const
		{
			return m_parameterDescs.at(index);
		}
		D3D11_SHADER_INPUT_BIND_DESC ShaderReflection::getInputBindingDesc(int index) const
		{
			return m_inputBindingDescs.at(index);
		}
		D3D11_SHADER_BUFFER_DESC ShaderReflection::getConstantBufferDesc(int index) const
		{
			return m_constantBufferDescs.at(index);
		}
	}
}