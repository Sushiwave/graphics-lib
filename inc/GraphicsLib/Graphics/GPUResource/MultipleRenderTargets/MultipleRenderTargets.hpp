#pragma once
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/IMultipleRenderTargets.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class MultipleRenderTargets
		: public IMultipleRenderTargets,
		  public GPUResource
	{
	public:
		using SetCall = std::function<void(int count, std::shared_ptr<IDepthStencilBuffer>)>;
	private:
		SetCall m_setCall;

		int m_count;

		std::vector<ID> m_renderingResultIDList;
	protected:
		std::vector<std::shared_ptr<IRenderTarget>> m_renderTargetList;
	public:
		MultipleRenderTargets() = default;
		MultipleRenderTargets(const SetCall& setCall, const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList);
		~MultipleRenderTargets() = default;



		[[nodiscard]] int getRenderTargetCount() const noexcept override;

		[[nodiscard]] cpp::Vector2D<int> getRenderTargetSize(int index) const override;
		[[nodiscard]] std::shared_ptr<ITexture2D> getRenderingResult(int index) override;



		void set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer) override;



		void refreshAll() override;
		void refresh(int unit) override;
	};
}