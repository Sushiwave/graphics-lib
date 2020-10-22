#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/DomainShader/IDomainShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class DomainShader
			: public d3d11::Shader,
			  public IDomainShader
		{
		private:
			cpp::com_ptr<ID3D11DomainShader> m_domainShader;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_create();
		public:
			DomainShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			DomainShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~DomainShader() = default;
		};
	}
}
