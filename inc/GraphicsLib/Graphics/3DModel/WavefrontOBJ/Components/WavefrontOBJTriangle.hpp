#pragma once
#include "WavefrontOBJVertex.hpp"
#include <GraphicsLib/Graphics/3DModel/Components/Triangle.hpp>





namespace cg
{
	namespace wavefrontobj
	{
		template <typename Vertex_>
		using Triangle = Triangle_<Vertex_>;
	}
}