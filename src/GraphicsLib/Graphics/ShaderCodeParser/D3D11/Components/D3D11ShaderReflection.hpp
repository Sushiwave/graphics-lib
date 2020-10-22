#pragma once
#include <d3d11shader.h>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class ShaderReflection
		{
		private:
			cpp::com_ptr<ID3D11ShaderReflection> m_shaderReflection;

			D3D11_SHADER_DESC m_shaderDesc;
			std::vector<D3D11_SHADER_INPUT_BIND_DESC> m_inputBindingDescs;
			std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_parameterDescs;
			std::vector<D3D11_SHADER_BUFFER_DESC> m_constantBufferDescs;
		public:
			ShaderReflection(ID3DBlob* binary);
			virtual ~ShaderReflection() = default;

			[[nodiscard]] D3D11_SHADER_DESC getShaderDesc() const;
			[[nodiscard]] D3D11_SIGNATURE_PARAMETER_DESC getParameterDesc(int index) const;
			[[nodiscard]] D3D11_SHADER_INPUT_BIND_DESC getInputBindingDesc(int index) const;
			[[nodiscard]] D3D11_SHADER_BUFFER_DESC getConstantBufferDesc(int index) const;
		};
	}
}
