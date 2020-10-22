#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/IShader.hpp>





namespace cg
{
	class IComputeShader
		: public virtual IShader
	{
	public:
		virtual void dispatch(int x, int y, int z) = 0;
	};
}
