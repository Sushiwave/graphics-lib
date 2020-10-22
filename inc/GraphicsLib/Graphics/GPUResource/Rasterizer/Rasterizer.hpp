#pragma once
#include <GraphicsLib/Graphics/GPUResource/Rasterizer/IRasterizer.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class Rasterizer
		: public GPUResource,
		  public IRasterizer
	{
	public:
		using SetCall = std::function<void()>;
	private:
		SetCall m_setCall;
	public:
		Rasterizer(const SetCall& setCall);
		virtual ~Rasterizer() = default;

		void set() override;
		static void release();
	};
}
