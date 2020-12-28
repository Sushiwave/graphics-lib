#pragma once
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Shape/Base/Shape.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>





namespace cg
{
	class AnyModel
		: public Shape
	{
	private:
		cpp::Vector3D<float> m_modelOriginalSize;
	public:
		AnyModel(const cpp::Vector3D<float>& modelOriginalSize);
		AnyModel(float modelOriginalWidth, float modelOriginalHeight, float modelOriginalDepth);
		virtual ~AnyModel() = default;
	};
}