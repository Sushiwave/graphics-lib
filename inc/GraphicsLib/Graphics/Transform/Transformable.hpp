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
		virtual ~Transformable();
	};
}
