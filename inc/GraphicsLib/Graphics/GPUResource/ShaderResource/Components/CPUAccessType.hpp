#pragma once
#include <d3d11.h>





namespace cg
{
	enum class CPUAccessType
		: UINT
	{
		none = 0,
		R = D3D11_CPU_ACCESS_READ,
		W = D3D11_CPU_ACCESS_WRITE,
		RW = R | W,
	};
}