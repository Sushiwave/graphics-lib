#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IDefaultTexture2D.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>





namespace cg
{
	namespace d3d11
	{
		class DefaultTexture2D
			: public Texture2D,
			  public IDefaultTexture2D
		{
		public:
			DefaultTexture2D() = default;
			DefaultTexture2D(const std::string& filename, bool forceSRGB = false);
			DefaultTexture2D(int width, int height, TextureFormat format, ImageXY* pImage = nullptr);
			DefaultTexture2D(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage = nullptr);
			
			DefaultTexture2D(const RawTexture2D& rawTexture);

			virtual ~DefaultTexture2D() = default;

			void resolve() override;

			void copy(const std::shared_ptr<ITexture2D> dest) override;
			void write(const ImageXY& image) override;
		};
	}
}