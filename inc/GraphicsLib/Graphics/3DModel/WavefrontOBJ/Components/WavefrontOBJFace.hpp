#pragma once
#include <GraphicsLib/Graphics/3DModel/Components/Face.hpp>
#include "WavefrontOBJVertex.hpp"





namespace cg
{
	namespace wavefrontobj
	{
		template <typename Vertex_>
		using Face = Face_<Vertex_>;
	}
}
