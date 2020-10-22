#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/PixelShader/IPixelShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class PixelShader
			: public d3d11::Shader,
			  public IPixelShader
		{
		private:
			cpp::com_ptr<ID3D11PixelShader> m_pixelShader;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_create();
		public:
			PixelShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			PixelShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~PixelShader() = default;
		};
	}
}
