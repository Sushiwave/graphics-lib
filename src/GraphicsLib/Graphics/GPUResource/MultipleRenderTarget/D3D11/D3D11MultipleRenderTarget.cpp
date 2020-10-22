#include <Graphics/GPUResource/MultipleRenderTarget/D3D11/D3D11MultipleRenderTarget.hpp>
#include <Graphics/GPUResource/RenderTarget/D3D11/D3D11RenderTarget.hpp>
#include <Graphics/GPUResource/DepthStencilBuffer/D3D11/D3D11DepthStencilBuffer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		MultipleRenderTarget::MultipleRenderTarget(const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList)
			: cg::MultipleRenderTarget([&](int count, std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer)
			  {
				  auto d3d11DepthStencilView = std::dynamic_pointer_cast<d3d11::DepthStencilBuffer>(depthStencilBuffer);
				  Device::getDeviceContext()->OMSetRenderTargets(static_cast<UINT>(m_renderTargetList.size()), m_renderTargetViewArray.get(), d3d11DepthStencilView->getDepthStencilView().Get());
			  },
			  renderTargetList)
		{
			auto count = renderTargetList.size();
			m_renderTargetViewArray = std::shared_ptr<ID3D11RenderTargetView*>(new ID3D11RenderTargetView*[count], std::default_delete<ID3D11RenderTargetView*[]>());
			for (size_t i = 0; i < count; ++i)
			{
				auto d3d11RenderTarget = std::dynamic_pointer_cast<d3d11::RenderTarget>(renderTargetList[i]);
				m_renderTargetViewArray.get()[i] = d3d11RenderTarget->getRenderTargetView().Get();
			}
		}

		MultipleRenderTarget& MultipleRenderTarget::operator=(const MultipleRenderTarget& other)
		{
			auto count = other.m_renderTargetList.size();

			if (count > 0)
			{
				m_renderTargetViewArray = std::shared_ptr<ID3D11RenderTargetView*>(new ID3D11RenderTargetView*[count], std::default_delete<ID3D11RenderTargetView*[]>());
				for (size_t i = 0; i < count; ++i)
				{
					m_renderTargetViewArray.get()[i] = other.m_renderTargetViewArray.get()[i];
				}
			}

			return *this;
		}
	}
}