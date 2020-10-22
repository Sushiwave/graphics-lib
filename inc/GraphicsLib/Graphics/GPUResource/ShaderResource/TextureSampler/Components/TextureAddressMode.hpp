#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class TextureAddressMode
	{
		wrap
#ifdef CONTEXT_D3D11
		= D3D11_TEXTURE_ADDRESS_WRAP,
#endif
		mirror
#ifdef CONTEXT_D3D11
		= D3D11_TEXTURE_ADDRESS_MIRROR,
#endif
		clamp
#ifdef CONTEXT_D3D11
		= D3D11_TEXTURE_ADDRESS_CLAMP,
#endif
		border
#ifdef CONTEXT_D3D11
		= D3D11_TEXTURE_ADDRESS_BORDER
#endif
	};
}