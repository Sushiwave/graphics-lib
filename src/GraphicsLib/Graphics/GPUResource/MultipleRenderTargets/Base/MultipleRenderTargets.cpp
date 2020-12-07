#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/MultipleRenderTargets.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	MultipleRenderTargets::MultipleRenderTargets(const SetCall& setCall, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList)
		: m_renderTargetList(renderTargetList),
		m_setCall(setCall)
	{
		m_count = static_cast<int>(renderTargetList.size());
		for (const auto& renderTarget : renderTargetList)
		{
			m_renderingResults.emplace_back(renderTarget->getRenderingResult());
		}
	}

	void MultipleRenderTargets::set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer)
	{
		auto selfID = getID();

		const auto& gpuState = GPUStateViewer::view();

		bool hasDepthStencilChanged = depthStencilBuffer ?
			(gpuState.depthStencilBuffer.id != depthStencilBuffer->getID()) :
			(gpuState.depthStencilBuffer.isEmpty == false);
		bool hasRenderTargetChanged = selfID != gpuState.renderTarget.id;

		if (hasRenderTargetChanged || hasDepthStencilChanged)
		{
			for (auto renderTarget : m_renderTargetList)
			{
				const auto renderingResultTextureLocationList = renderTarget->getRenderingResult()->getBoundedBufferLocationList();
				for (const auto& location : renderingResultTextureLocationList)
				{
					ShaderResourceMemoryAccessor::release(location.stage, ShaderResourceType::Texture, location.unit, location.usage);
				}
			}

			if (depthStencilBuffer)
			{
				const auto depthTexture = depthStencilBuffer->getDepthBufferTexture();
				if (depthTexture)
				{
					const auto depthTextureLocationList = depthTexture->getBoundedBufferLocationList();
					for (const auto& location : depthTextureLocationList)
					{
						ShaderResourceMemoryAccessor::release(location.stage, ShaderResourceType::Texture, location.unit, location.usage);
					}
				}

				const auto stencilTexture = depthStencilBuffer->getStencilBufferTexture();
				if (stencilTexture)
				{
					const auto stencilTextureLocationList = depthStencilBuffer->getStencilBufferTexture()->getBoundedBufferLocationList();
					for (const auto& location : stencilTextureLocationList)
					{
						ShaderResourceMemoryAccessor::release(location.stage, ShaderResourceType::Texture, location.unit, location.usage);
					}
				}
			}

			m_setCall(m_count, depthStencilBuffer);
		}

		auto& gpuStateRecorder = GPUStateRecorder::main;
		gpuStateRecorder.renderTargetSet(selfID, m_count);
		if (depthStencilBuffer)
		{
			gpuStateRecorder.depthStencilBufferSet(depthStencilBuffer->getID());
		}
		else
		{
			gpuStateRecorder.depthStencilBufferReleased();
		}
	}

	cpp::Vector2D<int> MultipleRenderTargets::getRenderTargetSize(int index) const
	{
		return m_renderTargetList.at(index)->getSize();
	}

	std::vector<std::shared_ptr<ITexture2D>> MultipleRenderTargets::getAllRenderingResults() const
	{
		return m_renderingResults;
	}

	std::shared_ptr<ITexture2D> MultipleRenderTargets::getRenderingResult(int index) const
	{
		return m_renderingResults.at(index);
	}

	int MultipleRenderTargets::getRenderTargetCount() const noexcept
	{
		return m_count;
	}

	void MultipleRenderTargets::refresh(int unit)
	{
		m_renderTargetList.at(unit)->refresh();
	}
	void MultipleRenderTargets::refreshAll()
	{
		for (auto renderTarget : m_renderTargetList)
		{
			renderTarget->refresh();
		}
	}
}
