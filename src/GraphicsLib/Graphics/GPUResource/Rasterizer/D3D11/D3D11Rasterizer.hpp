#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Rasterizer/Components/CullMode.hpp>
#include <GraphicsLib/Graphics/GPUResource/Rasterizer/Rasterizer.hpp>





namespace cg
{
	namespace d3d11
	{
		class Rasterizer
			: public cg::Rasterizer
		{
		private:
			cpp::com_ptr<ID3D11RasterizerState> m_state;
		public:
			Rasterizer(CullMode cullMode = CullMode::none, bool isWireFrameMode = false, bool multisampleEnable = false, bool antialiassedLineEnable = false, bool frontCounterClockwise = false, bool depthClipEnable = false, bool scissorEnable = false);
			virtual ~Rasterizer() = default;
		};
	}
}