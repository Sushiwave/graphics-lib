#pragma once
#include <GraphicsLib/Context.hpp>

#include <d3d11.h>





namespace cg
{
	enum class TextureFormat
	{
#ifdef CONTEXT_D3D11
		UNKNOWN = DXGI_FORMAT_UNKNOWN,
		
		R32G32B32A32_FLOAT = DXGI_FORMAT_R32G32B32A32_FLOAT,
		R32G32B32A32_SINT  = DXGI_FORMAT_R32G32B32A32_SINT,
		R32G32B32A32_UINT  = DXGI_FORMAT_R32G32B32A32_UINT,

		R32G32B32_FLOAT = DXGI_FORMAT_R32G32B32_FLOAT,
		R32G32B32_SINT  = DXGI_FORMAT_R32G32B32_SINT,
		R32G32B32_UINT  = DXGI_FORMAT_R32G32B32_UINT,

		R32G32_FLOAT = DXGI_FORMAT_R32G32_FLOAT,
		R32G32_SINT  = DXGI_FORMAT_R32G32_SINT,
		R32G32_UINT  = DXGI_FORMAT_R32G32_UINT,

		R16G16B16A16_FLOAT = DXGI_FORMAT_R16G16B16A16_FLOAT,
		R16G16B16A16_SINT  = DXGI_FORMAT_R16G16B16A16_SINT,
		R16G16B16A16_UINT  = DXGI_FORMAT_R16G16B16A16_UINT,
		R16G16B16A16_SNORM = DXGI_FORMAT_R16G16B16A16_SNORM,
		R16G16B16A16_UNORM = DXGI_FORMAT_R16G16B16A16_UNORM,

		R8G8B8A8_SINT  = DXGI_FORMAT_R8G8B8A8_SINT,
		R8G8B8A8_UINT  = DXGI_FORMAT_R8G8B8A8_UINT,
		R8G8B8A8_SNORM = DXGI_FORMAT_R8G8B8A8_SNORM,
		R8G8B8A8_UNORM = DXGI_FORMAT_R8G8B8A8_UNORM,

		R16G16_FLOAT = DXGI_FORMAT_R16G16_FLOAT,
		R16G16_SINT  = DXGI_FORMAT_R16G16_SINT,
		R16G16_UINT  = DXGI_FORMAT_R16G16_UINT,
		R16G16_SNORM = DXGI_FORMAT_R16G16_SNORM,
		R16G16_UNORM = DXGI_FORMAT_R16G16_UNORM,

		R32_FLOAT = DXGI_FORMAT_R32_FLOAT,
		R32_SINT  = DXGI_FORMAT_R32_SINT,
		R32_UINT  = DXGI_FORMAT_R32_UINT,

		R16_FLOAT = DXGI_FORMAT_R16_FLOAT,
		R16_SINT  = DXGI_FORMAT_R16_SINT,
		R16_UINT  = DXGI_FORMAT_R16_UINT,

		R32G32B32A32_TYPELESS    = DXGI_FORMAT_R32G32B32A32_TYPELESS,
		R16G16B16A16_TYPELESS    = DXGI_FORMAT_R16G16B16A16_TYPELESS,
		R8G8B8A8_TYPELESS        = DXGI_FORMAT_R8G8B8A8_TYPELESS,
		R16G16_TYPELESS          = DXGI_FORMAT_R16G16_TYPELESS,
		R32_TYPELESS             = DXGI_FORMAT_R32_TYPELESS,
		R16_TYPELESS             = DXGI_FORMAT_R16_TYPELESS,
		R32_FLOAT_X8X24_TYPELESS = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
		R24_UNORM_X8_TYPELESS    = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
		X32_TYPELESS_G8X24_UINT  = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
		X24_TYPELESS_G8_UINT     = DXGI_FORMAT_X24_TYPELESS_G8_UINT,

		D32_FLOAT            = DXGI_FORMAT_D32_FLOAT,
		D32_FLOAT_S8X24_UINT = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
		D16_UNORM            = DXGI_FORMAT_D16_UNORM,
		D24_UNORM_S8_UINT    = DXGI_FORMAT_D24_UNORM_S8_UINT,
#endif
	};
}
