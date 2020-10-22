#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IImmutableTexture2D.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>





namespace cg
{
	namespace d3d11
	{
		class ImmutableTexture2D
			: public Texture2D,
			  public IImmutableTexture2D
		{
		public:
			ImmutableTexture2D() = default;
			ImmutableTexture2D(const std::string& filename, bool forceSRGB = false);
			ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format);
			ImmutableTexture2D(ImageXY image, int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel);

			ImmutableTexture2D(const RawTexture2D& rawTexture);
			
			virtual ~ImmutableTexture2D() = default;
		};
	}
}