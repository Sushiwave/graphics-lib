#pragma once
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/IDepthStencilTester.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class DepthStencilTester
		: public GPUResource,
		  public IDepthStencilTester
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
		DepthStencilTester(const SetCall& setCall, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled);
		virtual ~DepthStencilTester() = default;

		[[nodiscard]] ComparisonFunction getDepthFunction() const noexcept override;
		[[nodiscard]] ComparisonFunction getStencilFunction() const noexcept override;

		[[nodiscard]] bool isDepthTestEnabled() const noexcept override;
		[[nodiscard]] bool isStencilTestEnabled() const noexcept override;
		[[nodiscard]] bool isDepthBufferWritingOperationEnabled() const noexcept override;


		static void release();

		void set() const override;
	};
}
