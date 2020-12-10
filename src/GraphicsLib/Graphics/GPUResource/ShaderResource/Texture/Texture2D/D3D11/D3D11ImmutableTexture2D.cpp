#include "D3D11ImmutableTexture2D.hpp"





namespace cg
{
	namespace d3d11
	{
		ImmutableTexture2D::ImmutableTexture2D(const std::string& filename, bool forceSRGB)
			: Texture2D(filename, CPUAccessType::none, GPUAccessType::R, forceSRGB)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format)
			: Texture2D(width, height, format, CPUAccessType::none, GPUAccessType::R, &image)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel)
			: Texture2D(width, height, format, CPUAccessType::none, GPUAccessType::R, mostDetailedMipLevel, mostRoughedMipLevel, &image)
		{
		}
		ImmutableTexture2D::ImmutableTexture2D(const RawTexture2D& rawTexture)
			: Texture2D(rawTexture)
		{
		}
	}
}
