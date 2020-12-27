#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/Components/AlphaBlendDescriptor.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/AlphaBlendState.hpp>





namespace cg
{
	namespace d3d11
	{
		class AlphaBlendState
			: public cg::AlphaBlendState
		{
		private:
			float m_blendFactor[4];

			cpp::com_ptr<ID3D11BlendState> m_blendState;
		public:
			AlphaBlendState() = default;
			AlphaBlendState(const AlphaBlendDescriptor& descriptor);
			virtual ~AlphaBlendState() = default;
		};
	}
}