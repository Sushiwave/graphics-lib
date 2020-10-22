#include "D3D11ImmutableTexture2D.hpp"





namespace cg
{
	namespace d3d11
	{
		ImmutableTexture2D::ImmutableTexture2D(const std::string& filename, bool forceSRGB)
			: Texture2D(filename, CPUAccessFlags::none, GPUAccessFlags::R, forceSRGB)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format)
			: Texture2D(width, height, format, CPUAccessFlags::none, GPUAccessFlags::R, &image)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel)
			: Texture2D(width, height, format, CPUAccessFlags::none, GPUAccessFlags::R, mostDetailedMipLevel, mostRoughedMipLevel, &image)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(const RawTexture2D& rawTexture)
			: Texture2D(rawTexture)
		{
		}
	}
}
