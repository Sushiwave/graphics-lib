#include "D3D11DynamicTexture2D.hpp"





namespace cg
{
	namespace d3d11
	{
		DynamicTexture2D::DynamicTexture2D(const std::string& filename, bool forceSRGB)
			: Texture2D(filename, CPUAccessType::W, GPUAccessType::R, forceSRGB)
		{
		}
		DynamicTexture2D::DynamicTexture2D(int width, int height, TextureFormat format, ImageXY* pImage)
			: Texture2D(width, height, format, CPUAccessType::W, GPUAccessType::R, pImage)
		{
		}
		DynamicTexture2D::DynamicTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage)
			: Texture2D(width, height, format, CPUAccessType::W, GPUAccessType::R, mostDetailedMipLevel, mostRoughedMipLevel, pImage)
		{
		}
		DynamicTexture2D::DynamicTexture2D(const RawTexture2D& rawTexture)
			: Texture2D(rawTexture)
		{
		}
		void DynamicTexture2D::resolve()
		{
			m_texture.resolve();
		}
		void DynamicTexture2D::copy(const std::shared_ptr<ITexture2D> dest)
		{
			auto d3d11Dest = std::dynamic_pointer_cast<Texture2D>(dest);
			m_texture.copy(d3d11Dest->getRawTexture());
		}
		void DynamicTexture2D::write(const ImageXY& image)
		{
			m_texture.write(image);
		}
	}
}
