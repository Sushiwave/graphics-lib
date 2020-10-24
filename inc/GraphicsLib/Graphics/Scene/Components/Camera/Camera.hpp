#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Components/Projection/Projection.hpp>
#include <GraphicsLib/Graphics/DrawableObject/Components/Transform/Transform.hpp>





namespace cg
{
	class Camera
	{
	private:
		std::shared_ptr<Transform> m_transform;
	public:
		Projection projection;
	public:
		Camera();
		virtual ~Camera() = default;

		void tweakTransform(const std::function<void(Transform&)>& operation) const;
		[[nodiscard]] Transform& getTransformRef() const noexcept;
	};
}
