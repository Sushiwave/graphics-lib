#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/ComputeShader/IComputeShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/Base/D3D11Shader.hpp>





namespace cg
{
	namespace d3d11
	{
		class ComputeShader
			: public d3d11::Shader,
			  public IComputeShader
		{
		private:
			cpp::com_ptr<ID3D11ComputeShader> m_computeShader;
		private:
			Shader::SetCall m_createSetCall() const;
			void m_create();
		public:
			ComputeShader(const std::string& sourceCode, const size_t sourceCodeLength, const std::string& entryPoint, const std::string& model);
			ComputeShader(const std::string& filename, const std::string& entryPoint, const std::string& model);
			virtual ~ComputeShader() = default;

			void dispatch(int x, int y, int z) override;
		};
	}
}
