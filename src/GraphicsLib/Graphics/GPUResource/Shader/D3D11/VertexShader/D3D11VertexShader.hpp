#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/VertexShader/IVertexShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class VertexShader
			: public d3d11::Shader,
			  public IVertexShader
		{
		private:
			cpp::com_ptr<ID3D11VertexShader> m_vertexShader;
			cpp::com_ptr<ID3D11InputLayout> m_inputLayout;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_parse();
			void m_create();
		public:
			VertexShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			VertexShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~VertexShader() = default;
		};
	}
}
