#pragma once
#include <GraphicsLib/Graphics/DrawableObject/Components/Material/Material.hpp>
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>
#include <GraphicsLib/Graphics/GPUResource/GeometryBuffer/IGeometryBuffer.hpp>
#include <ThirdParty/CPPLib/DesignPattern/Observer/Subject.hpp>
#include <GraphicsLib/ID/IIDHolder.hpp>
#include <GraphicsLib/Graphics/Transform/Transform.hpp>





namespace cg
{
	class DrawableObject
		: public cpp::Subject,
		  public IIDHolder 
	{
	public:
		class Part
		{
		private:
			std::shared_ptr<IGeometryBuffer> m_geometryBuffer;
			std::string m_name;
		public:
			Part(const std::string& name, std::shared_ptr<IGeometryBuffer> geometryBuffer);
			Part(const std::string& name, const Material& material, std::shared_ptr<IGeometryBuffer> geometryBuffer);
			virtual ~Part() = default;

			Material material;
		
			[[nodiscard]] std::string getName() const noexcept;
			std::shared_ptr<IGeometryBuffer> getGeometryBuffer() const noexcept;
		};
		using Parts = std::unordered_map<std::string, Part>;
	private:
		std::string m_name;
		ID m_id;

		std::string m_renderingGroupName;
		std::shared_ptr<Shape> m_shape;
		std::shared_ptr<Transform> m_transform;
	public:
		Transform* const transform;

		const Parts parts;

		int instanceCount = 0;
		PrimitiveTopology primitiveTopology = PrimitiveTopology::DEFAULT;
	public:
		DrawableObject(const std::string& name, const std::shared_ptr<Shape>& shape, const Parts& parts);
		virtual ~DrawableObject() = default;



		void moveTo(const std::string& renderingGroupName);
		[[nodiscard]] std::string whichRenderingGroupBelongTo() const noexcept;



		template <typename Shape_>
		void tweakShape(const std::function<void(const Shape_&)>& operation)
		{
			operation(*std::dynamic_pointer_cast<Shape_>(m_shape));
		}
		void tweakTransform(const std::function<void(Transform&)>& operation) const;



		[[nodiscard]] ID getID() const noexcept override;
		[[nodiscard]] std::string getName() const noexcept;
		template <typename Shape_>
		[[nodiscard]] Shape_ getShape() const
		{
			return *std::dynamic_pointer_cast<Shape_>(m_shape);
		}
		template <typename T>
		[[nodiscard]] std::shared_ptr<T> getShapeP() const
		{
			return std::dynamic_pointer_cast<T>(m_shape);
		}
	};
}
