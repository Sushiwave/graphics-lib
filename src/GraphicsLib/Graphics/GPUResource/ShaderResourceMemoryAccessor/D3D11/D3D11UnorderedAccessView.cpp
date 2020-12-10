#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11UnorderedAccessView.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>





#define D3D11SetUnorderedAccessViews(SHADER) [=](UINT unit){ Device::getDeviceContext()->SHADER##SetUnorderedAccessViews(unit, 1, cpD3DUAV.GetAddressOf(), nullptr); }





namespace cg
{
	namespace d3d11
	{
		UnorderedAccessView::UnorderedAccessView(const ID& id, ShaderResourceType type, const cpp::com_ptr<ID3D11UnorderedAccessView>& cpD3DUAV)
			: ShaderResourceMemoryAccessor
			(
				id,
				type,
				GPUAccessType::RW,
				{ { ShaderStage::cs, D3D11SetUnorderedAccessViews(CS) } }
			)
		{
		}
	}
}
