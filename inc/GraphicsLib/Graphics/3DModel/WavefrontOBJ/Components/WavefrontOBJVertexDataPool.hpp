#pragma once
#include "WavefrontOBJVertex.hpp"





namespace cg
{
	namespace wavefrontobj
	{
		template <typename T>
		class Pool
		{
		private:
			std::vector<T> m_pool;
		public:
			Pool() = default;
			virtual ~Pool() = default;

			[[nodiscard]] T get(int index) const
			{
				return m_pool.at(index);
			}
			void add(const T& data)
			{
				m_pool.emplace_back(data);
			}
			void clear()
			{
				m_pool.clear();
			}
		};

		class VertexDataPool
		{
		public:
			VertexDataPool() = default;
			virtual ~VertexDataPool() = default;

			Pool<Position3> position3DataPool;
			Pool<Position4> position4DataPool;
			Pool<Normal3> normal3DataPool;
			Pool<UV2> uv2DataPool;
		};
	}
}