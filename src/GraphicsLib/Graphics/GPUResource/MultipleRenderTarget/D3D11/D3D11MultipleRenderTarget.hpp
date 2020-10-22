#pragma once
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTarget/MultipleRenderTarget.hpp>

struct ID3D11RenderTargetView;





namespace cg
{
	namespace d3d11
	{
		class MultipleRenderTarget
			: public cg::MultipleRenderTarget
		{
		private:
			std::shared_ptr<ID3D11RenderTargetView*> m_renderTargetViewArray;
		public:
			MultipleRenderTarget() = default;
			MultipleRenderTarget(const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList);
			virtual ~MultipleRenderTarget() = default;



			MultipleRenderTarget& operator=(const MultipleRenderTarget& other);
		};
	}
}