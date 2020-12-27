#pragma once
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/Components/AlphaBlenderDescriptor.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/Components/TextureSamplerDescriptor.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/TextureFormat.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/Components/CullMode.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/CPUAccessType.hpp>

#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>

#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/IDepthStencilTester.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/IMultipleRenderTargets.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/IRasterizerState.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/IAlphaBlender.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IDynamicTexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IDefaultTexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IImmutableTexture2D.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/ITextureSampler.hpp>

#include <GraphicsLib/Graphics/GPUResource/Shader/Base/IShader.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/IDynamicConstantBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/IImmutableConstantBuffer.hpp>

#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IDynamicStructuredBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IDefaultStructuredBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/IImmutableStructuredBuffer.hpp>

#include <GraphicsLib/Graphics/GPUResource/VertexBuffer/IVertexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/IndexBuffer/IIndexBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/GeometryBuffer/IGeometryBuffer.hpp>





namespace cg
{
	class IGraphicsAPI
	{
	public:
		[[nodiscard]] virtual std::shared_ptr<IDepthStencilBuffer> createDepthStencilBuffer(int width, int height, TextureFormat format, int MSAASampleCount = 1, int MSAAQualityLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDepthStencilBuffer> createDepthStencilBuffer(const cpp::Vector2D<int>& size, TextureFormat format, int MSAASampleCount = 1, int MSAAQualityLevel = 0) = 0;

		[[nodiscard]] virtual std::shared_ptr<IRenderTarget> createRenderTarget(int width, int height, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount = 1) = 0;
		[[nodiscard]] virtual std::shared_ptr<IRenderTarget> createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount = 1) = 0;
		[[nodiscard]] virtual std::shared_ptr<IRenderTarget> createRenderTarget(int width, int height, TextureFormat format, int sampleCount = 1) = 0;
		[[nodiscard]] virtual std::shared_ptr<IRenderTarget> createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int sampleCount = 1) = 0;

		[[nodiscard]] virtual std::shared_ptr<IMultipleRenderTargets> createMultipleRenderTargets(const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList) = 0;
		[[nodiscard]] virtual std::shared_ptr<IMultipleRenderTargets> createMultipleRenderTargets(int width, int height, const std::vector<TextureFormat> renderTargetFormatList, int sampleCount = 1) = 0;
		[[nodiscard]] virtual std::shared_ptr<IMultipleRenderTargets> createMultipleRenderTargets(const cpp::Vector2D<int>& size, const std::vector<TextureFormat> renderTargetFormatList, int sampleCount = 1) = 0;

		[[nodiscard]] virtual std::shared_ptr<IRasterizerState> createRasterizerState(CullMode cullMode = CullMode::none, bool isWireFrameMode = false, bool multisampleEnable = false, bool antialiassedLineEnable = false, bool frontCounterClockwise = false, bool depthClipEnable = false, bool scissorEnable = false) = 0;

		[[nodiscard]] virtual std::shared_ptr<IAlphaBlender> createAlphaBlender(const AlphaBlenderDescriptor& descriptor = AlphaBlenderDescriptor()) = 0;

		[[nodiscard]] virtual std::shared_ptr<IDepthStencilTester> createDepthStencilTester(ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled) = 0;

		[[nodiscard]] virtual std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(const std::string& filename) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(const std::string& filename) = 0;
		[[nodiscard]] virtual std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(const std::string& filename) = 0;

		[[nodiscard]] virtual std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;
		[[nodiscard]] virtual std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(ImageXY image, const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0) = 0;

		[[nodiscard]] virtual std::shared_ptr<ITextureSampler> createTextureSampler(const TextureSamplerDescriptor& descriptor = TextureSamplerDescriptor()) = 0;

		[[nodiscard]] virtual std::shared_ptr<IShader> createShaderFromSourceCode(ShaderStage stage, const std::string& sourceCode, const std::string& entryPoint, const std::string& model) = 0;
		[[nodiscard]] virtual std::shared_ptr<IShader> createShaderFromFile(ShaderStage stage, const std::string& filename, const std::string& entryPoint, const std::string& model) = 0;

		[[nodiscard]] virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(const void* vertices, unsigned int vertexCount, unsigned int byteStride) = 0;
		[[nodiscard]] virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<unsigned int>& indices) = 0;
		[[nodiscard]] virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<unsigned short>& indices) = 0;

		[[nodiscard]] virtual std::shared_ptr<IDynamicConstantBuffer>   createDynamicConstantBuffer(unsigned int byteStride, const void* pData = nullptr) = 0;
		[[nodiscard]] virtual std::shared_ptr<IImmutableConstantBuffer> createImmutableConstantBuffer(const void* pData, unsigned int byteStride) = 0;

		[[nodiscard]] virtual std::shared_ptr<IDefaultStructuredBuffer>   createDefaultStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr) = 0;
		[[nodiscard]] virtual std::shared_ptr<IDynamicStructuredBuffer>   createDynamicStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr) = 0;
		[[nodiscard]] virtual std::shared_ptr<IImmutableStructuredBuffer> createImmutableStructuredBuffer(const void* pData, unsigned int byteStride, unsigned int elementCount) = 0;

		[[nodiscard]] virtual std::shared_ptr<IGeometryBuffer> createGeometryBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer, std::shared_ptr<IIndexBuffer> indexBuffer) = 0;
	};
}
