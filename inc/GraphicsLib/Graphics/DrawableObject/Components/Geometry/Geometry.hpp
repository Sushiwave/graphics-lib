#pragma once
#include <GraphicsLib/Graphics/GPUResource/GeometryBuffer/IGeometryBuffer.hpp>
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Material/Material.hpp>
#include <GraphicsLib/Graphics/Shape/Base/Shape.hpp>





namespace cg
{
	class Geometry
	{
	public:
		class Part
		{
		private:
			std::shared_ptr<IGeometryBuffer> m_geometryBuffer;
			std::string m_name;
		public:
			Material material;
			PrimitiveTopology primitiveTopology = PrimitiveTopology::DEFAULT;
		public:
			Part(const std::string& name, std::shared_ptr<IGeometryBuffer> geometryBuffer, PrimitiveTopology topology);
			Part(const std::string& name, const Material& material, std::shared_ptr<IGeometryBuffer> geometryBuffer, PrimitiveTopology topology);
			virtual ~Part() = default;

			[[nodiscard]] std::string getName() const noexcept;
			std::shared_ptr<IGeometryBuffer> getGeometryBuffer() const noexcept;
		};
		class Parts
		{
		public:
			using PartDict = std::unordered_map<std::string, Part>;
			using PartNameList = std::vector<std::string>;
		private:
			PartDict m_partDict;
		public:
			Parts(const PartDict& partDict);
			virtual ~Parts() = default;

			Part get(const std::string& name) const;
			PartNameList makePartNameList() const;
		};
	private:
		std::shared_ptr<Shape> m_shape;
	public:
		const Parts parts;
	public:
		Geometry();
		Geometry(std::shared_ptr<Shape> shape, const Parts parts);
		virtual ~Geometry() = default;

		template <typename Shape_>
		void tweakShape(const std::function<void(const Shape_&)>& operation)
		{
			operation(*std::dynamic_pointer_cast<Shape_>(m_shape));
		}
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
