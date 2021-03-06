#include "D3D11DefaultTexture2D.hpp"





namespace cg
{
	namespace d3d11
	{
		DefaultTexture2D::DefaultTexture2D(const std::string& filename, bool forceSRGB)
			: Texture2D(filename, CPUAccessType::W, GPUAccessType::RW, forceSRGB)
		{
		}
		DefaultTexture2D::DefaultTexture2D(int width, int height, TextureFormat format, ImageXY* pImage)
			: Texture2D(width, height, format, CPUAccessType::W, GPUAccessType::RW, pImage)
		{
		}
		DefaultTexture2D::DefaultTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage)
			: Texture2D(width, height, format, CPUAccessType::W, GPUAccessType::RW, mostDetailedMipLevel, mostRoughedMipLevel, pImage)
		{
		}
		DefaultTexture2D::DefaultTexture2D(const RawTexture2D& rawTexture)
			: Texture2D(rawTexture)
		{
		}
		void DefaultTexture2D::resolve()
		{
			m_texture.resolve();
		}
		void DefaultTexture2D::copy(const std::shared_ptr<ITexture2D> dest)
		{
			auto d3d11Dest = std::dynamic_pointer_cast<Texture2D>(dest);
			m_texture.copy(d3d11Dest->getRawTexture());
		}
		void DefaultTexture2D::write(const ImageXY& image)
		{
			m_texture.write(image);
		}
	}
}
