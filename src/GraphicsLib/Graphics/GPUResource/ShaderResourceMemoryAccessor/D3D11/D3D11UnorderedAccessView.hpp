#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class UnorderedAccessView
			: public ShaderResourceMemoryAccessor
		{
		public:
			UnorderedAccessView() = default;
			virtual ~UnorderedAccessView() = default;
			UnorderedAccessView(ShaderResourceType type, const cpp::com_ptr<ID3D11UnorderedAccessView>& cpD3DUAV);
		};
	}
}
