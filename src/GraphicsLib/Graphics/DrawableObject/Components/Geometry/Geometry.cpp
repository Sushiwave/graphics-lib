#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Geometry.hpp>





namespace cg
{
	Geometry::Part::Part(const std::string& name, std::shared_ptr<IGeometryBuffer> geometryBuffer, PrimitiveTopology topology)
		: m_name(name),
		  m_geometryBuffer(geometryBuffer),
		  primitiveTopology(topology)
	{
	}

	Geometry::Part::Part(const std::string& name, const Material& material, std::shared_ptr<IGeometryBuffer> geometryBuffer, PrimitiveTopology topology)
		: m_name(name),
		  material(material),
		  m_geometryBuffer(geometryBuffer),
		  primitiveTopology(topology)
	{
	}

	std::string Geometry::Part::getName() const noexcept
	{
		return m_name;
	}

	std::shared_ptr<IGeometryBuffer> Geometry::Part::getGeometryBuffer() const noexcept
	{
		return m_geometryBuffer;
	}
	Geometry::Geometry()
		: m_empty(true),
		  parts({ {} })
	{
	}
	Geometry::Geometry(std::shared_ptr<Shape> shape, const Parts parts)
		: m_empty(false),
		  shape(shape),
		  parts(parts)
	{
	}
	bool Geometry::empty() const
	{
		return m_empty;
	}
	Geometry::Parts::Parts(const PartDict& partDict)
		: m_partDict(partDict)
	{
	}
	Geometry::Part Geometry::Parts::get(const std::string& name) const
	{
		return m_partDict.at(name);
	}
	Geometry::Parts::PartNameList Geometry::Parts::makePartNameList() const
	{
		PartNameList list;
		for (auto pair : m_partDict)
		{
			list.emplace_back(pair.first);
		}
		return list;
	}
}
