#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>
#include <GraphicsLib/Graphics/Transform/Components/RotationMethod.hpp>
#include <GraphicsLib/Graphics/Transform/Components/CoordinateSystem.hpp>
#include <ThirdParty/CPPLib/DataStructure/HierarchicalTreeStructure.hpp>
#include <GraphicsLib/ID/IIDHolder.hpp>
#include <ThirdParty/CPPLib/DesignPattern/Observer/Observer.hpp>
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>

#include <DirectXMath.h>
#include <functional>





namespace cg
{
	class Transform
		: public IIDHolder,
		  public cpp::Observer,
		  public cpp::HierarchicalTreeStructure<Transform>
	{
	private:
		cg::ID m_id;
	private:
		//Coordinate System
		CoordinateSystem m_coordinateSystem = CoordinateSystem::rectangular;

		//Rectangular Coordinate System
		cpp::Vector3D<float> m_positionLocal = {};
		
		//Polar Coordinate System
		cpp::Vector3D<float> m_centerLocal;
		float m_radius = 0.0;
		float m_phi    = 0.0;
		float m_theta  = 0.0;



		//Rotation Method
		RotationMethod m_rotationMethod = RotationMethod::euler;

		//Euler Rotation
		mutable cpp::Vector3D<float> m_eulerRotationAnglesLocal = {};

		//Quaternion Rotation
		cpp::Vector3D<float> m_rotationAxisLocal = {};
		float m_quaternionRotationAngle = 0.0;

		//LookAt
		cpp::Vector3D<float> m_upLocal = {};
		cpp::Vector3D<float> m_focusPositionLocal = {};
		
		//Polar
		cpp::Vector2D<float> m_polarRotationAnglesLocal = {};

		//Direction
		cpp::Vector3D<float> m_directionLocal = {};



		//Scale
		cpp::Vector3D<float> m_scaleLocal = { 1.0f, 1.0f, 1.0f };
		cpp::Vector3D<float> m_shapeSize  = { 1.0f, 1.0f, 1.0f };
		


	private:
		//Cache Memorys
		mutable DirectX::XMFLOAT4X4 m_worldR = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_worldT = DirectX::XMFLOAT4X4();

		mutable DirectX::XMFLOAT4X4 m_localRT = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_worldRT = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_invWorldRT = DirectX::XMFLOAT4X4();

		mutable DirectX::XMFLOAT4X4 m_local = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_world = DirectX::XMFLOAT4X4();

		mutable DirectX::XMFLOAT4X4 m_localS = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_localR = DirectX::XMFLOAT4X4();
		mutable DirectX::XMFLOAT4X4 m_localT = DirectX::XMFLOAT4X4();



		//Flags for Caching
		mutable bool m_isShapeSizeChanged = false;

		mutable bool m_isLocalRTUpdated = true;
		mutable bool m_isInvWorldRTUpdated = true;

		mutable bool m_isLocalUpdated = true;
		mutable bool m_isWorldUpdated = true;

		mutable bool m_isLocalTUpdated = true;
		mutable bool m_isWorldTUpdated = true;
		
		mutable bool m_isLocalRUpdated = true;
		mutable bool m_isWorldRUpdated = true;

		mutable bool m_isLocalSUpdated = true;



	private:
		//Subject
		mutable std::shared_ptr<Shape> m_observedShape;

		mutable bool m_isAddedSelfToSubject = false;
		mutable std::function<void()> m_addSelfToSubjectDelay = []() {};



	private:
		std::shared_ptr<Transform> m_getLocalRTUpdatedParent() const;

		void m_updateWorldRT() const;
		void m_updateInvWorldRT() const;
		void m_updateWorldRTRecursively() const;

		void m_notifyRotationChanged() const;
		void m_notifyPositionChanged() const;
		void m_notifyScaleChanged() const;
	private:
		void update(cpp::Subject* pSubject) override;





	public:
		Transform();
		Transform(std::shared_ptr<Shape> shape);
		virtual ~Transform() = default;

		



		Transform& operator=(Transform& other);
		


			
			
		[[nodiscard]] cg::ID getID() const override;





		void changeCoordinateSystem(CoordinateSystem system);
		[[nodiscard]] CoordinateSystem getCoordinateSystem() const noexcept;
		void changeRotationMethod(RotationMethod method);
		[[nodiscard]] RotationMethod getRotationMethod() const noexcept;



		

		cpp::Vector3D<float> localToWorld(const cpp::Vector3D<float>& local) const;
		cpp::Vector3D<float> localToWorld(float x, float y, float z) const;
		cpp::Vector3D<float> worldToLocal(const cpp::Vector3D<float>& world) const;
		cpp::Vector3D<float> worldToLocal(float x, float y, float z) const;





		void translate(float x, float y, float z);
		void translate(const cpp::Vector3D<float>& offset);
		void translateX(float x);
		void translateY(float y);
		void translateZ(float z);

		void rotate(float quaternionRotationAngle);
		void rotate(float x, float y, float z);
		void rotate(const cpp::Vector3D<float>& offset);
		void rotateX(float x);
		void rotateY(float y);
		void rotateZ(float z);





		void changeFocusPositionLocal(const cpp::Vector3D<float>& target);
		void changeFocusPositionLocal(float x, float y, float z);
		void changeFocusPositionWorld(const cpp::Vector3D<float>& target);
		void changeFocusPositionWorld(float x, float y, float z);
		void tweakFocusPositionLocal(const std::function<void(cpp::Vector3D<float>&)>& operation);
		void tweakFocusPositionWorld(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changeUpLocal(const cpp::Vector3D<float>& up);
		void changeUpLocal(float x, float y, float z);
		void changeUpWorld(const cpp::Vector3D<float> & up);
		void changeUpWorld(float x, float y, float z);
		void tweakUpLocal(const std::function<void(cpp::Vector3D<float>&)>& operation);
		void tweakUpWorld(const std::function<void(cpp::Vector3D<float>&)> & operation);

		void changePosition(const cpp::Vector3D<float>& position);
		void changePosition(float x, float y, float z);
		void tweakPosition(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changeRadius(float radius);
		void tweakRadius(const std::function<void(float&)>& operation);
		void changeRadiusPhiTheta(float radius, float phi, float theta);
		void tweakRadiusPhiTheta(const std::function<void(float&, float&, float&)>& operation);
		void changePhiTheta(float phi, float theta);
		void tweakPhiTheta(const std::function<void(float&, float&)>& operation);
		void changePhi(float phi);
		void tweakPhi(const std::function<void(float&)>& operation);
		void changeTheta(float theta);
		void tweakTheta(const std::function<void(float&)> & operation);
		void changeCenterLocal(const cpp::Vector3D<float>& center);
		void changeCenterLocal(float x, float y, float z);
		void tweakCenterLocal(const std::function<void(cpp::Vector3D<float>&)> & operation);
		void changeCenterWorld(const cpp::Vector3D<float>& center);
		void changeCenterWorld(float x, float y, float z);
		void tweakCenterWorld(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changeScale(const cpp::Vector3D<float>& scale);
		void changeScale(float x, float y, float z);
		void tweakScale(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changeEulerRotationAngleX(float x);
		void tweakEulerRotationAngleX(const std::function<void(float&)>& operation);
		void changeEulerRotationAngleY(float y);
		void tweakEulerRotationAngleY(const std::function<void(float&)>& operation);
		void changeEulerRotationAngleZ(float z);
		void tweakEulerRotationAngleZ(const std::function<void(float&)>& operation);
		void changeEulerRotationAngles(const cpp::Vector3D<float>& eulerRotationAngles);
		void changeEulerRotationAngles(float x, float y, float z);
		void tweakEulerRotationAngles(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changeRotationAxisLocal(const cpp::Vector3D<float>& rotationAxis);
		void changeRotationAxisLocal(float x, float y, float z);
		void tweakRotationAxisLocal(const std::function<void(cpp::Vector3D<float>&)>& operation);
		void changeRotationAxisWorld(const cpp::Vector3D<float> & rotationAxis);
		void changeRotationAxisWorld(float x, float y, float z);
		void tweakRotationAxisWorld(const std::function<void(cpp::Vector3D<float>&)> & operation);

		void changeQuaternionRotationAngle(float angle);
		void tweakQuaternionRotationAngle(const std::function<void(float&)>& operation);

		void changeDirectionLocal(const cpp::Vector3D<float> & direction);
		void changeDirectionLocal(float x, float y, float z);
		void tweakDirectionLocal(const std::function<void(cpp::Vector3D<float>&)>& operation);
		void changeDirectionWorld(const cpp::Vector3D<float>& direction);
		void changeDirectionWorld(float x, float y, float z);
		void tweakDirectionLWorld(const std::function<void(cpp::Vector3D<float>&)>& operation);

		void changePolarRotationAngles(const cpp::Vector2D<float> & angles);
		void changePolarRotationAngles(float phi, float theta);
		void tweakPolarRotationAngles(const std::function<void(cpp::Vector2D<float>&)>& operation);
		void changePolarRotationAnglePhi(float phi);
		void tweakPolarRotationAnglePhi(const std::function<void(float&)>& operation);
		void changePolarRotationAngleTheta(float theta);
		void tweakPolarRotationAngleTheta(const std::function<void(float&)>& operation);
	




		[[nodiscard]] cpp::Vector3D<float> calcPositionLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcPositionWorld() const;

		[[nodiscard]] cpp::Vector3D<float> calcCenterLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcCenterWorld() const;
		[[nodiscard]] float calcRadius() const;
		[[nodiscard]] float calcPhi() const;
		[[nodiscard]] float calcTheta() const;



		[[nodiscard]] cpp::Vector3D<float> calcScaleLocal() const;



		[[nodiscard]] cpp::Vector3D<float> calcEulerRotationAnglesLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcEulerRotationAnglesWorld() const;

		[[nodiscard]] cpp::Vector3D<float> calcRotationAxisLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcRotationAxisWorld() const;
		[[nodiscard]] float calcQuaternionRotationAngleLocal() const;
		[[nodiscard]] float calcQuaternionRotationAngleWorld() const;

		[[nodiscard]] cpp::Vector2D<float> calcPolarRotationAnglesLocal() const;
		[[nodiscard]] cpp::Vector2D<float> calcPolarRotationAnglesWorld() const;

		[[nodiscard]] cpp::Vector3D<float> calcFocusPositionLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcFocusPositionWorld() const;



		[[nodiscard]] cpp::Vector3D<float> calcForwardLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcForwardWorld() const;

		[[nodiscard]] cpp::Vector3D<float> calcUpLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcUpWorld() const;

		[[nodiscard]] cpp::Vector3D<float> calcSideLocal() const;
		[[nodiscard]] cpp::Vector3D<float> calcSideWorld() const;	





		DirectX::XMFLOAT4X4 createScalingMatrixLocal() const;
		
		DirectX::XMFLOAT4X4 createRotationMatrixLocal() const;
		DirectX::XMFLOAT4X4 createRotationMatrixWorld() const;

		DirectX::XMFLOAT4X4 createTranslationMatrixLocal() const;
		DirectX::XMFLOAT4X4 createTranslationMatrixWorld() const;

		DirectX::XMFLOAT4X4 createLocalMatrix() const;
		DirectX::XMFLOAT4X4 createWorldMatrix() const;
	};
}
