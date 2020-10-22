#pragma once
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class GPUResource
		: public virtual IGPUResource
	{
	private:
		ID m_id;
	public:
		GPUResource() = default;
		GPUResource(const ID& id);
		virtual ~GPUResource() = default;

		[[nodiscard]] ID getID() const noexcept override;
	};
}