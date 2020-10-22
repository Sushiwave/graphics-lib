#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/GeometryShader/IGeometryShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class GeometryShader
			: public d3d11::Shader,
			  public IGeometryShader
		{
		private:
			cpp::com_ptr<ID3D11GeometryShader> m_geometryShader;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_create();
		public:
			GeometryShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			GeometryShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~GeometryShader() = default;
		};
	}
}