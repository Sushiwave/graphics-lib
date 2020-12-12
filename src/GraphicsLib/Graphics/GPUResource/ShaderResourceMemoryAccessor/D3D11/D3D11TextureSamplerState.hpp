#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class TextureSamplerState
			: public ShaderResourceMemoryAccessor
		{
		public:
			TextureSamplerState() = default;
			virtual ~TextureSamplerState() = default;
			TextureSamplerState(const cpp::com_ptr<ID3D11SamplerState>& cpD3DSampler);
		};
	}
}
