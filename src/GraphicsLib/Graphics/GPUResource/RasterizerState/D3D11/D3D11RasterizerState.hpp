#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/Components/CullMode.hpp>
#include <GraphicsLib/Graphics/GPUResource/RasterizerState/RasterizerState.hpp>





namespace cg
{
	namespace d3d11
	{
		class RasterizerState
			: public cg::RasterizerState
		{
		private:
			cpp::com_ptr<ID3D11RasterizerState> m_state;
		public:
			RasterizerState(CullMode cullMode = CullMode::none, bool isWireFrameMode = false, bool multisampleEnable = false, bool antialiassedLineEnable = false, bool frontCounterClockwise = false, bool depthClipEnable = false, bool scissorEnable = false);
			virtual ~RasterizerState() = default;
		};
	}
}