#pragma once
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/ShaderCodeParser/Components/ShaderResourceLocationDict.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/IGPUResource.hpp>





namespace cg
{
	class IShader
		: public virtual IGPUResource
	{
	public:
		[[nodiscard]] virtual ShaderStage getShaderStage() const = 0;
		[[nodiscard]] virtual ShaderResourceLocationDict getResourceLocationDict() const = 0;

		virtual void set() const = 0;
	};
}