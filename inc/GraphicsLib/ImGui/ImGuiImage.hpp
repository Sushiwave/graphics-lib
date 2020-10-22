#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTarget/IMultipleRenderTarget.hpp>
#include <ThirdParty/ExtendedImGui/ImGui/imgui.h>





namespace ImGui
{
	void Image(std::shared_ptr<cg::ITexture2D> texture, const ImVec2& size);
	void Image(std::shared_ptr<cg::IRenderTarget> renderTarget, const ImVec2& size); 
	void Image(std::shared_ptr<cg::IMultipleRenderTarget> mrt, int index, const ImVec2& size);
	
	void ImageDepth(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const ImVec2& size);
	void ImageStencil(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const ImVec2& size);
}
