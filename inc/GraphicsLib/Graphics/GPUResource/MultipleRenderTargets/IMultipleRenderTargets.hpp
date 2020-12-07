#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>





namespace cg
{
	class IMultipleRenderTargets
		: virtual public IGPUResource
	{
	public:
		[[nodiscard]] virtual int getRenderTargetCount() const = 0;


		[[nodiscard]] virtual cpp::Vector2D<int> getRenderTargetSize(int index) const = 0;
		[[nodiscard]] virtual std::shared_ptr<ITexture2D> getRenderingResult(int index) = 0;

		virtual void refresh(int unit) = 0;
		virtual void refreshAll() = 0;

		virtual void set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer) = 0;
	};
}