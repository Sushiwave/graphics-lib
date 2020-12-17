#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Components/Projection/Projection.hpp>
#include <GraphicsLib/Graphics/Transform/Transform.hpp>
#include <GraphicsLib/Graphics/Transform/Transformable.hpp>





namespace cg
{
	class Camera
		: public Transformable
	{
	public:
		Projection projection;
	public:
		Camera();
		virtual ~Camera() = default;
	};
}
