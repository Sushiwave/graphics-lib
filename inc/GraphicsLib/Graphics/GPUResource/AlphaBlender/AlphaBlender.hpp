#pragma once
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/IAlphaBlender.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class AlphaBlender
		: public GPUResource,
		  public IAlphaBlender
	{
	public:
		using SetCall = std::function<void()>;
	private:
		SetCall m_setCall;
	public:
		AlphaBlender(const SetCall& setCall);
		virtual ~AlphaBlender() = default;

		static void release();

		void set() override;
	};
}
