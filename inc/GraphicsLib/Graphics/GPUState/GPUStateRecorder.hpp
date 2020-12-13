#pragma once
#include <GraphicsLib/Graphics/GPUState/GPUState.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/IMultipleRenderTargets.hpp>





namespace cg
{
	class GPUStateRecorder
	{
	private:
		friend class GPUStateViewer;
	private:
		static const ID m_mainRecordingThreadName;
		
		mutable std::unordered_map<std::string, GPUState> m_records;
	public:
		static const GPUStateRecorder main;
	public:
		virtual ~GPUStateRecorder() = default;



		void rasterizerSet(const ID& id) const noexcept;
		void rasterizerReleased() const noexcept;
		void depthStencilTesterSet(const ID& id) const noexcept;
		void depthStencilTesterReleased() const noexcept;
		void blenderSet(const ID& id) const noexcept;
		void blenderReleased() const noexcept;
		void multipleRenderTargetsSet(const cg::IMultipleRenderTargets* multipleRenderTargets) const noexcept;
		void renderTargetSet(const cg::IRenderTarget* renderTarget) const noexcept;
		void renderTargetReleased() const noexcept;
		void depthStencilBufferSet(const cg::IDepthStencilBuffer* depthStencilBuffer) const noexcept;
		void depthStencilBufferReleased() const noexcept;
		void shaderSet(ShaderStage stage, const ID& id) const noexcept;
		void shaderReleased(ShaderStage stage) const noexcept;
		void shaderResourceReleased(ShaderStage stage, ShaderResourceType resourceType, GPUAccessType usage, int unitIndex) const noexcept;
		void shaderResourceSet(ShaderStage stage, ShaderResourceType resourceType, GPUAccessType usage, int unitIndex, const ID& id) const noexcept;



		void createNewRecordingThread(const std::string& name) const noexcept;
		void removeRecordingThread(const std::string& name) const noexcept;



		[[nodiscard]] GPUState getGPUState(const std::string& name) const;
	};
}
