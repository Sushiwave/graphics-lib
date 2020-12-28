#include <GraphicsLib/Context.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/Base/D3D11Texture2D.hpp>
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11ShaderResourceView.hpp>
#include <Graphics/GPUResource/RenderTarget/D3D11/D3D11RenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/MainRenderTarget/MainRenderTarget.hpp>
#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/ImGui/ImGuiImage.hpp>
#include <Graphics/GPUResource/DepthStencilBuffer/D3D11/D3D11DepthStencilBuffer.hpp>



namespace ImGui
{
	void Image(std::shared_ptr<cg::ITexture2D> texture, const ImVec2& size)
	{
		void* textureID;

#ifdef CONTEXT_D3D11
		textureID = static_cast<void*>(std::dynamic_pointer_cast<cg::d3d11::ShaderResourceView>(std::dynamic_pointer_cast<cg::d3d11::Texture2D>(texture)->getRawTexture().getSRV())->getRawView());
#endif

		ImGui::Image(textureID, size);
	}

	void Image(std::shared_ptr<cg::IRenderTarget> renderTarget, const ImVec2& size)
	{
		if (renderTarget->getID() == cg::GPUStateViewer::view().renderTarget.id)
		{
#ifdef CONTEXT_D3D11
			cg::d3d11::RenderTarget::release();
#endif
		}
		
		ImGui::Image(renderTarget->getRenderingResult(), size);
	}

	void Image(std::shared_ptr<cg::IMultipleRenderTargets> mrt, int index, const ImVec2& size)
	{
		if (mrt->getID() == cg::GPUStateViewer::view().renderTarget.id)
		{
#ifdef CONTEXT_D3D11
			cg::d3d11::RenderTarget::release();
#endif
		}
		ImGui::Image(mrt->getRenderingResult(index), size);
	}

	void ImageDepth(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const ImVec2& size)
	{
		if (depthStencilBuffer->getID() == cg::GPUStateViewer::view().depthStencilBuffer.id)
		{
#ifdef CONTEXT_D3D11
			cg::d3d11::RenderTarget::release();
#endif
		}

		ImGui::Image(depthStencilBuffer->getDepthBufferTexture(), size);
	}

	void ImageStencil(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const ImVec2& size)
	{
		if (depthStencilBuffer->getID() == cg::GPUStateViewer::view().depthStencilBuffer.id)
		{
#ifdef CONTEXT_D3D11
			cg::d3d11::RenderTarget::release();
#endif
		}

		ImGui::Image(depthStencilBuffer->getStencilBufferTexture(), size);
	}
}
