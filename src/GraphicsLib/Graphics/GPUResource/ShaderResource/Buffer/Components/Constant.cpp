#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/Components/Constant.hpp>





namespace cg
{
	Constant::Constant()
		: m_pData(nullptr)
	{
	}
	ID Constant::getID() const noexcept
	{
		return m_id;
	}

	std::shared_ptr<void> Constant::getP() const noexcept
	{
		return m_pData;
	}
	Constant Constant::clone() const
	{
		return Constant(m_cloneDataPointer());
	}
}
