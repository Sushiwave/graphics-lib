#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/TextureFormat.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/CPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/ImageXY.hpp>
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11UnorderedAccessView.hpp>
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ShaderResourceView.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/ImageFileFormat.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		class RawTexture2D
		{
		public:
			using Resolver = std::function<void()>;
		private:
			ID m_id;

			cpp::com_ptr<ID3D11Texture2D> m_textureBuffer;

			std::shared_ptr<ShaderResourceView> m_SRV;
			std::shared_ptr<UnorderedAccessView> m_UAV;

			bool m_isResolvedTexture;

			cpp::Vector2D<int> m_size;
			int m_mostDetailedMipLevel;
			int m_mostRoughedMipLevel;
			TextureFormat m_format;

			CPUAccessFlags m_cpuAccessFlags;
			GPUAccessFlags m_gpuAccessFlags;

			Resolver m_resolve;
		private:
			template <typename T>
			void m_write(const ImageXY& image, int dimension, bool isFloatingPoint)
			{
				if ((static_cast<int>(m_cpuAccessFlags) & static_cast<int>(CPUAccessFlags::W)) == 0) { return; }

				auto byteStride = sizeof(T);

				if (m_gpuAccessFlags == GPUAccessFlags::RW)
				{
					auto rowPitch = static_cast<UINT>(m_size.x*dimension*byteStride);
					Device::getDeviceContext()->UpdateSubresource(m_textureBuffer.Get(), 0, nullptr, image.create1DArray<T>(dimension, isFloatingPoint).get(), rowPitch, 0);
				}
				else
				{
					D3D11_MAPPED_SUBRESOURCE mappedResource;
					auto hr = Device::getDeviceContext()->Map(m_textureBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
					if(FAILED(hr))
					{
						throw COM_RUNTIME_ERROR(hr, "Failed to write to the texture.");
					}

					image.storeIn((T*)mappedResource.pData, dimension, isFloatingPoint);

					Device::getDeviceContext()->Unmap(m_textureBuffer.Get(), 0);
				}
			}
		private:
			RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, bool useMipMap, const ImageXY* pImage);
		public:
			RawTexture2D() = default;
			RawTexture2D(const std::string& filename, bool forceSRGB = false);
			RawTexture2D(const std::string& filename, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool forceSRGB = false);
			RawTexture2D(int width, int height, TextureFormat format, const ImageXY* pImage = nullptr);
			RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, const ImageXY* pImage = nullptr);
			RawTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, const ImageXY* pImage = nullptr);
			RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, const ImageXY* pImage = nullptr);

			RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, int mostDetailedMipLevel);
			RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, TextureFormat format, int mostDetailedMipLevel);
			RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, bool isResolvedTexture, int mostDetailedMipLevel, const Resolver& resolver);
			RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, bool isResolvedTexture, TextureFormat format, int mostDetailedMipLevel, const Resolver& resolver);

			virtual ~RawTexture2D() = default;
		public:
			[[nodiscard]] cpp::Vector2D<int> getSize() const noexcept;

			[[nodiscard]] int getMostDetailedMipLevel() const noexcept;
			[[nodiscard]] int getMostRoughedMipLevel() const noexcept;

			[[nodiscard]] bool isResolvedTexture() const noexcept;
			void resolve();

			void generateMipMaps();

			void saveTo(const std::string& filename, ImageFileFormat format);

			void copy(const RawTexture2D& dest);
			void write(const ImageXY& image);

			std::shared_ptr<IShaderResourceMemoryAccessor> getSRV() const;
			std::shared_ptr<IShaderResourceMemoryAccessor> getUAV() const;
		};
	}
}
