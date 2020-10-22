#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/DepthStencilBuffer.hpp>

namespace cg
{
	DepthStencilBuffer::DepthStencilBuffer(Refresher refresher, std::shared_ptr<IDefaultTexture2D> depthBufferTexture, std::shared_ptr<IDefaultTexture2D> depthBufferTextureMS, std::shared_ptr<IDefaultTexture2D> stencilBufferTexture, std::shared_ptr<IDefaultTexture2D> stencilBufferTextureMS, int sampleCount, int qualityLevel)
		: m_size(depthBufferTexture->getSize()),
		  m_depthBufferTexture(depthBufferTexture),
		  m_depthBufferTextureMS(depthBufferTextureMS),
		  m_stencilBufferTexture(stencilBufferTexture),
		  m_stencilBufferTextureMS(stencilBufferTextureMS),
		  m_refresh(refresher)
	{
	}

	void DepthStencilBuffer::refresh()
	{
		m_refresh(m_clearDepth, m_clearStencil);
	}

	[[nodiscard]] cpp::Vector2D<int> DepthStencilBuffer::getSize() const
	{
		return m_size;
	}

	void DepthStencilBuffer::changeClearDepth(float depth)
	{
		m_clearDepth = depth;
	}
	void DepthStencilBuffer::changeClearStencil(int stencil)
	{
		m_clearStencil = stencil;
	}
	[[nodiscard]] float DepthStencilBuffer::getClearDepth() const
	{
		return m_clearDepth;
	}
	[[nodiscard]] int DepthStencilBuffer::getClearStencil() const
	{
		return m_clearStencil;
	}

	[[nodiscard]] std::shared_ptr<IDefaultTexture2D> DepthStencilBuffer::getDepthBufferTexture() const
	{
		return m_depthBufferTexture;
	}
	[[nodiscard]] std::shared_ptr<IDefaultTexture2D> DepthStencilBuffer::getStencilBufferTexture() const
	{
		return m_stencilBufferTexture;
	}

	[[nodiscard]] std::shared_ptr<IDefaultTexture2D> DepthStencilBuffer::getDepthBufferTextureMS() const
	{
		return m_depthBufferTextureMS;
	}
	[[nodiscard]] std::shared_ptr<IDefaultTexture2D> DepthStencilBuffer::getStencilBufferTextureMS() const
	{
		return m_stencilBufferTextureMS;
	}
}
