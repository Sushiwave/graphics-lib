#include <Graphics/ShaderCodeParser/D3D11/D3D11ShaderCodeParser.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>





namespace cg
{
	namespace d3d11
	{
		ShaderResourceLocationDict ShaderCodeParser::parseShaderResourceLocation()
		{
			const auto& shaderDesc = m_shaderReflection.getShaderDesc();

			ShaderResourceLocationDict result;
			for (auto resourceType : ShaderResourceTypeAll)
			{
				result.emplace(resourceType, std::unordered_map<std::string, int>());
			}

			for (UINT i = 0; i < shaderDesc.BoundResources; ++i)
			{
				const auto& desc = m_shaderReflection.getInputBindingDesc(i);

				ShaderResourceType type;
				switch (desc.Type)
				{
				case D3D_SIT_CBUFFER:
					type = ShaderResourceType::ConstantBuffer;
					break;
				case D3D_SIT_TEXTURE:
				case D3D_SIT_TBUFFER:
				case D3D11_SIT_UAV_RWTYPED:
					type = ShaderResourceType::Texture;
					break;
				case D3D_SIT_SAMPLER:
					type = ShaderResourceType::TextureSampler;
					break;
				case D3D11_SIT_STRUCTURED:
				case D3D11_SIT_BYTEADDRESS:
				case D3D11_SIT_UAV_RWBYTEADDRESS:
				case D3D11_SIT_UAV_RWSTRUCTURED:
				case D3D11_SIT_UAV_APPEND_STRUCTURED:
				case D3D11_SIT_UAV_CONSUME_STRUCTURED:
				case D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
					type = ShaderResourceType::StructuredBuffer;
					break;
				default:
					break;
				}

				result[type].emplace(desc.Name, desc.BindPoint);
			}

			return result;
		}
		ShaderCodeParser::ShaderCodeParser(std::shared_ptr<IShader> shader)
			: m_binary(std::dynamic_pointer_cast<d3d11::Shader>(shader)->getBinaryData()),
			  m_shaderReflection(ShaderReflection(m_binary.Get()))
		{
		}
		ShaderCodeParser::ShaderCodeParser(cpp::com_ptr<ID3DBlob> binary)
			: m_binary(binary),
			  m_shaderReflection(ShaderReflection(binary.Get()))
		{

		}
		void ShaderCodeParser::createInputLayoutFromVertexShaderSignature(ID3D11InputLayout** ppOut)
		{
			const auto shaderDesc = m_shaderReflection.getShaderDesc();

			// Read input layout description from shader info
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
			for (UINT i = 0; i < shaderDesc.InputParameters; i++)
			{
				D3D11_SIGNATURE_PARAMETER_DESC paramDesc = m_shaderReflection.getParameterDesc(i);

				// fill out input element desc
				D3D11_INPUT_ELEMENT_DESC elementDesc;
				ZeroMemory(&elementDesc, sizeof(elementDesc));
				elementDesc.SemanticName = paramDesc.SemanticName;
				elementDesc.SemanticIndex = paramDesc.SemanticIndex;
				elementDesc.InputSlot = 0;
				elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDesc.InstanceDataStepRate = 0;


				// determine DXGI format
				if (paramDesc.Mask == 1)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
				}
				else if (paramDesc.Mask <= 3)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
				}
				else if (paramDesc.Mask <= 7)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				}
				else if (paramDesc.Mask <= 15)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				}

				//save element desc
				inputLayoutDesc.emplace_back(elementDesc);
			}

			// Try to create Input Layout
			auto hr = D3D11CreateFunctions::createInputLayout(Device::getDevice().Get(), m_binary.Get(), inputLayoutDesc, ppOut);

			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create InputLayout.");
			}
		}
	}
}