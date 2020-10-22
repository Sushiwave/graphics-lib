#pragma once
#include <GraphicsLib/Graphics/3DModel/Components/Triangles.hpp>
#include "WavefrontOBJVertex.hpp"





namespace cg
{
	namespace wavefrontobj
	{
		template <typename Vertex_>
		using Triangles = Triangles_<Vertex_>;
	}
}