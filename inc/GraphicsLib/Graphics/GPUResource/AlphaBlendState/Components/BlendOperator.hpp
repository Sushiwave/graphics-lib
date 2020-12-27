#pragma once
#include <d3d11.h>
#include <GraphicsLib/Context.hpp>




namespace cg
{
	enum class BlendOperator
	{
#ifdef CONTEXT_D3D11
		add = D3D11_BLEND_OP_ADD,
		subtract = D3D11_BLEND_OP_SUBTRACT,
		min = D3D11_BLEND_OP_MIN,
		max = D3D11_BLEND_OP_MAX,
#endif
	};
}
