#pragma once
#include <Graphics/GPUResource/Shader/D3D11/VertexShader/D3D11VertexShader.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessType.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/Components/TextureSamplerDescriptor.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/Components/CullMode.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/Components/AlphaBlendDescriptor.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/Components/D3D11/RawBuffer/Components/RawBufferType.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Components/RawTexture/Components/D3D11RawTexture2DType.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Components/D3D/D3DTexturePrecision.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/Components/ComparisonFunction.hpp>

#include <assert.h>
#include <d3d11.h>
#include <ThirdParty/DirectXTex/DirectXTex.h>





namespace cg
{
	namespace d3d11
	{
		class D3D11CreateFunctions
		{
		private:
			static void checkBindFlags(D3D11_USAGE usage, bool enableUnorderedAccess, UINT* out);
			static void checkTexture2DBindFlags(RawTexture2DType type, D3D11_USAGE usage, UINT sampleCount, UINT qualityLevels, UINT* out, bool isCreatedFromScratchImage = false);
			static void checkBufferBindFlags(RawBufferType type, D3D11_USAGE usage, bool enableUnorderedAccess, UINT* out);

			static void checkBufferMiscFlags(RawBufferType type, UINT* out);

			static void checkUsage(CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, D3D11_USAGE* out);
			static void checkTexture2DUsage(RawTexture2DType type, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, D3D11_USAGE* out);

			static HRESULT checkMSAAQualityLevels(ID3D11Device* pDevice, UINT sampleCount, DXGI_FORMAT format, UINT* out);
		public:
			static void createBufferDesc(UINT byteWidth, UINT byteStride, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, bool enableUnorderedAccess, RawBufferType bufferType, D3D11_BUFFER_DESC* pBufferDescOut);
			static HRESULT createBuffer(ID3D11Device* pDevice, const void* pData, const D3D11_BUFFER_DESC& bufferDesc, ID3D11Buffer** out);
			static HRESULT createBuffer(ID3D11Device* pDevice, const void* pData, UINT byteWidth, UINT byteStride, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, bool enableUnorderedAccess, RawBufferType bufferType, ID3D11Buffer** out);
			static HRESULT createBufferSRV(ID3D11Device* pDevice, ID3D11Buffer* pBuffer, RawBufferType bufferType, ID3D11ShaderResourceView** out);
			static HRESULT createBufferUAV(ID3D11Device* pDevice, ID3D11Buffer* pBuffer, RawBufferType bufferType, ID3D11UnorderedAccessView** out);





			static HRESULT createInputLayout(ID3D11Device* pDevice, ID3DBlob* vertexShaderBinaryData, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputElementDescList, ID3D11InputLayout** out);





			static HRESULT createRenderTargetView(ID3D11Device* pDevice, ID3D11Texture2D* pRenderTargetBuffer, DXGI_FORMAT format, ID3D11RenderTargetView** out);
			static HRESULT createRenderTargetBufferFromRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, ID3D11Texture2D** out);





			static HRESULT createTextureSamplerState(ID3D11Device* pDevice, const TextureSamplerDescriptor& desc, ID3D11SamplerState** out);





			static HRESULT createBlendState(ID3D11Device* pDevice, const AlphaBlendDescriptor& descriptor, ID3D11BlendState** out);





			static HRESULT createRasterizerState(ID3D11Device* pDevice, CullMode cullMode, bool isWireFrameMode, bool multisampleEnable, bool antialiassedLineEnable, bool frontCounterClockwise, bool depthClipEnable, bool scissorEnable, ID3D11RasterizerState** out);





			static HRESULT createDepthStencilState(ID3D11Device* pDevice, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled, ID3D11DepthStencilState** out);





			[[nodiscard]] static D3D11_SHADER_RESOURCE_VIEW_DESC fetchSRVDescFrom(ID3D11ShaderResourceView* pView);
			[[nodiscard]] static D3D11_TEXTURE2D_DESC fetchTexture2DDescFrom(ID3D11Texture2D* pTexture2D);

			static int checkTextureColorDimension(DXGI_FORMAT format);
			static TexturePrecision checkTexturePrecision(DXGI_FORMAT format);
			static bool checkCompatibilityBetweenTwoTextureFormats(DXGI_FORMAT format1, DXGI_FORMAT format2);

			static void createTexture2DDesc(ID3D11Device* pDevice, UINT width, UINT height, DXGI_FORMAT format, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, UINT mostDetailedMip, UINT mostRoughedMip, bool useMipMap, UINT sampleCount, UINT qualityLevels, RawTexture2DType type, D3D11_TEXTURE2D_DESC* out);
			static void createTexture2DDesc(ID3D11Device* pDevice, UINT width, UINT height, DXGI_FORMAT format, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, UINT mostDetailedMip, UINT mostRoughedMip, bool useMipMap, UINT sampleCount, RawTexture2DType type, D3D11_TEXTURE2D_DESC* out);

			static HRESULT createScratchImage(ID3D11Device* pDevice, const std::string& filename, DirectX::ScratchImage* out);

			static HRESULT createTexture2D(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA* pData, ID3D11Texture2D** out);
			static HRESULT createTexture2D(ID3D11Device* pDevice, DirectX::ScratchImage& scratchImage, RawTexture2DType type, CPUAccessType cpuAccessType, GPUAccessType gpuAccessType, bool forceSRGB, ID3D11Texture2D** out);
			static HRESULT createResolvedTexture(ID3D11Device* pDevice, ID3D11Texture2D* textureBufferMS, DXGI_FORMAT format, int mostDetailedMip, ID3D11Texture2D** out);

			static HRESULT createTexture2DSRV(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, UINT mostDetailedMip, ID3D11Texture2D* pTexture2D, ID3D11ShaderResourceView** out);
			static HRESULT createTexture2DUAV(ID3D11Device* pDevice, const D3D11_TEXTURE2D_DESC& desc, ID3D11Texture2D* pTexture2D, ID3D11UnorderedAccessView** out);





			static void checkDepthTextureFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out);
			static void checkStencilTextureFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out);
			static void checkDepthStencilBufferFormat(DXGI_FORMAT depthStencilViewFormat, DXGI_FORMAT* out);

			static HRESULT createDepthStencilView(ID3D11Device* pDevice, ID3D11Texture2D* pDepthStencilBuffer, DXGI_FORMAT format, ID3D11DepthStencilView** out);





			static HRESULT createVertexShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11VertexShader** out);
			static HRESULT createHullShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11HullShader** out);
			static HRESULT createDomainShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11DomainShader** out);
			static HRESULT createGeometryShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11GeometryShader** out);
			static HRESULT createPixelShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11PixelShader** out);
			static HRESULT createComputeShader(ID3D11Device* pDevice, ID3DBlob* binaryData, ID3D11ComputeShader** out);
		};
	}
}
