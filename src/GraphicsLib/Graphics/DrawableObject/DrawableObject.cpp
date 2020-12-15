#include <GraphicsLib/Graphics/DrawableObject/DrawableObject.hpp>





namespace cg
{
	DrawableObject::DrawableObject(const std::string& name, const std::shared_ptr<Shape>& shape, const Parts& parts)
		: m_name(name),
		  m_shape(shape),
		  m_transform(std::make_shared<Transform>(shape)),
		  transform(m_transform.get()),
		  parts(parts)
	{
	}

	void DrawableObject::moveTo(const std::string& renderingGroupName)
	{
		m_renderingGroupName = renderingGroupName;
		notify();
	}

	std::string DrawableObject::whichRenderingGroupBelongTo() const noexcept
	{
		return m_renderingGroupName;
	}
	
	void DrawableObject::tweakTransform(const std::function<void(Transform&)>& operation) const
	{
		operation(*m_transform);
	}
	
	ID DrawableObject::getID() const noexcept
	{
		return m_id;
	}

	std::string DrawableObject::getName() const noexcept
	{
		return m_name;
	}

	DrawableObject::Part::Part(const std::string& name, std::shared_ptr<IGeometryBuffer> geometryBuffer)
		: m_name(name),
		  m_geometryBuffer(geometryBuffer)
	{
	}

	DrawableObject::Part::Part(const std::string& name, const Material& material, std::shared_ptr<IGeometryBuffer> geometryBuffer)
		: m_name(name),
		  material(material),
		  m_geometryBuffer(geometryBuffer)
	{
	}

	std::string DrawableObject::Part::getName() const noexcept
	{
		return m_name;
	}

	std::shared_ptr<IGeometryBuffer> DrawableObject::Part::getGeometryBuffer() const noexcept
	{
		return m_geometryBuffer;
	}
}
