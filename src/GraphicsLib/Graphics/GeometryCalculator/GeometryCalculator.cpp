#include <GraphicsLib/Graphics/GeometryCalculator/GeometryCalculator.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>

#define _USE_MATH_DEFINES
#include <cmath>
#include <unordered_map>
#include <DirectXMath.h>





namespace cg
{
	GeometryCalculator::PositionList GeometryCalculator::calcBoxVertexPositionTRIANGLELIST(float width, float height, float depth)
	{
		Assert(0 < width,  "width must be greater than 0.");
		Assert(0 < height, "height must be greater than 0.");
		Assert(0 < depth,  "depth must be greater than 0.");


		float halfWidth = width*0.5f;
		float halfHeight = height*0.5f;
		float halfDepth = depth*0.5f;

		return
		{
			//right
			cpp::Vector3D<float>(halfWidth,  halfHeight, -halfDepth),
			cpp::Vector3D<float>(halfWidth,  halfHeight,  halfDepth),
			cpp::Vector3D<float>(halfWidth, -halfHeight,  halfDepth),
			cpp::Vector3D<float>(halfWidth, -halfHeight, -halfDepth),

			//left
			cpp::Vector3D<float>(-halfWidth,  halfHeight,  halfDepth),
			cpp::Vector3D<float>(-halfWidth,  halfHeight, -halfDepth),
			cpp::Vector3D<float>(-halfWidth, -halfHeight, -halfDepth),
			cpp::Vector3D<float>(-halfWidth, -halfHeight,  halfDepth),

			//top
			cpp::Vector3D<float>(-halfWidth,  halfHeight,  halfDepth),
			cpp::Vector3D<float>( halfWidth,  halfHeight,  halfDepth),
			cpp::Vector3D<float>( halfWidth,  halfHeight, -halfDepth),
			cpp::Vector3D<float>(-halfWidth,  halfHeight, -halfDepth),

			//bottom
			cpp::Vector3D<float>(-halfWidth, -halfHeight, -halfDepth),
			cpp::Vector3D<float>( halfWidth, -halfHeight, -halfDepth),
			cpp::Vector3D<float>( halfWidth, -halfHeight,  halfDepth),
			cpp::Vector3D<float>(-halfWidth, -halfHeight,  halfDepth),

			//back
			cpp::Vector3D<float>(-halfWidth, -halfHeight,  halfDepth),
			cpp::Vector3D<float>( halfWidth, -halfHeight,  halfDepth),
			cpp::Vector3D<float>( halfWidth,  halfHeight,  halfDepth),
			cpp::Vector3D<float>(-halfWidth,  halfHeight,  halfDepth),

			//front
			cpp::Vector3D<float>(-halfWidth,  halfHeight, -halfDepth),
			cpp::Vector3D<float>( halfWidth,  halfHeight, -halfDepth),
			cpp::Vector3D<float>( halfWidth, -halfHeight, -halfDepth),
			cpp::Vector3D<float>(-halfWidth, -halfHeight, -halfDepth)
		};
	};

	const GeometryCalculator::NormalList GeometryCalculator::m_boxNormalTRIANGLELIST =
	{
		cpp::Vector3D<float>(1.0, 0.0, 0.0),
		cpp::Vector3D<float>(1.0, 0.0, 0.0),
		cpp::Vector3D<float>(1.0, 0.0, 0.0),
		cpp::Vector3D<float>(1.0, 0.0, 0.0),

		cpp::Vector3D<float>(-1.0, 0.0, 0.0),
		cpp::Vector3D<float>(-1.0, 0.0, 0.0),
		cpp::Vector3D<float>(-1.0, 0.0, 0.0),
		cpp::Vector3D<float>(-1.0, 0.0, 0.0),

		cpp::Vector3D<float>(0.0, 1.0, 0.0),
		cpp::Vector3D<float>(0.0, 1.0, 0.0),
		cpp::Vector3D<float>(0.0, 1.0, 0.0),
		cpp::Vector3D<float>(0.0, 1.0, 0.0),

		cpp::Vector3D<float>(0.0, -1.0, 0.0),
		cpp::Vector3D<float>(0.0, -1.0, 0.0),
		cpp::Vector3D<float>(0.0, -1.0, 0.0),
		cpp::Vector3D<float>(0.0, -1.0, 0.0),

		cpp::Vector3D<float>(0.0, 0.0, 1.0),
		cpp::Vector3D<float>(0.0, 0.0, 1.0),
		cpp::Vector3D<float>(0.0, 0.0, 1.0),
		cpp::Vector3D<float>(0.0, 0.0, 1.0),

		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0)
	};

	GeometryCalculator::NormalList GeometryCalculator::calcBoxNormalTRIANGLELIST()
	{
		return m_boxNormalTRIANGLELIST;
	}

	const GeometryCalculator::UVList GeometryCalculator::m_boxUVTRIANGLELIST =
	{
		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),

		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),

		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),

		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),

		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),

		cpp::Vector2D<float>(1.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 0.0f)
	};

	GeometryCalculator::UVList GeometryCalculator::calcBoxUVTRIANGLELIST()
	{
		return m_boxUVTRIANGLELIST;
	}

	unsigned int GeometryCalculator::calcBoxVertexCountTRIANGLELIST()
	{
		return static_cast<unsigned int>(m_boxUVTRIANGLELIST.size());
	}


	const GeometryCalculator::Indices GeometryCalculator::m_boxIndexTRIANGLELIST =
	{
		0,1,3,
		1,2,3,

		4,5,7,
		5,6,7,

		8,9,11,
		9,10,11,

		12,13,15,
		13,14,15,

		16,17,19,
		17,18,19,

		20,21,23,
		21,22,23
	};

	GeometryCalculator::Indices GeometryCalculator::calcBoxIndexTRIANGLELIST()
	{
		return m_boxIndexTRIANGLELIST;
	}










	GeometryCalculator::PositionList GeometryCalculator::calcPlanePositionTRIANGLELIST(float width, float height, float z)
	{
		auto halfWidth = width * 0.5f;
		auto halfHeight = height * 0.5f;

		return
		{
			cpp::Vector3D<float>(-halfWidth, -halfHeight,  z),
			cpp::Vector3D<float>(-halfWidth,  halfHeight,  z),
			cpp::Vector3D<float>(halfWidth, -halfHeight,  z),
			cpp::Vector3D<float>(halfWidth,  halfHeight,  z)
		};
	}

	const GeometryCalculator::NormalList GeometryCalculator::m_planeNormalTRIANGLELIST =
	{
		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0),
		cpp::Vector3D<float>(0.0, 0.0, -1.0)
	};

	GeometryCalculator::NormalList GeometryCalculator::calcPlaneNormalTRIANGLELIST()
	{
		return m_planeNormalTRIANGLELIST;
	}

	const GeometryCalculator::UVList GeometryCalculator::m_planeUVTRIANGLELIST =
	{
		cpp::Vector2D<float>(0.0f, 0.0f),
		cpp::Vector2D<float>(0.0f, 1.0f),
		cpp::Vector2D<float>(1.0f, 0.0f),
		cpp::Vector2D<float>(1.0f, 1.0f)
	};

	const GeometryCalculator::Indices GeometryCalculator::m_planeIndexTRIANGLELIST
	{
		0, 1, 3,
		3, 2, 0
	};

	GeometryCalculator::UVList GeometryCalculator::calcPlaneUVTRIANGLELIST()
	{
		return m_planeUVTRIANGLELIST;
	}

	GeometryCalculator::Indices GeometryCalculator::calcPlaneIndexTRIANGLELIST()
	{
		return m_planeIndexTRIANGLELIST;
	}

	unsigned int GeometryCalculator::calcPlaneVertexCountTRIANGLELIST()
	{
		return static_cast<unsigned int>(m_planeUVTRIANGLELIST.size());
	}










	GeometryCalculator::PositionList GeometryCalculator::calcSphereVertexPositionTRIANGLELIST(float radius, unsigned int sliceCount, unsigned int stackCount)
	{
		Assert(0 < radius, "radius must be greater than 0.");

		PositionList positionList;
		positionList.reserve(calcSphereVertexCountTRIANGLELIST(sliceCount, stackCount));

		positionList.emplace_back(cpp::Vector3D<float>(0.0, radius, 0.0));

		float phiStep = DirectX::XM_PI / static_cast<float>(stackCount);
		float thetaStep = 2.0f * DirectX::XM_PI / static_cast<float>(sliceCount);
		for (unsigned int i = 1; i <= stackCount-1; ++i)
		{
			float phi = i * phiStep;
			for (unsigned int j = 0; j <= sliceCount; ++j)
			{
				float theta = j * thetaStep;
				auto p =
					cpp::Vector3D<float>(
						radius*sin(phi)*cos(theta),
						radius*cos(phi),
						radius*sin(phi)*sin(theta)
						);
				positionList.emplace_back(p);
			}
		}

		positionList.emplace_back(cpp::Vector3D<float>(0.0, -radius, 0.0));

		return positionList;
	}

	GeometryCalculator::NormalList GeometryCalculator::calcSphereNormal(const PositionList& vertexPositionList)
	{
		NormalList normalList;
		auto vertexCount = vertexPositionList.size();
		normalList.reserve(vertexCount);
		for (size_t i = 0; i < vertexCount; ++i)
		{
			normalList.emplace_back(vertexPositionList[i].normalized());
		}
		return normalList;
	}

	GeometryCalculator::UVList GeometryCalculator::calcSphereUVTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount)
	{
		UVList uvList;
		uvList.reserve(calcSphereVertexCountTRIANGLELIST(sliceCount, stackCount));

		const auto& firstUV = cpp::Vector2D<float>(0.0f, 0.0f);
		uvList.emplace_back(firstUV);

		float phiStep = DirectX::XM_PI / static_cast<float>(stackCount);
		float thetaStep = 2.0f * DirectX::XM_PI / static_cast<float>(sliceCount);

		for (unsigned int i = 0; i < stackCount - 1; ++i)
		{
			float phi = i * phiStep;
			for (unsigned int j = 0; j < sliceCount; ++j)
			{
				float theta = j * thetaStep;
				const auto& uv = cpp::Vector2D<float>(theta/(DirectX::XM_PI * 2.0f), phi/DirectX::XM_PI);
				uvList.emplace_back(uv);
			}
		}

		const auto& lastUV = cpp::Vector2D<float>(0.0f, 1.0f);
		uvList.emplace_back(lastUV);

		return uvList;
	}

	unsigned int GeometryCalculator::calcSphereVertexCountTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount)
	{
		return (sliceCount+1)*(stackCount-1)+2;
	}

	GeometryCalculator::Indices GeometryCalculator::calcSphereIndexTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount)
	{
		unsigned int c = 0;

		GeometryCalculator::Indices indices;
		unsigned int offset = 0;



		for (unsigned i = 1; i <= sliceCount; ++i)
		{
			indices.emplace_back(0);
			indices.emplace_back(offset+i+1);
			indices.emplace_back(offset+i);
		}



		offset = 1;
		auto ringVertexCount = sliceCount+1;
		for (unsigned int i = 0; i < stackCount-2; i++)
		{
			for (unsigned int j = 0; j < sliceCount; j++)
			{
				auto ul = offset+i*ringVertexCount+j;
				auto ur = offset+i*ringVertexCount+j+1;
				auto ll = offset+(i+1)*ringVertexCount+j;
				auto lr = offset+(i+1)*ringVertexCount+j+1;

				indices.emplace_back(ul);
				indices.emplace_back(ur);
				indices.emplace_back(ll);

				indices.emplace_back(ll);
				indices.emplace_back(ur);
				indices.emplace_back(lr);
			}
		}



		auto lastIndex = calcSphereVertexCountTRIANGLELIST(sliceCount, stackCount)-1;
		offset = lastIndex-ringVertexCount;
		for (unsigned int i = 0; i < sliceCount; ++i)
		{
			indices.emplace_back(lastIndex);
			indices.emplace_back(offset+i);
			indices.emplace_back(offset+i+1);
		}



		return indices;
	}










	GeometryCalculator::NormalList GeometryCalculator::calcNormal(const GeometryCalculator::PositionList& positionList, const GeometryCalculator::Indices& indexList)
	{
		const auto vertexCount = positionList.size();

		GeometryCalculator::NormalList normalList;
		normalList.resize(vertexCount);

		auto faceCountList = std::vector<int>();
		faceCountList.resize(vertexCount);

		const auto indexListSize = indexList.size();
		for (unsigned int i = 0; i < indexListSize; i += 3)
		{
			const auto i1 = indexList[i];
			const auto i2 = indexList[static_cast<size_t>(i)+1];
			const auto i3 = indexList[static_cast<size_t>(i)+2];

			const auto& v1 = positionList[i1];
			const auto& v2 = positionList[i2];
			const auto& v3 = positionList[i3];

			const auto& faceNormal = (v2 - v1).cross(v3 - v1).normalized();

			normalList[i1] = faceNormal;
			normalList[i2] = faceNormal;
			normalList[i3] = faceNormal;

			++faceCountList[i1];
			++faceCountList[i2];
			++faceCountList[i3];
		}
		for (size_t i = 0; i < vertexCount; ++i)
		{
			normalList[i] /= faceCountList[i];
			normalList[i].normalize();
		}

		return normalList;
	}
}
