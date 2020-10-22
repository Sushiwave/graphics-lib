#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/Components/Constant.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/ConstantBuffer/Base/IConstantBuffer.hpp>





namespace cg
{
	class IDynamicConstantBuffer
		: public virtual IConstantBuffer
	{
	public:
		virtual void update(const Constant& constant) = 0;
		virtual void copy(std::shared_ptr<IConstantBuffer> src) = 0;
	};
}
