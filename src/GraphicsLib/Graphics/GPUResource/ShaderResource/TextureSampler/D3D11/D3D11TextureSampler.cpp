#include <Graphics/GPUResource/ShaderResource/TextureSampler/D3D11/D3D11TextureSampler.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/ShaderResourceMemoryAccessor/D3D11/D3D11TextureSamplerState.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cg
{
	namespace d3d11
	{
		TextureSampler::TextureSampler(const TextureSamplerDescriptor& desc)
		{
			cpp::com_ptr<ID3D11SamplerState> samplerState;
			auto hr = D3D11CreateFunctions::createTextureSamplerState(Device::getDevice().Get(), desc, samplerState.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create TextureSamplerState");
			}
			m_state = std::make_shared<TextureSamplerState>(getID(), samplerState);
		}
		void TextureSampler::set(ShaderStage stage, int unit)
		{
			m_state->set(stage, unit);
		}
		BoundedBufferLocationList TextureSampler::getBoundedBufferLocationList() const
		{
			return BoundedBufferLocationList();
		}
	}
}
