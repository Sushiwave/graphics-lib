#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ConstantBufferView.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>





#define D3D11SetConstantBuffers(SHADER) [&](UINT unit){ Device::getDeviceContext()->SHADER##SetConstantBuffers(unit, 1, cpD3DBuffer.GetAddressOf()); }





namespace cg
{
	namespace d3d11
	{
		ConstantBufferView::ConstantBufferView(const cpp::com_ptr<ID3D11Buffer>& cpD3DBuffer)
			: ShaderResourceMemoryAccessor
			(
				ShaderResourceType::ConstantBuffer,
				GPUAccessType::R,
				{
					{ ShaderStage::vs, D3D11SetConstantBuffers(VS) },
					{ ShaderStage::hs, D3D11SetConstantBuffers(HS) },
					{ ShaderStage::ds, D3D11SetConstantBuffers(DS) },
					{ ShaderStage::gs, D3D11SetConstantBuffers(GS) },
					{ ShaderStage::ps, D3D11SetConstantBuffers(PS) },
					{ ShaderStage::cs, D3D11SetConstantBuffers(CS) }
				}
			)
		{
		}
	}
}