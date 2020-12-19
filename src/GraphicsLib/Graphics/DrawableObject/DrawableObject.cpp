#include <GraphicsLib/Graphics/DrawableObject/DrawableObject.hpp>





namespace cg
{
	DrawableObject::DrawableObject(const std::string& name, const Geometry& geometry)
		: Transformable(geometry.getShapeP<Shape>()),
		  m_name(name),
		  geometry(geometry)
	{
	}

	DrawableObject::DrawableObject(const std::string& name)
		: m_name(name)
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
	
	ID DrawableObject::getID() const noexcept
	{
		return m_id;
	}

	std::string DrawableObject::getName() const noexcept
	{
		return m_name;
	}
}
