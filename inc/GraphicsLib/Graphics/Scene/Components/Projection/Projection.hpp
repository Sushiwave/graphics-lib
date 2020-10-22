#pragma once
#include <DirectXMath.h>
#include <functional>
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>
#include "Components/ProjectionType.hpp"





namespace cg
{
	class Projection
	{
	private:
		// Perspective
		float m_fov    = 0.1f;
		float m_aspect = 0.1f;
		
		// Orthographic2D
		cpp::Vector2D<float> m_lowerLeft;
		cpp::Vector2D<float> m_upperRight;
		
		//Orthographic3D
		cpp::Vector2D<float> m_viewSize;

		// Perspective / Orthographic3D
		float m_nearZ = 0.1f;
		float m_farZ = 0.2f;



		ProjectionType m_type;



		mutable bool m_isUpdated = false;
		mutable DirectX::XMFLOAT4X4 m_matrix;
	public:
		Projection();
		virtual ~Projection() = default;





		Projection operator=(const Projection& other);





		void changeType(ProjectionType type);
		[[nodiscard]] ProjectionType getType() const noexcept;



		// Perspective
		void changeFov(float fov);
		void tweakFov(const std::function<void(float&)>& operation);

		void changeAspect(float aspect);
		void tweakAspect(const std::function<void(float&)>& operation);



		// Orthographic2D
		void changeLowerLeft(float x, float y);
		void changeLowerLeft(const cpp::Vector2D<float>& lowerLeft);
		void tweakLowerLeft(const std::function<void(cpp::Vector2D<float>&)>& operation);

		void changeUpperRight(float x, float y);		
		void changeUpperRight(const cpp::Vector2D<float>& upperRight);
		void tweakUpperRight(const std::function<void(cpp::Vector2D<float>&)>& operation);



		//Orthographic3D
		void changeViewWidth(float width);
		void tweakViewWidth(const std::function<void(float&)>& operation);

		void changeViewHeight(float height);
		void tweakViewHeight(const std::function<void(float&)>& operation);

		void changeViewSize(float width, float height);
		void changeViewSize(const cpp::Vector2D<float>& size);
		void tweakViewSize(const std::function<void(cpp::Vector2D<float>&)>& operation);



		// Perspective / Orthographic3D
		void changeNearZ(float z);
		void tweakNearZ(const std::function<void(float&)>& operation);

		void changeFarZ(float z);
		void tweakFarZ(const std::function<void(float&)>& operation);





		// Perspective
		[[nodiscard]] float getAspect() const noexcept;
		[[nodiscard]] float getFov() const noexcept;



		// Orthographic2D
		[[nodiscard]] cpp::Vector2D<float> getLowerLeft() const noexcept;
		[[nodiscard]] cpp::Vector2D<float> getUpperRight() const noexcept;



		// Orthographic3D
		[[nodiscard]] cpp::Vector2D<float> getViewSize() const noexcept;



		// Perspective / Orthographic3D
		[[nodiscard]] float getNearZ() const noexcept;
		[[nodiscard]] float getFarZ() const noexcept;





		[[nodiscard]] DirectX::XMFLOAT4X4 createMatrix() const;
	};
}
