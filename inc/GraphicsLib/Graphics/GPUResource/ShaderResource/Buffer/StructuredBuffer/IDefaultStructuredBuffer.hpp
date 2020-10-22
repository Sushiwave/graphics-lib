#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/StructuredBuffer/Base/IStructuredBuffer.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/Components/Constant.hpp>





namespace cg
{
	class IDefaultStructuredBuffer
		: public virtual IStructuredBuffer
	{
		virtual void update(const Constant& constant) = 0;
		virtual void copy(std::shared_ptr<IStructuredBuffer> src) = 0;
		virtual void set(ShaderStage stage, int unit, GPUAccessFlags usage) = 0;
	};
}