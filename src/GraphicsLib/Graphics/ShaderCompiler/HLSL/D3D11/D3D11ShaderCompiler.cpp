#include <Graphics/ShaderCompiler/HLSL/D3D11/D3D11ShaderCompiler.hpp>
#include <GraphicsLib/System/System.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Window/Components/WINAPI/WindowHandle/WINAPIWindowHandle.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>




namespace cg
{
	namespace d3d
	{
	#define MAX_STR_LEN 256

		cpp::com_ptr<ID3DBlob> ShaderCompiler::compile(const char* sourceCode, const size_t sourceCodeLength, const char* entryPoint, const char* model)
		{
			cpp::com_ptr<ID3DBlob> blob;
			ID3DBlob* errBlob;

			UINT flag = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
#if defined(DEBUG) || defined(_DEBUG)
			flag |= D3DCOMPILE_DEBUG;
#endif
			auto hr = D3DCompile(
				sourceCode, 
				sourceCodeLength, 
				nullptr, 
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryPoint,
				model,
				flag,
				NULL,
				blob.ReleaseAndGetAddressOf(),
				&errBlob
			);

			if (FAILED(hr))
			{
				if (errBlob)
				{
					throw COM_RUNTIME_ERROR(hr, (char*)errBlob->GetBufferPointer());
				}
				else
				{
					throw COM_RUNTIME_ERROR(hr, "Faile to compile the given source code.");
				}
			}

			return blob;
		}

		cpp::com_ptr<ID3DBlob> ShaderCompiler::compileFromFile(const char* filename, const char* entryPoint, const char* model)
		{
			cpp::com_ptr<ID3DBlob> blob;
			ID3DBlob* errBlob;

			WCHAR  convertedStr_filename[MAX_STR_LEN];
			size_t convertedStrLen;
			mbstowcs_s(&convertedStrLen, convertedStr_filename, filename, MAX_STR_LEN);
		
			UINT flag = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
#if defined(DEBUG) || defined(_DEBUG)
			flag |= D3DCOMPILE_DEBUG;
#endif
			auto hr = D3DCompileFromFile(
				convertedStr_filename,
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryPoint,
				model,
				flag,
				NULL,
				blob.ReleaseAndGetAddressOf(),
				&errBlob
			);
		
			if (FAILED(hr)) 
			{
				if (errBlob)
				{
					throw COM_RUNTIME_ERROR(hr, (char*)errBlob->GetBufferPointer());
				}
				else
				{
					throw COM_RUNTIME_ERROR(hr, std::string("Faile to compile ") + filename);
				}
			}
			return blob;
		}
	}
}