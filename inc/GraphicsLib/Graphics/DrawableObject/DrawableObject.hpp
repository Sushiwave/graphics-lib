#pragma once
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Geometry.hpp>
#include <ThirdParty/CPPLib/DesignPattern/Observer/Subject.hpp>
#include <GraphicsLib/ID/IIDHolder.hpp>
#include <GraphicsLib/Graphics/Transform/Transformable.hpp>





namespace cg
{
	class DrawableObject
		: public cpp::Subject,
		  public Transformable,
		  public IIDHolder 
	{
	private:
		std::string m_name;
		ID m_id;

		std::string m_renderingGroupName;
	public:
		Geometry geometry;

		int instanceCount = 0;
	public:
		DrawableObject(const std::string& name, const Geometry& geometry);
		DrawableObject(const std::string& name);
		virtual ~DrawableObject() = default;



		void moveToAnotherRenderingGroup(const std::string& renderingGroupName);
		[[nodiscard]] std::string getNameOfRenderingGroupToWhichThisBelongs() const noexcept;



		[[nodiscard]] ID getID() const noexcept override;
		[[nodiscard]] std::string getName() const noexcept;
	};
}
