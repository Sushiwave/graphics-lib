#pragma once
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/IAlphaBlendState.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class AlphaBlendState
		: public GPUResource,
		  public IAlphaBlendState
	{
	public:
		using SetCall = std::function<void()>;
	private:
		SetCall m_setCall;
	public:
		AlphaBlendState(const SetCall& setCall);
		virtual ~AlphaBlendState() = default;

		static void release();

		void set() override;
	};
}
