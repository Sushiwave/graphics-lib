#pragma once
#include <GraphicsLib/Graphics/ShaderCodeParser/Components/ShaderResourceLocationDict.hpp>





namespace cg
{
	class IShaderCodeParser
	{
	public:
		[[nodiscard]] virtual ShaderResourceLocationDict parseShaderResourceLocation() = 0;
	};
}
