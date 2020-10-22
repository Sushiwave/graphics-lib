#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3dcompiler.h>





namespace cg
{
	namespace d3d
	{
		class ShaderCompiler
		{
		public:
			[[nodiscard]] static cpp::com_ptr<ID3DBlob> compile(const char* sourceCode, const size_t sourceCodeLength, const char* entryPoint, const char* model);
			[[nodiscard]] static cpp::com_ptr<ID3DBlob> compileFromFile(const char* filename, const char* entryPoint, const char* model);
		};
	}
}
