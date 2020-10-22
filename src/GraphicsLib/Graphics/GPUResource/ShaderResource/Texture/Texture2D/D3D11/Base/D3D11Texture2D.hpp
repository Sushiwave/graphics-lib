#pragma once
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Components/RawTexture/D3D11RawTexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>





namespace cg
{
	namespace d3d11
	{
		class Texture2D
			: public ShaderResource,
			  public virtual ITexture2D
		{
		protected:
			RawTexture2D m_texture;
		public:
			Texture2D() noexcept = default;
			Texture2D(const std::string& filename, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, bool forceSRGB = false);
			Texture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, ImageXY* pImage = nullptr);
			Texture2D(int width, int height, TextureFormat format, CPUAccessFlags cpuAccessFlags, GPUAccessFlags gpuAccessFlags, int mostDetailedMipLevel, int mostRoughedMipLevel, ImageXY* pImage = nullptr);

			Texture2D(const RawTexture2D& rawTexture);

			virtual ~Texture2D() = default;

			[[nodiscard]] int getMostDetailedMipLevel() const override;
			[[nodiscard]] int getMostRoughedMipLevel() const override;

			[[nodiscard]] cpp::Vector2D<int> getSize() const override;

			void generateMipMaps() override;

			[[nodiscard]] bool isResolvedTexture() const override;

			void saveTo(const std::string& filename, ImageFileFormat format) override;

			void set(ShaderStage stage, int unit, GPUAccessFlags usage) override;

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;

			[[nodiscard]] RawTexture2D getRawTexture() const;
		};
	}
}