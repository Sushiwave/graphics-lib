#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <GraphicsLib/Graphics/ShaderPool/ShaderPool.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>





namespace cg
{
	namespace d3d11
	{
		void D3D11CreateFunctions::createBufferDesc(UINT byteWidth, UINT byteStride, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool enableUnorderedAccess, RawBufferType bufferType, D3D11_BUFFER_DESC* out)
		{
			ZeroMemory(out, sizeof(D3D11_BUFFER_DESC));

			checkUsage(cpuAccessFlags, gpuAccessFlags, &out->Usage);
			checkBufferBindFlags(bufferType, out->Usage, enableUnorderedAccess, &out->BindFlags);
			checkBufferMiscFlags(bufferType, &out->MiscFlags);

			out->StructureByteStride = (bufferType == RawBufferType::VertexBuffer || bufferType == RawBufferType::IndexBuffer || bufferType == RawBufferType::StructuredBuffer) ? byteStride : 0;

			out->ByteWidth = byteWidth;
			out->CPUAccessFlags = static_cast<UINT>(cpuAccessFlags);
		}

		HRESULT D3D11CreateFunctions::createBuffer(ID3D11Device* pDevice, const void* pData, const D3D11_BUFFER_DESC& bufferDesc, ID3D11Buffer** out)
		{
			D3D11_SUBRESOURCE_DATA* pSubresourceData;
			D3D11_SUBRESOURCE_DATA  subresourceData;
			if (pData)
			{
				subresourceData.pSysMem = pData;
				pSubresourceData = &subresourceData;
			}
			else
			{
				pSubresourceData = nullptr;
			}

			return pDevice->CreateBuffer(&bufferDesc, pSubresourceData, out);
		}

		HRESULT D3D11CreateFunctions::createBuffer(ID3D11Device* pDevice, const void* pData, UINT byteWidth, UINT byteStride, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool enableUnorderedAccess, RawBufferType bufferType, ID3D11Buffer** out)
		{
			D3D11_BUFFER_DESC bufferDesc;
			createBufferDesc(byteWidth, byteStride, cpuAccessFlags, gpuAccessFlags, enableUnorderedAccess, bufferType, &bufferDesc);
			return createBuffer(pDevice, pData, bufferDesc, out);
		}

		HRESULT D3D11CreateFunctions::createBufferSRV(ID3D11Device* pDevice, ID3D11Buffer* pBuffer, RawBufferType bufferType, ID3D11ShaderResourceView** out)
		{
			D3D11_BUFFER_DESC bufferDesc;
			pBuffer->GetDesc(&bufferDesc);

			D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
			ZeroMemory(&SRVDesc, sizeof(SRVDesc));
			switch (bufferType)
			{
			case RawBufferType::StructuredBuffer:
				SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
				SRVDesc.BufferEx.NumElements = bufferDesc.ByteWidth / bufferDesc.StructureByteStride;
				break;
			case RawBufferType::ByteAddressBuffer:
				SRVDesc.Format = DXGI_FORMAT_R32_TYPELESS;
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
				SRVDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
				SRVDesc.BufferEx.NumElements = bufferDesc.ByteWidth / 4;
				break;
			default:
				Assert(false, "bufferType must be a RawBufferType::StructuredBuffer or RawBufferType::ByteAddressBuffer.");
				break;
			}

			return pDevice->CreateShaderResourceView(pBuffer, &SRVDesc, out);
		}

		HRESULT D3D11CreateFunctions::createBufferUAV(ID3D11Device* pDevice, ID3D11Buffer* pBuffer, RawBufferType bufferType, ID3D11UnorderedAccessView** out)
		{
			D3D11_BUFFER_DESC bufferDesc;
			pBuffer->GetDesc(&bufferDesc);

			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
			ZeroMemory(&uavDesc, sizeof(uavDesc));

			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			switch (bufferType)
			{
			case RawBufferType::StructuredBuffer:
				uavDesc.Format = DXGI_FORMAT_UNKNOWN;
				uavDesc.Buffer.NumElements = bufferDesc.ByteWidth / bufferDesc.StructureByteStride;
				break;
			case RawBufferType::ByteAddressBuffer:
				uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
				uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
				uavDesc.Buffer.NumElements = bufferDesc.ByteWidth / 4;
				break;
			default:
				Assert(false, "bufferType must be a RawBufferType::StructuredBuffer or RawBufferType::ByteAddressBuffer.");
				break;
			}

			return pDevice->CreateUnorderedAccessView(pBuffer, &uavDesc, out);
		}

		HRESULT D3D11CreateFunctions::createInputLayout(ID3D11Device* pDevice, ID3DBlob* vertexShaderBinaryData, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputElementDescList, ID3D11InputLayout** out)
		{
			if (inputElementDescList.empty())
			{
				return S_FALSE;
			}
			return pDevice->CreateInputLayout(
				&inputElementDescList[0],
				static_cast<UINT>(inputElementDescList.size()),
				vertexShaderBinaryData->GetBufferPointer(),
				vertexShaderBinaryData->GetBufferSize(),
				out
			);
		}

		HRESULT D3D11CreateFunctions::createRenderTargetView(ID3D11Device* pDevice, ID3D11Texture2D* pRenderTargetBuffer, DXGI_FORMAT format, ID3D11RenderTargetView** out)
		{
			D3D11_RENDER_TARGET_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Format = format;
			desc.ViewDimension = D3D11CreateFunctions::fetchTexture2DDescFrom(pRenderTargetBuffer).SampleDesc.Count > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
			return pDevice->CreateRenderTargetView(pRenderTargetBuffer, &desc, out);
		}

		HRESULT D3D11CreateFunctions::createRenderTargetBufferFromRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, ID3D11Texture2D** out)
		{
			ID3D11Resource* resource;
			pRenderTargetView->GetResource(&resource);
			*out = reinterpret_cast<ID3D11Texture2D*>(resource);
			if (*out == nullptr)
			{
				return S_FALSE;
			}
			return S_OK;
		}

		HRESULT D3D11CreateFunctions::createTextureSamplerState(ID3D11Device* pDevice, const TextureSamplerDescriptor& desc, ID3D11SamplerState** out)
		{
			D3D11_SAMPLER_DESC d3d11Desc;
			ZeroMemory(&d3d11Desc, sizeof(D3D11_SAMPLER_DESC));

			d3d11Desc.Filter = static_cast<D3D11_FILTER>(desc.filter);
			d3d11Desc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressU);
			d3d11Desc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressV);
			d3d11Desc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(desc.addressW);
			d3d11Desc.BorderColor[0] = desc.borderColor.x;
			d3d11Desc.BorderColor[1] = desc.borderColor.y;
			d3d11Desc.BorderColor[2] = desc.borderColor.z;
			d3d11Desc.BorderColor[3] = desc.borderColor.w;
			d3d11Desc.MaxAnisotropy = desc.maxAnisotropy;

			return pDevice->CreateSamplerState(&d3d11Desc, out);
		}

		HRESULT D3D11CreateFunctions::createBlendState(ID3D11Device* pDevice, const AlphaBlenderDescriptor& descriptor, ID3D11BlendState** out)
		{
			D3D11_BLEND_DESC d3dBlendDesc;
			for (int i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			{
				auto element = descriptor.getElement(i);
				auto& d3dBlendDescPerRenderTarget = d3dBlendDesc.RenderTarget[i];

				d3dBlendDescPerRenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				d3dBlendDescPerRenderTarget.BlendEnable = element.isEnabled;
				d3dBlendDescPerRenderTarget.BlendOp = static_cast<D3D11_BLEND_OP>(element.blendOperator);
				d3dBlendDescPerRenderTarget.BlendOpAlpha = static_cast<D3D11_BLEND_OP>(element.blendAlphaOperator);
				d3dBlendDescPerRenderTarget.SrcBlend = static_cast<D3D11_BLEND>(element.srcBlendFactor);
				d3dBlendDescPerRenderTarget.SrcBlendAlpha = static_cast<D3D11_BLEND>(element.srcBlendAlphaFactor);
				d3dBlendDescPerRenderTarget.DestBlend = static_cast<D3D11_BLEND>(element.destBlendFactor);
				d3dBlendDescPerRenderTarget.DestBlendAlpha = static_cast<D3D11_BLEND>(element.destBlendAlphaFactor);
			}

			return pDevice->CreateBlendState(&d3dBlendDesc, out);
		}

		HRESULT D3D11CreateFunctions::createRasterizerState(ID3D11Device* pDevice, CullMode cullMode, bool isWireFrameMode, bool multisampleEnable, bool antialiassedLineEnable, bool frontCounterClockwise, bool depthClipEnable, bool scissorEnable, ID3D11RasterizerState** out)
		{
			D3D11_RASTERIZER_DESC desc;
			desc.FillMode = isWireFrameMode ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;
			desc.CullMode = static_cast<D3D11_CULL_MODE>(cullMode);
			desc.FrontCounterClockwise = frontCounterClockwise;
			desc.DepthBias = 0;
			desc.DepthBiasClamp = 0;
			desc.SlopeScaledDepthBias = 0;
			desc.DepthClipEnable = depthClipEnable;
			desc.ScissorEnable = scissorEnable;
			desc.MultisampleEnable = multisampleEnable;
			desc.AntialiasedLineEnable = antialiassedLineEnable;

			return pDevice->CreateRasterizerState(&desc, out);
		}

		HRESULT D3D11CreateFunctions::createDepthStencilState(ID3D11Device* pDevice, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled, ID3D11DepthStencilState** out)
		{
			D3D11_DEPTH_STENCIL_DESC desc;

			desc.DepthEnable = isDepthTestEnabled;
			desc.DepthWriteMask = isDepthBufferWritingOperationEnabled ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
			desc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(depthFunction);
			desc.StencilEnable = isStencilTestEnabled;
			desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			desc.BackFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(stencilFunction);

			return pDevice->CreateDepthStencilState(&desc, out);
		}

		void D3D11CreateFunctions::createTexture2DDesc(ID3D11Device* pDevice, UINT width, UINT height, DXGI_FORMAT format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, UINT mostDetailedMip, UINT mostRoughedMip, bool useMipMap, UINT sampleCount, UINT qualityLevels, RawTexture2DType type, D3D11_TEXTURE2D_DESC* out)
		{
			D3D11_USAGE usage;
			checkTexture2DUsage(type, cpuAccessFlags, gpuAccessFlags, &usage);

			UINT bindFlags;
			checkTexture2DBindFlags(type, usage, sampleCount, qualityLevels, &bindFlags);

			auto mipLevels = useMipMap ? mostRoughedMip - mostDetailedMip + 1 : 1;

			ZeroMemory(out, sizeof(*out));
			out->Width = width;
			out->Height = height;
			out->ArraySize = 1;
			out->Format = format;
			out->SampleDesc.Count = sampleCount;
			out->SampleDesc.Quality = qualityLevels;
			out->Usage = usage;
			out->BindFlags = bindFlags;
			out->CPUAccessFlags = static_cast<UINT>(cpuAccessFlags);
			out->MipLevels = mipLevels;

			if (useMipMap)
			{
				out->MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
			}
		}

		void D3D11CreateFunctions::createTexture2DDesc(ID3D11Device* pDevice, UINT width, UINT height, DXGI_FORMAT format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, UINT mostDetailedMip, UINT mostRoughedMip, bool useMipMap, UINT sampleCount, RawTexture2DType type, D3D11_TEXTURE2D_DESC* out)
		{
			UINT qualityLevels;
			auto hr = checkMSAAQualityLevels(pDevice, sampleCount, format, &qualityLevels);
			if (FAILED(hr))
			{
				sampleCount = 1;
				qualityLevels = 0;
			}
			createTexture2DDesc(pDevice, width, height, format, cpuAccessFlags, gpuAccessFlags, mostDetailedMip, mostRoughedMip, useMipMap, sampleCount, qualityLevels, type, out);
		}


		HRESULT D3D11CreateFunctions::createTexture2D(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA* pData, ID3D11Texture2D** out)
		{
			return pDevice->CreateTexture2D(&desc, pData, out);
		}

		HRESULT D3D11CreateFunctions::createTexture2D(ID3D11Device* pDevice, DirectX::ScratchImage& scratchImage, RawTexture2DType type, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool forceSRGB, ID3D11Texture2D** out)
		{
			D3D11_USAGE usage;
			checkTexture2DUsage(type, cpuAccessFlags, gpuAccessFlags, &usage);

			UINT bindFlags;
			checkTexture2DBindFlags(type, usage, 1, 0, &bindFlags, true);

			ID3D11Resource* pResource;
			auto hr = DirectX::CreateTextureEx(pDevice, scratchImage.GetImages(), scratchImage.GetImageCount(), scratchImage.GetMetadata(), usage, bindFlags, static_cast<UINT>(cpuAccessFlags), 0, forceSRGB, &pResource);

			hr = pResource->QueryInterface(IID_ID3D11Texture2D, reinterpret_cast<void**>(out));

			return hr;
		}

		HRESULT D3D11CreateFunctions::createResolvedTexture(ID3D11Device* pDevice, ID3D11Texture2D* pTextureBufferMS, DXGI_FORMAT format, int mostDetailedMip, ID3D11Texture2D** out)
		{
			auto desc = D3D11CreateFunctions::fetchTexture2DDescFrom(pTextureBufferMS);

			if (desc.SampleDesc.Count <= 1)
			{
				*out = nullptr;
				return S_FALSE;
			}

			D3D11_TEXTURE2D_DESC resolveTexDesc;

			RawTexture2DType type = RawTexture2DType::Texture;

			D3D11CreateFunctions::createTexture2DDesc(pDevice, desc.Width, desc.Height, format, CPUAccessFlags::none, GPUAccessFlags::RW, mostDetailedMip, mostDetailedMip - desc.MipLevels + 1, desc.MiscFlags == D3D11_RESOURCE_MISC_GENERATE_MIPS, 1, type, &resolveTexDesc);
			return D3D11CreateFunctions::createTexture2D(pDevice, resolveTexDesc, nullptr, out);
		}


		HRESULT D3D11CreateFunctions::createScratchImage(ID3D11Device* pDevice, const std::string& filename, DirectX::ScratchImage* outScratchImage)
		{
			auto filenameLength = filename.length();
			auto wFilename = std::unique_ptr<wchar_t>(new wchar_t[filenameLength+1]);
			size_t len;
			mbstowcs_s(&len, wFilename.get(), filenameLength+1, filename.c_str(), _TRUNCATE);

			DirectX::TexMetadata metadata;
			auto extension = strstr(filename.c_str(), ".");

			HRESULT hr;
			if (strcmp(extension, ".dds") == 0)
			{
				hr = DirectX::LoadFromDDSFile(wFilename.get(), 0, &metadata, *outScratchImage);
			}
			else if (strcmp(extension, ".hdr") == 0)
			{
				hr = DirectX::LoadFromHDRFile(wFilename.get(), &metadata, *outScratchImage);
			}
			else
			{
				hr = DirectX::LoadFromWICFile(wFilename.get(), 0, &metadata, *outScratchImage);
			}

			return hr;
		}

		HRESULT D3D11CreateFunctions::createTexture2DSRV(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, UINT mostDetailedMip, ID3D11Texture2D* pTexture2D, ID3D11ShaderResourceView** out)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
			shaderResourceViewDesc.Format = desc.Format;
			shaderResourceViewDesc.ViewDimension = (1 < desc.SampleDesc.Count) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MipLevels = desc.MipLevels;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = mostDetailedMip;

			return pDevice->CreateShaderResourceView(pTexture2D, &shaderResourceViewDesc, out);
		}

		HRESULT D3D11CreateFunctions::createTexture2DUAV(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, ID3D11Texture2D* pTexture2D, ID3D11UnorderedAccessView** out)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
			ZeroMemory(&UAVDesc, sizeof(UAVDesc));
			UAVDesc.Format = desc.Format;
			UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

			return pDevice->CreateUnorderedAccessView(pTexture2D, &UAVDesc, out);
		}

		HRESULT D3D11CreateFunctions::createDepthStencilView(ID3D11Device* pDevice, ID3D11Texture2D* pDepthStencilBuffer, DXGI_FORMAT format, ID3D11DepthStencilView** out)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.ViewDimension = D3D11CreateFunctions::fetchTexture2DDescFrom(pDepthStencilBuffer).SampleDesc.Count > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
			desc.Format = format;
			desc.Texture2DArray.ArraySize = 1;

			return pDevice->CreateDepthStencilView(pDepthStencilBuffer, &desc, out);
		}

		HRESULT D3D11CreateFunctions::createVertexShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11VertexShader** out)
		{
			return pDevice->CreateVertexShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}

		HRESULT D3D11CreateFunctions::createHullShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11HullShader** out)
		{
			return pDevice->CreateHullShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}

		HRESULT D3D11CreateFunctions::createDomainShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11DomainShader** out)
		{
			return pDevice->CreateDomainShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}

		HRESULT D3D11CreateFunctions::createGeometryShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11GeometryShader** out)
		{
			return pDevice->CreateGeometryShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}

		HRESULT D3D11CreateFunctions::createPixelShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11PixelShader** out)
		{
			return pDevice->CreatePixelShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}

		HRESULT D3D11CreateFunctions::createComputeShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11ComputeShader** out)
		{
			return pDevice->CreateComputeShader(binaryData->GetBufferPointer(), binaryData->GetBufferSize(), nullptr, out);
		}










		D3D11_SHADER_RESOURCE_VIEW_DESC D3D11CreateFunctions::fetchSRVDescFrom(ID3D11ShaderResourceView* pView)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC desc;
			pView->GetDesc(&desc);
			return desc;
		}

		D3D11_TEXTURE2D_DESC D3D11CreateFunctions::fetchTexture2DDescFrom(ID3D11Texture2D* pTexture2D)
		{
			D3D11_TEXTURE2D_DESC desc;
			pTexture2D->GetDesc(&desc);
			return desc;
		}










		int D3D11CreateFunctions::checkTextureColorDimension(DXGI_FORMAT format)
		{
			switch (format)
			{
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
			case DXGI_FORMAT_R32G32B32A32_SINT:
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
			case DXGI_FORMAT_R16G16B16A16_SINT:
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R8G8B8A8_SINT:
			case DXGI_FORMAT_R8G8B8A8_UINT:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
				return 4;
			case DXGI_FORMAT_R16G16_FLOAT:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R16G16_SNORM:
			case DXGI_FORMAT_R16G16_UNORM:
				return 2;
			case DXGI_FORMAT_R32_FLOAT:
			case DXGI_FORMAT_R32_SINT:
			case DXGI_FORMAT_R32_UINT:
			case DXGI_FORMAT_R16_FLOAT:
			case DXGI_FORMAT_R16_SINT:
			case DXGI_FORMAT_R16_UINT:
				return 1;
			default:
				Assert(false, "The given DXGI_FORMAT is not supported.");
				return int();
			}
		}

		TexturePrecision D3D11CreateFunctions::checkTexturePrecision(DXGI_FORMAT format)
		{
			switch (format)
			{
			case DXGI_FORMAT_R32G32B32A32_FLOAT:
			case DXGI_FORMAT_R32_FLOAT:
				return TexturePrecision::Float32;
			case DXGI_FORMAT_R16G16B16A16_FLOAT:
			case DXGI_FORMAT_R16G16_FLOAT:
			case DXGI_FORMAT_R16_FLOAT:
				return TexturePrecision::Float16;
			case DXGI_FORMAT_R32G32B32A32_SINT:
			case DXGI_FORMAT_R32_SINT:
				return TexturePrecision::Int32;
			case DXGI_FORMAT_R16G16B16A16_SINT:
			case DXGI_FORMAT_R16G16_SINT:
			case DXGI_FORMAT_R16_SINT:
			case DXGI_FORMAT_R16G16B16A16_SNORM:
			case DXGI_FORMAT_R16G16_SNORM:
				return TexturePrecision::Int16;
			case DXGI_FORMAT_R8G8B8A8_SINT:
			case DXGI_FORMAT_R8G8B8A8_SNORM:
				return TexturePrecision::Int8;
			case DXGI_FORMAT_R32G32B32A32_UINT:
			case DXGI_FORMAT_R32_UINT:
				return TexturePrecision::UInt32;
			case DXGI_FORMAT_R16G16B16A16_UINT:
			case DXGI_FORMAT_R16G16_UINT:
			case DXGI_FORMAT_R16_UINT:
			case DXGI_FORMAT_R16G16B16A16_UNORM:
			case DXGI_FORMAT_R16G16_UNORM:
				return TexturePrecision::UInt16;
			case DXGI_FORMAT_R8G8B8A8_UINT:
			case DXGI_FORMAT_R8G8B8A8_UNORM:
				return TexturePrecision::UInt8;
			default:
				Assert(false, "The given DXGI_FORMAT is not supported.");
				return TexturePrecision::Float32;
			}
		}

		bool D3D11CreateFunctions::checkCompatibilityBetweenTwoTextureFormats(DXGI_FORMAT format1, DXGI_FORMAT format2)
		{
			if (format1 == format2)
			{
				return true;
			}



			const auto isR32G32B32A32 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R32G32B32A32_FLOAT ||
					format == DXGI_FORMAT_R32G32B32A32_SINT ||
					format == DXGI_FORMAT_R32G32B32A32_UINT;
			};
			const auto isR16G16B16A16 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R16G16B16A16_FLOAT ||
					format == DXGI_FORMAT_R16G16B16A16_SINT ||
					format == DXGI_FORMAT_R16G16B16A16_UINT ||
					format == DXGI_FORMAT_R16G16B16A16_SNORM ||
					format == DXGI_FORMAT_R16G16B16A16_UNORM;
			};
			const auto isR8G8B8A8 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R8G8B8A8_SINT ||
					format == DXGI_FORMAT_R8G8B8A8_UINT ||
					format == DXGI_FORMAT_R8G8B8A8_SNORM ||
					format == DXGI_FORMAT_R8G8B8A8_UNORM;
			};
			const auto isR16G16 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R16G16_FLOAT ||
					format == DXGI_FORMAT_R16G16_SINT ||
					format == DXGI_FORMAT_R16G16_UINT ||
					format == DXGI_FORMAT_R16G16_SNORM ||
					format == DXGI_FORMAT_R16G16_UNORM;
			};
			const auto isR32 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R32_FLOAT ||
					format == DXGI_FORMAT_R32_SINT ||
					format == DXGI_FORMAT_R32_UINT;
			};
			const auto isR16 = [](DXGI_FORMAT format)
			{
				return format == DXGI_FORMAT_R16_FLOAT ||
					format == DXGI_FORMAT_R16_SINT ||
					format == DXGI_FORMAT_R16_UINT;
			};



			if (isR32G32B32A32(format1) && isR32G32B32A32(format2))
			{
				return true;
			}
			if (isR8G8B8A8(format1) && isR8G8B8A8(format2))
			{
				return true;
			}
			if (isR16G16B16A16(format1) && isR16G16B16A16(format2))
			{
				return true;
			}
			if (isR16G16(format1) && isR16G16(format2))
			{
				return true;
			}
			if (isR32(format1) && isR32(format2))
			{
				return true;
			}
			if (isR16(format1) && isR16(format2))
			{
				return true;
			}



			return false;
		}

		HRESULT D3D11CreateFunctions::checkMSAAQualityLevels(ID3D11Device* pDevice, UINT sampleCount, DXGI_FORMAT format, UINT* out)
		{
			HRESULT hr = S_OK;
			UINT numQualityLevels = -1;

			if (sampleCount == 1)
			{
				numQualityLevels = 0;
			}

			if (1 < sampleCount && sampleCount <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT)
			{
				hr = pDevice->CheckMultisampleQualityLevels(format, sampleCount, &numQualityLevels);
				if (FAILED(hr))
				{
					numQualityLevels = 0;
				}
				else
				{
					numQualityLevels -= 1;
				}
			}
			else if (sampleCount < 1 || D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT < sampleCount)
			{
				Assert(false, "The sampleCount must be between 1 and 32.");
			}

			*out = numQualityLevels;

			return hr;
		}

		void D3D11CreateFunctions::checkDepthStencilBufferFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out)
		{
			switch (depthStencilViewFormat)
			{
			case DXGI_FORMAT_D16_UNORM:
				*out = DXGI_FORMAT_R16_TYPELESS;
				break;
			case DXGI_FORMAT_D32_FLOAT:
				*out = DXGI_FORMAT_R32_TYPELESS;
				break;
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
				*out = DXGI_FORMAT_R32G8X24_TYPELESS;
				break;
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
				*out = DXGI_FORMAT_R24G8_TYPELESS;
				break;
			default:
				Assert(false, "The given DXGI_FORMAT is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkDepthTextureFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out)
		{
			switch (depthStencilViewFormat)
			{
			case DXGI_FORMAT_D32_FLOAT:
				*out = DXGI_FORMAT_R32_FLOAT;
				break;
			case DXGI_FORMAT_D16_UNORM:
				*out = DXGI_FORMAT_R16_FLOAT;
				break;
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
				*out = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
				break;
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
				*out = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				break;
			default:
				Assert(false, "The given DXGI_FORMAT is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkStencilTextureFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out)
		{
			switch (depthStencilViewFormat)
			{
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
				*out = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
				break;
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
				*out = DXGI_FORMAT_X24_TYPELESS_G8_UINT;
				break;
			default:
				Assert(false, "The given DXGI_FORMAT is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkTexture2DBindFlags(RawTexture2DType type, D3D11_USAGE usage, UINT sampleCount, UINT qualityLevels, UINT* out, bool isCreatedFromScratchImage)
		{
			switch (type)
			{
			case RawTexture2DType::Texture:
				checkBindFlags(usage, isCreatedFromScratchImage == false, out);
				break;
			case RawTexture2DType::RenderTarget:
				*out = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
				if ((sampleCount == 1) && (qualityLevels == 0))
				{
					*out |= D3D11_BIND_UNORDERED_ACCESS;
				}
				break;
			case RawTexture2DType::DepthStencil:
				*out = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
				break;
			default:
				Assert(false, "The given Texture2DType is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkBufferBindFlags(RawBufferType type, D3D11_USAGE usage, bool enableUnorderedAccess, UINT* out)
		{
			switch (type)
			{
			case RawBufferType::StructuredBuffer:
			case RawBufferType::ByteAddressBuffer:
				checkBindFlags(usage, enableUnorderedAccess, out);
				break;
			case RawBufferType::VertexBuffer:
				*out = D3D11_BIND_VERTEX_BUFFER;
				break;
			case RawBufferType::IndexBuffer:
				*out = D3D11_BIND_INDEX_BUFFER;
				break;
			case RawBufferType::ConstantBuffer:
				*out = D3D11_BIND_CONSTANT_BUFFER;
				break;
			default:
				Assert(false, "The given RawBufferType is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkBufferMiscFlags(RawBufferType type, UINT* out)
		{
			switch (type)
			{
			case RawBufferType::StructuredBuffer:
				*out = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
				break;
			case RawBufferType::ByteAddressBuffer:
				*out = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
				break;
			default:
				*out = 0;
				break;
			}
		}

		void D3D11CreateFunctions::checkBindFlags(D3D11_USAGE usage, bool enableUnorderedAccess, UINT* out)
		{
			switch (usage)
			{
			case D3D11_USAGE_STAGING:
				*out = 0;
				break;
			case D3D11_USAGE_DEFAULT:
				*out = D3D11_BIND_SHADER_RESOURCE | (enableUnorderedAccess ? D3D11_BIND_UNORDERED_ACCESS : 0);
				break;
			case D3D11_USAGE_IMMUTABLE:
			case D3D11_USAGE_DYNAMIC:
				*out = D3D11_BIND_SHADER_RESOURCE;
				break;
			default:
				Assert(false, "The given D3D11_USAGE is not supported.");
				break;
			}
		}

		void D3D11CreateFunctions::checkTexture2DUsage(RawTexture2DType type, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, D3D11_USAGE* out)
		{
			switch (type)
			{
			case RawTexture2DType::Texture:
				checkUsage(cpuAccessFlags, gpuAccessFlags, out);
				break;
			default:
				*out = D3D11_USAGE_DEFAULT;
				break;
			}
		}

		void D3D11CreateFunctions::checkUsage(CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, D3D11_USAGE* out)
		{
			switch (cpuAccessFlags)
			{
			case CPUAccessFlags::R:
			case CPUAccessFlags::RW:
				switch (gpuAccessFlags)
				{
				case GPUAccessFlags::none:
					*out = D3D11_USAGE_STAGING;
					break;
				default:
					Assert(false, "CPU-readable resources cannot be accessed by the GPU. If CPUAccessFlags is ""R"" or ""RW"", specify ""none"" for GPUAccessFlags.");
					break;
				}
				break;

			case CPUAccessFlags::none:
				switch (gpuAccessFlags)
				{
				case GPUAccessFlags::R:
					*out = D3D11_USAGE_IMMUTABLE;
					break;
				case GPUAccessFlags::RW:
					*out = D3D11_USAGE_DEFAULT;
					break;
				default:
					Assert(false, "There are no resources that are not accessible by the CPU or GPU. If CPUAccessFlags is ""none"", GPUAAccessFlags is set to ""R"" or ""RW"".");
					break;
				}
				break;

			case CPUAccessFlags::W:
				switch (gpuAccessFlags)
				{
				case GPUAccessFlags::R:
					*out = D3D11_USAGE_DYNAMIC;
					break;
				case GPUAccessFlags::RW:
					*out = D3D11_USAGE_DEFAULT;
					break;
				case GPUAccessFlags::none:
					*out = D3D11_USAGE_STAGING;
					break;
				}
				break;

			default:
				Assert(false, "The given CPUAccessFlags is not supported.");
				break;
			}
		}
	}
}
