#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>

#include <vector>





namespace cg
{
	class GeometryCalculator
	{
	public:
		using UVList = std::vector<cpp::Vector2D<float>>;
		using Indices = std::vector<unsigned int>;
		using PositionList = std::vector<cpp::Vector3D<float>>;
		using NormalList = std::vector<cpp::Vector3D<float>>;
	private:
		static const Indices    m_boxIndexTRIANGLELIST;
		static const NormalList m_boxNormalTRIANGLELIST;
		static const UVList     m_boxUVTRIANGLELIST;

		static const Indices    m_planeIndexTRIANGLELIST;
		static const UVList     m_planeUVTRIANGLELIST;
		static const NormalList m_planeNormalTRIANGLELIST;
	public:
		[[nodiscard]] static PositionList calcPlanePositionTRIANGLELIST(float width, float height, float z);
		[[nodiscard]] static NormalList   calcPlaneNormalTRIANGLELIST();
		[[nodiscard]] static Indices      calcPlaneIndexTRIANGLELIST();
		[[nodiscard]] static UVList       calcPlaneUVTRIANGLELIST();
		[[nodiscard]] static unsigned int calcPlaneVertexCountTRIANGLELIST();





		[[nodiscard]] static PositionList calcBoxVertexPositionTRIANGLELIST(float width, float height, float depth);
		[[nodiscard]] static NormalList   calcBoxNormalTRIANGLELIST();
		[[nodiscard]] static Indices      calcBoxIndexTRIANGLELIST();
		[[nodiscard]] static UVList       calcBoxUVTRIANGLELIST();
		[[nodiscard]] static unsigned int calcBoxVertexCountTRIANGLELIST();





		[[nodiscard]] static PositionList calcSphereVertexPositionTRIANGLELIST(float radius, unsigned int sliceCount, unsigned int stackCount);
		[[nodiscard]] static NormalList   calcSphereNormal(const PositionList& vertexPositionList);
		[[nodiscard]] static Indices      calcSphereIndexTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount);
		[[nodiscard]] static UVList       calcSphereUVTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount);
		[[nodiscard]] static unsigned int calcSphereVertexCountTRIANGLELIST(unsigned int sliceCount, unsigned int stackCount);





		[[nodiscard]] static NormalList calcNormal(const PositionList& positionList, const Indices& indices);
	};
}