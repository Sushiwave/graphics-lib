#pragma once
#include <GraphicsLib/Graphics/ShaderCodeParser/IShaderCodeParser.hpp>
#include <Graphics/ShaderCodeParser/D3D11/Components/D3D11ShaderReflection.hpp>





namespace cg
{
	namespace d3d11
	{
		class ShaderCodeParser
			: public IShaderCodeParser
		{
		private:
			cpp::com_ptr<ID3DBlob> m_binary;
			ShaderReflection m_shaderReflection;
		public:
			ShaderCodeParser(std::shared_ptr<IShader> shader);
			ShaderCodeParser(cpp::com_ptr<ID3DBlob> binary);
			virtual ~ShaderCodeParser() = default;

			[[nodiscard]] ShaderResourceLocationDict parseShaderResourceLocation() override;
			void createInputLayoutFromVertexShaderSignature(ID3D11InputLayout** ppOut);
		};
	}
}