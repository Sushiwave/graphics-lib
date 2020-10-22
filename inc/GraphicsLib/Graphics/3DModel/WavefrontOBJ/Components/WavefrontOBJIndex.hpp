#pragma once





namespace cg
{
	namespace wavefrontobj
	{
		struct Index
		{
			unsigned int vertex;
			unsigned int normal;
			unsigned int uv;

			Index() noexcept;
			virtual ~Index() = default;
		};
	}
}
