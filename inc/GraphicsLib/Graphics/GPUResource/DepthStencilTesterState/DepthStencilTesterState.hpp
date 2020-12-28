#pragma once
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTesterState/IDepthStencilTesterState.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class DepthStencilTesterState
		: public GPUResource,
		  public IDepthStencilTesterState
	{
	public:
		using SetCall = std::function<void()>;
	private:
		ComparisonFunction m_depthFunction;
		ComparisonFunction m_stencilFunction;

		bool m_isDepthTestEnabled;
		bool m_isStencilTestEnabled;

		bool m_isDepthBufferWritingOperationEnabled;

		SetCall m_setCall;
	public:
		DepthStencilTesterState(const SetCall& setCall, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled);
		virtual ~DepthStencilTesterState() = default;

		[[nodiscard]] ComparisonFunction getDepthFunction() const noexcept override;
		[[nodiscard]] ComparisonFunction getStencilFunction() const noexcept override;

		[[nodiscard]] bool isDepthTestEnabled() const noexcept override;
		[[nodiscard]] bool isStencilTestEnabled() const noexcept override;
		[[nodiscard]] bool isDepthBufferWritingOperationEnabled() const noexcept override;


		static void release();

		void set() const override;
	};
}
