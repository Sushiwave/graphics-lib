#include <GraphicsLib/Graphics/GPUResource/RenderTarget/RenderTarget.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	const auto releaseBoundedTexture = [](std::shared_ptr<IDefaultTexture2D> boundedTexture)
	{
		if (boundedTexture)
		{
			const auto locationList = boundedTexture->getBoundedBufferLocationList();
			for (const auto& location : locationList)
			{
				ShaderResourceMemoryAccessor::release(location.stage, ShaderResourceType::Texture, location.unit, location.usage);
			}
		}
	};





	RenderTarget::RenderTarget(SetCall setCall, Refresher refresher, std::shared_ptr<IDefaultTexture2D> renderingResult, std::shared_ptr<IDefaultTexture2D> renderingResultMS, int sampleCount, int qualityLevel)
		: m_size(renderingResult->getSize()),
		  m_mostDetailedMip(renderingResult->getMostDetailedMipLevel()),
		  m_mostRoughedMip(renderingResult->getMostRoughedMipLevel()),
		  m_sampleCount(sampleCount),
		  m_qualityLevel(qualityLevel),
		  m_renderingResult(renderingResult),
		  m_renderingResultMS(renderingResultMS),
		  m_setCall(setCall),
		  m_refresh(refresher)
	{
		changeClearColor(0, 0, 0, 0);
	}

	void RenderTarget::changeClearColor(float r, float g, float b, float a) noexcept
	{
		m_clearColor[0] = r;
		m_clearColor[1] = g;
		m_clearColor[2] = b;
		m_clearColor[3] = a;
	}

	void RenderTarget::changeClearColor(const cpp::Vector3D<float>& clearColor) noexcept
	{
		changeClearColor(clearColor.x, clearColor.y, clearColor.z);
	}

	void RenderTarget::changeClearColor(const cpp::Vector4D<float>& clearColor) noexcept
	{
		changeClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	}

	cpp::Vector4D<float> RenderTarget::getClearColor() const noexcept
	{
		return { m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3] };;
	}

	cpp::Vector2D<int> RenderTarget::getSize() const noexcept
	{
		return m_size;
	}

	std::shared_ptr<IDefaultTexture2D> RenderTarget::getRenderingResult() const noexcept
	{
		return m_renderingResult;
	}

	std::shared_ptr<IDefaultTexture2D> RenderTarget::getRenderingResultMS() const noexcept
	{
		return m_renderingResultMS;
	}

	int RenderTarget::getMostDetailedMip() const noexcept
	{
		return m_mostDetailedMip;
	}

	int RenderTarget::getMostRoughedMip() const noexcept
	{
		return m_mostRoughedMip;
	}

	int RenderTarget::getMSAASampleCount() const noexcept
	{
		return m_sampleCount;
	}

	int RenderTarget::getMSAAQualityLevel() const noexcept
	{
		return m_qualityLevel;
	}

	void RenderTarget::set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer) const 
	{
		const auto& gpuState = GPUStateViewer::view();
		const auto selfID = getID();


		bool hasDepthStencilChanged = depthStencilBuffer ?
			(gpuState.depthStencilBuffer.id != depthStencilBuffer->getID()) :
			gpuState.depthStencilBuffer.isEmpty == false;
		bool hasRenderTargetChanged = selfID != gpuState.renderTarget.id;


		
		if (hasDepthStencilChanged || hasRenderTargetChanged)
		{
			releaseBoundedTexture(m_renderingResult);
			releaseBoundedTexture(m_renderingResultMS);
			if (depthStencilBuffer)
			{
				releaseBoundedTexture(depthStencilBuffer->getDepthBufferTexture());
				releaseBoundedTexture(depthStencilBuffer->getDepthBufferTextureMS());
				releaseBoundedTexture(depthStencilBuffer->getStencilBufferTexture());
				releaseBoundedTexture(depthStencilBuffer->getStencilBufferTextureMS());
			}



			m_setCall(depthStencilBuffer);



			auto& gpuStateRecorder = GPUStateRecorder::main;
			gpuStateRecorder.renderTargetSet(this);
			if (depthStencilBuffer)
			{
				gpuStateRecorder.depthStencilBufferSet(depthStencilBuffer.get());
			}
			else
			{
				gpuStateRecorder.depthStencilBufferReleased();
			}
		}
	}

	void RenderTarget::release()
	{
		const auto& renderTargetBufferState = GPUStateViewer::view().renderTarget;

		if (renderTargetBufferState.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		static ID3D11RenderTargetView* nullArray[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
		d3d11::Device::getDeviceContext()->OMSetRenderTargets(renderTargetBufferState.count, nullArray, nullptr);
#endif

		auto& gpuStateRecorder = GPUStateRecorder::main;
		gpuStateRecorder.renderTargetReleased();
		gpuStateRecorder.depthStencilBufferReleased();
	}

	void RenderTarget::refresh()
	{
		m_refresh(m_clearColor);
	}
}
