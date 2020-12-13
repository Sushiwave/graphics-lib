#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessType.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/IResolvableTexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/ImageXY.hpp>

#include <memory>





namespace cg
{
	class IDefaultTexture2D
		: public virtual IResolvableTexture2D
	{
	public:
		virtual void copy(const std::shared_ptr<ITexture2D> dest) = 0;
		virtual void write(const ImageXY& image) = 0;
	};
}
