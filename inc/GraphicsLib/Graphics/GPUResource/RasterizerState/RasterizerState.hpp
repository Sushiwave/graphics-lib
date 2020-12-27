#pragma once
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/IRasterizerState.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class RasterizerState
		: public GPUResource,
		  public IRasterizerState
	{
	public:
		using SetCall = std::function<void()>;
	private:
		SetCall m_setCall;
	public:
		RasterizerState(const SetCall& setCall);
		virtual ~RasterizerState() = default;

		void set() override;
		static void release();
	};
}
