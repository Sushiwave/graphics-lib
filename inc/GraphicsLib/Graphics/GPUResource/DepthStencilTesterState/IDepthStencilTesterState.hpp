#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTesterState/Components/ComparisonFunction.hpp>





namespace cg
{
	class IDepthStencilTesterState
		: public virtual IGPUResource
	{
	public:
		[[nodiscard]] virtual ComparisonFunction getDepthFunction() const = 0;
		[[nodiscard]] virtual ComparisonFunction getStencilFunction() const = 0;
		
		[[nodiscard]] virtual bool isDepthTestEnabled() const = 0;
		[[nodiscard]] virtual bool isStencilTestEnabled() const = 0;
		[[nodiscard]] virtual bool isDepthBufferWritingOperationEnabled() const = 0;

		virtual void set() const = 0;
	};
}