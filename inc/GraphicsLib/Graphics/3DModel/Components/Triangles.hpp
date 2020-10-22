#pragma once
#include <GraphicsLib/Graphics/3DModel/Components/Triangle.hpp>

#include <vector>





namespace cg
{
	template <typename Vertex_>
	using Triangles_ = std::vector<Triangle_<Vertex_>>;
}
