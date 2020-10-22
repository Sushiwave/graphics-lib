#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>





namespace cg
{
	GPUResource::GPUResource(const ID& id)
		: m_id(id)
	{
	}

	ID GPUResource::getID() const noexcept
	{
		return m_id;
	}
}
