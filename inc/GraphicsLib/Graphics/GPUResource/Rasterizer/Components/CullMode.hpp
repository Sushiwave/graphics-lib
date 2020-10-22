#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class CullMode
	{
		none =
#ifdef CONTEXT_D3D11
		D3D11_CULL_NONE,
#endif
		front =
#ifdef CONTEXT_D3D11
		D3D11_CULL_FRONT,
#endif
		back =
#ifdef CONTEXT_D3D11
		D3D11_CULL_BACK,
#endif
	};
}