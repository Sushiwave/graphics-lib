#pragma once
#include <GraphicsLib/Graphics/API/IGraphicsAPI.hpp>





namespace cg
{
	namespace d3d11
	{
		class GraphicsAPI
			: public IGraphicsAPI
		{
		public:
			virtual ~GraphicsAPI() = default;

			[[nodiscard]] std::shared_ptr<IDepthStencilBuffer> createDepthStencilBuffer(int width, int height, TextureFormat format, int MSAASampleCount = 1, int MSAAQualityLevel = 0) override;
			[[nodiscard]] std::shared_ptr<IDepthStencilBuffer> createDepthStencilBuffer(const cpp::Vector2D<int>& size, TextureFormat format, int MSAASampleCount = 1, int MSAAQualityLevel = 0) override;

			[[nodiscard]] std::shared_ptr<IRenderTarget> createRenderTarget(int width, int height, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount = 1) override;
			[[nodiscard]] std::shared_ptr<IRenderTarget> createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount = 1) override;
			[[nodiscard]] std::shared_ptr<IRenderTarget> createRenderTarget(int width, int height, TextureFormat format, int sampleCount = 1) override;
			[[nodiscard]] std::shared_ptr<IRenderTarget> createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int sampleCount = 1) override;

			[[nodiscard]] std::shared_ptr<IMultipleRenderTarget> createMultipleRenderTarget(int width, int height, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList) override;
			[[nodiscard]] std::shared_ptr<IMultipleRenderTarget> createMultipleRenderTarget(const cpp::Vector2D<int>& size, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList) override;

			[[nodiscard]] std::shared_ptr<IRasterizer> createRasterizer(CullMode cullMode, bool isWireFrameMode = false, bool multisampleEnable = false, bool antialiassedLineEnable = false, bool frontCounterClockwise = false, bool depthClipEnable = false, bool scissorEnable = false) override;

			[[nodiscard]] std::shared_ptr<IAlphaBlender> createAlphaBlender(const AlphaBlenderDescriptor& descriptor) override;

			[[nodiscard]] std::shared_ptr<IDepthStencilTester> createDepthStencilTester(ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled) override;

			[[nodiscard]] std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(const std::string& filename);
			[[nodiscard]] std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(const std::string& filename);
			[[nodiscard]] std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(const std::string& filename);

			[[nodiscard]] std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);
			[[nodiscard]] std::shared_ptr<IDynamicTexture2D>   createDynamicTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);
			[[nodiscard]] std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);
			[[nodiscard]] std::shared_ptr<IDefaultTexture2D>   createDefaultTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);
			[[nodiscard]] std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);
			[[nodiscard]] std::shared_ptr<IImmutableTexture2D> createImmutableTexture2D(ImageXY image, const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMipLevel = 0, int mostRoughedMipLevel = 0);

			[[nodiscard]] std::shared_ptr<ITextureSampler> createTextureSampler(const TextureSamplerDescriptor& descriptor) override;

			[[nodiscard]] std::shared_ptr<IShader> createShaderFromSourceCode(ShaderStage stage, const std::string& sourceCode, const std::string& entryPoint, const std::string& model) override;
			[[nodiscard]] std::shared_ptr<IShader> createShaderFromFile(ShaderStage stage, const std::string& filename, const std::string& entryPoint, const std::string& model) override;

			[[nodiscard]] std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<unsigned int>& indices) override;
			[[nodiscard]] std::shared_ptr<IIndexBuffer> createIndexBuffer(const std::vector<unsigned short>& indices) override;

			[[nodiscard]] std::shared_ptr<IGeometryBuffer> createGeometryBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer, std::shared_ptr<IIndexBuffer> indexBuffer) override;

			[[nodiscard]] std::shared_ptr<IDynamicConstantBuffer>   createDynamicConstantBuffer(unsigned int byteStride, const void* pData = nullptr) override;
			[[nodiscard]] std::shared_ptr<IImmutableConstantBuffer> createImmutableConstantBuffer(const void* pData, unsigned int byteStride) override;

			[[nodiscard]] std::shared_ptr<IDefaultStructuredBuffer>   createDefaultStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr) override;
			[[nodiscard]] std::shared_ptr<IDynamicStructuredBuffer>   createDynamicStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData = nullptr) override;
			[[nodiscard]] std::shared_ptr<IImmutableStructuredBuffer> createImmutableStructuredBuffer(const void* pData, unsigned int byteStride, unsigned int elementCount) override;

			[[nodiscard]] std::shared_ptr<IVertexBuffer> createVertexBuffer(const void* vertices, unsigned int vertexCount, unsigned int byteStride) override;
		};
	}
}
