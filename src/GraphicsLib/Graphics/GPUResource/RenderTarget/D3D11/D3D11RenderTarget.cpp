#include <Graphics/GPUResource/RenderTarget/D3D11/D3D11RenderTarget.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/DepthStencilBuffer/D3D11/D3D11DepthStencilBuffer.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/D3D11DefaultTexture2D.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	constexpr ID3D11RenderTargetView* emptyRenderTargetView[1] = { nullptr };





	namespace d3d11
	{
		auto createRenderTargetBufferFromRenderTargetView = [&](ID3D11RenderTargetView* view)
		{
			cpp::com_ptr<ID3D11Texture2D> buffer;

			auto hr = D3D11CreateFunctions::createRenderTargetBufferFromRenderTargetView(view, buffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create RenderTargetView.");
			}

			return buffer;
		};
		auto createRenderTargetBuffer = [&](int width, int height, TextureFormat format, int mostDetailedMip, int mostRoughedMip, bool useMipMap, int sampleCount)
		{
			cpp::com_ptr<ID3D11Texture2D> buffer;
			auto pDevice = Device::getDevice().Get();
			D3D11_TEXTURE2D_DESC desc;

			D3D11CreateFunctions::createTexture2DDesc(pDevice, width, height, static_cast<DXGI_FORMAT>(format), CPUAccessType::none, GPUAccessType::RW, mostDetailedMip, mostRoughedMip, useMipMap, sampleCount, RawTexture2DType::RenderTarget, &desc);
			auto hr = D3D11CreateFunctions::createTexture2D(pDevice, desc, nullptr, buffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create a buffer for RenderTarget.");
			}

			return buffer;
		};
		auto createResolvedTexture = [&](cpp::com_ptr<ID3D11Texture2D> renderTargetBuffer, int mostDetailedMip)->cpp::com_ptr<ID3D11Texture2D>
		{
			auto desc = D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get());

			if (desc.SampleDesc.Count <= 1) { return nullptr; }

			cpp::com_ptr<ID3D11Texture2D> buffer;
			D3D11_TEXTURE2D_DESC resolveTexDesc;
			auto pDevice = Device::getDevice().Get();
			D3D11CreateFunctions::createTexture2DDesc(pDevice, desc.Width, desc.Height, desc.Format, CPUAccessType::none, GPUAccessType::RW, mostDetailedMip, mostDetailedMip - desc.MipLevels + 1, desc.MiscFlags == D3D11_RESOURCE_MISC_GENERATE_MIPS, 1, RawTexture2DType::RenderTarget, &resolveTexDesc);
			auto hr = D3D11CreateFunctions::createTexture2D(pDevice, resolveTexDesc, nullptr, buffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create ResolvedTexture.");
			}

			return buffer;
		};



		cpp::com_ptr<ID3D11RenderTargetView> RenderTarget::getRenderTargetView() const noexcept
		{
			return m_renderTargetView;
		}



		RenderTarget::RenderTarget(int width, int height, TextureFormat format, int mostDetailedMip, int mostRoughedMip, int sampleCount)
			: d3d11::RenderTarget(createRenderTargetBuffer(width, height, format, mostDetailedMip, mostRoughedMip, true, sampleCount), mostDetailedMip)
		{
		}
		RenderTarget::RenderTarget(int width, int height, TextureFormat format, int sampleCount)
			: d3d11::RenderTarget(createRenderTargetBuffer(width, height, format, 0, 0, false, sampleCount), 0)
		{
		}
		RenderTarget::RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, int mostDetailedMipLevel)
			: d3d11::RenderTarget(renderTargetBuffer,
								  createResolvedTexture(renderTargetBuffer, mostDetailedMipLevel),
								  [=]()
								  {
									  cpp::com_ptr<ID3D11RenderTargetView> renderTargetView;
									  auto hr = D3D11CreateFunctions::createRenderTargetView(Device::getDevice().Get(), renderTargetBuffer.Get(), D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get()).Format, renderTargetView.ReleaseAndGetAddressOf());
									  if(FAILED(hr))
									  {
										  throw COM_RUNTIME_ERROR(hr, "Failed to create RenderTargetView.");
									  }
									 return renderTargetView;
								  }(),
								  D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get()).Format,
								  mostDetailedMipLevel)
		{
		}
		RenderTarget::RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, const cpp::com_ptr<ID3D11Texture2D>& resolvedTextureBuffer, const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetView, DXGI_FORMAT format, int mostDetailedMipLevel)
			: cg::RenderTarget([&](std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer)
							   {
							       ID3D11DepthStencilView* d3d11DepthStencil = nullptr;
								   if (depthStencilBuffer)
								   {
									   d3d11DepthStencil = std::dynamic_pointer_cast<d3d11::DepthStencilBuffer>(depthStencilBuffer)->getDepthStencilView().Get();
								   }
								   Device::getDeviceContext()->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), d3d11DepthStencil);
							   },
							   [&](const ClearColor& clearColor)
							   {
			 					   Device::getDeviceContext()->ClearRenderTargetView(m_renderTargetView.Get(), clearColor.data());
							   },
							   resolvedTextureBuffer ?
							   std::make_shared<DefaultTexture2D>(RawTexture2D(resolvedTextureBuffer, true, mostDetailedMipLevel, [=]() { Device::getDeviceContext()->ResolveSubresource(resolvedTextureBuffer.Get(), 0, renderTargetBuffer.Get(), 0, format); })) :
							   std::make_shared<DefaultTexture2D>(RawTexture2D(renderTargetBuffer, mostDetailedMipLevel)),
							   resolvedTextureBuffer ?
							   std::make_shared<DefaultTexture2D>(RawTexture2D(renderTargetBuffer, static_cast<TextureFormat>(format), mostDetailedMipLevel)) :
							   nullptr,
							   D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get()).SampleDesc.Count,
							   D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get()).SampleDesc.Quality),
							   m_renderTargetView(renderTargetView)
		{
		}
		RenderTarget::RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetView, int mostDetailedMipLevel)
			: d3d11::RenderTarget(renderTargetBuffer, createResolvedTexture(renderTargetBuffer, mostDetailedMipLevel), renderTargetView, D3D11CreateFunctions::fetchTexture2DDescFrom(renderTargetBuffer.Get()).Format, mostDetailedMipLevel)
		{
		}
		RenderTarget::RenderTarget(const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetView, int mostDetailedMipLevel)
			: d3d11::RenderTarget(createRenderTargetBufferFromRenderTargetView(renderTargetView.Get()), renderTargetView, mostDetailedMipLevel)
		{
		}
	}
}
