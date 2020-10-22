#pragma once
#include "ID.hpp"





namespace cg
{
	class IIDHolder
	{
	public:
		[[nodiscard]] virtual ID getID() const = 0;
	};
}
