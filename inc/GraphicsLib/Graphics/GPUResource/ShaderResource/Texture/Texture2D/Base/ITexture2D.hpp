#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/ImageFileFormat.hpp>

#include <memory>





namespace cg
{
	class ITexture2D
		: public virtual IShaderResource
	{
	public:
		[[nodiscard]] virtual int getMostDetailedMipLevel() const = 0;
		[[nodiscard]] virtual int getMostRoughedMipLevel() const = 0;

		[[nodiscard]] virtual cpp::Vector2D<int> getSize() const = 0;

		virtual void generateMipMaps() = 0;

		[[nodiscard]] virtual bool isResolvedTexture() const = 0;

		virtual void set(ShaderStage stage, int unit, GPUAccessFlags usage) = 0;

		virtual void saveTo(const std::string& filename, ImageFileFormat format) = 0;
	};
}
