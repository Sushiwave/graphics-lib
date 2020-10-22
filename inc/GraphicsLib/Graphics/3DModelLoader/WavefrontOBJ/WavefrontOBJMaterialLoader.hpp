#pragma once
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJMaterial.hpp>






namespace cg
{
	namespace wavefrontobj
	{
		class MaterialLoader
		{
		public:
			[[nodiscard]]  static MaterialDict load(const std::string& filename);
		};
	}
}
