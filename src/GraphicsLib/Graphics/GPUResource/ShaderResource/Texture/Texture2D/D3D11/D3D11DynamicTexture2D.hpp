#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IDynamicTexture2D.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>





namespace cg
{
	namespace d3d11
	{
		class DynamicTexture2D
			: public Texture2D,
			  public IDynamicTexture2D
		{
		public:
			DynamicTexture2D() = default;
			DynamicTexture2D(const std::string& filename, bool forceSRGB = false);
			DynamicTexture2D(int width, int height, TextureFormat format, ImageXY* pImage);
			DynamicTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage);

			DynamicTexture2D(const RawTexture2D& rawTexture);

			virtual ~DynamicTexture2D() = default;

			void resolve() override;

			void copy(const std::shared_ptr<ITexture2D> dest) override;
			void write(const ImageXY& image) override;
		};
	}
}