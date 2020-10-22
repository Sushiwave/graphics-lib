#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class ConstantBufferView
			: public ShaderResourceMemoryAccessor
		{
		public:
			ConstantBufferView() = default;
			virtual ~ConstantBufferView() = default;
			ConstantBufferView(const ID& id, const cpp::com_ptr<ID3D11Buffer>& cpD3DBuffer);
		};
	}
}
