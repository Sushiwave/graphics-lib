#pragma once
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJMaterial.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJTriangles.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJVertexFormat.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJVertices.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJIndices.hpp>
#include <GraphicsLib/Context.hpp>
#include <ThirdParty/CPPLib/C++/SFINAE.hpp>

#include <memory>
#include <algorithm>
#include <functional>





namespace cg
{
	class WavefrontOBJModel
	{
	public:
		class Group
		{
		private:
			DEFINE_SFINAE_HAS_MEMBER(normal);
			DEFINE_SFINAE_HAS_MEMBER(uv);
		private:
			const int m_positionDimensionCount;
			const std::shared_ptr<void> m_vertices;
			const std::shared_ptr<void> m_triangles;
		public:
			const std::string name;
			const wavefrontobj::VertexFormat vertexFormat;
			const unsigned long long vertexByteSize;
			const unsigned long long vertexCount;
			const unsigned long long triangleCount;

			const wavefrontobj::Indices indices;
			const wavefrontobj::Material material;
		private:
			template <typename VertexSRC_, typename VertexDEST_>
			void m_copyPositionData(std::vector<VertexDEST_>* dest, const cpp::Vector3D<float>& offset) const
			{
				const auto offsetPosition = [&](auto& position)
				{
					position[0] += offset.x;
					position[1] += offset.y;
					position[2] += offset.z;
				};

				const auto src = std::reinterpret_pointer_cast<wavefrontobj::Vertices<VertexSRC_>>(m_vertices);

				const auto srcSize = src->size();
				dest->resize(srcSize);
				const auto destPositionDimensionCount = (*dest)[0].position.size();

				std::function<void(size_t)> copy;
				if (destPositionDimensionCount == 3 && m_positionDimensionCount == 4)
				{
					copy = [&](size_t i)
					{
						auto& srcPosition = src->at(i).position;
						offsetPosition(srcPosition);
						auto& destPosition = (*dest)[i].position;
						std::copy(srcPosition.begin(), srcPosition.end()-1, destPosition.begin());
					};
				}
				else if (destPositionDimensionCount == 4 && m_positionDimensionCount == 3)
				{
					copy = [&](size_t i)
					{
						auto& srcPosition = src->at(i).position;
						offsetPosition(srcPosition);
						auto& destPosition = (*dest)[i].position;
						std::copy(srcPosition.begin(), srcPosition.end(), destPosition.begin());
						destPosition[3] = 1.0;
					};
				}
				else
				{
					copy = [&](size_t i)
					{
						auto& srcPosition = src->at(i).position;
						offsetPosition(srcPosition);
						auto& destPosition = (*dest)[i].position;
						std::copy(srcPosition.begin(), srcPosition.end(), destPosition.begin());
					};
				}

				for (size_t i = 0; i < srcSize; ++i)
				{
					copy(i);
				}
			}
			template <typename VertexSRC_, typename VertexDEST_>
			void m_copyNormalData(std::vector<VertexDEST_>* dest) const
			{
				const auto src = std::reinterpret_pointer_cast<wavefrontobj::Vertices<VertexSRC_>>(m_vertices);
				const auto srcSize = src->size();
				dest->resize(srcSize);
				for (size_t i = 0; i < srcSize; ++i)
				{
					(*dest)[i].normal = src->at(i).normal;
				}
			}
			template <typename VertexSRC_, typename VertexDEST_>
			void m_copyUVData(std::vector<VertexDEST_>* dest) const
			{
				const auto src = std::reinterpret_pointer_cast<wavefrontobj::Vertices<VertexSRC_>>(m_vertices);
				const auto srcSize = src->size();
				dest->resize(srcSize);
				for (size_t i = 0; i < srcSize; ++i)
				{
					(*dest)[i].uv = src->at(i).uv;
				}
			}
		public:
			Group(const std::string& name, wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount,	unsigned int vertexCount, unsigned int triangleCount, int vertexByteSize, std::shared_ptr<void> vertices, std::shared_ptr<void> triangles, const wavefrontobj::Indices& indices, const wavefrontobj::Material& material);
			virtual ~Group() = default;
		
			template <typename Vertex_>
			void copyPositionDataTo(std::vector<Vertex_>* dest, const cpp::Vector3D<float>& offset) const
			{
				if (m_positionDimensionCount == 3)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::p:
						m_copyPositionData<wavefrontobj::VertexPosition3, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pt:
						m_copyPositionData<wavefrontobj::VertexPosition3UV2, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pn:
						m_copyPositionData<wavefrontobj::VertexPosition3Normal3, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyPositionData<wavefrontobj::VertexPosition3Normal3UV2, Vertex_>(dest, offset);
						break;
					}
				}
				else if (m_positionDimensionCount == 4)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::p:
						m_copyPositionData<wavefrontobj::VertexPosition4, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pt:
						m_copyPositionData<wavefrontobj::VertexPosition4UV2, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pn:
						m_copyPositionData<wavefrontobj::VertexPosition4Normal3, Vertex_>(dest, offset);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyPositionData<wavefrontobj::VertexPosition4Normal3UV2, Vertex_>(dest, offset);
						break;
					}
				}
			}
			template <typename Vertex_>
			void copyNormalDataTo(std::vector<Vertex_>* dest) const
			{
				if (m_positionDimensionCount == 3)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::pn:
						m_copyNormalData<wavefrontobj::VertexPosition3Normal3, Vertex_>(dest);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyNormalData<wavefrontobj::VertexPosition3Normal3UV2, Vertex_>(dest);
						break;
					}
				}
				else if (m_positionDimensionCount == 4)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::pn:
						m_copyNormalData<wavefrontobj::VertexPosition4Normal3, Vertex_>(dest);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyNormalData<wavefrontobj::VertexPosition4Normal3UV2, Vertex_>(dest);
						break;
					}
				}
			}
			template <typename Vertex_>
			void copyUVDataTo(std::vector<Vertex_>* dest) const
			{
				if (m_positionDimensionCount == 3)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::pt:
						m_copyUVData<wavefrontobj::VertexPosition3UV2, Vertex_>(dest);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyUVData<wavefrontobj::VertexPosition3Normal3UV2, Vertex_>(dest);
						break;
					}
				}
				else if (m_positionDimensionCount == 4)
				{
					switch (vertexFormat)
					{
					case wavefrontobj::VertexFormat::pt:
						m_copyUVData<wavefrontobj::VertexPosition4UV2, Vertex_>(dest);
						break;
					case wavefrontobj::VertexFormat::pnt:
						m_copyUVData<wavefrontobj::VertexPosition4Normal3UV2, Vertex_>(dest);
						break;
					}
				}
			}
			template <typename Vertex_>
			void copyVertexDataTo(std::vector<Vertex_>* dest, const cpp::Vector3D<float>& positionOffset, SFINAE_hasnt_normal<Vertex_> = nullptr, SFINAE_hasnt_uv<Vertex_> = nullptr) const
			{
				copyPositionDataTo(dest, positionOffset);
			}
			template <typename Vertex_>
			void copyVertexDataTo(std::vector<Vertex_>* dest, const cpp::Vector3D<float>& positionOffset, SFINAE_hasnt_normal<Vertex_> = nullptr, SFINAE_has_uv<Vertex_> = nullptr) const
			{
				copyPositionDataTo(dest, positionOffset);
				copyUVDataTo(dest);
			}
			template <typename Vertex_>
			void copyVertexDataTo(std::vector<Vertex_>* dest, const cpp::Vector3D<float>& positionOffset, SFINAE_has_normal<Vertex_> = nullptr, SFINAE_hasnt_uv<Vertex_> = nullptr) const
			{
				copyPositionDataTo(dest, positionOffset);
				copyNormalDataTo(dest);
			}
			template <typename Vertex_>
			void copyVertexDataTo(std::vector<Vertex_>* dest, const cpp::Vector3D<float>& positionOffset, SFINAE_has_normal<Vertex_> = nullptr, SFINAE_has_uv<Vertex_> = nullptr) const
			{
				copyPositionDataTo(dest, positionOffset);
				copyNormalDataTo(dest);
				copyUVDataTo(dest);
			}

			void* vertices() const;
		};
		using GroupList = std::vector<Group>;
	public:
		const cpp::Vector3D<float> size;
		const cpp::Vector3D<float> minXYZ;
		const GroupList groupList;
	public:
		WavefrontOBJModel();
		WavefrontOBJModel(const cpp::Vector3D<float>& size, const cpp::Vector3D<float>& minXYZ, const GroupList& groupList) noexcept;
		virtual ~WavefrontOBJModel() = default;
	};
}
