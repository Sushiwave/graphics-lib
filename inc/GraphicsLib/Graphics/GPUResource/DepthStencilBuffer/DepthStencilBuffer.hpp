#pragma once
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class DepthStencilBuffer
		: public GPUResource,
		  public IDepthStencilBuffer
	{
	public:
		using Refresher = std::function<void(float, int)>;
	private:
		cpp::Vector2D<int> m_size;
		float m_clearDepth = 1.0;
		int m_clearStencil = 0;


		std::shared_ptr<IDefaultTexture2D> m_depthBufferTexture;
		std::shared_ptr<IDefaultTexture2D> m_depthBufferTextureMS;

		std::shared_ptr<IDefaultTexture2D> m_stencilBufferTexture;
		std::shared_ptr<IDefaultTexture2D> m_stencilBufferTextureMS;

		Refresher m_refresh;
	public:
		DepthStencilBuffer() = default;
		DepthStencilBuffer(Refresher refresher, std::shared_ptr<IDefaultTexture2D> depthBufferTexture, std::shared_ptr<IDefaultTexture2D> depthBufferTextureMS, std::shared_ptr<IDefaultTexture2D> stencilBufferTexture, std::shared_ptr<IDefaultTexture2D> stencilBufferTextureMS, int sampleCount, int qualityLevel);
		virtual ~DepthStencilBuffer() = default;

		void refresh() override;

		[[nodiscard]] cpp::Vector2D<int> getSize() const override;

		void changeClearDepth(float depth) override;
		void changeClearStencil(int stencil) override;
		[[nodiscard]] float getClearDepth() const override;
		[[nodiscard]] int getClearStencil() const override;

		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getDepthBufferTexture() const override;
		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getStencilBufferTexture() const override;

		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getDepthBufferTextureMS() const override;
		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getStencilBufferTextureMS() const override;
	};
}
