#include "D3D11RawTexture2D.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>

#include <ThirdParty/DirectXTex/DirectXTex.h>

#include <limits>




#define MAX_TEXTURE_FILENAME_STR_SIZE 256
#define SHADERSTAGE_NUM 6





namespace cg
{
	namespace d3d11
	{
		RawTexture2D::RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, bool isResolvedTexture, TextureFormat format, int mostDetailedMipLevel, const Resolver& resolver)
			: m_textureBuffer(textureBuffer),
			  m_format(format),
			  m_resolve(resolver),
			  m_isResolvedTexture(isResolvedTexture)
		{
			auto desc = D3D11CreateFunctions::fetchTexture2DDescFrom(textureBuffer.Get());
		
			desc.Format = static_cast<DXGI_FORMAT>(format);

			m_cpuAccessFlags = static_cast<CPUAccessFlags>(desc.CPUAccessFlags);
			m_size = cpp::Vector2D<int>(desc.Width, desc.Height);
			m_mostDetailedMipLevel = mostDetailedMipLevel;
			m_mostRoughedMipLevel = m_mostDetailedMipLevel+desc.MipLevels-1;
			m_cpuAccessFlags = static_cast<CPUAccessFlags>(desc.CPUAccessFlags);

			switch (desc.Usage)
			{
			case D3D11_USAGE_STAGING:
				m_gpuAccessFlags = GPUAccessFlags::none;
				break;
			case D3D11_USAGE_IMMUTABLE:
				m_gpuAccessFlags = GPUAccessFlags::R;
				break;
			default:
				m_gpuAccessFlags = GPUAccessFlags::RW;
				break;
			}

			if (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
			{
				cpp::com_ptr<ID3D11ShaderResourceView> cpSRV;
			
				auto hr = D3D11CreateFunctions::createTexture2DSRV(Device::getDevice().Get(), desc, mostDetailedMipLevel, textureBuffer.Get(), cpSRV.ReleaseAndGetAddressOf());
				if(FAILED(hr))
				{	
					throw COM_RUNTIME_ERROR(hr, "Failed to create ShaderResourceView.");
				}
			
				m_SRV = std::make_shared<ShaderResourceView>(m_id, ShaderResourceType::Texture, cpSRV);

				if (desc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
				{
					cpp::com_ptr<ID3D11UnorderedAccessView> cpUAV;
					hr = D3D11CreateFunctions::createTexture2DUAV(Device::getDevice().Get(), desc, textureBuffer.Get(), cpUAV.ReleaseAndGetAddressOf());
					if(FAILED(hr))
					{
						throw COM_RUNTIME_ERROR(hr, "Failed to create UnorderedAccessView.");
					}

					m_UAV = std::make_shared<UnorderedAccessView>(m_id, ShaderResourceType::Texture, cpUAV);
				}
			}
		}
		RawTexture2D::RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, int mostDetailedMipLevel)
			: RawTexture2D(textureBuffer, static_cast<TextureFormat>(D3D11CreateFunctions::fetchTexture2DDescFrom(textureBuffer.Get()).Format), mostDetailedMipLevel)
		{
		}
		RawTexture2D::RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, TextureFormat format, int mostDetailedMipLevel)
			: RawTexture2D(textureBuffer, false, format, mostDetailedMipLevel, []() {})
		{
		}
		RawTexture2D::RawTexture2D(cpp::com_ptr<ID3D11Texture2D> textureBuffer, bool isResolvedTexture, int mostDetailedMipLevel, const Resolver& resolver
		)
			: RawTexture2D(textureBuffer, isResolvedTexture, static_cast<TextureFormat>(D3D11CreateFunctions::fetchTexture2DDescFrom(textureBuffer.Get()).Format), mostDetailedMipLevel, resolver)
		{
		}
		RawTexture2D::RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, bool useMipMap, const ImageXY* pImage)
			: RawTexture2D([&]()
			  {
				  D3D11_SUBRESOURCE_DATA* pData = nullptr;
				  D3D11_SUBRESOURCE_DATA data;
				  if (pImage)
				  {
					  Assert(pImage->getSize() == cpp::Vector2D<int>(width, height), "The size of Texture2D must be the same as the size of ImageXY.");

					  auto dxgiFormat = static_cast<DXGI_FORMAT>(m_format);
					  auto dimension = D3D11CreateFunctions::checkTextureColorDimension(dxgiFormat);
					  auto precision = D3D11CreateFunctions::checkTexturePrecision(dxgiFormat);
					  int byteStride = 0;
					  switch (precision)
					  {
					  case TexturePrecision::Float32:
					  case TexturePrecision::Float16:
						  data.pSysMem = pImage->create1DArray<float>(dimension, true).get();
						  byteStride = sizeof(float);
						  break;
					  case TexturePrecision::Int32:
						  data.pSysMem = pImage->create1DArray<int32_t>(dimension, true).get();
						  byteStride = sizeof(int32_t);
						  break;
					  case TexturePrecision::Int16:
						  data.pSysMem = pImage->create1DArray<int16_t>(dimension, true).get();
						  byteStride = sizeof(int16_t);
						  break;
					  case TexturePrecision::Int8:
						  data.pSysMem = pImage->create1DArray<int8_t>(dimension, true).get();
						  byteStride = sizeof(int8_t);
						  break;
					  case TexturePrecision::UInt32:
						  data.pSysMem = pImage->create1DArray<uint32_t>(dimension, true).get();
						  byteStride = sizeof(uint32_t);
						  break;
					  case TexturePrecision::UInt16:
						  data.pSysMem = pImage->create1DArray<uint16_t>(dimension, true).get();
						  byteStride = sizeof(uint16_t);
						  break;
					  case TexturePrecision::UInt8:
						  data.pSysMem = pImage->create1DArray<uint8_t>(dimension, true).get();
						  byteStride = sizeof(uint8_t);
						  break;
					  default:
						  Assert(false, "The given TexturePrecision is not supported.");
						  break;
					  }
					  data.SysMemPitch = m_size.x*dimension*byteStride;
					  data.SysMemSlicePitch = 0;

					  pData = &data;
				  }

				  D3D11_TEXTURE2D_DESC desc;
				  auto pDevice = Device::getDevice().Get();
				  cpp::com_ptr<ID3D11Texture2D> textureBuffer;
				  D3D11CreateFunctions::createTexture2DDesc(pDevice, width, height, static_cast<DXGI_FORMAT>(format), cpuAccessFlags, gpuAccessFlags, mostDetailedMipLevel, mostRoughedMipLevel, useMipMap, 1, RawTexture2DType::Texture, &desc);
				  
				  auto hr = D3D11CreateFunctions::createTexture2D(pDevice, desc, pData, textureBuffer.ReleaseAndGetAddressOf());
				  if(FAILED(hr))
				  {
					  throw COM_RUNTIME_ERROR(hr, "Failed to create a buffer for Texture2D.");
				  }

				  return textureBuffer;
			  }(),
			  mostDetailedMipLevel)
		{
		}
		RawTexture2D::RawTexture2D(const std::string& filename, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool forceSRGB)
			: RawTexture2D([&]()
						{
						   auto pDevice = Device::getDevice().Get();
						   DirectX::ScratchImage scratchImage;
						   cpp::com_ptr<ID3D11ShaderResourceView> cpSRV;
						   cpp::com_ptr<ID3D11Texture2D> textureBuffer;
						   auto hr = D3D11CreateFunctions::createScratchImage(pDevice, filename, &scratchImage);
						   if(FAILED(hr))
						   {
						 	   throw COM_RUNTIME_ERROR(hr, "Failed to create ScratchImage from " + filename + ".");
						   }
						   hr = D3D11CreateFunctions::createTexture2D(pDevice, scratchImage, RawTexture2DType::Texture, cpuAccessFlags, gpuAccessFlags, forceSRGB, textureBuffer.ReleaseAndGetAddressOf());
						   if(FAILED(hr))
						   {
							   throw COM_RUNTIME_ERROR(hr, "Failed to create a buffer for Texture2D from " + filename + ".");
						   }

						   return textureBuffer;
						}(),
						0)
		{
		}
		RawTexture2D::RawTexture2D(const std::string& filename, bool forceSRGB)
			: RawTexture2D(filename, CPUAccessFlags::none, GPUAccessFlags::RW, forceSRGB)
		{
		}
		RawTexture2D::RawTexture2D(int width, int height, TextureFormat format, const ImageXY* pImage)
			: RawTexture2D(width, height, format, CPUAccessFlags::none, GPUAccessFlags::RW, 0, 0, false, pImage)
		{
		}
		RawTexture2D::RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, const ImageXY* pImage)
			: RawTexture2D(width , height, format, cpuAccessFlags, gpuAccessFlags, 0, 0, false, pImage)
		{
		}
		RawTexture2D::RawTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, const ImageXY* pImage)
			: RawTexture2D(width, height, format, CPUAccessFlags::none, GPUAccessFlags::RW, mostDetailedMipLevel, mostRoughedMipLevel, pImage)
		{
		}

		RawTexture2D::RawTexture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, const ImageXY* pImage)
			: RawTexture2D(width, height, format, cpuAccessFlags, gpuAccessFlags, mostDetailedMipLevel, mostRoughedMipLevel, true, pImage)
		{
		}

		void RawTexture2D::saveTo(const std::string& filename, ImageFileFormat format)
		{
			std::string fileExtension = "";



			auto imageCodec = DirectX::WIC_CODEC_JPEG;
			switch (format)
			{
			case ImageFileFormat::jpg:
				imageCodec = DirectX::WIC_CODEC_JPEG;
				fileExtension = "jpg";
				break;
			case ImageFileFormat::png:
				imageCodec = DirectX::WIC_CODEC_PNG;
				fileExtension = "png";
				break;
			default:
				Assert(false, "The given ImageFileFormat is not supported.");
				break;
			}



			const auto& filenameWithExtension = filename+"."+fileExtension;
			wchar_t wFilename[MAX_TEXTURE_FILENAME_STR_SIZE];
			size_t len;
			mbstowcs_s(&len, wFilename, MAX_TEXTURE_FILENAME_STR_SIZE, filenameWithExtension.c_str(), _TRUNCATE);
	


			DirectX::ScratchImage image;
			auto hr = DirectX::CaptureTexture(Device::getDevice().Get(), Device::getDeviceContext().Get(), m_textureBuffer.Get(), image);
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to capture the screen.");
			}
			hr = DirectX::SaveToWICFile(image.GetImages()[0], DirectX::WIC_FLAGS_NONE, DirectX::GetWICCodec(imageCodec), wFilename);
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to save the captured image to " + filename + ".");
			}
		}

		void RawTexture2D::copy(const RawTexture2D& src)
		{
			Assert(m_id != src.m_id, "The source and destination resources must be different resources.");
			Assert((m_gpuAccessFlags == GPUAccessFlags::R && m_cpuAccessFlags == CPUAccessFlags::none) == false, "Immutable resources are not allowed to perform copy operations.");
			Assert(m_size == src.m_size, "The source and destination resources must have identical dimensions.");
			Assert(D3D11CreateFunctions::checkCompatibilityBetweenTwoTextureFormats(static_cast<DXGI_FORMAT>(m_format), static_cast<DXGI_FORMAT>(src.m_format)), "The source and destination resources must have compatible formats.");

			Device::getDeviceContext()->CopyResource(m_textureBuffer.Get(), src.m_textureBuffer.Get());
		}

		void RawTexture2D::write(const ImageXY& image)
		{
			if ((static_cast<int>(m_cpuAccessFlags) & static_cast<int>(CPUAccessFlags::W)) == 0) { return; }

			auto dxgiFormat = static_cast<DXGI_FORMAT>(m_format);
			auto dimension = D3D11CreateFunctions::checkTextureColorDimension(dxgiFormat);
			auto precision = D3D11CreateFunctions::checkTexturePrecision(dxgiFormat);

			switch (precision)
			{
			case TexturePrecision::Float32:
			case TexturePrecision::Float16:
				m_write<float>(image, dimension, true);
				break;
			case TexturePrecision::Int32:
				m_write<int32_t>(image, dimension, false);
				break;
			case TexturePrecision::Int16:
				m_write<int16_t>(image, dimension, false);
				break;
			case TexturePrecision::Int8:
				m_write<int8_t>(image, dimension, false);
				break;
			case TexturePrecision::UInt32:
				m_write<uint32_t>(image, dimension, false);
				break;
			case TexturePrecision::UInt16:
				m_write<uint16_t>(image, dimension, false);
				break;
			case TexturePrecision::UInt8:
				m_write<uint8_t>(image, dimension, false);
				break;
			default:
				Assert(false, "The given TexturePrecision is not supported.");
				break;
			}
		}

		std::shared_ptr<IShaderResourceMemoryAccessor> RawTexture2D::getSRV() const
		{
			return m_SRV;
		}

		std::shared_ptr<IShaderResourceMemoryAccessor> RawTexture2D::getUAV() const
		{
			return m_UAV;
		}

		cpp::Vector2D<int> RawTexture2D::getSize() const noexcept
		{
			return m_size;
		}

		void RawTexture2D::resolve()
		{
			if (isResolvedTexture())
			{
				m_resolve();
			}
		}

		void RawTexture2D::generateMipMaps()
		{
			m_SRV->generateMipMaps();
		}

		int RawTexture2D::getMostDetailedMipLevel() const noexcept
		{
			return m_mostDetailedMipLevel;
		}

		int RawTexture2D::getMostRoughedMipLevel() const noexcept
		{
			return m_mostRoughedMipLevel;
		}

		bool RawTexture2D::isResolvedTexture() const noexcept
		{
			return m_isResolvedTexture;
		}
	}
}