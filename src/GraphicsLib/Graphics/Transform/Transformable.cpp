#include <GraphicsLib/Graphics/Transform/Transformable.hpp>




namespace cg
{
	Transformable::Transformable()
		: m_transform(std::make_shared<Transform>()),
		  transform(m_transform.get())
	{
	}

	Transformable::~Transformable()
	{
	}
}
