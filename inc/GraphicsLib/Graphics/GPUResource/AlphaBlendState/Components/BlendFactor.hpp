#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class BlendFactor
	{
#ifdef CONTEXT_D3D11
		zero = D3D11_BLEND_ZERO,
		one = D3D11_BLEND_ONE,
		blendFactor = D3D11_BLEND_BLEND_FACTOR,
		invBlendFactor = D3D11_BLEND_INV_BLEND_FACTOR,
		srcColor = D3D11_BLEND_SRC_COLOR,
		invSrcColor = D3D11_BLEND_INV_SRC_COLOR,
		destColor = D3D11_BLEND_DEST_COLOR,
		invDestColor = D3D11_BLEND_INV_DEST_COLOR,
		srcAlpha = D3D11_BLEND_SRC_ALPHA,
		invSrcAlpha = D3D11_BLEND_INV_SRC_ALPHA,
		destAlpha = D3D11_BLEND_DEST_ALPHA,
		invDestAlpha = D3D11_BLEND_INV_DEST_ALPHA
#endif
	};
}