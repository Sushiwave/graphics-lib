#pragma once
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/Components/ShaderResourceBufferLocationList.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IShaderResourceMemoryAccessor
		: public virtual IGPUResource
	{
	public:
		virtual void set(ShaderStage stage, int unit) = 0;

		[[nodiscard]] virtual ShaderResourceBufferLocationList getManagedShaderResourceBufferLocationList() const = 0;
	};
}