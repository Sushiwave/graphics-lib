#pragma once
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/RenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/TextureFormat.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class RenderTarget
			: public cg::RenderTarget
		{
		private:
			cpp::com_ptr<ID3D11RenderTargetView> m_renderTargetView;
		private:
			RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, const cpp::com_ptr<ID3D11Texture2D>& resolvedTextureBuffer, const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetViewt, DXGI_FORMAT format, int mostDetailedMipLevel);
			RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetViewt, int mostDetailedMipLevel);
		public:
			RenderTarget() = default;
			RenderTarget(int width, int height, TextureFormat format, int mostDetailedMipLevel, int mostRoughedMipLevel, int sampleCount);
			RenderTarget(int width, int height, TextureFormat format, int sampleCount);

			RenderTarget(const cpp::com_ptr<ID3D11Texture2D>& renderTargetBuffer, int mostDetailedMipLevel);
			RenderTarget(const cpp::com_ptr<ID3D11RenderTargetView>& renderTargetView, int mostDetailedMipLevel);

			virtual ~RenderTarget() = default;

			[[nodiscard]] cpp::com_ptr<ID3D11RenderTargetView> getRenderTargetView() const noexcept;
		};
	}
}