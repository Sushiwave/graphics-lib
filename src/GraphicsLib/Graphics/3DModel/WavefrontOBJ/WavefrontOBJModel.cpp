#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/WavefrontOBJModel.hpp>





namespace cg
{
	WavefrontOBJModel::WavefrontOBJModel()
		: size(),
		  minXYZ(),
		  groupList()
	{
	}
	WavefrontOBJModel::WavefrontOBJModel(const cpp::Vector3D<float>& size, const cpp::Vector3D<float>& minXYZ, const GroupList& groupList) noexcept
		: size(size),
		  minXYZ(minXYZ),
		  groupList(groupList)
	{
	}
	WavefrontOBJModel::Group::Group(const std::string& name, wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, unsigned int vertexCount, unsigned int triangleCount, int vertexByteSize, std::shared_ptr<void> vertices, std::shared_ptr<void> triangles, const wavefrontobj::Indices& indices, const wavefrontobj::Material& material)
		: m_positionDimensionCount(positionDimensionCount),
		  name(name),
		  vertexFormat(vertexFormat),
		  vertexByteSize(vertexByteSize),
		  vertexCount(vertexCount),
		  triangleCount(triangleCount),
		  m_vertices(vertices),
		  m_triangles(triangles),
		  indices(indices),
		  material(material)
	{
	}
	void* WavefrontOBJModel::Group::vertices() const
	{
		if (m_positionDimensionCount == 3)
		{
			switch (vertexFormat)
			{
			case wavefrontobj::VertexFormat::p:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition3>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pt:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition3UV2>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pn:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition3Normal3>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pnt:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition3Normal3UV2>>(m_vertices))[0];
			}
		}
		else if (m_positionDimensionCount == 4)
		{
			switch (vertexFormat)
			{
			case wavefrontobj::VertexFormat::p:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition4>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pt:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition4UV2>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pn:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition4Normal3>>(m_vertices))[0];
			case wavefrontobj::VertexFormat::pnt:
				return &(*std::reinterpret_pointer_cast<wavefrontobj::Vertices<wavefrontobj::VertexPosition4Normal3UV2>>(m_vertices))[0];
			}
		}

		return nullptr;
	}
}
