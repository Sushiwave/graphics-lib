#pragma once





namespace cg
{
	namespace wavefrontobj
	{
		enum class VertexFormat
		{
			p = 1,
			n = 2,
			t = 4,
			pnt = p | n | t,
			pn = p | n,
			pt = p | t,
		};
	}
}