#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ShaderResourceView.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>






#define D3D11SetShaderResources(SHADER) [=](UINT unit){ Device::getDeviceContext()->SHADER##SetShaderResources(unit, 1, cpD3DSRV.GetAddressOf()); }





namespace cg
{
	namespace d3d11
	{
		ShaderResourceView::ShaderResourceView(const ID& id, ShaderResourceType type, const cpp::com_ptr<ID3D11ShaderResourceView>& cpD3DSRV)
			: ShaderResourceMemoryAccessor
			  (
				  id,
				  type,
				  GPUAccessType::R,
				  {
					  { ShaderStage::vs, D3D11SetShaderResources(VS) },
					  { ShaderStage::hs, D3D11SetShaderResources(HS) },
					  { ShaderStage::ds, D3D11SetShaderResources(DS) },
					  { ShaderStage::gs, D3D11SetShaderResources(GS) },
					  { ShaderStage::ps, D3D11SetShaderResources(PS) },
					  { ShaderStage::cs, D3D11SetShaderResources(CS) }
				  }
		  	  ),
			  m_view(cpD3DSRV)
		{
		}
		void ShaderResourceView::generateMipMaps()
		{
			Device::getDeviceContext()->GenerateMips(m_view.Get());
		}
		ID3D11ShaderResourceView* ShaderResourceView::getRawView() const
		{
			return m_view.Get();
		}
	}
}
