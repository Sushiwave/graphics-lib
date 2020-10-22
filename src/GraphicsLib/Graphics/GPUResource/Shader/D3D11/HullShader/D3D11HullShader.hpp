#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/HullShader/IHullShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class HullShader
			: public d3d11::Shader,
			  public IHullShader
		{
		private:
			cpp::com_ptr<ID3D11HullShader> m_hullShader;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_create();
		public:
			HullShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			HullShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~HullShader() = default;
		};
	}
}