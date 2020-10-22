#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/DepthStencilBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Components/TextureFormat.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class Texture2D;
	}
}




namespace cg
{
	namespace d3d11
	{
		class DepthStencilBuffer
			: public cg::DepthStencilBuffer
		{
		private:
			cpp::com_ptr<ID3D11DepthStencilView> m_depthStencilView;
		private:
			DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dFormat, int sampleCount, int qualityLevel);
			DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dFormat, DXGI_FORMAT d3dDepthBufferTextureForamt, DXGI_FORMAT d3dStencilBufferTextureForamt, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, int sampleCount, int qualityLevel);
			DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dDepthTextureForamt, DXGI_FORMAT d3dStencilTextureForamt, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel);
			DepthStencilBuffer(const cpp::Vector2D<int>& size, std::shared_ptr<IDefaultTexture2D> depthTextureMS, std::shared_ptr<IDefaultTexture2D> stencilTextureMS, DXGI_FORMAT d3dDepthTextureFormat, DXGI_FORMAT d3dStencilTextureFormat, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel);
			DepthStencilBuffer(const cpp::Vector2D<int>& size, std::shared_ptr<IDefaultTexture2D> depthTextureMS, std::shared_ptr<IDefaultTexture2D> stencilTextureMS, std::shared_ptr<IDefaultTexture2D> depthTexture, std::shared_ptr<IDefaultTexture2D> stencilTexture, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel);
		public:
			DepthStencilBuffer() = default;
			DepthStencilBuffer(int width, int height, TextureFormat format, int sampleCount, int qualityLevel);
			virtual ~DepthStencilBuffer() = default;

			[[nodiscard]] cpp::com_ptr<ID3D11DepthStencilView> getDepthStencilView() const;
		};
	}
}
