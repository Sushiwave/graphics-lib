#include <GraphicsLib/Graphics/Transform/Transformable.hpp>




namespace cg
{
	Transformable::Transformable()
		: Transformable(nullptr)
	{
	}

	Transformable::Transformable(std::shared_ptr<Shape> shape)
		: m_transform(std::make_shared<Transform>(shape)),
		  transform(m_transform.get())
	{
	}

	Transformable::~Transformable()
	{
	}
}
