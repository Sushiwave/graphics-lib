#pragma once





namespace cg
{
	class IScreenUpdater
	{
	public:
		[[nodiscard]] virtual bool update() = 0;
	};
}
