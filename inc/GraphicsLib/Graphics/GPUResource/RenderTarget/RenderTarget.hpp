#pragma once
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class RenderTarget
		: public GPUResource,
		  public IRenderTarget
	{
	protected:
		using ClearColor = std::array<float, 4>;
	public:
		using SetCall = std::function<void(std::shared_ptr<IDepthStencilBuffer>)>;
		using Refresher = std::function<void(const ClearColor&)>;
	private:
		cpp::Vector2D<int> m_size;

		int m_mostDetailedMip;
		int m_mostRoughedMip;
		int m_sampleCount;
		int m_qualityLevel;

		std::shared_ptr<IDefaultTexture2D> m_renderingResult;
		std::shared_ptr<IDefaultTexture2D> m_renderingResultMS;

		SetCall m_setCall;
		Refresher m_refresh;

		ClearColor m_clearColor;
	public:
		RenderTarget() = default;
		RenderTarget(SetCall setCall, Refresher refresher, std::shared_ptr<IDefaultTexture2D> renderingResult, std::shared_ptr<IDefaultTexture2D> renderingResultMS, int sampleCount, int qualityLevel);
		virtual ~RenderTarget() = default;

		void changeClearColor(float r, float g, float b, float a = 1.0f) noexcept override;
		void changeClearColor(const cpp::Vector3D<float>& clearColor) noexcept override;
		void changeClearColor(const cpp::Vector4D<float>& clearColor) noexcept override;

		[[nodiscard]] cpp::Vector4D<float> getClearColor() const noexcept override;
		[[nodiscard]] cpp::Vector2D<int> getSize() const noexcept override;

		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getRenderingResult() const noexcept override;
		[[nodiscard]] std::shared_ptr<IDefaultTexture2D> getRenderingResultMS() const noexcept override;

		void set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer) const override;
		static void release();

		[[nodiscard]] int getMostDetailedMip() const noexcept override;
		[[nodiscard]] int getMostRoughedMip() const noexcept override;
		[[nodiscard]] int getMSAASampleCount() const noexcept override;
		[[nodiscard]] int getMSAAQualityLevel() const noexcept override;

		void refresh() override;
	};
}
