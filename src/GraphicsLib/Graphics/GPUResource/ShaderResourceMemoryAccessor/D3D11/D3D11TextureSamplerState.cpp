#include "D3D11TextureSamplerState.hpp"
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>





#define D3D11SetSamplers(SHADER) [=](UINT unit){ Device::getDeviceContext()->SHADER##SetSamplers(unit, 1, cpD3DSampler.GetAddressOf()); }





namespace cg
{
	namespace d3d11
	{
		TextureSamplerState::TextureSamplerState(const ID& id, const cpp::com_ptr<ID3D11SamplerState>& cpD3DSampler)
			: ShaderResourceMemoryAccessor
			(
				id,
				ShaderResourceType::TextureSampler,
				GPUAccessType::R,
				{
					{ ShaderStage::vs, D3D11SetSamplers(VS) },
					{ ShaderStage::hs, D3D11SetSamplers(HS) },
					{ ShaderStage::ds, D3D11SetSamplers(DS) },
					{ ShaderStage::gs, D3D11SetSamplers(GS) },
					{ ShaderStage::ps, D3D11SetSamplers(PS) },
					{ ShaderStage::cs, D3D11SetSamplers(CS) }
				}
			)
		{
		}
	}
}
