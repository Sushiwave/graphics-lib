#include <GraphicsLib/Graphics/Shape/AnyModel.hpp>
#include <algorithm>





namespace cg
{
	AnyModel::AnyModel(const cpp::Vector3D<float>& modelOriginalSize)
		: Shape(1.0f/std::max(std::max(modelOriginalSize.x, modelOriginalSize.y), modelOriginalSize.z))
	{
	}
	AnyModel::AnyModel(float modelOriginalWidth, float modelOriginalHeight, float modelOriginalDepth)
		: AnyModel(cpp::Vector3D<float>(modelOriginalWidth, modelOriginalHeight, modelOriginalDepth))
	{
	}
}

