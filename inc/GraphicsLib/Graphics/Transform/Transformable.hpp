#pragma once
#include "Transform.hpp"





namespace cg
{
	class Transformable
	{
	private:
		std::shared_ptr<cg::Transform> m_transform;
	public:
		Transform* const transform;
	public:
		Transformable();
		Transformable(std::shared_ptr<cg::Shape> shape);
		virtual ~Transformable();
	};
}
