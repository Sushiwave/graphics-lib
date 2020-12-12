#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>





namespace cg
{
	ID GPUResource::getID() const noexcept
	{
		return m_id;
	}
}
