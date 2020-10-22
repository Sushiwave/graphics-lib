#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class TextureFilter
	{
		point
#ifdef CONTEXT_D3D11
		= D3D11_FILTER_MIN_MAG_MIP_POINT,
#endif
		bilinear
#ifdef CONTEXT_D3D11
		= D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
#endif
		trilinear
#ifdef CONTEXT_D3D11
		= D3D11_FILTER_MIN_MAG_MIP_LINEAR,
#endif
		anisotropic
#ifdef CONTEXT_D3D11
		= D3D11_FILTER_ANISOTROPIC
#endif
	};
}