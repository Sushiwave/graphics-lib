#pragma once
#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/IShaderResource.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>

#include <memory>





namespace cg
{
	class IImmutableTexture2D
		: public virtual ITexture2D
	{
	};
}
