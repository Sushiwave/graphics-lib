#include <Graphics/API/D3D11/D3D11GraphicsAPI.hpp>

#include <Graphics/GPUResource/DepthStencilBuffer/D3D11/D3D11DepthStencilBuffer.hpp>
#include <Graphics/GPUResource/RenderTarget/D3D11/D3D11RenderTarget.hpp>
#include <Graphics/GPUResource/ShaderResource/TextureSampler/D3D11/D3D11TextureSampler.hpp>
#include <Graphics/GPUResource/MultipleRenderTargets/D3D11/D3D11MultipleRenderTargets.hpp>

#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>
#include <Graphics/GPUResource/DepthStencilTester/D3D11/D3D11DepthStencilTester.hpp>
#include <Graphics/GPUResource/Rasterizer/D3D11/D3D11Rasterizer.hpp>
#include <Graphics/GPUResource/AlphaBlender/D3D11/D3D11AlphaBlender.hpp>

#include <Graphics/GPUResource/Shader/D3D11/PixelShader/D3D11PixelShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/HullShader/D3D11HullShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/DomainShader/D3D11DomainShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/GeometryShader/D3D11GeometryShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/VertexShader/D3D11VertexShader.hpp>
#include <Graphics/GPUResource/Shader/D3D11/ComputeShader/D3D11ComputeShader.hpp>

#include <GraphicsLib/API/API.hpp>

#include <Graphics/GPUResource/VertexBuffer/D3D11/D3D11VertexBuffer.hpp>
#include <Graphics/GPUResource/IndexBuffer/D3D11/D3D11IndexBuffer.hpp>
#include <Graphics/GPUResource/GeometryBuffer/D3D11/D3D11GeometryBuffer.hpp>

#include <Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/D3D11/D3D11ImmutableConstantBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/D3D11/D3D11DynamicConstantBuffer.hpp>

#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/D3D11DynamicStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/D3D11DefaultStructuredBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/D3D11/D3D11ImmutableStructuredBuffer.hpp>

#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/D3D11DynamicTexture2D.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/D3D11DefaultTexture2D.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/D3D11ImmutableTexture2D.hpp>





namespace cg
{
	namespace d3d11
	{
		std::shared_ptr<IDepthStencilBuffer> GraphicsAPI::createDepthStencilBuffer(int width, int height, TextureFormat format, int MSAASampleCount, int MSAAQualityLevel)
		{
			return std::make_shared<DepthStencilBuffer>(width, height, format, MSAASampleCount, MSAAQualityLevel);
		}

		std::shared_ptr<IDepthStencilBuffer> GraphicsAPI::createDepthStencilBuffer(const cpp::Vector2D<int>& size, TextureFormat format, int MSAASampleCount, int MSAAQualityLevel)
		{
			return createDepthStencilBuffer(size.x, size.y, format, MSAASampleCount, MSAAQualityLevel);
		}

		std::shared_ptr<IRenderTarget> GraphicsAPI::createRenderTarget(int width, int height, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount)
		{
			return std::make_shared<RenderTarget>(width, height, format, mostDetailedMip, mostRoughedMip, sampleCount);
		}

		std::shared_ptr<IRenderTarget> GraphicsAPI::createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount)
		{
			return createRenderTarget(size.x, size.y, format, mostDetailedMip, mostRoughedMip, sampleCount);
		}

		std::shared_ptr<IRenderTarget> GraphicsAPI::createRenderTarget(int width, int height, TextureFormat format, int sampleCount)
		{
			return std::make_shared<RenderTarget>(width, height, format, sampleCount);
		}

		std::shared_ptr<IRenderTarget> GraphicsAPI::createRenderTarget(const cpp::Vector2D<int>& size, TextureFormat format, int sampleCount)
		{
			return createRenderTarget(size.x, size.y, format, sampleCount);
		}

		std::shared_ptr<IMultipleRenderTargets> GraphicsAPI::createMultipleRenderTargets(int width, int height, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList)
		{
			return std::make_shared<MultipleRenderTargets>(renderTargetList);
		}

		std::shared_ptr<IMultipleRenderTargets> GraphicsAPI::createMultipleRenderTargets(const cpp::Vector2D<int>& size, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList)
		{
			return createMultipleRenderTargets(size.x, size.y, renderTargetList);
		}

		std::shared_ptr<IRasterizer> GraphicsAPI::createRasterizer(CullMode cullMode, bool isWireFrameMode, bool multisampleEnable, bool antialiassedLineEnable, bool frontCounterClockwise, bool depthClipEnable, bool scissorEnable)
		{
			return std::make_shared<Rasterizer>(cullMode, isWireFrameMode, multisampleEnable, antialiassedLineEnable, frontCounterClockwise, depthClipEnable, scissorEnable);
		}

		std::shared_ptr<IAlphaBlender> GraphicsAPI::createAlphaBlender(const AlphaBlenderDescriptor& descriptor)
		{
			return std::make_shared<AlphaBlender>(descriptor);
		}

		std::shared_ptr<IDepthStencilTester> GraphicsAPI::createDepthStencilTester(ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled)
		{
			return std::make_shared<DepthStencilTester>(depthFunction, stencilFunction, isDepthTestEnabled, isStencilTestEnabled, isDepthBufferWritingOperationEnabled);
		}

		std::shared_ptr<IDynamicTexture2D> GraphicsAPI::createDynamicTexture2D(const std::string& filename)
		{
			return std::make_shared<DynamicTexture2D>(filename);
		}

		std::shared_ptr<IDefaultTexture2D> GraphicsAPI::createDefaultTexture2D(const std::string& filename)
		{
			return std::make_shared<DefaultTexture2D>(filename);
		}

		std::shared_ptr<IImmutableTexture2D> GraphicsAPI::createImmutableTexture2D(const std::string& filename)
		{
			return std::make_shared<ImmutableTexture2D>(filename);
		}

		std::shared_ptr<IDynamicTexture2D> GraphicsAPI::createDynamicTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			if (mostDetailedMipLevel == 0 && mostRoughedMipLevel == 0)
			{
				return std::make_shared<DynamicTexture2D>(width, height, format, pImage);
			}
			else
			{
				return std::make_shared<DynamicTexture2D>(width, height, format, mostDetailedMipLevel, mostRoughedMipLevel, pImage);
			}
		}

		std::shared_ptr<IDynamicTexture2D> GraphicsAPI::createDynamicTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			return createDynamicTexture2D(size.x, size.y, format, pImage, mostDetailedMipLevel, mostRoughedMipLevel);
		}

		std::shared_ptr<IDefaultTexture2D> GraphicsAPI::createDefaultTexture2D(int width, int height, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			if (mostDetailedMipLevel == 0 && mostRoughedMipLevel == 0)
			{
				return std::make_shared<DefaultTexture2D>(width, height, format, pImage);
			}
			else
			{
				return std::make_shared<DefaultTexture2D>(width, height, format, mostDetailedMipLevel, mostRoughedMipLevel, pImage);
			}
		}

		std::shared_ptr<IDefaultTexture2D> GraphicsAPI::createDefaultTexture2D(const cpp::Vector2D<int>& size, TextureFormat format, ImageXY* pImage, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			return createDefaultTexture2D(size.x, size.y, format, pImage, mostDetailedMipLevel, mostRoughedMipLevel);
		}

		std::shared_ptr<IImmutableTexture2D> GraphicsAPI::createImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			if (mostDetailedMipLevel == 0 && mostRoughedMipLevel == 0)
			{
				return std::make_shared<ImmutableTexture2D>(image, width, height, format);
			}
			else
			{
				return std::make_shared<ImmutableTexture2D>(image, width, height, format, mostDetailedMipLevel, mostRoughedMipLevel);
			}
		}

		std::shared_ptr<IImmutableTexture2D> GraphicsAPI::createImmutableTexture2D(ImageXY image, const cpp::Vector2D<int>& size, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel)
		{
			return createImmutableTexture2D(image, size.x, size.y, format, mostDetailedMipLevel, mostRoughedMipLevel);
		}

		std::shared_ptr<ITextureSampler> GraphicsAPI::createTextureSampler(const TextureSamplerDescriptor& descriptor)
		{
			return std::make_shared<TextureSampler>(descriptor);
		}

		std::shared_ptr<IShader> GraphicsAPI::createShaderFromSourceCode(ShaderStage stage, const std::string& sourceCode, const std::string& entryPoint, const std::string& model)
		{
			switch (stage)
			{
			case ShaderStage::vs:
				return std::make_shared<VertexShader>(sourceCode, sourceCode.length(), entryPoint, model);
			case ShaderStage::hs:
				return std::make_shared<HullShader>(sourceCode, sourceCode.length(), entryPoint, model);
			case ShaderStage::ds:
				return std::make_shared<DomainShader>(sourceCode, sourceCode.length(), entryPoint, model);
			case ShaderStage::gs:
				return std::make_shared<GeometryShader>(sourceCode, sourceCode.length(), entryPoint, model);
			case ShaderStage::ps:
				return std::make_shared<PixelShader>(sourceCode, sourceCode.length(), entryPoint, model);
			case ShaderStage::cs:
				return std::make_shared<ComputeShader>(sourceCode, sourceCode.length(), entryPoint, model);
			default:
				return nullptr;
			}
		}

		std::shared_ptr<IShader> GraphicsAPI::createShaderFromFile(ShaderStage stage, const std::string& filename, const std::string& entryPoint, const std::string& model)
		{
			switch (stage)
			{
			case ShaderStage::vs:
				return std::make_shared<VertexShader>(filename, entryPoint, model);
			case ShaderStage::hs:
				return std::make_shared<HullShader>(filename, entryPoint, model);
			case ShaderStage::ds:
				return std::make_shared<DomainShader>(filename, entryPoint, model);
			case ShaderStage::gs:
				return std::make_shared<GeometryShader>(filename, entryPoint, model);
			case ShaderStage::ps:
				return std::make_shared<PixelShader>(filename, entryPoint, model);
			case ShaderStage::cs:
				return std::make_shared<ComputeShader>(filename, entryPoint, model);
			default:
				return nullptr;
			}
		}

		std::shared_ptr<IIndexBuffer> GraphicsAPI::createIndexBuffer(const std::vector<unsigned short>& indices)
		{
			if (indices.size() == 0) { return nullptr; };
			return std::make_shared<d3d11::IndexBuffer>(&indices[0], static_cast<unsigned int>(indices.size()), static_cast<unsigned int>(sizeof(unsigned short)));
		}
		std::shared_ptr<IIndexBuffer> GraphicsAPI::createIndexBuffer(const std::vector<unsigned int>& indices)
		{
			if (indices.size() == 0) { return nullptr; };
			return std::make_shared<d3d11::IndexBuffer>(&indices[0], static_cast<unsigned int>(indices.size()), static_cast<unsigned int>(sizeof(unsigned int)));
		}

		std::shared_ptr<IGeometryBuffer> GraphicsAPI::createGeometryBuffer(std::shared_ptr<IVertexBuffer> vertexBuffer, std::shared_ptr<IIndexBuffer> indexBuffer)
		{
			return std::make_shared<d3d11::GeometryBuffer>(vertexBuffer, indexBuffer);
		}

		std::shared_ptr<IDynamicConstantBuffer> GraphicsAPI::createDynamicConstantBuffer(unsigned int byteStride, const void* pData)
		{
			return std::make_shared<d3d11::DynamicConstantBuffer>(byteStride, pData);
		}
		std::shared_ptr<IImmutableConstantBuffer> GraphicsAPI::createImmutableConstantBuffer(const void* pData, unsigned int byteStride)
		{
			return std::make_shared<d3d11::ImmutableConstantBuffer>(pData, byteStride);
		}


		std::shared_ptr<IDefaultStructuredBuffer> GraphicsAPI::createDefaultStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData)
		{
			return std::make_shared<d3d11::DefaultStructuredBuffer>(byteStride, elementCount, pData);
		}
		std::shared_ptr<IDynamicStructuredBuffer> GraphicsAPI::createDynamicStructuredBuffer(unsigned int byteStride, unsigned int elementCount, const void* pData)
		{
			return std::make_shared<d3d11::DynamicStructuredBuffer>(byteStride, elementCount, pData);
		}
		std::shared_ptr<IImmutableStructuredBuffer> GraphicsAPI::createImmutableStructuredBuffer(const void* pData, unsigned int byteStride, unsigned int elementCount)
		{
			return std::make_shared<d3d11::ImmutableStructuredBuffer>(pData, byteStride, elementCount);
		}

		std::shared_ptr<IVertexBuffer> GraphicsAPI::createVertexBuffer(const void* vertices, unsigned int vertexCount, unsigned int byteStride)
		{
			if (vertexCount == 0) { return nullptr; }
			return std::make_shared<context::VertexBuffer>(vertices, vertexCount, byteStride);
		}
	}
}