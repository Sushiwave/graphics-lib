#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Base/IResolvable.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>




namespace cg
{
	class IResolvableTexture2D
		: public IResolvable,
		  public virtual ITexture2D
	{
	};
}
