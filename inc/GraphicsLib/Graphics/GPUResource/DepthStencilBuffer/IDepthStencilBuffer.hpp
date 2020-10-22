#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/IDefaultTexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>

#include <memory>





namespace cg
{
	class IDepthStencilBuffer
		: public virtual IGPUResource
	{
	public:
		virtual void refresh() = 0;

		[[nodiscard]] virtual cpp::Vector2D<int> getSize() const = 0;

		virtual void changeClearDepth(float depth) = 0;
		virtual void changeClearStencil(int stencil) = 0;
		[[nodiscard]] virtual float getClearDepth() const = 0;
		[[nodiscard]] virtual int getClearStencil() const = 0;

		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getDepthBufferTexture() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getStencilBufferTexture() const = 0;

		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getDepthBufferTextureMS() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getStencilBufferTextureMS() const = 0;
	};
}