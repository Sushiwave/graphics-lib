#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class ComparisonFunction
	{
		equal =
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_EQUAL,
#endif
		notEqual =
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_NOT_EQUAL,
#endif

		less =
#ifdef CONTEXT_D3D11 
		D3D11_COMPARISON_LESS,
#endif
		lessEqual = 
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_LESS_EQUAL,
#endif

		greater = 
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_GREATER,
#endif
		greaterEqual = 
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_GREATER_EQUAL,
#endif

		never = 
#ifdef CONTEXT_D3D11 
		D3D11_COMPARISON_NEVER,
#endif
		always =
#ifdef CONTEXT_D3D11
		D3D11_COMPARISON_ALWAYS,
#endif
	};
}