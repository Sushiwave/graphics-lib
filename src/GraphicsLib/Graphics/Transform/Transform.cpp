#include <GraphicsLib/Graphics/Transform/Transform.hpp>
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>





namespace cg
{
	const auto calcForwardFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->cpp::Vector3D<float>
	{
		return cpp::Vector3D<float>(matrix._31, matrix._32, matrix._33).normalized();
	};
	const auto calcUpFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->cpp::Vector3D<float>
	{
		return cpp::Vector3D<float>(matrix._21, matrix._22, matrix._23).normalized();
	};
	const auto calcSideFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->cpp::Vector3D<float>
	{
		return cpp::Vector3D<float>(matrix._11, matrix._12, matrix._13).normalized();
	}; 
	const auto calcEulerRotationAnglesFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->cpp::Vector3D<float>
	{
		const auto x = asin(-matrix._32);
		const auto y = atan2(matrix._31, matrix._33);
		const auto z = atan2(matrix._12, matrix._22);
		
		return { x, y, z };
	};
	const auto calcPolarRotationAnglesFromForward = [](const cpp::Vector3D<float>& forward)->cpp::Vector2D<float>
	{
		const auto theta = acos(forward.y);
		const auto phi = forward.z == 0.0f ? 0.0f : atan(forward.x/forward.z);
		return { phi, theta };
	};
	const auto calcRotationAxisFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->cpp::Vector3D<float>
	{
		const auto r = sqrt(pow(matrix._23-matrix._32, 2)+pow(matrix._31-matrix._13, 2)+pow(matrix._12-matrix._21, 2));
		const auto d  = r == 0.0f ? 0.0f : 1.0f/r;
		const auto x = (matrix._23-matrix._32)*d;
		const auto y = (matrix._31-matrix._13)*d;
		const auto z = (matrix._12-matrix._21)*d;
		return { x, y, z };
	};
	const auto calcQuaternionRotationAngleFromMatrix = [](const DirectX::XMFLOAT4X4& matrix)->float
	{
		return acos((matrix._11+matrix._22+matrix._33-1.0f)*0.5f);
	};









	Transform& Transform::operator=(Transform& other)
	{
		m_id = other.m_id;
		m_positionLocal = other.m_positionLocal;
		m_centerLocal = other.m_centerLocal;
		m_radius = other.m_radius;
		m_phi = other.m_phi;
		m_theta = other.m_theta;
		m_scaleLocal = other.m_scaleLocal;
		m_shapeSize = other.m_shapeSize;
		m_eulerRotationAnglesLocal = other.m_eulerRotationAnglesLocal;
		m_rotationAxisLocal = other.m_rotationAxisLocal;
		m_quaternionRotationAngle = other.m_quaternionRotationAngle;
		m_upLocal = other.m_upLocal;
		m_focusPositionLocal = other.m_focusPositionLocal;
		m_polarRotationAnglesLocal = other.m_polarRotationAnglesLocal;
		m_directionLocal = other.m_directionLocal;
		
		m_coordinateSystem = other.m_coordinateSystem;
		m_rotationMethod = other.m_rotationMethod;
		m_worldR = other.m_worldR;
		m_worldT = other.m_worldT;
		m_localRT = other.m_localRT;
		m_worldRT = other.m_worldRT;
		m_invWorldRT = other.m_invWorldRT;
		m_local = other.m_local;
		m_world = other.m_world;
		m_localS = other.m_localS;
		m_localR = other.m_localR;
		m_localT = other.m_localT;
		m_isAddedSelfToSubject = other.m_isAddedSelfToSubject;
		m_isLocalRTUpdated = other.m_isLocalRTUpdated;
		m_isLocalRUpdated = other.m_isLocalRUpdated;
		m_isLocalTUpdated = other.m_isLocalTUpdated;
		m_isLocalSUpdated = other.m_isLocalSUpdated;
		m_isLocalUpdated = other.m_isLocalUpdated;
		m_isInvWorldRTUpdated = other.m_isInvWorldRTUpdated;
		m_isWorldRUpdated = other.m_isWorldRUpdated;
		m_isWorldTUpdated = other.m_isWorldTUpdated;
		m_isWorldUpdated = other.m_isWorldUpdated;
		m_isShapeSizeChanged = other.m_isShapeSizeChanged;

		return *this;
	}










	cg::ID Transform::getID() const
	{
		return m_id;
	}










	std::shared_ptr<Transform> Transform::m_getLocalRTUpdatedParent() const
	{
		auto parent = m_parent;
		std::shared_ptr<Transform> updatedParent = nullptr;
		while (parent)
		{
			if (parent->m_isLocalRTUpdated)
			{
				updatedParent = parent;
			}
			parent = parent->m_parent;
		}
		return updatedParent;
	}
	void Transform::m_updateWorldRT() const
	{
		auto updatedParent = m_getLocalRTUpdatedParent();

		if (updatedParent == nullptr)
		{
			if (m_isLocalRTUpdated)
			{
				m_updateWorldRTRecursively();
			}
		}
		else
		{
			updatedParent->m_updateWorldRTRecursively();
		}
	}
	void Transform::m_updateInvWorldRT() const
	{
		m_updateWorldRT();
		if (m_isInvWorldRTUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_invWorldRT, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&m_worldRT)));
			m_isInvWorldRTUpdated = false;
		}
	}
	void Transform::m_updateWorldRTRecursively() const
	{
		if (m_isLocalRTUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_localRT, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&createRotationMatrixLocal()), DirectX::XMLoadFloat4x4(&createTranslationMatrixLocal())));
			m_isLocalRTUpdated = false;
		}

		if (isRootNode())
		{
			m_worldRT = m_localRT;
		}
		else
		{
			DirectX::XMStoreFloat4x4(&m_worldRT, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&m_parent->m_worldRT), DirectX::XMLoadFloat4x4(&m_localRT)));
		}

		m_isWorldRUpdated = true;
		m_isWorldTUpdated = true;
		m_isWorldUpdated = true;
		m_isInvWorldRTUpdated = true;

		for (auto pair : m_children)
		{
			pair.second->m_updateWorldRTRecursively();
		}
	}









	
	void Transform::m_notifyRotationChanged() const
	{
		m_isLocalRUpdated = true;
		m_isLocalRTUpdated = true;
		m_isLocalUpdated = true;
	}
	void Transform::m_notifyPositionChanged() const
	{
		m_isLocalTUpdated = true;
		m_isLocalRTUpdated = true;
		m_isLocalUpdated = true;
		if (m_rotationMethod == RotationMethod::lookAt)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::m_notifyScaleChanged() const
	{
		m_isLocalSUpdated = true;
		m_isLocalUpdated = true;
		m_isWorldUpdated = true;
	}










	void Transform::update(cpp::Subject* pSubject)
	{
		auto pShape = dynamic_cast<Shape*>(pSubject);
		if (pShape == nullptr) { return; }
		m_shapeSize = pShape->getSize();
		m_isShapeSizeChanged = true;
	}










	Transform::Transform()
	{
	}
	Transform::Transform(std::shared_ptr<Shape> shape)
	{
		if (shape)
		{
			m_observedShape = shape;
			m_addSelfToSubjectDelay = [&]()
			{
				addSelfToSubject(m_observedShape.get());
				m_shapeSize = m_observedShape->getSize();
			};
			m_isShapeSizeChanged = true;
		}
	}










	void Transform::changeCoordinateSystem(CoordinateSystem system)
	{
		if (m_coordinateSystem == system) { return; }

		if (system == CoordinateSystem::rectangular)
		{
			m_positionLocal = calcPositionLocal();
		}
		else if (system == CoordinateSystem::polar)
		{
			m_centerLocal = calcCenterLocal();
			m_radius = calcRadius();
			m_phi = calcPhi();
			m_theta = calcTheta();
		}

		m_coordinateSystem = system;
	}
	CoordinateSystem Transform::getCoordinateSystem() const noexcept
	{
		return m_coordinateSystem;
	}










	void Transform::changeRotationMethod(RotationMethod method)
	{
		if (m_rotationMethod == method) { return; }

		if (method == RotationMethod::euler) 
		{
			m_eulerRotationAnglesLocal = calcEulerRotationAnglesLocal();
		}
		else if (method == RotationMethod::lookAt)
		{
			m_focusPositionLocal = calcFocusPositionLocal();
			m_upLocal = calcUpLocal();
		}
		else if (method == RotationMethod::directionBase)
		{
			m_directionLocal = calcForwardLocal();
			m_upLocal = calcUpLocal();
		}
		else if (method == RotationMethod::polar)
		{
			m_polarRotationAnglesLocal = calcPolarRotationAnglesLocal();
			m_upLocal = calcUpLocal();
		}
		else if (method == RotationMethod::quaternion)
		{
			m_rotationAxisLocal = calcRotationAxisLocal();
			m_quaternionRotationAngle = calcQuaternionRotationAngleLocal();
		}

		m_rotationMethod = method;
	}
	RotationMethod Transform::getRotationMethod() const noexcept
	{
		return m_rotationMethod;
	}










	cpp::Vector3D<float> Transform::localToWorld(const cpp::Vector3D<float>& local) const
	{
		return localToWorld(local.x, local.y, local.z);
	}
	cpp::Vector3D<float> Transform::localToWorld(float x, float y, float z) const
	{
		if (m_parent)
		{
			m_parent->m_updateWorldRT();

			DirectX::XMFLOAT4 world;
			DirectX::XMStoreFloat4(&world, DirectX::XMVector4Transform(DirectX::XMVectorSet(x, y, z, 1.0), DirectX::XMLoadFloat4x4(&m_parent->m_worldRT)));
			return { world.x, world.y, world.z };
		}
		return { x, y, z };
	}

	cpp::Vector3D<float> Transform::worldToLocal(const cpp::Vector3D<float>& world) const
	{
		return worldToLocal(world.x, world.y, world.z);
	}
	cpp::Vector3D<float> Transform::worldToLocal(float x, float y, float z) const
	{
		if (m_parent)
		{
			m_parent->m_updateInvWorldRT();

			DirectX::XMFLOAT4 local;
			DirectX::XMStoreFloat4(&local, DirectX::XMVector4Transform(DirectX::XMVectorSet(x, y, z, 1.0), DirectX::XMLoadFloat4x4(&m_parent->m_invWorldRT)));
			return { local.x, local.y, local.z };
		}
		return { x, y, z };
	}










	void Transform::translate(const cpp::Vector3D<float>& offset)
	{
		translate(offset.x, offset.y, offset.z);
	}
	void Transform::translate(float x, float y, float z)
	{
		m_positionLocal.x += x;
		m_positionLocal.y += y;
		m_positionLocal.z += z;

		if (m_coordinateSystem == CoordinateSystem::rectangular)
		{
			m_notifyPositionChanged();
		}
	}
	void Transform::translateX(float x)
	{
		translate(x, 0, 0);
	}
	void Transform::translateY(float y)
	{
		translate(0, y, 0);
	}
	void Transform::translateZ(float z)
	{
		translate(0, 0, z);
	}





	void Transform::rotate(float quaternionRotationAngle)
	{
		this->m_quaternionRotationAngle += quaternionRotationAngle;
		if (m_rotationMethod == RotationMethod::quaternion)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::rotate(const cpp::Vector3D<float>& offset)
	{
		rotate(offset.x, offset.y, offset.z);
	}
	void Transform::rotate(float x, float y, float z)
	{
		m_eulerRotationAnglesLocal.x += x;
		m_eulerRotationAnglesLocal.y += y;
		m_eulerRotationAnglesLocal.z += z;

		if (m_rotationMethod == RotationMethod::euler)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::rotateX(float x)
	{
		rotate(x, 0, 0);
	}
	void Transform::rotateY(float y)
	{
		rotate(0, y, 0);
	}
	void Transform::rotateZ(float z)
	{
		rotate(0, 0, z);
	}










	void Transform::changePosition(const cpp::Vector3D<float>& position)
	{
		this->changePosition(position.x, position.y, position.z);
	}
	void Transform::changePosition(float x, float y, float z)
	{
		m_positionLocal.x = x;
		m_positionLocal.y = y;
		m_positionLocal.z = z;

		if (m_coordinateSystem == CoordinateSystem::rectangular)
		{
			m_notifyPositionChanged();
		}
	}
	void Transform::tweakPosition(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_positionLocal);
		changePosition(m_positionLocal.x, m_positionLocal.y, m_positionLocal.z);
	}





	void Transform::changeRadius(float radius)
	{
		changeRadiusPhiTheta(radius, m_phi, m_theta);
	}
	void Transform::tweakRadius(const std::function<void(float&)>& operation)
	{
		operation(m_radius);
		changeRadius(m_radius);
	}

	void Transform::changeRadiusPhiTheta(float radius, float phi, float theta)
	{
		m_radius = radius;
		m_phi = phi;
		m_theta = theta;
		if (m_coordinateSystem == CoordinateSystem::polar)
		{
			m_notifyPositionChanged();
		}
	}
	void Transform::tweakRadiusPhiTheta(const std::function<void(float&, float&, float&)>& operation)
	{
		operation(m_radius, m_phi, m_theta);
		changeRadiusPhiTheta(m_radius, m_phi, m_theta);
	}

	void Transform::changePhiTheta(float phi, float theta)
	{
		changeRadiusPhiTheta(m_radius, phi, theta);
	}
	void Transform::tweakPhiTheta(const std::function<void(float&, float&)>& operation)
	{
		operation(m_phi, m_theta);
		changePhiTheta(m_phi, m_theta);
	}

	void Transform::changePhi(float phi)
	{
		changePhiTheta(phi, m_theta);
	}
	void Transform::tweakPhi(const std::function<void(float&)>& operation)
	{
		operation(m_phi);
		changePhi(m_phi);
	}

	void Transform::changeTheta(float theta)
	{
		changePhiTheta(m_phi, theta);
	}
	void Transform::tweakTheta(const std::function<void(float&)>& operation)
	{
		operation(m_theta);
		changeTheta(m_theta);
	}





	void Transform::changeCenterLocal(float x, float y, float z)
	{
		m_centerLocal.x = x;
		m_centerLocal.y = y;
		m_centerLocal.z = z;
		if (m_coordinateSystem == CoordinateSystem::polar)
		{
			m_notifyPositionChanged();
		}
	}
	void Transform::changeCenterLocal(const cpp::Vector3D<float>& center)
	{
		changeCenterLocal(center.x, center.y, center.z);
	}
	void Transform::tweakCenterLocal(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_centerLocal);
		changeCenterLocal(m_centerLocal);
	}

	void Transform::changeCenterWorld(const cpp::Vector3D<float>& center)
	{
		changeCenterWorld(center.x, center.y, center.z);
	}
	void Transform::changeCenterWorld(float x, float y, float z)
	{
		changeCenterLocal(worldToLocal(x, y, z));
	}
	void Transform::tweakCenterWorld(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		cpp::Vector3D<float> centerWorld = calcCenterWorld();
		operation(centerWorld);
		changeCenterWorld(centerWorld);
	}






	void Transform::changeScale(const cpp::Vector3D<float>& scale)
	{
		this->changeScale(scale.x, scale.y, scale.z);
	}
	void Transform::changeScale(float x, float y, float z)
	{
		m_scaleLocal.x = x;
		m_scaleLocal.y = y;
		m_scaleLocal.z = z;

		m_notifyScaleChanged();
	}
	void Transform::tweakScale(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_scaleLocal);
		changeScale(m_scaleLocal.x, m_scaleLocal.y, m_scaleLocal.z);
	}

	void Transform::changeEulerRotationAngleX(float x)
	{
		changeEulerRotationAngles(x, m_eulerRotationAnglesLocal.y, m_eulerRotationAnglesLocal.z);
	}

	void Transform::tweakEulerRotationAngleX(const std::function<void(float&)>& operation)
	{
		operation(m_eulerRotationAnglesLocal.x);
		changeEulerRotationAngleX(m_eulerRotationAnglesLocal.x);
	}

	void Transform::changeEulerRotationAngleY(float y)
	{
		changeEulerRotationAngles(m_eulerRotationAnglesLocal.x, y, m_eulerRotationAnglesLocal.z);
	}

	void Transform::tweakEulerRotationAngleY(const std::function<void(float&)>& operation)
	{
		operation(m_eulerRotationAnglesLocal.y);
		changeEulerRotationAngleY(m_eulerRotationAnglesLocal.y);
	}

	void Transform::changeEulerRotationAngleZ(float z)
	{
		changeEulerRotationAngles(m_eulerRotationAnglesLocal.x, m_eulerRotationAnglesLocal.y, z);
	}

	void Transform::tweakEulerRotationAngleZ(const std::function<void(float&)>& operation)
	{
		operation(m_eulerRotationAnglesLocal.z);
		changeEulerRotationAngleZ(m_eulerRotationAnglesLocal.z);
	}



	void Transform::changeEulerRotationAngles(const cpp::Vector3D<float>& angles)
	{
		changeEulerRotationAngles(angles.x, angles.y, angles.z);
	}
	void Transform::changeEulerRotationAngles(float x, float y, float z)
	{
		m_eulerRotationAnglesLocal.x = x;
		m_eulerRotationAnglesLocal.y = y;
		m_eulerRotationAnglesLocal.z = z;
		if (m_rotationMethod == RotationMethod::euler)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakEulerRotationAngles(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_eulerRotationAnglesLocal);
		changeEulerRotationAngles(m_eulerRotationAnglesLocal);
	}





	void Transform::changeRotationAxisLocal(const cpp::Vector3D<float>& axis)
	{
		changeRotationAxisLocal(axis.x, axis.y, axis.z);
	}
	void Transform::changeRotationAxisLocal(float x, float y, float z)
	{
		m_rotationAxisLocal.x = x;
		m_rotationAxisLocal.y = y;
		m_rotationAxisLocal.z = z;
		if (m_rotationMethod == RotationMethod::quaternion)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakRotationAxisLocal(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_rotationAxisLocal);
		changeRotationAxisLocal(m_rotationAxisLocal);
	}

	void Transform::changeRotationAxisWorld(const cpp::Vector3D<float>& axis)
	{
		changeRotationAxisWorld(axis.x, axis.y, axis.z);
	}
	void Transform::changeRotationAxisWorld(float x, float y, float z)
	{
		changeRotationAxisLocal(worldToLocal(x, y, z));
	}
	void Transform::tweakRotationAxisWorld(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		auto rotationAxisWorld = localToWorld(m_rotationAxisLocal);
		operation(rotationAxisWorld);
		changeRotationAxisWorld(rotationAxisWorld);
	}





	void Transform::changeQuaternionRotationAngle(float angle)
	{
		m_quaternionRotationAngle = angle;
		if (m_rotationMethod == RotationMethod::quaternion)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakQuaternionRotationAngle(const std::function<void(float&)>& operation)
	{
		operation(m_quaternionRotationAngle);
		changeQuaternionRotationAngle(m_quaternionRotationAngle);
	}





	void Transform::changeDirectionLocal(const cpp::Vector3D<float>& direction)
	{
		changeDirectionLocal(direction.x, direction.y, direction.z);
	}
	void Transform::changeDirectionLocal(float x, float y, float z)
	{
		m_directionLocal.x = x;
		m_directionLocal.y = y;
		m_directionLocal.z = z;

		if (m_rotationMethod == RotationMethod::directionBase)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakDirectionLocal(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_directionLocal);
		changeDirectionLocal(m_directionLocal);
	}

	void Transform::changeDirectionWorld(const cpp::Vector3D<float>& direction)
	{
		changeDirectionWorld(direction.x, direction.y, direction.z);
	}
	void Transform::changeDirectionWorld(float x, float y, float z)
	{
		changeDirectionLocal(worldToLocal(x, y, z));
	}
	void Transform::tweakDirectionLWorld(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		auto directionWorld = localToWorld(m_directionLocal);
		operation(directionWorld);
		changeDirectionWorld(directionWorld);
	}





	void Transform::changeFocusPositionLocal(const cpp::Vector3D<float>& position)
	{
		changeFocusPositionLocal(position.x, position.y, position.z);
	}
	void Transform::changeFocusPositionLocal(float x, float y, float z)
	{
		m_focusPositionLocal.x = x;
		m_focusPositionLocal.y = y;
		m_focusPositionLocal.z = z;

		if (m_rotationMethod == RotationMethod::lookAt)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakFocusPositionLocal(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_focusPositionLocal);
		changeFocusPositionLocal(m_focusPositionLocal);
	}

	void Transform::changeFocusPositionWorld(const cpp::Vector3D<float>& target)
	{
		changeFocusPositionWorld(target.x, target.y, target.z);
	}
	void Transform::changeFocusPositionWorld(float x, float y, float z)
	{
		changeFocusPositionLocal(worldToLocal(x, y, z));
	}
	void Transform::tweakFocusPositionWorld(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		auto focusPositionWorld = calcFocusPositionWorld();
		operation(focusPositionWorld);
		changeFocusPositionWorld(focusPositionWorld);
	}





	void Transform::changeUpLocal(const cpp::Vector3D<float>& up)
	{
		changeUpLocal(up.x, up.y, up.z);
	}
	void Transform::changeUpLocal(float x, float y, float z)
	{
		m_upLocal.x = x;
		m_upLocal.y = y;
		m_upLocal.z = z;

		if (m_rotationMethod == RotationMethod::lookAt)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakUpLocal(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		operation(m_upLocal);
		changeUpLocal(m_upLocal);
	}

	void Transform::changeUpWorld(const cpp::Vector3D<float>& up)
	{
		changeUpWorld(up.x, up.y, up.z);
	}
	void Transform::changeUpWorld(float x, float y, float z)
	{
		changeUpLocal(worldToLocal(x, y, z));
	}
	void Transform::tweakUpWorld(const std::function<void(cpp::Vector3D<float>&)>& operation)
	{
		auto worldUp = localToWorld(m_upLocal);
		operation(worldUp);
		changeUpWorld(worldUp);
	}





	void Transform::changePolarRotationAngles(const cpp::Vector2D<float>& angles)
	{
		changePolarRotationAngles(angles.x, angles.y);
	}
	void Transform::changePolarRotationAngles(float phi, float theta)
	{
		m_polarRotationAnglesLocal.x = phi;
		m_polarRotationAnglesLocal.y = theta;

		if (m_rotationMethod == RotationMethod::polar)
		{
			m_notifyRotationChanged();
		}
	}
	void Transform::tweakPolarRotationAngles(const std::function<void(cpp::Vector2D<float>&)>& operation)
	{
		operation(m_polarRotationAnglesLocal);
		changePolarRotationAngles(m_polarRotationAnglesLocal);
	}
	
	void Transform::changePolarRotationAnglePhi(float phi)
	{
		changePolarRotationAngles(phi, m_polarRotationAnglesLocal.y);
	}
	void Transform::tweakPolarRotationAnglePhi(const std::function<void(float&)>& operation)
	{
		operation(m_polarRotationAnglesLocal.x);
		changePolarRotationAngles(m_polarRotationAnglesLocal);
	}

	void Transform::changePolarRotationAngleTheta(float theta)
	{
		changePolarRotationAngles(m_polarRotationAnglesLocal.x, theta);
	}
	void Transform::tweakPolarRotationAngleTheta(const std::function<void(float&)>& operation)
	{
		operation(m_polarRotationAnglesLocal.y);
		changePolarRotationAngles(m_polarRotationAnglesLocal);
	}









	
	cpp::Vector3D<float> Transform::calcPositionLocal() const
	{
		if (m_coordinateSystem == CoordinateSystem::rectangular)
		{
			return m_positionLocal;
		}
		else if(m_coordinateSystem == CoordinateSystem::polar)
		{
			float sinTheta = sin(m_theta);
			return m_centerLocal+cpp::Vector3D<float>(sinTheta*sin(m_phi), cos(m_theta), sinTheta*cos(m_phi)).normalized()*m_radius;
		}
		else
		{
			Assert(false, "The given CoordinateSystem is not supported.");
			return cpp::Vector3D<float>();
		}
	}
	cpp::Vector3D<float> Transform::calcPositionWorld() const
	{
		return localToWorld(calcPositionLocal());
	}
	


	cpp::Vector3D<float> Transform::calcScaleLocal() const
	{
		return m_scaleLocal;
	}



	cpp::Vector2D<float> Transform::calcPolarRotationAnglesLocal() const
	{
		return calcPolarRotationAnglesFromForward(calcForwardLocal());
	}
	cpp::Vector2D<float> Transform::calcPolarRotationAnglesWorld() const
	{
		return calcPolarRotationAnglesFromForward(calcForwardWorld());
	}



	cpp::Vector3D<float> Transform::calcCenterLocal() const
	{
		if (m_coordinateSystem != CoordinateSystem::polar)
		{
			return calcPositionLocal();
		}
		return m_centerLocal;
	}
	cpp::Vector3D<float> Transform::calcCenterWorld() const
	{
		if (m_coordinateSystem != CoordinateSystem::polar)
		{
			return calcPositionWorld();
		}
		return localToWorld(calcCenterLocal());
	}
	float Transform::calcRadius() const
	{
		if (m_coordinateSystem != CoordinateSystem::polar)
		{
			return 0.0;
		}
		return m_radius;
	}
	float Transform::calcPhi() const
	{
		if (m_coordinateSystem != CoordinateSystem::polar)
		{
			return 0.0;
		}
		return m_phi;
	}
	float Transform::calcTheta() const
	{
		if (m_coordinateSystem != CoordinateSystem::polar)
		{
			return 0.0;
		}
		return m_theta;
	}



	cpp::Vector3D<float> Transform::calcFocusPositionLocal() const
	{
		cpp::Vector3D<float> focusPosition;
		if (m_rotationMethod != RotationMethod::lookAt)
		{
			return calcPositionLocal()+calcForwardLocal();
		}

		return m_focusPositionLocal;
	}
	cpp::Vector3D<float> Transform::calcFocusPositionWorld() const
	{
		if (m_rotationMethod != RotationMethod::lookAt)
		{
			return calcPositionWorld()+calcForwardWorld();
		}

		return localToWorld(m_focusPositionLocal);
	}



	float Transform::calcQuaternionRotationAngleLocal() const
	{
		return calcQuaternionRotationAngleFromMatrix(createRotationMatrixLocal());
	}
	float Transform::calcQuaternionRotationAngleWorld() const
	{
		return calcQuaternionRotationAngleFromMatrix(createRotationMatrixWorld());
	}



	cpp::Vector3D<float> Transform::calcRotationAxisLocal() const
	{
		return calcRotationAxisFromMatrix(createRotationMatrixLocal());
	}
	cpp::Vector3D<float> Transform::calcRotationAxisWorld() const
	{
		return  calcRotationAxisFromMatrix(createRotationMatrixWorld());
	}



	cpp::Vector3D<float> Transform::calcForwardLocal() const
	{
		return calcForwardFromMatrix(createRotationMatrixLocal());
	}
	cpp::Vector3D<float> Transform::calcForwardWorld() const
	{
		return calcForwardFromMatrix(createRotationMatrixWorld());
	}



	cpp::Vector3D<float> Transform::calcUpLocal() const
	{
		return calcUpFromMatrix(createRotationMatrixLocal());
	}
	cpp::Vector3D<float> Transform::calcUpWorld() const
	{
		return calcUpFromMatrix(createRotationMatrixWorld());
	}



	cpp::Vector3D<float> Transform::calcSideLocal() const
	{
		return calcSideFromMatrix(createRotationMatrixLocal());
	}

	cpp::Vector3D<float> Transform::calcSideWorld() const
	{
		return calcSideFromMatrix(createRotationMatrixWorld());
	}



	cpp::Vector3D<float> Transform::calcEulerRotationAnglesLocal() const
	{
		return calcEulerRotationAnglesFromMatrix(createRotationMatrixLocal());
	}
	cpp::Vector3D<float> Transform::calcEulerRotationAnglesWorld() const
	{
		return calcEulerRotationAnglesFromMatrix(createRotationMatrixWorld());
	}










	DirectX::XMFLOAT4X4 Transform::createScalingMatrixLocal() const
	{
		if (m_isLocalSUpdated || m_isShapeSizeChanged)
		{
			if (m_isAddedSelfToSubject == false)
			{
				m_addSelfToSubjectDelay();
				m_isAddedSelfToSubject = true;
			}

			DirectX::XMStoreFloat4x4(&m_localS, DirectX::XMMatrixScaling(m_scaleLocal.x*m_shapeSize.x, m_scaleLocal.y*m_shapeSize.y, m_scaleLocal.z*m_shapeSize.z));
			
			m_isLocalSUpdated = false;
			m_isShapeSizeChanged = false;
		}
		return m_localS;
	}





	DirectX::XMFLOAT4X4 Transform::createRotationMatrixLocal() const
	{
		if (m_isLocalRUpdated)
		{
			if (m_rotationMethod == RotationMethod::euler)
			{
				DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();

				matrix = DirectX::XMMatrixMultiply(matrix, DirectX::XMMatrixRotationZ(m_eulerRotationAnglesLocal.z));
				matrix = DirectX::XMMatrixMultiply(matrix, DirectX::XMMatrixRotationX(m_eulerRotationAnglesLocal.x));

				DirectX::XMStoreFloat4x4(&m_localR, DirectX::XMMatrixMultiply(matrix, DirectX::XMMatrixRotationY(m_eulerRotationAnglesLocal.y)));
			}
			else if (m_rotationMethod == RotationMethod::quaternion)
			{
				DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
				if (!m_rotationAxisLocal.isZero())
				{
					DirectX::XMStoreFloat4x4(&m_localR, DirectX::XMMatrixMultiply(matrix, DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(m_rotationAxisLocal.x, m_rotationAxisLocal.y, m_rotationAxisLocal.z, 0.0f), m_quaternionRotationAngle))));
				}
				else
				{
					DirectX::XMStoreFloat4x4(&m_localR, DirectX::XMMatrixIdentity());
				}
			}
			else if (m_rotationMethod == RotationMethod::lookAt || m_rotationMethod == RotationMethod::polar || m_rotationMethod == RotationMethod::directionBase)
			{
				cpp::Vector3D<float> direction = {};
				if (m_rotationMethod == RotationMethod::lookAt)
				{
					direction = m_focusPositionLocal-calcPositionLocal();
				}
				else if(m_rotationMethod == RotationMethod::polar)
				{
					float sinTheta = sin(m_polarRotationAnglesLocal.y);
					direction = cpp::Vector3D<float>(sinTheta*sin(m_polarRotationAnglesLocal.x), cos(m_polarRotationAnglesLocal.y), sinTheta*cos(m_polarRotationAnglesLocal.x));
				}
				else if (m_rotationMethod == RotationMethod::directionBase)
				{
					direction = m_directionLocal;
				}
				const auto xAxis = m_upLocal.cross(direction).normalized();
				const auto zAxis = direction.normalized();
				const auto yAxis = zAxis.cross(xAxis);
				DirectX::XMStoreFloat4x4(&m_localR, DirectX::XMMatrixSet(xAxis.x, xAxis.y, xAxis.z, 0.0,
																		 yAxis.x, yAxis.y, yAxis.z, 0.0,
																		 zAxis.x, zAxis.y, zAxis.z, 0.0,
																		 0.0f,    0.0f,    0.0f,    1.0f));			
			}
			else
			{
				DirectX::XMStoreFloat4x4(&m_localR, DirectX::XMMatrixIdentity());
			}

			m_isLocalRUpdated = false;
		}

		return m_localR;
	}
	DirectX::XMFLOAT4X4 Transform::createRotationMatrixWorld() const
	{
		m_updateWorldRT();

		if (m_isWorldRUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_worldR, DirectX::XMMatrixSet(m_worldRT._11, m_worldRT._12, m_worldRT._13, 0.0f,
					                                                 m_worldRT._21, m_worldRT._22, m_worldRT._23, 0.0f,
					                                                 m_worldRT._31, m_worldRT._32, m_worldRT._33, 0.0f,
					                                                 0.0f,          0.0f,          0.0f,          1.0f));

			m_isWorldRUpdated = false;
		}

		return m_worldR;
	}





	DirectX::XMFLOAT4X4 Transform::createTranslationMatrixLocal() const
	{
		const auto positionLocal = calcPositionLocal();
		if (m_isLocalTUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_localT, DirectX::XMMatrixTranslation(positionLocal.x, positionLocal.y, positionLocal.z));

			m_isLocalTUpdated = false;
		}
		return m_localT;
	}
	DirectX::XMFLOAT4X4 Transform::createTranslationMatrixWorld() const
	{
		m_updateWorldRT();

		if (m_isWorldTUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_worldT, DirectX::XMMatrixSet(1.0f,          0.0f,          0.0f,          0.0,
				                                                     0.0f,          1.0f,          0.0f,          0.0,
				                                                     0.0f,          0.0f,          1.0f,          0.0,
				                                                     m_worldRT._41, m_worldRT._42, m_worldRT._43, 1.0f));

			m_isWorldTUpdated = false;
		}

		return m_worldT;
	}





	DirectX::XMFLOAT4X4 Transform::createLocalMatrix() const
	{
		if (m_isLocalUpdated)
		{
			DirectX::XMStoreFloat4x4(&m_local, DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&createScalingMatrixLocal()), DirectX::XMLoadFloat4x4(&createRotationMatrixLocal())), DirectX::XMLoadFloat4x4(&createTranslationMatrixLocal())));

			m_isLocalUpdated = false;
		}

		return m_local;
	}
	DirectX::XMFLOAT4X4 Transform::createWorldMatrix() const
	{
		m_updateWorldRT();

		if (m_isWorldUpdated || m_isShapeSizeChanged)
		{
			DirectX::XMStoreFloat4x4(&m_world, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&createScalingMatrixLocal()), DirectX::XMLoadFloat4x4(&m_worldRT)));

			m_isWorldUpdated = false;
		}

		return m_world;
	}
}
