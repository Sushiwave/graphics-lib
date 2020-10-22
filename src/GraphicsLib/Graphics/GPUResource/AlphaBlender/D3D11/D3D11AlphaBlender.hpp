#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/Components/AlphaBlenderDescriptor.hpp>
#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/AlphaBlender.hpp>





namespace cg
{
	namespace d3d11
	{
		class AlphaBlender
			: public cg::AlphaBlender
		{
		private:
			float m_blendFactor[4];

			cpp::com_ptr<ID3D11BlendState> m_blendState;
		public:
			AlphaBlender() = default;
			AlphaBlender(const AlphaBlenderDescriptor& descriptor);
			virtual ~AlphaBlender() = default;
		};
	}
}