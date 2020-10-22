#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include <ThirdParty/CPPLib/DataStructure/Array/Array2.hpp>
#include <ThirdParty/CPPLib/DataStructure/Array/Array3.hpp>
#include <ThirdParty/CPPLib/DataStructure/Array/Array4.hpp>
#include <vector>





namespace cg
{
	namespace wavefrontobj
	{
		using Normal3 = cpp::Array3<float>;
		using UV2 = cpp::Array2<float>;
		template <int size_>
		using Position = cpp::Array_<float, size_>;
		using Position4 = Position<4>;
		using Position3 = Position<3>;
		
		using UV2List       = std::vector<UV2>;
		using Normal3List   = std::vector<Normal3>;
		using Position3List = std::vector<Position3>;
		using Position4List = std::vector<Position4>;

		struct VertexPosition3
		{
			Position3 position = {};

			VertexPosition3()
			{
			}
			VertexPosition3(Position3 position, Normal3 normal, UV2 uv)
				: position(position)
			{
			}
			VertexPosition3(Position4 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition3UV2
		{
			Position3 position = {};
			UV2 uv = {};

			VertexPosition3UV2()
			{
			}
			VertexPosition3UV2(Position3 position, Normal3 normal, UV2 uv)
				: position(position),
				  uv(uv)
			{
			}
			VertexPosition3UV2(Position4 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition3Normal3
		{
			Position3 position = {};
			Normal3 normal = {};

			VertexPosition3Normal3()
			{
			}
			VertexPosition3Normal3(Position3 position, Normal3 normal, UV2 uv)
				: position(position),
				  normal(normal)
			{
			}
			VertexPosition3Normal3(Position4 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition3Normal3UV2
		{
			Position3 position = {};
			Normal3 normal = {};
			UV2 uv = {};

			VertexPosition3Normal3UV2()
			{
			}
			VertexPosition3Normal3UV2(Position3 position, Normal3 normal, UV2 uv)
				: position(position),
				  normal(normal),
				  uv(uv)
			{
			}
			VertexPosition3Normal3UV2(Position4 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition4
		{
			Position4 position = {};

			VertexPosition4()
			{
			}
			VertexPosition4(Position4 position, Normal3 normal, UV2 uv)
				: position(position)
			{
			}
			VertexPosition4(Position3 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition4UV2
		{
			Position4 position = {};
			UV2 uv = {};

			VertexPosition4UV2()
			{
			}
			VertexPosition4UV2(Position4 position, Normal3 normal, UV2 uv)
				: position(position),
				  uv(uv)
			{
			}
			VertexPosition4UV2(Position3 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition4Normal3
		{
			Position4 position = {};
			Normal3 normal = {};

			VertexPosition4Normal3()
			{
			}
			VertexPosition4Normal3(Position4 position, Normal3 normal, UV2 uv)
				: position(position),
				  normal(normal)
			{
			}
			VertexPosition4Normal3(Position3 position, Normal3 normal, UV2 uv)
			{
			}
		};
		struct VertexPosition4Normal3UV2
		{
			Position4 position = {};
			Normal3 normal = {};
			UV2 uv = {};

			VertexPosition4Normal3UV2()
			{
			}
			VertexPosition4Normal3UV2(Position4 position, Normal3 normal, UV2 uv)
				: position(position),
				  normal(normal),
				  uv(uv)
			{
			}
			VertexPosition4Normal3UV2(Position3 position, Normal3 normal, UV2 uv)
			{
			}
		};
	}
}